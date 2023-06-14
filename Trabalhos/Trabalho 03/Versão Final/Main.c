/*Evandro Salvador MArinho da Silva - 22052988
Link: https://youtu.be/zYogs2TGUZg*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Login.h"
#include "arvoreMultiway.h"
#include "arvoreMultiway_02.h"

#define MAX_STR_LEN 256
#define FILENAME_01 "Precos.txt"

int main(){
    No *raiz = NULL;
    FILE *file = fopen(FILENAME_01, "r");

    char line[MAX_STR_LEN];
    char *strg[50];
    int count = 0;

    if (file == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    int ordem = 0;

    while (fgets(line, MAX_STR_LEN, file) && count < 50){
        char *token = strtok(line, ";");
        while (token != NULL){
            Produto *p = (Produto *)malloc(sizeof(Produto));

            strcpy(p->nomeProduto, strdup(token));
            strg[count] = strdup(token);
            token = strtok(NULL, ";");
            count++;

            if (token == NULL){
                printf("Arquivo Acabou\n\n");
                break;
            }
            strcpy(p->valorProduto, strdup(token));
            insereMultiway(&raiz, ordem, p);
            ordem++;
            strg[count] = strdup(token);
            token = strtok(NULL, ";");
            count++;
        }
    }
    fclose(file);

    int opcao = 0;
    int remedio;
    load_users();
    No_02 *raiz_02 = NULL;
    Produto *f = (Produto *)malloc(sizeof(Produto));

    while(opcao != 3){
        printf("1 - Cadastrar\n");
        printf("2 - Login\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            register_user();
            break;
        case 2:
            login();
            if(login()==1){
                do{
                    printf("\nWelcome, %s!\n", users[num_users - 1].name);
                    printf("1 - Comprar\n");
                    printf("2 - Relatorio\n");
                    printf("3 - Sair\n");
                    printf("Opcao: \n");
                    scanf("%d", &opcao);
                switch (opcao){
                case 1:
                    printf("Voce deseja comprar algum remedio?\n");
                    printf("1 - Sim\n");
                    printf("2 - Nao\n");
                    scanf("%d", &opcao);

                        while (opcao != 2) {
                            printf("Qual remedio voce deseja comprar?\n");
                            imprimeArvore(raiz, 0);
                            scanf("%d", &remedio);
                            insereMultiway_02(&raiz_02, remedio, f);
                            printf("Voce deseja comprar outro remedio?\n");
                            printf("1 - Sim\n");
                            printf("2 - Nao\n");
                            scanf("%d", &opcao);
                        }
                        break;
                    case 2:
                        printf("1 - Compras\n");
                        printf("2 - Usuarios\n");
                        printf("3 - Sair\n");
                        scanf("%d", &opcao);
                        switch (opcao){
                        case 1:
                            printf("Relatorio de compras:\n");
                            printf("Lista de compras do dia:\n");
                            imprimeArvore_02(raiz_02, 0);
                            break;
                        case 2:
                            print_users();
                            break;
                        case 3:
                            break;
                        default:
                            break;
                        }
                        break;
                    case 3:
                        printf("Saindo...\n");
                        break;
                    default:
                        printf("Opcao invalida!\n");
                        break;
                    }
                } while (opcao != 3);
                    break;
            }
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
        free(raiz_02);
    }
}
