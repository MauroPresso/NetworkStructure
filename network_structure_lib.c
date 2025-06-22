/**
 * @file network_structure_lib.c
 * @brief Desarrollos de funciones para manipulación de datos.
 *
 * Este archivo contiene los desarrollos de funciones para manipular datos.
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "network_structure_lib.h"

/**
* @brief Extrae un segmento de bits de un valor de 64 bits.
* 
* Devuelve un segmento de bits definido por las posiciones startBit y endBit.
* 
* @param value Valor original.
* @param startBit Posición inicial (0-63).
* @param endBit Posición final (0-63).
* @return Segmento de bits extraído. Si las posiciones son inválidas, retorna 0.
*/
uint64_t extract_bits_segment64(uint64_t value, uint8_t startBit, uint8_t endBit) 
{
    if(endBit > 63 || startBit > endBit)
    {
        printf("\nError: La posicion del bit del final no puede ser mayor a 63 \ny la posicion del bit del inicio no puede ser mayor a la posicion del bit del final.\n");
        return value; // Retorna el valor original.
    }
    else
    {
        if(startBit <= endBit) // Si startBit = endBit, solo me extrae 1 bit.
        {
            uint64_t left;
            left = ((sizeof(uint64_t)*8) - 1) - endBit;
            uint64_t segment;
            segment = value << left;
            uint64_t aux;
            aux = segment >> (left + startBit);
            segment = aux;
            return segment;
        }
    }
}

/**
 * @brief Cuenta la cantidad de dispositivos que hay en la red.
 * 
 * @return retorna la cantidad de dispositivos de la red (retorna en una variable, no muestra en consola).
*/
uint8_t count_Devices(void)
{
    uint8_t cant;
    
    
    return cant;
}

/**
 * @brief Trabaja con el registro un equipo a eleccion.
 * 
 * @param ID ID del equipo del cual se quiere obtener el registro.
 * 
 * @return devuelve el registro completo de ese equipo en forma de una estructura.
*/
struct Register get_Register(uint16_t ID)
{
    struct Register registro;
    registro.header.ID = extract_bits_segment64(registro.header.ID, 48, 63);
    registro.header.Lower_Level_Devices_Count = extract_bits_segment64(registro.header.Lower_Level_Devices_Count, 32, 47);
    registro.header.Device_Type = extract_bits_segment64(registro.header.Device_Type, 24, 31);
    if(registro.header.Device_Type == 1 || registro.header.Device_Type == 2) // El dispositivo es SENSOR o ACTUADOR
    {
        if(registro.header.Device_Type == 1) // El dispositivo es SENSOR
        {
            registro.header.Info = extract_bits_segment64(registro.header.Info, 20, 21);
        }
        else // registro.header.Device_Type == 2 -> El dispositivo es ACTUADOR
        {
            registro.header.Info = extract_bits_segment64(registro.header.Info, 23, 23);
        }
    }
    registro.header.Upper_Level_Device_ID = extract_bits_segment64(registro.header.Upper_Level_Device_ID, 0, 15);
    return registro;
}