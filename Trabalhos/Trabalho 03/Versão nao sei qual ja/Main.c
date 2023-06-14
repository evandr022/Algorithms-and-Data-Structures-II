#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Login.h"

int main(){
    int opcao;
    char remedio[50];
    load_users();
    
    do{
        printf("1 - Cadastrar\n");
        printf("2 - Login\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                register_user();
                break;
            case 2:
                login();
                do{
                    printf("Welcome, %s!\n", users[num_users-1].name);
                    printf("Opcao: \n");
                    printf("1 - Comprar\n");
                    printf("2 - Cancelamento\n");
                    printf("3 - Devolucao\n");
                    printf("4 - Relatorio\n");
                    printf("5 - Sair\n");
                    scanf("%d", &opcao);
                    switch(opcao){
                        case 1:
                            printf("Qual remedio voce deseja comprar?\n");
                            scanf("%s", &remedio);
                            printf("Voce deseja comprar %s?\n", remedio);
                            printf("1 - Sim\n");
                            printf("2 - Nao\n");
                            scanf("%d", &opcao);
                            switch(opcao){
                                case 1:
                                    printf("Compra realizada com sucesso!\n");
                                    break;
                                case 2:
                                    printf("Compra cancelada!\n");
                                    break;
                                default:
                                    printf("Opcao invalida!\n");
                                    break;
                            }
                            break;
                        case 2:
                            printf("Qual remedio voce deseja cancelar?\n");
                            scanf("%s", &remedio);
                            printf("Voce deseja cancelar %s?\n", remedio);
                            printf("1 - Sim\n");
                            printf("2 - Nao\n");
                            scanf("%d", &opcao);
                            switch(opcao){
                                case 1:
                                    printf("Cancelamento realizado com sucesso!\n");
                                    break;
                                case 2:
                                    printf("Cancelamento cancelado!\n");
                                    break;
                                default:
                                    printf("Opcao invalida!\n");
                                    break;
                            }
                            break;
                        case 3:
                            printf("Qual remedio voce deseja devolver?\n");
                            scanf("%s", &remedio);
                            printf("Voce deseja devolver %s?\n", remedio);
                            printf("1 - Sim\n");
                            printf("2 - Nao\n");
                            scanf("%d", &opcao);
                            switch(opcao){
                                case 1:
                                    printf("Devolucao realizada com sucesso!\n");
                                    break;
                                case 2:
                                    printf("Devolucao cancelada!\n");
                                    break;
                                default:
                                    printf("Opcao invalida!\n");
                                    break;
                            } while(opcao != 2);
                            break;
                        case 4:
                            printf("Relatorio:\n");
                            printf("1 - Compras\n");
                            printf("2 - Devolucoes\n");
                            printf("3 - Usuarios\n");
                            printf("4 - Sair\n");
                            scanf("%d", &opcao);
                            switch(opcao){
                                case 1:
                                    break;
                                case 2:
                                    break;
                                case 3:
                                    print_users();
                                    break;
                                case 4:
                                    break;
                                default:
                                    break;
                            } while(opcao != 4);
                            break;
                        case 5:
                            printf("Saindo...\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                    }
                }while(opcao != 5);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }while(opcao != 3);
    return 0;
}