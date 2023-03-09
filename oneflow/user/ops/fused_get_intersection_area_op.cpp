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
#include "oneflow/core/framework/framework.h"
#include "oneflow/core/framework/op_generated.h"

namespace oneflow {

Maybe<void> FusedGetIntersectionAreaOp::InferLogicalTensorDesc(user_op::InferContext* ctx) {
  const user_op::TensorDesc& b1_x1 = ctx->InputTensorDesc("b1_x1", 0);
  const user_op::TensorDesc& b1_x2 = ctx->InputTensorDesc("b1_x2", 0);
  const user_op::TensorDesc& b1_y1 = ctx->InputTensorDesc("b1_y1", 0);
  const user_op::TensorDesc& b1_y2 = ctx->InputTensorDesc("b1_y2", 0);
  const user_op::TensorDesc& b2_x1 = ctx->InputTensorDesc("b2_x1", 0);
  const user_op::TensorDesc& b2_x2 = ctx->InputTensorDesc("b2_x2", 0);
  const user_op::TensorDesc& b2_y1 = ctx->InputTensorDesc("b2_y1", 0);
  const user_op::TensorDesc& b2_y2 = ctx->InputTensorDesc("b2_y2", 0);

  CHECK_EQ_OR_RETURN(b1_x1.shape(), b1_x2.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b1_y1.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b1_y2.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b2_x1.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b2_x2.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b2_y1.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b2_y2.shape());

  user_op::TensorDesc* inter = ctx->MutOutputTensorDesc("inter", 0);
  inter->set_is_dynamic(b1_x1.is_dynamic());
  inter->set_shape(b1_x1.shape());

  return Maybe<void>::Ok();
}

Maybe<void> FusedGetIntersectionAreaOp::InferPhysicalTensorDesc(user_op::InferContext* ctx) {
  return FusedGetIntersectionAreaOp::InferLogicalTensorDesc(ctx);
}

Maybe<void> FusedGetIntersectionAreaOp::InferDataType(user_op::InferContext* ctx) {
  const user_op::TensorDesc& b1_x1 = ctx->InputTensorDesc("b1_x1", 0);
  const user_op::TensorDesc& b1_x2 = ctx->InputTensorDesc("b1_x2", 0);
  const user_op::TensorDesc& b1_y1 = ctx->InputTensorDesc("b1_y1", 0);
  const user_op::TensorDesc& b1_y2 = ctx->InputTensorDesc("b1_y2", 0);
  const user_op::TensorDesc& b2_x1 = ctx->InputTensorDesc("b2_x1", 0);
  const user_op::TensorDesc& b2_x2 = ctx->InputTensorDesc("b2_x2", 0);
  const user_op::TensorDesc& b2_y1 = ctx->InputTensorDesc("b2_y1", 0);
  const user_op::TensorDesc& b2_y2 = ctx->InputTensorDesc("b2_y2", 0);

  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b1_x2.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b1_x2>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b1_x2.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b1_y1.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b1_y1>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b1_y1.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b1_y2.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b1_y2>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b1_y2.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b2_x1.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b2_x1>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b2_x1.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b2_x2.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b2_x2>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b2_x2.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b2_y1.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b2_y1>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b2_y1.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b2_y2.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b2_y2>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b2_y2.data_type());

  user_op::TensorDesc* inter = ctx->MutOutputTensorDesc("inter", 0);
  inter->set_data_type(b1_x1.data_type());
  return Maybe<void>::Ok();
}

Maybe<void> FusedGetIntersectionAreaOp::GetSbp(user_op::SbpContext* ctx) {
  const user_op::TensorDesc& b1_x1 = ctx->LogicalTensorDesc4InputArgNameAndIndex("b1_x1", 0);
  FOR_RANGE(int64_t, i, 0, b1_x1.shape().NumAxes()) {
    ctx->NewBuilder()
        .Split(user_op::OpArg("b1_x1", 0), i)
        .Split(user_op::OpArg("b1_x2", 0), i)
        .Split(user_op::OpArg("b1_y1", 0), i)
        .Split(user_op::OpArg("b1_y2", 0), i)
        .Split(user_op::OpArg("b2_x1", 0), i)
        .Split(user_op::OpArg("b2_x2", 0), i)
        .Split(user_op::OpArg("b2_y1", 0), i)
        .Split(user_op::OpArg("b2_y2", 0), i)
        .Split(user_op::OpArg("inter", 0), i)
        .Build();
  }
  return Maybe<void>::Ok();
}

Maybe<void> FusedGetIntersectionAreaGradOp::InferLogicalTensorDesc(user_op::InferContext* ctx) {
  const user_op::TensorDesc& b1_x1 = ctx->InputTensorDesc("b1_x1", 0);
  const user_op::TensorDesc& b1_x2 = ctx->InputTensorDesc("b1_x2", 0);
  const user_op::TensorDesc& b1_y1 = ctx->InputTensorDesc("b1_y1", 0);
  const user_op::TensorDesc& b1_y2 = ctx->InputTensorDesc("b1_y2", 0);
  const user_op::TensorDesc& b2_x1 = ctx->InputTensorDesc("b2_x1", 0);
  const user_op::TensorDesc& b2_x2 = ctx->InputTensorDesc("b2_x2", 0);
  const user_op::TensorDesc& b2_y1 = ctx->InputTensorDesc("b2_y1", 0);
  const user_op::TensorDesc& b2_y2 = ctx->InputTensorDesc("b2_y2", 0);
  const user_op::TensorDesc& inter_diff = ctx->InputTensorDesc("inter_diff", 0);

  CHECK_EQ_OR_RETURN(b1_x1.shape(), b1_x2.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b1_y1.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b1_y2.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b2_x1.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b2_x2.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b2_y1.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), b2_y2.shape());
  CHECK_EQ_OR_RETURN(b1_x1.shape(), inter_diff.shape());

  user_op::TensorDesc* b1_x1_diff = ctx->MutOutputTensorDesc("b1_x1_diff", 0);
  b1_x1_diff->set_is_dynamic(b1_x1.is_dynamic());
  b1_x1_diff->set_shape(b1_x1.shape());

  user_op::TensorDesc* b1_x2_diff = ctx->MutOutputTensorDesc("b1_x2_diff", 0);
  b1_x2_diff->set_is_dynamic(b1_x1.is_dynamic());
  b1_x2_diff->set_shape(b1_x1.shape());

  user_op::TensorDesc* b2_x1_diff = ctx->MutOutputTensorDesc("b2_x1_diff", 0);
  b2_x1_diff->set_is_dynamic(b1_x1.is_dynamic());
  b2_x1_diff->set_shape(b1_x1.shape());

  user_op::TensorDesc* b2_x2_diff = ctx->MutOutputTensorDesc("b2_x2_diff", 0);
  b2_x2_diff->set_is_dynamic(b1_x1.is_dynamic());
  b2_x2_diff->set_shape(b1_x1.shape());

  user_op::TensorDesc* b1_y1_diff = ctx->MutOutputTensorDesc("b1_y1_diff", 0);
  b1_y1_diff->set_is_dynamic(b1_x1.is_dynamic());
  b1_y1_diff->set_shape(b1_x1.shape());

  user_op::TensorDesc* b1_y2_diff = ctx->MutOutputTensorDesc("b1_y2_diff", 0);
  b1_y2_diff->set_is_dynamic(b1_x1.is_dynamic());
  b1_y2_diff->set_shape(b1_x1.shape());

  user_op::TensorDesc* b2_y1_diff = ctx->MutOutputTensorDesc("b2_y1_diff", 0);
  b2_y1_diff->set_is_dynamic(b1_x1.is_dynamic());
  b2_y1_diff->set_shape(b1_x1.shape());

  user_op::TensorDesc* b2_y2_diff = ctx->MutOutputTensorDesc("b2_y2_diff", 0);
  b2_y2_diff->set_is_dynamic(b1_x1.is_dynamic());
  b2_y2_diff->set_shape(b1_x1.shape());

  return Maybe<void>::Ok();
}

Maybe<void> FusedGetIntersectionAreaGradOp::InferPhysicalTensorDesc(user_op::InferContext* ctx) {
  return FusedGetIntersectionAreaGradOp::InferLogicalTensorDesc(ctx);
}

Maybe<void> FusedGetIntersectionAreaGradOp::InferDataType(user_op::InferContext* ctx) {
  const user_op::TensorDesc& b1_x1 = ctx->InputTensorDesc("b1_x1", 0);
  const user_op::TensorDesc& b1_x2 = ctx->InputTensorDesc("b1_x2", 0);
  const user_op::TensorDesc& b1_y1 = ctx->InputTensorDesc("b1_y1", 0);
  const user_op::TensorDesc& b1_y2 = ctx->InputTensorDesc("b1_y2", 0);
  const user_op::TensorDesc& b2_x1 = ctx->InputTensorDesc("b2_x1", 0);
  const user_op::TensorDesc& b2_x2 = ctx->InputTensorDesc("b2_x2", 0);
  const user_op::TensorDesc& b2_y1 = ctx->InputTensorDesc("b2_y1", 0);
  const user_op::TensorDesc& b2_y2 = ctx->InputTensorDesc("b2_y2", 0);
  const user_op::TensorDesc& inter_diff = ctx->InputTensorDesc("inter_diff", 0);

  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b1_x2.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b1_x2>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b1_x2.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b1_y1.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b1_y1>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b1_y1.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b1_y2.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b1_y2>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b1_y2.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b2_x1.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b2_x1>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b2_x1.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b2_x2.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b2_x2>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b2_x2.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b2_y1.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b2_y1>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b2_y1.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), b2_y2.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <b2_y2>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(b2_y2.data_type());
  CHECK_EQ_OR_RETURN(b1_x1.data_type(), inter_diff.data_type())
      << Error::RuntimeError()
      << "The data type of <b1_x1> is expected to be equal with that of <inter_diff>, but got "
      << DataType_Name(b1_x1.data_type()) << " and " << DataType_Name(inter_diff.data_type());

  user_op::TensorDesc* b1_x1_diff = ctx->MutOutputTensorDesc("b1_x1_diff", 0);
  b1_x1_diff->set_data_type(b1_x1.data_type());

  user_op::TensorDesc* b1_x2_diff = ctx->MutOutputTensorDesc("b1_x2_diff", 0);
  b1_x2_diff->set_data_type(b1_x1.data_type());

  user_op::TensorDesc* b2_x1_diff = ctx->MutOutputTensorDesc("b2_x1_diff", 0);
  b2_x1_diff->set_data_type(b1_x1.data_type());

  user_op::TensorDesc* b2_x2_diff = ctx->MutOutputTensorDesc("b2_x2_diff", 0);
  b2_x2_diff->set_data_type(b1_x1.data_type());

  user_op::TensorDesc* b1_y1_diff = ctx->MutOutputTensorDesc("b1_y1_diff", 0);
  b1_y1_diff->set_data_type(b1_x1.data_type());

  user_op::TensorDesc* b1_y2_diff = ctx->MutOutputTensorDesc("b1_y2_diff", 0);
  b1_y2_diff->set_data_type(b1_x1.data_type());

  user_op::TensorDesc* b2_y1_diff = ctx->MutOutputTensorDesc("b2_y1_diff", 0);
  b2_y1_diff->set_data_type(b1_x1.data_type());

  user_op::TensorDesc* b2_y2_diff = ctx->MutOutputTensorDesc("b2_y2_diff", 0);
  b2_y2_diff->set_data_type(b1_x1.data_type());

  return Maybe<void>::Ok();
}

Maybe<void> FusedGetIntersectionAreaGradOp::GetSbp(user_op::SbpContext* ctx) {
  const user_op::TensorDesc& b1_x1 = ctx->LogicalTensorDesc4InputArgNameAndIndex("b1_x1", 0);
  FOR_RANGE(int64_t, i, 0, b1_x1.shape().NumAxes()) {
    ctx->NewBuilder()
        .Split(user_op::OpArg("b1_x1", 0), i)
        .Split(user_op::OpArg("b1_x2", 0), i)
        .Split(user_op::OpArg("b1_y1", 0), i)
        .Split(user_op::OpArg("b1_y2", 0), i)
        .Split(user_op::OpArg("b2_x1", 0), i)
        .Split(user_op::OpArg("b2_x2", 0), i)
        .Split(user_op::OpArg("b2_y1", 0), i)
        .Split(user_op::OpArg("b2_y2", 0), i)
        .Split(user_op::OpArg("inter_diff", 0), i)
        .Split(user_op::OpArg("b1_x1_diff", 0), i)
        .Split(user_op::OpArg("b1_x2_diff", 0), i)
        .Split(user_op::OpArg("b1_y1_diff", 0), i)
        .Split(user_op::OpArg("b1_y2_diff", 0), i)
        .Split(user_op::OpArg("b2_x1_diff", 0), i)
        .Split(user_op::OpArg("b2_x2_diff", 0), i)
        .Split(user_op::OpArg("b2_y1_diff", 0), i)
        .Split(user_op::OpArg("b2_y2_diff", 0), i)
        .Build();
  }
  return Maybe<void>::Ok();
}

}  // namespace oneflow
