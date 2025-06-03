#include "sql/operator/physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/expr/expression_tuple.h"
#include <functional>
#include <queue>

class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator(std::vector<OrderBySqlNode> order_by);

  virtual ~OrderByPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  std::vector<OrderBySqlNode> &order_by() { return order_by_; }

  RC fetch_and_sort_tables();
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  std::vector<OrderBySqlNode> order_by_;

  using order_line = pair<vector<Value>, Tuple *>;
  using order_func = std::function<bool(const order_line &, const order_line &)>;
  using order_list = std::priority_queue<order_line, vector<order_line>, order_func>;
  order_list order_and_field_line;

  Tuple *tuple_ = nullptr;
};
