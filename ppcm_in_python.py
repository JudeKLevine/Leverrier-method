def div(n):
    L = []
    for i in range(2, n + 1):
        while n%i == 0:
            n = n//i
            L.append(i)
    return L

def produit(L):
    produit = 1
    for i in L:
        produit = produit*i
    return produit

def ppcm():
    a = int(input("entrez la valeur de a : "))
    b = int(input("entrez la valeur de b : "))
    c = div(a)
    d = div(b)
    for i in c :
        for j in d:
            if i == j:
                d.remove(j)
    return produit(d)*produit(c)
