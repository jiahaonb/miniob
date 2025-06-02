#include "sql/stmt/drop_table_stmt.h"
#include "sql/parser/parse_defs.h" // For DropTableSqlNode
#include "common/log/log.h"      // For sql_debug, if not already in a common header
// #include "event/sql_debug.h" // In miniob-big_order, this was the include for sql_debug, check if different in miniob

// Assuming sql_debug is a macro or function available for logging.
// If it's not available or has a different name in miniob, this will need adjustment.
// For now, let's assume a similar logging facility exists.
// If sql_debug is specifically from "event/sql_debug.h" and that path doesn't exist/is different,
// we might need to adapt or find an alternative logging mechanism.

RC DropTableStmt::create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt)
{
  // todo: check if db is used. In the source it is not used.
  // If not used, it can be removed from the signature in both .h and .cpp
  stmt = new DropTableStmt(drop_table.relation_name);
  LOG_DEBUG("drop table statement: table name %s", drop_table.relation_name.c_str()); // Changed sql_debug to LOG_DEBUG as a guess
  return RC::SUCCESS;
} 