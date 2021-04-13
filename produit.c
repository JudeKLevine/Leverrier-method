#include<stdio.h>
#include<stdlib.h>
#include<math.h>


//------------------------------------------------------------------//
// affiche : affiche les valeurs contenues dans une Matrice         //
//                                                                  //
// Entree : le Tableau et sa taille                                 //
// sortie : Affiche chaque element de la matrice                    //
//------------------------------------------------------------------//

void affiche(float ** Matrice, int taille)
{
    int i;
    int j;
 
    for(i = 0; i < taille; i++)
    {
        for(j = 0; j< taille; j++)
        {
            if(j == 0) printf("| %.1f\t",Matrice[i][j]);
            else       
                printf("%.1f\t",Matrice[i][j]);
        }
        printf("| \n");
    }
    printf("\n");
}

//Même principe que la fonction precedente, mais affiche les elements d'un vecteur//
 
void affiche2(float * Vecteur, int taille)
{
    int i;

    for(i = 0; i < taille ; i++)
    {       
        if(i == 0) printf("[ %.1f,\t",Vecteur[i]);
        else if (i == taille - 1) printf("%.1f ]",Vecteur[i]);
        else printf("%.1f,\t",Vecteur[i]);
    }
    printf("\n");
}

//--------------------------------------------------------------------//
// ProduitMatrice : Calcul le produit de deux matrices de meme taille //
//                                                                    //
// Entree : les deux matrices et leur taille commune                  //
// sortie : Renvoie la matrice produit des deux autres                //
//--------------------------------------------------------------------//

float ** produitMatrice(float ** Matrice1, float ** Matrice2, int taille)
{
	int i; 
	int j;
	int k;
	float sum;

	float **Tableau;

    Tableau = malloc(taille*sizeof(float*));

	for(i = 0; i < taille; i++)
	{
        Tableau[i] = malloc(sizeof(float)*taille);
		for(j = 0; j < taille; j++)
		{
			sum = 0;
			for(k = 0; k < taille; k++)
			{
				sum += Matrice1[i][k]*Matrice2[k][j];
			}
			Tableau[i][j] = sum;
		}
	}
	return Tableau;
}

//----------Trace d'une matrice--------------//
///      Renvoie la trace d'une matrice     ///

float TraceMatrice(float ** Matrice, int taille)
{
    int i;
    float Trace;
    
    for(i = 0; i < taille; i++)
    {
        Trace += Matrice[i][i];
    }
    return Trace;
}
// Renvoie la matrice somme des deux matrices passées en arguments//

float ** SommeMatrice(float ** Matrice1, float ** Matrice2, int taille)
{
    int i;
    int j;
    float ** Matrice3;

    Matrice3 = malloc(sizeof(float*)*taille);
    for(i = 0; i < taille; i++)
    {
        Matrice3[i] = malloc(sizeof(float)*taille);
        for(j = 0; j < taille; j++)
        {
            Matrice3[i][j] = Matrice1[i][j] + Matrice2[i][j];
        }
    }
    return Matrice3;
}
// Renvoie la matrice produit de la matrice passée en parametre et d'une      //
//                                constante                                   //

float ** Produit_Matrice_CA(float ** Matrice, int taille, float constante)
{
    int i;
    int j;
    float ** Matrice1;

    Matrice1 = malloc(sizeof(float*)*taille);
    for(i = 0; i < taille; i++)
    {
        Matrice1[i] = malloc(sizeof(float)*taille);
        for(j = 0; j < taille; j++)
        {
            Matrice1[i][j] = Matrice[i][j] * constante;
        }
    }
    return Matrice1;
}
// Renvoie la matrice identité de taille N // 

float ** Identite(int taille)
{
    int i;
    int j;
    float ** Matrice;

    Matrice = malloc(sizeof(float*)*taille);
    for(i = 0; i < taille; i++)
    {
        Matrice[i] = malloc(sizeof(float)*taille);
        for(j = 0; j < taille; j++)
        {
            if(i == j)  Matrice[i][j] = 1;
            else        Matrice[i][j] = 0;
        }
    }
    return Matrice;
}

// Renvoie matrice de la suite de Leverrier en fonction de n //

float ** suite_matrice(float ** Matrice, int taille, int n)
{
    int i;
    int j;
    float ** Matrice2;
    float ** Matrice3;
    float ** Matrice1; 

    Matrice1 = malloc(sizeof(float*)*taille);
    for(i = 0; i < taille; i++)
    {
        Matrice1[i] = malloc(sizeof(float)*taille);
    }
    if(n == 0) return Matrice;
    else
        Matrice2 = Produit_Matrice_CA(Identite(taille), taille, -1 / (n) * 
                   TraceMatrice(suite_matrice(Matrice, taille, n - 1), taille));

        Matrice3 = SommeMatrice(suite_matrice(Matrice, taille, n - 1), Matrice2, 
                                                                        taille);
        return produitMatrice(Matrice, Matrice3, taille);
}

// Renvoie un tableau contenant les valeurs du polynome caracteristique de la //
// matrice passée ne parametre par ordre du plus grand monome                 //   
            
float * Polynome(float ** Matrice, int taille)
{
    int i; 
    float * Coeficient;

    Coeficient = malloc(sizeof(float) * (1 + taille));
    Coeficient[0] = pow(-1,taille);
    for (i = 0; i < taille; i++)
    {
        Coeficient[i + 1] = -1.0/(1 + i) * (TraceMatrice(suite_matrice(Matrice, 
                                                           taille, i), taille));
    }
    return Coeficient;
}

//-----------FONCTION MAIN-----------//

int main()
{
    int i;
    int j;
    int taille;
    float **Matrice;

    printf("Entrez la taille votre matrice\t");
    scanf("%d",&taille);

    Matrice = malloc(sizeof(float*)*taille);
    for (i = 0; i < taille; i++)
    {
        Matrice[i] = malloc(sizeof(float)*taille);
        for(j = 0; j < taille; j++)
        {
            if( j%taille == 0) printf("\n");            
            printf("[%d][%d] = ",i + 1,j + 1);
            scanf("%f",&Matrice[i][j]);
        }
        printf("\n");
    }
    affiche(Matrice, taille);
    affiche2(Polynome(Matrice, taille),taille + 1);
    printf("Le determinant de votre matrice est : %.1f\n",Polynome(Matrice, 
                                                             taille)[taille]);
}


