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
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include "common/value.h"
#include "common/sys/rc.h"

// Helper function to create a null value for miniob
inline Value create_null_value() {
  Value val;
  val.set_null(true);
  return val;
}

// Helper function to check if a value is null
inline bool is_value_null(const Value& val) {
  // In miniob, we need to check if the value was explicitly set as null
  // For aggregation purposes, we'll also consider UNDEFINED values as null
  return val.attr_type() == AttrType::UNDEFINED;
}

class Aggregator
{
public:
  virtual ~Aggregator() = default;

  virtual RC accumulate(const Value &value) = 0;
  virtual RC evaluate(Value &result)        = 0;

protected:
  Value value_ = create_null_value();
};

class CountAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    if (is_value_null(value)) {
      return RC::SUCCESS;
    }
    count_++;
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    result = Value(count_);
    return RC::SUCCESS;
  }

private:
  int count_ = 0;
};

class AvgAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    if (is_value_null(value)) {
      return RC::SUCCESS;
    }
    if (is_value_null(value_)) {
      value_ = value;
      count_ = 1;
    } else {
      Value::add(value, value_, value_);
      count_++;
    }
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    if (count_ > 0) {
      Value avg = value_;
      avg       = Value(avg.get_float() / static_cast<float>(count_));
      result    = avg;
    } else {
      result = create_null_value();
    }
    return RC::SUCCESS;
  }

private:
  int count_ = 0;
};

#define _agg(FUN)                            \
public:                                      \
  RC accumulate(const Value &value) override \
  {                                          \
    if (is_value_null(value)) {              \
      return RC::SUCCESS;                    \
    }                                        \
    if (is_value_null(value_)) {             \
      value_ = value;                        \
    } else {                                 \
      FUN;                                   \
    }                                        \
    return RC::SUCCESS;                      \
  }                                          \
  RC evaluate(Value &result) override        \
  {                                          \
    result = value_;                         \
    return RC::SUCCESS;                      \
  }

class SumAggregator : public Aggregator
{
  _agg(Value::add(value, value_, value_))
};

class MaxAggregator : public Aggregator
{
  _agg(if (value.compare(value_) > 0) { value_ = value; })
};

class MinAggregator : public Aggregator
{
  _agg(if (value.compare(value_) < 0) { value_ = value; })
};
