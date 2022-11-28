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
#ifndef ONEFLOW_CORE_PLATFORM_INCLUDE_PTHREAD_FORK_H_
#define ONEFLOW_CORE_PLATFORM_INCLUDE_PTHREAD_FORK_H_

namespace oneflow {

namespace pthread_fork {

bool IsForkedSubProcess();

extern const char* kOfCudaNotSupportInForkedSubProcess;
extern const char* kOfNpuNotSupportInForkedSubProcess;
}  // namespace pthread_fork

}  // namespace oneflow

#endif  // ONEFLOW_CORE_PLATFORM_INCLUDE_PTHREAD_FORK_H_
