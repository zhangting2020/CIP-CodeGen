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

Status ElementalIrEmitter::Visit(const MloInstruction* mlo) {
     switch(mlo->OpCode()) {
        case MloOpCode::kAdd:
            return HanddleAdd(mlo);
        case MloOpCode::kSubtract:
            return HanddleSubtract(mlo);
        case MloOpCode::kMultiply:
            return HandleMultiply(mlo);
        case MloOpCode::kDivide:
            return HandleDivide(mlo);
        case MloOpCode::kMinimum:
            return HandleMiniMum(mlo);
        case MloOpCode::kMaximum:
            return HandleMaximum(mlo);
    }
}

Status ElementalIrEmitter::HandleAdd(MloInstruction* mlo) {
    //read
    body_generators_.empalce_back("Read_" + mlo->mlo_op_name_, "READ", [this](std::vector<llvm::Value*> llvm_values, llvm::IRBuilder<>* llvm_builder){
        IrArray ret = {llvm_builder->CreateLoad(llvm_values[0]),llvm_builder->CreateLoad(llvm_values[1])};
        return ret;
    });

    //compute
    body_generators_.empalce_back("Read_" + mlo->mlo_op_name_, "COMPUTE", [this, mlo](std::vector<llvm::Value*> llvm_values, llvm::IRBuilder<>* llvm_builder){
        if() {//check data type
            IrArray ret = {llvm_builder->CreateFadd(llvm_values[0], llvm_values[1])};
            return ret;
        } else if{
            IrArray ret = {llvm_builder->CreateAdd(llvm_values[0], llvm_values[1])};
            return ret;
        }
    });

    //store
    body_generators_.empalce_back("Store_" + mlo->mlo_op_name_, "STORE", [this](std::vector<llvm::Value*> llvm_values, llvm::IRBuilder<>* llvm_builder){
        IrArray ret = { llvm_builder->CreateStore(llvm_values[0], llvm_values[1] };
        return ret;
    });
}

}
