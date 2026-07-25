//
// Created by intel one on 7/9/2026.
//
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "utilities.h"

int main(void) {

    char password[20];
    printf("Enter your password: ");
    read_password(password);
    printf("\nYou entered: %s\n", password);

    int running = 1;
    while (running) {
        printf("1. Login as student\n");
        printf("2. Login as faculty\n");
        printf("3. Login as admin\n");
        printf("4. Forgot password\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("This part will be later.\n");
                break;
            case 2:
                printf("This part will be later.\n");
                break;
            case 3:
                printf("This part will be later.\n");
                break;
            case 4:
                printf("This part will be later.\n");
                break;
            case 5:
                running = 0;
                break;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }
    return 0;
}