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
/*
// 根据resnet50和bert模型所使用的算子进行低层IR指令选择enum class MetaOpCode {  
    // 复杂算子  Convolution,  Pooling,  PoolingGrad,  Dot,  BatchNormalzationInference,  BatchNormalzationTraining,  BatchNormGrad,  
    // 一元算子  Copy,  Cast,  Log,  Exp,  Rsqrt,  Negative,  Sqrt,  
    // 二元算子  Add,  Subtract,  Multiply,  Divide,  Minimum,  Maximum,  Compare,  
    // 其他元算子  Broadcast,  Reshape,  Rng,  Slice,  Concat,  Transpose,  Reduce,  Select,};
*/

Status IrEmitter::Visit(const MloInstruction* mlo) {
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

    //

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