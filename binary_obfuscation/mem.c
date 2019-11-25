//
// Created by zurek on 11/18/2019.
//

#include "mem.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int unprotectMemory(void * mem, long unsigned int size) {
    unsigned int old = 0;

    if (VirtualProtect(mem, size, PAGE_EXECUTE_READWRITE, (PDWORD) &old) == FALSE) {
        return FAILURE;
    }

    return SUCCESS;
}
