#include "mlo_instruction.h"
#include "codegen/compiler.h"
#include "codegen/gpu/gpu_compiler.h"
#include "codegen/gpu/gpu_ir_emitter.h"

int main() {
    cip::MloInstruction instruction(cip::OpCode::kAdd);
    cip::MloModule mlo_module({instruction});
    cip::Compiler *pc;
    std::string target = "cuda";
    if (target == "cuda") {
        pc = new cip::gpu::GpuCompiler();
    }

    auto exec = pc->run(&mlo_module);

    delete pc;
    return 0;
}
