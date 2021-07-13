class GpuEmitter {
    void code() {

    }
    runtime_module run() {

    }
}


class Executor {
    void run() {
        for (auto rm : vec_rms) {
            rm.run();
        }
    }
    std::vector<runtime_module> vec_rms;
}


class Compiler {
    virturl run() = 0;
}; 

class GPUCompiler : public Compiler {
    void run() {
        GpuEmitter emit;
        emit.code();
        auto rm = emit.run();
        exec.push_back(rm);
    }
    Executor exec;
};

int main() {
    std::string instruction = "add a b c";
    Device dev;
    Compiler *pc;
    if (dev = GPUDevice) {
        pc = new GPUCompiler();
    } else if () {
        ...
    }
    pc->run();
}

/********************
 * 1. 定义一个指令的格式，即后端Compiler的输入
 * 2. 解析指令，得到元素子类型，输入和输出
 * 3. 定义Compiler及其派生类，根据target创建对应的Compiler
 *      3.1 Compiler成员变量：执行器Executor
 *      3.2 Compiler成员函数：run方法，里面包含llvm ir的生成和编译，以及封装执行器
 * 4. llvm ir的生成通过visitor模式实现，基类为BaseVisitor，派生类为GpuEmitter，CpuEmitter
 *      4.1 在XXXEmitter中调用XXXElementalIrEmitter实现llvm ir的生成
 *      4.2 XXXElementalIrEmitter的基类LLVMIrEmitter实现llvm ir相关的基本功能
 * 5. llvm ir的编译通过visitor模式实现，基类为BaseVisitor，派生类为GpuKernel，CpuKernel
 *      5.1 在GpuKernel和CpuKernel中编译llvm ir
 *      5.2 封装得到执行器Executor
 * 
 * *****************/
