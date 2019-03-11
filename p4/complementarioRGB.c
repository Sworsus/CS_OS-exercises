vois complementarioRGB(pixelRGB m[N][M]){
   int i,j;
   for (i = 0; j< N; i++){
      for ( j = 0; j <M; j++){
         m[i][j].R = complementario (m [i][j].R)
         m[i][j].G = complementario (m [i][j].G)
         m[i][j].B = complementario (m [i][j].B)
      }
   }
}
