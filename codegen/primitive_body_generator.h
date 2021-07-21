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

#include <vector>
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


using IrArray = std::vector<llvm::Value*>;
using Generator = std::function<IrArray(IrArray, llvm::IRBuilder<>* llvm_builder)>;

class ElementalBodyGenerator {
public:
    ElementalBodyGenerator(std::string name, std::string type, Generator generator)
      :generator_name_(name), generator_type_(type), generator_(generator){}

    ~ElementalBodyGenerator(){}

    std::string GetName() {
        return generator_name_;
    }
    std::string GetType() {
        generator_type_
    }
    Generator& GetGenerator() {
        return  generator_;
    }
    IrArray Run(const IrArray& ir_array, llvm::IRBuilder *ir_builder) {
        return generator_(ir_array, ir_builder);
    }
private:
    std::string generator_name_;
    std::string generator_type_;
    Generator generator_;
};
