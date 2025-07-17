/**
 * @file network_structure_prog.c
 * @brief Programa donde se realiza el inciso nro 2.
 *
 * Este archivo contiene el programa donde se realiza el inciso nro 2.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "network_structure_lib.h"

int main()
{
    struct Registro* network;
    uint8_t devices_count;
    devices_count = countDevices();
    if(devices_count != 0)
    {
        network = (struct Registro*)malloc((devices_count)*(sizeof(struct Registro)));
        // Cargando vector.
        uint16_t id;
        id = 1; // El 1er ID es igual a 1.
        for(uint8_t c = 0; c < (devices_count); c++)
        {
            network[c] = getRegister(id); // Cargo el registro en la posicion correspondiente. En la 1er vuelta, ID = 1.
            id++; // Incremento el ID para continuar cargando los siguientes registros.
        }
        // Imprimiendo el vector.
        printf("\n\n\n-------------------------------------------------------------\n");
        printf("Registros de TODOS los equipos de la red\n");
        for(uint8_t c = 0; c < (devices_count); c++)
        {
            printf("\n---------------------------------------------\n");
            printf("Registro completo del dispositivo nro %u\n\n", (c+1));
            printf("- ID: %u\n", network[c].header.ID);
            if(network[c].header.Device_Type == 0)
            {
                printf("- Tipo de dispositivo: CPU\n");
            }
            if(network[c].header.Device_Type == 1)
            {
                printf("- Tipo de dispositivo: SENSOR ");
                if(network[c].header.Info == 0)
                {
                    printf("de CAUDAL\n");
                }
                if(network[c].header.Info == 1)
                {
                    printf("de TEMPERATURA\n");
                }
                if(network[c].header.Info == 2)
                {
                    printf("de PRESION\n");
                }
                if(network[c].header.Info == 3)
                {
                    printf("de NIVEL\n");
                }
            }
            if(network[c].header.Device_Type == 2)
            {
                printf("- Tipo de dispositivo: ACTUADOR ");
                if(network[c].header.Info == 0)
                {
                    printf("(VALVULA)\n");
                }
                if(network[c].header.Info == 1)
                {
                    printf("(MOTOR)\n");
                }
            }
            if(network[c].header.Device_Type == 3)
            {
                printf("- Tipo de dispositivo: CONCENTRADOR\n");   
            }
            printf("- ID del dispositivo padre: %u\n", network[c].header.Upper_Level_Device_ID);
            printf("- Cantidad de dispositivos hijos: %u\n", network[c].header.Lower_Level_Devices_Count);
            if(network[c].header.Lower_Level_Devices_Count != 0)
            {
                for(uint16_t i = 0 ; i < (network[c].header.Lower_Level_Devices_Count); i++)
                {
                    printf("\n\t- ID del hijo nro %u:\t%u", (i+1), network[c].LowerIDsVector[i]);
                }
                printf("\n---------------------------------------------");
                free(network[c].LowerIDsVector);
                printf("\nSe libero la memoria dinamica");
                network[c].LowerIDsVector = NULL;
                printf("\nSe libero el puntero al vector de IDs");
            }
            printf("\n---------------------------------------------\n");
        }
        printf("\n-------------------------------------------------------------");
        free(network);
        printf("\nSe libero la memoria dinamica");
        network = NULL;
        printf("\nSe libero el puntero al vector de registros");
        printf("\n-------------------------------------------------------------\n");
    }
    printf("\nFIN DEL PROGRAMA :D");
    return 0;
}