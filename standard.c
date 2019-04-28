#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "values.h"
#include "my_yylex.h"
#include "executions.h"


#define ATTEMPTS_PER_TEST 5
#define MAX_STATEMENT_SIZE 5


long double parse(tables_t* tables, char* statement, long double x)
{
    int state[MAX_STATES] = {0};
    long double result[MAX_STATES] = {0};
    int stack_top = 0;

    double st = clock();
    token_t token = my_yylex(statement);
    //printf("[lex1 %.0f] ", clock() - st);

    while (true)
    {
        if (token.id == INVALID_TOKEN)
        {
            printf("Invalid token has been found [id=%d, data=\"%Lf\"",
                   token.id, token.data);
            return false;
        }
        
        int cur_state = state[stack_top];
        table_cell_t cell = tables->trans[cur_state][token.id];

        switch (cell.action)
        {
            case AC_SHIFT:
                stack_top++;
                state[stack_top] = cell.num;
                if (token.data != X)
                {
                    result[stack_top] = token.data;
                }
                else
                {
                    result[stack_top] = x;
                }
                st = clock();
                token = my_yylex("");
                //printf("[lex2 %.0f] ", clock() - st);
                break;
                
            case AC_REDUCE:
                apply[cell.num](&result, stack_top);                
                stack_top -= tables->grammar_size[cell.num];
                cur_state = state[stack_top];
                state[++stack_top] = tables->
                    trans[cur_state][tables->grammar_left[cell.num]].num;
                break;
                
            case AC_ACCEPT:
                return result[1];
                
            case AC_ERROR:
                printf("Invalid token [id=%d] for the %d-th state.\n",
                       token.id, cur_state);
                return -1.11111;
        }
    }
}


void measure_time(tables_t* tables, char* statements[20])
{
    double timer[MAX_STATEMENT_SIZE];
    int len;
    for (len = 0; len < MAX_STATEMENT_SIZE; len++)
    {
        printf("[len = %d]\n", len + 1);
        double sum = 0;
        int attempt;
        for (attempt = 0; attempt < ATTEMPTS_PER_TEST; attempt++)
        {
            double start_time = clock();

            int x;
            for (x = 0; x < 1e5; x++)
            {
                double st = clock();
                //printf("[x %d] ", x);
                parse(tables, statements[len], x);
                //printf("[total] %.0f\n\n", clock() - st);
            }

            double elapsed = (clock() - start_time) / CLOCKS_PER_SEC;
            sum += elapsed;

            printf("Elapsed time: %.3f sec\n", elapsed);
        }
        timer[len] = sum / attempt;

        printf("_________________________________\n");
        printf("Average elapsed time: %.3f sec\n", sum / attempt);
    }

    printf("\n");
    int i;
    for (i = 0; i < MAX_STATEMENT_SIZE; i++)
    {
        printf("recalc,%d,%.3lf\n", i + 1, timer[i]);
    }
    printf("\n");
}


int main()
{
    tables_t tables = 
    {
        #include "syn_tables.h"
    };

    char* statements[20] =
    {
        #include "statements.h"
    };

    //printf("%Lf\n", parse(&tables, statements[19], 12)); // -6.318700
    //printf("%Lf\n", parse(&tables, statements[11], 50)); // -198.012978

    measure_time(&tables, statements);
    
    return (EXIT_SUCCESS);
}
