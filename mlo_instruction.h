// Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include "status.h"
#include <string>

/*
// 根据resnet50和bert模型所使用的算子进行低层IR指令选择enum class MetaOpCode {  
    // 复杂算子  Convolution,  Pooling,  PoolingGrad,  Dot,  BatchNormalzationInference,  BatchNormalzationTraining,  BatchNormGrad,  
    // 一元算子  Copy,  Cast,  Log,  Exp,  Rsqrt,  Negative,  Sqrt,  
    // 二元算子  Add,  Subtract,  Multiply,  Divide,  Minimum,  Maximum,  Compare,  
    // 其他元算子  Broadcast,  Reshape,  Rng,  Slice,  Concat,  Transpose,  Reduce,  Select,};
*/

namespace cip {

enum MloOpCode {
    kConvolution = 0,
    kPooling,
    kPoolingGrad,
    kDot,
    kBatchNormalzationInference,
    kBatchNormalzationTraining,
    kBatchNormGrad,
    kCopy,
    kCast,
    kLog,
    kExp,
    kRsqrt,
    kNegative,
    kSqrt,
    kAdd,
    kSubtract,
    kMultiply,
    kDivide,
    kCompare,
    kMinimum,
    kMaximum,
    kBroadcast,
    kReshape,
    kRng,
    kSlice,
    kConcat,
    kReduce,
    kTranspose,
    kSelect
};

class MloVisitorBase;
class Shape;

class MloInstruction {
public:
    Status Accept(MloVisitorBase* visitor);
private:
    friend class MloVisitorBase;

    Shape shape_;
    MloOpCode mlo_op_code_;
    std::string mlo_op_name_;
};

}