/**
 * @file: breakout.c
 * @author: Billy.Ljm
 * @date: 21 June 2015
 * @brief: Variant of the classic "Breakout" game
 *
 * Ball gets faster & paddle gets smaller as points increase.
 * Also, shoot lasers by clicking the mouse. The lasers can destroy bricks,
 * However, it is immediate GAME OVER if the laser hits the ball.
 * The ball's trajectory is controlled by the part of the paddle used to block it.
 * Bricks further up are also worth more points.
 * There is also an auto-play invokable with `./breakout GOD`
 *
 * Ball only reflects vertically if it collides with brick
 * Because of this, the ball can sometimes destroy whole blocks of bricks at one time
 */

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// commonly accessed variables
#define PI 3.1415926535
#define HEIGHT 600.0 // height of game's window
#define WIDTH 400.0 // width of game's window
#define BORDERW 5 // border width
#define BORDERC "black" // border colour
#define DIAMETER 10 // diameter of ball (must be smaller than bottom gap)

// prototypes
// graphical functions
void initBricks(int numCols, int numRows, GRect bricks[numCols][numRows]); //initialise bricks
GOval initBall(); // initialise ball
GRect initPaddle(); // initialise paddle
GRect initLaser();
GRect initLeftBorder(), initRightBorder(), initTopBorder(), initBottomBorder(); // initialise borders
GLabel initMessageboard(); // initialise message board
GLabel initLifebar(); // initialise life bar

// helper functions
void updateMessageboard(GLabel messageboard, char* message); // update message board
void updateLifebar(GLabel lifebar, int lives); // update life bar
GObject detectCollision(GWindow window, GOval ball); // check if ball collides w/ any GObject

// game play functions
void updateBallSpeed(double* vx, double* vy, int points); // increment speed of ball based on points
void randBallAngle(double* vx, double* vy); // randomise ball angle (during start & when live lost)
void ballBlocked(GObject paddle, GObject ball, double* vx, double* vy); // update ball velocity when blocked w/ paddle
void updatePaddleSize(GObject paddle, int points); // update paddle width

int main(int argc, char** argv)
{
	// check arguments for god mode
	bool godmode;
	if(argc < 2)
		godmode = false;
	else if(argc == 2 && strcmp(argv[1], "GOD") == 0)
		godmode = true;
	else{
		printf("<How to Use Breakout>\n./breakout --- normal mode\n./breakout GOD --- GOD MODE!!!\n");
		return 0;
	}

	// design parameters
	int numRows = 5; // number of rows for bricks
	int numCols = 10; // number of columns for bricks
	int lives = 3; // number of lives
	srand48(time(NULL));

	// variable declarations
	int points = 0; // number of bricks destroyed
	int numBricks = numRows * numCols; // number of bricks left
	int mouseX; // x-coordinate or mouse (or of ball if in god mode)
	bool laserShot = false; // indicate if there is currently a laser in screen
	char pointStr[12]; // to store points in string form
	double vx, vy; // ball velocities
	updateBallSpeed(&vx, &vy, points);
	double laserSpeed = 0.08; // laser speed

	// graphical objects declarations
	GWindow window;
	GEvent event; // to listen to events
	GRect bricks[numCols][numRows]; // bricks[x][y] to be broken
	GOval ball; // ball which bounces off paddle
	GRect paddle; // paddle player controls
	GRect laser; // laser which player shoots
	GRect leftB, rightB, topB, bottomB; // borders
	GLabel messageboard; // message board
	GLabel lifebar; // life bar
	GObject collided; // object ball collides into

	// initialise graphical elements
	window = newGWindow(WIDTH, HEIGHT);
	initBricks(numCols, numRows, bricks);
	ball = initBall();
	paddle = initPaddle();
	laser = initLaser();
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
	updatePaddleSize(paddle, points);
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
	pause(500);
	waitForClick();
	updateMessageboard(messageboard, "0");

	// main game
	NEWFRAME: while (lives > 0 && numBricks > 0)
	{
		// if god mode, make paddle follow ball
		if(godmode)
			mouseX = getX(ball) + (DIAMETER - getWidth(paddle))/2;
		// else get mouse x-coordinates
		else{
			event = getNextEvent(MOUSE_EVENT);
			if(event != NULL && getEventType(event) == MOUSE_MOVED)
				mouseX = getX(event);
			else
				mouseX = -1; // flag for next conditional
		}

		// else make paddle follow mouse
		if(mouseX != -1){
			if(mouseX < getWidth(paddle)/2 + BORDERW)
				move(paddle, BORDERW - getX(paddle), 0);
			else if(mouseX > WIDTH - BORDERW - getWidth(paddle)/2)
				move(paddle, WIDTH - BORDERW - getWidth(paddle) - getX(paddle), 0);
			else
				move(paddle, mouseX - getWidth(paddle)/2 - getX(paddle), 0);
		}

		// shoot laser
		if(!laserShot){
			event = getNextEvent(MOUSE_EVENT);
			if(event != NULL && getEventType(event) == MOUSE_CLICKED){
				setLocation(laser, getX(paddle) + (getWidth(paddle) - getWidth(laser))/2,
					getY(paddle) - getHeight(paddle) - getHeight(laser));
				add(window, laser);
				laserShot = true;
			}
		}

		// move ball & laser
		move(ball, vx, vy);
		if(laserShot)
			move(laser, 0, -laserSpeed);

		// check for ball collisions
		collided = detectCollision(window, ball);
		// if no collision
		if(collided == NULL || collided == messageboard || collided == lifebar){
			// do nothing
		}
		// ball shot by laser
		else if(collided == laser){
			lives = 0;
			goto GAMEOVER;
		}
		// paddle block ball
		else if(collided == paddle){
			//move(ball, 0, getY(paddle) - DIAMETER - getY(ball));
			ballBlocked(paddle, ball, &vx, &vy);
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
			randBallAngle(&vx, &vy);
			if(lives > 0){
				pause(500);
				waitForClick();
			}
		}
		// ball hits brick
		else{
			for(int i = 0; i < numCols; i++){
				for(int j = 0; j < numRows; j++){
					if(collided == bricks[i][j]){
						vy = -vy;
						removeGWindow(window, bricks[i][j]);
						numBricks--;
						points += numRows - j;
						sprintf(pointStr, "%i", points);
						updateMessageboard(messageboard, pointStr);
						updatePaddleSize(paddle, points);
						updateBallSpeed(&vx, &vy, points);
						goto LASERCHECK;
					}
				}
			}
		}

		// check for laser collisions
		LASERCHECK: if(laserShot){
			collided = detectCollision(window, laser);
			// if no collision
			if(collided == NULL || collided == messageboard || collided == lifebar){
				// do nothing
			}
			// laser shot ball
			else if(collided == ball){
				lives = 0;
				goto GAMEOVER;
			}
			// laser hit top border
			else if(collided == topB){
				removeGWindow(window, laser);
				laserShot = false;
			}
			else{
				for(int i = 0; i < numCols; i++){
					for(int j = 0; j < numRows; j++){
						if(collided == bricks[i][j]){
							removeGWindow(window, laser);
							laserShot = false;

							removeGWindow(window, bricks[i][j]);
							numBricks--;
							points += numRows - j;
							sprintf(pointStr, "%i", points);
							updateMessageboard(messageboard, pointStr);
							updatePaddleSize(paddle, points);
							updateBallSpeed(&vx, &vy, points);
							goto NEWFRAME;
						}
					}
				}
			}
		}
	}

	// Create end screen
	GAMEOVER: setColor(messageboard, "orange");
	if(lives == 0)
		updateMessageboard(messageboard, "GAME OVER");
	else if(numBricks == 0)
		updateMessageboard(messageboard, "YOU WON!");
	else
		updateMessageboard(messageboard, "ERROR");

	// wait for click to close window
	pause(1000);
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

	char* color[] = {"red", "orange", "yellow", "green", "blue"};
	for(int i = 0; i < numCols; i++){
		for(int j = 0; j < numRows; j++){
			bricks[i][j] = newGRect(xoffset + i * (w + xgap),
									yoffset + j * (h + ygap),
									w, h);
			setFilled(bricks[i][j], true);
			setColor(bricks[i][j], color[j % sizeof(color)]);
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
	setColor(ball, "magenta");
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
	setColor(paddle, "cyan");
	return paddle;
}

/**
 * @brief: initialises laser
 * @return: laser Gobject
 */
GRect initLaser(){
	float w = 3;
	float h = 30;

	GRect laser = newGRect((WIDTH - w) / 2, 50 + h, w, h);
	setFilled(laser, true);
	setColor(laser, "dark_gray");
	return laser;
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
 * @param obejct: Gobject to check for collisions
 * @return: Gobject collided into, else NULL
 *
 * Simplifies ball to box & check for collision.
 * Also only detects 1 collided object each time called
 */
GObject detectCollision(GWindow window, GObject object)
{
	double gap = 1; // gap b/w hit box & actual objects

	// Get object dimensions
	double x = getX(object);
	double y = getY(object);
	double w  = getWidth(object);
	double h = getHeight(object);

	// to search & store any objects collided into
	GObject collided = NULL;

	// check top-left corner
	collided = getGObjectAt(window, x - gap, y - gap);
	if (collided != NULL)
		return collided;
	// check top-right corner
	collided = getGObjectAt(window, x + w + gap, y - gap);
	if (collided != NULL)
		return collided;
	// check bottom-left corner
	collided = getGObjectAt(window, x - gap, y + h + gap);
	if (collided != NULL)
		return collided;
	// check bottom-right corner
	collided = getGObjectAt(window, x + w + gap, y + h + gap);
	if (collided != NULL)
		return collided;
	// no collision
	return NULL;
}

/**
 * @brief: speed up ball speed (called when bricks broken & points increase)
 * @param [in] vx, vy: initial velocity
 * @param [out] vx, vy: final velocity
 * @param points: current points
 */
void updateBallSpeed(double* vx, double* vy, int points){
	if(points == 0){
		*vx = 0.05; *vy = 0;
		randBallAngle(vx,vy);
	}
	else{
		*vx = *vx * 1.01;
		*vy = *vy * 1.01;
	}
	return;
}

/**
 * @brief: randomise ball angle
 * @param [out] vx: x-velocity
 * @param[out] vy: y-velocity
 */
void randBallAngle(double* vx, double* vy){
	double v = sqrt(pow(*vx,2) + pow(*vy,2));

	double theta = (0.25 + drand48() / 2) * PI;
	*vy = v * sin(theta);
	*vx = v * cos(theta);
	return;
}

/**
 * @brief: update ball if blocked with paddle
 * @param paddle: paddle GObject
 * @param ball: ball Gobject
 * @param [in] vx, vy: ball's velocity before collision
 * @param [out] vx, vy: ball's velocity after collision
 */
void ballBlocked(GObject paddle, GObject ball, double* vx, double* vy){
	double v = sqrt(pow(*vx,2) + pow(*vy,2)); // net speed
	*vx = (2*getX(ball) + DIAMETER - 2*getX(paddle) - getWidth(paddle)) / (getWidth(paddle) + DIAMETER) * 19/20 *v;
	*vy = -sqrt(pow(v,2) - pow(*vx,2));
	return;
}

/**
 * @brief: update paddle width
 * @param paddle: paddleGobject
 * @param points: current points
 */
void updatePaddleSize(GObject paddle, int points){
	double width = 80 - points;
	if(width < 20)
		width = 20;
	setSize(paddle, width, getHeight(paddle));
	return;
}
