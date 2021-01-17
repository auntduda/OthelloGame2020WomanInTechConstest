/* Michael Hanna, mwhanna
 * CS 152, Spring 2017
 * Project 2
 */
  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "players.h"
#include "player1.h"
#include "player2.h"

/*Given the player type as its one-letter abbreviation*/
/*return a player of that type*/
pos (*player_type(char type))(game*){
    switch(type){       
        case 'f':
            return player1;
        
        case 's':
            return player2;
            
        default:
            return human;
    }
}

int main(int argc, char* argv[]) {
    /*we only want to parse 4 arguments max here, so this is just done manually*/
    char black;
    char white;

    srand(time(NULL));
    
    if(argc > 1){
        black = 'h';
        white = 'h';
    } else {
        black = 's';
        white = 'f';
        if(rand()%2){
            black = 'f';
            white = 's';
        }
    }
    
	pos (*player_black)(game*) = player_type(black);
    pos (*player_white)(game*) = player_type(white);
    
    game* g = new_game(8, 8, CELLS);
    pos this_move;
    int go;
    char* v;

    int turns = 0;
    
    while(!game_over(g)){
        turns++;
        game_show(g);
        if(!exists_move(g)){
            printf("No valid moves for %s; turn passed to %s\n", 
            (g->next)? "White": "Black", (!g->next)? "White": "Black");
            pass(g);
        }
        this_move = (g->next)? player_white(g): 
                               player_black(g);
        printf("Move applied at %d, %d:\n", this_move.r, this_move.c);
        apply_move(g, this_move);
    }
    game_show(g);
    go = game_outcome(g);
    v = (go < 2)? (go? "White wins": "Black wins"):"Draw";
    if(white=='f')printf("First player is white and second player is black\n");
    else printf("First player is black and second player is white\n");
    printf("Game Outcome: %s\n\n", v);
    game_free(g);
}
