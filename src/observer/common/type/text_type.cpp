#include "common/utils.h"
#include "common/type/text_type.h"
#include "common/value.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"

int TextType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::TEXTS && right.attr_type() == AttrType::TEXTS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

int TextType::cast_cost(AttrType type)
{
  if (type == AttrType::CHARS || type == AttrType::TEXTS) {
    return 0;
  }
  if (type == AttrType::DATES) {
    return 1;
  }
  if (type == AttrType::INTS) {
    return 1;
  }
  if (type == AttrType::FLOATS) {
    return 1;
  }
  return INT32_MAX;
}

RC TextType::cast_to(const Value &val, AttrType type, Value &result, bool allow_type_promotion) const
{
  switch (type) {
    case AttrType::TEXTS: {
      result.set_text(val.value_.pointer_value_, val.length_);
    } break;
    case AttrType::DATES: {
      int date_val;
      RC  rc = parse_date(val.value_.pointer_value_, date_val);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      result.set_date(date_val);
    } break;
    case AttrType::INTS: {
      float float_val;
      RC    rc = parse_float_prefix(val.value_.pointer_value_, float_val);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      int int_val = static_cast<int>(float_val);
      // 是整数
      if (int_val == float_val || !allow_type_promotion) {
        result.set_int(int_val);
      } else {

        result.set_float(float_val);
      }
    } break;
    case AttrType::FLOATS: {
      float float_val;
      RC    rc = parse_float_prefix(val.value_.pointer_value_, float_val);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      result.set_float(float_val);
    } break;
    default: return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

RC TextType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}

RC TextType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}