#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Salva o endereço virtual, físico e instrução no correct.txt
void save_addresses_value(int endereco_virtual, int endereco_fisico, int valor) {

	FILE *file;
	file = fopen("correct2.txt", "a");
	fprintf(file,"Virtual address: %d Physical address: %d Value: %d\n", endereco_virtual, endereco_fisico, valor);
	fclose(file);
}


// Salva a quantidade de arquivos traduzidos no correct.txt
void save_translated_addresses(int translated_addresses) {

    FILE *file;
	file = fopen("correct2.txt", "a");
    fprintf(file, "Number of Translated Addresses  = %d\n", translated_addresses);
    fclose(file);
}


// Salva a quantidade de page faults e a taxa de page faults no correct.txt
void save_page_faults(int page_fault_total) {

    FILE *file;
	file = fopen("correct2.txt", "a");

    fprintf(file, "Page Faults = %d\n", page_fault_total);

    double page_fault_rate = (double)page_fault_total / 1000.0;
    fprintf(file, "Page Fault Rate = %.3f", page_fault_rate);
    fclose(file);
}


void limpa_arquivo() {
    FILE *file;
    file = fopen("correct2.txt", "w");
    fclose(file);
}