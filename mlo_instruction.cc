#include "mlo_instruction.h"

namespace cip {

MloInstruction::MloInstruction(OpCode opcode) {
    opcode_ = opcode;
}

OpCode MloInstruction::opcode() {
    return opcode_;
}

};