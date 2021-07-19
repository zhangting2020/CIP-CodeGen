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

#include "codegen/elemental_ir_emitter.h"

namespace cip {
namespace gpu {

class GpuElementalIrEmitter : public ElementalIrEmitter{
public:
    Status HandleElementwiseUnary(MloInstruction* mlo) override;
    Status HandleElementwiseBinary(MloInstruction* mlo) override;

    //Unary
    Status HandleCast(MloInstruction* mlo) override;
    Status HandleCopy(MloInstruction* mlo) override;
    Status HandleExp(MloInstruction* mlo) override;
    Status HandleLog(MloInstruction* mlo) override;
    Status HandleSqrt(MloInstruction* mlo) override;
    Status HandleRsqrt(MloInstruction* mlo) override;
    Status HandleNegative(MloInstruction* mlo) override;

    //Binary
    Status HandleAdd(MloInstruction* mlo) override;
    Status HandleSubtract(MloInstruction* mlo) override;
    Status HandleMultiply(MloInstruction* mlo) override;
    Status HandleDivide(MloInstruction* mlo) override;
    Status HandleMaximum(MloInstruction* mlo) override;
    Status HandleMiniMum(MloInstruction* mlo) override;
    Status HandleCompare(MloInstruction* mlo) override;

    //other
    Status HandleBroadcast(MloInstruction* mlo) override;
    Status HandleReduce(MloInstruction* mlo) override;
    Status HandleReshape(MloInstruction* mlo) override;
    Status HandleRng(MloInstruction* mlo) override;
    Status HandleSelect(MloInstruction* mlo) override;
    Status HandleTranspose(MloInstruction* mlo) override;

    Status HandleConcat(MloInstruction* mlo) override;
    Status HandleSlice(MloInstruction* mlo) override;

    //operator
    //operator
    //about the base code block,
    virtual llvm::Value* ThreadIdx(){};
    virtual llvm::Value* ThreadIdy(){};
    virtual llvm::Value* ThreadIdz(){};
    virtual llvm::Value* BlockDimx(){};
    virtual llvm::Value* BlockDimy(){};
    virtual llvm::Value* BlockDimz(){};
    virtual llvm::Value* BlockIdx(){};
    virtual llvm::Value* BlockIdy(){};
    virtual llvm::Value* BlockIdz(){};
    virtual void ThreadSync(){};
    llvm::Value* Alloca(){};

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
};

}
}