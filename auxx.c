#include <stdlib.h>
#include <stdio.h>
#include "auxx.h"

int flanqueia(game* g, pos p){
	return outflanks(g,p);
}

poslist* vira(game* g, pos p){
	return flips(g,p);
}

unsigned n_vira(game* g, pos p){
	return n_flips(g,p);
}

game* copia_jogo(game* g){
	return game_copy(g);
}

void melhor_canto(game* g, unsigned* n, pos* p){
	return corners(g, n, p);
}

void melhor_lado(game* g, unsigned* n, pos* p){
	return edges(g, n, p);
}

void melhor_interior(game* g, unsigned* n, pos* p){
	return interior(g, n, p);
}

square proxima_cor(game* g){
	return  (g->next)? WHITE: BLACK;
}