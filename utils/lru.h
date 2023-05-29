void lru(FILE* backing_store_file, int page_number_lru, int ciclo) {
    int page_number_index = 0;
    int tempo_atual = ciclo;
    int frame = 0;

    for (int page_number = 0; page_number < 256; page_number++) {
        if (!(page_fault_check(page_number))) {
            if(tempo_menor_que_ciclo(page_number, tempo_atual)) {
                tempo_atual = tabela_pagina[page_number].quando_usado;
                page_number_index = page_number;
            }
        }
    }

    lru_change_table(backing_store_file, frame, page_number_lru, ciclo, page_number_index);
}


int tempo_menor_que_ciclo(int page_number, int ciclo) {
    if(tabela_pagina[page_number].quando_usado < ciclo) {
        return 1;
    }

    return 0;
}


void lru_change_table(FILE* backing_store_file, int frame, int page_number_lru, int ciclo, int page_number_index) {
    frame = tabela_pagina[page_number_index].numero_frame;
    tabela_pagina[page_number_index].bit_validacao = false;
    
    coloca_instrucao_memoria_fisica(frame, backing_store_file);
    atualiza_tabela_pagina(page_number_lru, frame, ciclo);
}