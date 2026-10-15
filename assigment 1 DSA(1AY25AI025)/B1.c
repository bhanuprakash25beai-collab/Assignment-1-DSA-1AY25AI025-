#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

int main() {
    struct Student *ptr, *temp;
    int n, i, add;
    float sum = 0, average;
    int topper = 0;
    char choice;

    // Read number of students
    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    // Dynamically allocate memory
    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read student records using pointer arithmetic
    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr + i)->roll_no,
              (ptr + i)->name,
              &(ptr + i)->marks);
    }

    // Calculate average and find topper
    sum = 0;
    for (i = 0; i < n; i++) {
        sum += (ptr + i)->marks;

        if ((ptr + i)->marks > (ptr + topper)->marks) {
            topper = i;
        }
    }

    average = sum / n;

    printf("\nAverage marks: %.2f\n", average);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           (ptr + topper)->name,
           (ptr + topper)->roll_no,
           (ptr + topper)->marks);

    // Ask whether to add two more students
    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        temp = (struct Student *)realloc(
            ptr, (n + 2) * sizeof(struct Student));

        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            free(ptr);
            return 1;
        }

        ptr = temp;

        for (i = n; i < n + 2; i++) {
            printf("Enter roll, name, marks: ");
            scanf("%d %19s %f",
                  &(ptr + i)->roll_no,
                  (ptr + i)->name,
                  &(ptr + i)->marks);
        }

        // Recalculate average and topper
        sum = 0;
        topper = 0;

        for (i = 0; i < n + 2; i++) {
            sum += (ptr + i)->marks;

            if ((ptr + i)->marks > (ptr + topper)->marks) {
                topper = i;
            }
        }

        average = sum / (n + 2);

        printf("\nUpdated average marks: %.2f\n", average);
        printf("Updated topper: %s (Roll %d, Marks %.2f)\n",
               (ptr + topper)->name,
               (ptr + topper)->roll_no,
               (ptr + topper)->marks);
    }

    // Free dynamically allocated memory
    free(ptr);

    return 0;
}
