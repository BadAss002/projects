#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_LEN 100

int check_password(const char *input) {
    FILE *file = fopen("password.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла с паролем\n");
        return 0;
    }

    char real_password[MAX_LEN];
    fgets(real_password, MAX_LEN, file);
    fclose(file);
    real_password[strcspn(real_password, "\n")] = 0;

    if (strcmp(input, real_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    // setlocale(LC_ALL, "UTF-8");
    char input[MAX_LEN];
    printf("Enter password: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = 0;
    if (check_password(input)) {
        printf("Access\n");
    } else {
        printf("NO Access\n");
    }

    return 0;
}
