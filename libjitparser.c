#include <jit/jit.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "values.h"
#include "my_yylex.h"

#include "experiment.h"


//#include "executions.h"
void apply_prod_0(jit_function_t function, jit_value_t result,
                  int stack_top) {}
void apply_prod_1(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    //result[stack_top - 2] = result[stack_top - 2] + result[stack_top - 0];

    jit_value_t stack_top_minus2 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top - 2);
    jit_value_t stack_top_minus0 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top);
    jit_value_t minus2 = jit_insn_load_elem(
        function, result, stack_top_minus2, jit_type_float64);
    jit_value_t minus0 = jit_insn_load_elem(
        function, result, stack_top_minus0, jit_type_float64);
    jit_value_t temp = jit_insn_add(function, minus2, minus0);
    jit_insn_store_elem(function, result, stack_top_minus2, temp);
}
void apply_prod_2(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] - result[stack_top - 0];

    jit_value_t stack_top_minus2 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top - 2);
    jit_value_t stack_top_minus0 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top);
    jit_value_t minus2 = jit_insn_load_elem(
        function, result, stack_top_minus2, jit_type_float64);
    jit_value_t minus0 = jit_insn_load_elem(
        function, result, stack_top_minus0, jit_type_float64);
    jit_value_t temp = jit_insn_sub(function, minus2, minus0);
    jit_insn_store_elem(function, result, stack_top_minus2, temp);
}
void apply_prod_3(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_4(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] * result[stack_top - 0];

    jit_value_t stack_top_minus2 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top - 2);
    jit_value_t stack_top_minus0 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top);
    jit_value_t minus2 = jit_insn_load_elem(
        function, result, stack_top_minus2, jit_type_float64);
    jit_value_t minus0 = jit_insn_load_elem(
        function, result, stack_top_minus0, jit_type_float64);
    jit_value_t temp = jit_insn_mul(function, minus2, minus0);
    jit_insn_store_elem(function, result, stack_top_minus2, temp);
}
void apply_prod_5(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 2] / result[stack_top - 0];

    jit_value_t stack_top_minus2 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top - 2);
    jit_value_t stack_top_minus0 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top);
    jit_value_t minus2 = jit_insn_load_elem(
        function, result, stack_top_minus2, jit_type_float64);
    jit_value_t minus0 = jit_insn_load_elem(
        function, result, stack_top_minus0, jit_type_float64);
    jit_value_t temp = jit_insn_div(function, minus2, minus0);
    jit_insn_store_elem(function, result, stack_top_minus2, temp);
}
void apply_prod_6(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_7(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_8(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    // result[stack_top - 0] = result[stack_top - 0];
}
void apply_prod_9(jit_function_t function, jit_value_t result,
                  int stack_top)
{
    // result[stack_top - 2] = result[stack_top - 1];

    jit_value_t stack_top_minus2 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top - 2);
    jit_value_t stack_top_minus1 = jit_value_create_nint_constant(
        function, jit_type_nint, stack_top - 1);
    jit_value_t minus1 = jit_insn_load_elem(
        function, result, stack_top_minus1, jit_type_float64);
    jit_insn_store_elem(function, result, stack_top_minus2, minus1);

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


jit_function_t create_code(jit_context_t ctxt, tables_t* tables,
                           char* statement)
{
    jit_type_t params[1];
    //params[0] = jit_type_sys_long_double;
    params[0] = jit_type_float64;

    jit_type_t signature = jit_type_create_signature(
        jit_abi_cdecl, jit_type_float64, params, 1, 1);

    jit_function_t function = jit_function_create(ctxt, signature);

    jit_value_t x = jit_value_get_param(function, 0);
    jit_value_t size = jit_value_create_nint_constant(
        function, jit_type_int, MAX_STATES * sizeof(long double));

    jit_value_t result = jit_insn_alloca(function, size);
    jit_value_t zero = jit_value_create_float64_constant(
        function, jit_type_float64, 0);

    int i;
    for (i = 0; i < 10; i++)
    {
        jit_value_t index = jit_value_create_nint_constant(
            function, jit_type_int, i);
        jit_insn_store_elem(function, result, index, zero);
    }

    int state[MAX_STATES] = {0};
    int stack_top = 0;

    token_t token = my_yylex(statement);

    while (true)
    {
        if (token.id == INVALID_TOKEN)
        {
            printf("Invalid token has been found at %Lf-th position of input.",
                   token.data);
            return function;
        }

        int cur_state = state[stack_top];
        table_cell_t cell = tables->trans[cur_state][token.id];

        jit_value_t stack_top_const;

        switch (cell.action)
        {
            case AC_SHIFT:
                stack_top++;
                state[stack_top] = cell.num;

                jit_value_t rval;

                if (token.data != X)
                {
                    rval = jit_value_create_float64_constant(
                        function, jit_type_float64,
                        (double)token.data);
                }
                else
                {
                    rval = x;
                }

                stack_top_const = jit_value_create_nint_constant(
                    function, jit_type_int, stack_top);
                jit_insn_store_elem(function, result, stack_top_const, rval);

                token = my_yylex("");

                break;

            case AC_REDUCE:
                apply[cell.num](function, result, stack_top);
                stack_top -= tables->grammar_size[cell.num];
                cur_state = state[stack_top];
                state[++stack_top] = tables->
                    trans[cur_state][tables->grammar_left[cell.num]].num;
                break;

            case AC_ACCEPT:;
                stack_top_const = jit_value_create_nint_constant(
                    function, jit_type_int, stack_top);
                jit_value_t answer = jit_insn_load_elem(
                    function, result, stack_top_const, jit_type_float64);
                jit_insn_return(function, answer);

                return function;

            case AC_ERROR:
                printf("Invalid token [id=%d] for the %d-th state.\n",
                       token.id, cur_state);
                return function;
        }
    }

    return function;
}


long double calculate(jit_function_t function, double x)
{
    void* args[1];
    args[0] = &x;
    double result;
    jit_function_apply(function, args, &result);

    return result;
}


jit_function_t get_jit_function(tables_t* tables, char* statement)
{
    jit_context_t ctxt = jit_context_create();
    jit_context_build_start(ctxt);

    jit_function_t function = create_code(ctxt, tables, statement);

    jit_function_compile(function);
    jit_context_build_end(ctxt);

    return function;
}


double test_for_one_len(tables_t* tables, char* statement)
{
    jit_function_t jit_fun = get_jit_function(tables, statement);

    double sum = 0;
    int attempt;
    for (attempt = 0; attempt < ATTEMPTS_PER_TEST; attempt++)
    {
        double start_time = clock();

        int x;
        for (x = 0; x < X_RANGE; x++)
        {
            calculate(jit_fun, x);
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
        printf("libjit,%d,%.3lf\n", i + 1, timer[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    tables_t tables =
    {
        #include "syn_tables.h"
    };

    char* statements[] =
    {
        #include "statements.h"
    };

    if (argc > 1)
    {
        jit_function_t jit_fun = get_jit_function(&tables, argv[1]);
        printf("%.17Lf\n", calculate(jit_fun, 0));
    }
    else
    {
        //test_for_one_len(&tables, statements[19]);

        //jit_function_t dummy = get_jit_function(&tables, statements[19]);
        //printf("%Lf\n", (long double)calculate(dummy, (double)12)); // -6.318700

        measure_time(&tables, statements);
    }

    return (EXIT_SUCCESS);
}
