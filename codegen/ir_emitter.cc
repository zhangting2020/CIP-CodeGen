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

}


Status IrEmitter::HandleConvolution(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandlePooling(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandlePoolingGrad(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleDot(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleBatchNormalzationTraining(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleBatchNormGrad(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleBatchNormalzationInference(const MloInstruction* mlo) {
    //Unimplemented();
}

Status IrEmitter::HandleCast(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}

Status IrEmitter::HandleCopy(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}

Status IrEmitter::HandleExp(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}

Status IrEmitter::HandleLog(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}

Status IrEmitter::HandleSqrt(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}

Status IrEmitter::HandleRsqrt(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}

Status IrEmitter::HandleNegative(const MloInstruction* mlo) {
    return HandleElementwiseUnary(mlo);
}

Status IrEmitter::HandleAdd(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}

Status IrEmitter::HandleSubtract(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}

Status IrEmitter::HandleMultiply(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}

Status IrEmitter::HandleDivide(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}

Status IrEmitter::HandleMaximum(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}

Status IrEmitter::HandleMiniMum(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}

Status IrEmitter::HandleCompare(const MloInstruction* mlo) {
    return HandleElementwiseBinary(mlo);
}

Status IrEmitter::HandleBroadcast(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleReduce(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleReshape(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleRng(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleSelect(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleTranspose(const MloInstruction* mlo) {
    //Unimplemented();
}

Status IrEmitter::HandleConcat(const MloInstruction* mlo) {
    //Unimplemented();
}
Status IrEmitter::HandleSlice(const MloInstruction* mlo) {
    //Unimplemented();
}

}
