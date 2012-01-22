/*===========================================================================

	example.c

	A very basic soccer strategy.  All four players attempt to run
	up to the ball and kick it west!

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/

#include "players.h"
/* 
players.h includes a rather unusual macro, UN().  This macro
will convert the names of the functions in this .c file to
unique names.  For instance, if this were the east team, UN(team_name)()
will become EASTteam_name().  This is necessary for the automatic
compiling and linking of arbitrary teams for tournaments.

Below are the functions player1() through player4().  Each
function is passed 4 parameters.  The incoming parameters are 
the robot's sensory information:  

	local_area[]	Reveals what's nearby.  Indexed by
			N,NE,E,SE,S, etc. so that, for example,
			local_area[S] tells you what is in the
			cell to the south of the robot.  Possible 
			values include: BOUNDARY, OPPONENT, TEAMMATE,
			BALL and EMPTY.

	ball_direction	Compass heading to the ball: N, S, E, W, NE, etc.

	x, y		The robot's location.  y varies from 1 to 22,
			x varies from 1 to 78.

The function should return an integer indicating either a direction to
move (N, NE, E, S, etc) or KICK to kick the ball.
*/


/*-----------------------------------------------------

	homogeneousplayer()

	If the ball is nearby, either get to
	the east side of it, or if already on the
	east, kick it.

-----------------------------------------------------*/
int UN(homogeneousplayer)(int a[9], int bd, int x, int y)
{
#define R(x) return x;
#define B(x) a[x]==BALL
#define D(x,i) ("0123:5678,1256:8785,3010:2367"[x+i*10]-48)
#define F(x) if(a[x]<BALL)R(x)
if(B(E)&&(a[NE]==6||a[SE]==6)) R(bd);
if(B(bd)) R("9259-8985"[bd]-48)
F(D(bd,0))F(D(bd,1))F(D(bd,2))
}

/*-----------------------------------------------------

	player1()

	If the ball is nearby, either get to
	the east side of it, or if already on the
	east, kick it.

-----------------------------------------------------*/
int UN(player1)(int local_area[9], int ball_direction, int x, int y)
/*
UN(player1)(int local_area[9] . . .) becomes
EASTplayer(int local_area[9] . . .) or
WESTplayer(int local_area[9] . . .) depending on whether
this team is compiled to play on the east or west.
*/

{
/*
 * Just do the same thing as homogeneousplayer
 */
return(UN(homogeneousplayer)(local_area, ball_direction, x, y));
}

/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int UN(player2)(int local_area[9], int ball_direction, int x, int y)
{
/*
 * Just do the same thing as homogeneousplayer
 */
return(UN(homogeneousplayer)(local_area, ball_direction, x, y));
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int UN(player3)(int local_area[9], int ball_direction, int x, int y)
{
/*
 * Just do the same thing as homogeneousplayer
 */
return(UN(homogeneousplayer)(local_area, ball_direction, x, y));
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int UN(player4)(int local_area[9], int ball_direction, int x, int y)
{
/*
 * Just do the same thing as homogeneousplayer
 */
return(UN(homogeneousplayer)(local_area, ball_direction, x, y));
}

/*-----------------------------------------------------

	team_name()

	Every team must have a name.  Make sure it
	is exactly 20 characters.  Pad with spaces.

-----------------------------------------------------*/
char *UN(team_name)()
{
char	*s;

/*  "####################\0" <--- 20 characters */
s = (char*)"Matthew Dutton      \0";
return(s);
}

/*-----------------------------------------------------

	initialize_game()

	This function is called only once per
	game, before play begins.  You can leave it
	empty, or put code here to initialize your
	variables, etc.

-----------------------------------------------------*/
void UN(initialize_game)()
{
}

/*-----------------------------------------------------

	initialize_point()

	This function is called once per point, just
	before play begins for that point.
	You can leave it empty, or put code here to initialize 
	your variables, etc.

-----------------------------------------------------*/
void UN(initialize_point)()
{
}

/*-----------------------------------------------------

	lost_point()

	If your team loses a point, this function is
	called, otherwise, if you win the point, won_point()
	is called.  You can leave it empty, or put code here 
	for negative re-inforcement, etc.

-----------------------------------------------------*/
void UN(lost_point)()
{
}

/*-----------------------------------------------------

	won_point()

	If your team wins a point, this function is
	called, otherwise, if you lose the point, lost_point()
	is called.  You can leave it empty, or put code here 
	for positive re-inforcement, etc.

-----------------------------------------------------*/
void UN(won_point)()
{
}

/*-----------------------------------------------------

        game_over()

        This function is called once at the end of
        the match.  You can leave it empty, or put code 
        here to save things to a file, etc.

-----------------------------------------------------*/
void UN(game_over)()
{
}

