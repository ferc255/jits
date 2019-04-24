#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "values.h"
#include "my_yylex.h"
#include "executions.h"


bool parse(tables_t* tables, long double x)
{
    int state[MAX_STATES] = {0};
    long double result[MAX_STATES] = {0};
    int stack_top = 0;
    token_t token = my_yylex("3.2-12/(40-6.17)+((2*12+1)/4-7.7)*0.3-(12*4.1-7)/6+(7-12/(6.1-(12-0.2)*0.4))");
    
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
                token = my_yylex("");
                break;
                
            case AC_REDUCE:
                apply[cell.num](&result, stack_top);                
                stack_top -= tables->grammar_size[cell.num];
                cur_state = state[stack_top];
                state[++stack_top] = tables->
                    trans[cur_state][tables->grammar_left[cell.num]].num;
                break;
                
            case AC_ACCEPT:
                printf("Result: %Lf\n", result[1]);
                return true;
                
            case AC_ERROR:
                printf("Invalid token [id=%d] for the %d-th state.\n",
                       token.id, cur_state);
                return false;
        }
    }
}


int main()
{
    tables_t tables = 
    {
        #include "syn_tables.h"
    };
    
    if (!parse(&tables, 12))
    {
        return (EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}
