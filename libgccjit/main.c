#include <libgccjit.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "values.h"
#include "my_yylex.h"
#include "executions.h"


bool parse(tables_t* tables)
{
    int state[MAX_STATES] = {0};
    int result[MAX_STATES] = {0};
    int stack_top = 0;
    
    token_t token = my_yylex();
    
    while (true)
    {
        if (token.id == INVALID_TOKEN)
        {
            printf("Invalid token has been found at %d-th position of input.",
                   token.data);
            return false;
        }
        
        int cur_state = state[stack_top];
        table_cell_t cell = tables->trans[cur_state][token.id];
        
        switch (cell.action)
        {
            case AC_SHIFT:
                stack_top++;
                state[stack_top] = cell.num;
                result[stack_top] = token.data;
                token = my_yylex();
                break;
                
            case AC_REDUCE:
                apply[cell.num](&result, stack_top);                
                stack_top -= tables->grammar_size[cell.num];
                cur_state = state[stack_top];
                state[++stack_top] = tables->
                    trans[cur_state][tables->grammar_left[cell.num]].num;
                break;
                
            case AC_ACCEPT:
                printf("Result: %d\n", result[1]);
                return true;
                
            case AC_ERROR:
                printf("Invalid token [id=%d] for the %d-th state.\n",
                       token.id, cur_state);
                return false;
        }
    }
}


void create_code(gcc_jit_context* ctxt)
{
    gcc_jit_type* Lf_type =
        gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_LONG_DOUBLE);

    gcc_jit_param* x_val =
        gcc_jit_context_new_param(ctxt, NULL, Lf_type, "x_val");

    gcc_jit_function* func =
        gcc_jit_context_new_function(
            ctxt, NULL, GCC_JIT_FUNCTION_EXPORTED, Lf_type, "dummy",
            1, &x_val, 0
        );

    gcc_jit_block* block =
        gcc_jit_function_new_block(func, "main_block");

    gcc_jit_lvalue* result =
        gcc_jit_function_new_local(func, NULL, Lf_type, "result");
    gcc_jit_rvalue* x =
        gcc_jit_param_as_rvalue(x_val);

    char str[100];
    scanf("%s", str);

    gcc_jit_block_add_assignment(
        block, NULL, result, gcc_jit_context_new_rvalue_from_double(
            ctxt, Lf_type, strtold(&str[0], NULL)));

    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if ('0' <= str[i] && str[i] <= '9')
        {
            gcc_jit_rvalue* digit =
                gcc_jit_context_new_rvalue_from_double(
                    ctxt, Lf_type, strtold(&str[i], NULL));
            if (i > 0)
            {
                if (str[i - 1] == '+')
                {
                    gcc_jit_block_add_assignment_op(
                        block, NULL, result, GCC_JIT_BINARY_OP_PLUS, digit);
                }
                else
                {
                    gcc_jit_block_add_assignment_op(
                        block, NULL, result, GCC_JIT_BINARY_OP_MULT, digit);
                }
            }
        }
    }


    gcc_jit_block_end_with_return(
        block, NULL, gcc_jit_lvalue_as_rvalue(result));
                                  
}


typedef long double (*fn_type)(long double);

fn_type get_jit_function()
{
    gcc_jit_context* ctxt = gcc_jit_context_acquire();
    if (!ctxt)
    {
        printf("Bad context\n");
        exit(0);
    }

    create_code(ctxt);

    gcc_jit_result* result = gcc_jit_context_compile(ctxt);
    if (!result)
    {
        printf("JIT-level compilation is failed\n");
        exit(0);
    }
    gcc_jit_context_release(ctxt);

    void* fn_ptr = gcc_jit_result_get_code(result, "dummy");
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

    fn_type dummy = get_jit_function();
    printf("%Lf\n", dummy(2));

    return (EXIT_SUCCESS);
}
