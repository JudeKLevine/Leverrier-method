## chiffrement de Hill

def Produit_Mat_vect(Matrice, vecteur):
    
    Resultat = []
    for i in range(len(Matrice)):
        result = 0
        for j in range(len(vecteur)):
            result += Matrice[i][j] * vecteur[j][0]
        Resultat.append([result])

    return Resultat

# Avec des lettres en miniscule

def Chiffrement_Hill(Matrice):
    
    mot = input("entrez votre mot en miniscule : ")
    long = len(mot)     # permet de faire le test à la fin
                        # de savoir si pai ou impair  
    M = [[ord(i) - 97] for i in mot]
    if len(M) % 2 != 0: M.append([0])
    
    group_lettre = []
    b = len(M) // 2
    
    for i in range(b):
        group_lettre.append(M[2 * i: 2 * i + 2])

    group_pro_lettre = [Produit_Mat_vect(Matrice, group_lettre[i]) for i in range(b)]
    
    Mot = []
    for i in range(len(group_pro_lettre)):
        for j in range(2):
            Mot.append(chr(group_pro_lettre[i][j][0] % 26 + 65))
    if long % 2 != 0 : Mot.remove(Mot[-1])
      
    Mot = "".join(Mot)
    return Mot
