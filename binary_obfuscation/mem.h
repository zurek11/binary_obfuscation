//
// Created by zurek on 11/18/2019.
//

#ifndef PROJEKT_MEM_H
#define PROJEKT_MEM_H

#include "err.h"

// Allows a portion of the memory to be modified.
int unprotectMemory(void * mem, long unsigned int size);


#endif //PROJEKT_MEM_H
