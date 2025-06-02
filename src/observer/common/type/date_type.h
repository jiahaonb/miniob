#pragma once

#include "common/type/data_type.h"

/**
 * @brief 日期类型
 * @ingroup DateType
 */
class DateType : public DataType
{
public:
  DateType() : DataType(AttrType::DATES) {}
  ~DateType() override = default;
  // 不用实现 cast to，也不需要考虑其他类型转 date
  int cast_cost(AttrType type) override;
  int compare(const Value &left, const Value &right) const override;
  RC  to_string(const Value &val, string &result) const override;
};
