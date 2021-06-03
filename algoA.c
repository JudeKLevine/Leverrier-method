#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void affiche(int * Tableau, int taille)
{
    int     i;

    for(i = 0; i < taille; i++)
    {
        printf("%d\t", Tableau[i]);
    }
    printf("\n");
}
//---------------------SECTION 1.1---------------------------//

//-----------------------------------------------------------//
//                      Algorithme A                         //
//-----------------------------------------------------------//
int maxTab(int * Tableau, int taille)
{
    int     i;
    int     max = Tableau[0]; // initialisation avec la premiere valeur du tab

    for(i = 0; i < taille; i++) 
    {
        if(max < Tableau[i]) max = Tableau[i]; // teste avec toutes les valeurs 
    }                                          // du tableau et recupere celle 
    return max;                                // qui est la plus grande
}

//-----------------------------------------------------------//
//                      Algorithme B                         //
//-----------------------------------------------------------//
int indiceDe(int * Tableau, int taille, int cible)
{
    int     i = 0;
    int     indice;

    while(Tableau[i] != cible & i < taille - 1)
    {
        i++;
    }
    if(i == taille - 1) indice = - 1;
    else indice = i;
    return indice;
}

//-----------------------------------------------------------//
//                      Algorithme C                         //
//-----------------------------------------------------------//
int nbOccurences(int * Tableau, int taille, int cible)
{
    int     i;
    int     result = 0;

    for(i = 0; i < taille; i++)
    {
        if(Tableau[i] == cible) result ++;
    }
    return result;
}

/*
//-----------------------------------------------------------//
//                      Algorithme D                         //
//-----------------------------------------------------------//

int * possedeElemMaj(int * Tableau, int taille)
{
    int     i, j = 0;
    int     med = taille / 2;
    int  *  inverse_Tab;
    int  *  result = calloc(2, sizeof(int));

    inverse_Tab = malloc(sizeof(int) * taille);

    for(i = 0; i < taille; i++)
    {
        inverse_Tab[i] = Tableau[taille - i - 1];
    }

    while(indiceDe(inverse_Tab, taille, Tableau[j]) > med & j <= med)
    {
        j++;
    }
    result[1] = Tableau[j];
    if(j = med) result[0] = 0;
    else result[0] = 1;
    return result; 
}
*/

//-----------------------------------------------------------//
//                      Algorithme E                         //
//-----------------------------------------------------------//
int estOrdonne(int * Tableau, int taille)
{
    int     i;
    int     count = 0;
    int     result;

    for(i = 0; i < taille - 1; i++)
    {
        if(Tableau[i] <= Tableau[i + 1]) count ++;
        else count --;
    }
    if(count == taille - 1) return 1;
    if(count == 1 - taille) return -1;
    else                    return 0;
}

//-----------------------------------------------------------//
//                      Algorithme F                         //
//-----------------------------------------------------------//
int signeValeur(int * Tableau, int taille)
{
    int     i;
    int     count = 0;

    for(i = 0; i < taille; i++)
    {
        if(Tableau[i] >= 0) count ++;
        else count --;
    }
    if(count == taille - 1) return 1;
    if(count == 1 - taille) return -1;
    else                    return 0;
}

//-----------------------------------------------------------//
//                      Algorithme G                         //
//-----------------------------------------------------------//
int * decalageGauche(int * Tableau, int taille)
{
    int     i;
    int  *  Tableau_Tmp;

    Tableau_Tmp = malloc(sizeof(int) * taille);
    for(i = 0; i < taille - 1; i++)
    {
        Tableau_Tmp[i] = Tableau[i + 1];
    }
    Tableau_Tmp[taille - 1] = Tableau[0];
    return Tableau_Tmp;
}

//-----------------------------------------------------------//
//                      Algorithme H                         //
//-----------------------------------------------------------//
int * decalageDroite(int * Tableau, int taille)
{
    int     i;
    int  *  Tableau_Tmp;

    Tableau_Tmp = malloc(sizeof(int) * taille);
    for(i = 1; i < taille; i++)
    {
        Tableau_Tmp[i] = Tableau[i - 1];
    }
    Tableau_Tmp[0] = Tableau[taille - 1];
    return Tableau_Tmp;
}

//-----------------------------------------------------------//
//      Section 1.2 : Autres algorithmes sur les tableaux    //
//-----------------------------------------------------------//

//-----------------------------------------------------------//
//                      Algorithme I                         //
//-----------------------------------------------------------//
int  * trouvePremierPair(int * Tableau, int taille)
{
    int     i = 0;
    int     indice;
    int  *  pair = calloc(2, sizeof(int));

    while(Tableau[i] % 2 != 0 & i < taille - 1)
    {
        i++;
    }
    if(i == taille - 1)
    {
        pair[0] = -1;
        pair[1] = -1;
    }
    else
    {
        pair[0] = i;
        pair[1] = Tableau[i];
    }  
    return pair;
}

//-----------------------------------------------------------//
//                      Algorithme J                         //
//-----------------------------------------------------------//


int tousleschiffres(int * Tableau, int taille)
{
    int     i;
    int     count = 0;
    
    for(i = 0; i < 10; i++)
    {
        if(nbOccurences(Tableau, taille, i) == 0) count --;
    }
    if(count < 0) printf("\n\tFaux\n");
    else          printf("\n\tVrai\n");
}

//-----------------------------------------------------------//
//      Section 1.3 : l'incontournable factorielle           //
//-----------------------------------------------------------//

//-----------------------------------------------------------//
//                      Algorithme K                         //
//-----------------------------------------------------------//

int facto(int n)
{
    int     i;
    int     result;
    int     produit = 1;

    if(n == 0) result = 1;
    else 
    {
        for(i = 1; i < n + 1; i++)
        {
            produit = produit * i;
        }
        result = produit;
    }
    return result;
}

//-----------------------------------------------------------//
//                      Algorithme L                         //
//-----------------------------------------------------------//
int prevision(int * Tableau, int taille)
{
}

//-----------------------------------------------------------//
//                      Algorithme M                         //
//-----------------------------------------------------------//
int stockMax(int * Tableau, int taille)
{
}

//-----------------------------------------------------------//
//      Section 1.4 : Autour d'un stock suur les fenetres    //
//-----------------------------------------------------------//

int main()
{
    int   i;
    int * Tableau = calloc(10, sizeof(int));
    
    for(i = 0; i < 10; i++)
    {
        Tableau[i] = 1;
    }
    //printf("%d",indiceDe(Tableau, 10, -4));
    //printf("\n%d\n", maxTab(Tableau, 10));
    //printf("%d\n", facto(10));
    //printf("\n%d\n", nbOccurences(Tableau, 10, 10));
    //printf("\n%d\n", signeValeur(Tableau, 10));
    //affiche(decalageDroite(Tableau, 10), 10);
    //affiche(trouvePremierPair(Tableau, 10), 2);
    tousleschiffres(Tableau, 10);
    affiche(possedeElemMaj(Tableau, 10), 2);
}
    
