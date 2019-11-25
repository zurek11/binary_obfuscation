//
// Created by zurek on 11/18/2019.
//

#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "pe.h"

int locatePhySection(char * path, char * name, int * offset, int * size) {
    int i;
    int j;

    FILE * fd;

    char found = 1;     // Section found?

    IMAGE_DOS_HEADER dosh;
    IMAGE_NT_HEADERS nth;
    IMAGE_SECTION_HEADER sech;

    fd = fopen(path, "rb");

    if (!fd) {
        return FAILURE;
    }

    //
    // Extracts the header from the binary file.
    // It assumes no fail; looot of checks can be done here.
    //
    fread(&dosh, 1, sizeof(IMAGE_DOS_HEADER), fd);
    fseek(fd, dosh.e_lfanew, SEEK_SET);
    fread(&nth, 1, sizeof(IMAGE_NT_HEADERS), fd);

    //
    // Search for the target section header.
    //
    for (i = 0; i < nth.FileHeader.NumberOfSections; i++) {
        fread(&sech, 1, sizeof(IMAGE_SECTION_HEADER), fd);

        for (j = 0; j < 8; j++) {
            if (sech.Name[j] != 0 && sech.Name[j] != name[j]) {
                found = 0;
                break;
            }
        }

        //
        // Is the section we're looking for?
        //
        if (found) {
            *offset = sech.PointerToRawData;
            *size = sech.SizeOfRawData;

            break;
        }

        found = 1;
    }

    fclose(fd);

    if (!found) {
        return FAILURE;
    }

    return SUCCESS;
}

int locateVirSection(const char * name, void ** addr, int * size)
{
    int i;
    int j;
    int nope = 0;

    // Get the handle of this module.
    HANDLE h = GetModuleHandle(NULL);

    IMAGE_DOS_HEADER * dosh;
    IMAGE_NT_HEADERS * nth;
    IMAGE_SECTION_HEADER * currSect;

    if (!h) {
        return FAILURE;
    }

    dosh = (IMAGE_DOS_HEADER *)h;
    nth  = (IMAGE_NT_HEADERS *)((char *)dosh + dosh->e_lfanew);
    currSect = (IMAGE_SECTION_HEADER *)((char *)nth + sizeof(IMAGE_NT_HEADERS));

    for (i = 0; i < nth->FileHeader.NumberOfSections; i++) {
        nope = 0;

        for (j = 0; j < 8; j++) {
            if (currSect->Name[j] != 0 && currSect->Name[j] != name[j]) {
                nope = 1;
                currSect++;
                break;
            }
        }

        // Found!
        if (!nope) {
            break;
        }
    }

    // Section header not found.
    if (nope) {
        return FAILURE;
    }

    *addr = ((char *)h + currSect->VirtualAddress);
    *size = currSect->SizeOfRawData;
    return SUCCESS;
}
