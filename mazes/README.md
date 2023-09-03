# Sokoban maps
This folder contains 60 maps for the Sokoban game. The maps have been extracted from the binary file of a Sokoban implementation for DOS called `pusher` in [this](https://github.com/begoon/sokoban-maps) repository, and then saved in a single binary file. Each maze follows the same format `length (1), size_x (1), size_y (1), map tiles (size_x * size_y)`, where `length` is how many moves are needed at minimum to complete the maze, and the values in () indicate how many bytes are reservered in the binary. To find the `nth` maze in the file, read  `size_x` and `size_y` for a maze, and then jump `size_x * size_y + 1` bytes to find the size of the next one, repeating `n-1` times.

```
level, length, (size_x, size_y)
map tiles


1, 50, (22, 11)
    XXXXX             
    X   X             
    X*  X             
  XXX  *XXX           
  X  *  * X           
XXX X XXX X     XXXXXX
X   X XXX XXXXXXX  ..X
X *  *             ..X
XXXXX XXXX X@XXXX  ..X
    X      XXX  XXXXXX
    XXXXXXXX          


2, 43, (14, 10)
XXXXXXXXXXXX  
X..  X     XXX
X..  X *  *  X
X..  X*XXXX  X
X..    @ XX  X
X..  X X  * XX
XXXXXX XX* * X
  X *  * * * X
  X    X     X
  XXXXXXXXXXXX


3, 37, (17, 10)
        XXXXXXXX 
        X     @X 
        X *X* XX 
        X *  *X  
        XX* * X  
XXXXXXXXX * X XXX
X....  XX *  *  X
XX...    *  *   X
X....  XXXXXXXXXX
XXXXXXXX         


4, 64, (22, 13)
              XXXXXXXX
              X  ....X
   XXXXXXXXXXXX  ....X
   X    X  * *   ....X
   X ***X*  * X  ....X
   X  *     * X  ....X
   X ** X* * *XXXXXXXX
XXXX  * X     X       
X   X XXXXXXXXX       
X    *  XX            
X **X** @X            
X   X   XX            
XXXXXXXXX             


5, 51, (17, 13)
        XXXXX    
        X   XXXXX
        X X*XX  X
        X     * X
XXXXXXXXX XXX   X
X....  XX *  *XXX
X....    * ** XX 
X....  XX*  * @X 
XXXXXXXXX  *  XX 
        X * *  X 
        XXX XX X 
          X    X 
          XXXXXX 


6, 44, (12, 11)
XXXXXX  XXX 
X..  X XX@XX
X..  XXX   X
X..     ** X
X..  X X * X
X..XXX X * X
XXXX * X*  X
   X  *X * X
   X *  *  X
   X  XX   X
   XXXXXXXXX


7, 44, (13, 12)
       XXXXX 
 XXXXXXX   XX
XX X @XX ** X
X    *      X
X  *  XXX   X
XXX XXXXX*XXX
X *  XXX ..X 
X * * * ...X 
X    XXX...X 
X ** X X...X 
X  XXX XXXXX 
XXXX         


8, 66, (16, 17)
  XXXX          
  X  XXXXXXXXXXX
  X    *   * * X
  X *X * X  *  X
  X  * *  X    X
XXX *X X  XXXX X
X@X* * *  XX   X
X    * X*X   X X
XX  *    * * * X
 XXXX  XXXXXXXXX
  XXX  XXX      
  X      X      
  X      X      
  X......X      
  X......X      
  X......X      
  XXXXXXXX      


9, 67, (17, 18)
          XXXXXXX
          X  ...X
      XXXXX  ...X
      X      ...X
      X  XX  ...X
      XX XX  ...X
     XXX XXXXXXXX
     X *** XX    
 XXXXX  * * XXXXX
XX   X* *   X   X
X@ *  *    *  * X
XXXXXX ** * XXXXX
     X *    X    
     XXXX XXX    
        X  X     
        X  X     
        X  X     
        XXXX     


10, 97, (21, 20)
              XXXX   
         XXXXXX  X   
         X       X   
         X  XXXX XXX 
 XXX  XXXXX XXX    X 
XX@XXXX   *** X    X 
X **   ** *   X....XX
X  ***X    *  X.....X
X *   X ** ** X.....X
XXX   X  *    X.....X
  X   X * * * X.....X
  X XXXXXXX XXX.....X
  X   X  * *  X.....X
  XXX X ** * *XXXXXXX
    X X  *      X    
    X X *** *** X    
    X X       X X    
    X XXXXXXXXX X    
    X           X    
    XXXXXXXXXXXXX    


11, 65, (19, 15)
          XXXX     
     XXXX X  X     
   XXX  XXX* X     
  XX   @  *  X     
 XX  * **XX XX     
 X  X*XX     X     
 X X * ** X XXX    
 X   * X  X * XXXXX
XXXX    X  ** X   X
XXXX XX *         X
X.    XXX  XXXXXXXX
X.. ..X XXXX       
X...X.X            
X.....X            
XXXXXXX            


12, 66, (13, 16)
  XXXXXXXXX  
  X&.&X&.&X  
  X.&.&.&.X  
  X&.&.&.&X  
  X.&.&.&.X  
  X&.&.&.&X  
  XXX   XXX  
    X   X    
XXXXXX XXXXXX
X           X
X * * * * * X
XX * * * * XX
 X* * * * *X 
 X   *@*   X 
 X  XXXXX  X 
 XXXX   XXXX 


13, 76, (20, 13)
    XXXXXXXXX       
  XXX   XX  XXXXX   
XXX      X  X   XXXX
X  ** X* X  X  ... X
X X  *X@*XX X X.X. X
X  XX X*  X    ... X
X *X    * X X X.X. X
X    XX  XX* * ... X
X * XX   X  X*X.X. X
XX **  *   *  *... X
 X*  XXXXXX    XX  X
 X   X    XXXXXXXXXX
 XXXXX              


14, 58, (17, 13)
XXXXXXXXXXXXXXXX 
X              X 
X X XXXXXX     X 
X X  * * * *X  X 
X X   *@*   XX XX
X X X* * *XXX...X
X X   * *  XX...X
X XXX*** * XX...X
X     X XX XX...X
XXXXX   XX XX...X
    XXXXX     XXX
        X     X  
        XXXXXXX  


15, 72, (17, 17)
       XXXX      
    XXXX  X      
   XX  X  X      
   X  * * X      
 XXX X*   XXXX   
 X  *  XX*   X   
 X  X @ * X *X   
 X  X      * XXXX
 XX XXXX*XX     X
 X *X.....X X   X
 X  *...&. *X XXX
XX  X.....X   X  
X   XXX XXXXXXX  
X **  X  X       
X  X     X       
XXXXXX   X       
     XXXXX       


16, 63, (14, 15)
XXXXX         
X   XX        
X    X  XXXX  
X *  XXXX  X  
X  ** *   *X  
XXX@ X*    XX 
 X  XX  * * XX
 X *  XX XX .X
 X  X*XX*  X.X
 XXX   *..XX.X
  X    X.&...X
  X ** X.....X
  X  XXXXXXXXX
  X  X        
  XXXX        


17, 71, (18, 16)
       XXXXXXX    
 XXXXXXX     X    
 X     X *@* X    
 X** X   XXXXXXXXX
 X XXX......XX   X
 X   *......XX X X
 X XXX......     X
XX   XXXX XXX X*XX
X  X*   X  *  X X 
X  * ***  X *XX X 
X   * * XXX** X X 
XXXXX     *   X X 
    XXX XXX   X X 
      X     X   X 
      XXXXXXXX  X 
             XXXX 


18, 71, (22, 13)
      XXXXXXXXXXXX    
      X  .  XX   X    
      X X.     @ X    
 XXXXXX XX...X XXXX   
XX  XX...XXXX     XXXX
X * XX...    * X  *  X
X     .. XX X XX XX  X
XXXX*XXX*X *  X   X XX
 XXX  X    XX* ** X X 
 X   ** X X * X *XX X 
 X                  X 
 XXXXXXXXXXXXXXXXX  X 
                 XXXX 


19, 117, (28, 20)
        XXXXXX              
        X   @XXXX           
      XXXXX *   X           
      X   XX    XXXX        
      X *XX  XX    X        
      X   X  XXXXX X        
      X X** *    X X        
      X  * * XXX X X        
      X X   *  X X X        
      X X  X*X   X X        
     XX XXXX   X X X        
     X  *  XXXXX X X XXXX   
    XX    *     *  XXX  XXXX
XXXXX  XXX * *X * X   .....X
X     XX      X  XX  X.....X
X ****    XXXXXX*XX   X.XX.X
XX    XX              X....X
 XX  XXXXXXXXXXXXXXX   ....X
  X  X             XXXXX  XX
  XXXX                 XXXX 


20, 102, (20, 20)
       XXXXXXXXXXXX 
       X..........X 
     XXX.X.X.X.X..X 
     X   .........X 
     X@ * * * &.&.X 
    XXXXXXX XXXXXXX 
 XXXX   X    XX  X  
XX    * X    X * XX 
X  X*X XXX XXX*   XX
X *  * *   X * * * X
X  X * XX       X* X
X   *XXXX*XXXX*XX  X
XXXX  XX   X    X  X
   X* XX   X X **  X
   X   X * X  *    X
   XXX X ** X  * XXX
     X X    X * XX  
     X XXXXXXXX X   
     X          X   
     XXXXXXXXXXXX   


21, 58, (16, 14)
   XXXXXXXXXX   
   X..  X   X   
   X..      X   
   X..  X  XXXX 
  XXXXXXX  X  XX
  X            X
  X  X  XX  X  X
XXXX XX  XXXX XX
X  *  XXXXX X  X
X X *  *  X *  X
X @*  *   X   XX
XXXX XX XXXXXXX 
   X    X       
   XXXXXX       


22, 117, (22, 20)
            XXXX      
 XXXXXXXXXXXX  XXXXX  
 X    X  X  *  X   XX 
 X * * *  * X * *   X 
 XX* *   X @X *   * X 
XXX   XXXXXXXXXXXX XX 
X  * *X  X......X *X  
X X   X  X......XX X  
X  XX XX X .....X  X  
X X      *...... * X  
X X * XX X......X  X  
X  * *X  X......X *X  
X *   X  XX*XXXXX  X  
X * * XXXX * *  * *X  
XX X     * * * *   XXX
 X  XXXXXX *    *    X
 X         X XXXXXXX X
 XXXXXXX X*          X
       X   XXXXXXXXXXX
       XXXXX          


23, 81, (25, 14)
       XXXXXXX           
       X  X  XXXX        
       X *X* X  XX       
XXXXXXXX  X  X   XXXXXXXX
X....  X *X* X  *X  X   X
X....X X     X*  X      X
X..X.    *X  X *    X*  X
X... @XX  X* X*  X  X   X
X.... XX *X     *XXXXXXXX
XXXXXXXX  X**X*  X       
       X *X  X  *X       
       X  X  X   X       
       XXXX  XXXXX       
          XXXX           


24, 104, (21, 19)
   XXXXXXXXXX        
   X........XXXX     
   X.X.X....X  X     
   X........** X     
   X     .XXX  XXXX  
 XXXXXXXXX  * X   X  
 X     *   * *  * X  
 X  X    X  * *X  X  
 XX XXXXX   X  X  X  
 X *     X   XXXX X  
XX  *X   X XX  X  X  
X    XX*XXX    X  XX 
X *    * X  X  X   X 
XXXXX    X XX X XX XX
    X*X X  *  * *   X
    X@X  *X***  X   X
    XXX  *      XXXXX
      XX  X  X  X    
       XXXXXXXXXX    


25, 93, (23, 17)
               XXXX    
          XXXXXX  XXXXX
    XXXXXXX       X   X
    X      * * XX X X X
    X  XXXX *  X     .X
    X      * X X XX.X.X
    XX*XXXX* * * XX.X.X
    X     X    XXXX.XXX
    X *   XXXXXX  X.X.X
XXXXXX***XX      @X.X.X
X      X    X*X*XXX. .X
X XXXX X*****    X ...X
X X    *     X   X ...X
X X   XX XX     XXX...X
X XXXXXX*XXXXXX  XXXXXX
X        X    X  X     
XXXXXXXXXX    XXXX     


26, 63, (15, 15)
XXXXXXXXX      
X       X      
X       XXXX   
XX XXXX X  X   
XX X@XX    X   
X *** *  **X   
X  X XX *  X   
X  X XX  * XXXX
XXXX  *** *X  X
 X   XX   ....X
 X X   X X.. .X
 X   X X XX...X
 XXXXX *  X...X
     XX   XXXXX
      XXXXX    


27, 80, (23, 13)
 XXXXXXXXXXXXXXXXX     
 X...   X    X   XXX   
XX.....  *XX X X * X   
X......X  *  X  *  X   
X......X  X  X X X XX  
XXXXXXXXX *  * X X  XXX
  X     X*XX* XX XX   X
 XX   *    X *  *   X X
 X  XX XXX X  XXXXX*X X
 X * **     *   *     X
 X *    *XX* XXXXXXXX X
 XXXXXXX  @ XX      XXX
       XXXXXX          


28, 73, (15, 17)
     XXXXXXX   
     X@ X  X   
     X *   X   
    XXX XX X   
 XXXX *  X XX  
 X       X  XX 
 X * *XXXX * X 
 X ** X  X  *X 
 X*  *   X*  X 
XX  **X   ** XX
X **  X  X  * X
X     XXXX *  X
X  X*XX..XX   X
XXX .X....XXXXX
  X .......XX  
  X....   ..X  
  XXXXXXXXXXX  


29, 66, (24, 11)
                XXXXX   
       XXXXXX XXX   XXXX
   XXXXX    XXX * *  * X
XXXX  XX X* *    * X   X
X....   ** * *  *   X*XX
X.. X XX X   XXX*XX X  X
X....    X XXX    X    X
X....    X XX  *  XXX* X
X..XXXXXX  *  X  XXXX XX
XXXX    X   XXX    @  X 
        XXXXXXXXXXXXXXX 


30, 77, (14, 20)
 XXXXX        
 X   XXXXXXX  
 X * XXX   X  
 X *    ** X  
 XX XXXX   X  
XXX X  X XXX  
X   X  X@XX   
X **    * X   
X   X X * XXXX
XXXXX X   X  X
 X   *XXXX   X
 X  *     *  X
 XX   XXXXX XX
 XXXXXXXXXX  X
XX....X *  * X
X.....X **X  X
X.. ..X *  * X
X.....*   X  X
XX  XXXXXXXXXX
 XXXX         


31, 51, (15, 12)
 XXXXXXX       
 X  X  XXXXX   
XX  X  X...XXX 
X  *X  X...  X 
X * X** ...  X 
X  *X  X... .X 
X   X *XXXXXXXX
XX*       * * X
XX  X  ** X   X
 XXXXXX  XX**@X
      X      XX
      XXXXXXXX 


32, 74, (18, 16)
  XXXX            
  X  XXXXXXXXX    
 XX  XX @X   X    
 X  *X * *   XXXX 
 X*  *  X * *X  XX
XX  *XX X* *     X
X  X  X X   ***  X
X *    *  *XX XXXX
X * * X*X  X  X   
XX  XXX  XXX* X   
 X  X....     X   
 XXXX......XXXX   
   X....XXXX      
   X...XX         
   X...X          
   XXXXX          


33, 55, (13, 15)
      XXXX   
  XXXXX  X   
 XX     *X   
XX *  XX XXX 
X@* * X *  X 
XXXX XX   *X 
 X....X* * X 
 X....X   *X 
 X....  ** XX
 X... X *   X
 XXXXXX* *  X
      X   XXX
      X* XXX 
      X  X   
      XXXX   


34, 52, (12, 15)
XXXXXXXXXXXX
XX     XX  X
XX   *   * X
XXXX XX ** X
X   * X    X
X *** X XXXX
X   X X * XX
X  X  X  * X
X *X *X    X
X   ..X XXXX
XXXX.. * X@X
X.....X *X X
XX....X  * X
XXX..XX    X
XXXXXXXXXXXX


35, 85, (20, 16)
XXXXXXXXXXXX  XXXXXX
X   X    X@XXXX....X
X   **X       .....X
X   X XXX   XX ....X
XX XX XXX  X   ....X
 X * *     X XX XXXX
 X  * *XX  X       X
XXXX X  XXXX XX XX X
X  X X*   XX XX    X
X *  *  X XX XXXXXXX
X X * *    X X      
X  * XX XX X X      
X **     **  X      
XX XX XXX *  X      
 X    X X    X      
 XXXXXX XXXXXX      


36, 94, (18, 19)
     XXXX         
   XXX  XX        
XXXX  *  X        
X   * *  XXXX     
X *   X *   X XXXX
X  X  X   * X X..X
XX*X* XXXX*XXXX..X
 X   XXXXX XX ...X
 X*X XX@XX XX  ..X
 X X    *     ...X
 X   XXXX XXX  ..X
 XXX XX X  XX ...X
  XX* XXXX* XXX..X
  X   XX    X X..X
 XX **XX  * X XXXX
 X     **** X     
 X * XXX    X     
 X   X XXXXXX     
 XXXXX            


37, 82, (21, 15)
XXXXXXXXXXX          
X......   XXXXXXXXX  
X......   X  XX   X  
X..XXX *    *     X  
X... * * X  XXX   X  
X...X*XXXXX    X  X  
XXX    X   X*  X *XXX
  X  ** * *  *XX  * X
  X  *   X*X  XX    X
  XXX XX X  * XXXXXXX
   X  * * XX XX      
   X    *  *  X      
   XX   X X   X      
    XXXXX@XXXXX      
        XXX          


38, 65, (14, 15)
 XXXXXXXXX    
 X....   XX   
 X.X.X  * XX  
XX....X X @XX 
X ....X  X  XX
X     X* XX* X
XX XXX  *    X
 X*  * * *X  X
 X X  * * XX X
 X  XXX  XX  X
 X    XX XX XX
 X  * X  *  X 
 XXX* *   XXX 
   X  XXXXX   
   XXXX       


39, 98, (23, 18)
              XXX      
             XX.XXX    
             X....X    
 XXXXXXXXXXXXX....X    
XX   XX     XX....XXXXX
X  **XX  * @XX....    X
X      ** *X  ....X   X
X  * XX ** X X....X  XX
X  * XX *  X XX XXX  X 
XX XXXXX XXX         X 
XX   *  * XXXXX XXX  X 
X *XXX  X XXXXX X XXXX 
X   *   X       X      
X  * X* * *XXX  X      
X ***X *   X XXXX      
X    X  ** X           
XXXXXX   XXX           
     XXXXX             


40, 39, (11, 11)
      XXXX 
XXXXXXX @X 
X     *  X 
X   *XX *X 
XX*X...X X 
 X *...  X 
 X X. .X XX
 X   X X* X
 X*  *    X
 X  XXXXXXX
 XXXX      


41, 68, (20, 15)
           XXXXX    
          XX   XX   
         XX     X   
        XX  **  X   
       XX **  * X   
       X *    * X   
XXXX   X   ** XXXXX 
X  XXXXXXXX XX    X 
X..           ***@X 
X.X XXXXXXX XX   XX 
X.X XXXXXXX. X* *XXX
X........... X   * X
XXXXXXXXXXXXXX  *  X
             XX  XXX
              XXXX  


42, 68, (13, 18)
 XXXXXXXX    
 X@XX   XXXX 
 X *   *   X 
 X  * * ***X 
 X **X X   X 
XX*    *   X 
X  *  *****XX
X *XXXX X   X
X  *....X   X
X XX....X** X
X XX....   XX
X   ....X  X 
XX X....X**X 
 X X....X  X 
 X         X 
 XXXX XX*XXX 
    X    X   
    XXXXXX   


43, 73, (17, 16)
    XXXXXXXXXXXX 
    X          XX
    X  X X** *  X
    X* X*X  XX @X
   XX XX X * X XX
   X   * X*  X X 
   X   X *   X X 
   XX * *   XX X 
   X  X  XX  * X 
   X    XX **X X 
XXXXXX**   X   X 
X....X  XXXXXXXX 
X.X... XX        
X....   X        
X....   X        
XXXXXXXXX        


44, 114, (25, 19)
      XXXXXX             
   XXXXX   X             
   X   X X XXXXX         
   X * X  *    XXXXXX    
  XX*  XXX XX       X    
XXX  ** * * X  XX   XXXXX
X       *   XXXXXX XX   X
X  XXXXXXXX X@   X X  X X
XX XXX      XXXX X*X X  X
 X XXX XXXX XX.. X   * XX
 X  *  *  X*XX.. X*XX  XX
 X  X X X     ..XX XX * X
 XXXX   X XX X..X    *  X
    XXXXX    X..X X X  XX
        XXXXXX..X   X XX 
             X..XXXXX  X 
             X..       X 
             XX  XXX  XX 
              XXXXXXXXX  


45, 55, (19, 11)
        XXXXXXX    
    XXXXX  X  XXXX 
    X   X   *    X 
 XXXX X** XX XX  X 
XX      X X  XX XXX
X  XXX *X*  *  *  X
X...    X XX  X   X
X...X    @ X XXX XX
X...X  XXX  *  *  X
XXXXXXXX XX   X   X
          XXXXXXXXX


46, 95, (22, 17)
    XXXXXXXXX  XXXX   
    X   XX  XXXX  X   
    X   *   X  *  X   
    X  X XX X     XXXX
    XX *   * **X X   X
    XXXX  X  X * *   X
XXXXX  XXXX    XXX...X
X   X* X  X XXXX.....X
X      X  X X XX.....X
XXXXXX X  X*   XXX...X
   X   XX X *X   X...X
  XX       *  *X XXXXX
 XX ***XX  X *   X    
 X   X  X XXX  XXX    
 X   *  X* @XXXX      
 XXXXX  X   X         
     XXXXXXXX         


47, 66, (19, 15)
 XXXXX             
 X   X             
 X X XXXXXX        
 X      *@XXXXXX   
 X * XX* XXX   X   
 X XXXX *    * X   
 X XXXXX X  X* XXXX
XX  XXXX XX*      X
X  *X  *  X XX XX X
X         X X...X X
XXXXXX  XXX  ...  X
     XXXX X X...X X
          X XXX X X
          X       X
          XXXXXXXXX


48, 63, (16, 15)
       XXXX     
       X  XX    
       X   XX   
       X ** XX  
     XXX*  * XX 
  XXXX    *   X 
XXX  X XXXXX  X 
X    X X....* X 
X X   * ....X X 
X  * X X.&..X X 
XXX  XXXX XXX X 
  XXXX @*  XX*XX
     XXX *     X
       X  XX   X
       XXXXXXXXX


49, 88, (19, 16)
      XXXXXXXXXXXX 
     XX..    X   X 
    XX..& *    * X 
   XX..&.X X X* XX 
   X..&.X X X *  X 
XXXX...X  X    X X 
X  XX X          X 
X @* * XXX  X X XX 
X *   *   X X   X  
XXX**   X X X X X  
  X   *   X X XXXXX
  X *X XXXXX      X
  X*   X   X   X  X
  X  XXX   XX     X
  X  X      X    XX
  XXXX      XXXXXX 


50, 91, (21, 16)
     XXXXXXXXXXXXX   
     X    XXX    X   
     X     * *  XXXX 
   XXXX X   * *    X 
  XX *  X*XXXX * * X 
XXX   X X   XXX  * X 
X *  *  X  *  X XXXX 
X XX*XXXX X*X  *  XXX
X XX  XXX X X X  *  X
X    @*   *   X * X X
XXXXX  X  XX  X *X  X
  X... XXXXX*  X  X X
  X.......X ** X* X X
  X.......X         X
  X.......XXXXXXX  XX
  XXXXXXXXX     XXXX 


51, 67, (16, 14)
XXXXX XXXX      
X...X X  XXXX   
X...XXX  *  X   
X....XX *  *XXX 
XX....XX   *  X 
XXX... XX * * X 
X XX    X  *  X 
X  XX X XXX XXXX
X * X X*  *    X
X  * @ *    *  X
X   X * ** * XXX
X  XXXXXX  XXX  
X XX    XXXX    
XXX             


52, 72, (21, 14)
 XXXX                
XX  XXXXX            
X       X XXXXX      
X *XXX  XXX   X      
X..X  *X X  X X      
X..X      **X XXX    
X.&X X  X* *    XXXXX
X..X  XX     XX*X   X
X.&*  * X XX  *     X
X..XX  *   X   XXXXXX
X.&XX*XX   XXXXX     
X..  * XXXXX         
X  X @ X             
XXXXXXXX             


53, 80, (13, 19)
   XXXXXXXXXX
   X  XXX   X
   X *   *  X
   X  XXXX*XX
   XX X  X  X
  XX  X.&   X
  X  XX..X  X
  X @ X.&X XX
  X X*X..X* X
  X * X..X  X
  X X X&&X  X
  X * X..X*XX
  X    .&X  X
 XXX  X  X  X
XX    XXXX  X
X  XXXXXXX*XX
X *      *  X
X  XX   X   X
XXXXXXXXXXXXX


54, 118, (23, 20)
 XXXXXXXXXXXXXXXXXXXXX 
 X   XX  X   X   X   X 
 X *     *   *   *   XX
XXXXX X  X   XXX XX*XXX
X   X XX*XXXXXX   X   X
X *   X ......X   X * X
XX X  X ......XXXXX   X
XX XXXXXXXXX..X   X XXX
X          X..X *   X  
X XX XXX XXX..XX X  XXX
X X   X   XX..XX XXX  X
X   @      *..X       X
X X   X   XX  X   XX  X
XXXXX XXXXXXXXXXXXXX XX
X          X   X    * X
X *  X * * *   X X    X
X X*XX *X  XX XX    X X
X  * ** XXXX *  * X X X
X          X   X      X
XXXXXXXXXXXXXXXXXXXXXXX


55, 88, (22, 15)
 XXXXXXXXXXXXXXXXXXXXX
XX                   X
X    * X      XX X   X
X  XXXXXX XXX  X*XX XX
XX*X   XX*X....   X X 
X  X    * X....XX X X 
X * X X X X....XX   X 
X * X**   X....XX*X X 
X X *@*XX*X....XX   X 
X   ***   X....X    X 
X  *X   X XXXXXX *XXX 
XX  X XXX**  *   * X  
XX     X *  * XX   X  
 XXXXX   X   XXXXXXX  
     XXXXXXXXX        


56, 59, (14, 16)
XXXXXXXXXX    
X        XXXX 
X XXXXXX X  XX
X X * * *  * X
X       X*   X
XXX*  **X  XXX
  X  XX X *XX 
  XX*X   * @X 
   X  * * XXX 
   X X   *  X 
   X XX   X X 
  XX  XXXXX X 
  X         X 
  X.......XXX 
  X.......X   
  XXXXXXXXX   


57, 50, (18, 11)
         XXXX     
 XXXXXXXXX  XX    
XX  *      * XXXXX
X   XX XX   XX...X
X X** * **X*XX...X
X X    @  X   ...X
X  *X XXX**   ...X
X *  **  * XX....X
XXX*       XXXXXXX
  X  XXXXXXX      
  XXXX            


58, 133, (27, 20)
              XXXXXX       
          XXXXX    X       
          X  XX X  XXXXX   
          X   &.X..X   X   
 XXXXX XXXX *X.X...    X   
 X   XXX  XX X&....XX XX   
 X *      XX X..X..XX X    
XXXXXX X   X X&.XXXXX X    
X   X *X*X X X..XXXXX X    
X *  *     X X&.    X X    
XX XX  * XXX X  XX  X X    
 X  *  * XXX XXXXX XX X    
 XXX*XXX*XXX  XXXX XX X    
XXXX X         XXX  X X    
X  * X  *XXXX  XXX**X@XXXXX
X      * X X  XXXX  X*X   X
XXXX X  *X X              X
   X  *  X XX  XX  XXXXXXXX
   XX  XXX  XXXXXXXX       
    XXXX                   


59, 152, (29, 20)
         XXXX                
         X  X                
         X  XXXXXXXX         
   XXXXXXX  X      X         
   X   X X X X X   XX        
   X *     *  XX  * X        
  XXX *X X  X X     XXXXXXXXX
  X  *  X  *X X ** X   X X  X
 XX X   X     XXX    * X X  X
 X  X*   X XXX  X  X **X X  X
 X    *XX *  X   XX *  X X XX
XXXX* * X    XX  X   *    ..X
X  X    XXX X * * XXX  XXX.&X
X     XX  ** @  *     XX....X
X  XX  XX   *  X*X  XX....&.X
XX X  *  X X *XX  XX....&.XXX
XX XX  *  X * X  X....&.XXX  
X    * XXXX   X ....&.XXX    
X   X  X  X  X  ..&.XXX      
XXXXXXXX  XXXXXXXXXXX        


60, 108, (26, 16)
        XXXXX             
        X   XXXX          
        X *    XXXX  XXXX 
        X   X *X  XXXX  X 
XXXXXXXXXXX X   *   X   X 
X..     X *  XXXX X  X  X 
X..*  X   *  X  * X * .XX 
X.&X X * * XX  XX    X.X  
X..X* @ X   XX    ** X.X  
X..X * *  * * XX   XX .X  
X.&** X XX   * X*X * X.X  
X..X      XX   X     X.X  
X..XXXXXXX  XXX XXXXXX.XX 
X **                  &.XX
X  XXXXXXXXXXXXXXXXXX  ..X
XXXX                XXXXXX
```
