/**
 * LLVM equivalent of:
 *
 * int sum(int a, int b) {
 *     return a + b;
 * }
 */

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef int32_t (*funcPtr_t) (int32_t, int32_t);

int main(int argc, char const *argv[]) {
    LLVMModuleRef mod = LLVMModuleCreateWithName("my_module");

    LLVMTypeRef param_types[] = { LLVMInt32Type(), LLVMInt32Type() };
    LLVMTypeRef ret_type = LLVMFunctionType(LLVMInt32Type(), param_types, 2, 0);
    LLVMValueRef sum = LLVMAddFunction(mod, "mul", ret_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(sum, "entry");

    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, entry);
    LLVMValueRef tmp = LLVMBuildAdd(builder, LLVMGetParam(sum, 0), LLVMGetParam(sum, 1), "tmp");

    LLVMTypeRef vectortype = LLVMVectorType(LLVMInt32Type(), 10);
    LLVMValueRef vec = LLVMGetUndef(vectortype);
    vec = LLVMBuildInsertElement(  // vec[0] = 7;
        builder,
        vec,
        LLVMConstInt(LLVMInt32Type(), 7, true),
        LLVMConstInt(LLVMInt32Type(), 0, true),
        ""
    );
    vec = LLVMBuildInsertElement(  // vec[1] = 9;
        builder,
        vec,
        LLVMConstInt(LLVMInt32Type(), 9, true),
        LLVMConstInt(LLVMInt32Type(), 1, true),
        ""
    );
    LLVMValueRef first = LLVMBuildExtractElement(
        builder,
        vec,
        LLVMConstInt(LLVMInt32Type(), 0, true),
        ""
    );
    LLVMValueRef second = LLVMBuildExtractElement(
        builder,
        vec,
        LLVMConstInt(LLVMInt32Type(), 1, true),
        ""
    );
    LLVMValueRef mult = LLVMBuildMul(builder, first, second, "");
    vec = LLVMBuildInsertElement(  // vec[5] = 63;
        builder,
        vec,
        mult,
        LLVMConstInt(LLVMInt32Type(), 5, true),
        ""
    );
    LLVMValueRef c = LLVMBuildExtractElement(
        builder,
        vec,
        LLVMConstInt(LLVMInt32Type(), 5, 0),
        ""
    );


    /*
    LLVMValueRef b = LLVMConstInt(LLVMInt32Type(), 24, 0);
    LLVMValueRef t_o = LLVMConstInt(LLVMInt32Type(), 21, 0);
    LLVMValueRef one = LLVMConstInt(LLVMInt32Type(), 1, 0);
    LLVMValueRef zero = LLVMConstInt(LLVMInt32Type(), 0, 0);


    //LLVMTypeRef arraytype = LLVMArrayType(LLVMInt32Type(), 2);
    LLVMTypeRef vectortype = LLVMVectorType(LLVMInt32Type(), 2);
    //LLVMValueRef a = LLVMBuildArrayAlloca(builder, arraytype, b, "ar");
    //LLVMValueRef a = LLVMBuildArrayMalloc(builder, arraytype, b, "ar");
    //LLVMBuildStore(builder, b, a);
    //LLVMValueRef va = LLVMAddGlobal(mod, vectortype, "vector122");


    LLVMValueRef vec = LLVMGetUndef(vectortype);
    vec = LLVMBuildInsertElement(builder, vec, b, one, "foiwejf");
    vec = LLVMBuildInsertElement(builder, vec, t_o, zero, "foiwejf");
    LLVMValueRef c = LLVMBuildExtractElement(builder, vec, zero, "jjkd");
    */

    LLVMBuildRet(builder, c);

    char *error = NULL;
    LLVMVerifyModule(mod, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);

    LLVMExecutionEngineRef engine;
    error = NULL;
    LLVMLinkInMCJIT();
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();
    if (LLVMCreateExecutionEngineForModule(&engine, mod, &error) != 0) {
        fprintf(stderr, "failed to create execution engine\n");
        abort();
    }
    if (error) {
        fprintf(stderr, "error: %s\n", error);
        LLVMDisposeMessage(error);
        exit(EXIT_FAILURE);
    }

    if (argc < 3) {
        fprintf(stderr, "usage: %s x y\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int32_t x = strtoll(argv[1], NULL, 10);
    int32_t y = strtoll(argv[2], NULL, 10);

    {
        funcPtr_t funcPtr = (funcPtr_t)LLVMGetPointerToGlobal(engine, sum);
        printf("%d\n", funcPtr(x,y));
    }

    // Write out bitcode to file
    if (LLVMWriteBitcodeToFile(mod, "sum.bc") != 0) {
        fprintf(stderr, "error writing bitcode to file, skipping\n");
    }

    LLVMDisposeBuilder(builder);
    LLVMDisposeExecutionEngine(engine);
}
