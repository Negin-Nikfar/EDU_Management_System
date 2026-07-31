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