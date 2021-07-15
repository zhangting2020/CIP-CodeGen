# CIP-CodeGen
CodeGen for Machine Learning Compiler Framework


# CodeGen主要过程描述
## 1. 构造输入

定义一个指令的格式，即后端Compiler的输入：
- 前端提供给CodeGen模块的是MLOModule，它的表示目前并不明确，该模块输入包含什么？
- 我们如何自己构造一个可以测试的输入，它不一定是MLOModule的准确表示，只用于提供测试所需的信息。


## 2. Compiler::run

根据target，创建对应的Compiler，完成llvm ir的生成和编译。

这里主要给出`target="cuda"`时的过程，调用GpuCompiler的run方法，它接受MLOModule并返回Executable执行对象。

以下需要列出run过程的主要步骤，调用的接口。

### 2.1 CompileModuleToLlvmIr

以下仅仅是举例步骤描述，如果涉及到重要函数的调用，需要说明：

- step 1: xxx function：初始化llvm module
- step 2: `ir_emitter->Handle(&instruction)`：遍历mlo_module的instruction，`GpuIrEmitter::Handle`作为入口，选择instruction的OpCode处理过程

```c++
Status GpuIrEmitter::Handle(MloInstruction *mlo) {
    switch (mlo->opcode()) {
        case kAdd:
            HandleAdd(mlo);
            break;
        ......
        default:
            break;
    }
}
```
- step 3: `ElementalIrEmitter::HandleAdd`中生成该指令的ir，添加到llvm module中

### 2.2 CompileLlvmIrToBinary



### 2.3 封装执行器
