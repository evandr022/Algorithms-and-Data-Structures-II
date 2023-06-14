#define true 1
#define false 0

void menuAdmin() {

	int exit = false;
	int opcao;

	while(!exit) {

		printf("\n");
		printf("1 - Listar medicamentos\n");
		printf("2 - Listar clientes\n");
		printf("10 - Sair\n");

		scanf("%d", &opcao);

		if (opcao == 1) {
			listaMedicamentos(arvoreMedicamentos, 0);
		}
		else if (opcao == 2) {
			listaClientes(arvoreClientes, 0);
		}
		else if (opcao == 10) {
			exit = true;
		}
	}
}

void menuCliente() {

	int exit = false;
	int opcao;

	while(!exit) {

		printf("\n");
		printf("1 - Listar medicamentos\n");
		printf("2 - Cadastro\n");
		printf("3 - Login\n");
		printf("10 - Sair\n");

		scanf("%d", &opcao);

		if (opcao == 1) {
			listaMedicamentos(arvoreMedicamentos, 0);
		}
		else if (opcao == 2) {
			cadastroCliente();
		}
		else if (opcao == 10) {
			exit = true;
		}
	}
}