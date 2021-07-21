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

#include <vector>
#include "codegen/mlo_visitor_base.h"
#include "elemental_body_generator.h"
#include "llvm/IR/IRBuilder.h"

namespace cip {

class PrimitiveIrEmitter : public MloVisitorBase {
public:
    ElementalIrEmitter(){}
    ~ElementalIrEmitter(){}

    Status Visit(const MloInstruction* mlo) override;

    virtual Status HandleElementwiseUnary(const MloInstruction* mlo) = 0;
    virtual Status HandleElementwiseBinary(const MloInstruction* mlo) = 0;

    //AI api
    Status HandleConvolution(const MloInstruction* mlo) override {};
    Status HandlePooling(const MloInstruction* mlo) override {};
    Status HandlePoolingGrad(const MloInstruction* mlo) override {};
    Status HandleDot(const MloInstruction* mlo) override {};
    Status HandleBatchNormalzationTraining(const MloInstruction* mlo) override {};
    Status HandleBatchNormGrad(const MloInstruction* mlo) override {};
    Status HandleBatchNormalzationInference(const MloInstruction* mlo) override {};

    //Unary
    Status HandleCast(const MloInstruction* mlo);
    Status HandleCopy(const MloInstruction* mlo);
    Status HandleExp(const MloInstruction* mlo);
    Status HandleLog(const MloInstruction* mlo);
    Status HandleSqrt(const MloInstruction* mlo);
    Status HandleRsqrt(const MloInstruction* mlo);
    Status HandleNegative(const MloInstruction* mlo);

    //Binary
    Status HandleAdd(const MloInstruction* mlo);
    Status HandleSubtract(const MloInstruction* mlo);
    Status HandleMultiply(const MloInstruction* mlo);
    Status HandleDivide(const MloInstruction* mlo);
    Status HandleMaximum(const MloInstruction* mlo);
    Status HandleMiniMum(const MloInstruction* mlo);
    Status HandleCompare(const MloInstruction* mlo);

    //other
    virtual Status HandleBroadcast(const MloInstruction* mlo) = 0;
    virtual Status HandleReduce(const MloInstruction* mlo) = 0;
    virtual Status HandleReshape(const MloInstruction* mlo) = 0;
    virtual Status HandleRng(const MloInstruction* mlo) = 0;
    virtual Status HandleSelect(const MloInstruction* mlo) = 0;
    virtual Status HandleTranspose(const MloInstruction* mlo) = 0;

    virtual Status HandleConcat(const MloInstruction* mlo) = 0;
    virtual Status HandleSlice(const MloInstruction* mlo) = 0;

    //operator
    //about the base code block,
    virtual llvm::Value* ThreadIdx(llvm::IRBuilder* ir_builder) = 0;
    virtual llvm::Value* ThreadIdy(llvm::IRBuilder* ir_builder) = 0;
    virtual llvm::Value* ThreadIdz(llvm::IRBuilder* ir_builder) = 0;
    virtual llvm::Value* BlockDimx(llvm::IRBuilder* ir_builder) = 0;
    virtual llvm::Value* BlockDimy(llvm::IRBuilder* ir_builder) = 0;
    virtual llvm::Value* BlockDimz(llvm::IRBuilder* ir_builder) = 0;
    virtual llvm::Value* BlockIdx(llvm::IRBuilder* ir_builder) = 0;
    virtual llvm::Value* BlockIdy(llvm::IRBuilder* ir_builder) = 0;
    virtual llvm::Value* BlockIdz(llvm::IRBuilder* ir_builder) = 0;
    virtual void ThreadSync(llvm::IRBuilder* ir_builder) = 0;

    //virtual llvm::Value* Alloca(llvm::IRBuilder* ir_builder) = 0;
    /*
    virtual llvm::Value* BlockRead(llvm::Value* base, llvm::Value* offset,Type *Ty) = 0;
    virtual llvm::value* ThreadRead(llvm::Value* base, llvm::Value* offset,Type *Ty) = 0;

    virtual void BlockWrite(llvm::Value*,llvm::Value* base, llvm::Value* offset,Type *Ty) = 0;
    virtual void ThreadWrite(llvm::Value*,llvm::Value* base, llvm::Value* offset,Type *Ty) = 0;

    virtual llvm::Value* Assign(llvm::Value*) = 0;
    virtual llvm::Value* Exp(llvm::Value*) = 0;
    virtual llvm::Value* Log(llvm::Value*) = 0;
    virtual llvm::Value* Negative(llvm::Value*) = 0;
    virtual llvm::Value* Rsqrt(llvm::Value*) = 0;
    virtual llvm::Value* Sqrt(llvm::Value*) = 0;

    virtual llvm::Value* Add(llvm::Value*, llvm::Value*) = 0;
    virtual llvm::Value* Subtract(llvm::Value*, llvm::Value*) = 0;
    virtual llvm::Value* Multiply(llvm::Value*, llvm::Value*) = 0;
    virtual llvm::Value* Divide(llvm::Value*, llvm::Value*) = 0;
    virtual llvm::Value* Maximum(llvm::Value*, llvm::Value*) = 0;
    virtual llvm::Value* Minimum(llvm::Value*, llvm::Value*) = 0;

    virtual llvm::Value* TypeCast(llvm::Value*, Type *, llvm::Value*, Type *) = 0;
    virtual llvm::Value* Select(llvm::Value*, llvm::Value*, llvm::Value*) = 0;
    */

    std::vector<ElementalBodyGenerator>& Handle(MloInstruction* mlo);
    std::vector<ElementalBodyGenerator>& GetBodyGenerators();
protected:
    std::vector<PrimitiveBodyGenerator> body_generators_;
};

}