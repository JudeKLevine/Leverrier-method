Circle=function(vect_Orig, R, Nb_point){
  
    points = (0:Nb_point)*2*pi/Nb_point
    x = vect_Orig[1] + R*cos(points)
    y = vect_Orig[2] + R*sin(points)
    
    plot(x,y,type='l', col = 'red', main = "Cercle de rayon R")
    points(vect_Orig[1], vect_Orig[2], type='p', col="black", lwd = 1)
    segments(vect_Orig[1], vect_Orig[2], vect_Orig[1] + R, vect_Orig[2], 
             col = 'black')
    text(x = vect_Orig[1] + R/2, y = vect_Orig[2] + R*0.11, "R", lwd = 1)
    
}
Circle(c(5,5),1,10000)
