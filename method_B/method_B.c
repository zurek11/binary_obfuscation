//
// Created by zurek on 11/18/2019.
//
#include <stdio.h>
#include <string.h>

#include "..\binary_obfuscation\pe.h"
#include "..\binary_obfuscation\mem.h"
#include "..\binary_obfuscation\cypher.h"

#define SECTION_NAME    ".dummy"

// Declaration of dummy procedure.
extern const char * dummy_op(void) __attribute__((section(SECTION_NAME)));

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

// This routines decrypts our section in the virtual memory.
void decryptor() {
    void * sect = 0;
    int size = 0;
    int i = 0;

    // Locate where the section is.
    if (!locateVirSection(SECTION_NAME, &sect, &size)) {
        printf("could not locate the section; aborting...\n");
        return;
    }

    // Allow to modify such memory.
    if (!unprotectMemory(sect, size)) {
        printf("Error while modifying the virtual memory; aborting...\n");
        return;
    }

    applyXORChyperLong(sect, size, key, 32);
}

int main(int argc, char ** argv) {
    char name[50];

    printf("Type valid password: ");
    scanf("%s", name);

    // Decrypt the data section.
    decryptor();

    if (strcmp(name, dummy_op()) == 0){
        printf("Good.\n");
    }
    else {
        printf("Wrong.\n");
    }

    return 0;
}

const char * dummy_op(){
    return "unicorns";
}
