/*
Copyright 2020 The OneFlow Authors. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef ONEFLOW_CORE_JOB_ID_STATE_H_
#define ONEFLOW_CORE_JOB_ID_STATE_H_

#include "oneflow/core/common/util.h"
#include "oneflow/core/device/device_id.h"
#include "oneflow/core/graph/stream_id.h"
#include "oneflow/core/graph/task_id.h"

namespace oneflow {

class IdState {
 public:
  int64_t regst_desc_id_state_{};
  int64_t mem_block_id_state_{};
  int64_t chunk_id_state_{};
  HashMap<StreamId, TaskId::task_index_t> task_index_state_{};
  HashMap<DeviceId, StreamId::stream_index_t> stream_index_state_{};
};

class IdStateMgr final {
 public:
  OF_DISALLOW_COPY_AND_MOVE(IdStateMgr);
  ~IdStateMgr() = default;

  IdState SaveIdState();
  void LoadIdState(const IdState& id_state);

  void SetRegstDescIdState(int64_t id) { id_state_.regst_desc_id_state_ = id; }
  int64_t GetRegstDescIdState() { return id_state_.regst_desc_id_state_; }

  void SetMemBlockIdState(int64_t id) { id_state_.mem_block_id_state_ = id; }
  int64_t GetMemBlockIdState() { return id_state_.mem_block_id_state_; }

  void SetChunkIdState(int64_t id) { id_state_.chunk_id_state_ = id; }
  int64_t GetChunkIdState() { return id_state_.chunk_id_state_; }

  void SetTaskIndexState(const StreamId& stream_id, int64_t idx) {
    id_state_.task_index_state_[stream_id] = idx;
  }
  int64_t GetTaskIndexState(const StreamId& stream_id) {
    if (id_state_.task_index_state_.count(stream_id) == 0) { return 0; }
    return id_state_.task_index_state_[stream_id];
  }

  void SetStreamIndexState(const DeviceId& device_id, int64_t stream_index) {
    id_state_.stream_index_state_[device_id] = stream_index;
  }
  int64_t GetStreamIndexState(const DeviceId& device_id) {
    if (id_state_.stream_index_state_.count(device_id) == 0) { return 0; }
    return id_state_.stream_index_state_[device_id];
  }

 private:
  friend class Singleton<IdStateMgr>;
  IdStateMgr() = default;

  IdState id_state_{};
};

}  // namespace oneflow

#endif