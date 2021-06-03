#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//--------------------------------------------------------------------//
//               Affiche le contenu d'un tableau de n float           //
//------------------------------------------------------------------- //

void affiche(float * T, int n)
{   int i = 0;

    for(i = 0; i < n; i++)
    {
        printf("%f\t",T[i]);
        if(i%3 == 0) printf("\n");
    }
    printf("\n\n");
}

//------------------------------------------------------------------------//
// miror binary : Tableau inversÃ© des valeurs                            //
//                                                                        //
// Entree : Un nombre Ã  convertir en binaire                             //
//                                                                        //
// Sortie : renvoie un tableau d'entier inversÃ© contenant les valeurs de //
//          la conversion de n en de la conversion de n en binaire        //                                                
//------------------------------------------------------------------------//

int * miror_binary(int n){
    int     i = 0;
    int  *  T=malloc(sizeof(int) * 5);  // on se limite Ã  32, ce qui justifie la 
				      // taille 5.
	while (n > 0)                     
	{
		T[i] = n % 2;
		n = n / 2;
		i++;
    	}
    return T;
}

//-------------------------------------------------------------------------//
// Decimal :   de la base binaire Ã  la base decimal                       //
//                                                                         //
// Entree : Un tableau d'entier contenant des valeurs en binaire et sa     //
//          taille                                                         //
// Sortie : renvoie la valeur de la conversion de ce nombre                //                                               
//-------------------------------------------------------------------------//

int Decimal(int * T, int n)
{
    int     sum = 0;
    int     i = 0;

    for(i = 0; i < n; i++)
    {
        sum += T[n - 1 - i] * i * i;
    }
    return sum;
}

int main()
{
    int     i = 0;
    float * T = NULL;
    T = malloc(sizeof(float) * 15);   // l'exemple pour n = 15

    for(i = 0; i < 15; i++)
    {
        T[i] = 1.0 * Decimal(miror_binary(i), 5) / 32.0;
    }
    affiche(T, 15);
}
