#ifndef __AUX_H
#define __AUX_H

#include "players.h"

/* se eu jogar na posição p, eu viro alguma peça do inimigo? */
/* equivalente: é um movimento válido? */
int flanqueia(game* g, pos p);

/* lista das posicoes dos cara q vira se colocar naquela posicao*/
poslist* vira(game* g, pos p);

/*quantos vira se colocar naquela posicao*/
unsigned n_vira(game* g, pos p);

/*copia o jogo*/
game* copia_jogo(game* g);

/*jogada de canto que mais vira*/
void melhor_canto(game* g, unsigned* n, pos* p);

/*jogada de lado que mais vira*/
void melhor_lado(game* g, unsigned* n, pos* p);

/*jogada de dentro que mais vira*/
void melhor_interior(game* g, unsigned* n, pos* p);

/*qual a cor da proxima pessoa que joga*/
square proxima_cor(game* g);

                        
#endif