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

namespace clp{

//A Mlo Instruction Visitor

class MloVisitorBase{
public:
    MloVisitorBase(){}
    ~MloVisitorBase(){}

    virtual Status HandleElementwiseUnary(MloInstruction* mlo) = 0;
    virtual Status HandleElementwiseBinary(MloInstruction* mlo) = 0;

    //Unary
    virtual Status HandleCast(MloInstruction* mlo) = 0;
    virtual Status HandleCopy(MloInstruction* mlo) = 0;
    virtual Status HandleExp(MloInstruction* mlo) = 0;
    virtual Status HandleLog(MloInstruction* mlo) = 0;
    virtual Status HandleSqrt(MloInstruction* mlo) = 0;
    virtual Status HandleRsqrt(MloInstruction* mlo) = 0;
    virtual Status HandleNegative(MloInstruction* mlo) = 0;

    //Binary
    virtual Status HandleAdd(MloInstruction* mlo) = 0;
    virtual Status HandleSubtract(MloInstruction* mlo) = 0;
    virtual Status HandleMultiply(MloInstruction* mlo) = 0;
    virtual Status HandleDivide(MloInstruction* mlo) = 0;
    virtual Status HandleMaximum(MloInstruction* mlo) = 0;
    virtual Status HandleMiniMum(MloInstruction* mlo) = 0;
    virtual Status HandleCompare(MloInstruction* mlo) = 0;

    //other
    virtual Status HandleBroadcast(MloInstruction* mlo) = 0;
    virtual Status HandleReduce(MloInstruction* mlo) = 0;
    virtual Status HandleReshape(MloInstruction* mlo) = 0;
    virtual Status HandleRng(MloInstruction* mlo) = 0;
    virtual Status HandleSelect(MloInstruction* mlo) = 0;
    virtual Status HandleTranspose(MloInstruction* mlo) = 0;

    virtual Status HandleConcat(MloInstruction* mlo) = 0;
};

}