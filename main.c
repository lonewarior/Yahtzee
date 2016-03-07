/*************************************************************************
 * Programmer: Mitchell Weholt                                           *
 * Class: CptS 121; Lab Section 3                                        *
 * Programming Assignment: PA5											 *
 * Date: 10/23/15                                                        *
 *                                                                       *
 * Description: The game of Yahtzee. There are two players, and the game *
 *				goes back and forth between them. After each combo is used
 *				the program will not allow you to use them again, and will
 *				even show an 'X' in place of the number. Moreover, if a	 *
 *				combo is selected, but the dice do not meet the			 *
 *				requirements, then no points will be awarded. At the end,*
 *				if a player has over 63 points in the "Sum of #" category*
 *	 			then an extra 35 points will be given.					 * 
 *				There are 13 rounds.									 *
 *																		 *
 *																		 *
 ************************************************************************/



#include "Yahtzee.h"

void main (void)
{
	main_gameplay ();
}
