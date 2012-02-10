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

	Heterogenous team strategy()

	HACK: I encode my lookup tables as strings to conserve
	characters. I index into the array depending using a grid
	position (0-8) and subtract '0' to convert the result into
	a command (move, kick, noop).
		Example choice: "0123:5678"
	
	When the ball is on screen, what do you do?
	- If right next to the ball, on the west, obstruct.
	- Otherwise, go west, avoiding obstacles
	- If already on the west, kick!
	Ball-D     Ret  Alt1
	NW	0       K9    K9
	N	1      NE2    E5
	NE	2       E5    N1
	W	3       K9    K9
	PLR	4     nop:  nop:
	E	5     nop:  nop:     #SE8
	SW	6       K9    K9
	S	7      SE8    E5
	SE	8       E5    S7
	Built string: "9259::985,9519::957"

	Which direction should we move to get to an offscreen ball
	- and alternatives if that choice is blocked.
	- If all choices are blocked, do nothing. You're screwed.
		Ball-D      Ret  Alt1 Alt2
		NW	0		NW0    N1   W3
		N	1		NE2   NE2  NW0
		NE	2		NE2    E5   N1
		W	3		 W3   SW6  NW0
		PLR	4	    nop   nop  nop
		E	5		 E5   SE8  NE2
		SW	6		SW6    S7   W3
		S	7		SE8   SE8  SW6
		SE	8		SE8    E5   S7
	First choice:   "0223:5688"
	Alternate 1:  "1256:8785"
	Alternate 2:  "3010:2367"
	Built string: "0123:5678,1256:8785,3010:2367"

	MACROS:
	D(i) - lookup the action for when the ball is Close.
			b = the position of the ball on the grid
			i = which lookup table to use
				0,1 = first/second LUT for when the ball is near
				2,3,4 = first/second/third LUT for when the ball is far
	F(x) - return x if x is free (==open or goal), otherwise keep evaluating...
-----------------------------------------------------*/
#define D(i) (t[b+i*10]-48)
#define F(x) (a[x]<2)?(x):
#define DO(x) char*t=x; return (a[E]==2&&(a[NE]==OPPONENT||a[SE]==OPPONENT))?b:(a[b]==2)?(D(0)==9?9:F(D(0))D(1)):F(D(2))F(D(3))D(4);

int UN(playerA)(int a[9], int b)
{
DO("9259::985,9519::957,0223:5688,1256:8785,3010:2367")
}

int UN(playerB)(int a[9], int b)
{
DO("9259:8985,9519:2957,0223:5688,3010:2367,1256:8785")
}

int UN(playerC)(int a[9], int b)
{
DO("9259::985,9519::957,0223:5688,1256:8785,3010:2367")
}

int UN(playerD)(int a[9], int b)
{
DO("9259:8985,9519:2957,0223:5688,3010:2367,1256:8785")
}

#define ASSIGN_TEAM(p1,p2,p3,p4) \
    int UN(player1)(int a[9], int b, int x, int y) { return UN(player##p1)(a,b); } \
    int UN(player2)(int a[9], int b, int x, int y) { return UN(player##p2)(a,b); } \
    int UN(player3)(int a[9], int b, int x, int y) { return UN(player##p3)(a,b); } \
    int UN(player4)(int a[9], int b, int x, int y) { return UN(player##p4)(a,b); } \
    static char const * dutton_team = "Matt Dutton-pj2-" #p1#p2#p3#p4 "\0"; \
/* END MACRO */


// Uncomment one of the team assignments below to configure the team
ASSIGN_TEAM(A,A,A,A)
//ASSIGN_TEAM(A,A,A,B)
//ASSIGN_TEAM(A,A,B,B)
//ASSIGN_TEAM(A,B,B,A)
//ASSIGN_TEAM(A,A,B,C)
//ASSIGN_TEAM(A,B,C,D)

/*-----------------------------------------------------

	team_name()

	Every team must have a name.  Make sure it
	is exactly 20 characters.  Pad with spaces.

-----------------------------------------------------*/
char *UN(team_name)()
{
char	*s;

/*  "####################\0" <--- 20 characters */
s = (char*)dutton_team;
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


