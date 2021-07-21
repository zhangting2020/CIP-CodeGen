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

#include "elemental_ir_emitter.h"

namespace cip {

Status PrimitiveIrEmitter::Visit(const MloInstruction* mlo) {
#define SWITCH(mlo_op_code, mlo)    \
    case MloOpCode::k##mlo_op_code: \
        return Handle##mlo_op_code(mlo);

    switch(mlo->OpCode()) {
        SWITCH(Convolution, mlo);
        SWITCH(Pooling, mlo);
        SWITCH(PoolingGrad, mlo);
        SWITCH(Dot, mlo);
        SWITCH(BatchNormalzationInference, mlo);
        SWITCH(BatchNormalzationTraining, mlo);
        SWITCH(BatchNormGrad, mlo);
        SWITCH(Copy, mlo);
        SWITCH(Cast, mlo);
        SWITCH(Log, mlo);
        SWITCH(Exp, mlo);
        SWITCH(Rsqrt, mlo);
        SWITCH(Negative, mlo);
        SWITCH(Sqrt, mlo);
        SWITCH(Add, mlo);
        SWITCH(Subtract, mlo);
        SWITCH(Multiply, mlo);
        SWITCH(Divide, mlo);
        SWITCH(Minimum, mlo);
        SWITCH(Maximum, mlo);
        SWITCH(Compare, mlo);
        SWITCH(Broadcast, mlo);
        SWITCH(Reshape, mlo);
        SWITCH(Slice, mlo);
        SWITCH(Rng, mlo);
        SWITCH(Concat, mlo);
        SWITCH(Transpose, mlo);
        SWITCH(Reduce, mlo);
        SWITCH(Select, mlo);
        default:
            break;
    }
#undef SWITCH 
}

std::function<llvm::value*(llvm::value*,llvm::value*,llvm::IRBuilder<>*)> GetBinaryOp(const MloInstruction* mlo) {
    return [mlo](llvm::value* left,llvm::value* right,llvm::IRBuilder<>* llvm_builder) {
         switch(mlo->OpCode()) {
             case MloOpCode::Add:
                llvm_builder->CreateFadd(llvm_values[0], llvm_values[1]);
         }
    }
}

Status PrimitiveIrEmitter::HandleElementwiseBinary(const MloInstruction* mlo) {
     //read
    body_generators_.empalce_back("Read_" + mlo->mlo_op_name_, "READ", [this](IrArray llvm_values, llvm::IRBuilder<>* llvm_builder){
        return IrArray{llvm_builder->CreateLoad(llvm_values[0]), llvm_builder->CreateLoad(llvm_values[1])};
    });

    //compute
    body_generators_.empalce_back("Read_" + mlo->mlo_op_name_, "COMPUTE", [this, mlo](IrArray llvm_values, llvm::IRBuilder<>* llvm_builder){
        return IrArray{GetBinaryOp(mlo)(llvm_values[0], llvm_values[1], llvm_builder)};
    });

    //store
    body_generators_.empalce_back("Store_" + mlo->mlo_op_name_, "STORE", [this](IrArray llvm_values, llvm::IRBuilder<>* llvm_builder){
        return IrArray{llvm_builder->CreateStore(llvm_values[0], llvm_values[1])};
    });

    return Status();
}

Status PrimitiveIrEmitter::HandleCast(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}
Status PrimitiveIrEmitter::HandleCopy(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}
Status PrimitiveIrEmitter::HandleExp(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}
Status PrimitiveIrEmitter::HandleLog(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}
Status PrimitiveIrEmitter::HandleSqrt(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}
Status PrimitiveIrEmitter::HandleRsqrt(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}
Status PrimitiveIrEmitter::HandleNegative(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}

//Binary
Status PrimitiveIrEmitter::HandleAdd(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}
Status PrimitiveIrEmitter::HandleSubtract(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}
Status PrimitiveIrEmitter::HandleMultiply(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}
Status PrimitiveIrEmitter::HandleDivide(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}
Status PrimitiveIrEmitter::HandleMaximum(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}
Status PrimitiveIrEmitter::HandleMiniMum(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}
Status PrimitiveIrEmitter::HandleCompare(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}


}
