/**
 * @file network_structure_main.c
 * @brief Programa principal.
 *
 * Este archivo contiene el programa principal.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "network_structure_lib.h"

int main()
{
    uint8_t totalDeDispositivos;
    totalDeDispositivos = countDevices();
    printf("\nTotal de dispositivos en la red: %u", totalDeDispositivos);
    printf("\n-------------------------------------------------------------\n\n");

    return 0;
}
