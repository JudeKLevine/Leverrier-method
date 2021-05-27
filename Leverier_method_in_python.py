#--------------CALCUL DU POLYNOME CARACTERISTIQUE---------------#
# Pour ce calcul, nous n'utiliserons aucune fonction predefinie #

# Poduit de deux matrices
def produitMat(Matrice1, Matrice2):
  m = []
  if len(Matrice1[0]) != len(Matrice2):
    print("erreur")
    return False

  for i in range(len(Matrice1)):

    ligne = []
    for j in range(len(Matrice2[0])):

      element = 0
      for k in range(len(Matrice1[0])):

        element = element + Matrice2[i][k] * Matrice1[k][j]
      ligne.append( element )
    m.append(ligne)

  return m

# donne la trace de la matrice
def traceMat(Matrice):
    sum = 0
    for i in range(len(Matrice)):
        sum = sum + Matrice[i][i]
    return sum

# somme de deux matrices
def somme_mat(Matrice1, Matrice2):
    Matrice_somme = []
    for i in range(len(Matrice1)):

        colonne = []
        for j in range(len(Matrice1)):

            sum = Matrice1[i][j] + Matrice2[i][j]
            colonne.append(sum)
        Matrice_somme.append(colonne)

    return Matrice_somme

# Produit d'une matrice par un scalaire
def pro_mat_sca(Matrice, scalaire):
    Matrice_result = []
    for i in range(len(Matrice)):

        colonne = []
        for j in range(len(Matrice)):

            sum = Matrice[i][j] * scalaire
            colonne.append(sum)
        Matrice_result.append(colonne)
    return Matrice_result

# La matrice identité de taille n
def id(Taille):
    L = []
    for i in range(Taille):

        L.append([])
        for j in range(Taille):

            if i == j:  L[i].append(1)
            else:       L[i].append(0)
    return L

# Matrices recursives de Leverrier
def calculMat(Matrice, n):
    Matrice_rec = []
    V = id(len(Matrice))
    if n == 0: Matrice_rec = Matrice
    else:
        A = -1 / n * traceMat(calculMat(Matrice, n - 1))
        B = pro_mat_sca(V, A)
        C = somme_mat(calculMat(Matrice, n - 1), B)
        Matrice_rec = produitMat(C, Matrice)
    return Matrice_rec

# Tableau contenant les coeficients des des mônomes ordonés
# du polynome caracterisetique de la matrice L

def leverier(Matrice):
    Coef = [(-1)**len(Matrice)]
    L = [calculMat(Matrice, i) for i in range(len(Matrice))]
    Trace = [traceMat(i)/(L.index(i) + 1) for i in L]
    for i in Trace:
        Coef.append(i)
    return Coef
