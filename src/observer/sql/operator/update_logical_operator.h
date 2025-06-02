/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include <string>
#include "sql/operator/logical_operator.h"

using namespace std;

class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const string &attribute_name, const Value *value);

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table *table() const { return table_; }
  const string &attribute_name() const { return attribute_name_; }
  const Value *value() const { return value_; }

private:
  Table *table_;
  string attribute_name_;
  const Value *value_;
}; 