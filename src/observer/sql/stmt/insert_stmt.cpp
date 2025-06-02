/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db,  InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }


  // check the fields number
  Value     *values     = inserts.values.data();
  const int        value_num  = static_cast<int>(inserts.values.size());
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  auto filed_metas = table_meta.field_metas();
  // 合法性判断
  for (int i=0;i<filed_metas->size();i++) {
    auto &filed = (*filed_metas)[i];
    auto &value = values[i];
    if ( values[i].attr_type() != filed.type()) {
      // 类型不匹配时尝试转型，chars 可以转成 text
      Value to_value;
      RC    rc = Value::cast_to(values[i], filed.type(), to_value);
      if (OB_FAIL(rc)) {
        LOG_WARN("value doesn't match: %s != %s", attr_type_to_string(values[i].attr_type()), attr_type_to_string(filed.type()));
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      values[i] = to_value;
    }
    
    switch (filed.type())
    {
      case AttrType::DATES: {
        if(!DateType::check_date(value.get_int())) {
          LOG_WARN("not a valid date%u",value.get_int());
          return RC::INVALID_ARGUMENT;
        }
      } break;
      default: break;
    }
  }  


  // everything alright
  stmt = new InsertStmt(table, values, value_num);
  return RC::SUCCESS;
}

