
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "grades.h"
#include "linked-list.h"

#define FAIL -1


 struct course {
	int grade;
	char* course_name;
};

struct student {
	int id;
	char* student_name;
	struct list * course_list;

};

struct grades{
	struct list * students_list;
};

int student_clone (void*stud,void**output);
void student_destroy(void*students);
void course_destroy(void*course);
int course_clone(void*cuourse,void**output);


int student_clone (void*student,void**output){
	struct student *out_student = (struct student *) malloc (sizeof(struct student));
		if (out_student == NULL){
			return FAIL;
		}
		struct student *local_student = (struct student*) student;


			out_student->student_name =(char*)malloc(strlen(local_student->student_name)+1);
			if(out_student->student_name==NULL){
				return FAIL;
			}
			strcpy(out_student->student_name,local_student->student_name);
			out_student->id = local_student->id;
			out_student->course_list = list_init(course_clone,course_destroy);
			if(out_student->course_list == NULL){
				free(out_student->student_name);
				free(out_student);
				return FAIL;
			}


			*output =  (void*)out_student;
			//free(out_student->student_name);
			//free(out_student);

	return 0;
}
void student_destroy(void*students){
	struct student * temp_student = (struct student *) students;
	free(temp_student->student_name);
	list_destroy(temp_student->course_list);
	free(temp_student);

}

int course_clone(void*course,void**output){
	struct course *out_course = (struct course *) malloc (sizeof(struct course));
	if (out_course == NULL){
		return FAIL;
	}
	struct course *local_course = (struct course*) course;


		out_course->course_name =(char*)malloc(strlen(local_course->course_name)+1);
		if(out_course->course_name==NULL){
			free(out_course);
			return FAIL;
		}
		strcpy(out_course->course_name,local_course->course_name);
		out_course->grade = local_course->grade;
		*output = (void*)out_course;

		return 0;
	}

void course_destroy(void*course){
	struct course * temp_course = (struct course *) course;
	free(temp_course->course_name);
	free(temp_course);
}

/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init(){
	struct grades *grd =(struct grades*) malloc (sizeof(struct grades));
	if (!grd){
		return NULL;
	}
	grd->students_list = list_init(student_clone,student_destroy);
	if(grd->students_list == NULL){
		free(grd);
		return NULL;
	}

return grd;
}

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades){
	list_destroy(grades->students_list);
	free(grades);
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){
	struct student *current_student = (struct student *)malloc(sizeof(struct student));
	if(!current_student){
		return FAIL;
	}
	current_student->id = id;
	current_student->student_name = (char*) malloc (strlen (name)+1);
	if(! (current_student->student_name)){
		free(current_student);
		return FAIL;
	}
	strcpy(current_student->student_name,name);
	if ((grades == NULL) ||(grades->students_list == NULL)){
		free(current_student->student_name);
		free(current_student);
		return FAIL;
	}

	struct iterator* current_node =  list_begin(grades->students_list);
	//checks if the given id already exists
	while(current_node){
		if ((current_student->id ==
				(((struct student *)(list_get(current_node)))->id))){
			free(current_student->student_name);
			free(current_student);
			return FAIL;
		}
		current_node=list_next (current_node);
	}
	// if the id is not already in the list, we initite a node with a new student
	current_student->course_list = list_init (course_clone,course_destroy);
	if((current_student->course_list)==NULL){
		free(current_student->student_name);
		free(current_student);
		return FAIL;
	}
	if(list_push_back(grades->students_list,current_student)){

			free(current_student->student_name);
			list_destroy(current_student->course_list);
			free(current_student);
			return FAIL;
	}
	free(current_student->student_name);
	list_destroy(current_student->course_list);
	free(current_student);
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
			return FAIL;
	}
	if ((grade < 0) ||(grade > 100)){
		return FAIL;
	}
	struct course* current_course=(struct course*) malloc (sizeof(struct course));
	if(current_course == NULL){
		return FAIL;
	}
	current_course->course_name = (char*) malloc (strlen (name)+1);
	if(!(current_course->course_name)){
		free(current_course);
		return FAIL;
	}
	strcpy(current_course->course_name, name);
	current_course->grade = grade;
	struct iterator* current_student =  list_begin(grades->students_list);
		while(current_student){
			//checks if the given student already exists
			if (id == (((struct student *)(list_get(current_student)))->id)){
				//checks if the given course already exists
				struct iterator * current_course = list_begin(((struct student*)(list_get(current_student)))->course_list);

				while(current_course){
				if(!(strcmp(((struct course*)( list_get (current_course)))->course_name,name))){
					free((((struct student*)(list_get(current_student)))->course_list));
					return FAIL;
				}
				}
				if(!(list_push_back(((struct student *)
					(list_get(current_student)))->course_list,(void*)current_course)));
				free((((struct student*)(list_get(current_student)))->course_list));
				return 0;
			}
			current_student=list_next (current_student);
		}
	return FAIL;

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

				return FAIL;
		}
	struct iterator* current_node =  list_begin(grades->students_list);
		while(current_node){
			if (id == ((struct student *)(list_get(current_node)))->id){
				student_exist=1;
				*out = (char*) malloc (strlen (((struct student *)
						(list_get(current_node)))->student_name)+1);
				if (!(*out)){
					return FAIL;
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
			return FAIL;
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

					return FAIL;
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
									printf(",");

									}
				}
				current_node=list_next (current_node);
			}
		if(! student_exist){
			return FAIL;
		}
		printf("\n");

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

					return FAIL;
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
