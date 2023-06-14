

void configMedicamentos() {

	FILE *file = fopen(FILE_MEDICAMENTOS, "r");

	if (file == NULL) {
		perror(FILE_MEDICAMENTOS);
	}

	char linha[100];
	
	while(fgets(linha, sizeof(linha), file)) {
		Medicamento *m = malloc(sizeof(Medicamento));
		m->id = atoi(strtok(linha, ";"));
		strcpy(m->nome, strtok(NULL, ";"));
		m->preco = atof(strtok(NULL, "\n"));
		inserir(&arvoreMedicamentos, m->id, m);
	}

	fclose(file);
}

void configClientes() {

	FILE *file = fopen(FILE_CLIENTES, "r");

	if (file == NULL) {
		perror(FILE_CLIENTES);
	}

	char linha[100];
	
	while(fgets(linha, sizeof(linha), file)) {
		Cliente *c = malloc(sizeof(Cliente));
		c->id = atoi(strtok(linha, ";"));
		strcpy(c->nome, strtok(NULL, ";"));
		strcpy(c->email, strtok(NULL, ";"));
		strcpy(c->senha, strtok(NULL, "\n"));
		insereCliente(c);
	}

	fclose(file);
}

void config() {
	configMedicamentos();
	configClientes();
}