#include "mlo_module.h"

namespace cip {

MloModule::MloModule(const std::vector<MloInstruction> &mlo_instructions) {
    mlo_instructions_ = mlo_instructions;
}

std::vector<MloInstruction> MloModule::instructions() {
    return mlo_instructions_;
}

};