//
// Created by zurek on 11/18/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "..\binary_obfuscation\pe.h"
#include "..\binary_obfuscation\mem.h"
#include "..\binary_obfuscation\cypher.h"

#define SECTION_NAME    ".dummy"

// Declaration of dummy procedure.
extern const char * dummy_op(void) __attribute__((section(SECTION_NAME)));


// This routines decrypts our section in the virtual memory.
void decryptor() {
    void * sect = 0;
    int size = 0;
    int i = 0;

    FILE * key;
    char * buff;

    key = fopen("naiveC.key", "rb");

    if (!key) {
        printf("Key not found; could not decrypt.\n");
        return;
    }

    // Locate where the section is.
    if (!locateVirSection(SECTION_NAME, &sect, &size)) {
        printf("could not locate the section; aborting...\n");
        return;
    }

    buff = (char *)malloc(sizeof(char) * size);

    fread(buff, 1, size, key);
    fclose(key);

    // Allow to modify such memory.
    if (!unprotectMemory(sect, size)) {
        printf("Error while modifying the virtual memory; aborting...\n");
        return;
    }

    applyXORChyperLong(sect, size, buff, size);
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
