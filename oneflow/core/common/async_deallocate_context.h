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
#ifndef ONEFLOW_CORE_COMMON_ASYNC_DEALLOCATE_CONTEXT_H_
#define ONEFLOW_CORE_COMMON_ASYNC_DEALLOCATE_CONTEXT_H_

#include "oneflow/core/common/deallocate_context.h"

namespace oneflow {

class ThreadPool;

class AsyncDeallocateContext final : public DeallocateContext {
 public:
  AsyncDeallocateContext();
  ~AsyncDeallocateContext() override;

  void Dispatch(std::function<void()> Handle) override;

 private:
  std::shared_ptr<ThreadPool> thread_pool_;
};

}  // namespace oneflow

#endif  // ONEFLOW_CORE_COMMON_ASYNC_DEALLOCATE_CONTEXT_H_