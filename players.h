/* Michael Hanna, mwhanna
 * CS 152, Spring 2017
 * Project 2
 */

#ifndef __PLAYERS_H
#define __PLAYERS_H

#include "logic.h"

/*prompts the user for a move, telling them if the move is invalid, and returns
the valid move*/
pos human(game* g);

unsigned n_traverse (game* g, pos p, int x, int y);
unsigned n_flips(game* g, pos p);
void corners(game* g, unsigned* n, pos* p);
void edges(game* g, unsigned* n, pos* p);
void interior(game* g, unsigned* n, pos* p);
game* game_copy(game* g);

/*checks if the game is over, and returns the winner*/
int did_i_win(game* g);

/*counts the number of pieces on the board, unweighted*/
int piece_counting(game* g);

/*takes in the value to be incremented, # rows - 1, # cols - 1, edge weight,
corner weight, position row, position col, and increments the value*/
void add_weight(unsigned* n, unsigned nr1, unsigned nc1, int ew, int cw, 
                unsigned pr, unsigned pc);
                        
#endif