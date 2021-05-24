## cette methode permet de detreminer le pgcd de deux 
## nombres en passant par leur ppcm

def div(n):
    L = []
    for i in range(2, n + 1):
        while n%i == 0:
            n = n//i
            L.append(i)
    return L # renvoie la liste des diviseurs de n

def produit(L):
    produit = 1
    for i in L:
        produit = produit*i
    return produit # le produit des elements contenus dans le tableau

def ppcm(a, b):

    c = div(a)
    d = div(b)
    for i in c :
        for j in d:
            if i == j:
                d.remove(j)
    return produit(d)*produit(c)

def pgcd(a, b):
    return a * b // ppcm(a, b)
# renvoie le pgcd de deux nombres
