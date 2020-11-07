/**
 * @file: breakout.c
 * @author: Billy.Ljm
 * @date: 19 June 2015
 * @brief: Variant of the classic "Breakout" game
 *
 * Ball only reflects vertically if it collides w/ paddle or brick
 * Hitting the side of the paddle or brick makes no difference
 */

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// commonly accessed variables
#define HEIGHT 600.0 // height of game's window
#define WIDTH 400.0 // width of game's window
#define BORDERW 5 // border width
#define BORDERC "black" // border colour
#define DIAMETER 10 // diameter of ball (must be smaller than bottom gap)

// prototypes
void initBricks(int numCols, int numRows, GRect bricks[numCols][numRows]); //initialise bricks
GOval initBall(); // initialise ball
GRect initPaddle(); // initialise paddle
GRect initLeftBorder(), initRightBorder(), initTopBorder(), initBottomBorder(); // initialise borders
GLabel initMessageboard(); // initialise message board
void updateMessageboard(GLabel messageboard, char* message); // update message board
GLabel initLifebar(); // initialise life bar
void updateLifebar(GLabel lifebar, int lives);
GObject detectCollision(GWindow window, GOval ball); // check if ball collides w/ any GObject


int main(void)
{
	// design parameters
	int numRows = 5; // number of rows for bricks
	int numCols = 10; // number of columns for bricks
	int lives = 3; // number of lives
	srand48(time(NULL));
	double vx = 0.01 + drand48() * 0.04; // x-velocity (in pixels per frame)
	double vy = -(0.04 + drand48() * 0.03); // y-velocity (in pixels per frame)

	// variable declarations
	int points = 0; // number of bricks destroyed
	int numBricks = numRows * numCols; // number of bricks left
	char pointStr[12]; // to store points in string form

	// graphical objects declarations
	GWindow window;
	GEvent event; // to listen to events
	GRect bricks[numCols][numRows]; // bricks[x][y] to be broken
	GOval ball; // ball which bounces off paddle
	GRect paddle; // paddle player controls
	GRect leftB, rightB, topB, bottomB; // borders
	GLabel messageboard; // message board
	GLabel lifebar; // life bar
	GObject collided; // object ball collides into

	// initialise graphical elements
	window = newGWindow(WIDTH, HEIGHT);
	initBricks(numCols, numRows, bricks);
	ball = initBall();
	paddle = initPaddle();
	leftB = initLeftBorder();
	rightB = initRightBorder();
	topB = initTopBorder();
	bottomB = initBottomBorder();
	messageboard = initMessageboard();
	lifebar = initLifebar();

	// initial draw
	for(int i = 0; i < numCols; i++){
		for(int j = 0; j < numRows; j++)
			add(window, bricks[i][j]);
	}
	add(window, ball);
	add(window, paddle);
	add(window, leftB);
	add(window, rightB);
	add(window, topB);
	setVisible(bottomB, false);
	add(window, bottomB);
	updateMessageboard(messageboard, "Click to Start");
	add(window, messageboard);
	updateLifebar(lifebar, lives);
	add(window, lifebar);

	// wait for click to start game
	waitForClick();

	// main game
	while (lives > 0 && numBricks > 0)
	{
		// move paddle
		event = getNextEvent(MOUSE_EVENT);
		if (event != NULL && getEventType(event) == MOUSE_MOVED)
		{
			if(getX(event) < getWidth(paddle)/2 + BORDERW)
				move(paddle, BORDERW - getX(paddle), 0);
			else if(getX(event) > WIDTH - BORDERW - getWidth(paddle)/2)
				move(paddle, WIDTH - BORDERW - getWidth(paddle) - getX(paddle), 0);
			else
				move(paddle, getX(event) - getWidth(paddle)/2 - getX(paddle), 0);
		}

		// move ball
		move(ball, vx, vy);

		// check for ball collisions
		collided = detectCollision(window, ball);

		// if no collision
		if(collided == NULL || collided == messageboard || collided == lifebar){
			// do nothing
		}

		// paddle block ball
		else if(collided == paddle){
			vy = -vy;
			move(ball, 0, getY(paddle) - DIAMETER - getY(ball));
		}

		// ball bounces off borders
		else if(collided == leftB || collided == rightB)
			vx = -vx;
		else if(collided == topB)
			vy = -vy;

		// ball went off bottom of screen
		else if(collided == bottomB){
			move(ball, (WIDTH - DIAMETER)/2 - getX(ball), (HEIGHT - DIAMETER)/2 - getY(ball));
			lives--;
			updateLifebar(lifebar, lives);
			if(lives > 0)
				waitForClick();
		}

		// ball hits brick
		else{
			for(int i = 0; i < numCols; i++){
				for(int j = 0; j < numRows; j++){
					if(collided == bricks[i][j]){
						vy = -vy;
						removeGWindow(window, bricks[i][j]);
						numBricks--;
						points++;
						sprintf(pointStr, "%i", points);
						updateMessageboard(messageboard, pointStr);
					}
				}
			}
		}
	}

	// Create end screen
	setColor(messageboard, "orange");
	if(lives == 0)
		updateMessageboard(messageboard, "GAME OVER");
	else if(numBricks == 0)
		updateMessageboard(messageboard, "YOU WON!");
	else
		updateMessageboard(messageboard, "ERROR");

	// wait for click to close window
	waitForClick();
	closeGWindow(window);
	return 0;
}


/**
 * @brief: initialises all bricks
 * @param [out] bricks: bricks numbered from left to right, then top to bottom
 */
void initBricks(int numCols, int numRows, GRect bricks[numCols][numRows])
{
	float w = 30; // width of bricks
	float h = 10; // height of bricks
	float xgap = 5; // horizontal gap
	float ygap = 5; // vertical gap
	float yoffset = 70; // gap b/w bricks & top border
	float xoffset = (WIDTH - numCols * w - (numCols - 1) * xgap)/2; // to centre bricks

	for(int i = 0; i < numCols; i++){
		for(int j = 0; j < numRows; j++){
			bricks[i][j] = newGRect(xoffset + i * (w + xgap),
									yoffset + j * (h + ygap),
									w, h);
			setFilled(bricks[i][j], true);
			setColor(bricks[i][j], "blue");
		}
	}
}


/**
 * @brief: initialises ball at middle
 * @return: ball Gobject
 */
GOval initBall()
{
	float d = 20; // diameter

	GOval ball = newGOval((WIDTH - DIAMETER)/2, (HEIGHT - DIAMETER)/2, DIAMETER, DIAMETER);
	setFilled(ball, true);
	setColor(ball, "red");
	return ball;
}


/**
 * @brief: initialises paddle at bottom-middle
 * @return: paddle Gobject
 */
GRect initPaddle()
{
	float w = 70; // width
	float h = 10; // height
	float gap = 15; // gap from bottom of screen

	GRect paddle = newGRect((WIDTH - w)/2, HEIGHT - h - gap, w, h);
	setFilled(paddle, true);
	setColor(paddle, "green");
	return paddle;
}

/**
 * @brief: initialises left border
 * @return: left border GRect
 */
GRect initLeftBorder(){
	GRect border = newGRect(0, 0, BORDERW, HEIGHT);
	setFilled(border, true);
	setColor(border, BORDERC);
	return border;
}


/**
 * @brief: initialises right border
 * @return: right border GRect
 */
GRect initRightBorder(){
	GRect border = newGRect(WIDTH - BORDERW, 0, BORDERW, HEIGHT);
	setFilled(border, true);
	setColor(border, BORDERC);
	return border;
}


/**
 * @brief: initialises top border
 * @return: top border GRect
 */
GRect initTopBorder(){
	GRect border = newGRect(0, 0, WIDTH, BORDERW);
	setFilled(border, true);
	setColor(border, BORDERC);
	return border;
}


/**
 * @brief: initialises bottom border
 * @return: bottom border GRect
 */
GRect initBottomBorder(){
	GRect border = newGRect(0, HEIGHT - BORDERW, WIDTH, BORDERW);
	setFilled(border, true);
	setColor(border, BORDERC);
	return border;
}


/**
 * @brief: initialises message board
 * @return: message board Gobject
 */
GLabel initMessageboard()
{
	GLabel messageboard = newGLabel("");
	setColor(messageboard, "gray");
	setFont(messageboard, "SansSerif-50");
	sendToBack(messageboard);
	return messageboard;
}


/**
 * @brief: update centred message board
 * @param messageboard: messageboard Gobject
 * @param message: message to be printed onto message board
 */
void updateMessageboard(GLabel messageboard, char* message)
{
	setLabel(messageboard, message);
	double dx = (WIDTH - getWidth(messageboard)) / 2 - getX(messageboard);
	double dy = (HEIGHT - getHeight(messageboard)) / 2 - getY(messageboard);
	move(messageboard, dx, dy);
}


/**
 * @brief: initialises life bar
 * @return: life bar Gobject
 */
GLabel initLifebar(){
	GLabel lifebar = newGLabel("");
	setColor(lifebar, "gray");
	setFont(lifebar, "SansSerif-30");
	setLocation(lifebar, getWidth(lifebar) + BORDERW + 10, getHeight(lifebar));
	sendToBack(lifebar);
	return lifebar;
}


/**
 * @brief: update life bar
 * @param lifebar: lifebar Gobject
 * @param lives: number of lives
 */
void updateLifebar(GLabel lifebar, int lives){
	// set label
	char lifestr[lives + 1];
	lifestr[lives] = '\0';
	for(int i = 0; i < lives; i++)
		lifestr[i] = '*';
	setLabel(lifebar, lifestr);
}


/**
 * @brief: check if ball collides with anything
 *
 * @param window: relevant Gwindow
 * @param ball: ball as a Gobject
 * @return: Gobject collided into, else NULL
 *
 * Simplifies ball to box & check for collision.
 * Also only detects 1 collided object each time called
 */
GObject detectCollision(GWindow window, GOval ball)
{
	double x = getX(ball); // x-coordinate
	double y = getY(ball); // y-coordinate
	GObject object = NULL; // to search & store any objects collide into

	// check top-left corner
	object = getGObjectAt(window, x, y);
	if (object != NULL)
		return object;

	// check top-right corner
	object = getGObjectAt(window, x + DIAMETER, y);
	if (object != NULL)
		return object;

	// check bottom-left corner
	object = getGObjectAt(window, x, y + DIAMETER);
	if (object != NULL)
		return object;

	// check bottom-right corner
	object = getGObjectAt(window, x + DIAMETER, y + DIAMETER);
	if (object != NULL)
		return object;

	// no collision
	return NULL;
}
