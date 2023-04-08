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

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/   
/*------------------------------------------------*/
#define NAME_VISUALISER_IMG "./display "
#define NAME_VISUALISER     "./ViewSig.sh "

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/

/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/                     
/*------------------------------------------------*/
int main(int argc,char **argv)
 {
  int i,j;
  char BufSystVisuSig[100];
  int length;

  //===============================
  //Question 1
  //===============================

   float* SignR=LoadSignalDat("Sound_degraded",&length);
   float* SignI=fmatrix_allocate_1d(length);
   float* SignR_Trans=fmatrix_allocate_1d(length);
   float* SignI_Trans=fmatrix_allocate_1d(length);
   float cos_theta = cos(500*2*PI/11025);
   float rho =0.99;
   float num_R, num_I, denum_R, denum_I;
   float new_Value_R, new_Value_I;

   dft(SignR,SignI,SignR_Trans,SignI_Trans,length,0);
   
   for (i = 0; i < length-2; i++) {
	   // new_Value_R = SignR_Trans[i]-2*cos_theta*SignR_Trans[i+1]+SignR_Trans[i+2];
	   // new_Value_I = SignI_Trans[i]-2*cos_theta*SignI_Trans[i+1]+SignI_Trans[i+2];
      // SignR_Trans[i] = new_Value_R;
      // SignI_Trans[i] = new_Value_I;
      num_R = 1-2*cos_theta*SignR_Trans[i+1]+SignR_Trans[i+2];
      denum_R = 1/(1-2*rho*cos_theta*SignR_Trans[i+1]+pow(rho,2)*SignR_Trans[i+2]);
      num_I = 1-2*cos_theta*SignI_Trans[i+1]+SignI_Trans[i+2];
      denum_I = 1/(1-2*rho*cos_theta*SignI_Trans[i+1]+pow(rho,2)*SignI_Trans[i+2]);
      new_Value_R = SignR_Trans[i]*num_R*denum_R-SignI_Trans[i]*num_I*denum_I;
      new_Value_I = SignI_Trans[i]*num_R*denum_R+SignR_Trans[i]*num_I*denum_I;
      SignR_Trans[i]=new_Value_R;
      SignI_Trans[i]=new_Value_I;
   }
   num_R = 1-2*cos_theta*SignR_Trans[length-1];
   denum_R = 1/(1-2*rho*cos_theta*SignR_Trans[length-1]);
   num_I = 1-2*cos_theta*SignI_Trans[length-1];
   denum_I = 1/(1-2*rho*cos_theta*SignI_Trans[length-1]);
   new_Value_R = SignR_Trans[length-2]*num_R*denum_R-SignI_Trans[length-2]*num_I*denum_I;
   new_Value_I = SignI_Trans[length-2]*num_R*denum_R+SignR_Trans[length-2]*num_I*denum_I;
   SignR_Trans[length-2]=new_Value_R;
   SignI_Trans[length-2]=new_Value_I;
    // new_Value_R = SignR_Trans[length-2]-2*cos_theta*SignR_Trans[length-1];
    // new_Value_I = SignI_Trans[length-2]-2*cos_theta*SignI_Trans[length-1];
      // SignR_Trans[i] = new_Value_R;
      // SignI_Trans[i] = new_Value_I;
   
   dft(SignR_Trans,SignI_Trans,SignR,SignI,length,1);
   
   //Sauvegarde en fichier .dat
   SaveSignalDatWav("Sound_restored",SignR,length,11025);

   //Visu Ecran
   strcpy(BufSystVisuSig,NAME_VISUALISER);
   strcat(BufSystVisuSig,"Sound_restored.dat&");
   printf(" %s",BufSystVisuSig);
   system(BufSystVisuSig);

   //---------------------------------------------
   //Sauvegarde de SignZ (30000 echantillons 
   //al�atoire entre [0::200]) dans un 
   //fichier .wav avec une periode 
   //d'echantillonnage de 10000: Nb echant/secondes
   //(pour 3 secondes d'�coute)
   //----------------------------------------------
   //----------------------------------------------
   if (0)
      {
       length=30000;
       float*  SignZ=fmatrix_allocate_1d(length);
       for(i=0;i<length;i++) SignZ[i]=(int)(((float)rand()/RAND_MAX)*200.0);
       SaveSignalDatWav("SignalZ",SignZ,length,10000);
      }
     

     //Rappel -Pour Lecture/Sauvegarde/Visu [Fichier Son]
     //=================================================
     //float*  SignIn=LoadSignalDat("NameSignalIn",&length);
     //SaveSignalDat("NameSignalOut",SignIn,length); 
     //strcpy(BufSystVisuSig,NAME_VISUALISER);
     //strcat(BufSystVisuSig,"NameSignalOut.dat&");
     //printf(" %s",BufSystVisuSig);
     //system(BufSystVisuSig);
  
 
  //==End=========================================================

  //retour sans probleme
  printf("\n C'est fini ... \n\n");
  return 0; 	 
}


