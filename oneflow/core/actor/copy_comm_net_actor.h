#ifndef ONEFLOW_CORE_ACTOR_COPY_COMM_NET_ACTOR_H_
#define ONEFLOW_CORE_ACTOR_COPY_COMM_NET_ACTOR_H_

#include "oneflow/core/actor/actor.h"

namespace oneflow {

class CopyCommNetActor final : public Actor {
 public:
  OF_DISALLOW_COPY_AND_MOVE(CopyCommNetActor);
  CopyCommNetActor() = default;
  ~CopyCommNetActor() = default;

  void Init(const TaskProto&, const ThreadCtx&) override;

 private:
  struct RegstCtx {
    const void* comm_net_token;
    Regst* regst_raw_ptr;
    int64_t producer;
  };

  int HandlerNormal(const ActorMsg&) override;
  int HandlerWaitUntilNoReadableRegst(const ActorMsg&) override;

  bool IsReadReady() override {
    return piece_id2regst_ctx.find(expected_piece_id())
           != piece_id2regst_ctx.end();
  }
  void Act() override;

  HashMap<int64_t, RegstCtx> piece_id2regst_ctx;
  void* stream_id_;
};

}  // namespace oneflow

#endif  // ONEFLOW_CORE_ACTOR_COPY_COMM_NET_ACTOR_H_
