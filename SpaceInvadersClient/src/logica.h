#include <stdbool.h>
//Estructuras
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
    int enemigosRestantes;
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
struct EscudoSeccion
{
    int posx;
    int posy;
    int vidas;
    bool vivo;
};
struct Escudo
{
    struct EscudoSeccion SuperiorIzq;
    struct EscudoSeccion SuperiorDer;
    struct EscudoSeccion InferiorIzq;
    struct EscudoSeccion InferiorDer;
};

//Funciones
void inicializar(struct Jugador *ju, struct Enemigos *e, struct Balas *b, struct Escudo *esc[], int filas, int columnas);//posiciones iniciales
void reiniciarEnemigos(struct Enemigos *e); //posicion inicial enemigos
void colocarEscudos(struct Escudo *esc[]); //posicion inicial bunkers
void colocarSeccionesEscudo(int posX , struct Escudo *esc); //posicion secciones bunkers
void detectarColision(struct Jugador *ju, struct Enemigos e, int *isdead); //detecta si esta en un rango de colision
void meDispararon(struct Jugador *ju, struct Misil *m, int *isdead); //detecta si el jugador fue impactado po una bala enemiga
void leDispare(struct Enemigos *e, struct Balas *b); //detecta si un enemigo fue impactado por una bala aleada
void debilitarEscudo(struct Escudo *esc[], struct Misil *m); //detecta si un escudo fue impactado por una bala enemiga
void debilitarSeccionEscudo(struct Escudo *esc, struct Misil *m);//detecta si una seccion de un escudo fue impactado por una bala enemiga
void ejecutarAccion(int accion, struct Jugador *ju, struct Balas *b);//recibe un parametro que define una accion que modifica al jugador
