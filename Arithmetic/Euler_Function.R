Euler1_function=function(int1){
  
  res = int1
  produit = 1
  for(i in 2:(as.integer(sqrt(int1) + 1))){
    if( res %% i == 0){
      Nb = 0
      while(res %% i == 0){
        Nb = Nb + 1
        res = as.integer(res/i)
      }
      produit = produit * (i-1)*(i^(Nb-1))
    }
  }
  produit = produit * ifelse(res > 1, (res-1), 1)
  return(produit)
}
