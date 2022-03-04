import numpy as np
import sympy as sm
def dichotomie(f, a, b, eps):
    while np.abs(a - b) > eps :
        c = (a + b)/2
        if f.subs(x, c)*f.subs(x, a) < 0:
            b, a = c, a
        else:
            b, a = b, c
    return (a+b)/2


def dicho_nbr(f, a, b, eps):
    sum = 0
    while np.abs(a - b) > eps :
        sum += 1
        c = (a + b)/2
        if f.subs(x, c)*f.subs(x, a) < 0:
            b, a = c, a
        else:
            b, a = b, c
    return sum


sm.var("x")
F = sm.sin(x) - sm.ln(x)
G = 2*x + 3 - sm.exp(x)
a = dichotomie(F,2,3,10**(-8))
c = dicho_nbr(F, 2, 3, 10**(-8))
b = dichotomie(G,1,5,10**(-8))
d = dicho_nbr(G,1,5,10**(-8))
print(a,b,c,d)
