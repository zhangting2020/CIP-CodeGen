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

#include "gpu_ir_emitter.h"

namespace cip {

namespace gpu {

Status GpuIrEmitter::HandleElementwiseUnary(const MloInstruction* mlo) {

}

Status GpuIrEmitter::HandleElementwiseBinary(const MloInstruction* mlo) {
    //get body generator
    GpuPrimitiveIrEmitter* primitive_ir_emitter;
    primitive_ir_emitter.HanddleAdd(MloInstruction);
    auto body_generators = primitive_ir_emitter.GetBodyGenerators();

    //create llvm ir function
    auto context = llvm_module_->getContext();
    static FunctionType* func_type = nullptr;
    if() { //datatype
        func_type = TypeBuilder<void,float*,float*,float*,uint32_t>::get(context);
    } else {
    }

    llvm_module_->getOrInsertFunction(mlo->mlo_op_code_, *func_type);
    auto func = llvm_module_->getFunction(mlo->mlo_op_code_);
    //setting block
    auto block_num = 1;
    auto block_size = 1;
    int loop_factor = 1;

    auto entry_block = BasicBlock::Create(context, "entry", func);
    IRBuilder<> entry_irbuilder(entry_block);

    auto add_block = BasicBlock::Create(context, "add", func);
    IRBuilder<> add_irbuilder(add_block);

    auto exit_block = BasicBlock::Create(context, "exit", func);
    IRBuilder<> exit_irbuilder(exit_block);
    exit_irbuilder.CreateRetVoid();

    auto args_it = func->arg_begin();
    Value* arg_a = args_it ++;
    Value* arg_b = args_it ++;
    value* arg_c = args_it ++;
    Value* arg_n = args_it ++;

    auto block_dimx = entry_irbuilder.getInt32(block_size);
    auto tidx = elemental_ir_emitter.ThreadIdx(&entry_irbuilder);
    auto bidx = elemental_ir_emitter.BlockIdx(&entry_irbuilder);

    auto _1 = entry_irbuilder.CreateMul(bidx, block_dimx);
    auto _2 = entry_irbuilder.CreateAdd(_1, tidx);

    auto _3 = entry_irbuilder.CreateICmpULT(_2, arg_n);
    entry_irbuilder.CreateCondBr(_3, add_irbuilder, exit_irbuilder);

    auto _4 = add_irbuilder.CreateGEP(arg_a, _2);
    auto _5 = add_irbuilder.CreateGEP(arg_b, _2);
    auto _6 = add_irbuilder.CreateGEP(arg_c, _2);

    auto vals = body_generators[0].run(IrArray{_4, _5}, add_irbuilder);
    auto res = body_generators[1].run(vals, add_irbuilder);
    body_generators[2].run(res, add_irbuilder);
    add_irbuilder.CreateBr(exit_irbuilder);

    //Add schedule wrapper

    //
    return Status();
}

Status GpuIrEmitter::HandleBroadcast(const MloInstruction* mlo) {
    return Status();
}

Status GpuIrEmitter::HandleReduce(const MloInstruction* mlo) {
    return Status();
}

Status GpuIrEmitter::HandleReshape(const MloInstruction* mlo) {
    return Status();
}

Status GpuIrEmitter::HandleRng(const MloInstruction* mlo) {
    return Status();
}

Status GpuIrEmitter::HandleSelect(const MloInstruction* mlo) {
    return Status();
}

Status GpuIrEmitter::HandleTranspose(const MloInstruction* mlo) {
    return Status();
}

Status GpuIrEmitter::HandleConcat(const MloInstruction* mlo) {
    return Status();
}

Status GpuIrEmitter::HandleSlice(const MloInstruction* mlo) {
    return Status();
}

}
}