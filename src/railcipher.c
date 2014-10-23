/***
 *
 * Author: Louis Philip Pena Penn
 * File: railcipher.c
 * Date 10/19/2014
 * Course Section: CIS3360-14
 *
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXCHARACTERS 10000

long getFileSize(FILE* fp);
int validChar(char c);
char *railfenceCipher(char *plaintext, int depth);

int main(int argc, char** argv) {

    assert(argc == 3);
    
    int i = 0, j = 0;
    FILE *keyFile = fopen(argv[1], "r");
    FILE *ifp = fopen(argv[2], "rb");
    char *plaintext, *ciphertext;
    char text[128] = {0};


    if (!keyFile)
        printf("The file, %s, cannot be opened.\n", argv[1]), exit(EXIT_FAILURE);
    if (!ifp) 
        printf("The file, %s, cannot be opened.\n", argv[2]), exit(EXIT_FAILURE);

    // depth is the key for the rail cipher
    int depth;

    if (fscanf(keyFile, "%d", &depth) != 1 && depth < 1 || depth >= 25) {
        printf("Your key file, %s, should contain a single integer less than 25 and larger than 1.\n", argv[1]);
        printf("Check that the vlues are correct.\n");
        exit(EXIT_FAILURE);
    }
    fclose(keyFile);

    int fileSize = getFileSize(ifp);

    // allocate memort for message
    plaintext = calloc(1, fileSize + 1);
    
    if (!plaintext) {
        fclose(ifp);
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    } 
    // while there is text to scan we scan in strings
    // we then loop through each character of the string
    // checking for valid and adding to plaintext array
    while (fscanf(ifp, "%s", text) != EOF) {
        for (j = 0; j < strlen(text); j++) {
            char lowered = tolower(text[j]);
            if (validChar(lowered)){
                plaintext[i] = lowered;
                i++;
            }
        }
    }
    fclose(ifp);

    if (strlen(plaintext) > MAXCHARACTERS) {
        fprintf(stderr, "The text in, %s, is too long.\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    printf("\n\n\n\nRail Fence Depth:%d",depth);
    printf("\n\n\n\nPlaintext:\n\n");
    // print the plaintext
    for (i = 0; i < strlen(plaintext); i++) {
        printf("%c", plaintext[i]);
        if (i != 0 && ((i + 1) % 80 == 0)) {
            printf("\n");
        }
    }
    
    // perform the encryption
    ciphertext = railfenceCipher(plaintext, depth);

    printf("\n\n\nCiphertext:\n\n");  
    
    // print the ciphertext
    for (i = 0; i < strlen(ciphertext); i++) {
        printf("%c", ciphertext[i]);
        if (i != 0 && ((i + 1) % 80 == 0)) {
            printf("\n");
        }
    }
    printf("\n");

    free(plaintext);
    free(ciphertext);
    return 0;
}

// returns the size of the file
long getFileSize(FILE *fp) {

    int size;
    // moves cursor to end of file
    fseek(fp, 0L, SEEK_END);
    // returns position of cursor
    size = ftell(fp);
    //reset cursor to beginning of stream
    rewind(fp);

    return size;
}

int validChar(char c) {
    // here we observe that the 
    // ASCII values we want range from 97 to 122
    if (c < 97 || c > 122) {
        return 0;
    }    
    return 1;

}

char *railfenceCipher(char *plaintext, int depth){
    int i = 0, j = 0, k = 0, movingUp = 0;
    int len = strlen(plaintext);
    char fence[depth][len];
    memset(fence, 0, len * depth * sizeof(char));

    char *finalText = malloc(sizeof(char) * len);
 
    for (j = 0; j < len; j++){
        fence[i][j] = plaintext[j];
        // if we reach the bottom rail we reverse direction and vice versa
        if (i == depth - 1) movingUp = 1;
        else if (i == 0) movingUp = 0;
        
        if (movingUp) i--;
        else if (!movingUp) i++;
    }
    // for each row we loop through all columnds in that row
    // if the char found in that element is valid we
    // appened it to the finalText array,
    for (i = 0; i < depth; i++) {
        for (j = 0; j < len; j++) {
            if (validChar(fence[i][j])) {
                finalText[k] = fence[i][j];
                k++;
            }
        }
    }

    return finalText;
    
}
