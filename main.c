//
// Created by intel one on 7/9/2026.
//
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "utilities.h"

int main(void) {
    Student s;
    strcpy(s.first_name, "Negin");
    strcpy(s.last_name, "Nikfar");
    strcpy(s.student_id, "404103874");
    strcpy(s.national_code, "1190411202");
    strcpy(s.field, "Computer Engineering");
    strcpy(s.department, "Computer Engineering");
    s.entrance_year = 2008;
    strcpy(s.section, "Bsc");
    strcpy(s.mentor, "Dr.Ali.Najimi");
    strcpy(s.password, "123456789");
    strcpy(s.security.birthplace, "Shahreza");
    strcpy(s.security.first_school, "Madaraneh");
    strcpy(s.security.first_book, "mathematics");
    strcpy(s.security.bike_color, "green");
    strcpy(s.enrollments[0].semester, "14042");
    strcpy(s.enrollments[0].course_id, "CE101");
    s.enrollments[0].grade = 19.5;
    s.enrollment_count = 1;

    Student students[1];
    students[0] = s;
    save_students(students, 1);

    Student loaded[10];
    load_students(loaded, 10);
    printf("Name: %s %s \n", loaded[0].first_name, loaded[0].last_name);
    printf("Student id: %s \n", loaded[0].student_id);
    printf("National_code: %s \n", loaded[0].national_code);
    printf("Field: %s \n", loaded[0].field);
    printf("Department: %s \n", loaded[0].department);
    printf("Entrance_year: %d \n", loaded[0].entrance_year);
    printf("Section: %s \n", loaded[0].section);
    printf("Mentor: %s \n", loaded[0].mentor);
    printf("Password: %s \n", loaded[0].password);
    printf("Birthplace: %s \n", loaded[0].security.birthplace);
    printf("First_school: %s \n", loaded[0].security.first_school);
    printf("First_book: %s \n", loaded[0].security.first_book);
    printf("Bike_color: %s \n", loaded[0].security.bike_color);
    printf("Enrollment: %s - %s - %.2f\n",
        loaded[0].enrollments[0].semester,
        loaded[0].enrollments[0].course_id,
        loaded[0].enrollments[0].grade);
    return 0;
}
