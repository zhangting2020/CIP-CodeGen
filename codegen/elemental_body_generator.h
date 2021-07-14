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

#include <string>
#include <functional>

#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/TypeBuilder.h"
#include "llvm/Support/TargetSelect.h"

namespace cip {


using std::function<llvm::Value*(const std::unordered_map<std::string,llvmm::Value>& dependency, llvm::IRBuilder<>* llvm_builder)> Generator;
class ElementalBodyGenerator {
public:
    ElementalBodyGenerator(){}
    ~ElementalBodyGenerator(){}

    void init(std::string name, std::string type, Generator gen);
    std::string GetName();
    std::string GetType();
    llvm::Value* Run(const std::unordered_map<std::string,llvmm::Value>& dependency, llvm::IRBuilder<>* llvm_builder);
private:
    std::string name;
    std::string type;
    Generator generator;
};

}