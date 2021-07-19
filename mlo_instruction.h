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

#include "status.h"
#include <string>

namespace cip {

enum MloOpCode {
    kAdd = 0,
    kSubtract,
    kMultiply,
    kDivide,
    kCompare,
    kMinimum,
    kMaximum,
    kLog,
    kExp,
    kSqrt,
    kRsqrt,
    kSelect
};

class MloVisitorBase;
class Shape;

class MloInstruction {
public:
    Status Accept(MloVisitorBase* visitor);
private:
    friend class MloVisitorBase;

    Shape shape_;
    MloOpCode mlo_op_code_;
    std::string mlo_op_name_;
};

}