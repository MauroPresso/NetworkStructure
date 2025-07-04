/**
 * @file network_structure_lib.c
 * @brief Desarrollos de funciones para manipulación de datos.
 *
 * Este archivo contiene los desarrollos de funciones para manipular datos.
*/

#include <stdint.h>
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
* @return Segmento de bits extraído. Si las posiciones son inválidas, retorna el valor original.
*/
uint64_t extract_bits_segment64(uint64_t value, uint8_t startBit, uint8_t endBit) 
{
    if(endBit > 63 || startBit > endBit)
    {
        printf("\nError: La posicion del bit del final no puede ser mayor a 63\ny la posicion del bit del inicio no puede ser mayor a la posicion del bit del final.\n");
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
uint8_t countDevices(void)
{
    FILE *pf;
    pf = fopen("D:\\Facultad\\InformaticaII_UTN-FRN\\NetworkStructure\\network_structure.dat","rb");
    if (pf == NULL)
    {
        printf("\n-------------------------------------------------------------");
        printf("\nError 404: Not Found\n");
        printf("-------------------------------------------------------------\n");
        return 0;
    }
    else
    {
        printf("\n-------------------------------------------------------------");
        printf("\nFile opening was OK. Continue with the procedure.\n");
    }
    uint64_t header;
    uint64_t lower_level_devices_count;
    uint8_t total_devices_count;
    total_devices_count = 0;
    while(fread(&header, sizeof(uint64_t), 1, pf) != 0) // Mientras lea un header, sigue en el bucle.
    {
        total_devices_count++; // Cada header que lee, es un device que se debe sumar a la cuenta.
        // Extraer el número de dispositivos de nivel inferior (bits 32-47)
        lower_level_devices_count = extract_bits_segment64(header, 32, 47); // Paso header como primer parámetro porque lo leyó primero.
        // Saltar los IDs de los dispositivos conectados (cada uno son 2 bytes)
        fseek(pf, lower_level_devices_count * sizeof(uint16_t), SEEK_CUR);
    }
    fclose(pf);
    printf("\nFile closing was OK. Continue with the program.\n");
    printf("-------------------------------------------------------------\n");
    return total_devices_count;
}

/**
 * @brief Trabaja con el registro un equipo a eleccion.
 * 
 * @param ID ID del equipo del cual se quiere obtener el registro.
 * 
 * @return devuelve el registro completo de ese equipo en forma de una estructura.
*/
struct Registro getRegister(uint16_t target_id)
{
    FILE *pf;
    pf = fopen("D:\\Facultad\\InformaticaII_UTN-FRN\\NetworkStructure\\network_structure.dat","rb");
    if (pf == NULL)
    {
        printf("\n-------------------------------------------------------------");
        printf("\nError 404: Not Found\n");
        printf("-------------------------------------------------------------\n");
        exit;
    }
    else
    {
        printf("\n-------------------------------------------------------------");
        printf("\nFile opening was OK. Continue with the procedure.\n");
    }
    struct Registro registre;
    uint64_t header;
    uint16_t lower_level_devices_count;
    uint16_t device_id;
    while(fread(&header, sizeof(uint64_t), 1, pf) != 0) // Mientras lea un header, sigue en el bucle.
    {
        device_id = extract_bits_segment64(header, 48, 63);
        lower_level_devices_count = extract_bits_segment64(header, 32, 47);
        if(target_id == device_id) // El dispositivo se encontró.
        {
            registre.header.ID = extract_bits_segment64(header, 48, 63);
            registre.header.Lower_Level_Devices_Count = extract_bits_segment64(header, 32, 47);
            registre.header.Device_Type = extract_bits_segment64(header, 24, 31);
            if(registre.header.Device_Type == 1 || registre.header.Device_Type == 2) // El dispositivo es SENSOR o ACTUADOR
            {
                if(registre.header.Device_Type == 1) // El dispositivo es SENSOR
                {
                    registre.header.Info = extract_bits_segment64(header, 20, 21);
                }
                else // registro.header.Device_Type == 2 -> El dispositivo es ACTUADOR
                {
                    registre.header.Info = extract_bits_segment64(header, 23, 23);
                }
            }
            registre.header.Upper_Level_Device_ID = extract_bits_segment64(header, 0, 15);
            // Terminó de leer el header.
            // Creo el vector dinámico para guardar los IDs.
            registre.LowerIDsVector = (uint16_t*)malloc((lower_level_devices_count) * sizeof(uint16_t));
            // Verificar si malloc tuvo éxito (OBLIGATORIO para el examen)
            if (registre.LowerIDsVector == NULL) 
            {
                printf("Error: No se pudo asignar memoria para LowerIDsVector\n");
                fclose(pf);
                return registre;
            }
            // 2. Leer los IDs de conexiones
            for(uint8_t i = 0; i < lower_level_devices_count; i++) 
            {
                if (fread(&(registre.LowerIDsVector[i]), sizeof(uint16_t), 1, pf) != 1) // Falló la lectura.
                {
                    printf("Error al leer el ID de conexión %u\n", i);
                    free(registre.LowerIDsVector); // Liberar memoria si falla la lectura
                    registre.LowerIDsVector = NULL;
                }
            }
        }
        else
        {
            // Saltar los IDs de los dispositivos conectados (cada uno son 2 bytes)
            fseek(pf, lower_level_devices_count * sizeof(uint16_t), SEEK_CUR);
        }
    }
    fclose(pf);
    printf("\nFile closing was OK. Continue with the program.\n");
    printf("-------------------------------------------------------------\n");
    return registre;
}

/**
 * @brief muestra en consola los ID de todos los equipos de la red.
*/
void showIDs(void)
{
    FILE *pf;
    pf = fopen("D:\\Facultad\\InformaticaII_UTN-FRN\\NetworkStructure\\network_structure.dat","rb");
    if (pf == NULL)
    {
        printf("\n-------------------------------------------------------------");
        printf("\nError 404: Not Found\n");
        printf("-------------------------------------------------------------\n");
        exit;
    }
    else
    {
        printf("\n-------------------------------------------------------------");
        printf("\nFile opening was OK. Continue with the procedure.\n");
    }
    uint64_t header;
    uint16_t device_id;
    int counter = 0;
    printf("\n=== IDs validos de dispositivos ===\n");
    while(fread(&header, sizeof(uint64_t), 1, pf) == 1) 
    {
        // Extraer ID (primeros 16 bits del header)
        device_id = *((uint16_t*)&header); // Alternativa directa
        // Filtrar ID inválido (65535)
        if(device_id != 65535) 
        {
            printf("Dispositivo %d: ID = %u\n", ++counter, device_id);
        }
        // Saltar conexiones (asumiendo 2 bytes por ID)
        uint16_t num_conexiones = *((uint16_t*)&header + 1); // Segundo uint16_t
        fseek(pf, num_conexiones * sizeof(uint16_t), SEEK_CUR);
    }
    if(counter == 0) 
    {
        printf("No se encontraron dispositivos validos.\n");
    }
    fclose(pf);
    printf("\nFile closing was OK. Continue with the program.\n");
    printf("-------------------------------------------------------------\n");
}