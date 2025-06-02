#pragma once

// In miniob, rc.h is typically under common/sys/rc.h or similar
// Adjust if common/sys/rc.h is not the correct path in the target project.
#include "common/sys/rc.h" 

class SQLStageEvent; // Forward declaration, ensure this class/type is available in miniob

/**
 * @brief 删除表的执行器
 * @ingroup Executor
 */
class DropTableExecutor
{
public:
  DropTableExecutor()          = default;
  virtual ~DropTableExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
}; 