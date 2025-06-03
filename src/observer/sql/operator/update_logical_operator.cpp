
#include "update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(
    BaseTable *table, std::vector<FieldMeta> field_metas, std::vector<std::unique_ptr<Expression>> values)
    : table_(table), field_metas_(std::move(field_metas)), values_(std::move(values))
{}
