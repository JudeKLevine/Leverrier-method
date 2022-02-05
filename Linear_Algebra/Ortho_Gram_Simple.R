#--------------------------------------------------------------------//
#                   Orthogonalisation de Gram Schmidt               //
#     Entree : Une matrice(la matrice d'une base)                    //
#     sortie : Matrice de la base orthogonalisée                     //
# -------------------------------------------------------------------//

 #Transforme une liste en matrice à 1 colonne
vecteur=function(Vect){ # Beaucoup plus simple pour avoir des vecteurs
  
    A = matrix(Vect, ncol = 1, nrow = length(Vect))
    return(A)
}

# projection de vecteur2 sur col(Vecteur1)
Projection=function(Vecteur1, Vecteur2){
    
    if(norm(Vecteur1) == 0){
        print('VECTEUR NUL')
    }
    MatriceP = matrix(NA, ncol = length(Vecteur1), nrow = length(Vecteur1))
    MatriceP = 1/(norm(Vecteur1, type = '2')*norm(Vecteur1, type = '2'))*(vecteur(Vecteur1)%*%t(vecteur(Vecteur1)))
                                
    return(MatriceP%*%vecteur(Vecteur2))
}

# Programme renvoie une base orthogonale, pas orthonormée
# il suffit diviser chaque vecteur par sa norme pour avoir 
# une base orthonormée

Orthogonal_Gram=function(Matrice){ # ici matrice represente les vecteurs de la
                                    # base que l'on veut orthogonalisé
  tailleN = length(Matrice[,1])  
  tailleC = length(Matrice[1,])
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
    #             TEST              #
    #################################

# TEst 1
A = matrix(c(c(3,2),c(1,2)),  ncol=2, nrow=2, byrow = TRUE)
A
Orthogonal_Gram(A)

# TESt 2 : Matrice de HIlbert
M = matrix(NA, ncol = 2, nrow = 2)
for (i in 1:2){
  for(j in 1:2){
    M[i,j] = 1/(i+j-1)
  }
}
Orthogonal_Gram(M)

# Test 3 : 
Mat = matrix(c (c(1,1,1), c(1,-1,0)), nrow = 2, ncol = 3 , byrow=TRUE)
Mat
round(Orthogonal_Gram(Mat), 2)


