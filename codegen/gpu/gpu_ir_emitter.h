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
#include "codegen/ir_emitter.h"

namespace cip{

namespace gpu{

class GpuIrEmitter : public IrEmitter {
public:
    Status HandleElementwiseUnary(const MloInstruction* mlo) override;
    Status HandleElementwiseBinary(const MloInstruction* mlo) override;

    //api
    /*
    virtual Status HandleConvolution(const MloInstruction* mlo);
    virtual Status HandlePooling(const MloInstruction* mlo);
    virtual Status HandlePoolingGrad(const MloInstruction* mlo);
    virtual Status HandleDot(const MloInstruction* mlo);
    virtual Status HandleBatchNormalzationTraining(const MloInstruction* mlo);
    virtual Status HandleBatchNormGrad(const MloInstruction* mlo);
    virtual Status HandleBatchNormalzationInference(const MloInstruction* mlo);
    */

    //other
    Status HandleBroadcast(const MloInstruction* mlo);
    Status HandleReduce(const MloInstruction* mlo);
    Status HandleReshape(const MloInstruction* mlo);
    Status HandleRng(const MloInstruction* mlo);
    Status HandleSelect(const MloInstruction* mlo);
    Status HandleTranspose(const MloInstruction* mlo);

    Status HandleConcat(const MloInstruction* mlo);
    Status HandleSlice(const MloInstruction* mlo);
};

}

}