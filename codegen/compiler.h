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

#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/TypeBuilder.h"
#include "llvm/Support/TargetSelect.h"

#include "codegen/ir_emitter.h"

namespace cip {

class MloModule;
class MloInstruction;

// After compilation, an Executable will be returned.
class Executable {
public:
    virtual ~Executable() {}
};

class Compiler {
public:
    virtual ~Compiler() {}

    virtual Executable* run(MloModule* mlo_module);
    virtual void CompileModuleToLlvmIr();
    virtual void CompileLlvmIrToBinary();

    IrEmitter *ir_emitter;

private:
    llvm::LLVMContext* llvm_context;
    llvm::Module* llvm_module;
    llvm::IRBuilder<>* llvm_builder;
    MloModule *mlo_module_;
};

}