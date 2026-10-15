
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

// Add two polynomials
polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int i, exp;

    result.degree = (a.degree > b.degree)
                    ? a.degree : b.degree;

    for (exp = result.degree; exp >= 0; exp--) {
        float ca = 0, cb = 0;

        if (exp <= a.degree)
            ca = a.coef[a.degree - exp];

        if (exp <= b.degree)
            cb = b.coef[b.degree - exp];

        result.coef[result.degree - exp] = ca + cb;
    }

    return result;
}

// Display a polynomial
void display(polynomial p) {
    int i, exp, printed = 0;
    float c;

    for (i = 0; i <= p.degree; i++) {
        exp = p.degree - i;
        c = p.coef[i];

        if (fabs(c) < 0.00001)
            continue;

        // Print the sign
        if (printed) {
            printf(c > 0 ? " + " : " - ");
        } else if (c < 0) {
            printf("-");
        }

        // Print coefficient
        if (exp == 0 || fabs(c) != 1.0f)
            printf("%.2f", fabs(c));
        else if (exp > 0 && fabs(c) == 1.0f) {
            // Omit coefficient 1 for x terms
        }

        // Print variable and exponent
        if (exp > 0) {
            printf("x");
            if (exp > 1)
                printf("^%d", exp);
        }

        printed = 1;
    }

    if (!printed)
        printf("0");

    printf("\n");
}

// Read a polynomial
polynomial readPolynomial(void) {
    polynomial p;
    int i;

    do {
        printf("Enter degree (0-100): ");
        scanf("%d", &p.degree);
    } while (p.degree < 0 || p.degree > 100);

    printf("Enter coefficients from highest power to constant:\n");

    for (i = 0; i <= p.degree; i++) {
        printf("Coefficient of x^%d: ", p.degree - i);
        scanf("%f", &p.coef[i]);
    }

    return p;
}

int main(void) {
    polynomial a, b, result;

    printf("First polynomial:\n");
    a = readPolynomial();

    printf("\nSecond polynomial:\n");
    b = readPolynomial();

    printf("\nA(x) = ");
    display(a);

    printf("B(x) = ");
    display(b);

    result = add(a, b);

    printf("A(x) + B(x) = ");
    display(result);

    return 0;
}

