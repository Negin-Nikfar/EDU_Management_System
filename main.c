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
    s.entrance_year = 2008;
    strcpy(s.national_code, "1190411202");
    strcpy(s.field, "Computer Engineering");
    strcpy(s.department, "Computer Engineering");
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
    printf("Entrance_year: %d \n", loaded[0].entrance_year);
    printf("National_code: %s \n", loaded[0].national_code);
    printf("Field: %s \n", loaded[0].field);
    printf("Department: %s \n", loaded[0].department);
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

    Faculty f;
    strcpy(f.first_name, "MohammadAli");
    strcpy(f.last_name, "Eshghi");
    strcpy(f.faculty_id, "4567890123");
    f.entrance_year = 1980;
    strcpy(f.national_code, "1199190091");
    strcpy(f.field, "Data Scientist");
    strcpy(f.department, "Computer Science");
    strcpy(f.last_degree, "Ph.D");
    strcpy(f.password, "110029933");

    Faculty faculty[1];
    faculty[0] = f;
    save_faculty(faculty, 1);

    Faculty faculty_loaded[10];
    load_faculty(faculty_loaded, 10);
    printf("Name: %s %s \n", faculty_loaded[0].first_name, faculty_loaded[0].last_name);
    printf("Faculty id: %s \n", faculty_loaded[0].faculty_id);
    printf("Entrance_year: %d \n", faculty_loaded[0].entrance_year);
    printf("National_code: %s \n", faculty_loaded[0].national_code);
    printf("Field: %s \n", faculty_loaded[0].field);
    printf("Department: %s \n", faculty_loaded[0].department);
    printf("Last_degree: %s \n", faculty_loaded[0].last_degree);
    printf("Password: %s \n", faculty_loaded[0].password);

    Course c;
    strcpy(c.name, "FOP");
    strcpy(c.course_id, "40153");
    c.units = 3;
    strcpy(c.prerequisites[0], "CS101");
    strcpy(c.prerequisites[1], "CS102");
    c.prereq_count = 2;
    strcpy(c.section, "Bsc");
    strcpy(c.field, "Computer Engineering");
    strcpy(c.department, "Computer Engineering");


    Course course[1];
    course[0] = c;
    save_courses(course, 1);

    Course courses_loaded[10];
    load_courses(courses_loaded, 10);
    printf("Name: %s \n", courses_loaded[0].name);
    printf("Course id: %s \n", courses_loaded[0].course_id);
    printf("Units: %d \n", courses_loaded[0].units);
    printf("Section: %s \n", courses_loaded[0].section);
    printf("Field: %s \n", courses_loaded[0].field);
    printf("Department: %s \n", courses_loaded[0].department);
    printf("Prereq_count: %d \n", courses_loaded[0].prereq_count);
    printf("Prereq 0: %s\n", courses_loaded[0].prerequisites[0]);
    printf("Prereq 1: %s\n", courses_loaded[0].prerequisites[1]);

    Offering o;
    strcpy(o.course_id, "40153");
    strcpy(o.faculty_id, "4567890123");
    strcpy(o.semester, "14042");
    o.capacity = 100;
    o.enrolled_count = 17;
    strcpy(o.department, "Computer Engineering");
    strcpy(o.place, "Class No.101");

    Offering offerings[10];
    offerings[0] = o;
    save_offerings(offerings, 1);

    Offering offerings_loaded[10];
    load_offerings(offerings_loaded, 10);
    printf("Course_id: %s \n", offerings_loaded[0].course_id);
    printf("Faculty_id: %s \n", offerings_loaded[0].faculty_id);
    printf("Semester: %s \n", offerings_loaded[0].semester);
    printf("Capacity: %d \n", offerings_loaded[0].capacity);
    printf("Enrolled_count: %d \n", offerings_loaded[0].enrolled_count);
    printf("Department: %s \n", offerings_loaded[0].department);
    printf("Place: %s \n", offerings_loaded[0].place);

    Calendar my_calendar;
    my_calendar.offering_active = true;
    my_calendar.unit_selection_active = false;
    my_calendar.class_exam_active = false;
    my_calendar.grade_recording_active = false;
    save_calendar(my_calendar);

    Calendar my_calendar_loaded = load_calendar();
    printf("Offering: %d\n", my_calendar_loaded.offering_active);
    printf("Unit selection: %d\n", my_calendar_loaded.unit_selection_active);

    Request r;
    r.id = 1;
    r.type = OFFER_COURSE;
    strcpy(r.faculty_id, "4567890123");
    strcpy(r.course_id, "40153");
    strcpy(r.semester, "14042");
    r.extra_cap = 100;
    strcpy(r.place, "Class No.101");
    r.status = PENDING;

    Request requests[10];
    requests[0] = r;
    save_requests(requests, 1);
    Request requests_loaded[10];
    load_requests(requests_loaded, 10);
    printf("id: %d \n", requests_loaded[0].id);
    printf("RequestType: %d \n", requests_loaded[0].type);
    printf("Faculty_id: %s \n", requests_loaded[0].faculty_id);
    printf("Course_id: %s \n", requests_loaded[0].course_id);
    printf("Semester: %s \n", requests_loaded[0].semester);
    printf("Extra Cap: %d \n", requests_loaded[0].extra_cap);
    printf("Place: %s \n", requests_loaded[0].place);
    printf("RequestStatus: %d \n", requests_loaded[0].status);
    return 0;
}