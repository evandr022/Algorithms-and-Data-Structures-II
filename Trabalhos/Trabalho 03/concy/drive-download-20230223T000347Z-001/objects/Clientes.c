typedef struct cliente {
	int id;
	char nome[20];
	char email[20];
	char senha[20];
} Cliente;

void listaClientes(node *no, int nivel) {
	if (no != NULL) {
	  	listaClientes(no->esquerda, nivel + 1);

		Cliente *c = no->dados;
	  	printf(
	  		"%d - %s, %s, %s\n",
	  		c->id,
	  		c->nome,
	  		c->email,
	  		c->senha
	 	);
	 	free(c);

	  	listaClientes(no->direita, nivel + 1);
	} 
}

void insereCliente(Cliente * c) {
	inserir(&arvoreClientes, c->id, c);
}

void cadastroCliente() {
	char tmp;
	char nome[20], email[20], senha[20];

	scanf("%c", &tmp);
	
	printf("Insira o nome\n");
	scanf("%[^\n]", nome);
	scanf("%c", &tmp);

	printf("Insira o email\n");
	scanf("%[^\n]", email);
	scanf("%c", &tmp);

	printf("Insira a senha\n");
	scanf("%[^\n]", senha);

	int id;

	node * no = maior(arvoreClientes);

	if (no != NULL) {
		id = no->info +1;
	}
	else {
		id = 1;
	}

	Cliente *c = malloc(sizeof(Cliente));
	c->id = id;
	strcpy(c->nome, nome);
	strcpy(c->email, email);
	strcpy(c->senha, senha);
	
	insereCliente(c);

	FILE *file = fopen(FILE_CLIENTES, "a");
	if (file == NULL) {
		perror(FILE_CLIENTES);
	}
	fprintf(file, "%d;%s;%s;%s\n", c->id, c->nome, c->email, c->senha);
	fclose(file);
}