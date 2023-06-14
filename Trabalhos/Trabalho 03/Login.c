/*
1. Crie uma janela de interface do usuário com opções de cadastro e login.
2. Se o usuário selecionar "Cadastro", permita que eles insiram seus dados de cadastro (como nome, endereço de e-mail e senha) e salve-os em um banco de dados.
3. Se o usuário selecionar "Login", solicite que eles insiram seu endereço de e-mail e senha e verifique se as informações correspondem aos dados salvos no banco de dados. Se as informações estiverem corretas, permita que o usuário prossiga para a próxima etapa.
4. Se o usuário selecionar "Sair", encerre o programa.
*/

#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

struct User {
    char name[50];
    char email[50];
    char password[50];
};

struct User users[MAX_USERS];

int num_users = 0;

void register_user() {
    printf("Please enter your name: ");
    scanf("%s", users[num_users].name);
    printf("Please enter your email address: ");
    scanf("%s", users[num_users].email);
    printf("Please enter your password: ");
    scanf("%s", users[num_users].password);
    num_users++;
    printf("Registration successful!\n");
}

int login() {
    char email[50], password[50];
    printf("Please enter your email address: ");
    scanf("%s", email);
    printf("Please enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(email, users[i].email) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful!\n");
            return 1;
        }
    }

    printf("Invalid email address or password.\n");
    return 0;
}

int main() {
    int choice;

    while (1) {
        printf("1. Register\n2. Login\n3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                if (login()) {
                    // user is logged in
                    printf("Welcome, %s!\n", users[num_users-1].name);
                    // do something after login
                }
                break;
            case 3:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}
