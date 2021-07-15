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

#include "codegen/gpu/gpu_compiler.h"

namespace cip {

namespace gpu {

Executable* GpuCompiler::run(MloModule* mlo_module) {
    mlo_module_ = mlo_module;
    CompileModuleToLlvmIr();
}

void GpuCompiler::CompileModuleToLlvmIr() {
    // step 1: init something for llvm ir

    ir_emitter->llvm_module = llvm_module;

    auto instructions = mlo_module_->instructions();
    for (auto &instruction : instructions) {
        ir_emitter->Handle(&instruction); // add it to llvm_module
    }
}

}
}