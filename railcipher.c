#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int main(int argc, char** argv){
    assert(argc == 3);
    
    FILE* keyFile = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    return 0;
}
