/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include <stdio.h>          
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */


///-------------------------------TP3----------------------------------///
//                                                                      //
//                Simulation de Monte Carlo : Approximation de Pi       //
//                                                                      //
//----------------------------------------------------------------------//


//----------------------------------------------------------------------//
// affiche_tableau : affiche les éléments d'un tableau                  //
//                                                                      //
// Entree :  un tableau contenant de longs floats et sa taille          //
//                                                                      //
// sortie :  affiche les differentes valeurs contenu dans ce tableau    //
//----------------------------------------------------------------------// 
void affiche_tableau(double * Tableau, int taille)
{
    int i;

    for(i = 0; i < taille; i++)
    {   
        if(i % 4 == 0) { printf("\n"); } // saute la ligne apres avoir affiché
                                         // 4 valeurs
        printf("%lf\t",Tableau[i]);
    }
}

//----------------------------------------------------------------------//
// simulpi :   Simulation de la valeur de PI                            //
//                                                                      //
// Entree  : nbr_pt : le nombre de points pour l'estimation de PI       //
//                                                                      //
// Sortie  : Une valeur approchée de PI  en double precision            //                                                       
//----------------------------------------------------------------------//

double simulPi(long nbr_pt)
{
	int         i;
    double      xr;
    double      yr;  
	double      nbr_pt_Disk = 0;


    // test pour une valeur de n
	for(i = 0; i < nbr_pt ; i++)
	{
        // tirages generant les coordonnées
		xr = genrand_real2();
		yr = genrand_real2();

		if(xr*xr + yr*yr < 1) nbr_pt_Disk ++;
	}
      
           // transtypage des entiers en doubles sous linux
	return 4.0 * nbr_pt_Disk / (1.0 * nbr_pt);
}

//----------------------------------------------------------------------//
// Tableau_experience_Pi :  Un tableau                                  //
//                                                                      //
// Entree : nb_exper : nombre d'experiences faisant appel à la fonction //
//                     simulPi                                          //
//          nb_point :  nombre de points pour l'estimation de Pi        //
//                                                                      //
// sortie : Renvoie un tableau contenant les differentes approximations //
//          de  Pi                                                      //
//----------------------------------------------------------------------//

double * Tableau_experience_Pi( int nb_exper, int nb_point )
{   

    double     *Table_exper = NULL;
    int        i = 0;

    Table_exper = malloc(sizeof(double)*nb_exper);

    // Differentes approximation de Pi
    for(i = 0 ; i < nb_exper; i++)
    {
        Table_exper[i] = simulPi(nb_point);
    }

    return Table_exper;
}

//----------------------------------------------------------------------//
// Moyenne :                 Calcule la moyenne                         //
//                                                                      //
// Entree : Tableau_exper_Pi : tableau contenant les valeurs de Pi pour //
//                             differentes experiences                  //
//         taille : la tableau du tableau Tableau_exper_Pi              //
//                                                                      //
// sortie : Renvoie la moyenne des valeurs de Pi du tableau             //
//----------------------------------------------------------------------//

double Moyenne( double * Tableau_exper_Pi, int taille )
{
    int        i = 0;
    double     sum_val_exp = 0; 
    
    for(i = 0; i < taille; i++)
    {
        sum_val_exp += Tableau_exper_Pi[i];
    }
    
    // transtypage de l'entier en double sous linux
    return sum_val_exp / ( 1.0 * taille );
}

//----------------------------------------------------------------------//
// Estimate_variance : calcule l'estimation sans biais de la variance   //
//                                                                      //
// Entree : Tableau_exper_Pi : un tableau contenant tous les resulstats //
//                             des evenements la fonction simulPi       //
//          taille           : la taille du tableau Tableau_exper_Pi    //
//          moy              : la moyenne des valeurs de Pi du tableau  //
//                                                                      //
// sortie : la valeur de l'estimation de la variance                    //
//----------------------------------------------------------------------//

double Estimate_variance( double * Tableau_exper_Pi, int taille, double moy) 
{
    int       i = 0;
    double    sum_car = 0;

    for(i = 0; i < taille ; i++)
    {
        sum_car += (moy - Tableau_exper_Pi[i])*(moy - Tableau_exper_Pi[i]);
    }

    //transtypage d'entier taille en double
    return sum_car / (1.0 * (taille - 1)); // avec un tableau de taille >= 2 

}

//----------------------------------------------------------------------//
// Valeur_t : Donne la valeur de la constante t pour la loi de Student  //
//            pour a = 0.05 en fonction du nombre d'experiences         //
// Entree : nbr_exper : le nombre d'exepriences de la fonction simulPi  //
//                                                                      //
// sortie : Renvoie la valeurd la constante t                           //
//----------------------------------------------------------------------//

double Valeur_t(int nbr_exper)
{
    double Tableau_va_t[34] = {12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365,
                                2.308, 2.262, 2.228, 2.201, 2.179, 2.160, 2.145, 
                                2.131, 2.120, 2.110, 2.101, 2.093, 2.086, 2.080, 
                                2.074, 2.069, 2.064, 2.060, 2.056, 2.052, 2.048,
                                2.045, 2.042, 2.021, 2.000, 1.980, 1.960      };
    
    // Pour nbr_exper > 34, t = 1.960
    if( nbr_exper > 33 ) { return Tableau_va_t[33] ; }
    
    return Tableau_va_t[nbr_exper - 1];
}


//----------------------------------------------------------------------//
// Intervalle : calcule les bornes de l'intervalle de confiance         //
//                                                                      //
// Entree : estimate_var : une estimation sans biais de la variance     //
//                         correspondant au nombre d'experiences        //
//          moy          : la moyenne des valeurs de Pi                 //
//          nbr_exper    : le nombre d'experiences executées            //
//                                                                      //
// sortie : Renvoie un tableau de taille 2 contenant les bornes de      //
//          l'intervalle de confiance                                   //
//----------------------------------------------------------------------//

double * Intervalle(double estimate_var, double moy, int nbr_exper) 
{   

    double      R_val;
    double      *borne = calloc(2,sizeof(double));
    
    // Calcul de la marge d'erreur
    R_val = sqrt( estimate_var / (nbr_exper)) * Valeur_t(nbr_exper); 

    borne[0] = moy - R_val; 
    borne[1] = moy + R_val; 

    return borne;
}

//--------------ce programme est independant des autres----------------//

//----------------------------------------------------------------------//
// Autre_approximation_Pi : Donne une approximation de Pi               //
//                                                                      //
// Entree : val_max_entier : l'entier maximale pour la somme            //
//                                                                      //
// sortie : Renvoie une valeur approchée de la constante Pi             //
//----------------------------------------------------------------------//

double Autre_approximation_Pi(int val_max_entier)
{
    int         i;
    float       som_inv_car_ent;

    for(i = 1; i <= val_max_entier; i++)
    {   
        som_inv_car_ent += 1/ (1.0 * i * i); //la somme des carrés des inverses
    }                                        // des nombres entiers
    return sqrt(6 * som_inv_car_ent);
}

//----------------------------------Test---------------------------------//
int main(void)
{

    // Declaration et initialisation des variables utiles
    int      nbr_pt;
    int      nbr_exp;
    int      choix;
    int      nbr_tests;
    int      nbr_chiffres;
    int      val_max_entier;
    double   *Tab_exp_Pi = NULL;
    double   *intervalle;
    double   var;
    double   moy;
    double   err_absol;
    double   err_relat;
    
    printf("Quels nombres de tests voulez-vous effectuer ?\t");
    scanf("%d",&nbr_tests);

    printf("\n\nNombre de points pour la simulation :\n\t nombre_point = ");
    scanf("%d",&nbr_pt);
    // ce nombre etant utile pour tous les programmes, 
    // doit être demandé au debut
    

    //------------------------interface utilisateur---------------------------//

    // Choix possibles pour l'utilisateur//
    printf("\n1) Simulation de PI \n");
    printf("2) Expriences de simulation de PI\n");
    printf("3) Calcul de la Moyenne\n");
    printf("4) Calcul de l'estimateur sans biais de la variance\n");
    printf("5) Calcul de l'intervalle de confiance et de la marge d'erreur\n");
    printf("6) Comparaison de la moyenne des estimations de PI\n");
    printf("7) Autre approximation de PI\n");
        
    while( nbr_tests != 0 )
    {
        printf("\n\tFaire un choix\n");
        scanf("\t%d",&choix);

        switch (choix) {
        case 1:
            printf("Une approximation de Pi est : %lf\n\n",simulPi(nbr_pt));
        break;

        case 2:
            printf("Nombre d'experiences :\n\t nombre_experience = "); 
            scanf("%d",&nbr_exp);

            Tab_exp_Pi = Tableau_experience_Pi(nbr_exp, nbr_pt);
        
            printf("Les resultats des simulations sont : \n");
            affiche_tableau(Tab_exp_Pi, nbr_exp);
        break;

        case 3:
            printf("Nombre d'experiences :\n\t nombre_experience = "); 
            scanf("%d",&nbr_exp);

            Tab_exp_Pi = Tableau_experience_Pi(nbr_exp, nbr_pt);
        
            moy = Moyenne(Tab_exp_Pi, nbr_exp);
            printf("la moyenne des approximations de PI est : \n\t%lf",moy); 
        break;

        case 4:
            printf("Nombre d'experiences :\n\t nombre_experience = "); 
            scanf("%d",&nbr_exp);

            Tab_exp_Pi = Tableau_experience_Pi(nbr_exp, nbr_pt);
        
            moy = Moyenne(Tab_exp_Pi, nbr_exp);
            var = Estimate_variance(Tab_exp_Pi, nbr_exp, moy);
            printf("l'estimation sans biais de la variance est :\n\t%lf",var);
        break;

        case 5:
            printf("Nombre d'experiences :\n\t nombre_experience = "); 
            scanf("%d",&nbr_exp);

            Tab_exp_Pi = Tableau_experience_Pi(nbr_exp, nbr_pt);
        
            moy = Moyenne(Tab_exp_Pi, nbr_exp);
            var = Estimate_variance(Tab_exp_Pi, nbr_exp, moy);

            intervalle = Intervalle(var, moy, nbr_exp);
            printf("\nl'intervalle de confiance est :\n\t [%lf, %lf]\n", intervalle[0], intervalle[1]); 
            printf("\nLa marge d'erreur est : \t%lf \n",intervalle[1] - moy);
        break;
    
        case 6:
            // calcul d'erreurs pour un nombre donné de simulations
            printf("Nombre d'experiences :\n\t nombre_experience = "); 
            scanf("%d",&nbr_exp);

            Tab_exp_Pi = Tableau_experience_Pi(nbr_exp, nbr_pt);
            moy = Moyenne(Tab_exp_Pi, nbr_exp);

            err_absol = M_PI - Moyenne(Tab_exp_Pi, nbr_exp);
            err_relat = ( err_absol / M_PI ) * 100; // pour ramener le resulat en pourcentage
            printf("L'erreur absolue pour moyenne(Pi) = %lf est  : %lf\n",moy,err_absol);
            printf("L'erreur relative pour moyenne(Pi) = %lf est : %lf %%\n",moy,err_relat);

            if ( fabs(err_relat) < 0.0001 ) printf("\nVotre valeur est assez bonne");
            else printf("\nVous devez changer le nombre de points pour avoir une bonne approximation");
        break;
        case 7 :

            printf("la valeur maximale des entiers : ");
            scanf("%d",&val_max_entier);
       
            printf("\n une valeur approchée de Pi est :%f\n", Autre_approximation_Pi(val_max_entier)); 
        break;
        }
    nbr_tests --;
    printf("\n--------------------------------------------------------------\n");
    }
    printf("\n-----------------------------Fin du test-----------------------------\n");
}
