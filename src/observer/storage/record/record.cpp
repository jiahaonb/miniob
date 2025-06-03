/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "storage/record/record.h"
#include "common/value.h"
#include <algorithm>

RC Record::set_field(int field_offset, int field_len, const Value &value)
{
  if (field_offset + field_len > len_) {
    LOG_ERROR("invalid offset or length. offset=%d, length=%d, total length=%d", field_offset, field_len, len_);
    return RC::INVALID_ARGUMENT;
  }
  
  // 计算实际数据长度（不超过字段长度）
  int actual_len = std::min(field_len, value.length());
  
  // 复制数据
  memcpy(data_ + field_offset, value.data(), actual_len);
  
  // 如果是字符串类型且长度小于字段长度，添加结束符
  if (actual_len < field_len) {
    data_[field_offset + actual_len] = '\0';
  }
  
  return RC::SUCCESS;
} 