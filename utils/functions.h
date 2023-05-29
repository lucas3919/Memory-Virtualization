#include "structs.h"


/*############################### CHECK ARGS ###############################*/
int check_args(int argc);


/*############################### PAGE TABLE ###############################*/
int page_fault_check(int page_number);
int tabela_pagina_cheia(int frame_atual);
void coloca_instrucao_memoria_fisica(int frame_atual, FILE* backing_store_file);
void atualiza_tabela_pagina(int page_number, int frame_atual, int ciclo);
void cria_endereco_fisico(int page_number, int offset, int *endereco_fisico);


/*################################# FIFO ##################################*/
void fifo(FILE* backing_store_file, int frame_substituicao, int page_number_fifo, int ciclo);
int frame_number_same_as_substitute(int frame_substituicao, int index);
void fifo_change_page_table(FILE* backing_store_file, int page_number_fifo, int page_number, int frame_substituicao, int ciclo);


/*################################# LRU ##################################*/
void lru(FILE* backing_store_file, int page_number_lru, int ciclo);
int tempo_menor_que_ciclo(int page_number, int ciclo);
void lru_change_table(FILE* backing_store_file, int frame_substituicao, int page_number_lru, int ciclo, int page_number_index);


/*################################ FILES ################################*/
int check_adresses_file(char* file);
int check_backing_store_file();
void save_addresses_value(int endereco_virtual, int endereco_fisico, int valor);
void save_translated_addresses(int translated_addresses);
void save_page_faults(int page_fault_total);
void limpa_arquivo();


/*############################### STRUCTS ###############################*/
Memoria_fisica memoria_fisica[256 * 128];
Tabela_pagina tabela_pagina[256];


/*############################### FUNCTIONS ###############################*/
int check_args(int argc) {
    if(argc < 3) {
        printf("ERROR! YOU HAVE NOT GIVEN ENOUGH ARGUMENTS! PLEASE ENTER 4 ARGUMENTS.");
        return 0;
    }

    if (argc > 4) {
        printf("ERROR! YOU HAVE GIVEN MORE ARGUMENTS THAN NECESSARY! PLEASE ENTER 4 ARGUMENTS.");
        return 0;
    }
}


int check_adresses_file(char* file) {
    FILE * addresses_file;
    addresses_file = fopen(file, "r");

    if(addresses_file == NULL) {
        printf("ERROR! ADDRESS FILE COULD NOT BE FOUND OR COULD NOT BE OPENED");
        fclose(addresses_file);
        return 1;
    }

    return 0;
}


int check_backing_store_file() {
    FILE * backing_store_file;
    backing_store_file = fopen("BACKING_STORE.bin", "r");

    if(backing_store_file == NULL) {
        printf("ERROR! BACKING_STORE FILE COULD NOT BE FOUND OR COULD NOT BE OPENED");
        fclose(backing_store_file);
        return 1;
    }
    
    return 0;
}


int page_fault_check(int page_number) {
    if (tabela_pagina[page_number].bit_validacao == false) {
        return 1;
    }

    return 0;
}


int tabela_pagina_cheia(int frame_atual) {

    if(frame_atual < 128) {
        return 0;
    }

    return 1;
}


void coloca_instrucao_memoria_fisica(int frame_atual, FILE* backing_store_file) {
    fread(memoria_fisica[frame_atual].pagina, 1, 256, backing_store_file);
}


void atualiza_tabela_pagina(int page_number, int frame_atual, int ciclo) {
    tabela_pagina[page_number].numero_frame = frame_atual;
    tabela_pagina[page_number].bit_validacao = true;
    tabela_pagina[page_number].quando_usado = ciclo;
}


void cria_endereco_fisico(int page_number, int offset, int *endereco_fisico) {
    *endereco_fisico = tabela_pagina[page_number].numero_frame;
    *endereco_fisico = (((*endereco_fisico) * 256) + offset);
}