#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "values.h"
#include "my_yylex.h"
#include "executions.h"

#include "experiment.h"


typedef enum
{
    AT_X,
    AT_LEAF,
    AT_FUNCTION,
} ast_node_type_t;

typedef struct ast_node_t
{
    int fun_idx;
    long double val;
    ast_node_type_t type;
    int child[3];
} ast_node_t;


void build_ast(tables_t* tables, char* statement,
               ast_node_t* arena, int* arena_top)
{
    int state[MAX_STATES] = {0};
    int stack_top = -1;

    int input_ptr = 0;
    token_t token = my_yylex(statement);

    int arena_idx[BUFFER_SIZE];

    while (true)
    {        
        if (token.id == INVALID_TOKEN)
        {
            printf("Invalid token has been found at %d-th position of input.",
                   (int)token.data);
            exit(0);
        }
        
        int cur_state = state[stack_top];
        table_cell_t cell = tables->trans[cur_state][token.id];

        switch (cell.action)
        {
            case AC_SHIFT:
                stack_top++;
                (*arena_top)++;
                state[stack_top] = cell.num;
                if (token.data != X)
                {
                    arena[*arena_top].type = AT_LEAF;
                    arena[*arena_top].val = token.data;
                }
                else
                {
                    arena[*arena_top].type = AT_X;
                }
                token = my_yylex("");

                arena_idx[stack_top] = *arena_top;
                break;
                
            case AC_REDUCE:
                (*arena_top)++;
                arena[*arena_top].type = AT_FUNCTION;
                arena[*arena_top].fun_idx = cell.num;

                int i;
                for (i = 0; i < tables->grammar_size[cell.num]; i++)
                {
                    arena[*arena_top].child[2 - i] =
                        arena_idx[stack_top - i];
                }

                stack_top -= tables->grammar_size[cell.num];
                cur_state = state[stack_top];
                state[++stack_top] = tables->
                    trans[cur_state][tables->grammar_left[cell.num]].num;

                arena_idx[stack_top] = *arena_top;
                break;
                
            case AC_ACCEPT:
                return;
                
            case AC_ERROR:
                printf("Invalid token [id=%d] for the %d-th state.\n",
                       token.id, cur_state);
                exit(0);
        }
    }
}


long double calculate(ast_node_t* arena, int arena_top, long double x,
                      tables_t* tables)
{
    long double aux[3];
    int i;
    for (i = 0; i <= arena_top; i++)
    {
        if (arena[i].type == AT_FUNCTION)
        {
            int j;
            for (j = 0; j < 3; j++)
            {
                aux[j] = arena[arena[i].child[j]].val;
            }
            apply[arena[i].fun_idx](&aux, 2);

            arena[i].val = aux[3 - tables->grammar_size[arena[i].fun_idx]];
        }
        else if (arena[i].type == AT_X)
        {
            arena[i].val = x;
        }
    }

    return arena[arena_top].val;
}


double test_for_one_len(tables_t* tables, char* statement, ast_node_t* arena)
{
    int arena_top = -1;
    build_ast(tables, statement, arena, &arena_top);

    double sum = 0;
    int attempt;
    for (attempt = 0; attempt < ATTEMPTS_PER_TEST; attempt++)
    {
        double start_time = clock();

        int x;
        for (x = 0; x < X_RANGE; x++)
        {
            double st = clock();
            calculate(arena, arena_top, x, tables);
        }

        double elapsed = (clock() - start_time) / CLOCKS_PER_SEC;
        sum += elapsed;

        printf("Elapsed time: %.3f sec\n", elapsed);
    }

    return sum;
}


void measure_time(tables_t* tables, char* statements[20])
{
    ast_node_t arena[BUFFER_SIZE];
    double timer[MAX_STATEMENT_SIZE];

    int len;
    for (len = MIN_STATEMENT_SIZE; len < MAX_STATEMENT_SIZE; len++)
    {
        printf("[len = %d]\n", len + 1);
      
        double sum = test_for_one_len(tables, statements[len], arena);
        timer[len] = sum / ATTEMPTS_PER_TEST;

        printf("_________________________________\n");
        printf("Average elapsed time: %.3f sec\n", timer[len]);
    }

    printf("\n");
    int i;
    for (i = MIN_STATEMENT_SIZE; i < MAX_STATEMENT_SIZE; i++)
    {
        printf("ast,%d,%.3lf\n", i + 1, timer[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    tables_t tables = 
    {
        #include "syn_tables.h"
    };

    char* statements[20] =
    {
        #include "statements.h"
    };

    if (argc > 1)
    {
        ast_node_t arena[BUFFER_SIZE];
        int arena_top = -1;
        build_ast(&tables, argv[1], arena, &arena_top);
        printf("%.17Lf\n", calculate(arena, arena_top, 0, &tables));
    }
    else
    {



        //ast_node_t arena[BUFFER_SIZE];
        //test_for_one_len(&tables, statements[10], arena);

        /*
        int arena_top = -1;
        ast_node_t arena[BUFFER_SIZE];
        build_ast(&tables, statements[19], arena, &arena_top);
        printf("%Lf\n", calculate(arena, arena_top, 12, &tables));  // -6.318700
        build_ast(&tables, statements[11], arena, &arena_top);
        printf("%Lf\n", calculate(arena, arena_top, 50, &tables));  // -198.012978
        */

        measure_time(&tables, statements);
    }

    
    return (EXIT_SUCCESS);
}
