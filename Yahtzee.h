/*************************************************************************
 * Programmer: Mitchell Weholt
 * Class: CptS 121; Lab Section 3
 * Programming Assignment: PA4
 * Date: 10/7/15
 *
 * Description: Write a program that implements a craps game according
 *				to the provided rules.The game should allow for wagering.
 *				This means that you need to prompt that user for an
 *				initial bank balance from which wagers will be added or
 *				subtracted. Before each roll prompt the user for a
 *				wager. Once a game is lost or won, the bank balance
 *				should be adjusted. As the game progresses, print
 *				various messages to create some "chatter" such as,
 * 				"Sorry, you busted!", or "Oh, you're going for broke,
 *				huh?", or "Aw cmon, take a chance!", or "You're up big,
 *				now's the time to cash in your chips!"*
 *
 ************************************************************************/

#ifndef PA4_FUNCTIONS
#define PA4_FUNCTIONS

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// The game of craps
void main_gameplay ();

// Prints rules
void print_game_rules (void);

// Gets user provided bank balance
double get_bank_balance (void);

// Gets user provided wager
double get_wager_amount (void);

// Randomly selects an integer between 1-6
int roll_die (void);

// Prints ASCII dice and sum
void print_dice (int die1, int die2, int die_sum);

// Adds two ints together and returns an int
int calculate_sum_dice (int die1, int die2);

// Checks to see if wager is within the balance
int check_wager_amount (double wager, double balance);

// Calls wager functions and prints error messages if wager is too high
double process_wager (double balance);

// Determines if first roll is a win, loss, or a point
int is_win_loss_or_point (int sum_dice);

// Asks user if he/she wants to continue and ensures the responce is valid
char get_user_continue (void);

// Adds or subtracts wager from bank balance
double adjust_bank_balance (double bank_balance, double wager_amount, int add_or_subtract);

// Determines if every roll after the first is a win, loss, or neither
int is_point_loss_or_neither (int sum_dice, int point_value);

// Prints "dealer" chatter messages depending on input
void chatter_messages (int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);

#endif // !PA4_FUNCTIONS
