//
// Created by zurek on 11/18/2019.
//

#include <stdlib.h>
#include <stdio.h>

#include "cypher.h"

#define DEBUG_HEX

void applyProceduralXORChyperSmall(void * memptr, unsigned int size, char key) {
    char * val = (char *)memptr;
    char xor = 0;

    int start_size = 3;
    char start[] = {0x55, 0x48, 0x89};

    int end_size = 4;
    char end[] = { 0xc3, 0x90, 0x90, 0x90 };

    while (size > 0) {
        // Begin to recognize the start token.
        if (*val == start[0]) {
            if (*(val + 1) == start[1] && *(val + 2) == start[2]) {
                xor = 1;        // Switch on xor encryption.
                val = val + 3;  // Skip the prologue.
            }
        }

        // Begin to recognize the end token.
        if (*val == end[0]) {
            if (*(val + 1) == end[1] && *(val + 2) == end[2] && *(val + 3) == end[3]) {
                xor = 0;        // Switch on xor encryption.
                val = val + 4;  // Skip the prologue.
            }
        }

        // Xor encryption enabled?
        if (xor) {
            *val = *val ^ key;
        }

        val++;
        size--;
    }
}

void applyXORChyperSmall(
    void * memptr,
    unsigned int size,
    char key
) {
    char * val = (char *)memptr;

    while (size > 0) {
        *val = *val ^ key;

        val++;
        size--;
    }
}

void applyXORChyperLong(void * memptr, unsigned int size, char * key, unsigned int keysize) {
    char * val = (char *)memptr;
    unsigned int ki = 0;

    while (size > 0) {
        *val = *val ^ key[ki];

        ki = (ki + 1) % keysize;

        val++;
        size--;
    }
}

int applyPhyXORSmallOverSection(char * path, int offset, int size, char key) {
    // Open to modify binary file content.
    FILE * fd = fopen(path, "r+b");
    char * buffer;

    if (!fd) {
        return FAILURE;
    }

    buffer = malloc(size);

    if (!buffer) {
        fclose(fd);
        return FAILURE;
    }

    // Jump to the desired file location and read.
    fseek(fd, offset, SEEK_SET);
    fread(buffer, 1, size, fd);

    printf("\nNative data:\n");
    // Show before.
    showData(buffer, size);

    // Apply the cypher operation.
    applyXORChyperSmall(buffer, size, key);

    printf("\nEncoded data:\n");
    // Show after.
    showData(buffer, size);

    // Go back to the original position and modify the whole section.
    fseek(fd, offset, SEEK_SET);
    fwrite(buffer, 1, size, fd);

    free(buffer);
    fclose(fd);

    return SUCCESS;
}

int applyPhyXORLongOverSection(char * path, int offset, int size, char * key, unsigned int keysize) {
    // Open to modify binary file content.
    FILE * fd = fopen(path, "r+b");
    char * buffer;

    if (!fd) {
        return FAILURE;
    }

    buffer = malloc(size);

    if (!buffer) {
        fclose(fd);
        return FAILURE;
    }

    // Jump to the desired file location and read.
    fseek(fd, offset, SEEK_SET);
    fread(buffer, 1, size, fd);

    printf("\nNative data:\n");
    // Show before.
    showData(buffer, size);

    // Apply the cypher operation.
    applyXORChyperLong(buffer, size, key, keysize);

    printf("\nEncoded data:\n");
    // Show after.
    showData(buffer, size);

    // Go back to the original position and modify the whole section.
    fseek(fd, offset, SEEK_SET);
    fwrite(buffer, 1, size, fd);

    free(buffer);
    fclose(fd);

    return SUCCESS;
}

int applyPhyProceduralEncryption(char * path, int offset, int size, char key) {
    // Open to modify binary file content.
    FILE * fd = fopen(path, "r+b");
    char * buffer;

    if (!fd) {
        return FAILURE;
    }

    buffer = malloc(size);

    if (!buffer) {
        fclose(fd);
        return FAILURE;
    }

    // Jump to the desired file location and read.
    fseek(fd, offset, SEEK_SET);
    fread(buffer, 1, size, fd);

    printf("\nNative data:\n");
    // Show before.
    showData(buffer, size);

    // Apply the cypher operation.
    applyProceduralXORChyperSmall(buffer, size, key);

    printf("\nEncoded data:\n");
    // Show after.
    showData(buffer, size);

    // Go back to the original position and modify the whole section.
    fseek(fd, offset, SEEK_SET);
    fwrite(buffer, 1, size, fd);

    free(buffer);
    fclose(fd);

    return SUCCESS;
}

void showData(void * memptr, unsigned int size) {
    char * val = (char *)memptr;
    int column = 0;

    while (size > 0) {
        if (!column) {
            printf("\n");
        }

        printf("%02x ", *val & 0xff);

        column = (column + 1) % 16;

        val++;
        size--;
    }
}
