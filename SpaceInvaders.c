#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Structs
struct Jugador
{
    int posx;
    int posy;
    int vidas;
    bool vivo;
};
struct Calamar
{
    int posx;
    int posy;
    int puntos; //10
    bool vivo;
};
struct Cangrejo
{
    int posx;
    int posy;
    int puntos;//20
    bool vivo;
};
struct Pulpo
{
    int posx;
    int posy;
    int puntos;//40
    bool vivo;
};
struct Enemigos
{
    struct Calamar calamares[22];
    struct Cangrejo cangrejos[22];
    struct Pulpo pulpos[11];
};

struct Platillo
{
    int posx;
    int posy;
    int puntos; //50 + (rand() % 51)
    bool vivo;
};
struct Misil
{
    int posx;
    int posy;
    bool vivo;
};

struct Balas
{
    int posx;
    int posy;
    bool vivo;
};
struct Escudo
{
    int posx;
    int posy;
    int vidas;
    bool vivo;
};


//Funciones
void inicializar(struct Jugador *j, struct Enemigos *e, struct Balas *b[], int filas, int columnas);//posiciones iniciales
void reiniciarEnemigos(struct Enemigos *e); //posicion inicial enemigos
void iniciarBalas(struct Balas *b[]); //inicializa las balas
void colocarEscudos(struct Escudo *esc[]); //posicion inicial bunkers
void detectarColision(struct Jugador *j, struct Enemigos e); //detecta si esta en un rango de colision 
void meDispararon(struct Jugador *j, struct Misil *m); //detecta si el jugador fue impactado po una bala enemiga
void leDispare(struct Enemigos *e, struct Balas *b, int *res); //detecta si un enemigo fue impactado por una bala aleada
void debilitarEscudo(struct Escudo *esc, struct Misil *m); //detecta si un escudo fue impactado por una bala enemiga



int main()
{
    int fil = 17;
    int col = 17;
    int enemigosRestantes = 55;
    int puntaje = 0;
    struct Jugador jugador;
    struct Enemigos enemigos;
    struct Balas balas[5];
    struct Escudo escudos[16];
    inicializar(&jugador,&enemigos,fil,col); 
    return 0;
}

void inicializar(struct Jugador *j, struct Enemigos *e, struct Balas *b[], int filas, int columnas){
    j->posx = (columnas-1)/2;
    j->posy = filas-1;
    j->vidas = 3;
    j->vivo = true;
    reiniciarEnemigos(&e);
    iniciarBalas(&b);
}

void reiniciarEnemigos(struct Enemigos *e){
    for(int i = 2; i < 7; i++)
    {
        for(int j = 3; j < 14; j++)
        {
            if (i==2) {
                e->pulpos[j-3].posy = i;
                e->pulpos[j-3].posx = j;
                e->pulpos[j-3].puntos = 40;
                e->pulpos[j-3].vivo = true;
            }
            else if (3<=i<5) {
                e->cangrejos[j-3].posy = i;
                e->cangrejos[j-3].posx = j;
                e->cangrejos[j-3].puntos = 20;
                e->cangrejos[j-3].vivo = true;
            }
            else
            {
                e->calamares[j-3].posy = i;
                e->calamares[j-3].posx = j;
                e->calamares[j-3].puntos = 10;
                e->calamares[j-3].vivo = true;
            }
        }
    }
}

void iniciarBalas(struct Balas *b[]){
    for(int i = 0; i < 5; i++)
    {
        b[i]->vivo = false;
    }
}

void colocarEscudos(struct Escudo *esc[]){//incompleta, no sirve aun
    for(int i = 13; i < 15; i++)
    {
        for(int j = 3; j < 14; j = j + 2)
        {
            esc[j-3]->posx = j;
            esc[j-3]->posy = i;
            esc[j-3]->vivo = true;
            esc[j-3]->vidas = 2;
            esc[j-2]->posx = j + 1;
            esc[j-2]->posy = i;
            esc[j-2]->vivo = true;
            esc[j-2]->vidas = 2;
        }
        
    }
    
}

void detectarColision(struct Jugador *ju, struct Enemigos e){
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 11; i++)
        {
            if (i==0) {//sustituir igualdades por funciones que comprueben rango
                if ((e.pulpos[j].posy == ju->posy) && (e.pulpos[j].posx == ju->posy) && (e.pulpos[j].vivo)) {
                    ju->vivo = false;
                }
            }
            else if (1<=i<3) {//sustituir igualdades por funciones que comprueben rango
                if ((e.cangrejos[j].posy == ju->posy) && (e.cangrejos[j].posx == ju->posy) && (e.cangrejos[j].vivo)) {
                    ju->vivo = false;
                }
            }
            else
            {//sustituir igualdades por funciones que comprueben rango
                if ((e.calamares[j].posy == ju->posy) && (e.calamares[j].posx == ju->posy) && (e.calamares[j].vivo)) {
                    ju->vivo = false;
                }
            }
        }
    }
}

void meDispararon(struct Jugador *j, struct Misil *m){
    
}