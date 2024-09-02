#include <stdio.h>
#include <stdbool.h>

#include "life.h"

//testing connectivity 
/* Be sure to read life.h and the other given source files to understand
 * what they provide and how they fit together.  You don't have to
 * understand all of the code, but you should understand how to call
 * parse_life() and clearterm().
 */

/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argument (which is required) is a starting state in one of the Life
 * formats supported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 */
//adha0wd7haw0d8hasd87hawd08awr381byoabsdaousbd

void free_grid2(char grid[2][26][82], int next){
    for(int i=0; i<26; i++){
        for(int a=0; a<82; a++){
            grid[next][i][a] = DEAD;
        }
    }
}

int convert(char a){
    int x=0;
    if(a==48) x=0;
    else if(a==49) x=1;
    else if(a==50) x=2;
    else if(a==51) x=3;
    else if(a==52) x=4;
    else if(a==53) x=5;
    else if(a==54) x=6;
    else if(a==55) x=7;
    else if(a==56) x=8;
    else if(a==57) x=9;
    return x;
}

/*
• If c is alive and has fewer than 2 live neighbors, it dies.
• If c is alive and has more than 3 live neighbors, it dies.
• If c is alive and has exactly 2 or 3 live neighbors, it remains alive.
• If c is dead and has exactly 3 live neighbors, it becomes alive
*/

int computeneighbors(char grid[2][26][82], int current, int y, int x){
    int liveneighbors = 0;
    if(grid[current][y][x]==LIVE) liveneighbors = liveneighbors-1;
    for(int i=y-1; i<y+2; i++){
        for(int a=x-1; a<x+2; a++){
            if(grid[current][i][a] == LIVE){
                liveneighbors = liveneighbors + 1;
            }   
        }
    }
    
    return liveneighbors;
}


void printgeneration(char grid[2][26][82],  int next){
   
    for(int i=1; i<25; i++){
        for(int a=1; a<81; a++){
            printf("%c", grid[next][i][a]);
        }
        printf("\n");
    } 
}


//computes and calls print at the end of it
void computegeneration(char grid[2][26][82], int generationlimit){

    int currentgeneration = 1;
    int next=0;
    while(currentgeneration<=generationlimit){
    for (int current = 0; ; current = ( current + 1) % 2) {
      
        if(current==0) next=1;
        if(current==1) next=0;
        
    free_grid2(grid, next);

    for(int i=1; i<25; i++){
        for(int a=1; a<81; a++){
            if(grid[current][i][a] == DEAD && computeneighbors(grid, current, i, a)==3){
                //
                grid[next][i][a] = LIVE;
            }
            else if (grid[current][i][a] == LIVE && computeneighbors(grid, current, i, a)<2){
                //
                grid[next][i][a] = DEAD;
            }
            else if (grid[current][i][a] == LIVE && computeneighbors(grid, current, i, a)>3){
                //
                grid[next][i][a] = DEAD;
            }
            else if (grid[current][i][a] == LIVE && (computeneighbors(grid, current, i, a) == 2 || computeneighbors(grid, current, i, a) == 3)){
                //
                grid[next][i][a] = LIVE;
            }
            
        }
    }
    
    currentgeneration++;
    if(currentgeneration>generationlimit) break;
    }
    
    }


    printgeneration(grid, next);
}





int main(int argc, char *argv[])
{

    //create a function that converts argv[2] the gen limit number to multidigits in case the *char is passed as something like "52" or other multidigits

    if(argc<1){
        printf("ERROR0\n");
        return -1;
    }
    if(argc>3){
        printf("ERROR1\n");
         return -1;
         } 

    if(*argv[2]<48 || *argv[2]>57){
        printf("ERROR2\n");
        return -1;
    }


    int generationlimit = 0;
    for(int i=0; argv[2][i]!='\0'; i++){
        generationlimit = generationlimit * 10 + convert(argv[2][i]);
    }
   
    int y = GRIDY+2;
    int x = GRIDX+2;
    char **gridstart = parse_life(argv[1]);
    char gridarray[2][y][x];

    //fill the array with empty dead cells to create the barrier

    for(int z=0; z<2; z++){
    for(int i=0; i<y; i++){
        for(int a=0; a<x; a++){
            gridarray[z][i][a] = DEAD;
        }
    }
    }

    

    //copy the parsed doublepointer onto a usable array
    for(int i=0; i<24; i++){
        for(int a=0; a<80; a++){
            gridarray[0][i+1][a+1] = gridstart[i][a];
        }
    }

    if(generationlimit==0){
    printgeneration(gridarray, 0);
    return 0;
    }

  
    computegeneration(gridarray, generationlimit);
    
    
    return 0;
}
