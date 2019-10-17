#include <stdio.h>
#include <string.h>

int tess(const char* state, int param)
{
    printf("strlen %d\n", (int)strlen(state));
    printf("string %s\n", state);
    for (int i = 0; i < strlen(state); i++)
    {
        printf("%c\n", state[i]);
    }
    printf("%d\n", param);
}
