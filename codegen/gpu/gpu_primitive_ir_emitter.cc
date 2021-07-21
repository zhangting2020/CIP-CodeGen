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

#include "gpu_primitive_ir_emitter.h"

namespace cip {

namespace gpu {

std::function<llvm::value*(llvm::value*,llvm::value*,llvm::IRBuilder<>*)> 
    GpuPrimitiveIrEmitter::GetBinaryOp(const MloInstruction* mlo) {
    return [mlo](llvm::value* left,llvm::value* right,llvm::IRBuilder<>* llvm_builder) {
         switch(mlo->OpCode()) {
             case MloOpCode::kAdd:
                llvm_builder->CreateFadd(llvm_values[0], llvm_values[1]);
         }
    }
}

std::function<llvm::value*(llvm::value*,llvm::IRBuilder<>*)> 
    GpuPrimitiveIrEmitter::GetUnaryOp(const MloInstruction* mlo) {
    return [mlo](llvm::value* left,llvm::value* right,llvm::IRBuilder<>* llvm_builder) {
         switch(mlo->OpCode()) {
             case MloOpCode::kLog:
                llvm_builder->CreateFadd(llvm_values[0], llvm_values[1]);
         }
    }
}

Status GpuPrimitiveIrEmitter::HandleElementwiseBinary(const MloInstruction* mlo) {
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

Status GpuPrimitiveIrEmitter::HandleElementwiseUnary(const MloInstruction* mlo) {
     //read
    body_generators_.empalce_back("Read_" + mlo->mlo_op_name_, "READ", [this](IrArray llvm_values, llvm::IRBuilder<>* llvm_builder){
        return IrArray{llvm_builder->CreateLoad(llvm_values[0])};
    });

    //compute
    body_generators_.empalce_back("Read_" + mlo->mlo_op_name_, "COMPUTE", [this, mlo](IrArray llvm_values, llvm::IRBuilder<>* llvm_builder){
        return IrArray{GetUnaryOp(mlo)(llvm_values[0], llvm_builder)};
    });

    //store
    body_generators_.empalce_back("Store_" + mlo->mlo_op_name_, "STORE", [this](IrArray llvm_values, llvm::IRBuilder<>* llvm_builder){
        return IrArray{llvm_builder->CreateStore(llvm_values[0], llvm_values[1])};
    });

    return Status();
}

//others
Status GpuPrimitiveIrEmitter::HandleBroadcast(const MloInstruction* mlo) {
    return Status();
}
Status GpuPrimitiveIrEmitter::HandleReduce(const MloInstruction* mlo) {
    return Status();
}
Status GpuPrimitiveIrEmitter::HandleReshape(const MloInstruction* mlo) {
    return Status();
}
Status GpuPrimitiveIrEmitter::HandleRng(const MloInstruction* mlo) {
    return Status();
}
Status GpuPrimitiveIrEmitter::HandleSelect(const MloInstruction* mlo) {
    return Status();
}
Status GpuPrimitiveIrEmitter::HandleTranspose(const MloInstruction* mlo) {
    return Status();
}
Status GpuPrimitiveIrEmitter::HandleConcat(const MloInstruction* mlo) {
    return Status();
}
Status GpuPrimitiveIrEmitter::HandleSlice(const MloInstruction* mlo) {
    return Status();
}

}

}