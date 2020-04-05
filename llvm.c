#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <stdbool.h>
#include <inttypes.h>


#include "values.h"
#include "my_yylex.h"

#include "experiment.h"


//#include "executions.h"
void apply_prod_0(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top) {}
void apply_prod_1(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    //result[stack_top - 2] = result[stack_top - 2] + result[stack_top - 0];

    *result = LLVMBuildInsertElement(
        builder,
        *result,
        LLVMBuildFAdd(
            builder,
            LLVMBuildExtractElement(
                builder,
                *result,
                LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
                ""
            ),
            LLVMBuildExtractElement(
                builder,
                *result,
                LLVMConstInt(LLVMInt32Type(), stack_top, true),
                ""
            ),
            ""
        ),
        LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
        ""
    );
}
void apply_prod_2(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] - result[stack_top - 0];

    *result = LLVMBuildInsertElement(
        builder,
        *result,
        LLVMBuildFSub(
            builder,
            LLVMBuildExtractElement(
                builder,
                *result,
                LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
                ""
            ),
            LLVMBuildExtractElement(
                builder,
                *result,
                LLVMConstInt(LLVMInt32Type(), stack_top, true),
                ""
            ),
            ""
        ),
        LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
        ""
    );
}
void apply_prod_3(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_4(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] * result[stack_top - 0];

    *result = LLVMBuildInsertElement(
        builder,
        *result,
        LLVMBuildFMul(
            builder,
            LLVMBuildExtractElement(
                builder,
                *result,
                LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
                ""
            ),
            LLVMBuildExtractElement(
                builder,
                *result,
                LLVMConstInt(LLVMInt32Type(), stack_top, true),
                ""
            ),
            ""
        ),
        LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
        ""
    );
}
void apply_prod_5(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] / result[stack_top - 0];

    *result = LLVMBuildInsertElement(
        builder,
        *result,
        LLVMBuildFDiv(
            builder,
            LLVMBuildExtractElement(
                builder,
                *result,
                LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
                ""
            ),
            LLVMBuildExtractElement(
                builder,
                *result,
                LLVMConstInt(LLVMInt32Type(), stack_top, true),
                ""
            ),
            ""
        ),
        LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
        ""
    );
}
void apply_prod_6(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_7(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_8(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_9(LLVMBuilderRef builder, LLVMValueRef* result, int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 1];

    *result = LLVMBuildInsertElement(
        builder,
        *result,
        LLVMBuildExtractElement(
            builder,
            *result,
            LLVMConstInt(LLVMInt32Type(), stack_top - 1, true),
            ""
        ),
        LLVMConstInt(LLVMInt32Type(), stack_top - 2, true),
        ""
    );
}
void (*apply[])() =
{
    apply_prod_0,
    apply_prod_1,
    apply_prod_2,
    apply_prod_3,
    apply_prod_4,
    apply_prod_5,
    apply_prod_6,
    apply_prod_7,
    apply_prod_8,
    apply_prod_9,
};


LLVMValueRef create_code(LLVMModuleRef module, tables_t* tables, char* statement)
{
    LLVMTypeRef param_types[] = { LLVMX86FP80Type() };
    LLVMTypeRef ret_type = LLVMFunctionType(LLVMX86FP80Type(), param_types, 1, 0);
    LLVMValueRef func = LLVMAddFunction(module, "calculate", ret_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, "entry");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, entry);

    LLVMTypeRef vectortype = LLVMVectorType(LLVMX86FP80Type(), MAX_STATES);
    LLVMValueRef result = LLVMGetUndef(vectortype);

    LLVMValueRef x = LLVMGetParam(func, 0);

    int state[MAX_STATES] = {0};
    int stack_top = 0;

    token_t token = my_yylex(statement);

    while (true)
    {
        if (token.id == INVALID_TOKEN)
        {
            printf("Invalid token has been found at %Lf-th position of input.",
                   token.data);
            return func;
        }

        int cur_state = state[stack_top];
        table_cell_t cell = tables->trans[cur_state][token.id];

        switch (cell.action)
        {
            case AC_SHIFT:
                stack_top++;
                state[stack_top] = cell.num;

                LLVMValueRef rval;

                if (token.data != X)
                {
                    rval = LLVMConstReal(LLVMX86FP80Type(), token.data);
                }
                else
                {
                    rval = x;
                }

                result = LLVMBuildInsertElement(
                    builder,
                    result,
                    rval,
                    LLVMConstInt(LLVMInt32Type(), stack_top, true),
                    ""
                );

                token = my_yylex("");

                break;

            case AC_REDUCE:
                apply[cell.num](builder, &result, stack_top);
                stack_top -= tables->grammar_size[cell.num];
                cur_state = state[stack_top];
                state[++stack_top] = tables->
                    trans[cur_state][tables->grammar_left[cell.num]].num;
                break;

            case AC_ACCEPT:
                LLVMBuildRet(
                    builder,
                    LLVMBuildExtractElement(
                        builder,
                        result,
                        LLVMConstInt(LLVMInt32Type(), 1, true),
                        ""
                    )
                );

                return func;

            case AC_ERROR:
                printf("Invalid token [id=%d] for the %d-th state.\n",
                       token.id, cur_state);
                return func;
        }
    }
}


typedef long double (*fn_type) (long double);

fn_type get_jit_function(tables_t* tables, char* statement)
{
    LLVMModuleRef module = LLVMModuleCreateWithName("my_module");

    LLVMValueRef func = create_code(module, tables, statement);

    char *error = NULL;
    LLVMVerifyModule(module, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);

    LLVMExecutionEngineRef engine;
    error = NULL;
    LLVMLinkInMCJIT();
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();
    if (LLVMCreateExecutionEngineForModule(&engine, module, &error) != 0) {
        fprintf(stderr, "failed to create execution engine\n");
        abort();
    }
    if (error) {
        fprintf(stderr, "error: %s\n", error);
        LLVMDisposeMessage(error);
        exit(EXIT_FAILURE);
    }

    return (fn_type)LLVMGetPointerToGlobal(engine, func);
}

double test_for_one_len(tables_t* tables, char* statement)
{
    fn_type calculate = get_jit_function(tables, statement);

    double sum = 0;
    int attempt;
    for (attempt = 0; attempt < ATTEMPTS_PER_TEST; attempt++)
    {
        double start_time = clock();

        int x;
        for (x = 0; x < X_RANGE; x++)
        {
            calculate(x);
        }

        double elapsed = (clock() - start_time) / CLOCKS_PER_SEC;
        sum += elapsed;

        printf("Elapsed time: %.3f sec\n", elapsed);
    }

    return sum;
}


void measure_time(tables_t* tables, char* statements[20])
{
    double timer[MAX_STATEMENT_SIZE];
    int len;
    for (len = MIN_STATEMENT_SIZE; len < MAX_STATEMENT_SIZE; len++)
    {
        printf("[len = %d]\n", len + 1);

        double sum = test_for_one_len(tables, statements[len]);
        timer[len] = sum / ATTEMPTS_PER_TEST;

        printf("_________________________________\n");
        printf("Average elapsed time: %.3f sec\n", timer[len]);
    }

    printf("\n");
    int i;
    for (i = 0; i < MAX_STATEMENT_SIZE; i++)
    {
        printf("llvm,%d,%.3lf\n", i + 1, timer[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    tables_t tables =
    {
        #include "syn_tables.h"
    };

    const char* statements[20] =
    {
        #include "statements.h"
    };

    if (argc > 1)
    {
        fn_type calculate = get_jit_function(&tables, argv[1]);

        printf("%.17Lf\n", calculate(12));
    }
    else
    {
        //test_for_one_len(&tables, statements[19]);

        /*
          fn_type dummy = get_jit_function(&tables, statements[19]);
          printf("%Lf\n", dummy(12)); // -6.318700
          dummy = get_jit_function(&tables, statements[11]);
          printf("%Lf\n", dummy(50)); // -198.012978
        */

        measure_time(&tables, statements);
    }



    return (EXIT_SUCCESS);
}
