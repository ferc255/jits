#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "values.h"


int calc_max_match(lex_automaton_t* automaton, char* input, int start_pos, 
                   token_id_t* token)
{
    int cur_state = 0;
    int result = 0;

    int i;
    for (i = start_pos; i < strlen(input); i++)
    {
        cur_state = automaton->table[cur_state][input[i]];
        if (cur_state == ERROR_STATE)
        {
            return result;
        }
        if (automaton->final[cur_state] != INVALID_TOKEN)
        {
            *token = automaton->final[cur_state];
            result = i - start_pos + 1;
        }
    }
    
    return result;
}

char temp[BUFFER_SIZE];

void parse_data(token_t* token, char* input, int start_pos, int len)
{
    // That doesn't work for some reasons.
    //char* temp = malloc(len + 1);
    //memcpy(temp, input + start_pos, len);
    int j;
    for (j = 0; j < len; j++)
    {
        temp[j] = input[start_pos + j];
    }
    temp[len] = '\0';
    //

    if (temp[0] == 'x')
    {
        token->data = X;
        return;
    }
    
    int i;
    for (i = 0; i < strlen(temp); i++)
    {
        if (!isdigit(temp[i]) && temp[i] != '.')
        {
            return;
        }
    }
    token->data = strtold(temp, NULL);
}


token_t my_yylex(char* data)
{
    lex_automaton_t automaton =
    {
        #include "lex_automaton.h"
    };

    static char input[BUFFER_SIZE];
    static int i = 0;

    if (strcmp(data, "") != 0)
    {
        i = 0;
        strcpy(input, data);
    }
    
    for ( ; i < strlen(input); )
    {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
        {
            i++;
            continue;
        }
        
        token_t token;
        int max_match = calc_max_match(&automaton, input, i, &token.id);
        
        if (max_match == 0)
        {
            printf("[my_yylex.h] Error while parsing input ");
            printf("at %d position.\n", i);
            exit(0);
        }
        
        parse_data(&token, input, i, max_match);
        i += max_match;
        
        return token;
    }
    
    token_t end = 
    {
        .id = 0,
    };
    
    return end;
}

