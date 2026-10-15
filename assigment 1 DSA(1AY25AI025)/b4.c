


#include <stdio.h>

#define MAX 100
#define MAX_TERMS 10000

typedef struct {
    int row, col, value;
} term;

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int next_pos[MAX];
    int i, j;
    int num_cols = a[0].col;
    int num_terms = a[0].value;

     
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    // Step 1: Count terms in each column of original matrix
    for (i = 1; i <= num_terms; i++) {
        row_terms[a[i].col]++;
    }

    // Step 2: Calculate starting positions
    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++) {
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];
    }

    // Print arrays before placing terms
    printf("\nrow_terms[]:\n");
    for (i = 0; i < num_cols; i++) {
        printf("%d ", row_terms[i]);
    }

    printf("\nstarting_pos[]:\n");
    for (i = 0; i < num_cols; i++) {
        printf("%d ", starting_pos[i]);
    }
    printf("\n");

    // Preserve starting positions while placing terms
    for (i = 0; i < num_cols; i++) {
        next_pos[i] = starting_pos[i];
    }

    // Step 3: Place terms directly in transposed row-major order
    for (i = 1; i <= num_terms; i++) {
        j = next_pos[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }
}

void print_triples(term a[]) {
    int i;

    printf("Row\tCol\tValue\n");

    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

int main(void) {
    term a[MAX_TERMS + 1];
    term b[MAX_TERMS + 1];

    int rows, cols, value;
    int i, j, k = 1;

    printf("Enter number of rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2 ||
        rows <= 0 || rows > MAX ||
        cols <= 0 || cols > MAX) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");

    a[0].row = rows;
    a[0].col = cols;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (scanf("%d", &value) != 1) {
                printf("Invalid input.\n");
                return 1;
            }

            if (value != 0) {
                if (k > MAX_TERMS) {
                    printf("Too many non-zero elements.\n");
                    return 1;
                }

                a[k].row = i;
                a[k].col = j;
                a[k].value = value;
                k++;
            }
        }
    }

    a[0].value = k - 1;

    printf("\nOriginal matrix triples:\n");
    print_triples(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    print_triples(b);

    printf("\nTriples are already in row-major order.\n");

    return 0;
}

