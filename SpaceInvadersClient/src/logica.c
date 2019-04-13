#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "logica.h"
//Structs
void inicializar(struct Jugador *ju, struct Enemigos *e, struct Balas *b, struct Escudo *esc[], int filas, int columnas){
    ju->posx = (columnas-1)/2;
    ju->posy = filas-1;
    ju->vidas = 3;
    ju->vivo = true;
    b->vivo = false;
    reiniciarEnemigos(e);
    colocarEscudos(esc);
}

void reiniciarEnemigos(struct Enemigos *e){
    for(int i = 2; i < 7; i++)
    {
        for(int j = 3; j < 14; j++)
        {
            switch (i)
            {
                case 2:
                    e->pulpos[j-3].posy = i;
                    e->pulpos[j-3].posx = j;
                    e->pulpos[j-3].puntos = 40;
                    e->pulpos[j-3].vivo = true;
                    break;
                case 3:
                    e->cangrejos[j-3].posy = i;
                    e->cangrejos[j-3].posx = j;
                    e->cangrejos[j-3].puntos = 20;
                    e->cangrejos[j-3].vivo = true;
                    break;
                case 4:
                    e->cangrejos[j+8].posy = i;
                    e->cangrejos[j+8].posx = j;
                    e->cangrejos[j+8].puntos = 20;
                    e->cangrejos[j+8].vivo = true;
                    break;
                case 5:
                    e->calamares[j-3].posy = i;
                    e->calamares[j-3].posx = j;
                    e->calamares[j-3].puntos = 10;
                    e->calamares[j-3].vivo = true;
                    break;
                case 6:
                    e->calamares[j+8].posy = i;
                    e->calamares[j+8].posx = j;
                    e->calamares[j+8].puntos = 10;
                    e->calamares[j+8].vivo = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void colocarEscudos(struct Escudo *esc[]){
    for(int i = 0; i < 4; i++)
    {
        colocarSeccionesEscudo(3+3*i,esc[i]);
    }
}

void colocarSeccionesEscudo(int posX , struct Escudo *esc){
    //posX
    esc->SuperiorDer.posx = posX;
    esc->SuperiorIzq.posx = posX+1;
    esc->InferiorDer.posx = posX;
    esc->InferiorIzq.posx = posX+1;
    //PosY
    esc->SuperiorDer.posy = 13;
    esc->SuperiorIzq.posy = 13;
    esc->InferiorDer.posy = 14;
    esc->InferiorIzq.posy = 14;
    //Vidas
    int vidas = 2;
    esc->SuperiorDer.vidas = vidas;
    esc->SuperiorIzq.vidas = vidas;
    esc->InferiorDer.vidas = vidas;
    esc->InferiorIzq.vidas = vidas;
    //Vivo
    esc->SuperiorDer.vivo = true;
    esc->SuperiorIzq.vivo = true;
    esc->InferiorDer.vivo = true;
    esc->InferiorIzq.vivo = true;
}

void detectarColision(struct Jugador *ju, struct Enemigos e, int *isdead){
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 11; i++)
        {
            switch (i)
            {
                case 0:
                    if ((e.pulpos[j].posy == ju->posy) && (e.pulpos[j].posx == ju->posy) && (e.pulpos[j].vivo)) {
                        ju->vivo = false;
                        *isdead = TRUE;
                    }
                    break;
                case 1:
                    if ((e.cangrejos[j].posy == ju->posy) && (e.cangrejos[j].posx == ju->posy) && (e.cangrejos[j].vivo)) {
                        ju->vivo = false;
                        *isdead = TRUE;
                    }
                    break;
                case 2:
                    if ((e.cangrejos[11+j].posy == ju->posy) && (e.cangrejos[11+j].posx == ju->posy) && (e.cangrejos[11+j].vivo)) {
                        ju->vivo = false;
                        *isdead = TRUE;
                    }
                    break;
                case 3:
                    if ((e.calamares[j].posy == ju->posy) && (e.calamares[j].posx == ju->posy) && (e.calamares[j].vivo)) {
                        ju->vivo = false;
                        *isdead = TRUE;
                    }
                    break;
                case 4:
                    if ((e.calamares[11+j].posy == ju->posy) && (e.calamares[11+j].posx == ju->posy) && (e.calamares[11+j].vivo)) {
                        ju->vivo = false;
                        *isdead = TRUE;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void meDispararon(struct Jugador *ju, struct Misil *m, int *isdead){
    if ((m->posy == ju->posy) && (m->posx == ju->posy) && (m->vivo)) {
        ju->vidas--;
        m->vivo = false;
        if (ju->vidas == 0) {
            ju->vivo = false;
            *isdead = TRUE;
        }

    }
}

void leDispare(struct Enemigos *e, struct Balas *b){
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 11; i++)
        {
            switch (i)
            {
                case 0:
                    if ((e->pulpos[j].posy == b->posy) && (e->pulpos[j].posx == b->posy) && (e->pulpos[j].vivo) && (b->vivo)) {
                        b->vivo = false;
                        e->pulpos[j].vivo = false;
                        e->enemigosRestantes--;
                    }
                    break;
                case 1:
                    if ((e->cangrejos[j].posy == b->posy) && (e->cangrejos[j].posx == b->posy) && (e->cangrejos[j].vivo) && (b->vivo)) {
                        b->vivo = false;
                        e->cangrejos[j].vivo = false;
                        e->enemigosRestantes--;
                    }
                    break;
                case 2:
                    if ((e->cangrejos[j+11].posy == b->posy) && (e->cangrejos[j+11].posx == b->posy) && (e->cangrejos[j+11].vivo) && (b->vivo)) {
                        b->vivo = false;
                        e->cangrejos[j].vivo = false;
                        e->enemigosRestantes--;
                    }
                    break;
                case 3:
                    if ((e->calamares[j].posy == b->posy) && (e->calamares[j].posx == b->posy) && (e->calamares[j].vivo) && (b->vivo)) {
                        b->vivo = false;
                        e->calamares[j].vivo = false;
                        e->enemigosRestantes--;
                    }
                    break;
                case 4:
                    if ((e->calamares[j+11].posy == b->posy) && (e->calamares[j+11].posx == b->posy) && (e->calamares[j+11].vivo) && (b->vivo)) {
                        b->vivo = false;
                        e->calamares[j].vivo = false;
                        e->enemigosRestantes--;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    if (e->enemigosRestantes == 0) {
        reiniciarEnemigos(&e);
    }
}

void debilitarEscudo(struct Escudo *esc[], struct Misil *m){
    for(int i = 0; i < 4; i++)
    {
        debilitarSeccionEscudo(esc[i],m);
    }

}
void debilitarSeccionEscudo(struct Escudo *esc, struct Misil *m){
    if (esc->SuperiorIzq.vivo && (esc->SuperiorIzq.posx == m->posx) && (esc->SuperiorIzq.posy == m->posy)) {
        esc->SuperiorIzq.vidas--;
        if (esc->SuperiorIzq.vidas == 0) {
            esc->SuperiorIzq.vivo = false;
        }
    }
    else if (esc->SuperiorDer.vivo && (esc->SuperiorDer.posx == m->posx) && (esc->SuperiorDer.posy == m->posy)) {
        esc->SuperiorDer.vidas--;
        if (esc->SuperiorDer.vidas == 0) {
            esc->SuperiorDer.vivo = false;
        }
    }
    else if (esc->SuperiorDer.vivo && (esc->SuperiorDer.posx == m->posx) && (esc->SuperiorDer.posy == m->posy)) {
        esc->SuperiorDer.vidas--;
        if (esc->SuperiorDer.vidas == 0) {
            esc->SuperiorDer.vivo = false;
        }
    }
    else if (esc->InferiorDer.vivo && (esc->InferiorDer.posx == m->posx) && (esc->InferiorDer.posy == m->posy)) {
        esc->InferiorDer.vidas--;
        if (esc->InferiorDer.vidas == 0) {
            esc->InferiorDer.vivo = false;
        }
    }
}

void ejecutarAccion(int accion, struct Jugador *ju, struct Balas *b){
    switch (accion)
    {
        case 0:
            break;
        case 1:
            b->vivo = true;
            b->posx = ju->posx;
            b->posy = ju->posy;
            break;
        case 2:
            if(ju->posx<17){
                ju->posx++;
            }
            break;
        case 3:
            if(ju->posx>0){
                ju->posx--;
            }
            break;
        default:
            break;
    }
}
