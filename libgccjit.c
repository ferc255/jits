#include <libgccjit.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "values.h"
#include "my_yylex.h"


//#include "executions.h"
void apply_prod_0(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top) {}
void apply_prod_1(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    //result[stack_top - 2] = result[stack_top - 2] + result[stack_top - 0];

    gcc_jit_block_add_assignment(
        block, NULL,
        gcc_jit_context_new_array_access(
            ctxt, NULL,
            result,
            gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top - 2)
        ),
        gcc_jit_context_new_binary_op(
            ctxt, NULL, GCC_JIT_BINARY_OP_PLUS, Lf_type,
            gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
                ctxt, NULL,
                result,
                gcc_jit_context_new_rvalue_from_int(
                    ctxt, int_type, stack_top - 2)
            )),
            gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
                ctxt, NULL,
                result,
                gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top)
            ))
        )
    );
}
void apply_prod_2(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] - result[stack_top - 0];

    gcc_jit_block_add_assignment(
        block, NULL,
        gcc_jit_context_new_array_access(
            ctxt, NULL,
            result,
            gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top - 2)
        ),
        gcc_jit_context_new_binary_op(
            ctxt, NULL, GCC_JIT_BINARY_OP_MINUS, Lf_type,
            gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
                ctxt, NULL,
                result,
                gcc_jit_context_new_rvalue_from_int(
                    ctxt, int_type, stack_top - 2)
            )),
            gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
                ctxt, NULL,
                result,
                gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top)
            ))
        )
    );
}
void apply_prod_3(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_4(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] * result[stack_top - 0];

    gcc_jit_block_add_assignment(
        block, NULL,
        gcc_jit_context_new_array_access(
            ctxt, NULL,
            result,
            gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top - 2)
        ),
        gcc_jit_context_new_binary_op(
            ctxt, NULL, GCC_JIT_BINARY_OP_MULT, Lf_type,
            gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
                ctxt, NULL,
                result,
                gcc_jit_context_new_rvalue_from_int(
                    ctxt, int_type, stack_top - 2)
            )),
            gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
                ctxt, NULL,
                result,
                gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top)
            ))
        )
    );
}
void apply_prod_5(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] / result[stack_top - 0];

    gcc_jit_block_add_assignment(
        block, NULL,
        gcc_jit_context_new_array_access(
            ctxt, NULL,
            result,
            gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top - 2)
        ),
        gcc_jit_context_new_binary_op(
            ctxt, NULL, GCC_JIT_BINARY_OP_DIVIDE, Lf_type,
            gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
                ctxt, NULL,
                result,
                gcc_jit_context_new_rvalue_from_int(
                    ctxt, int_type, stack_top - 2)
            )),
            gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
                ctxt, NULL,
                result,
                gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top)
            ))
        )
    );
}
void apply_prod_6(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    //result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_7(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    //result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_8(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    //result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_9(gcc_jit_context* ctxt, gcc_jit_block* block,
                  gcc_jit_type* int_type, gcc_jit_type* Lf_type,
                  gcc_jit_rvalue* result, int stack_top)
{
    //result[stack_top - 2] = result[stack_top - 1];

    gcc_jit_block_add_assignment(
        block, NULL,
        gcc_jit_context_new_array_access(
            ctxt, NULL,
            result,
            gcc_jit_context_new_rvalue_from_int(ctxt, int_type, stack_top - 2)
        ),
        gcc_jit_lvalue_as_rvalue(gcc_jit_context_new_array_access(
            ctxt, NULL,
            result,
            gcc_jit_context_new_rvalue_from_int(
                ctxt, int_type, stack_top - 1)
        ))
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


void create_code(gcc_jit_context* ctxt, tables_t* tables)
{
    gcc_jit_type* int_type =
        gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT);
    gcc_jit_type* Lf_type =
        gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_LONG_DOUBLE);
    gcc_jit_type* array_int_type =
        gcc_jit_context_new_array_type(ctxt, NULL, int_type, MAX_STATES);
    gcc_jit_type* array_Lf_type =
        gcc_jit_context_new_array_type(ctxt, NULL, Lf_type, MAX_STATES);

    gcc_jit_param* x_val =
        gcc_jit_context_new_param(ctxt, NULL, Lf_type, "x_val");

    gcc_jit_function* func =
        gcc_jit_context_new_function(
            ctxt, NULL, GCC_JIT_FUNCTION_EXPORTED, Lf_type, "libgccjit",
            1, &x_val, 0
        );

    gcc_jit_block* block =
        gcc_jit_function_new_block(func, "main_block");

    //gcc_jit_lvalue* state =
    //    gcc_jit_function_new_local(func, NULL, array_int_type, "state");
    gcc_jit_rvalue* result =
        gcc_jit_lvalue_as_rvalue(
            gcc_jit_function_new_local(func, NULL, array_Lf_type, "result"));
    //gcc_jit_lvalue* stack_top =
    //    gcc_jit_function_new_local(func, NULL, int_type, "stack_top");
    //gcc_jit_block_add_assignment(
    //    block, NULL, stack_top, gcc_jit_context_zero(ctxt, int_type));

    gcc_jit_rvalue* x =
        gcc_jit_param_as_rvalue(x_val);

    int state[MAX_STATES] = {0};
    int stack_top = 0;
  
    token_t token = my_yylex("((2*12+1)/4-7.7)*0.3+(12/(6.1-(12-0.2)))");

    while (true)
    {
        if (token.id == INVALID_TOKEN)
        {
            printf("Invalid token has been found at %Lf-th position of input.",
                   token.data);
            return;
        }

        int cur_state = state[stack_top];
        table_cell_t cell = tables->trans[cur_state][token.id];
        
        switch (cell.action)
        {
            case AC_SHIFT:
                stack_top++;
                state[stack_top] = cell.num;

                gcc_jit_block_add_assignment(
                    block, NULL,
                    gcc_jit_context_new_array_access(
                        ctxt, NULL,
                        result,
                        gcc_jit_context_new_rvalue_from_int(
                            ctxt, int_type, stack_top)
                    ),
                    gcc_jit_context_new_rvalue_from_double(
                        ctxt, Lf_type, token.data)
                );
                
                //result[stack_top] = token.data;
                token = my_yylex("");

                break;
                
            case AC_REDUCE:
                printf("%d\n", cell.num);

                apply[cell.num](ctxt, block,
                                int_type, Lf_type,
                                result, stack_top);
                stack_top -= tables->grammar_size[cell.num];
                cur_state = state[stack_top];
                state[++stack_top] = tables->
                    trans[cur_state][tables->grammar_left[cell.num]].num;
                break;
                
            case AC_ACCEPT:
                gcc_jit_block_end_with_return(
                    block,
                    NULL,
                    gcc_jit_lvalue_as_rvalue(
                        gcc_jit_context_new_array_access(
                            ctxt,
                            NULL,
                            result,
                            gcc_jit_context_one(ctxt, int_type)
                        )
                    )
                );
             
                return;
                
            case AC_ERROR:
                printf("Invalid token [id=%d] for the %d-th state.\n",
                       token.id, cur_state);
                return;
        }        
    }
}


typedef long double (*fn_type)(long double);

fn_type get_jit_function(tables_t* tables)
{
    gcc_jit_context* ctxt = gcc_jit_context_acquire();
    if (!ctxt)
    {
        printf("Bad context\n");
        exit(0);
    }

    create_code(ctxt, tables);

    gcc_jit_result* result = gcc_jit_context_compile(ctxt);
    if (!result)
    {
        printf("JIT-level compilation is failed\n");
        exit(0);
    }
    gcc_jit_context_release(ctxt);

    void* fn_ptr = gcc_jit_result_get_code(result, "libgccjit");
    if (!fn_ptr)
    {
        printf("Cannot get function from the JIT\n");
        exit(0);
    }

    return (fn_type)fn_ptr;
}


int main()
{
    tables_t tables = 
    {
        #include "syn_tables.h"
    };

    /*
    if (!parse(&tables))
    {
        return (EXIT_FAILURE);
    }
    */

    fn_type dummy = get_jit_function(&tables);
    printf("%Lf\n", dummy(2));

    return (EXIT_SUCCESS);
}
