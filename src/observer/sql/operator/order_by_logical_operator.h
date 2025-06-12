#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子
 * @ingroup LogicalOperator
 */
class OrderByLogicalOperator : public LogicalOperator
{
public:
  OrderByLogicalOperator(std::vector<OrderBySqlNode> order_by) : order_by_(std::move(order_by)) {}

  LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }

  std::vector<OrderBySqlNode> &order_by() { return order_by_; }

private:
  std::vector<OrderBySqlNode> order_by_;
};