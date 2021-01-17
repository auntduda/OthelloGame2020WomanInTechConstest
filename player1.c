
#include <stdlib.h>
#include <stdio.h>
#include "player1.h"

/*retorna o movimento válido que vira mais peças*/
pos player1(game* g){
    unsigned i, j;
    pos p;
    pos best_p;
    unsigned best_n=0;
    for(i = 0; i < g->b->nrows; i++){
        for(j = 0; j < g->b->ncols; j++){
            p = make_pos(i, j);
            
            if(i==g->b->nrows || j==g->b->ncols){ /*minha estrategia era nao encostar nas paredes, mas nao deu tempo de desenvolver mais*/
                continue;
            }

            if(flanqueia(g, p) && n_vira(g,p)>best_n){
                best_p=p;
                best_n=n_vira(g,p);
            }
        }
    }
    return best_p;
}