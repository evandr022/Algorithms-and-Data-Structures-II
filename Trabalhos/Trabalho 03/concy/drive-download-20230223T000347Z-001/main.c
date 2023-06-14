#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "objects/arvoreB.c"

#define true 1
#define false 0
#define FILE_MEDICAMENTOS "data/medicamentos.csv"
#define FILE_CLIENTES "data/clientes.csv"

node *arvoreMedicamentos = NULL;
node *arvoreClientes = NULL;

#include "objects/Medicamentos.c"
#include "objects/Clientes.c"

#include "config/Config.c"
#include "config/Menu.c"

int main(int argc, char const *argv[])
{
	
	if (argc < 2) {
		return 0;
	}
	else {

		config();

		if (strcmp(argv[1], "--admin") == 0) {
			printf("Usuário Admin\n");
			menuAdmin();
		}
		else if (strcmp(argv[1], "--cliente") == 0) {
			printf("Usuário Cliente\n");
			menuCliente();
		}
		else {
			printf("Argumento inválido: %s\n", argv[1]);
		}
	}

	return 0;
}