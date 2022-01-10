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

#ifndef ONEFLOW_CORE_AUTO_PARALLEL_BOXING_COLLECTOR_
#define ONEFLOW_CORE_AUTO_PARALLEL_BOXING_COLLECTOR_

#include "oneflow/core/auto_parallel/sbp_graph.h"
#include "oneflow/core/common/hash_container.h"
#include "oneflow/core/graph/op_graph.h"
#include "oneflow/core/job/parallel_desc.h"
#include "oneflow/core/job/sbp_parallel.cfg.h"
#include "sbp_graph.h"
#include "sbp_util.h"

namespace oneflow {

class BoxingCollector {
 public:
  BoxingCollector() = default;

  ~BoxingCollector() = default;

  // Collect all the possible Sbp Parallel from an OpGraph
  void CollectUniverse(const OpGraph& op_graph);
  // Collect all the possible Sbp Parallel from a cfg::NdSbpSignature
  void CollectUniverse(const cfg::NdSbpSignature& nd_sbp_sig);
  // Collect all the possible Sbp Parallel from a SbpNode
  void CollectUniverse(const auto_parallel::SbpNode<cfg::NdSbpSignature>* sbp_node);
  // Collect all the possible Sbp Parallel from a SbpGraph
  void CollectUniverse(const auto_parallel::SbpGraph<cfg::NdSbpSignature>& sbp_graph);
  // Set default Sbp list
  void CollectUniverse(int32_t max_axis);
  // Collect Sbp Parallel
  void CollectUniverse(const cfg::SbpParallel& sbp);

  // Construct a boxing collector with given sbp graph
  void Init(const auto_parallel::SbpGraph<cfg::NdSbpSignature>& sbp_graph);
  // Construct a boxing collector with given operator graph
  void Init(const OpGraph& op_graph);

  // Generate nd sbp list
  void GenerateNdSbpList();
  // Generate the transfer rule for different combinations and hierarchies
  Maybe<void> GenerateCombination(int32_t max_middle_node_num);
  // Print the cost and middle nodes
  void PrintBoxingTables();
  // Ask if the boxing algorithm accepts the current sbp combination
  // If customized is true and we can not find a middle node list with
  Maybe<void> AskSbpCombination(const cfg::NdSbp& sbp_producer, const cfg::NdSbp& sbp_consumer,
                                const BlobDesc& logical_blob_desc,
                                const ParallelDesc& producer_parallel_desc,
                                const ParallelDesc& consumer_parallel_desc, bool customized,
                                std::vector<cfg::NdSbp>& middle_sbps);
  // Filter nd sbp from nd_sbp_lists with given logical shape
  Maybe<void> FilterNdSbpList4LogicalShape(const BlobDesc& logical_blob_desc,
                                           const std::shared_ptr<Shape>& parallel_hierarchy);

 private:
  // Stores all the possible cfg::SbpParallel.
  HashMap<::oneflow::cfg::SbpParallel, int32_t> SbpParallelUniverse_;
  // Relationship between id and Sbp Parallel
  std::vector<::oneflow::cfg::SbpParallel> id2SbpParallel;
  // minimum cost
  // minimum_copy_cost[producer][consumer]
  std::vector<std::vector<double>> minimum_copy_cost;
  // middle nodes
  // middle_nodes[producer][consumer][different choices] is a vector of middle nodes
  // middle_nodes[producer][consumer][different choices].size() is the minimum number of middle
  // nodes that needs to be inserted
  std::vector<std::vector<std::vector<std::vector<int32_t>>>> middle_nodes;
  // Stores all the possible cfg::NdSbp.
  std::unordered_map<::oneflow::cfg::NdSbp, int32_t> NdSbpUniverse;
  // Relationship between id and Nd Sbp
  std::vector<cfg::NdSbp> nd_sbp_lists;
};  // class BoxingCollector

}  // namespace oneflow

#endif  // ONEFLOW_CORE_AUTO_PARALLEL_BOXING_COLLECTOR_