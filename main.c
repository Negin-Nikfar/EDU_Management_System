//
// Created by intel one on 7/9/2026.
//
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "authentication.h"
#include "utilities.h"

int main(void) {
    Student students[100];
    int student_count = load_students(students, 100);

    Faculty faculty[100];
    int faculty_count = load_faculty(faculty, 100);

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
            case 1: {
                    int index = authenticate(ROLE_STUDENT, students, student_count, faculty, faculty_count);
                    if (index != -1) {
                        printf("Login successful! Welcome, %s.\n", students[index].first_name);
                    }
                    break;
                }
            case 2: {
                    int index = authenticate(ROLE_FACULTY, students, student_count, faculty, faculty_count);
                    if (index != -1) {
                        printf("Login successful! Welcome, %s.\n", faculty[index].first_name);
                    }
                    break;
                }
            case 3: {
                    int index = authenticate(ROLE_ADMIN, students, student_count, faculty, faculty_count);
                    if (index != -1) {
                        printf("Admin Login successful!\n");
                    }
                    break;
                }
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