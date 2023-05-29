void fifo(FILE* backing_store_file, int frame_substituicao, int page_number_fifo, int ciclo) {
    
    for (int page_number = 0; page_number < 256; page_number++) {
        if (!(page_fault_check(page_number))) {
            if (frame_number_same_as_substitute(frame_substituicao, page_number)) { 
                fifo_change_page_table(backing_store_file, page_number_fifo, page_number, frame_substituicao, ciclo);
                break;
            }
        }
    }
}


int frame_number_same_as_substitute(int frame_substituicao, int page_number) {
    if (tabela_pagina[page_number].numero_frame == frame_substituicao) {
        return 1;
    }

    return 0;
}


void fifo_change_page_table(FILE* backing_store_file, int page_number_fifo, int page_number, int frame_substituicao, int ciclo) {
    tabela_pagina[page_number].bit_validacao = false;
    fread(memoria_fisica[frame_substituicao].pagina, 1, 256, backing_store_file);
    atualiza_tabela_pagina(page_number_fifo, frame_substituicao, ciclo);
}