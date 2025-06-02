#include "common/log/log.h"
#include "sql/operator/update_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/delete_stmt.h"


RC UpdatePhysicalOperator::open(Trx* trx) 
{
    if(children_.empty()) {
        return RC::SUCCESS;
    }
    std::unique_ptr<PhysicalOperator>& child = children_[0];
    RC rc = child->open(trx);
    if(rc != RC::SUCCESS) {
        LOG_WARN("failed to open child operator: %s", strrc(rc));
        return rc;  
    }
    trx_ = trx;

    // 第一阶段：收集所有需要更新的记录
    while (RC::SUCCESS == (rc = child->next())) {
        Tuple *tuple = child->current_tuple();
        if (nullptr == tuple) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
            return rc;
        }

        RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
        Record &record = row_tuple->record();
        records_.emplace_back(std::move(record));
    }

    child->close();

    // 第二阶段：执行更新操作（先删除再插入）
    for (Record &record : records_) {
        rc = trx_->delete_record(table_, record);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to update:delete record: %s", strrc(rc));
            return rc;
        }
        ::memcpy(record.data() + value_offset_, value_.data(), value_.length());
        // new Record then insert
        if(value_.attr_type() == AttrType::CHARS) {
            *(record.data() + value_.length() + value_offset_) = '\0';
        }
        rc = trx_->insert_record(table_, record);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to update:insert record: %s", strrc(rc));
            return rc;        
        }
    }

    return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
    return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
    return RC::SUCCESS;
}


