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

#include "ir_emitter.h"
#include "elemental_ir_emitter.h"

namespace cip {

Status IrEmitter::Visit(const MloInstruction* mlo) {
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


Status IrEmitter::HandleElementwiseUnary(const MloInstruction* mlo) {
    //create add kernel
    //get body generator
    ElementalIrEmitter elemental_ir_emitter;
    elemental_ir_emitter.HanddleAdd(MloInstruction);
    auto body_generators = elemental_ir_emitter.GetBodyGenerators();

    //create llvm ir function
    auto context = llvm_module_->getContext();
    static FunctionType* func_type = nullptr;
    if() { //datatype
        func_type = TypeBuilder<void,float*,float*,float*,void>::get(context);
    } else {
    }

    llvm_module_->getOrInsertFunction(mlo->mlo_op_code_, *func_type);
    auto func = llvm_module_->getFunction(mlo->mlo_op_code_);
    //setting block
    auto block_num = 1;
    auto block_size = 1;
    auto block_datasize = 1;
    int loop_factor = 1;

    auto entry_block = BasicBlock::Create(context, "entry", func);
    IRBuilder<> entry_irbuilder(entry_block);

    auto exit_block = BasicBlock::Create(context, "exit", func);
    IRBuilder<> exit_irbuilder(exit_block);

    auto args_it = func->arg_begin();
    Value* arg_a = args_it ++;
    Value* arg_b = args_it ++;
    Value* arg_n = args_it ++;

    auto block_dimx = entry_irbuilder.getInt32(block_size);
    auto block_stride = entry_irbuilder.getInt32(block_datasize);
    auto tidx = elemental_ir_emitter.ThreadIdx(&entry_irbuilder);
    auto bidx = elemental_ir_emitter.BlockIdx(&entry_irbuilder);

    auto _1 = entry_irbuilder.CreateMul(bidx, block_stride);
    auto _2 = entry_irbuilder.CreateMul(_1, tidx);

    auto idx = entry_irbuilder.CreateAlloca(Type::getInt32Ty(context), 0);
    entry_irbuilder.CreateStore(_2, idx);
    for(int idx = 0; idx < loop_factor ; ++idx) {
        auto _3 = entry_irbuilder.CreateLoad(idx);
        if(idx == loop_factor - 1) {
            auto _4 = entry_irbuilder.CreateICmpULT(_3, arg_n);
            entry_irbuilder.CreateCondBr()
        } else {
            auto _5 = entry_irbuilder.CreateGEP(arg_a, _3);
        }
    }

    return Status();
}

Status IrEmitter::HandleElementwiseBinary(const MloInstruction* mlo) {

}

Status IrEmitter::HandleAdd(const MloInstruction* mlo) {
   
}

Status IrEmitter::HandleAdd(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}

}

}