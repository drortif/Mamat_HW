#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubblesort(int* grades, int size) {
    for(int i =0; i<size-1; i++) {
    	for(int j=0; j<size-i-1; j++) {
    		if(grades[j]>grades[j+1]) {
    			swap(&(grades[j]),&(grades[j+1]));
    		}
    	}
    }
}




float average(int* grades, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += grades[i];
    }

    return (float) (sum) / size;
}

int median(int* grades, int size) {

    return grades[(size + 1) / 2];
}







float pass_percent(int* grades, int size) {
    int pass = 0;
    for (int i = 0; i < size; i++)
    {
        if (grades[i] >= 55) {
            pass++;
        }

    }
    float passrate = (float) pass / size * 100;
    return passrate;
}

void print_histogram(int* grades, int size, FILE* fp_w) {
    int histogram[100] = { 0 };
    for (int i = 0; i < size; i++)
    {
        histogram[grades[i] - 1] ++;

    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(fp_w, "%d ", histogram[(10 * i) + j]);
        }
        if (i < 9) {
            fprintf(fp_w, "\n");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    FILE* fp_w, * fp_r;
    fp_w = fopen("course_statistics.txt", "w");
    fp_r = fopen(argv[1], "r");
    int num_of_students = atoi(argv[2]);
    int* grades = (int*)malloc(sizeof(int) * num_of_students);

    for (int i = 0; i < num_of_students; i++) {
        fscanf(fp_r, "%d", grades + i);
    }
    bubblesort(grades,num_of_students);


    fprintf(fp_w, "num of students = %d\n", num_of_students);

    fprintf(fp_w, "avg = %.3f\n", average(grades, num_of_students));

    fprintf(fp_w, "the median is - %d\n", median(grades, num_of_students));

    fprintf(fp_w, "max grade = %d", grades[num_of_students-1]);

    fprintf(fp_w, ", min grade = %d\n", grades[0]);

    fprintf(fp_w, "pass rate = %.2f%%\n", pass_percent(grades, num_of_students));

    print_histogram(grades, num_of_students, fp_w);

    fclose(fp_w);
    fclose(fp_r);
    free(grades);
    return 0;
}
