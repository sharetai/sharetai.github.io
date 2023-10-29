#include <stdio.h>
#include <stdlib.h>

void unreachableFunction()
{
    printf("Pwned!\n");
    exit(0);
}

int main() {
    printf("Hello World!\n");
    return 0;
}