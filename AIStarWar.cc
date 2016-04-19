
#include "Player.hh"
#include <stack>
#include <vector>
using namespace std;


/**
 * Write the name of your player and save this file
 * as AI<name>.cc
 */
#define PLAYER_NAME DarthEspelta





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


    /**
     * Play method.
     *
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */
    virtual void play () {
        //Cambiar number_window_columns() por universe
        //%numer_universe_columns() eliminado
        bool hihaalgo = false;
        //cerr << "asd" << endl;
        Pos error = {-1,-1};
        for (Starship_Id sid = begin(me()); sid != end(me()); ++sid) {
        //cerr << "??" << endl;
          Starship s = starship(sid);
          if (s.alive) { // if the starship is alive and
            Pos p = s.pos;
            Pos aux = p + DEFAULT;
            /*while (cell(aux).type == EMPTY and within_universe(aux)) {
                aux += aux;
            }*/
            if (within_window(p - DEFAULT,round()) and cell(p - DEFAULT).type == MISSILE) {
                if (within_window(p + UP,round() + 1) and cell(p + UP).type == EMPTY) move(sid,UP);
                if (within_window(p + DOWN,round() + 1) and cell(p + DOWN).type == EMPTY) move(sid,DOWN);
                if (within_window(p + FAST_UP,round() + 1) and cell(p + FAST_UP).type == EMPTY) move(sid,FAST_UP);
                if (within_window(p + FAST_DOWN,round() + 1) and cell(p + FAST_UP).type == EMPTY) move(sid,FAST_DOWN);
            }
            if (within_window(p + SLOW_DOWN - DEFAULT,round() + 1) and cell(p + SLOW_DOWN - DEFAULT).type == MISSILE) {
                if(within_window(p + DEFAULT,round() + 1))
                move(sid,DEFAULT);
            }
            if ((cell(p + DEFAULT).type == STARSHIP or cell(aux).type == ASTEROID) and s.nb_miss > 0) shoot(sid);
            if ((cell(p + FAST)).type == STARSHIP or cell(p + FAST).type == ASTEROID and s.nb_miss > 0) shoot(sid);
            if (s.nb_miss == 0) {
            Pos ir = go_coin(p,MISSILE_BONUS,hihaalgo);
            //cerr << "Voy a " << ir << " estoy en" << p << endl;
            if (ir == error) move(s.sid,FAST);
            else move(s.sid,ir-p);
          }
          else {
                Pos ir = go_coin(p,POINT_BONUS,hihaalgo);
                //cerr << "Voy a " << ir << " estoy en " << p << endl;
                if (ir == error) move(s.sid,FAST);
                else move(s.sid,ir-p);

            }
        }
}
}


    Pos go_coin(Pos estoy,CType c,bool& he_trobat_algo) { //bfs
          vector<vector<bool>>v(number_rows(),vector<bool>(number_universe_columns(),false));
          vector< vector<Pos> >anterior (number_rows(), vector<Pos>(number_universe_columns(),-1));
          queue<Pos> q;
          stack<Pos> p;
          q.push(estoy);
          v[first(estoy)][second(estoy)%number_window_columns()] = true;
          bool he_trobat_coin = false;
          Pos coin;
          coin = {-1,-1};
          Pos a_moverme;
          while (not q.empty() and not he_trobat_coin) {
              Pos actual = q.front(); q.pop();
              int i = first(actual);
              int j = second(actual);
              //UP
              if (within_window(actual + UP, round() + 1)) {
                  if (not he_trobat_coin) {
                      if (not v[i - 1][(j + 1)%number_window_columns()]) {
                      Pos parriba = actual + UP;
                      if (cell(parriba - DEFAULT).type != MISSILE and cell(parriba - DEFAULT - DEFAULT).type != MISSILE and cell(parriba).type != ASTEROID and cell(parriba).type != MISSILE and cell(parriba).type != STARSHIP) {
                          if (within_window(actual + SLOW_UP,round() + 1) and cell({i -1,j}).type != ASTEROID and within_window(actual + DEFAULT,round() + 1) and cell({i,j + 1}).type != ASTEROID) {
                          //cerr << "VoyAEncolar" << endl;
                          Pos arriba = actual + UP;
                          //cerr << "Encolo A" << arriba << endl;
                          q.push(arriba);
                          // << "Encolas: " << first(actual) << " " << second(actual) - 1 << endl;
                          v[i - 1][(j + 1)%number_window_columns()] = true;
                          anterior[i - 1][(j + 1)%number_window_columns()] = actual;
                              if (cell(actual + UP).type == c) {
                                  //cerr << "Encuentro moneda? U" << endl;
                                  // << "He encontrado la bola, left" << endl;
                                  he_trobat_coin = true;
                                  he_trobat_algo = true;
                                  coin = actual + UP;
                                 }
                             }
                        }
                      }
                  }

              }
              //SLOOWN
              //cerr << "D:" << endl;
              if (within_window(actual + SLOW_DOWN, round()+1)) {
                  //cerr << "?" << endl;
                  if (not he_trobat_coin) {
                      //cerr << "entra moneda" << endl;
                      if(not v[i + 1][j%number_window_columns()]) {
                          //cerr << "peta visitados" << endl;
                          Pos pabajol = actual + SLOW_DOWN;
                          if ((cell(pabajol - DEFAULT).type != MISSILE) and cell(pabajol - DEFAULT - DEFAULT).type != MISSILE and cell(actual + SLOW_DOWN).type != ASTEROID and cell(actual + SLOW_DOWN).type != MISSILE and cell(actual + SLOW_DOWN).type != STARSHIP) {
                          Pos abajo_lento = actual + SLOW_DOWN;
                          //cerr << "Encolo SD" << abajo_lento << endl;
                          q.push(abajo_lento);
                          ////cerr << "Encolas: " << first(actual) << " " << second(actual) - 1 << endl;
                           v[i + 1][j%number_window_columns()] = true;
                          anterior[i + 1][j%number_window_columns()] = actual;
                              if (cell(actual + SLOW_DOWN).type == c) {
                                  //cerr << "Encuentro moneda? SD" << endl;
                                  //cerr << "He encontrado la bola, left" << endl;
                                  he_trobat_coin = true;
                                  he_trobat_algo = true;
                                  coin = actual + SLOW_DOWN;
                                }
                            }
                          }
                        }
                      }
              //SLOW
              if (within_window(actual + SLOW, round()+1) and not he_trobat_coin and not v[i][(j)%number_window_columns()]) {
                  Pos pabajo = actual + SLOW;
                  if (cell(pabajo- DEFAULT).type != MISSILE and cell(pabajo - DEFAULT - DEFAULT).type != MISSILE and cell(actual + SLOW).type != ASTEROID and cell(actual + SLOW).type != MISSILE and cell(actual + SLOW).type != STARSHIP) {
                  if (within_window(actual + SLOW_DOWN,round() + 1) and cell({i + 1,j}).type != ASTEROID and within_window(actual + DEFAULT,round() + 1) and cell({i,j + 1}).type != ASTEROID) {
                   Pos lento = actual + SLOW;
                   //cerr << "Encolo S" << lento << endl;
                   q.push(lento);
                  ////cerr << "Encolas: " << first(actual) << " " << second(actual) - 1 << endl;
                  v[i][(j)%number_window_columns()] = true;
                  anterior[i][(j)%number_window_columns()] = actual;
                  if (cell(actual + SLOW).type == c) {
                      //cerr << "Encuentro moneda? S" << endl;
                      ////cerr << "He encontrado la bola, left" << endl;
                      he_trobat_coin = true;
                      he_trobat_algo = true;
                      coin = actual + SLOW;
                    }
                  }
                  }
              }
              //SLOW_UP
              if (within_window(actual + SLOW_UP, round()+1) and not he_trobat_coin and not v[i - 1][j%number_window_columns()]) {
                  Pos pabajou = actual + SLOW_UP;
                  if (cell(pabajou - DEFAULT).type != MISSILE and cell(pabajou - DEFAULT - DEFAULT).type != MISSILE and cell(actual + SLOW_UP).type != ASTEROID and cell(actual + SLOW_UP).type != MISSILE and cell(actual + SLOW_UP).type != STARSHIP) {
                  Pos lento_arriba = actual + SLOW_UP;
                  //cerr << "Encolo SU" << lento_arriba << endl;
                  q.push(lento_arriba);
                  ////cerr << "Encolas: " << first(actual) << " " << second(actual) - 1 << endl;
                   v[i - 1][j%number_window_columns()] = true;
                  anterior[i - 1][j%number_window_columns()] = actual;
                  if (cell(actual + SLOW_UP).type == c) {
                      //cerr << "Encuentro moneda? SU" << endl;
                      ////cerr << "He encontrado la bola, left" << endl;
                      he_trobat_coin = true;
                      he_trobat_algo = true;
                      coin = actual + SLOW_UP;
                        }
                  }
              }

                  //FAST_UP
              if (within_window(actual + FAST_UP, round()+1) and not he_trobat_coin and not v[i - 1][(j + 2)%number_window_columns()]) {
                  Pos rapidou = actual + FAST_UP;
                  if (cell(rapidou - DEFAULT).type != MISSILE and cell(rapidou - DEFAULT - DEFAULT).type != MISSILE and cell(actual + FAST_UP).type != ASTEROID and cell(actual + FAST_UP).type != MISSILE and cell(actual + FAST_UP).type != STARSHIP) {
                  if (within_window(actual + DEFAULT,round() + 1) and cell({i,j + 1}).type != ASTEROID and within_window(actual + UP,round() + 1) and cell({i - 1,j + 1}).type != ASTEROID and within_window(actual + SLOW,round() + 1) and cell({i - 1,j}).type != ASTEROID and within_window(actual + FAST,round() + 1) and cell({i,j + 2}).type != ASTEROID) {
                  Pos rapido_arriba = actual + FAST_UP;
                  //cerr << "EncoloFU " << rapido_arriba << endl;
                  q.push(rapido_arriba);
                  ////cerr << "Encolas: " << first(actual) << " " << second(actual) - 1 << endl;
                   v[i - 1][(j + 2)%number_window_columns()] = true;
                  anterior[i - 1][(j+2)%number_window_columns()] = actual;
                  if (cell(actual + FAST_UP).type == c) {
                      //cerr << "Encuentro moneda? FU" << endl;
                      ////cerr << "He encontrado la bola, left" << endl;
                      he_trobat_coin = true;
                      he_trobat_algo = true;
                      coin = actual + FAST_UP;
                        }
                  }
                  }
              }
                      //FAST
              if (within_window(actual + FAST, round()+1) and not he_trobat_coin and not v[i][(j + 2)%number_window_columns()]) {
                  Pos rapido = actual + FAST;
                  if (cell(rapido - DEFAULT).type != MISSILE and cell(rapido - DEFAULT - DEFAULT).type != MISSILE and cell(actual + FAST).type != ASTEROID and cell(actual + FAST).type != MISSILE and cell(actual + FAST).type != STARSHIP) {
                  Pos rapido = actual + FAST;
                  //cerr << "Encolo F" << rapido << endl;
                  q.push(rapido);
                  ////cerr << "Encolas: " << first(actual) << " " << second(actual) - 1 << endl;
                  v[i][(j + 2)%number_window_columns()] = true;
                  anterior[i][(j + 2)%number_window_columns()] = actual;
                  if (cell(actual + FAST).type == c) {
                      //cerr << "Encuentro moneda? F" << endl;
                      ////cerr << "He encontrado la bola, left" << endl;
                      he_trobat_coin = true;
                      he_trobat_algo = true;
                      coin = actual + FAST;
                        }
                  }
              }
                          //FAST_DOWN
              if (within_window(actual + FAST_DOWN, round()+1) and not he_trobat_coin and not v[i + 1][(j + 2)%number_window_columns()]) {
                  Pos rapidoa = actual + FAST_DOWN;
                  if (cell(rapidoa - DEFAULT).type != MISSILE and cell(rapidoa - DEFAULT - DEFAULT).type != MISSILE and cell(actual + FAST_DOWN).type != ASTEROID and cell(actual + FAST_DOWN).type != MISSILE and cell(actual + FAST_DOWN).type != STARSHIP) {
                  if (within_window(actual + DEFAULT,round() + 1) and cell({i,j + 1}).type != ASTEROID and within_window(actual + DOWN,round() + 1) and cell({i + 1,j + 1}).type != ASTEROID and within_window(actual + DOWN,round() + 1) and cell({i + 1,j}).type != ASTEROID and within_window(actual + FAST,round() + 1) and cell({i,j + 2}).type != ASTEROID) {
                  Pos rapido_abajo = actual + FAST_DOWN;
                  //cerr << "EncoloFD " << rapido_abajo << endl;
                   q.push(rapido_abajo);
                  ////cerr << "Encolas: " << first(actual) << " " << second(actual) - 1 << endl;
                  v[i + 1][(j + 2)%number_window_columns()] = true;
                  anterior[i + 1][(j + 2)%number_window_columns()] = actual;
                  if (cell(actual + FAST_DOWN).type == c) {
                      //cerr << "Encuentro moneda? FD" << endl;
                      ////cerr << "He encontrado la bola, left" << endl;
                      he_trobat_coin = true;
                      he_trobat_algo = true;
                      coin = actual + FAST_DOWN;
                        }
                  }
                  }
              }
          }
              //cerr << he_trobat_coin << endl;

                          if (he_trobat_coin) {
                              he_trobat_algo = true;
                              //cerr << "entro aqui?" << endl;
                              p.push(coin);
                              a_moverme = anterior[first(coin)][(second(coin)%number_window_columns())];
                              while (a_moverme != estoy) {
                                  p.push(a_moverme);
                                  //cerr << "Miro anterior: " << anterior[first(a_moverme)][second(a_moverme)%number_universe_columns()] << endl;
                                  a_moverme = anterior[first(a_moverme)][second(a_moverme)%number_window_columns()];
                            }
                              return p.top();
                          }
                      else {
                          //cerr << "entro aqui" << endl;
                          return {-1,-1};
                      }
        }
    };



/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
