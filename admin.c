//
// Created by intel one on 7/9/2026.
//
#include <stdio.h>
#include "admin.h"

void admin_calendar(Calendar *calendar) {
    int running = 1;
    while (running) {
        printf("Admin: Calendar\n");
        printf("1. Offering: %s\n", calendar->offering_active ? "enabled" : "disabled");
        printf("2. Unit selection: %s\n", calendar->unit_selection_active ? "enabled" : "disabled");
        printf("3. Class & exams: %s\n", calendar->class_exam_active ? "enabled" : "disabled");
        printf("4. Grade recording: %s\n", calendar->grade_recording_active ? "enabled" : "disabled");
        printf("5. Go to main menu\n");
        printf("Enter a time to trigger: ");

        int choice;
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            calendar->offering_active = !calendar->offering_active;
            break;
        case 2:
            if (!calendar->unit_selection_active && calendar->unit_selection_active) {
                printf("Offering period must end before unit selection can end.\n");
            }
            else {
                calendar->unit_selection_active = !calendar->unit_selection_active;
            }
            break;
        case 3:
            calendar->class_exam_active = !calendar->class_exam_active;
            break;
        case 4:
            calendar->grade_recording_active = !calendar->grade_recording_active;
            break;
        case 5:
            running = 0;
            break;
        default:
            printf("Invalid choice. Try again!\n");
        }
        if (choice != 5) {
            save_calendar(*calendar);
        }
    }
}

void show_students_table(Student students[], int student_count) {
    printf("Admin: Students: Students list\n");
    printf("1. Students list\n");

    for (int i = 0; i < student_count; i++) {
        printf("|%s |%s |%s |%s |%s |%d |%s |%s |%s |%s |%s |%s|\n",
            students[i].first_name, students[i].last_name,
            students[i].student_id, students[i].national_code,
            students[i].field, students[i].entrance_year,
            students[i].section, students[i].mentor,
            students[i].department, students[i].security.birthplace,
            students[i].security.first_book, students[i].security.bike_color);
    }
    printf("1. Search\n");
    printf("2. Go back\n");
    printf("Enter an option: ");
    int choice;
    scanf("%d", &choice);


    if (choice == 1) {
        printf("This part will be later...\n");
    }
}

void admin_students(Student students[], int *student_count) {
    int running = 1;
    while (running) {
        printf("Admin: Students\n");
        printf("1. Students list\n");
        printf("2. Register student(s)\n");
        printf("3. Remove student(s)\n");
        printf("4. Go back\n");
        printf("Enter an option: ");

        int choice;
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            show_students_table(students, *student_count);
            break;
        case 2:
            printf("This part will be later...\n");
            break;
        case 3:
            printf("This part will be later...\n");
            break;
        case 4:
            running = 0;
            break;
        default:
            printf("Invalid choice. Try again!\n");
        }
    }
}
