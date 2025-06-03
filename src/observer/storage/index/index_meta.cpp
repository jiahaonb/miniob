/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELDS("fields");
const static Json::StaticString FIELD_UNIQUE("unique");

RC IndexMeta::init(const char *name, const vector<FieldMeta> &fields, bool unique)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  if (fields.empty()) {
    LOG_ERROR("Failed to init index, fields is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_   = name;
  fields_ = fields;
  unique_ = unique;
  
  // Calculate total length and offsets
  fields_total_len_ = 0;
  fields_offset_.clear();
  for (const auto &field : fields_) {
    fields_offset_.push_back(fields_total_len_);
    fields_total_len_ += field.len();
  }
  
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  json_value[FIELD_UNIQUE] = unique_;
  
  Json::Value fields_value(Json::arrayValue);
  for (const FieldMeta &field : fields_) {
    Json::Value field_value;
    field.to_json(field_value);
    fields_value.append(std::move(field_value));
  }
  json_value[FIELD_FIELDS] = std::move(fields_value);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &fields_value = json_value[FIELD_FIELDS];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!fields_value.isArray() || fields_value.size() <= 0) {
    LOG_ERROR("Field name is not a string. json value=%s", fields_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  vector<FieldMeta> fields;
  for (Json::ArrayIndex i = 0; i < fields_value.size(); i++) {
    const Json::Value &field_value = fields_value[i];
    FieldMeta field;
    RC rc = FieldMeta::from_json(field_value, field);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to deserialize table meta. table name =%s", table.name());
      return rc;
    }
    fields.push_back(field);
  }

  bool unique = false;
  if (json_value.isMember(FIELD_UNIQUE.c_str())) {
    const Json::Value &unique_value = json_value[FIELD_UNIQUE];
    if (!unique_value.isBool()) {
      LOG_ERROR("Index unique flag is not a boolean. json value=%s", unique_value.toStyledString().c_str());
      return RC::INTERNAL;
    }
    unique = unique_value.asBool();
  }

  return index.init(name_value.asCString(), fields, unique);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const vector<FieldMeta> &IndexMeta::fields() const
{
  return fields_;
}

bool IndexMeta::unique() const
{
  return unique_;
}

int IndexMeta::fields_total_len() const
{
  return fields_total_len_;
}

const vector<int> &IndexMeta::fields_offset() const
{
  return fields_offset_;
}

char *IndexMeta::make_entry_from_record(const char *record)
{
  char *entry = new char[fields_total_len_];
  make_entry_from_record(entry, record);
  return entry;
}

void IndexMeta::make_entry_from_record(char *entry, const char *record)
{
  for (size_t i = 0; i < fields_.size(); i++) {
    const auto &field = fields_[i];
    memcpy(entry + fields_offset_[i], record + field.offset(), field.len());
  }
}

void IndexMeta::desc(ostream &os) const
{
  os << "index name=" << name_ << ", unique=" << unique_ << ", fields=[";
  for (size_t i = 0; i < fields_.size(); i++) {
    if (i > 0) {
      os << ", ";
    }
    os << fields_[i].name();
  }
  os << "]";
}