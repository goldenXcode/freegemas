#include "board.h"


#include <ctime>
#include <iostream>
#include <boost/format.hpp>
using boost::format;

Board::Board(){
    lDEBUG << Log::CON("Board");
    generate();
}

void Board::generate(){
    std::srand(time(0));

    do{
	for (int i = 0; i < 8; ++i)
	{
	    for (int j = 0; j < 8; ++j)
	    {
		squares[i][j] = static_cast<tSquare>((int)Gosu::random(1,8));
		squares[i][j].mustFall = true;
		squares[i][j].origY = Gosu::random(-7, -1);
		squares[i][j].destY = j - squares[i][j].origY;
	    }
	}
    }while(!check().empty() || solutions().empty()); 
    // Regenera si hay alguna solución directa o si es imposible

    lDEBUG << "Generado un board con posibles soluciones, sin soluciones inmediatas";
}

void Board::swap(int x1, int y1, int x2, int y2){
    tSquare temp = squares[x1][y1];

    squares[x1][y1] = squares[x2][y2];
    squares[x2][y2] = temp;
}

void Board::del(int x, int y){
    squares[x][y] = sqEmpty;
}

vector<coord> Board::solutions(){
    vector<coord> resultados;
    
    if(!check().empty()){
	resultados.push_back(coord(-1,-1));
	return resultados;
    }


    /* 
       Checkemos todos los posibles boards
       (49 * 4) + (32 * 2) aunque hay muchos repetidos
    */
    bool flag = false;


    Board temp = *this;
    for(int x = 0; x < 8; ++x){
	for(int y = 0; y < 8; ++y){
	    
	    // Cambiar con superior y check
	    if(y > 0){
		temp.swap(x,y, x,y-1);
		if(!temp.check().empty()){
		    resultados.push_back(coord(x,y));
		    flag = true;
		}
		temp.swap(x,y, x,y-1);
	    }

	    // Cambiar con inferior y check
	    if(y < 7){
		temp.swap(x, y, x, y+1);
		if(!temp.check().empty()){
		    resultados.push_back(coord(x,y));
		    flag = true;
		}
		temp.swap(x, y, x, y+1);
	    }

	    // Cambiar con celda izquierda y check
	    if(x > 0){
		temp.swap(x, y, x - 1, y);
		if(!temp.check().empty()){
		    resultados.push_back(coord(x,y));
		    flag = true;
		}
		temp.swap(x, y, x - 1, y);
	    }

	    // Cambiar con celda derecha y check
	    if(x < 7){
		temp.swap(x, y, x + 1, y);
		if(!temp.check().empty()){
		    resultados.push_back(coord(x,y));
		    flag = true;
		}
		temp.swap(x, y, x + 1, y);
	    }

	    
	}
    }
    
    
    return resultados;

}

vector<coord> Board::check(){
    // Recorremos filas
    tr1::array<tr1::array<int, 8>, 8> comprobHor;
    tr1::array<tr1::array<int, 8>, 8> comprobVer;

    // Ponemos matrices de comprobación a cero
    for(int y = 0; y < 8; ++y){
	for(int x = 0; x < 8; ++x){
	    comprobHor[x][y] = comprobVer[x][y] = 0;
	}
    }

    // Rellenamos la matriz de comprobaciones por FILAS
    for(int y = 0; y < 8; ++y){ 
	for(int x = 0; x < 8; ++x){ 

	    /* Recorremos de j - 1 hasta el inicio */
	    for(int k = x - 1; k >= 0; --k){ 
		if(squares[x][y] == squares[k][y] && squares[x][y] != sqEmpty){
		    comprobHor[x][y] = comprobHor[x][y] + 1;
		}else{
		    break; // Si alguna casilla no coincide, pues pasamos
		}
	    }

	    /* Recorremos de j + 1 hasta el final */
	    for(int k = x + 1; k < 8; ++k){
		if(squares[x][y] == squares[k][y] && squares[x][y] != sqEmpty){
		    comprobHor[x][y] = comprobHor[x][y] + 1;
		}else{
		    break; // Si alguna casilla no coincide, pues pasamos
		}
	    }
	}
    }


    // Rellenamos la matriz de comprobaciones por COLUMNAS
    for(int x = 0; x < 8; ++x){ 
	for(int y = 0; y < 8; ++y){ 

	    /* Recorremos de y - 1 hasta el inicio */
	    for(int k = y - 1; k >= 0; --k){ 
		if(squares[x][y] == squares[x][k] && squares[x][y] != sqEmpty){
		    comprobVer[x][y] = comprobVer[x][y] + 1;
		}else{
		    break; // Si alguna casilla no coincide, pues pasamos
		}
	    }

	    /* Recorremos de y + 1 hasta el final */
	    for(int k = y + 1; k < 8; ++k){
		if(squares[x][y] == squares[x][k] && squares[x][y] != sqEmpty){
		    comprobVer[x][y] = comprobVer[x][y] + 1;
		}else{
		    break; // Si alguna casilla no coincide, pues pasamos
		}
	    }
	}
    }


    bool flag = false;

    vector<coord> coordenadas;

    for(int y = 0; y < 8; ++y){ 
	for(int x = 0; x < 8; ++x){ 
	    if(comprobHor[x][y] > 1 || comprobVer[x][y] > 1){
		coordenadas.push_back(coord(x,y));
	    }
	}
    }

    return coordenadas;
}


void Board::calcFallMovements(){
    lDEBUG << "Board::calcFallMovements";
    for(int x = 0; x < 8; ++x){

	// De abajo a arriba
	for(int y = 7; y >= 0; --y){

	    // origY guarda la posición en el inicio de la caida
	    squares[x][y].origY = y;
	    
	    // Si la casilla es vacía, bajamos todas las squares por encima
	    if(squares[x][y] == sqEmpty){

		for(int k = y-1; k >= 0; --k){		    
		    squares[x][k].mustFall = true;
		    squares[x][k].destY ++;

		}
	    }
	}
    }
}

void Board::applyFall(){
    lDEBUG << "Board::applyFall";
    for(int x = 0; x < 8; ++x){
	// Desde abajo a arriba para no sobreescribir squares

	for(int y = 7; y >= 0; --y){
	    if(squares[x][y].mustFall && squares[x][y] != sqEmpty){
		int y0 = squares[x][y].destY;
		
		squares[x][y + y0] = squares[x][y];
		squares[x][y] = sqEmpty;
	    }
	}
   }
}

void Board::fillSpaces(){

    lDEBUG << "Board::fillSpaces";

	for(int x = 0; x < 8; ++x){
	    // Contar cuántos espacios hay que bajar
	    int saltos = 0;

	    for(int y = 0; y < 8; ++y){
		if(squares[x][y] != sqEmpty) break;
		saltos ++;
	    }

	    for(int y = 0; y < 8; ++y){
		if(squares[x][y] == sqEmpty) {
		    
		    squares[x][y] = static_cast<tSquare> ( (int)Gosu::random(1,8) );
		    
		    squares[x][y].mustFall = true;  
		    squares[x][y].origY = y - saltos;
		    squares[x][y].destY = saltos;
		}		
	    }
	}	
}

void Board::endAnimations(){
    for(int x = 0; x < 8; ++x){
	for(int y = 0; y < 8; ++y){
	    squares[x][y].mustFall = false;
	    squares[x][y].origY = y;
	    squares[x][y].destY = 0;
	}
    }
}

Board::~Board(){
    lDEBUG << Log::DES("Board");
}
