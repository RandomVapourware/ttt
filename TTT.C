/* MARTIAN TIC-TAC-TOE - ALPHA 0.0.20 */

/* A tic-tac-toe game for Turbo C on DOS.
   May Require EGAVGA.BGI from Turbo C to be placed in directory.
   May not work on real hardware; I used emulator 86Box.
   Screen resolution is hard coded, sorry. */

#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void drawframe();
void drawgame(char *);
void end();
void playfield();
int testinput(char);
int think( char *, char, char );
char win(char *);

/* ----- ----- MAIN ----- ----- */
main()
{
   /* Game State is stored in this String */
   char gamestate[16] = "nnnnnnnnn";
   char *statep = &gamestate[0];

   char player = 'x';
   char computer = 'o';
   char input = ' ';
   int computerfirst = 0;
   int moved = 0;
   int graphdriver = DETECT, graphmode;
   srand( time( NULL ) );

   /* Before Game, Select X or O */
   while ( input != 'x' && input != 'o' ) {
      puts( "Will you play as X or O?" );
      input = getch();
   }
   if ( input == 'o' ) {
      player = 'o';
      computer = 'x';
      computerfirst = 1;
   }

   /* Initiate Graphics Mode */
   initgraph( &graphdriver, &graphmode, "" );
   drawframe();
   drawgame(statep);

   while ( win( gamestate ) == 'n' ) {
      /* Player Turn */
      if ( computerfirst == 0 )
         if ( strchr( gamestate, 'n') != NULL ) {
            while ( moved == 0 ) {
               input = getch();
               if ( testinput(input) < 10
               && gamestate[testinput(input)] == 'n' ) {
                  gamestate[testinput(input)] = player;
                  moved = 1;
               }
            }
         } else
            goto label;
      if ( win( gamestate ) != 'n' ) {
         drawgame(statep);
         setfillstyle( SOLID_FILL, BLACK );
         bar( 600, 150, 420, 100 );
         setlinestyle( 0, 0xFFFF, 1 );
         rectangle( 600, 150, 420, 100 );
         if ( win( gamestate ) == player )
            outtextxy( 430, 110, "PLAYER WINS" );
         else if ( win( gamestate ) == computer )
            outtextxy( 430, 110, "COMPUTER WINS" );
         else
            outtextxy( 430, 110, "GAME OVER: NO WINNER" );
         end();
      }
      else
      computerfirst = 0;
      moved = 0;
      /* Computer Turn */
      if ( strchr( gamestate, 'n') != NULL )
         gamestate[ think( statep, computer, player ) ] = computer;
      /* Draw Graphics */
      drawgame(statep);
   }
   label:
   setfillstyle( SOLID_FILL, BLACK );
   setbkcolor( BLACK );
   bar( 600, 150, 420, 100 );
   setlinestyle( 0, 0xFFFF, 1 );
   rectangle( 600, 150, 420, 100 );
   if ( win( gamestate ) == player )
      outtextxy( 430, 110, "PLAYER WINS" );
   else if ( win( gamestate ) == computer )
      outtextxy( 430, 110, "COMPUTER WINS" );
   else
      outtextxy( 430, 110, "GAME OVER: NO WINNER" );
   while ( 1 ) {
      input = getch();
      testinput( input );
   }
}

/* ----- ----- FUNCTIONS ----- ----- */

/* -- DRAWFRAME() -- */
/* Draw the Decorations */
void drawframe()
{
   /* Define shape and location of Pyramids */
   int pyr1[6] = { 420, 300, 440, 250, 460, 300 };
   int pyr2[6] = { 480, 300, 510, 200, 540, 300 };
   int pyr3[6] = { 560, 300, 580, 250, 600, 300 };
   /* Background */
   setfillstyle( SOLID_FILL, LIGHTBLUE );
   bar( 0, 0, getmaxx(), getmaxy() );
   setfillstyle( SOLID_FILL, RED );
   bar( 0, 300, getmaxx(), getmaxy() );
   fillpoly( 3, pyr1 ); fillpoly( 3, pyr2 ); fillpoly( 3, pyr3 );
   setlinestyle( 0, 0xFFFF, 1 );
   line( 0, 300, getmaxx(), 300 );
   playfield();
}

/* -- DRAWGAME() -- */
/* Draw the Current Game State */
void drawgame(char * state)
{
   playfield();
   /* Q */
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[0] == 'x' ) {
      line( 45, 45, 155, 155 );
      line( 45, 155, 155, 45 );
   } else if ( state[0] == 'o' ) {
      circle( 100, 100, 50 );
   } else
      outtextxy( 45, 45, "Q" );
   /* W */
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[1] == 'x' ) {
      line( 165, 45, 275, 155 );
      line( 165, 155, 275, 45 );
   } else if ( state[1] == 'o' ) {
      circle( 220, 100, 50 );
   } else
      outtextxy( 165, 45, "W" );
   /* E */ 
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[2] == 'x' ) {
      line( 285, 45, 395, 155 );
      line( 285, 155, 395, 45 );
   } else if ( state[2] == 'o' ) {
      circle( 340, 100, 50 );
   } else
      outtextxy( 285, 45, "E" );
   /* A */
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[3] == 'x' ) {
      line( 45, 165, 155, 275 );
      line( 45, 275, 155, 165 );
   } else if ( state[3] == 'o' ) {
      circle( 100, 220, 50 );
   } else
      outtextxy( 45, 165, "A" );
   /* S */
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[4] == 'x' ) {
      line( 165, 165, 275, 275 );
      line( 165, 275, 275, 165 );
   } else if ( state[4] == 'o' ) {
      circle( 220, 220, 50 );
   } else
      outtextxy( 165, 165, "S" );
   /* D */
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[5] == 'x' ) {
      line( 285, 165, 395, 275 );
      line( 285, 275, 395, 165 );
   } else if ( state[5] == 'o' ) {
      circle( 340, 220, 50 );
   } else
      outtextxy( 285, 165, "D" );
   /* Z */
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[6] == 'x' ) {
      line( 45, 285, 155, 395 );
      line( 45, 395, 155, 285 );
   } else if ( state[6] == 'o' ) {
      circle( 100, 340, 50 );
   } else
      outtextxy( 45, 285, "Z" );
   /* X */
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[7] == 'x' ) {
      line( 165, 285, 275, 395 );
      line( 165, 395, 275, 285 );
   } else if ( state[7] == 'o' ) {
      circle( 220, 340, 50 );
   } else
      outtextxy( 165, 285, "X" );
   /* C */
   setlinestyle( 0, 0xFFFF, 3 );
   if ( state[8] == 'x' ) {
      line( 285, 285, 395, 395 );
      line( 285, 395, 395, 285 );
   } else if ( state[8] == 'o' ) {
      circle( 340, 340, 50 );
   } else
      outtextxy( 285, 285, "C" );
}

/* -- END() -- */
/* Return to DOS Prompt */
void end()
{
   getch();
   closegraph();
   exit( EXIT_SUCCESS );
}

/* -- PLAYFIELD() -- */
/* Draw the Play Field */
void playfield()
{
   setfillstyle( SOLID_FILL, BLACK );
   setbkcolor( BLACK );
   bar( 40, 20, 400, 400 );
   bar( 40, 20, 400, 35 );
   setlinestyle( 0, 0xFFFF, 1 );
   line( 40, 35, 400, 35 );
   outtextxy( 45, 25, "MARTIAN TIC-TAC-TOE | press p twice to quit" );
   rectangle( 40, 20, 400, 400 );
   rectangle( 160, 35, 280, 400 );
   rectangle( 40, 160, 400, 280 );
}

/* -- TESTINPUT() -- */
/* Test Input as Reasonable */
int testinput( char input )
{
   switch (input) {
      case 'q': return 0;
      case 'w': return 1;
      case 'e': return 2;
      case 'a': return 3;
      case 's': return 4;
      case 'd': return 5;
      case 'z': return 6;
      case 'x': return 7;
      case 'c': return 8;
      case 'p': end();
      default: return 20;
   }
}

/* -- THINK() -- */
/* Take a Board State, Output a Move */
int think( char * state, char computer, char player )
{
   char future[16];
   char *futurep = &future[0];
   char moves[16] = "000000000";
   int i;
   char max = '1';

   for ( i = 0; i < 9; i++ ) {
   /* Test for LEGALMOVE */
   if ( state[i] == 'n' ) {
      moves[i] = '1';
      /* Test for BLOCKMOVE */
      strcpy( futurep, state );
      future[i] = player;
      if ( win( future ) == player ) {
         moves[i] = '2';
         if ( max != '3' )
            max = '2';
      }
      /* Test for WINMOVE */
      strcpy( futurep, state );
      future[i] = computer;
      if ( win( future ) == computer ) {
         moves[i] = '3';
         max = '3';
      }
   } else
      moves[i] = '0';
   }
   do {
      i = rand() % 9;
   } while ( moves[i] != max );
   return i;
}

/* -- WIN() -- */
/* Check Board State for Win Conditions */
char win( char * state )
{
   if ( state[0] == state[1] && state[0] == state[2] )
      if ( state[0] != 'n' )
         return state[0];
   if ( state[3] == state[4] && state[3] == state[5] )
      if ( state[3] != 'n' )
         return state[3];
   if ( state[6] == state[7] && state[6] == state[8] )
      if ( state[6] != 'n' )
         return state[6];
   if ( state[0] == state[3] && state[0] == state[6] )
      if ( state[0] != 'n' )
         return state[0];
   if ( state[1] == state[4] && state[1] == state[7] )
      if ( state[1] != 'n' )
         return state[1];
   if ( state[2] == state[5] && state[2] == state[8] )
      if ( state[2] != 'n' )
         return state[2];
   if ( state[0] == state[4] && state[0] == state[8] )
      if ( state[0] != 'n' )
         return state[0];
   if ( state[2] == state[4] && state[2] == state[6] )
      if ( state[2] != 'n' )
         return state[2];
   return 'n';
}
