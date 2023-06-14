#define MAX_USERS 100
#define FILENAME "users.txt"

struct User {
    char name[50];
    char email[50];
    char password[50];
};

struct User users[MAX_USERS];

int num_users = 0;

void save_users() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error: cannot open file.\n");
        return;
    }
    for (int i = 0; i < num_users; i++) {
        fprintf(fp, "%s,%s,%s\n", users[i].name, users[i].email, users[i].password);
    }
    fclose(fp);
}

void load_users() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("Error: cannot open file.\n");
        return;
    }
    while (fscanf(fp, "%[^,],%[^,],%s\n", users[num_users].name, users[num_users].email, users[num_users].password) == 3) {
        num_users++;
    }
    fclose(fp);
}

int is_registered(char *email) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(email, users[i].email) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user() {
    char email[50];
    printf("Please enter your name: ");
    scanf("%s", users[num_users].name);
    while (1) {
        printf("Please enter your email address: ");
        scanf("%s", email);
        if (is_registered(email)) {
            printf("This email is already registered. Please enter a different email address.\n");
        } else {
            strcpy(users[num_users].email, email);
            break;
        }
    }
    printf("Please enter your password: ");
    scanf("%s", users[num_users].password);
    num_users++;
    save_users();
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

void print_users() {
    printf("Lista de usuario resgitrados:\n");
    for (int i = 0; i < num_users; i++) {
        printf("Name: %s\nEmail: %s\nPassword: %s\n\n", users[i].name, users[i].email, users[i].password);
    }
}