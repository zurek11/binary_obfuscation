//
// Created by zurek on 11/18/2019.
//

#ifndef PROJEKT_CYPHER_H
#define PROJEKT_CYPHER_H

#include "err.h"

// Apply XOr encryption with procedural logic.
void applyProceduralXORChyperSmall(void * memptr, unsigned int size, char key);

// Apply XOR cypher operation on a memory area, given your custom key.
void applyXORChyperSmall(void * memptr, unsigned int size, char key);

// Apply XOR cypher operation on a memory area, given your custom multibyte key.
void applyXORChyperLong(void * memptr, unsigned int size, char * key, unsigned int keysize);

// Apply a XOR operation all over the Physical file area. Returns 0 on success.
int applyPhyXORSmallOverSection(char * path, int offset, int size, char key);

// Apply a XOR operation all over the Physical file area. Returns 0 on success.
int applyPhyXORLongOverSection(char * path, int offset, int size, char * key, unsigned int keysize);

// Apply procedural encryption with a single key.
int applyPhyProceduralEncryption(char * path, int offset, int size, char key);

// Prints on screen the CPU instruction.
void showData(void * memptr, unsigned int size);

#endif //PROJEKT_CYPHER_H
