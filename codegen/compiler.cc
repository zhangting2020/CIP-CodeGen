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

#include "compiler.h"
#include "schedule_wrapper.h"

namespace cip {

Executable Compiler::Compile(MloModule* mlo_module) {
    llvm::Context llvm_context;
    llvm::Module llvm_module("",llvm_context);

    Schedules schedules;

    CompileModuleToLlvmIr(mlo_module, &llvm_module, &schedules);

    CompileLlvmIrToBinary(llvm_module);
}

Status Compiler::CompileModuleToLlvmIr(MloModule* mlo_module, llvm::Module* llvm_module, Schedules* schedule) {

    IrEmitter ir_emitter(llvm_module, schedule);
    std::vector<MloInstruction*> mlo_instructions = mlo_module.GetOrderdMloInstructions();

    for(auto mlo_instr : mlo_instructions) {
        mlo_instr->Accept(&ir_emitter);
    }
}

}