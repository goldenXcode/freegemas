/**
 * @file stateJuego.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Archivo para la clase de juego principal
 * 
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#ifndef _STATEGAME_H_
#define _STATEGAME_H_

#include <Gosu/Gosu.hpp>

#include <utility>
#include <set>
using namespace std;

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "state.h"
#include "board.h"
#include "floatingScore.h"
#include "baseButton.h"
#include "scoreTable.h"
#include "sdlfont.h"

class Game;

/**
 * @class StateGame
 *
 * @brief This is the main state of the game.
 *
 * Here is where the game actually takes place. 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class StateGame : public State{
public:

    /// Creates a new StateGame, initializing the loading screen
    StateGame(Game * p);


    void update();
    void draw();
    void buttonDown(Gosu::Button B);
    void buttonUp(Gosu::Button B);
    ~StateGame();

private:

    /** 
     * Function for the movement equation
     * 
     * @param t Delta of time
     * @param b Initial value
     * @param c Difference between initial and final value
     * @param d Duration
     * 
     * @return the proper value according the easing equation
     */
    static float eqMovIn(float t, float b, float c, float d);
    static float eqMovOut(float t, float b, float c, float d);

    void gemsOutScreen();

    int mostrandoPista;
    int totalAnimPista;

    coord coordPista;

    /// Carga las imágenes de las gemas
    //void cargarGemas();

    /// Loads the resources and intializes some variables
    void init();

    /// Loads the images for the gems
    void loadGems();

    /// Tests if the moouse is over a gem
    bool overGem(int mX, int mY);

    /// Returns the coords of the gem the mouse is over
    coord getCoord(int mX, int mY);

    /// Regenera la imagen del marcador de puntos

    /// Redraws the score board
    void redrawScoreboard();

    /// Creates a small label that indicates the points generated by a match
    void createFloatingScores();
    
    
    bool checkClickedSquare(int mX, int mY);

    /// Shows a hint for a possible match
    void showHint();

    /// Plays the sound for the match
    void playMatchSound();

    /// Resets the game
	void resetGame();

    /// The game board
    Board board;


    /// Different states of the game
    enum tState{
        eFirstFlip,
        eLoading,
        eInicialGemas,
        eEspera,
        eGemaMarcada,
        eGemasCambiando,
        eGemasDesapareciendo,
        eGemasNuevasCayendo,
        eDesapareceBoard,
        eTimeFinished,
        eShowingScoreTable
    };

    /// Current state
    tState state;

    /// Coordinates for the selected square (if any)
    coord selectedSquareFirst;

    /// Coordinates for the second selected square
    coord selectedSquareSecond;


    /// Animation current step
    int pasoAnim;

    /// Total animation steps
    int totalAnim;

    /// Total initial animation steps
    int totalAnimInit;

    /// Container for the grouped squares
    MultipleMatch groupedSquares;

    /// Current score
    int puntos;

    /// @{
    /// @name Images for the gems
    boost::shared_ptr<Gosu::Image> imgBoard;
    boost::shared_ptr<Gosu::Image> imgWhite;
    boost::shared_ptr<Gosu::Image> imgRed;
    boost::shared_ptr<Gosu::Image> imgPurple;
    boost::shared_ptr<Gosu::Image> imgOrange;
    boost::shared_ptr<Gosu::Image> imgGreen;
    boost::shared_ptr<Gosu::Image> imgYellow;
    boost::shared_ptr<Gosu::Image> imgBlue;
    /// @}

    /// Image for the gem selector
    boost::shared_ptr<Gosu::Image> imgSelector;

    /// Image for the score text
    boost::shared_ptr<Gosu::Image> txtPuntos;

    /// @{
    /// @name Buttons of the interface
    boost::scoped_ptr<BaseButton> hintButton;
    boost::scoped_ptr<BaseButton> resetButton;
    boost::scoped_ptr<BaseButton> exitButton;
    boost::scoped_ptr<BaseButton> musicButton;
    /// @}

    /// Group of floating scores. There may be some at the same time.
    vector<FloatingScore> scoreSet;

    /// Background for the clock
    boost::shared_ptr<Gosu::Image> imgTimeBackground;

    /// Image for the clock header
    boost::shared_ptr<Gosu::Image> imgTimeHeader;

    /// Background for the current-score board
    boost::shared_ptr<Gosu::Image> imgScoreBackground;

    /// Image for the current-score header
    boost::shared_ptr<Gosu::Image> imgScoreHeader;

    /// Font for the clock
    boost::shared_ptr<Gosu::Font> fontTime;

    /// Font for the current-score text
    boost::shared_ptr<Gosu::Font> fontScore;

    /// Loading screen image
    boost::shared_ptr<Gosu::Image> imgLoadingBanner;

    /// String with the remaining time
    string txtTime;

    /// Starting time
    double timeStart;


    /// @{
    /// @name Sounds of the game
    boost::scoped_ptr<Gosu::Sample> sfxMatch1, sfxMatch2, sfxMatch3;
    boost::scoped_ptr<Gosu::Sample> sfxSelect;
    boost::scoped_ptr<Gosu::Sample> sfxFall;
    boost::scoped_ptr<Gosu::Song> sfxSong;
    /// @}

    /// Current score acumulator
    int acumulator;

    /// Flag that indicates whether the user is clicking
    bool clicking;

    /// Reference to the score table
    boost::scoped_ptr<ScoreTable> scoreTable;
};

#endif /* _STATEGAME_H_ */
