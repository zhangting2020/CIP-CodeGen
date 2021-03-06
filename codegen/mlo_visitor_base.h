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
#include "mlo_instruction.h"

namespace cip {

//A Mlo Instruction Visitor
/*
// 根据resnet50和bert模型所使用的算子进行低层IR指令选择enum class MetaOpCode {  
    // 复杂算子  Convolution,  Pooling,  PoolingGrad,  Dot,  BatchNormalzationInference,  BatchNormalzationTraining,  BatchNormGrad,  
    // 一元算子  Copy,  Cast,  Log,  Exp,  Rsqrt,  Negative,  Sqrt,  
    // 二元算子  Add,  Subtract,  Multiply,  Divide,  Minimum,  Maximum,  Compare,  
    // 其他元算子  Broadcast,  Reshape,  Rng,  Slice,  Concat,  Transpose,  Reduce,  Select,};
*/

template<class InstructionPtr>
class MloVisitorBase {
public:
    MloVisitorBase(){}
    ~MloVisitorBase(){}

    virtual Status Visit(InstructionPtr *mlo) = 0;
    //virtual Status HandleElementwiseUnary(InstructionPtr* mlo) = 0;
    //virtual Status HandleElementwiseBinary(InstructionPtr* mlo) = 0;

    //AI api
    virtual Status HandleConvolution(InstructionPtr* mlo) = 0;
    virtual Status HandlePooling(InstructionPtr* mlo) = 0;
    virtual Status HandlePoolingGrad(InstructionPtr* mlo) = 0;
    virtual Status HandleDot(InstructionPtr* mlo) = 0;
    virtual Status HandleBatchNormalzationTraining(InstructionPtr* mlo) = 0;
    virtual Status HandleBatchNormGrad(InstructionPtr* mlo) = 0;
    virtual Status HandleBatchNormalzationInference(InstructionPtr* mlo) = 0;

    //Unary
    virtual Status HandleCast(InstructionPtr* mlo) = 0;
    virtual Status HandleCopy(InstructionPtr* mlo) = 0;
    virtual Status HandleExp(InstructionPtr* mlo) = 0;
    virtual Status HandleLog(InstructionPtr* mlo) = 0;
    virtual Status HandleSqrt(InstructionPtr* mlo) = 0;
    virtual Status HandleRsqrt(InstructionPtr* mlo) = 0;
    virtual Status HandleNegative(InstructionPtr* mlo) = 0;

    //Binary
    virtual Status HandleAdd(InstructionPtr* mlo) = 0;
    virtual Status HandleSubtract(InstructionPtr* mlo) = 0;
    virtual Status HandleMultiply(InstructionPtr* mlo) = 0;
    virtual Status HandleDivide(InstructionPtr* mlo) = 0;
    virtual Status HandleMaximum(InstructionPtr* mlo) = 0;
    virtual Status HandleMiniMum(InstructionPtr* mlo) = 0;
    virtual Status HandleCompare(InstructionPtr* mlo) = 0;

    //other
    virtual Status HandleBroadcast(InstructionPtr* mlo) = 0;
    virtual Status HandleReduce(InstructionPtr* mlo) = 0;
    virtual Status HandleReshape(InstructionPtr* mlo) = 0;
    virtual Status HandleRng(InstructionPtr* mlo) = 0;
    virtual Status HandleSelect(InstructionPtr* mlo) = 0;
    virtual Status HandleTranspose(InstructionPtr* mlo) = 0;

    virtual Status HandleConcat(InstructionPtr* mlo) = 0;
    virtual Status HandleSlice(InstructionPtr* mlo) = 0;
};

}