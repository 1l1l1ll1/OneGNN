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
#ifndef ONEFLOW_CORE_JOB_COMPILE_MODE_H_
#define ONEFLOW_CORE_JOB_COMPILE_MODE_H_

#include "oneflow/core/common/maybe.h"

namespace oneflow {

enum class CompileMode {
  kInvalid = 0,
  kNaive,
  kRankPerIter,
  kRankPerThread,
  kEnd,
};

template<typename DerivedT>
struct CompileModeVisitor {
  template<typename... Args>
  static auto Visit(CompileMode compile_mode, Args&&... args) {
    switch (compile_mode) {
      case CompileMode::kInvalid: LOG(FATAL) << "invalid compile mode";
      case CompileMode::kNaive: return DerivedT::VisitNaive(std::forward<Args>(args)...);
      case CompileMode::kRankPerIter:
        return DerivedT::VisitRankPerIter(std::forward<Args>(args)...);
      case CompileMode::kRankPerThread:
        return DerivedT::VisitRankPerThread(std::forward<Args>(args)...);
      case CompileMode::kEnd: LOG(FATAL) << "invalid compile mode";
    }
    LOG(FATAL) << "invalid compile mode";
  }
};

Maybe<CompileMode> CurrentCompileMode();

}  // namespace oneflow

#endif  // ONEFLOW_CORE_JOB_COMPILE_MODE_H_