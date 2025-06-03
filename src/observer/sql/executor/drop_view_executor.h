#pragma once

#include "src/common/sys/rc.h"

class SQLStageEvent;

/**
 * @brief 删除视图的执行器
 * @ingroup Executor
 */
class DropViewExecutor
{
public:
  DropViewExecutor()          = default;
  virtual ~DropViewExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};
