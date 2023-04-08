#include <math.h>
#include <stdio.h>

typedef struct complex {
    float r;
    float im;
} complex;

complex complex_mul(complex a, complex b) {
    complex out;
    out.r = a.r * b.r - a.im * b.im;
    out.im = a.r * b.im + a.im * b.r;
    return out;
}

complex complex_exp(complex in) {
    // ex+iy = excosy+iexsiny

    complex out;
    out.r = exp(in.r) * in.im;
    out.im = exp(in.r) * sin(in.im);
    return out;
}

complex complex_inv(complex in) {
    complex out;
    float norm2 = in.im*in.im + in.r*in.r;
    out.r = in.r / norm2;
    out.im = - in.im / norm2;
    return out;
}

complex r2c(float r) {
    complex out = {.r = r, .im = 0.0};
    return out;
}

complex complex_neg(complex in) {
    complex out = {.r = -in.r, .im = -in.im};
    return out;
}

complex complex_add(complex a, complex b) {
    complex out = {.r = a.r + b.r, .im = a.im + b.im};
    return out;
}

complex J = {.r = 0.0, .im = 1.0};

void complex_print(complex n) {
    printf("%f + %fim", n.r, n.im);
}
