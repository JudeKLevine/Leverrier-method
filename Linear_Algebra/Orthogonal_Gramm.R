# --- Ce programme n'utilise que des fonctions de bases du langage
# --- TOus les outils de calcul matricielle ont été reprogrammé
# --- Il aurait été plus simple en utilisant les packages


#--------------------------------------------------------------------//
#                   Orthogonalisation de Gramm Schmidt               //
#     Entree : Une matrice(la matrice d'une base)                    //
#     sortie : Matrice de la base orthogonalisée                     //
# -------------------------------------------------------------------//

# Produit de deux matrices
Produit_Matrice=function(Matrice1, Matrice2){
  
  Ncol1 = length(Matrice1[1,])
  Nrow1 = length(Matrice1[,1])
  
  Ncol2 = length(Matrice2[1,])
  Nrow2 = length(Matrice2[,1])
  
  Result = matrix(NA,nrow = Nrow1, ncol = Ncol2)
  
  if(Ncol1 != Nrow2){
    print("LE PRODUIT N'EST PAS POSSIBLE")
  }
  for(i in 1:Nrow1){
    Vect = c()
    for(j in 1:Ncol2){
      Val = 0
      for(k in 1:Nrow2){
        Val = Val + Matrice1[i,k]*Matrice2[k,j];
      }
      Vect[j] = Val
    }
    Result[i,] = Vect
  }
  return(Result)
}
 
#Transforme une liste en matrice à 1 colonne
vecteur=function(Vect){ # Beaucoup plus simple pour avoir des vecteurs
  
    A = matrix(Vect, ncol = 1, nrow = length(Vect))
    return(A)
}

# Renvoie la matrice transposée de Matrice
# utile pour la matrice de la projection orthogonale 
Transpose=function(Matrice){
  
    Ncol = length(Matrice[1,])
    Nrow = length(Matrice[,1])
    
    Matrice_trans = matrix(NA, ncol = Nrow, nrow = Ncol)
    
    for(i in 1:Ncol){
        Matrice_trans[i,] = Matrice[,i]
    }
    return(Matrice_trans)
}

# Renvoie la norme d'un vecteur
Norme=function(Vecteur){
  
  N = 0
  taille = length(Vecteur)
  
  for(i in 1:taille){
    N = N + Vecteur[i]*Vecteur[i]
  }
  return(sqrt(N))
}

# projection de vecteur2 sur col(Vecteur1)
Projection=function(Vecteur1, Vecteur2){
    
    if(Norme(Vecteur1) == 0){
        print('VECTEUR NUL')
    }
    MatriceP = matrix(NA, ncol = length(Vecteur1), nrow = length(Vecteur1))
    MatriceP = 1/(Norme(Vecteur1)*Norme(Vecteur1))*(Produit_Matrice(vecteur(
                                      Vecteur1), Transpose(vecteur(Vecteur1))))
                                
    return(Produit_Matrice(MatriceP, vecteur(Vecteur2)))
}

# Programme renvoie une base orthogonale, pas orthonormée
# il suffit diviser chaque vecteur par sa norme pour avoir 
# une base orthonormée
Orthogonal_Gramm=function(Matrice){ # ici matrice represente les vecteurs de la
                                    # base que l'on veut orthogonalisé
  tailleC = length(Matrice[,1])  
  tailleN = length(Matrice[1,])
  Base = matrix(NA, nrow = tailleN, ncol = tailleC)
      Base[,1] = Matrice[,1]
      for(i in 2:tailleC){
        B = matrix(Matrice[,i], nrow = tailleN, ncol = 1)
        
          for(j in 1:(i-1)){
              B = B - Projection(vecteur(Base[,j]), vecteur(Matrice[,i]))
          }
          Base[,i] = B
      }
      return(Base)
  }

    #################################
    #
    #             TEST
    #
    #################################

# Test 1
A = matrix(c(c(3,2),c(1,2)),  ncol=2, nrow=2, byrow = TRUE)
A
Orthogonal_Gramm(A)

# Test 2 : Matrice de HIlbert
M = matrix(NA, ncol = 2, nrow = 2)
for (i in 1:2){
  for(j in 1:2){
    M[i,j] = 1/(i+j-1)
  }
}
Orthogonal_Gramm(M)

# Test 3 : 
Mat = matrix(c (c(1,1,-1), c(0,1,-1), c(1,1,0)), nrow = 3, ncol = 3 , byrow=TRUE)
Mat
round(Orthogonal_Gramm(Mat), 2)
