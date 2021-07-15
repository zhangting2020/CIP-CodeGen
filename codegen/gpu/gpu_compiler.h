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

#include "codegen/compiler.h"

namespace cip {
namespace gpu {

class GpuExecutable : public Executable {
public:
    ~GpuExecutable() override {}
};


class GpuCompiler : public Compiler
{
public:
    GpuCompiler() override {
        ir_emitter = new cip::gpu::GpuIrEmitter();
    }
    ~GpuCompiler() override {}

    Executable* run(MloModule* mlo_module) override;
    void CompileModuleToLlvmIr() override;
};
}
}