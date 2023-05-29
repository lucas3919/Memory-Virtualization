#ifndef  STRUCTS_H
#define  STRUCTS_H

#include <stdint.h>

typedef struct 
{
    int numero_frame;
    bool bit_validacao;
    int quando_usado;
} Tabela_pagina;


typedef struct 
{
    int8_t *pagina;
    int page_number;
} Memoria_fisica;

#endif