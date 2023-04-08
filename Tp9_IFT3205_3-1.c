/*------------------------------------------------------*/
/* Prog    : Tp9_IFT3205.c                              */
/* Auteur  : Élie Leblanc, Justin Veilleux              */
/* Date    : --/--/2010                                 */
/* version :                                            */ 
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/
// elie.leblanc@umontreal.ca justin.veilleux@umontreal.ca

/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionDemo9.h"
#include "complex.c"

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/   
/*------------------------------------------------*/
#define NAME_VISUALISER_IMG "./display "
#define NAME_VISUALISER     "./ViewSig.sh "

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/

void apply_the_filter(float * signal_r, int length) {
    float * signal_i = malloc(sizeof(float) * length);
    float * signal_r_copy = malloc(sizeof(float) * length);
    float * signal_i_copy = malloc(sizeof(float) * length);

    for (int i = 0;i < length;i++) {
        signal_i[i] = 0.0;
        signal_r_copy[i] = 0.0;
        signal_i_copy[i] = 0.0;
    }

    dft(signal_r, signal_i, signal_r_copy, signal_i_copy, length, 0);
    

    for (int i = 0;i < length;i++){

        complex z = complex_exp(complex_mul(r2c(- 2.0 * PI * (float)i / (float)length), J));

        
        complex x = {.r = signal_r_copy[i], .im = signal_i_copy[i]};

        complex y = complex_mul(complex_add(r2c(1.0),
                                            complex_mul(r2c(-2.0),
                                                        complex_inv(z))),
                                complex_add(r2c(1.0),
                                            complex_mul(r2c(-1.0/3.0),
                                                        complex_inv(z))));

        y = complex_mul(x, z);
        signal_r_copy[i] = y.r;
        signal_i_copy[i] = y.im;
    }

    dft(signal_r_copy, signal_i_copy, signal_r, signal_i, length, 1);
    free(signal_i);
    free(signal_i_copy);
    free(signal_r_copy);
}




/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/                     
/*------------------------------------------------*/
int main(int argc,char **argv)
{



    // Dirac

    int length = 100;

    float * signal_r = malloc(sizeof(float) * length);
    for (int i = 0;i < length;i++) {
        signal_r[i] = 0.0;
    }

    signal_r[0] = 1.0;

    apply_the_filter(signal_r, length);
    SaveSignalDat("dirac_transmitted", signal_r, length);
    

    for (int i = 0;i < length;i++){
        signal_r[i] = 1.0;
    }

    for (int i = 0;i < 5;i++) {
        signal_r[i] = 0.0;
    }

    apply_the_filter(signal_r, length);
    SaveSignalDat("step_transmitted", signal_r, length);

    return 0; 	 
}


