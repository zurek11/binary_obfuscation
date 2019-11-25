//
// Created by zurek on 11/18/2019.
//

#include <stdio.h>
#include <string.h>

#include "..\binary_obfuscation\pe.h"
#include "..\binary_obfuscation\mem.h"
#include "..\binary_obfuscation\cypher.h"

#define SECTION_NAME    ".dummy"
#define KEY             0x55

// Declaration of dummy procedure.
extern const char * dummy_op(void) __attribute__((section(SECTION_NAME)));

// This routines decrypts our section in the virtual memory.
void decryptor() {
    void * sect = 0;
    int size    = 0;
    int i       = 0;

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

    applyXORChyperSmall(sect, size, KEY);
}

const char * dummy_op(){
    return "unicorns";
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
