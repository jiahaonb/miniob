#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const Value& value, int value_offset, int field_len) : table_(table), value_(value), value_offset_(value_offset), field_len_(field_len) 
{}