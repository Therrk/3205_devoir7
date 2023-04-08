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

float complex_norm(complex in) {
    float out = in.r * in.r + in.im * in.im;
    out = sqrt(out);
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

complex J = {.r = 1.0, .im = 0.0};

