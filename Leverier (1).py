def produitMat(m1, m2):
  m = []
  if len(m1[0]) != len(m2):
    print("erreur")
    return False
  for i in range(len(m1)):
    ligne = []
    for j in range(len(m2[0])):
      element = 0
      for k in range(len(m1[0])):
        element = element + m2[i][k] * m1[k][j]
      ligne.append(element)
    m.append(ligne)
  return m

def traceMat(n):
    sum = 0
    for i in range(len(n)):
        for j in range(len(n)):
            if i==j:
                sum = sum + n[i][j]
    return sum

def somme_mat(mat1,mat2):
    k = []
    for i in range(len(mat1)):
        colonne = []
        for j in range(len(mat1)):
            a = mat1[i][j] + mat2[i][j]
            colonne.append(a)
        k.append(colonne)
    return k

def pro_mat_sca(mat1,b):
    k = []
    for i in range(len(mat1)):
        colonne = []
        for j in range(len(mat1)):
            a = mat1[i][j]*b
            colonne.append(a)
        k.append(colonne)
    return k
def id(n):
    L = []
    for i in range(n):
        L.append([])
    for i in range(n):
        for j in range(n):
            if i==j:
                L[i].append(1)
            else:
                L[i].append(0)
    return L

def calculMat(L, n):
    M = []
    V = id(len(L))
    if n == 0:
        M = L
    else:
        A = -1/(n)*traceMat(calculMat(L, n-1))
        B = pro_mat_sca(V,A)
        C = somme_mat(calculMat(L, n-1),B)
        M = produitMat(C,L)
    return M
def leverier(L):
    Coef = [(-1)**len(L)]
    L = [calculMat(L, i) for i in range(len(L))]
    Trace = [traceMat(i)/(L.index(i) + 1) for i in L]
    for i in Trace:
        Coef.append(i)
    return Coef
