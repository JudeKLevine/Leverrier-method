ellipse=function(vect_or, a, b, Nb_point, angle){
  
  # a represente le demi-grand axe OA
  # b represente le demi-grand axe OB
  # angle represente l'orientation de l'ellipse 
  
  theta = (0:Nb_point)*2*pi/Nb_point
  x = vect_or[1] + a*cos(theta)
  y = vect_or[2] + b*sin(theta + angle)
  
  # les points principaux
  
  A_x = vect_or[1] + a*cos(pi)
  A_y = vect_or[2] + b*sin(pi + angle)
  
  B_x = vect_or[1] + a*cos(pi/2)
  B_y = vect_or[2] + b*sin(pi/2 + angle)
  
  C_x = vect_or[1] + a
  C_y = vect_or[2] + b*sin(angle)
  
  
  plot(x,y, type='l')
  segments(vect_or[1], vect_or[2], A_x, A_y)
  segments(vect_or[1], vect_or[2], B_x, B_y, col='red')
  segments(vect_or[1], vect_or[2], C_x, C_y, col='blue')

}


O = c(1,0)
ellipse(O,2,1,100,pi/1.5)
