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

//------------------------------------------------------------------//
//                                                                  //
//          Definition et initialisation des structures             //
//                                                                  //
//------------------------------------------------------------------//
struct male
{
    int  *   mois; // permet de recuperer des informations sur le nombre de 
                   // lapins en fonction des mois
    int  *   age;  // permet de recuperer l'age des lapins
};

struct femelle
{
    int  *   mois;
    int  *   age;
};

//--------------------------------------------------------------------//
// Simul_Fibonacci : Simule rapidement l'accroissement des lapins     //
//                                                                    //
// Entree : Nbr_mois : le nombre de mois d'observation                //
// Sortie : Renvoie un tableau contenant le nombre de lapins en fon-  // 
//          ction des mois                                            //
//--------------------------------------------------------------------//

int * Simul_Fibonacci(int Nbr_mois)
{   
    int     i;
    int  *  Tab;

    Tab = malloc(sizeof(int) * Nbr_mois);

    for(i = 0; i < Nbr_mois + 1; i++)
    {
        if      (i == 0 || i == 1) Tab[i] = 1;
        else    Tab[i] = Tab[i - 1] + Tab[i - 2];
    }
    return Tab;
}

//-------------------------------------------------------------------//
// Somme : Calcule la somme de certains elements d'un tableau        //
// Entrée : Tableau : Le tableau dont nous voulons additionner les   //
//                    elements                                       //
//          inf et sup : les bornes inferieure et superieure des     //
//          des indices des elements du tableau pour la somme        //
// Sortie : Renvoie la valeur de la somme des elements du tableau    //
//          dont l'indice est entre inf et sup                       //
//-------------------------------------------------------------------//
int Somme(int * Tableau, int inf, int sup)
{
    int     i;
    int     resultat = 0;

    for(i = inf; i < sup; i++)
    {
        resultat += Tableau[i];
    }
    return resultat;
}

//-------------------------------------------------------------------//
// Affiche : Affiche les elements d'un tableau                       //
// Entrée : Tableau : Le tableau à afficher les elements             //
//          taille  : la taille dudit tableau                        //
// Sortie : affiche tous les elements du tableau
//-------------------------------------------------------------------//

void affiche(int * Tableau, int taille)
{
    int     i;

    for(i = 0; i < taille; i++)
    {
        if(i%11 == 0 && i != 0) printf("%d\n\t",Tableau[i]);
        else                   printf("%d\t",Tableau[i]);
    }
    printf("\n");
}

void affiche_float(float* Tableau, int taille)
{
    int     i;

    for(i = 1; i < taille; i++)
    {
        if(i%3 == 0 && i != 0) printf("%f\n",Tableau[i]);
        else printf("%f\t",Tableau[i]);
    }
    printf("\n");
}


//-------------------------------------------------------------------//
// nombre_lapereaux : Determine le nombre de lapereaux par portées   //
// aucune entrée                                                     //
// Sortie : Renvoie un nombre compris entre 3 et 6 avec la même      //
//          probabilité                                              //
//-------------------------------------------------------------------//
int nombre_lapereau()
{
    int resultat;
    double proba;
    double alea_nbr;

    //proba    = 1.0/4;
    alea_nbr = genrand_real1();

    if     (alea_nbr < 1.0/4) resultat = 3;
    else if(alea_nbr < 2.0/4) resultat = 4;
    else if(alea_nbr < 3.0/4) resultat = 5;
    else                      resultat = 6;
    
    return resultat;
}

//-------------------------------------------------------------------//
// nombre_de_portee : Determine le nombre de portée pour une année   //
// aucune entrée                                                     //
// Sortie : Renvoie un nombre compris entre 4 et 8 avec des probabi- //
//          lités differentes                                        //
//-------------------------------------------------------------------//

int nombre_de_portee()
{
    int      resultat; // les resultats possibles sont {4,5,6,7,8}
    double   alea_nbr;       

    // 1/4 est la probabilité d'avoir des resultats dans {5,6,7}
    // 1/8 est la probabilité d'avoir des resultats dans {4,8}

    alea_nbr = genrand_real1();
    if      (alea_nbr < 1.0/8)    resultat = 4;
    else if (alea_nbr < 1.0/4)    resultat = 8;
    else if (alea_nbr < 1.0/2)    resultat = 5;
    else if (alea_nbr < 3.0/4)    resultat = 6;
    else                          resultat = 7;

    return resultat;
}

//-------------------------------------------------------------------//
// Sexe   : Determine le nombre de males et de femelles par portée   //
// Entrée : nbr_lapereaux : le nombre de lapereaux                   //
// Sortie : Renvoie un tableau de taille 2 contenant le nombre de    //
//          male et de femelle                                       //
//-------------------------------------------------------------------//

int * Sexe(int nbr_lapereaux)
{
    int i;
    int *resultat;
    double alea_nbr;    
    
    resultat = calloc(2, sizeof(int));
    for(i = 0; i < nbr_lapereaux; i++)
    {
        alea_nbr = genrand_real1(); 
        if (alea_nbr < 0.5) resultat[0] ++;
        else                resultat[1] ++;
    }
    return resultat;
}

//-------------------------------------------------------------------//
// Mort : Permet selon certains criteres de retirer des lapins       // 
// (morts) après chaque fin d'année                                  //
// Entrée : Tableaux : Le tableau contenant le nombre de lapins par  //
//                     année                                         //
//          annee    : le nombre d'année                             //
// Sortie : renvoie un tableau contenant les lapins vivants          //
//-------------------------------------------------------------------//

int * Mort(int * Tableau, int taille)     // durant tout le programme, les cases 
{                                         // du tableau representeront les ages  
    int       i;                          // des lapins et taille sera l'année
    int       j;                          // de realisation de l'experiences
    int    *  Tab = calloc(taille, sizeof(int));
    double    Nbr_aleat;

    Tab = Tableau; 
    
    //--------MORT DES LAPEREAUX----------//      // peu importe l'année, les 
    for(j = 0; j < Tableau[taille - 1]; j++)      // lapereaux ont la même pro-
     {                                            // babilité de survie.
        Nbr_aleat = genrand_real1();              // Nous avons p = 0.35
        if(Nbr_aleat > 0.35) Tab[taille - 1] --;
     }
    
    //-------PREMIER CAS : MORT DES ADULTES------//
    if(taille < 11)
    {
        for(i = 0; i < taille - 1; i++)
        {
            for(j = 0; j < Tableau[i]; j++)     // Et p = 0.6 la probabilité 
            {                                   // pour un lapin entre 1 et 10
                Nbr_aleat = genrand_real1();    // ans de survivre
                if(Nbr_aleat > 0.60) Tab[i] --;
            }
        }                                        
    }                                           
                                                 
    //-----SECOND CAS : MORT DES ADULTES-----//
    else if(taille > 16)
    {                                          
        //----LES MOINS DE 11 ANS---//             
        for(i = taille - 10; i < taille - 1; i++)    
        {                                     
            for(j = 0; j < Tableau[i]; j++)
            {                                                               
                Nbr_aleat = genrand_real1();  
                if(Nbr_aleat > 0.60) Tab[i] --;    
            }                                   
        }                                    
        //----LES ENTRE 10 ET 15 ANS---//
        for(i = taille - 16; i < taille - 10; i++)
        {                                     // Dans cette partie, la decroi-
            for(j = 0; j < Tableau[i]; j++)   // ssance de la probabilité de sur
            {                                 // vie est donnée par
                Nbr_aleat = genrand_real1();  //p = 0.1 * (16 - année - age)
                if(Nbr_aleat > 0.1 * (i - taille + 16)) Tab[i] --;
            }
        }
        //---LES PLUS DE 15 ANS---//
        for(i = 0; i < taille - 15; i++)
        {
            Tab[i] = 0;
        }
    }

    else 
    {
        //---MORT DES ENTRE 10 ET 15 ANS---//
        for(i = 0; i < taille - 10; i++)
        {                                     // de même, pour cette par, elle
            for(j = 0; j < Tableau[i]; j++)   // est donnée par
            {                                 // p = 0.6 - 0.1*(année - age -10)
                Nbr_aleat = genrand_real1();
                if(Nbr_aleat > 1.6 - 0.1 * (taille - i)) Tab[i] --;
            }
        }
        //-------MORT DES MOIS DE 10 ANS-------//
        for(i = taille - 10; i < taille - 1; i++)
        {
            for(j = 0; j < Tableau[i]; j++)
            {
                Nbr_aleat = genrand_real1();
                if(Nbr_aleat > 0.60) Tab[i] --;
            }
        }
    }    
    return Tab;
}

//-------------------------------------------------------------------//
// Taux_de_croissance : Permet de calculer les taux de croissance    // 
//                   des lapins entre l'année de depart et l'année t //
// Entrée : Nbr_popu1 : la population total à l'instant initial      //
//          Nbr_popu2 : la population total à l'instant t            //
//          annee     : l'année t                                    //
// Sortie : renvoie un tableau contanant les taux de croissance con- //
//          tinue et non continue                                    //
//-------------------------------------------------------------------//

float * Taux_de_croissance(int Nbr_popu1, int Nbr_popu2, int annee)
{
    float  *  Tableau = calloc(2, sizeof(int));

    Tableau[0] = 1.0 / (annee - 1) * log(1.0 * Nbr_popu2 / Nbr_popu1) * 100;
    Tableau[1] = pow((1.0 * Nbr_popu2 / Nbr_popu1), 1.0 / (annee - 1)) - 1;

    return Tableau;
}

//--------------------------FONCTION PRICIPALE--------------------------------//

int main()
{
    //------------Declaration des variables------------//

    int      i;
    int      j;
    int      k;
    int      Nbr_Femelle;
    int      Nbr_Male;
    int      Nbr_lapins_vivants;
    int      annee;
    int      Nbr_mois;
    int      nbr_porte;
    int      Nbr_aleat;
    int      nbr_lapereaux;
    int      choix;
    int      test;
    int   *  Tableau_Annee_Fibo;
    int   *  sexe;
    int   *  Total_femelle;
    float *  fact_de_Croi;


    struct   male Male;
    struct   femelle Femelle;

    printf("Combien de tests voulez-vouz faire?\t");
    scanf("%d",&test);
        
    while(test != 0)
    {
       printf("\nEntrez le nombre d'années\n Nombre_année = ");
       scanf("%d",&annee);

       //---------------Allocation de memoire : Tableau des ages--------------//
       Male.age = calloc(annee, sizeof(int));
       Femelle.age = calloc(annee, sizeof(int));
       //---------------Allocation de memoire : Tableau des naissances--------//
       Male.mois = calloc(12, sizeof(int));
       Femelle.mois = calloc(12, sizeof(int));

       Total_femelle = calloc(annee, sizeof(int));
       Tableau_Annee_Fibo = calloc(annee, sizeof(int));
       fact_de_Croi = calloc(annee, sizeof(float));

       printf("\n1 ) Simulation rapide de l'accroissement des lapins\n");
       printf("2 ) Simulation plus realiste de l'accroissement des lapins\n");
       printf("\n Faire un choix \t");
       scanf("%d",&choix);
    
       switch(choix)
       {
         case 1:
  
            printf("\nEntrez le nombre de mois\n Nombre_mois  = "); 
            scanf("%d",&Nbr_mois);   
            affiche(Simul_Fibonacci(Nbr_mois), Nbr_mois);
            for(i = 0; i < annee; i++)
            {
                Tableau_Annee_Fibo[i] = Simul_Fibonacci(12*annee + 1)[12*i + 11];
            }
            printf("\n Nombre total de couples par année\n\t");
            affiche(Tableau_Annee_Fibo, annee);
           break;

         case 2: 
            
            printf("\nNombre initial de femelles : ");
            scanf("%d",&Femelle.age[0]);
            printf("Nombre initial de mâles : ");
            scanf("%d",&Male.age[0]);
            printf("L'evolution de la population des femelles par année et \n");
            printf("par mois. Le premier tableau represente l'evolution de la");
            printf("population par année et celui du bas par mois\n");

            //-------------INITIALISATION ET PREMIERES NAISSANCES-------------//
            
            Total_femelle[0] = Femelle.age[0];

            printf("\n%d : \t", 1);
            affiche(Femelle.age, 1);
            printf("%d : \t", 1);
            affiche(Femelle.mois, 12);

            //------------PREMIERE NAISSANCE-----------//
            for(j = 0; j < Femelle.age[0]; j++)
            {
                nbr_porte = nombre_de_portee();
                for(k = 0; k < nbr_porte; k++)
                {
                    Nbr_aleat = genrand_real1() * 12;
                    sexe = Sexe(nombre_lapereau());
                    Femelle.mois[Nbr_aleat] += sexe[0];
                    Male.mois[Nbr_aleat] += sexe[1];
                }
            }

            Male.age[1] = Somme(Male.mois, 0, 12) - Male.age[0];
            Femelle.age[1] = Somme(Femelle.mois, 0, 12) - Femelle.age[0];
            
            //---------------------PREMIERS MORTS---------------------//
            
            Femelle.age = Mort(Femelle.age, 2);
            Male.age = Mort(Male.age, 2);
            Total_femelle[1] = Somme(Femelle.age, 0, 2);
            fact_de_Croi[0] = 1.0 * Total_femelle[0] / Total_femelle[1];

            printf("\n%d : \t", 2);
            affiche(Femelle.age, 2);
            printf("%d : \t", 2);
            affiche(Femelle.mois, 12);
            printf("\n");
            //---------NAISSANCES DES LAPINS-----------//

            for(i = 2; i < annee; i++)
            {
                Nbr_Femelle = 0;
                Nbr_Male = 0;

                for(j = 0; j < Somme(Femelle.age, 0, i - 1); j++) // Nombre de 
                {                                                 // femelles en
                    nbr_porte = nombre_de_portee();               // age de re-
                    for(k = 0; k < nbr_porte; k++)                // production
                    {
                        Nbr_aleat = genrand_real1() * 12;  // determine les mois
                        nbr_lapereaux = nombre_lapereau(); // pour les portées
                        sexe = Sexe(nbr_lapereaux);

                        Femelle.mois[Nbr_aleat] += sexe[0]; // Repartition des 
                        Male.mois[Nbr_aleat] += sexe[1];    // naissances dans 
                                                            // les mois
                        Nbr_Male += sexe[0];                
                        Nbr_Femelle += sexe[1];
                    }
                }
                Male.age[i] = Nbr_Male;
                Femelle.age[i] = Nbr_Femelle;

                //------------MORT DES LAPINS--------------//

                Femelle.age = Mort(Femelle.age, i + 1);
                Male.age = Mort(Male.age, i + 1);                
                //--AFFICHAGE DE L'EVOLUTION DE LA POPULATION DES FEMLELLES--//

                printf("%d : \t", i + 1);
                affiche(Femelle.age, i + 1);
                printf("%d : \t", i + 1);
                affiche(Femelle.mois, 12);
 
                printf("\n\n");
                Total_femelle[i] = Somme(Femelle.age, 0, i + 1); 
                
                fact_de_Croi[i - 1] = 1.0 * Total_femelle[i - 1] / Total_femelle
                                                                            [i];               
            }
            fact_de_Croi[annee - 1] = 1.0 * Total_femelle[annee - 2] / 
                                                       Total_femelle[annee - 1];
            printf("la vieé\n");           
            affiche(Total_femelle, annee);
            printf("la vie\n");            
            //-----------FACTEUR D'ACCROISSEMENT DE LA POPULATION-------------//
            printf("\nLes rapports des nombres totaux des femelles de deux ann");
            printf("ées consecutives sont \n");
            affiche_float(fact_de_Croi, annee);
            
            //-----------------EVOLUTION DE LA POPULATION---------------------//
            nbr_lapereaux = (Male.age[annee - 1] + Femelle.age[annee - 1]) * 0.35;
            
            Nbr_lapins_vivants = Somme(Femelle.mois, 0, 12) + Somme(Male.mois, 
                                                                         0, 12);
            printf("\nLes femelles en fonction de l'ages à la %d eme année sont"
                                                                        ,annee);
            printf("\n");
            affiche(Femelle.age, annee);
            printf("\n");
            printf("\nLes males en fonction de l'age à la %deme année sont \n"
                                                                        ,annee);
            affiche(Male.age, annee);
            printf("\nRESULATS GENERAUX\n");
            printf("\n\tLe nombre total de lapins à la %d eme année est :%d\n\n"
              ,annee, Somme(Femelle.age, 0, annee) + Somme(Male.age, 0, annee));
            printf("\n\tLe nombre total de lapereaux à cette même année est : %d\n" 
                               , Femelle.age[annee - 1] + Male.age[annee - 1]);
            printf("\n\tIl y a eu exactement %d lapins morts depuis le debut de",
            Nbr_lapins_vivants - Somme(Femelle.age, 0, annee) - Somme(Male.age,
                                                                    0, annee));
            printf(" l'experience\n\t ce qui represente %f%% de la population\n"
            ,1.0 * (Nbr_lapins_vivants - Somme(Femelle.age, 0, annee) - Somme(
                                     Male.age, 0, annee)) / Nbr_lapins_vivants);

            //----------------------TAUX DE CROISSANCE------------------------//
            printf("\nTAUX DE CROISSANCE\n");
            printf("\nChoisir l'année à partir de laquelle calculer le taux de c");
            printf("roissance : Année = ");
            scanf("%d",&choix);
 
            while(choix == annee) // valeur interdite
            {
                printf("\nChoisir l'année à partir de laquelle calculer le ");
                printf("taux de croissance : Année = ");
                scanf("%d",&choix);
            }
         
            printf("\n\tLe taux de croissance continu est : %f %%\n",
            Taux_de_croissance(Total_femelle[choix],Total_femelle[annee - 1], 
                                                                     annee)[0]);
            printf("\n\tLe taux de croissance non continu est : %f %%\n",100 * 
            Taux_de_croissance(Total_femelle[choix],Total_femelle[annee - 1], 
                                                                     annee)[1]);
            
          break;
       }
       test --;
    }
    printf("\n--------------FIN DES TESTS----------------\n"); 
}
