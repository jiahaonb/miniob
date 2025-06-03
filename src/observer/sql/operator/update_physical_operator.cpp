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
    records_.clear();
    while (RC::SUCCESS == (rc = child->next())) {
        Tuple *tuple = child->current_tuple();
        if (nullptr == tuple) {
            LOG_WARN("child->next() succeeded but current_tuple() is null, rc=%s", strrc(rc));
            child->close();
            return RC::INTERNAL;
        }

        RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
        Record record_copy;
        rc = record_copy.copy_data(row_tuple->record().data(), row_tuple->record().len());
        if (rc != RC::SUCCESS) {
            LOG_WARN("Failed to copy data for record_copy: %s", strrc(rc));
            child->close();
            return rc;
        }
        record_copy.set_rid(row_tuple->record().rid());
        records_.emplace_back(std::move(record_copy));
    }

    if (rc != RC::RECORD_EOF) {
        LOG_WARN("child operator next() failed with: %s", strrc(rc));
        child->close();
        return rc;
    }
    rc = RC::SUCCESS;

    child->close();

    // 第二阶段：执行更新操作（先删除再插入）
    for (Record &old_record_from_vec : records_) {
        rc = trx_->delete_record(table_, old_record_from_vec);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to update:delete record: %s", strrc(rc));
            return rc;
        }

        Record new_record;
        RC copy_rc = new_record.copy_data(old_record_from_vec.data(), old_record_from_vec.len());
        if (copy_rc != RC::SUCCESS) {
            LOG_WARN("failed to copy old_record_from_vec data to new_record: %s", strrc(copy_rc));
            return copy_rc;
        }
        new_record.set_rid(old_record_from_vec.rid());

        // 检查值长度是否超过字段长度
        if (this->value_.length() > this->field_len_) {
            LOG_WARN("Value length (%d) exceeds field length (%d), will be truncated",
                     this->value_.length(), this->field_len_);
        }

        RC set_rc = new_record.set_field(this->value_offset_, this->field_len_, this->value_);
        if (set_rc != RC::SUCCESS) {
             LOG_WARN("failed to set field in new_record: %s, offset: %d, len: %d",
                      strrc(set_rc), this->value_offset_, this->field_len_);
             return set_rc;
        }

        rc = trx_->insert_record(table_, new_record);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to update:insert new_record: %s", strrc(rc));
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


