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
#include "oneflow/user/ops/comm_net_device_infer_util.h"
#include "oneflow/core/common/decorator.h"

namespace oneflow {

namespace {

Maybe<Symbol<Stream>> RawGetTransportDevice(Symbol<Device> device) {
  return Stream::New(JUST(Device::New(device->type())), StreamType::kCcl);
}

}  // namespace

decltype(GetTransportDevice) GetTransportDevice = DECORATE(&RawGetTransportDevice, ThreadLocal);

Maybe<Symbol<Device>> DefaultGetOutputDeivce(user_op::DeviceAndStreamInferContext* ctx) {
  CHECK_GT_OR_RETURN(ctx->inputs().size(), 0);
  return ctx->InputTensorDevice4ArgNameAndIndex("in", 0);
}

}  // namespace oneflow
