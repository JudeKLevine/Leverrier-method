# RESOLUTION DES EQUATIONS :

### METHODE DE DICHOTOMIE

Dichotomie=function(f, a, b, eps)
{
  if(f(a)*f(b) > 0){print("CHANGEZ LES BORNES")}
  else{
    while(abs(a - b) > eps)
    {
      c = (a + b)/2
      if(f(c) * f(a) < 0){b = c; a = a}
      else               {b = b; a = c}
    }
    return(a/2+b/2)
  }
}
## TESTS
f=function(x){x-exp(x)+2}
Dichotomie(f, -2, -1, 0.000002) # -1.841405

### METHODE DE NEWTON
Newton_method=function(Fc, f, a, e) # avec f, la derivée de Fc
{
  if(abs(Fc(a) < e)){ return(a)}
  else
    {
      while(abs(Fc(a)) > e)
      {
        a = a - Fc(a)/f(a)  
      }
      return(a)
  }
}

## TESTS
Fc=function(x){x-exp(x)+2}
f=function(x){1-exp(x)}
Newton_method(Fc, f, -1, 0.02) # -1.843482
