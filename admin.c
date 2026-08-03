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

////////student////////

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

////////faculty////////

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

////////request////////

void admin_requests(Request requests[], int *request_count,
                    Offering offerings[], int *offering_count,
                    Course courses[], int course_count,
                    Faculty faculty[], int faculty_count) {
    printf("Admin: Requests\n");
    int pending_index[100];
    int pending_count = 0;
    for (int i = 0; i < *request_count; i++) {
        if (requests[i].status == PENDING) {
            pending_index[pending_count] = i;
            pending_count++;
        }
    }
    if (pending_count == 0) {
        printf("No pending requests.\n");
        return;
    }
    printf("List of requests\n");
    for (int i = 0; i < pending_count; i++) {
        int request_index = pending_index[i];
        Request request = requests[request_index];
        char course_name[100] = "Unknown";
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, request.course_id) == 0) {
                strcpy(course_name, courses[j].name);
                break;
            }
        }
        char faculty_name[100] = "Unknown";
        char faculty_department[100] = "Unknown";
        for (int j = 0; j < faculty_count; j++) {
            if (strcmp(faculty[j].faculty_id, request.faculty_id) == 0) {
                sprintf(faculty_name, "%s %s", faculty[j].first_name, faculty[j].last_name);
                strcpy(faculty_department, faculty[j].department);
                break;
            }
        }
        printf("%d. ", i + 1);
        if (request.type == OFFER_COURSE) {
            printf("Course offering\n");
        }
        else if (request.type == REMOVE_OFFERING) {
            printf("Course removing\n");
        }
        else if (request.type == ADD_CAPACITY) {
            printf("Capacity increment\n");
        }
        printf("Course: %s\n", course_name);
        printf("Faculty: %s\n", faculty_name);
        printf("Department: %s\n", faculty_department);
        printf("Capacity: %d\n", request.extra_cap);

        if (request.type == ADD_CAPACITY) {
            int enrolled= 0;
            for (int j = 0; j < *offering_count; j++) {
                if (strcmp(offerings[j].course_id, request.course_id) == 0 &&
                    strcmp(offerings[j].semester, request.semester) == 0) {
                    enrolled = offerings[j].enrolled_count;
                    break;
                }
            }
            printf("No. enrollments: %d\n", enrolled);
        }
    }
    printf("1. Go to request number\n");
    printf("2. Go back\n");
    printf("Enter an option: ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter request number: ");
        int request_number;
        scanf("%d", &request_number);

        if (request_number < 1 || request_number > pending_count) {
            printf("Invalid request number.\n");
            return;
        }
        int request_index = pending_index[request_number - 1];
        Request *r = &requests[request_index];
        printf("1. Approve\n");
        printf("2. Reject\n");
        printf("Go back\n");
        printf("Enter an option: ");

        int action;
        scanf("%d", &action);

        if (action == 1) {
            if (r->type == OFFER_COURSE) {
                Offering new_offering;
                strcpy(new_offering.course_id, r->course_id);
                strcpy(new_offering.faculty_id, r->faculty_id);
                strcpy(new_offering.semester, r->semester);
                new_offering.capacity = r->extra_cap;
                strcpy(new_offering.place, r->place);
                new_offering.enrolled_count = 0;
                for (int j = 0; j < course_count; j++) {
                    if (strcmp(courses[j].course_id, r->course_id) == 0) {
                        strcpy(new_offering.department, courses[j].department);
                        break;
                    }
                }
                offerings[*offering_count] = new_offering;
                (*offering_count)++;
                save_offerings(offerings, *offering_count);
            }
            else if (r->type == REMOVE_OFFERING) {
                for (int j = 0; j < *offering_count; j++) {
                    if (strcmp(offerings[j].course_id, r->course_id) == 0 &&
                        strcmp(offerings[j].semester, r->semester) == 0) {
                        for (int k = j; k < *offering_count - 1; k++) {
                            offerings[k] = offerings[k + 1];
                        }
                        (*offering_count)--;
                        break;
                    }
                }
                save_offerings(offerings, *offering_count);
            }
            else if (r->type == ADD_CAPACITY) {
                for (int j = 0; j < *offering_count; j++) {
                    if (strcmp(offerings[j].course_id, r->course_id) == 0 &&
                        strcmp(offerings[j].semester, r->semester) == 0) {
                        offerings[j].capacity += r->extra_cap;
                        break;
                    }
                }
                save_offerings(offerings, *offering_count);
            }
            r->status = APPROVED;
            printf("Request approved.\n");
        }
        else if (choice == 2) {
            r->status = REJECTED;
            printf("Request rejected.\n");
        }
        save_requests(requests, *request_count);
    }
}

////////offering////////

void search_offerings(Offering offerings[],int matching_indexes[],
                      int matching_count, Course courses[], int course_count) {
    printf("1. Search by course name\n");
    printf("2. Search by course id\n");
    printf("3. Search by department\n");
    printf("Enter an option: ");
    int choice;
    scanf("%d", &choice);

    printf("The phrase to search: ");
    char phrase[50];
    scanf("%s", phrase);

    int found = 0;
    for (int i = 0; i < matching_count; i++) {
        int index = matching_indexes[i];
        char course_name[100] = "Unknown";
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, offerings[index].course_id) == 0) {
                strcpy(course_name, courses[j].name);
                break;
            }
        }
        int match = 0;
        if (choice == 1 && strstr(course_name, phrase) != NULL) {
            match = 1;
        }
        else if (choice == 2 && strstr(offerings[index].course_id, phrase) != NULL) {
            match = 1;
        }
        else if (choice == 3 && strstr(offerings[index].department, phrase) != NULL) {
            match = 1;
        }
        if (match) {
            printf("| %s | %s | %s | %s | %d | %d | %s | %s |\n",
                course_name, offerings[index].course_id,
                offerings[index].faculty_id,offerings[index].semester,
                offerings[index].capacity,offerings[index].enrolled_count,
                offerings[index].department,offerings[index].place);
            found = 1;
        }
    }
    if (!found) {
        printf("No such offering found. Try again!\n");
    }
}

void admin_enroll_student(Offering offerings[], int matching_indexes[],
                          int matching_count, Student students[], int *student_count) {
    printf("Enter offering number: ");
    int number;
    scanf("%d", &number);

    if (number < 1 || number > matching_count) {
        printf("Invalid offering number.\n");
        return;
    }
    int offering_index = matching_indexes[number - 1];
    printf("Enter student id: ");
    char student_id[50];
    scanf("%s", student_id);

    int student_index = -1;
    for (int i = 0; i < *student_count; i++) {
        if (strcmp(students[i].student_id, student_id) == 0) {
            student_index = i;
            break;
        }
    }
    if (student_index == -1) {
        printf("Student not found.\n");
        return;
    }
    for (int i = 0; i < students[student_index].enrollment_count; i++) {
        if (strcmp(students[student_index].enrollments[i].course_id, offerings[offering_index].course_id) == 0 &&
            strcmp(students[student_index].enrollments[i].semester, offerings[offering_index].semester) == 0) {
            printf("Student already enrolled in this course.\n");
            return;
            }
    }
    if (offerings[offering_index].enrolled_count >= offerings[offering_index].capacity) {
        printf("Warning: No capacity available. Adding as admin override.\n");
    }
    int enrolled_index = students[student_index].enrollment_count;
    strcpy(students[student_index].enrollments[enrolled_index].semester, offerings[offering_index].semester);
    strcpy(students[student_index].enrollments[enrolled_index].course_id, offerings[offering_index].course_id);
    students[student_index].enrollments[enrolled_index].grade = -1;
    students[student_index].enrollment_count++;

    offerings[offering_index].enrolled_count++;
    save_students(students, *student_count);
    printf("Done! Student added to offering.\n");
}

void admin_withdraw_student(Offering offerings[], int matching_indexes[],
                            int matching_count, Student students[],int student_count) {
    printf("Enter offering number: ");
    int number;
    scanf("%d", &number);

    if (number < 1 || number > matching_count) {
        printf("Invalid number.\n");
        return;
    }
    int offering_index = matching_indexes[number - 1];
    printf("Enter student id: ");
    char student_id[50];
    scanf("%s", student_id);

    int student_index = -1;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].student_id, student_id) == 0) {
            student_index = i;
            break;
        }
    }
    if (student_index == -1) {
        printf("Student not found.\n");
        return;
    }
    int enrolled_index = -1;
    for (int i = 0; i < students[student_index].enrollment_count; i++) {
        if (strcmp(students[student_index].enrollments[i].course_id, offerings[offering_index].course_id) == 0 &&
            strcmp(students[student_index].enrollments[i].semester, offerings[offering_index].semester) == 0) {
            enrolled_index = i;
            break;
            }
    }
    if (enrolled_index == -1) {
        printf("Student isn't enrolled in this course.\n");
        return;
    }
    for (int i = enrolled_index; i < students[student_index].enrollment_count - 1; i++) {
        students[student_index].enrollments[i] = students[student_index].enrollments[i + 1];
    }
    students[student_index].enrollment_count--;
    offerings[offering_index].enrolled_count--;
    save_students(students, student_count);
    printf("Done! Student removed from offering.\n");
}

void admin_offerings(Offering offerings[], int *offering_count,
                     Course courses[], int course_count,
                     Student students[], int *student_count) {
    printf("Admin: Offerings\n");
    printf("Enter semester number: ");
    char semester[50];
    scanf("%s", semester);

    int matching_indexes[100];
    int matching_count = 0;
    for (int i = 0; i < *offering_count; i++) {
        if (strcmp(offerings[i].semester, semester) == 0) {
            matching_indexes[matching_count] = i;
            matching_count++;
        }
    }
    if (matching_count == 0) {
        printf("No offerings found for this semester.\n");
        return;
    }
    printf("List of offerings - %s\n", semester);
    for (int i = 0; i < matching_count; i++) {
        int index = matching_indexes[i];
        char course_name[100] = "Unknown";
        for (int j = 0; j < course_count; j++) {
            if (strcmp(courses[j].course_id, offerings[index].course_id) == 0) {
                strcpy(course_name, courses[j].name);
                break;
            }
        }
        printf("| %d | %s | %s | %s | %s |%d | %d | %s | %s |\n",
            i + 1, course_name, offerings[index].course_id,
            offerings[index].faculty_id, offerings[index].semester,
            offerings[index].capacity, offerings[index].enrolled_count,
            offerings[index].department, offerings[index].place);
    }
    printf("1. Search\n");
    printf("2. Add student to an offering\n");
    printf("3. Remove student from an offering\n");
    printf("4. Go back\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        search_offerings(offerings, matching_indexes, matching_count, courses, course_count);
    }
    else if (choice == 2) {
        admin_enroll_student(offerings, matching_indexes, matching_count, students, student_count);
        save_offerings(offerings, *student_count);
    }
    else if (choice == 3) {
        admin_withdraw_student(offerings, matching_indexes, matching_count, students, *student_count);
        save_offerings(offerings, *offering_count);
    }
}

////////courses////////

void search_courses(Course courses[], int course_count) {
    printf("1. Search by course name\n");
    printf("2. Search by course id\n");
    printf("3. Search by field\n");
    printf("4. Search by department\n");
    printf("Enter an option: ");
    int choice;
    scanf("%d", &choice);

    printf("The phrase to search: ");
    char answer[100];
    scanf("%s", answer);

    int found = 0;
    for (int i = 0; i < course_count; i++) {
        int match = 0;
        if (choice == 1 && strstr(courses[i].name, answer) != NULL) {
            match = 1;
        }
        else if (choice == 2 && strstr(courses[i].course_id, answer) != NULL) {
            match = 1;
        }
        else if (choice == 3 && strstr(courses[i].field, answer) != NULL) {
            match = 1;
        }
        else if (choice == 4 && strstr(courses[i].department, answer) != NULL) {
            match = 1;
        }
        if (match) {
            printf("| %s | %s | %d | ", courses[i].name, courses[i].course_id, courses[i].units);
            for (int j = 0; j < courses[i].prereq_count; j++) {
                printf("%s", courses[i].prerequisites[j]);
                if (j < courses[i].prereq_count - 1) {
                    printf(", ");
                }
            }
            printf("| %s | %s | %s | ", courses[i].section, courses[i].field, courses[i].department);
            found = 1;
        }
    }
    if (!found) {
        printf("No courses found. Try again!\n");
    }
}

void add_course(Course courses[], int *course_count, Calendar *calendar) {
    if (calendar->class_exam_active || calendar->grade_recording_active) {
        printf("Can't add course midterm!\n");
        return;
    }
    Course c;
    printf("Enter course name: ");
    scanf(" %[^\n]", c.name);

    printf("Enter course id: ");
    scanf("%s", c.course_id);

    for (int i = 0; i < *course_count; i++) {
        if (strcmp(courses[i].course_id, c.course_id) == 0) {
            printf("Course id already exists.\n");
            return;
        }
    }
    printf("Enter units: ");
    scanf(" %d", &c.units);

    printf("Enter number of prerequisites (0 if none): ");
    int n;
    scanf("%d", &n);

    c.prereq_count = n;
    for (int i = 0; i < n; i++) {
        printf("Enter prerequisite %d course id: ", i + 1);
        scanf("%s", c.prerequisites[i]);
    }
    printf("Enter section (BSc/MSc/PhD): ");
    scanf("%s", c.section);

    printf("Enter field:");
    scanf(" %[^\n]", c.field);

    printf("Enter department:");
    scanf(" %[^\n]", c.department);

    courses[*course_count] = c;
    (*course_count)++;
    save_courses(courses, *course_count);
    printf("Course added.\n");
}

void remove_course(Course courses[], int *course_count, Offering offerings[], int offering_count) {
    printf("Enter course id: ");
    char course_id[50];
    scanf("%s", course_id);

    int index = -1;
    for (int i = 0; i < *course_count; i++) {
        if (strcmp(courses[i].course_id, course_id) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Course not found.\n");
        return;
    }
    int active = 0;
    for (int i = 0; i < offering_count; i++) {
        if (strcmp(offerings[i].course_id, course_id) == 0) {
            active = 1;
            break;
        }
    }
    if (active) {
        printf("Warning: This course has existing offerings.\n");
        printf("Continue? [y/n] ");
        char c;
        scanf(" %c", &c);
        if (c != 'y' && c != 'Y') {
            return;
        }
    }
    for (int i = index; i < *course_count - 1; i++) {
        courses[i] = courses[i + 1];
    }
    (*course_count)--;
    save_courses(courses, *course_count);
    printf("Course removed.\n");
}

void admin_courses(Course courses[], int *course_count, Offering offerings[],
                   int offering_count, Calendar *calendar) {
    int running = 1;
    while (running) {
        printf("Admin: Courses\n");
        printf("List of courses\n");
        for (int i = 0; i  < *course_count; i++) {
            printf("| %s | %s | %d |\n", courses[i].name, courses[i].course_id, courses[i].units);
            for (int j = 0; j < courses[i].prereq_count; j++) {
                printf("%s", courses[i].prerequisites[j]);
                if (j < courses[i].prereq_count - 1) {
                    printf(", ");
                }
            }
            printf(" | %s | %s | %s |\n", courses[i].section, courses[i].field, courses[i].department);
        }
        printf("1. Search\n");
        printf("2. Add a course\n");
        printf("3. Remove a course\n");
        printf("4. Go back\n");
        printf("Enter an option: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                search_courses(courses, *course_count);
                break;
            case 2:
                add_course(courses, course_count, calendar);
                break;
            case 3:
                remove_course(courses, course_count, offerings, offering_count);
                break;
            case 4:
                running = 0;
                break;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }
}