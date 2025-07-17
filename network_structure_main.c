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
    printf("\n-------------------------------------------------------------");
    printf("\nTotal de dispositivos en la red: %u", totalDeDispositivos);
    printf("\n-------------------------------------------------------------\n");
    showIDs();
    printf("\n-------------------------------------------------------------\n");
    uint16_t targetID;
    printf("\nIngrese el ID del dispositivo del cual desee obtener el registro completo:\t");
    scanf("%u" , &targetID);
    struct Registro registro;
    registro = getRegister(targetID);
    printf("\n---------------------------------------------\n");
    printf("Registro completo del dispositivo nro %u\n\n", targetID);
    printf("- ID: %u\n", registro.header.ID);
    /*printf("- Tipo de Dispositivo: %u\n", registro.header.Device_Type);
    printf("- Info de Dispositivo: %u\n", registro.header.Info);*/ 
    if(registro.header.Device_Type == 0)
    {
        printf("- Tipo de dispositivo: CPU\n");
    }
    if(registro.header.Device_Type == 1)
    {
        printf("- Tipo de dispositivo: SENSOR ");
        if(registro.header.Info == 0)
        {
            printf("de CAUDAL\n");
        }
        if(registro.header.Info == 1)
        {
            printf("de TEMPERATURA\n");
        }
        if(registro.header.Info == 2)
        {
            printf("de PRESION\n");
        }
        if(registro.header.Info == 3)
        {
            printf("de NIVEL\n");
        }
    }
    if(registro.header.Device_Type == 2)
    {
        printf("- Tipo de dispositivo: ACTUADOR ");
        if(registro.header.Info == 0)
        {
            printf("(VALVULA)\n");
        }
        if(registro.header.Info == 1)
        {
            printf("(MOTOR)\n");
        }
    }
    if(registro.header.Device_Type == 3)
    {
        printf("- Tipo de dispositivo: CONCENTRADOR\n");   
    }
    printf("- ID del dispositivo padre: %u\n", registro.header.Upper_Level_Device_ID);
    printf("- Cantidad de dispositivos hijos: %u\n", registro.header.Lower_Level_Devices_Count);
    if(registro.header.Lower_Level_Devices_Count != 0)
    {
        for(uint16_t i = 0 ; i < (registro.header.Lower_Level_Devices_Count); i++)
        {
            printf("\n\t- ID del hijo nro %u:\t%u", (i+1), registro.LowerIDsVector[i]);
        }
        printf("\n---------------------------------------------");
        free(registro.LowerIDsVector);
        printf("\nSe libero la memoria dinamica");
        registro.LowerIDsVector = NULL;
        printf("\nSe libero el puntero al vector de IDs");
    }
    printf("\n---------------------------------------------\n");
    printf("\n-------------------------------------------------------------\n");
    printf("FIN DEL PROGRAMA :D");
    printf("\n-------------------------------------------------------------\n");
    return 0;
}
