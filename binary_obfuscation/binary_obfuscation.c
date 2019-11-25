//
// Created by zurek on 11/18/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "cypher.h"
#include "pe.h"

#define XOR_KEY         0x55

// Apply encryption with single-byte key.
void naiveAEncryption() {
    int sectO = 0;
    int sectS = 0;

    printf("Locating target .dummy section...\n");
    if (locatePhySection("../cmake-build-debug/MakeMethodA.exe", ".dummy", &sectO, &sectS) == FAILURE) {
        printf("I/O error or section not found.\n");
        return;
    }

    printf("Applying obfuscation to .dummy section...\n");
    if (applyPhyXORSmallOverSection("../cmake-build-debug/MakeMethodA.exe", sectO, sectS, XOR_KEY) == FAILURE) {
        printf("\nFailed to apply obfuscation over the whole section.\n");
        return;
    }

    printf("\nNow your application has been obfuscated!\n");
}

// Apply encryption with multy-byte key.
void naiveBEncryption() {
    int sectO = 0;
    int sectS = 0;

    char key[32] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f,

        0x10, 0x11, 0x12, 0x13,
        0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b,
        0x1c, 0x1d, 0x1e, 0x1f,
    };

    printf("Locating target .dummy section...\n");
    if (locatePhySection("../cmake-build-debug/MakeMethodB.exe", ".dummy", &sectO, &sectS) == FAILURE) {
        printf("I/O error or section not found.\n");
        return;
    }

    printf("Applying obfuscation to .dummy section...\n");
    if (applyPhyXORLongOverSection("../cmake-build-debug/MakeMethodB.exe", sectO, sectS, key, 32) == FAILURE) {
        printf("Failed to apply obfuscation over the whole section.\n");
        return;
    }

    printf("Done!\n");
}

// Apply encryption with multy-byte key.
void naiveCEncryption() {
    int sectO = 0;
    int sectS = 0;

    char byte;
    char * buff;
    int i = 0;

    FILE * kfd; // Key file descriptor.

    printf("Locating target .dummy section...\n");
    if (locatePhySection("../cmake-build-debug/MakeMethodC.exe", ".dummy", &sectO, &sectS) == FAILURE) {
        printf("I/O error or section not found.\n");
        return;
    }

    buff = (char *)malloc(sizeof(char) * sectS);

    // Give the random number generator a seed.
    // This is a very weak method to obtain random numbers.
    srand(time(NULL));

    // Generate and save the key.
    for (i; i < sectS; i++) {
        buff[i] = rand();
    }

    // Generate the key file.
    kfd = fopen("naiveC.key", "wb");

    // Save the key in memory.
    fwrite(buff, 1, sectS, kfd);

    fclose(kfd);

    printf("Applying obfuscation to .dummy section...\n");
    if (applyPhyXORLongOverSection("../cmake-build-debug/MakeMethodC.exe", sectO, sectS, buff, sectS) == FAILURE) {
        printf("Failed to apply obfuscation over the whole section.\n");
        return;
    }

    free(buff);
    printf("Done!\n");
}

void onlyNecessaryEncryption() {
    int sectO = 0;
    int sectS = 0;

    printf("Locating target .dummy section...\n");
    if (locatePhySection("../cmake-build-debug/MakeMethodD.exe", ".dummy", &sectO, &sectS) == FAILURE) {
        printf("I/O error or section not found.\n");
        return;
    }

    printf("Applying obfuscation to .dummy section...\n");
    if (applyPhyProceduralEncryption("../cmake-build-debug/MakeMethodD.exe", sectO, sectS, XOR_KEY) == FAILURE) {
        printf("\nFailed to apply obfuscation over the whole section.\n");
        return;
    }

    printf("\nNow your application has been obfuscated!\n");
}

// Entrypoint for the binary.
int main(int argc, char ** argv) {
//    naiveAEncryption();
//    naiveBEncryption();
//    naiveCEncryption();
    onlyNecessaryEncryption();

    return 0;
}
