#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------//
//          affiche les caracteres d'une chaine            //
//       prend en entrée la chaine et sa taille            //
//---------------------------------------------------------//

void affiche(char * vecteur, int taille)
{
    int     i;    
    for(i = 0; i < taille; i++)
    {
        printf("%c", vecteur[i]);
    }
    printf("\n");
}


//----------------------------------------------------------//
// Produit d'une matrice et d'un vecteur [modulo 26] + 97   //
//   Prend en entrée la matrice, le vecteur et leur taille  //
// Ce produit de matrice est adapté pour le chiffre de Hill //
//----------------------------------------------------------//

int * Produit_Mat_vect(int ** Matrice, int * vecteur, int taille)
{
    int  *  Resultat = calloc(2, sizeof(int));       
    int     result;
    int     i,j;
    
    for(i = 0; i < taille; i++)
    {
        result = 0;
        for(j = 0; j < taille; j++)
        {
            result += Matrice[i][j] * vecteur[j];
        }
    Resultat[i] = result % 26 + 97;
    }
    return Resultat;
}

//---------------------------------------------------------//
//             creation d'une matrice carrée               //
//         Prend en entrée la taille de la matrice         //
//---------------------------------------------------------//

int ** Matrice(int taille)
{
    int **  Matrix;
    int     i;
    int     j;

    Matrix = malloc(sizeof(int*) * taille);

    for(i = 0; i < taille; i++)
    {
        Matrix[i] = malloc(sizeof(int) * taille);
        for(j = 0; j < taille; j++)
        {
            printf("Matrix[%d][%d] = ", i + 1, j + 1);
            scanf("%d", &Matrix[i][j]);
        }
    }
    return Matrix;
}


int main()
{
    int **  matrix;
    int *   vect = calloc(2, sizeof(int));
    int     i;
    int     Nbr_lettre; 
    int     Nbr_vect;
    char *  Mot_chiffre;
    char    mot[100];

    matrix = Matrice(2);
    
    printf("Entrez le mot à chiffrer (en miniscule) : ");
    scanf("%s", mot);
    printf("Entrez le nombre de lettre du mot : ");
    scanf("%d", &Nbr_lettre);
 
    if(Nbr_lettre % 2 == 1)
    {
        mot[Nbr_lettre] = 'x'; // on ajoute une lettre dans le mot à chiffrer
        Nbr_vect = 1 + Nbr_lettre / 2;

    }
    else Nbr_vect = Nbr_lettre / 2;

    Mot_chiffre = calloc(Nbr_lettre, sizeof(char));

    // Separation des caracteres deux à deux et produit de la matrice et des 
    // vecteurs engendrés. 

    for(i = 0; i < Nbr_vect; i++)
    {
        int * vectx = calloc(2, sizeof(int));
        vectx[0] = mot[2 * i] - 97;           //  Separation des caracteres
        vectx[1] = mot[2 * i + 1] - 97;       //  deux à deux

        Mot_chiffre[2 * i] = Produit_Mat_vect(matrix, vectx, 2)[0];     
        Mot_chiffre[2 * i + 1] = Produit_Mat_vect(matrix, vectx, 2)[1]; 
    }
    printf("\n Votre mot chiffré est : \t"); 
    affiche(Mot_chiffre, Nbr_lettre);  // mot chiffré
}

