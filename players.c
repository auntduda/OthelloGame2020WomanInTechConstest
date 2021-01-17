/* Michael Hanna, mwhanna
 * CS 152, Spring 2017
 * Project 2
 */
  
#include <stdlib.h>
#include <stdio.h>
#include "players.h"

/*returns a pseudo-boolean int for if the given char is a valid input*/
int valid_rc(char c){
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

/*converts from a row / column display character to the corresponding row / 
column index*/
unsigned ctrc(char c){
    if(c <= '9'){
        return c - '0';
    } else if(c <= 'Z'){
        return c - 'A' + 10;
    } else{
        return c - 'a' + 36;
    }
}

/*prompts the user for a move, telling them if the move is invalid, and returns
the valid move*/
pos human(game* g){
    char c1, c2;
    unsigned u1, u2;
    int invalid_input, invalid_move;
    pos p;
    do{
        printf("%s", (g->next)? "White: ": "Black: ");
        scanf(" %c%c", &c1, &c2);
        printf("Your input: r: %c, c: %c\n", c1, c2);
        
        u1 = ctrc(c1);
        u2 = ctrc(c2);
        invalid_input = !in_bounds(g, u1, u2);
        if(invalid_input){
            printf("\nInput invalid; please input valid row / column #\n");
        }
        
        p = make_pos(u1, u2);
        if(!invalid_input){
            invalid_move = !outflanks(g, p);
            if(invalid_move){
                printf("\nInput move does not outflank; input valid move\n");
            }
        }
    }while(invalid_input || invalid_move);
    return make_pos(ctrc(c1), ctrc(c2));
}


/*given pos p, a valid direction (i.e. x and y that do ouflank), return the
number of pieces that will be outflanked in the x y direction from pos p*/
unsigned n_traverse (game* g, pos p, int x, int y){
    square ts = (g->next)? WHITE: BLACK;
    p.r += x;
    p.c += y;
    unsigned n = 0;
    square ns = board_get(g->b, p);
    
    while(ns != ts){
        n++;
        p.r += x;
        p.c += y;
        ns = board_get(g->b, p);
    }
    return n;
}

/*returns the number of outflanked pieces given a piece (of the color specified
by the turn in g) placed at p.*/
unsigned n_flips(game* g, pos p){
    int i, j;
    unsigned n = 0;
    for(i = -1; i <= 1; i++){
        for(j = -1; j <= 1; j++){
            if(outflank_path(g, p, i, j)){//outflank_path in logic.c
                n += n_traverse(g, p, i, j);
            }
        }
    }
    return n;
}

/*given a game, updates n to the number of flips of the highest-flipping valid
corner move, and p to the position thereof*/
void corners(game* g, unsigned* n, pos* p){
    unsigned nr = g->b->nrows, nc = g->b->ncols;
    pos tp = make_pos(0,0);
    unsigned nf;
    if(outflanks(g, tp)){
        nf = n_flips(g, tp);
        *p = tp;
        *n = nf;
    }
    tp = make_pos(0, nc - 1);
    if(outflanks(g, tp)){
        nf = n_flips(g, tp);
        if(nf > *n){
            *p = tp;
            *n = nf;
        }
    }
    tp = make_pos(nr - 1, 0);
    if(outflanks(g, tp)){
        nf = n_flips(g, tp);
        if(nf > *n){
            *p = tp;
            *n = nf;
        }
    }
    tp = make_pos(nr - 1, nc - 1);
    if(outflanks(g, tp)){
        nf = n_flips(g, tp);
        if(nf > *n){
            *p = tp;
            *n = nf;
        }
    }
}

/*given a game, updates n to the number of flips of the highest-flipping valid
edge move, and p to the position thereof*/
void edges(game* g, unsigned* n, pos* p){
    unsigned nr = g->b->nrows, nc = g->b->ncols;
    pos tp;
    unsigned nf, i, j, rb = nr - 1, cb = nc - 1;
    
    for(j = 1; j < cb; j++){
        tp = make_pos(0, j);
        if(outflanks(g, tp)){
            nf = n_flips(g, tp);
            if(nf > *n){
                *p = tp;
                *n = nf;
            }
        }
    }
    for(i = 1; i < rb; i++){
        tp = make_pos(i, 0);
        if(outflanks(g, tp)){
            nf = n_flips(g, tp);
            if(nf > *n){
                *p = tp;
                *n = nf;
            }
        }
        tp = make_pos(i, cb);
        if(outflanks(g, tp)){
            nf = n_flips(g, tp);
            if(nf > *n){
                *p = tp;
                *n = nf;
            }
        }
    }
    for(j = 1; j < cb; j++){
        tp = make_pos(rb, j);
        if(outflanks(g, tp)){
            nf = n_flips(g, tp);
            if(nf > *n){
                *p = tp;
                *n = nf;
            }
        }
    }
}

/*given a game, updates n to the number of flips of the highest-flipping valid
edge move, and p to the position thereof*/
void interior(game* g, unsigned* n, pos* p){
    unsigned nr = g->b->nrows, nc = g->b->ncols;
    pos tp;
    unsigned nf, i, j, rb = nr - 1, cb = nc - 1;
    
    for(i = 1; i < cb; i++){
        for(j = 1; j < rb; j++){
            tp = make_pos(i, j);
            if(outflanks(g, tp)){
                nf = n_flips(g, tp);
                if(nf > *n){
                    *p = tp;
                    *n = nf;
                }
            }
        }
    }
}


/*checks if the game is over, and returns the winner*/
int did_i_win(game* g){
    if(!game_over(g)){
        return 0;
    }
    unsigned go = game_outcome(g);
    return (go < 2)? (go? -1: 1):0;
}

/*counts the number of pieces on the board, unweighted*/
int piece_counting(game* g){
    unsigned black = 0, white = 0;
    piece_count(g, &black, &white);//in logic.c
    return black - white;
}

/*hard-copies a game*/
game* game_copy(game* g){
    if(!g){
        fprintf(stderr, "game_copy: game is null");
        exit(1);
    }
    unsigned nrows = g->b->nrows, ncols = g->b->ncols;
    game* ng = new_game(nrows, ncols, g->b->type);
    ng->next = g->next;    
    
    unsigned i, j;
    if(g->b->type == CELLS){
        for(i = 0; i < nrows; i++){
            for(j = 0; j < ncols; j++){
                ng->b->u.cells[i][j] = g->b->u.cells[i][j];
            }
        }
    } else {//copying a bitrep board is much faster
        unsigned nrc = nrows*ncols, num_entries = nrc / 16;
        if(nrc%16){
            num_entries++;
        }
        for(i = 0; i < num_entries; i++){
            ng->b->u.bits[i] = g->b->u.bits[i];
        }
    }
    return ng;
}