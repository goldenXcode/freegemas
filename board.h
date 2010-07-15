#ifndef _BOARD_H_
#define _BOARD_H_

#include <Gosu/Gosu.hpp>

#include <boost/foreach.hpp>

#include <algorithm>
#include <vector>
#include <tr1/array>
using namespace std;

#include "log.h"

enum tSquare { sqEmpty, sqWhite, sqRed, sqPurple, sqOrange, sqGreen, sqYellow, sqBlue };

/**
 * @class Casilla
 *
 * @brief Representa una casilla del board.
 *
 * Además de la gema, tiene atributos para la gestión de las animaciones 
 * cuando desaparecen otras gemas.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


struct Square{
    /// Tipo de gema que contiene la casilla.
    tSquare tipo;

    Square(const tSquare & t = sqEmpty) : origY(0), destY(0), mustFall(false){
	tipo = t;
    }

    bool operator==(const Square & C){
	return C.tipo == tipo;
    }

    bool operator==(const tSquare & t){
	return tipo == t;
    }

    operator tSquare(){ return tipo; }

    /// Posición inicial vertical de la casilla - Se usa para hacer las animaciones
    int origY;

    /** Desplazamiento vertical. 

	Cuando se ha hecho un grupo de figuras, y éstas desaparecen,
	las que están encima deben caer. Este atributo cuenta el
	número de casillas que debe caer hacia abajo.
    */

    int destY; 
    
    /// Indica si debe o no caer
    bool mustFall; 
};

/**
 * @class Punto cartesiano con coordenadas x e y
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


struct coord{
    int x, y;
    coord(int x = 0, int y = 0) : x(x), y(y) { }

    bool operator ==(const coord & c){
	return (c.x == x && 
		c.y == y);
    }

    friend ostream& operator << (ostream& out, coord & C){
	out << "(" << C.x << "," << C.y << ")";

	return out;
    }
};

class Match : public vector<coord>{
public:
    coord midSquare() const{
	return at(size() / 2);
    }

    bool matched(coord c) {
	return (std::find(begin(), end(), c) != end());
    }

    friend ostream& operator << (ostream& out, Match & M){
	out << "Match (" << M.size() << "): ";
	for (size_t i = 0; i < M.size(); ++i)
	{
	    out << M[i] << ", ";
	}
	
	return out;
    }
};

class MultipleMatch : public vector<Match>{
public:
    bool matched(coord C){
	vector<Match>::iterator it;
	for(it = begin(); it != end(); ++it){
	    if(it -> matched(C))
	       return true;
	}
	return false;
    }
    
};

/**
 * @class Board
 *
 * @brief Representa un board de juego en un momento dado.
 *
 * Contiene una matriz de 8x8 con el contenido de las casillas
 * además de algoritmos que permiten hacer comprobaciones sobre el board.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Board{
public:
    Board();

    ~Board();

    /// Swaps squares x1,y1 and x2,y2
    void swap(int x1, int y1, int x2, int y2);

    /// Empties square (x,y)
    void del(int x, int y);
    
    /// Generates a random board.
    void generate();

    /// Calculates squares' positions after deleting the matching gems.
    void calcFallMovements();

    /// Applies calculated positions on previous method
    void applyFall();

    /// Fills board's gaps with newly generated gems
    void fillSpaces();

    /// Checks if there are matching horizontal and/or vertical groups
    MultipleMatch check();

    /// Checks if current board has any possible valid movement
    vector<coord> solutions();

    /// Resets squares' animations
    void endAnimations();

    tr1::array< tr1::array<Square, 8>, 8> squares;
    friend ostream& operator <<(ostream& out, Board & B);
};
#endif /* _BOARD_H_ */
