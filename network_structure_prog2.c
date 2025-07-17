/**
 * @file network_structure_prog.c
 * @brief Programa donde se realiza DEFINITIVAMENTE el inciso nro 2.
 *
 * Este archivo contiene el programa donde se realiza DEFINITIVAMENTE el inciso nro 2.
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
        // Seleccionando ID.
        uint16_t userTargetID;
        uint16_t newTargetID;
        printf("\n\n\nIngrese el ID del equipo:\t");
        scanf("%u" , &userTargetID);
        do{
            printf("\nIngrese el ID del equipo:\t");
            scanf("%u" , &userTargetID);
        }while(userTargetID < 1 || userTargetID > 10);
        uint8_t path_devices_count;
        path_devices_count = 1;
        newTargetID = userTargetID;
        // Bucle para contar los dispositivos de la conexion.
        while(network[newTargetID].header.Upper_Level_Device_ID != 65535) // 65535 es un ID invalido.
        {
            path_devices_count++;
            newTargetID = network[newTargetID].header.Upper_Level_Device_ID;
        }
        printf("\nCantidad de dispositivos en la secuencia de conexion:\t%u\n", path_devices_count);

        // Libero los vectores de IDs de los registros.
        for(uint8_t c = 0; c < (devices_count); c++) 
        {
            if(network[c].header.Lower_Level_Devices_Count != 0)
            {
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