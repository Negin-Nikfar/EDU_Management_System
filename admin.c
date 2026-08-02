//
// Created by intel one on 7/9/2026.
//
#include <stdio.h>
#include <string.h>
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

void search_students(Student students[], int student_count) {
    printf("Search:\n");
    printf("1. Search by first name\n");
    printf("2. Search by last name\n");
    printf("3. Search by student id\n");
    printf("Enter an option: ");

    int choice;
    scanf("%d", &choice);

    printf("The phrase to search: ");
    char phrase[100];
    scanf("%s", phrase);

    int found = 0;
    for (int i = 0; i < student_count; i++) {
        int match = 0;
        if (choice == 1 && strstr(students[i].first_name, phrase) != NULL) {
            match = 1;
        }
        else if (choice == 2 && strstr(students[i].last_name, phrase) != NULL) {
            match = 1;
        }
        else if (choice == 3 && strstr(students[i].student_id, phrase) != NULL) {
            match = 1;
        }
        if (match) {
            printf("|%s |%s |%s |%s |%s |%d |%s |%s |%s|\n",
                students[i].first_name, students[i].last_name,
                students[i].student_id, students[i].national_code,
                students[i].field, students[i].entrance_year,
                students[i].section, students[i].mentor, students[i].department);
            found = 1;
        }
    }
    if (!found) {
        printf("No such student found. Try again!\n");
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
        search_students(students, student_count);
    }
}

void register_one_student(Student students[], int *student_count) {
    Student s;
    printf("Enter a first name: ");
    scanf("%s", s.first_name);

    printf("Enter a last name: ");
    scanf("%s", s.last_name);

    printf("Enter a student id: ");
    scanf("%s", s.student_id);

    for (int i = 0; i < *student_count; i++) {
        if (strcmp(students[i].student_id, s.student_id) == 0) {
            printf("Student id already exists.\n");
            return;
        }
    }
    printf("Enter a national code: ");
    scanf("%s", s.national_code);

    printf("Enter field: ");
    scanf(" %[^\n]", s.field);

    printf("Enter entrance_year: ");
    scanf("%d", &s.entrance_year);

    printf("Enter department: ");
    scanf(" %[^\n]", s.department);

    printf("Enter section: ");
    scanf("%s", s.section);

    printf("Enter mentor: ");
    scanf(" %[^\n]", s.mentor);

    printf("Enter password: ");
    scanf("%s", s.password);

    printf("Set security answers:\n");
    printf("Birthplace: ");
    scanf("%s", s.security.birthplace);

    printf("First school: ");
    scanf("%s", s.security.first_school);

    printf("First book: ");
    scanf("%s", s.security.first_book);

    printf("Bike_color: ");
    scanf("%s", s.security.bike_color);

    s.enrollment_count = 0;
    students[*student_count] = s;
    (*student_count)++;

    save_students(students, *student_count);
    printf("Done! Student registered.\n");
}

void register_students(Student students[], int *student_count) {
    printf("Admin: Students: Register student(s)\n");
    printf("Register student(s)\n");
    printf("1. Register one student\n");
    printf("2. Register a group of students (import a file)\n");
    printf("Enter an option: ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        register_one_student(students, student_count);
    }
    else if (choice == 2) {
        printf("File import will be added.\n");
    }
    else {
        printf("Invalid choice. Try again!\n");
    }
}

void remove_student(Student students[], int *student_count) {
    printf("Admin: Students: remove student(s)\n");
    printf("Remove student(s)\n");
    printf("Enter student id: ");

    char student_id[50];
    scanf("%s", student_id);

    int index = -1;
    for (int i = 0; i < *student_count; i++) {
        if (strcmp(students[i].student_id, student_id) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Student not found. Try again!\n");
        return;
    }
    printf("|%s |%s |%s |%s |%s |%d |%s |%s |%s |\n",
        students[index].first_name, students[index].last_name,
        students[index].student_id, students[index].national_code,
        students[index].field, students[index].entrance_year,
        students[index].department, students[index].section,
        students[index].mentor);
    printf("Remove student? [y/n] ");
    char answer;
    scanf(" %c", &answer);

    if (answer == 'y' || answer == 'Y') {
        for (int i = index; i < *student_count - 1; i++) {
            students[i] = students[i + 1];
        }
        (*student_count)--;
        save_students(students, *student_count);
        printf("Done! Student removed.\n");
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
            register_students(students, student_count);
            break;
        case 3:
            remove_student(students, student_count);
            break;
        case 4:
            running = 0;
            break;
        default:
            printf("Invalid choice. Try again!\n");
        }
    }
}

void search_faculty(Faculty faculty[], int faculty_count) {
    printf("Search:\n");
    printf("1. Search by first name\n");
    printf("2. Search by last name\n");
    printf("3. Search by faculty id\n");
    printf("Enter an option: ");

    int choice;
    scanf("%d", &choice);

    printf("The phrase to search: ");
    char phrase[100];
    scanf("%s", phrase);

    int found = 0;
    for (int i = 0; i < faculty_count; i++) {
        int match = 0;
        if (choice == 1 && strstr(faculty[i].first_name, phrase) != NULL) {
            match = 1;
        }
        else if (choice == 2 && strstr(faculty[i].last_name, phrase) != NULL) {
            match = 1;
        }
        else if (choice == 3 && strstr(faculty[i].faculty_id, phrase) != NULL) {
            match = 1;
        }
        if (match == 1) {
            printf("|%s |%s |%s |%s |%s |%d |%s |%s |\n",
                faculty[i].first_name, faculty[i].last_name,
                faculty[i].faculty_id, faculty[i].national_code,
                faculty[i].field, faculty[i].entrance_year,
                faculty[i].last_degree, faculty[i].department);
            found = 1;
        }
    }
    if (!found) {
        printf("No faculties found. Try again!\n");
    }
}

void show_faculty_table(Faculty faculty[], int faculty_count) {
    printf("Admin: Faculty members: faculty list\n");
    printf("Faculty list\n");

    for (int i = 0; i < faculty_count; i++) {
        printf("|%s |%s |%s |%s |%s |%d |%s |%s |\n",
            faculty[i].first_name, faculty[i].last_name,
            faculty[i].faculty_id, faculty[i].national_code,
            faculty[i].field, faculty[i].entrance_year,
            faculty[i].last_degree, faculty[i].department);
        printf("1. Search\n");
        printf("2. Go back\n");
        printf("Enter an option: ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            search_faculty(faculty, faculty_count);
        }
    }
}

void register_faculty(Faculty faculty[], int *faculty_count) {
    printf("Admin: Faculty members: register faculty member(s)\n");

    Faculty f;

    printf("1. Enter first name: ");
    scanf("%s", f.first_name);

    printf("2. Enter last name: ");
    scanf("%s", f.last_name);

    printf("3. Enter faculty id: ");
    scanf("%s", f.faculty_id);
    for (int i = 0; i < *faculty_count; i++) {
        if (strcmp(faculty[i].faculty_id, f.faculty_id) == 0) {
            printf("Faculty id already exists.\n");
            return;
        }
    }
    printf("Enter national code: ");
    scanf("%s", f.national_code);

    printf("Enter field: ");
    scanf(" %[^\n]", f.field);

    printf("Enter entrance_year: ");
    scanf("%d", &f.entrance_year);

    printf("Enter department: ");
    scanf(" %[^\n]", f.department);

    printf("Enter last degree: ");
    scanf(" %[^\n]", f.last_degree);

    printf("Enter password: ");
    scanf(" %[^\n]", f.password);

    faculty[*faculty_count] = f;
    (*faculty_count)++;

    save_faculty(faculty, *faculty_count);
    printf("Done! Faculty registered.\n");
}

void remove_faculty(Faculty faculty[], int *faculty_count) {
    printf("Admin: Faculty members: remove faculty member(s)\n");
    printf("Enter faculty id: ");

    char faculty_id[50];
    scanf("%s", faculty_id);

    int index = 0;
    for (int i = 0; i < *faculty_count; i++) {
        if (strcmp(faculty[i].faculty_id, faculty_id) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("No faculty found. Try again!\n");
        return;
    }
    printf("Remove faculty? [y/n] ");
    char answer;
    scanf("%c", &answer);

    if (answer == 'y' || answer == 'Y') {
        for (int i = index; i < *faculty_count - 1; i++) {
            faculty[i] = faculty[i + 1];
        }
        (*faculty_count)--;
        save_faculty(faculty, *faculty_count);
        printf("Done! Faculty removed.\n");
    }
}

void admin_faculty(Faculty faculty[], int *faculty_count) {
    int running = 1;
    while (running) {
        printf("Admin: Faculty members\n");
        printf("1. Faculty list\n");
        printf("2. Register faculty member(s)\n");
        printf("3. Remove faculty member(s)\n");
        printf("4. Go back\n");
        printf("Enter an option: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            show_faculty_table(faculty, *faculty_count);
            break;
        case 2:
            register_faculty(faculty, faculty_count);
            break;
        case 3:
            remove_faculty(faculty, faculty_count);
            break;
        case 4:
            running = 0;
            break;
        default:
            printf("Invalid choice. Try again!\n");
        }
    }
}
