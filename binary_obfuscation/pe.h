//
// Created by zurek on 11/18/2019.
//

#ifndef PROJEKT_PE_H
#define PROJEKT_PE_H

#include "err.h"

// Locate a section in a physical file.
int locatePhySection(char * path, char * name, int * offset, int * size);

// Locate a section in the virtual memory.
int locateVirSection(const char * name, void ** addr, int * size);

#endif //PROJEKT_PE_H
