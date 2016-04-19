

#include "Player.hh"
#include <vector>
#include <queue>
#include <cmath>
#include <stack>


using namespace std;


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Vegettalx777





struct PLAYER_NAME : public Player {


    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
        return new PLAYER_NAME;
    }


    /**
     * Attributes for your player can be defined here.
     */
    Dir dir;
    /**
     * Play method.
     *
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */
    virtual void play () {
        Pos inicio = goku(me()).pos;
        if (goku(me()).type == With_Ball or goku(me()).type == On_Kinton_With_Ball) {
            int d1,d2;
            Pos kinton = go_kinton(inicio,d1);
            Pos mover = go_capsula(inicio,d2);
            if (d1 < d2) dir = a_mover(kinton,inicio);
            move(dir);
            dir = a_mover(mover,inicio);
            move(dir);
        }
        else if (goku(me()).type != With_Ball) {
            if (goku(me()).strength < calcula_min_strength()) {
                        int d1,d2;
                        Pos kinton = go_kinton(inicio,d1);
                        Pos mongeta = go_mongeta(inicio,d2);
                        if (d1 < d2) dir = a_mover(kinton,inicio);
                        move(dir);
                        dir = a_mover(mongeta,inicio);
                        move(dir);
            }
            int d1,d2;
            Pos kinton = go_kinton(inicio,d1);
            Pos bola = go_bola(inicio,d2);
            if (d1 < d2) dir = a_mover(kinton,inicio);
            move(dir);
            dir = a_mover(bola,inicio);
            move(dir);
        }
        else {
            int d1,d2;
            Pos kinton = go_kinton(inicio,d1);
            Pos mongeta = go_mongeta(inicio,d2);
            if (d1 < d2) dir = a_mover(kinton,inicio);
            move(dir);
            dir = a_mover(mongeta,inicio);
            move(dir);
        }
    }

       Dir a_mover(Pos p, Pos inicio) {
           if (p.i == inicio.i + 1) return Bottom;
           if (p.i == inicio.i - 1) return Top;
           if (p.j == inicio.j + 1) return Right;
           if (p.j == inicio.j - 1) return Left;
           return None;
       }



      int calcula_min_strength() {
        int min1;
        if (goku(0).strength< goku(1).strength) {
            min1 = goku(0).strength;
        }
        else min1 = goku(1).strength;
        if (goku(2).strength < min1) return goku(2).strength;
        return min1;
      }

      Pos go_bola(Pos estoy,int& db) { //bfs
        vector< vector<int> >distancias (rows(), vector<int>(cols(),-1));
        vector< vector<Pos> >anterior (rows(), vector<Pos>(cols()));
        queue<Pos> q;
        stack<Pos> p;
        q.push(estoy);
        distancias[estoy.i][estoy.j] = 0;
        bool he_trobat_bola = false;
        Pos bola;
        bola.i = -1;
        bola.j = -1;
        Pos a_moverme;
        while (not q.empty() and not he_trobat_bola) {
            Pos actual = q.front(); q.pop();
            if (not he_trobat_bola and distancias[actual.i][actual.j - 1] == -1 and cell(actual.i,actual.j - 1).type != Rock) {
                q.push({actual.i,actual.j - 1});
                //cerr << "Encolas: " << actual.i << " " << actual.j - 1 << endl;
                distancias[actual.i][actual.j - 1] = 1 + distancias[actual.i][actual.j];
                anterior[actual.i][actual.j - 1] = actual;
                if (cell(actual.i,actual.j - 1).type == Ball) {
                    cerr << "He encontrado la bola, left" << endl;
                    he_trobat_bola = true;
                    bola.i = actual.i;
                    bola.j = actual.j - 1;
                    db = distancias[actual.i][actual.j - 1];
                }
            }
            if (not he_trobat_bola and distancias[actual.i][actual.j + 1] == -1 and cell(actual.i,actual.j + 1).type != Rock) {
                q.push({actual.i,actual.j + 1});
                //cerr << "Encolas: " << actual.i << " " << actual.j + 1 << endl;
                 distancias[actual.i][actual.j + 1] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i][actual.j + 1] = actual;
                 if (cell(actual.i,actual.j + 1).type == Ball) {
                     cerr << "He encontrado la bola,right" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i;
                     bola.j = actual.j + 1;
                     db = distancias[actual.i][actual.j + 1];
                 }
                }
            if (not he_trobat_bola and distancias[actual.i - 1][actual.j] == -1 and cell(actual.i - 1,actual.j).type != Rock) {
                q.push({actual.i - 1,actual.j});
                //cerr << "Encolas: " << actual.i - 1 << " " << actual.j << endl;
                 distancias[actual.i - 1][actual.j] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i - 1][actual.j] = actual;
                 if (cell(actual.i - 1,actual.j).type == Ball) {
                     cerr << "He encontrado la bola,top" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i - 1;
                     bola.j = actual.j;
                     db = distancias[actual.i - 1][actual.j];
                 }
                }
            if (not he_trobat_bola and distancias[actual.i + 1][actual.j] == -1  and cell(actual.i + 1,actual.j).type != Rock) {
                q.push({actual.i + 1,actual.j});
                //cerr << "Encolas: " << actual.i + 1 << " " << actual.j << endl;
                 distancias[actual.i + 1][actual.j] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i + 1][actual.j] = actual;
                 if (cell(actual.i + 1,actual.j).type == Ball) {
                     cerr << "He encontrado la bola,bot" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i + 1;
                     bola.j = actual.j;
                     db = distancias[actual.i + 1][actual.j];
                    }
                }
            }
            cerr << "bola vale: " << bola.i << " " << bola.j << endl;
            if (he_trobat_bola) {
                p.push(bola);
                a_moverme = anterior[bola.i][bola.j];
                /*cerr << "bola vale: " << bola.i << " " << bola.j << endl;
                cerr << "a_moverme vale: " << a_moverme.i << " " << a_moverme.j << endl;*/
                while (a_moverme != estoy) {
                   cerr << "Estoy vale esto: " << estoy.i << " " << estoy.j << endl;
                    cerr << "Vas a mirar la posición: " << a_moverme.i << " " << a_moverme.j << endl;
                    p.push(a_moverme);
                    a_moverme = anterior[a_moverme.i][a_moverme.j];
              }

            }
            cerr << "MI POSICION: i = " << goku(me()).pos.i << " j= " << goku(me()).pos.j << endl;
            /*while (not p.empty()) {
                cerr << "Quito el" << p.top().i << " " << p.top().j << endl;
                p.pop();
            }*/
            //cerr << "ME MOVERE A: i= " << p.top().i << " j= " << p.top().j << endl;
                    if (he_trobat_bola) return p.top();
                    Pos error;
                    error.i = -1;
                    error.j = -1;
                    return error;

      }

      Pos go_capsula(Pos estoy,int& d) { //bfs
        vector< vector<int> >distancias (rows(), vector<int>(cols(),-1));
        vector< vector<Pos> >anterior (rows(), vector<Pos>(cols()));
        queue<Pos> q;
        stack<Pos> p;
        q.push(estoy);
        distancias[estoy.i][estoy.j] = 0;
        bool he_trobat_bola = false;
        Pos bola;
        bola.i = -1;
        bola.j = -1;
        Pos a_moverme;
        while (not q.empty() and not he_trobat_bola) {
            Pos actual = q.front(); q.pop();
            if (not he_trobat_bola and distancias[actual.i][actual.j - 1] == -1 and cell(actual.i,actual.j - 1).type != Rock) {
                q.push({actual.i,actual.j - 1});
                //cerr << "Encolas: " << actual.i << " " << actual.j - 1 << endl;
                distancias[actual.i][actual.j - 1] = 1 + distancias[actual.i][actual.j];
                anterior[actual.i][actual.j - 1] = actual;
                if (cell(actual.i,actual.j - 1).type == Capsule) {
                    cerr << "He encontrado la bola, left" << endl;
                    he_trobat_bola = true;
                    bola.i = actual.i;
                    bola.j = actual.j - 1;
                    d = distancias[actual.i][actual.j - 1];
                }
            }
            if (not he_trobat_bola and distancias[actual.i][actual.j + 1] == -1 and cell(actual.i,actual.j + 1).type != Rock) {
                q.push({actual.i,actual.j + 1});
                //cerr << "Encolas: " << actual.i << " " << actual.j + 1 << endl;
                 distancias[actual.i][actual.j + 1] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i][actual.j + 1] = actual;
                 if (cell(actual.i,actual.j + 1).type == Capsule) {
                     cerr << "He encontrado la bola,right" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i;
                     bola.j = actual.j + 1;
                      d = distancias[actual.i][actual.j + 1];
                 }
                }
            if (not he_trobat_bola and distancias[actual.i - 1][actual.j] == -1 and cell(actual.i - 1,actual.j).type != Rock) {
                q.push({actual.i - 1,actual.j});
                //cerr << "Encolas: " << actual.i - 1 << " " << actual.j << endl;
                 distancias[actual.i - 1][actual.j] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i - 1][actual.j] = actual;
                 if (cell(actual.i - 1,actual.j).type == Capsule) {
                     cerr << "He encontrado la bola,top" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i - 1;
                     bola.j = actual.j;
                     d = distancias[actual.i - 1][actual.j];
                 }
                }
            if (not he_trobat_bola and distancias[actual.i + 1][actual.j] == -1  and cell(actual.i + 1,actual.j).type != Rock) {
                q.push({actual.i + 1,actual.j});
                //cerr << "Encolas: " << actual.i + 1 << " " << actual.j << endl;
                 distancias[actual.i + 1][actual.j] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i + 1][actual.j] = actual;
                 if (cell(actual.i + 1,actual.j).type == Capsule) {
                     cerr << "He encontrado la bola,bot" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i + 1;
                     bola.j = actual.j;
                      d = distancias[actual.i + 1][actual.j];
                    }
                }
            }
            cerr << "bola vale: " << bola.i << " " << bola.j << endl;
            if (he_trobat_bola) {
                p.push(bola);
                a_moverme = anterior[bola.i][bola.j];
                /*cerr << "bola vale: " << bola.i << " " << bola.j << endl;
                cerr << "a_moverme vale: " << a_moverme.i << " " << a_moverme.j << endl;*/
                while (a_moverme != estoy) {
                   cerr << "Estoy vale esto: " << estoy.i << " " << estoy.j << endl;
                    cerr << "Vas a mirar la posición: " << a_moverme.i << " " << a_moverme.j << endl;
                    p.push(a_moverme);
                    a_moverme = anterior[a_moverme.i][a_moverme.j];
              }

            }
            cerr << "MI POSICION: i = " << goku(me()).pos.i << " j= " << goku(me()).pos.j << endl;
            /*while (not p.empty()) {
                cerr << "Quito el" << p.top().i << " " << p.top().j << endl;
                p.pop();
            }*/
            cerr << "ME MOVERE A: i= " << p.top().i << " j= " << p.top().j << endl;
            if (he_trobat_bola) return p.top();
            Pos error;
            error.i = -1;
            error.j = -1;
            return error;

      }


      Pos go_kinton(Pos estoy,int& d) { //bfs
        vector< vector<int> >distancias (rows(), vector<int>(cols(),-1));
        vector< vector<Pos> >anterior (rows(), vector<Pos>(cols()));
        queue<Pos> q;
        stack<Pos> p;
        q.push(estoy);
        distancias[estoy.i][estoy.j] = 0;
        bool he_trobat_bola = false;
        Pos bola;
        bola.i = -1;
        bola.j = -1;
        Pos a_moverme;
        while (not q.empty() and not he_trobat_bola) {
            Pos actual = q.front(); q.pop();
            if (not he_trobat_bola and distancias[actual.i][actual.j - 1] == -1 and cell(actual.i,actual.j - 1).type != Rock) {
                q.push({actual.i,actual.j - 1});
                //cerr << "Encolas: " << actual.i << " " << actual.j - 1 << endl;
                distancias[actual.i][actual.j - 1] = 1 + distancias[actual.i][actual.j];
                anterior[actual.i][actual.j - 1] = actual;
                if (cell(actual.i,actual.j - 1).type == Kinton) {
                    cerr << "He encontrado la bola, left" << endl;
                    he_trobat_bola = true;
                    bola.i = actual.i;
                    bola.j = actual.j - 1;
                     d = distancias[actual.i][actual.j - 1];
                }
            }
            if (not he_trobat_bola and distancias[actual.i][actual.j + 1] == -1 and cell(actual.i,actual.j + 1).type != Rock) {
                q.push({actual.i,actual.j + 1});
                //cerr << "Encolas: " << actual.i << " " << actual.j + 1 << endl;
                 distancias[actual.i][actual.j + 1] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i][actual.j + 1] = actual;
                 if (cell(actual.i,actual.j + 1).type == Kinton) {
                     cerr << "He encontrado la bola,right" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i;
                     bola.j = actual.j + 1;
                      d = distancias[actual.i][actual.j + 1];
                 }
                }
            if (not he_trobat_bola and distancias[actual.i - 1][actual.j] == -1 and cell(actual.i - 1,actual.j).type != Rock) {
                q.push({actual.i - 1,actual.j});
                //cerr << "Encolas: " << actual.i - 1 << " " << actual.j << endl;
                 distancias[actual.i - 1][actual.j] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i - 1][actual.j] = actual;
                 if (cell(actual.i - 1,actual.j).type == Kinton) {
                     cerr << "He encontrado la bola,top" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i - 1;
                     bola.j = actual.j;
                      d = distancias[actual.i - 1][actual.j];
                 }
                }
            if (not he_trobat_bola and distancias[actual.i + 1][actual.j] == -1  and cell(actual.i + 1,actual.j).type != Rock) {
                q.push({actual.i + 1,actual.j});
                //cerr << "Encolas: " << actual.i + 1 << " " << actual.j << endl;
                 distancias[actual.i + 1][actual.j] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i + 1][actual.j] = actual;
                 if (cell(actual.i + 1,actual.j).type == Kinton) {
                     cerr << "He encontrado la bola,bot" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i + 1;
                     bola.j = actual.j;
                      d = distancias[actual.i + 1][actual.j];
                    }
                }
            }
            cerr << "bola vale: " << bola.i << " " << bola.j << endl;
            if (he_trobat_bola) {
                p.push(bola);
                a_moverme = anterior[bola.i][bola.j];
                /*cerr << "bola vale: " << bola.i << " " << bola.j << endl;
                cerr << "a_moverme vale: " << a_moverme.i << " " << a_moverme.j << endl;*/
                while (a_moverme != estoy) {
                   cerr << "Estoy vale esto: " << estoy.i << " " << estoy.j << endl;
                    cerr << "Vas a mirar la posición: " << a_moverme.i << " " << a_moverme.j << endl;
                    p.push(a_moverme);
                    a_moverme = anterior[a_moverme.i][a_moverme.j];
              }

            }
            cerr << "MI POSICION: i = " << goku(me()).pos.i << " j= " << goku(me()).pos.j << endl;
            /*while (not p.empty()) {
                cerr << "Quito el" << p.top().i << " " << p.top().j << endl;
                p.pop();
            }*/
            cerr << "ME MOVERE A: i= " << p.top().i << " j= " << p.top().j << endl;
            if (he_trobat_bola) return p.top();
            Pos error;
            error.i = -1;
            error.j = -1;
            return error;

      }

      Pos go_mongeta(Pos estoy,int& d) { //bfs
        vector< vector<int> >distancias (rows(), vector<int>(cols(),-1));
        vector< vector<Pos> >anterior (rows(), vector<Pos>(cols()));
        queue<Pos> q;
        stack<Pos> p;
        q.push(estoy);
        distancias[estoy.i][estoy.j] = 0;
        bool he_trobat_bola = false;
        Pos bola;
        bola.i = -1;
        bola.j = -1;
        Pos a_moverme;
        while (not q.empty() and not he_trobat_bola) {
            Pos actual = q.front(); q.pop();
            if (not he_trobat_bola and distancias[actual.i][actual.j - 1] == -1 and cell(actual.i,actual.j - 1).type != Rock) {
                q.push({actual.i,actual.j - 1});
                //cerr << "Encolas: " << actual.i << " " << actual.j - 1 << endl;
                distancias[actual.i][actual.j - 1] = 1 + distancias[actual.i][actual.j];
                anterior[actual.i][actual.j - 1] = actual;
                if (cell(actual.i,actual.j - 1).type == Bean) {
                    cerr << "He encontrado la bola, left" << endl;
                    he_trobat_bola = true;
                    bola.i = actual.i;
                    bola.j = actual.j - 1;
                    d = distancias[actual.i][actual.j - 1];
                }
            }
            if (not he_trobat_bola and distancias[actual.i][actual.j + 1] == -1 and cell(actual.i,actual.j + 1).type != Rock) {
                q.push({actual.i,actual.j + 1});
                //cerr << "Encolas: " << actual.i << " " << actual.j + 1 << endl;
                 distancias[actual.i][actual.j + 1] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i][actual.j + 1] = actual;
                 if (cell(actual.i,actual.j + 1).type == Bean) {
                     cerr << "He encontrado la bola,right" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i;
                     bola.j = actual.j + 1;
                     d = distancias[actual.i][actual.j + 1];
                 }
                }
            if (not he_trobat_bola and distancias[actual.i - 1][actual.j] == -1 and cell(actual.i - 1,actual.j).type != Rock) {
                q.push({actual.i - 1,actual.j});
                //cerr << "Encolas: " << actual.i - 1 << " " << actual.j << endl;
                 distancias[actual.i - 1][actual.j] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i - 1][actual.j] = actual;
                 if (cell(actual.i - 1,actual.j).type == Bean) {
                     cerr << "He encontrado la bola,top" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i - 1;
                     bola.j = actual.j;
                     d = distancias[actual.i - 1][actual.j];
                 }
                }
            if (not he_trobat_bola and distancias[actual.i + 1][actual.j] == -1  and cell(actual.i + 1,actual.j).type != Rock) {
                q.push({actual.i + 1,actual.j});
                //cerr << "Encolas: " << actual.i + 1 << " " << actual.j << endl;
                 distancias[actual.i + 1][actual.j] = 1 + distancias[actual.i][actual.j];
                 anterior[actual.i + 1][actual.j] = actual;
                 if (cell(actual.i + 1,actual.j).type == Bean) {
                     cerr << "He encontrado la bola,bot" << endl;
                     he_trobat_bola = true;
                     bola.i = actual.i + 1;
                     bola.j = actual.j;
                     d = distancias[actual.i + 1][actual.j];
                    }
                }
            }
            cerr << "bola vale: " << bola.i << " " << bola.j << endl;
            if (he_trobat_bola) {
                p.push(bola);
                a_moverme = anterior[bola.i][bola.j];
                /*cerr << "bola vale: " << bola.i << " " << bola.j << endl;
                cerr << "a_moverme vale: " << a_moverme.i << " " << a_moverme.j << endl;*/
                while (a_moverme != estoy) {
                   cerr << "Estoy vale esto: " << estoy.i << " " << estoy.j << endl;
                    cerr << "Vas a mirar la posición: " << a_moverme.i << " " << a_moverme.j << endl;
                    p.push(a_moverme);
                    a_moverme = anterior[a_moverme.i][a_moverme.j];
              }

            }
            cerr << "MI POSICION: i = " << goku(me()).pos.i << " j= " << goku(me()).pos.j << endl;
            /*while (not p.empty()) {
                cerr << "Quito el" << p.top().i << " " << p.top().j << endl;
                p.pop();
            }*/
            cerr << "ME MOVERE A: i= " << p.top().i << " j= " << p.top().j << endl;
            if (he_trobat_bola) return p.top();
            Pos error;
            error.i = -1;
            error.j = -1;
            return error;

      }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

