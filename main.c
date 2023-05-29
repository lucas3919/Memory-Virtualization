#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils/structs.h"
#include "utils/functions.h"
#include "utils/save_file.h"
#include "utils/fifo.h"
#include "utils/lru.h"

int translated_addresses = 0;
int page_fault_total = 0;
float page_fault_rate= 0.0;

int endereco_fisico = -1;
int frame_substituicao = 0;
int ciclo = 0;

int main (int argc, char *argv[]) {

    // Argumentos da linha de comando do terminal
    char *command_line_file = argv[1];
    char *command_line_table = argv[2];
    char *command_line_tlb = argv[3];

    // Vaiaveis
    int endereco_logico, valor = 0;
    int page_number = 0, offset = 0;
    int frame_atual = 0;

    // String Linha do arquivo addresses.txt
    char linha[100];

    // Arquivos
    FILE *addresses_file;
    FILE *backing_store_file;

    limpa_arquivo();
    check_args(argc);
    
    // Cria o espaço da memória física, cada bloco de página receber um espaço de 8Bits 256 vezes.
    for(int index = 0; index < 256; index++) {
        memoria_fisica[index].pagina = (int8_t*)malloc(sizeof(int8_t) * 256);
    }

    // Tenta abrir o arquivo addresses.txt e trata o erro caso não consigo encontrar o arquivo ou abrir ele
    addresses_file = fopen(command_line_file, "r"); 
    if(check_adresses_file(command_line_file)) {
        return 0;
    }
    
    // Tenta abrir o arquivo BACKING_STORE.txt e trata o erro caso não consigo encontrar o arquivo ou abrir ele
    backing_store_file = fopen("BACKING_STORE.bin", "r");
    if (check_backing_store_file()) {
        return 0;
    }
    fclose(backing_store_file);

    while (fgets(linha, 100, addresses_file) != NULL) {

        /* Pega a linha retirada do addresses.txt e converte a String para um Inteiro
        Referência: https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm*/
        endereco_logico = atoi(linha);

        translated_addresses++;

        /* Faz a operação de shift binário pra esquerda e compara com uma porta AND
        Apagando todos os bits que forem inúteis, mantendo todos os 1 e 0 do necessário 
        Referência: Operating System Concepts, Silberchatz, P-51; Programming Projects - Specific 
        Referência: https://www.geeksforgeeks.org/left-shift-right-shift-operators-c-cpp/
        Referência: https://www.tutorialspoint.com/cprogramming/c_operators.htm              */
        offset = (((1 << 8) - 1) & endereco_logico);
        page_number = (((1 << 8) - 1) & (endereco_logico >> 8));


        /*############################### PAGE FAULT ###############################*/
        if (page_fault_check(page_number)) {

            page_fault_total++;
            backing_store_file = fopen("BACKING_STORE.bin", "rb");

            /* Move o ponteiro para o BACKING_STORE.bin na posição específicada pelo número da página 
            Para escrevermos na memória física a instrução dessa posição do BACKING_STORE.bin
            Referência: Operating System Concepts, Silberchatz, P-53; Programming Projects - Handling Page Faults
            Referência: https://acervolima.com/fseek-em-c-c-com-exemplo/                   */ 
            fseek(backing_store_file, page_number * 256, 0);

            if(!(tabela_pagina_cheia(frame_atual))) {

                /* Armazena na memória física, naquele frame atual e seu respectivo numero de página,
                A Instrução do arquivo BACKING_STORE.bin. Usando o fread() dentro da função. (veja o functions.h)
                O qual acima na função, fseek(), teve seu ponteiro mudado para apontar para a posição que queríamos.
                1 Byte (8Bits), 256 vezes. Isso no caso é o tamanho que temos da página do arquivo BACKING_STORE.bin
                Referência: Operating System Concepts, Silberchatz, P-53; Programming Projects - Handling Page Faults 
                Referência: https://terminalroot.com.br/2014/10/exemplos-de-funcoes-fread-fwrite-remove.html                                      */
                coloca_instrucao_memoria_fisica(frame_atual, backing_store_file);

                memoria_fisica[frame_atual].page_number = page_number;
                atualiza_tabela_pagina(page_number, frame_atual, ciclo);
                frame_atual++;
            }

            else {
                /*############################### FIFO ###############################*/
                if(!(strcmp(command_line_table, "fifo"))) {
                    fifo(backing_store_file, frame_substituicao, page_number, ciclo);
                    frame_substituicao++;

                    // Reseta o fifo quando estiver cheio
                    if (frame_substituicao == 128) {
                        frame_substituicao = 0;
                    }
                }

                /*################################ LRU ################################*/
                else if(!(strcmp(command_line_table, "lru"))) {
                    lru(backing_store_file, page_number, ciclo);
                }
            }
            
            fclose(backing_store_file);
        }

        /*############################### SEM PAGE FAULT ###############################*/
        else {
            tabela_pagina[page_number].quando_usado = ciclo;
        }

        cria_endereco_fisico(page_number, offset, &endereco_fisico);
        valor = memoria_fisica[tabela_pagina[page_number].numero_frame].pagina[offset];
        save_addresses_value(endereco_logico, endereco_fisico, valor);
        ciclo++;
    }

    save_translated_addresses(translated_addresses);
    save_page_faults(page_fault_total);
    fclose(addresses_file);

    return 0;
}