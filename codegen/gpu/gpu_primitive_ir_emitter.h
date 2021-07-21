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

#include "codegen/primitive_ir_emitter.h"

namespace cip {
namespace gpu {

class GpuPrimitiveIrEmitter : public PrimitiveIrEmitter{
public:
    virtual std::function<llvm::value*(llvm::value*, llvm::value*, llvm::IRBuilder<>*)> 
        GetBinaryOp(const MloInstruction* mlo);
    virtual std::function<llvm::value*(llvm::value*, llvm::IRBuilder<>*)> 
        GetUnaryyOp(const MloInstruction* mlo);

    Status HandleElementwiseUnary(MloInstruction* mlo) override;
    Status HandleElementwiseBinary(MloInstruction* mlo) override;

    //AI api
    virtual Status HandleConvolution(const MloInstruction* mlo);
    virtual Status HandlePooling(const MloInstruction* mlo);
    virtual Status HandlePoolingGrad(const MloInstruction* mlo);
    virtual Status HandleDot(const MloInstruction* mlo);
    virtual Status HandleBatchNormalzationTraining(const MloInstruction* mlo);
    virtual Status HandleBatchNormGrad(const MloInstruction* mlo);
    virtual Status HandleBatchNormalzationInference(const MloInstruction* mlo);

    //other
    Status HandleBroadcast(MloInstruction* mlo) override;
    Status HandleReduce(MloInstruction* mlo) override;
    Status HandleReshape(MloInstruction* mlo) override;
    Status HandleRng(MloInstruction* mlo) override;
    Status HandleSelect(MloInstruction* mlo) override;
    Status HandleTranspose(MloInstruction* mlo) override;

    Status HandleConcat(MloInstruction* mlo) override;
    Status HandleSlice(MloInstruction* mlo) override;

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
    virtual llvm::Value* Alloca(llvm::IRBuilder* ir_builder) = 0;

    /*
    llvm::Value* BlockRead(llvm::Value* base, llvm::Value* offset,Type *Ty);
    llvm::value* ThreadRead(llvm::Value* base, llvm::Value* offset,Type *Ty);

    void BlockWrite(llvm::Value*,llvm::Value* base, llvm::Value* offset,Type *Ty);
    void ThreadWrite(llvm::Value*,llvm::Value* base, llvm::Value* offset,Type *Ty);

    llvm::Value* Assign(llvm::Value*);
    virtual llvm::Value* Exp(llvm::Value*);
    virtual llvm::Value* Log(llvm::Value*);
    llvm::Value* Negative(llvm::Value*) ;
    virtual llvm::Value* Rsqrt(llvm::Value*) {};
    virtual llvm::Value* Sqrt(llvm::Value*) {};

    llvm::Value* Add(llvm::Value*, llvm::Value*);
    llvm::Value* Subtract(llvm::Value*, llvm::Value*);
    llvm::Value* Multiply(llvm::Value*, llvm::Value*);
    llvm::Value* Divide(llvm::Value*, llvm::Value*);
    llvm::Value* Maximum(llvm::Value*, llvm::Value*);
    llvm::Value* Minimum(llvm::Value*, llvm::Value*);

    virtual llvm::Value* TypeCast(llvm::Value*, Type *, llvm::Value*, Type *){};
    llvm::Value* Select(llvm::Value*, llvm::Value*, llvm::Value*);
    */
};

}
}