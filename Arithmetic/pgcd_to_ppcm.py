## Cette programme permet de determiner le ppcm 
## de deux nombres à partir de leur pgcd 

def pgcd(a, b):
    reste = a % b
    while reste != 0:
        a = b
        b = reste
        reste  = a % b
    return b

def ppcm(a, b):
    return a * b // pgcd(a, b)
