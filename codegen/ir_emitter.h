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
#include "mlo_visitor_base.h"
#include "llvm/IR/IRBuilder.h"
#include "shedule_wrapper.h"

namespace cip{

//Abstract base class for translating MLO instruction to LLVM IR

class IrEmitter : public MloVisitorBase<const MloInstruction*>{
public:
    IrEmitter(llvm::Module* module):llvm_module_(module){}
    ~IrEmitter(){}

    Status Visit(const MloInstruction* mlo);

    virtual Status HandleElementwiseUnary(const MloInstruction* mlo) = 0;
    virtual Status HandleElementwiseBinary(const MloInstruction* mlo) = 0;

    //Unary
    virtual Status HandleCast(const MloInstruction* mlo) = 0;
    virtual Status HandleCopy(const MloInstruction* mlo) = 0;
    virtual Status HandleExp(const MloInstruction* mlo) = 0;
    virtual Status HandleLog(const MloInstruction* mlo) = 0;
    virtual Status HandleSqrt(const MloInstruction* mlo) = 0;
    virtual Status HandleRsqrt(const MloInstruction* mlo) = 0;
    virtual Status HandleNegative(const MloInstruction* mlo) = 0;

    //Binary
    Status HandleAdd(const MloInstruction* mlo);
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
    virtual Status HandleSlice(MloInstruction* mlo) = 0;

protected:
    llvm::Module *llvm_module_{ nullptr };
    std::vector<ScheduleWrapper> schedule_wrappers_;
};

}