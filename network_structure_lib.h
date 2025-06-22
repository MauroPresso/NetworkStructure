/**
 * @file network_structure_lib.h
 * @brief Declaraciones de funciones para manipulación de datos.
 *
 * Este archivo contiene las declaraciones de funciones para manipular datos.
*/
#pragma once
#include <stdint.h>

struct Header
{
    uint16_t Upper_Level_Device_ID;
    uint8_t Info;
    uint8_t Device_Type;
    uint16_t Lower_Level_Devices_Count;
    uint16_t ID;
};

/**
 * @brief Extrae un segmento de bits de un valor de 64 bits.
 * 
 * @param value Valor original.
 * @param startBit Bit inicial del segmento (0-63).
 * @param endBit Bit final del segmento (0-63).
 * @return Segmento extraído como un valor de 64 bits.
*/
uint64_t extract_bits_segment64(uint64_t value, uint8_t startBit, uint8_t endBit);

/**
 * @brief muestra en consola los ID de todos los equipos de la red.
*/
void showIDs(void);

/**
 * @brief Cuenta la cantidad de dispositivos que hay en la red.
 * 
 * @return retorna la cantidad de dispositivos de la red (retorna en una variable, no muestra en consola).
*/
uint8_t countDevices(void);

/**
 * @brief Trabaja con el registro un equipo a eleccion.
 * 
 * @param ID ID del equipo del cual se quiere obtener el registro.
 * 
 * @return devuelve el registro completo de ese equipo en forma de una estructura.
*/
struct Header getRegister(uint16_t ID);
