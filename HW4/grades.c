
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "grades.h"
#include "linked-list.h"

/* Defined elsewhere */


 struct course {
	int grade;
	char* course_name;
}

struct student {
	int id;
	char* student_name;
	struct list * course_list;

}

struct grades{
	struct list * students_list;
};

int student_clone (void*stud,void**output){
	struct student *Student = (struct student *) stud;
	*output = (struct student *) malloc (sizeof (Student));
	if (*output == NULL){
		return -1;
	}
	return 0;
}
void student_destroy(void*students);
int course_clone(void*cuourse,void**output);
void course_destroy(void*course);

/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init(){
	struct grades *grd =(struct grades*) malloc (sizeof(struct grades));
	if (!grd){
		return -1;
	}
	grd->students_list = list_init(student_clone,student_destroy);
	if(grd->students_list == NULL){
		free(grd);
		return -1;
	}

return grd;
}

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
	free(grades);
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){
	struct student *current_student;
	current_student->id = id;
	name = (char*) malloc (strlen (current_student->student_name)+1);
	if(! name){
		return -1;
	}
	current_student->student_name = name;
	if ((grades == NULL) ||(grades->students_list == NULL)){
		free(name);
		return -1;
	}
	if(!(list_push_back(grades->students_list,current_student))){
		free(name);
		return -1;
	}
	struct iterator* current_node =  list_begin(grades);
	while(current_node){
		if ((current_student->id ==
				(((struct student *)(list_get(current_node)))->id))){
			free(name);
			return -1;
		}
		current_node=list_next (current_node);
	}
	free(name);
	return 0;
}

/**
 * @brief Adds a course with "name" and " to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
	if ((grades == NULL) ||(grades->students_list == NULL)){
			return -1;
	}
	if ((grade < 0) ||(grade > 100)){
		return -1;
	}
	struct course* current_course;
	name = (char*) malloc (strlen (current_course->course_name)+1);
	if(!name){
		return -1;
	}
	current_course->course_name = name;
	current_course->grade = grade;
	struct iterator* current_node =  list_begin(grades->students_list);
		while(current_node){
			if (id == (((struct student *)(list_get(current_node)))->id)){
				if(!(list_push_back(((struct student *)
					(list_get(current_node)))->course_list,current_course)));
				free(name);
				return 0;
			}
			current_node=list_next (current_node);
		}
		free(name);
	return -1;

}

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "*out" to NULL.
 * @note "out" is a pointer to char*. Meaning, your function should
 * allocate memory on the heap and set "*out" to point on that memory.
 * This methodology (of returning values via pointers) is very common in C.
 * An example of C method that returns a value via pointer:
 * void foo(int *out) {
 *   *out = 1;
 * }
 */
float grades_calc_avg(struct grades *grades, int id, char **out){
	float sum =0;
	int student_exist = 0;
	int courses = 0;
	if ((grades == NULL) ||(grades->students_list == NULL)){

				return -1;
		}
	struct iterator* current_node =  list_begin(grades->students_list);
		while(current_node){
			if (id == ((struct student *)(list_get(current_node)))->id){
				student_exist=1;
				*out = (char*) malloc (strlen (((struct student *)
						(list_get(current_node)))->student_name)+1);
				if (!(*out)){
					return -1;
				}
				*out = ((struct student *)
						(list_get(current_node)))->student_name;
				struct iterator* current_course_node =  list_begin
						(((struct student *)
								(list_get(current_node)))->course_list);
								while(current_course_node){
									sum += ((struct course *)
										(list_get(current_course_node)))->grade;
									courses ++;
									current_node=list_next (current_node);

									}


				}
				current_node=list_next (current_node);
			}
		if(!student_exist){
			free(*out);
			return -1;
		}
		if (!courses){
			return 0;
		}
		return (sum/courses);
}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
	if ((grades == NULL) ||(grades->students_list == NULL)){

					return -1;
			}
	int student_exist = 0;
	struct iterator* current_node =  list_begin(grades->students_list);
		while(current_node){
			if (id == ((struct student *)(list_get(current_node)))->id){
				student_exist = 1;
			printf("%s %d:",((struct student *)
					(list_get(current_node)))->student_name,((struct student *)
							(list_get(current_node)))->id);
				struct iterator* current_course_node =  list_begin
						(((struct student *)
								(list_get(current_node)))->course_list);
							while(current_course_node){
								printf(" %s %d,",
								((struct course *)
								(list_get(current_course_node)))->course_name,
								((struct course *)
									(list_get(current_course_node)))->grade);
									current_course_node=
											list_next (current_course_node);

									}
				}
				current_node=list_next (current_node);
			}
		if(! student_exist){
			return -1;
		}

		return 0;

}

/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){
	if ((grades == NULL) ||(grades->students_list == NULL)){

					return -1;
			}
	struct iterator* current_node =  list_begin(grades->students_list);
			while(current_node){
				printf("%s %d:",((struct student *)
						(list_get(current_node)))->student_name,
						((struct student *)(list_get(current_node)))->id);
					struct iterator* current_course_node =  list_begin
							(((struct student *)
									(list_get(current_node)))->course_list);
								while(current_course_node){
									printf(" %s %d,",
										((struct course *)
								(list_get(current_course_node)))->course_name,
										((struct course *)
									(list_get(current_course_node)))->grade);
										current_course_node=
												list_next (current_course_node);

										}
									printf("\n");
									current_node=list_next (current_node);

					}
			return 0;
}

int main(int argc, char **argv) {
	printf("Hello World\n");
	return 0;
}
