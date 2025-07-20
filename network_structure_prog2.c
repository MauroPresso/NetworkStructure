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
        uint16_t currentID;
        do{
            printf("\nIngrese el ID del equipo (1 a 10):\t");
            scanf("%u" , &userTargetID);
            if(userTargetID < 1 || userTargetID > 10)
            {
                printf("\nID ingresado erroneo. Intente nuevamente.");
            }
        }while(userTargetID < 1 || userTargetID > 10);
        uint8_t path_devices_count;
        path_devices_count = 1;
        currentID = userTargetID;
        // Bucle para contar los dispositivos de la conexion.
        while(path_devices_count <= 10) 
        {
            // 1) Buscamos en el array el registro cuyo header.ID == currentID
            int idx = -1;
            for (size_t i = 0; i < devices_count; i++) 
            {
                if (network[i].header.ID == currentID)
                {
                    idx = (int)i;
                    break;
                }
            }
            if (idx < 0) 
            {
                // No encontramos ese ID en la red: terminamos
                break;
            }
            // 2) Leemos el Upper_Level_Device_ID de ese registro
            uint16_t parentID = network[idx].header.Upper_Level_Device_ID;
            // 3) Si es inválido (65535), ya llegamos a la raíz
            if (parentID == 65535) 
            {
                break;
            }
            // 4) Subimos un nivel y aumentamos el contador
            currentID = parentID;
            path_devices_count++;
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
        printf("\n-------------------------------------------------------------\n");
        printf("\n-------------------------------------------------------------\n");
        printf("\nCantidad de dispositivos en la secuencia de conexion:\t%u\n", path_devices_count);
        // Cargando el vector secuencia.
        currentID = userTargetID;
        uint16_t* path_vector;
        path_vector = (uint16_t*)malloc((path_devices_count)*(sizeof(uint16_t)));
        for(size_t k = 0; k < path_devices_count; k++)
        {
            path_vector[k] = currentID;
            // 1) Buscamos en el array el registro cuyo header.ID == currentID
            int idx = -1;
            for (size_t i = 0; i < devices_count; i++) 
            {
                if (network[i].header.ID == currentID)
                {
                    idx = (int)i;
                    break;
                }
            }
            if (idx < 0) 
            {
                // No encontramos ese ID en la red: terminamos
                break;
            }
            // 2) Leemos el Upper_Level_Device_ID de ese registro
            uint16_t parentID = network[idx].header.Upper_Level_Device_ID;
            // 3) Si es inválido (65535), ya llegamos a la raíz
            if (parentID == 65535) 
            {
                break;
            }
            // 4) Subimos un nivel y aumentamos el contador
            currentID = parentID;
        }
        // Imprimiendo el vector secuencia.
        printf("\n-------------------------------------------------------------------------------\n");
        printf("Secuencia de conexion del ID seleccionado por el usuario (ID = %u):\n", userTargetID);
        for(int d = ((int)(path_devices_count) - 1); d >= 0; --d)
        {
            if(d != 0)
            {
                printf("ID %u ->\t", path_vector[d]);
            }
            else
            {
                printf("ID %u", path_vector[d]);
            }
        }        
        printf("\n-------------------------------------------------------------------------------\n");
        printf("\n-------------------------------------------------------------");
        free(network);
        printf("\nSe libero la memoria dinamica");
        network = NULL;
        printf("\nSe libero el puntero al vector de registros");
        free(path_vector);
        printf("\nSe libero la memoria dinamica");
        path_vector = NULL;
        printf("\nSe libero el puntero al vector de la secuencia de conexion");
        printf("\n-------------------------------------------------------------\n");
    }
    printf("\nFIN DEL PROGRAMA :D");
    return 0;
}