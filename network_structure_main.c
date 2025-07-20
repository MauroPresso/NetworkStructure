/**
 * @file network_structure_main.c
 * @brief Programa donde se pone a prueba el funcionamiento de las funciones del inciso nro 1.
 *
 * Este archivo contiene el programa donde se pone a prueba el funcionamiento de las funciones del inciso nro 1.
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
    do{
        printf("\nIngrese el ID del equipo (1 a 10):\t");
        scanf("%u" , &targetID);
        if(targetID < 1 || targetID > 10)
        {
            printf("\nID ingresado erroneo. Intente nuevamente.");
        }
    }while(targetID < 1 || targetID > 10);
    struct Registro registro;
    registro = getRegister(targetID);
    printf("\n---------------------------------------------\n");
    printf("Registro completo del dispositivo nro %u\n\n", targetID);
    printf("- ID: %u\n", registro.header.ID);
    if(registro.header.Device_Type == 0)
    {
        printf("- Tipo de dispositivo: CPU\n");
    }
    else if(registro.header.Device_Type == 1)
    {
        printf("- Tipo de dispositivo: SENSOR ");
        if(registro.header.Info == 0)
        {
            printf("de CAUDAL\n");
        }
        else if(registro.header.Info == 1)
        {
            printf("de TEMPERATURA\n");
        }
        else if(registro.header.Info == 2)
        {
            printf("de PRESION\n");
        }
        else if(registro.header.Info == 3)
        {
            printf("de NIVEL\n");
        }
    }
    else if(registro.header.Device_Type == 2)
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
    else if(registro.header.Device_Type == 3)
    {
        printf("- Tipo de dispositivo: CONCENTRADOR\n");   
    }
    // ID del padre.
    if(registro.header.Upper_Level_Device_ID == 65535)
    {
        printf("- ID del dispositivo padre: ID invalido\n");
    }
    else
    {
        printf("- ID del dispositivo padre: %u\n", registro.header.Upper_Level_Device_ID);
    }
    printf("- Cantidad de dispositivos hijos: %u\n", registro.header.Lower_Level_Devices_Count);
    if(registro.header.Lower_Level_Devices_Count != 0)
    {
        for(uint16_t i = 0 ; i < (registro.header.Lower_Level_Devices_Count); i++)
        {
            printf("\n\t- ID del hijo nro %u:\t%u", (i+1), registro.LowerIDsVector[i]);
        }
        printf("\n---------------------------------------------");
        free(registro.LowerIDsVector);
        registro.LowerIDsVector = NULL;
    }
    printf("\n---------------------------------------------\n");
    printf("\n-------------------------------------------------------------\n");
    printf("FIN DEL PROGRAMA :D");
    printf("\n-------------------------------------------------------------\n");
    return 0;
}
