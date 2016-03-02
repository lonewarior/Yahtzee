#include "Yahtzee.h"

 //************************************************************
 // Function: main_gameplay (void)
 // Date Created: 10/7/15
 // Date Last Modified: 10/7/15
 // Description: Runs the main gameplay for craps
 // Input parameters: none
 // Returns: none
 // Preconditions: Start of program
 // Postconditions: none
 //************************************************************
void main_gameplay (void)
{
	/******** Variables *********/
	double balance = 0.0, wager = 0.0, old_balance = 0.0;
	int die1 = 0, die2 = 0, die_sum = 0, roll1 = 0, point = 0, turn = 0, subsequent_rolls = 0, number_rolls = 0;
	char user_continue = '\0';

	srand((unsigned int)time (NULL)); // Set random string


	/********** Game pre-reqs **********/
	// Print rules
	print_game_rules ();
	// Ask user for starting balance
	balance = get_bank_balance ();
	old_balance = balance;


	/******** START GAMEPLAY ********/
	do
	{
		// FIRST ROLL
		do
		{
			// Get wager
			wager = process_wager (balance);

			// Roll the dice and sum
			die1 = roll_die ();
			die2 = roll_die ();
			number_rolls++;
			die_sum = calculate_sum_dice (die1, die2);
			point = die_sum;
			old_balance = balance;

			// Print pretty die
			print_dice (die1, die2, die_sum);

			// Win or loss logic
			roll1 = is_win_loss_or_point (die_sum);
			switch (roll1)
			{
				case 1:
					balance = adjust_bank_balance (balance, wager, 1);
					printf("You won! Your balance is now %.2lf. ", balance);
					chatter_messages (number_rolls, roll1, old_balance, balance);
					printf("Do you want to roll again? ", balance);
					user_continue = get_user_continue ();
					turn = 0;
					break;
				case 0:
					balance = adjust_bank_balance (balance, wager, 0);
					// Check if balance is now 0
					if (balance == 0)
					{
						printf("Oh no! You went broke. Better luck next time!");
						user_continue = 'n';
						turn = 1;
						break;
					}
					printf("Sorry, you lost! Your balance is now %.2lf. ", balance);
					chatter_messages (number_rolls, roll1, old_balance, balance);
					printf("Do you want to roll again? ", balance);
					user_continue = get_user_continue ();
					turn = 0;
					break;
				case -1:
					printf("Keep rolling until you make your point (roll a %d). Just don't roll a 7!", die_sum);
					printf("\nDo you want to continue rolling? ");
					turn=1;
					user_continue = get_user_continue ();
					break;
			}

		}
		while (turn == 0);

		// THE OTHER ROLLS
		while ((user_continue == 'Y') || (user_continue == 'y'))
		{
			// Roll the dice
			die1 = roll_die ();
			die2 = roll_die ();
			die_sum = calculate_sum_dice (die1, die2);
			number_rolls++;
			// Print the dice
			print_dice (die1, die2, die_sum);

			old_balance = balance;

			// Check if the roll wins
			subsequent_rolls = is_point_loss_or_neither (die_sum, point);
			switch (subsequent_rolls)
			{
				case 1:
					balance = adjust_bank_balance (balance, wager, 1);
					printf("You won! Your new balance is now %.2lf. \n", balance);
					chatter_messages (number_rolls, subsequent_rolls, old_balance, balance);
					printf("Do you want to roll again? ");
					user_continue = get_user_continue ();
					if (('y' == user_continue) || ('Y' == user_continue))
						{user_continue = 'T';}
					break;
				case 0:
					balance = adjust_bank_balance (balance, wager, 0);
					// Check if balance is now 0
					if (balance == 0)
					{
						printf("Oh no! You lost and went broke. Better luck next time!\n");
						user_continue = 'n';
						break;
					}
					printf("Sorry, you lost. Your new balance is now %.2lf. \n", balance);
					chatter_messages (number_rolls, subsequent_rolls, old_balance, balance);
					printf("Do you want to roll again? ");
					user_continue = get_user_continue ();
					if (('y' == user_continue) || ('Y' == user_continue))
						{user_continue = 'T';}
					break;
				case -1:
					user_continue = 'Y';
					printf("You didn't make your point. \n");
					chatter_messages (number_rolls, subsequent_rolls, old_balance, balance);
					printf("Do you want to continue rolling? ");
					user_continue = get_user_continue ();
					break;
				default:
					break;
			}

		}

	}
	while ((user_continue == 'Y') || (user_continue == 'y') || (user_continue == 'T'));

}

 /************************************************************
 * Function: print_game_rules (void)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Prints the game rules
 * Input parameters: none
 * Returns: none
 * Preconditions: Start of program
 * Postconditions: none
 *************************************************************/
void print_game_rules (void)
{
	printf("************************************************ Welcome to Craps! ************************************************\n\n");
	printf("How to play:\n\n");
	printf("A player rolls two dice. Each die has six faces. These faces contain 1, 2, 3, 4, 5, and 6 spots.\nAfter the dice have come to rest, the sum of the spots on the two upward faces is calculated.\nIf the sum is 7 or 11 on the first throw, the player wins. If the sum is 2, 3, or 12\non the first throw (called 'craps'), the player loses (i.e. the 'house' wins). If the sum is 4, 5, 6, 8, 9, or 10\non the first throw, then the sum becomes the player's 'point.' To win, you must continue rolling the dice until\nyou 'make your point.' The player loses by rolling a 7 before making the point.\n\n");
}

 /************************************************************
 * Function: get_bank_balance (void)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Gets the starting balance from user
 * Input parameters: none
 * Returns: Balance as double
 * Preconditions: Start of program
 * Postconditions: Returns balance
 *************************************************************/
double get_bank_balance (void)
{
	double balance = 0.0;
	printf("Enter your starting balance: ");
	scanf("%lf", &balance);

	return balance;
}

 /************************************************************
 * Function: get_wager_amount (void)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Gets wager from user
 * Input parameters: none
 * Returns: Wager as double
 * Preconditions: Start of program
 * Postconditions: Returns wager
 *************************************************************/
double get_wager_amount (void)
{
	double wager = 0.0;
	printf("Enter your wager and press enter to roll: ");
	scanf("%lf", &wager);

	return wager;
}

 /************************************************************
 * Function: roll_die (void)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Selects a random int between 1-6
 * Input parameters: none
 * Returns: Random integer between 1-6
 * Preconditions: Start of program
 * Postconditions: Returns random integer between 1-6
 *************************************************************/
int roll_die (void)
{
	int roll = 0;
	roll = rand () % 6 + 1;

	return roll;
}

 /************************************************************
 * Function: print_dice (int die1, int die2, int die_sum)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Prints out ASCII dice
 * Input parameters: Die1, Die2, and die_sum
 * Returns: none
 * Preconditions: Start of program
 * Postconditions: none
 *************************************************************/
void print_dice (int die1, int die2, int die_sum)
{
	printf("\n*******************************************************************************************************************\n");
	if ((die1 == 1) && (die2 == 1))
	{
		printf("-----	-----\n|   |	|   |\n| o |	| o |\n|   |	|   |\n-----	-----\n");
	}
	else if (((die1 == 1) && (die2 == 2)) || ((die1 == 2) && (die2 == 1)))
	{
		printf("-----	-----\n|   |	|o  |\n| o |	|   |\n|   |	|  o|\n-----	-----\n");
	}
	else if (((die1 == 1) && (die2 == 3)) || ((die1 == 3) && (die2 == 1)))
	{
		printf("-----	-----\n|   |	|o  |\n| o |	| o |\n|   |	|  o|\n-----	-----\n");
	}
	else if (((die1 == 1) && (die2 == 4)) || ((die1 == 4) && (die2 == 1)))
	{
		printf("-----	-----\n|   |	|o o|\n| o |	|   |\n|   |	|o o|\n-----	-----\n");
	}
	else if (((die1 == 1) && (die2 == 5)) || ((die1 == 5) && (die2 == 1)))
	{
		printf("-----	-----\n|   |	|o o|\n| o |	| o |\n|   |	|o o|\n-----	-----\n");
	}
	else if (((die1 == 1) && (die2 == 6)) || ((die1 == 6) && (die2 == 1)))
	{
		printf("-----	-----\n|   |	|o o|\n| o |	|o o|\n|   |	|o o|\n-----	-----\n");
	}
	else if ((die1 == 2) && (die2 == 2))
	{
		printf("-----	-----\n|o  |   |o  |\n|   |	|   |\n|  o|	|  o|\n-----	-----\n");
	}
	else if (((die1 == 2) && (die2 == 3) || ((die1 == 3) && (die2 == 2))))
	{
		printf("-----	-----\n|o  |   |o  |\n| o |	|   |\n|  o|	|  o|\n-----	-----\n");
	}
	else if (((die1 == 2) && (die2 == 4)) || ((die1 == 4) && (die2 ==2)))
	{
		printf("-----	-----\n|o o|   |o  |\n|   |	|   |\n|o o|	|  o|\n-----	-----\n");
	}
	else if (((die1 == 2) && (die2 == 5)) || ((die1 == 5) && (die2 ==2)))
	{
		printf("-----	-----\n|o o|   |o  |\n| o |	|   |\n|o o|	|  o|\n-----	-----\n");
	}
	else if (((die1 == 2) && (die2 == 6)) || ((die1 == 6) && (die2 == 2)))
	{
		printf("-----	-----\n|o o|   |o  |\n|o o|	|   |\n|o o|	|  o|\n-----	-----\n");
	}
	else if ((die1 == 3) && (die2 == 3))
	{
		printf("-----	-----\n|o  |   |o  |\n| o |	| o |\n|  o|	|  o|\n-----	-----\n");
	}
	else if (((die1 == 3) && (die2 == 4)) || ((die1 == 4) && (die2 == 3)))
	{
		printf("-----	-----\n|o  |   |o o|\n| o |	|   |\n|  o|	|o o|\n-----	-----\n");
	}
	else if (((die1 == 3) && (die2 == 5)) || ((die1 == 5) && (die2 == 3)))
	{
		printf("-----	-----\n|o  |   |o o|\n| o |	| o |\n|  o|	|o o|\n-----	-----\n");
	}
	else if (((die1 == 3) && (die2 == 6)) || ((die1 == 6) && (die2 == 3)))
	{
		printf("-----	-----\n|o  |   |o o|\n| o |	|o o|\n|  o|	|o o|\n-----	-----\n");
	}
	else if (((die1 == 4) && (die2 == 4)))
	{
		printf("-----	-----\n|o o|   |o o|\n|   |	|   |\n|o o|	|o o|\n-----	-----\n");
	}
	else if (((die1 == 4) && (die2 == 5)) || ((die1 == 5) && (die2 == 4)))
	{
		printf("-----	-----\n|o o|   |o o|\n|   |	| o |\n|o o|	|o o|\n-----	-----\n");
	}
	else if (((die1 == 4) && (die2 == 6)) || ((die1 == 6) && (die2 == 4)))
	{
		printf("-----	-----\n|o o|   |o o|\n|   |	|o o|\n|o o|	|o o|\n-----	-----\n");
	}
	else if (((die1 == 5) && (die2 == 4)) || ((die1 == 4) && (die2 == 5)))
	{
		printf("-----	-----\n|o o|   |o o|\n| o |	|   |\n|o o|	|o o|\n-----	-----\n");
	}
	else if ((die1 == 5) && (die2 == 5))
	{
		printf("-----	-----\n|o o|   |o o|\n| o |	| o |\n|o o|	|o o|\n-----	-----\n");
	}
	else if (((die1 == 5) && (die2 == 6)) || ((die1 == 6) && (die2 == 5)))
	{
		printf("-----	-----\n|o o|   |o o|\n| o |	|o o|\n|o o|	|o o|\n-----	-----\n");
	}
	else if ((die1 == 6) && (die2 == 6))
	{
		printf("-----	-----\n|o o|   |o o|\n|o o|	|o o|\n|o o|	|o o|\n-----	-----\n");
	}
	else
	{
		printf("Error");
	}

	if (die_sum >= 10)
	{printf("-- Sum: %d --\n\n", die_sum);}
	else {printf("-- Sum: %d  --\n\n", die_sum);}


	printf("*******************************************************************************************************************\n\n");


}

 /************************************************************
 * Function: calculate_sum_dice (int die1, int die2)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Calculates the sum of two int values
 * Input parameters: die1, die2
 * Returns: Sum of two integers as an integer
 * Preconditions: Start of program
 * Postconditions: Returns sum
 *************************************************************/
int calculate_sum_dice (int die1, int die2)
{
	int die_sum = 0;
	die_sum = die1 + die2;

	return die_sum;
}

 /************************************************************
 * Function: check_wager_amount(double wager, double balance)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Checks if wager is greater than balance
 * Input parameters: Wager, balance
 * Returns: int 0 for less than balance, 1 for greater than
 * Preconditions: Start of program
 * Postconditions: Returns int
 *************************************************************/
int check_wager_amount (double wager, double balance)
{
	int result = 0;
	if (balance-wager >= 0)
	{
		result = 1;
	}

	return result;
}

 /************************************************************
 * Function: process_wager (double balance)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Calls get_wager_amount, check_wager_amount
 *				then prints an error and loops if the wager
 *				is greater than balance
 * Input parameters: Balance
 * Returns: Wager as double
 * Preconditions: Start of program
 * Postconditions: Returns wager
 *************************************************************/
double process_wager (double balance)
{
	int wager_result = 0;
	double wager = 0.0;
	do
	{
		wager = get_wager_amount ();
		wager_result = check_wager_amount (wager, balance);
		if (wager_result != 1)
		{
			printf("\noops! You tried to bet more than you have, which is %.2lf. Try again.\n", balance);
		}

	}
	while (wager_result == 0);

	return wager;
}

 /************************************************************
 * Function: is_win_loss_or_point (int die_sum)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Checks if the first rolls was won, loss, or
 *				point. Returns 0 for win, 1 for loss, -1
 *				for point.
 * Input parameters: Die_sum
 * Returns: Int value for win, loss, or point
 * Preconditions: Start of program
 * Postconditions: Returns int
 *************************************************************/
int is_win_loss_or_point (int die_sum)
{
	int result = 0;

	switch (die_sum)
	{
	case 7:
	case 11: result = 1;
			 break;
	case 4:
	case 5:
	case 6:
	case 8:
	case 9:
	case 10: result = -1;

	default:
		break;
	}

	return result;
}

 /************************************************************
 * Function: get_user_continue (void)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Gets user continue value, then checks for
 *				a valid input
 * Input parameters: none
 * Returns: Character for user continue
 * Preconditions: Start of program
 * Postconditions: Returns character
 *************************************************************/
char get_user_continue (void)
{
	char user_continue = 'a';

	do
	{
	printf("Enter ""Y"" for yes, or ""N"" for no. ");
	scanf (" %c", &user_continue);
		if ((user_continue != 'Y') && (user_continue != 'y') && (user_continue != 'n') && (user_continue != 'N'))
		{
			printf("\nInvalid responce. ");
		}
	}
	while ((user_continue != 'Y') && (user_continue != 'y') && (user_continue != 'n') && (user_continue != 'N'));


	return user_continue;
}

 /************************************************************
 * Function: adjust_bank_balance (double bank_balance, double
 *			 wager_amount, int add_or_subtract)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Subtracts or adds wager to/from balance
 * Input parameters: Balance, wager, add_or_subtract
 * Returns: New bank balance
 * Preconditions: Start of program
 * Postconditions: Returns bank balance
 *************************************************************/
double adjust_bank_balance (double bank_balance, double wager_amount, int add_or_subtract)
{
	double new_balance = 0.0;

	switch (add_or_subtract)
	{
	case 1:
		new_balance = bank_balance + wager_amount;
		break;
	case 0:
		new_balance = bank_balance - wager_amount;
		break;
	default:
		break;
	}

	return new_balance;
}

 /************************************************************
 * Function: is_point_loss_or_neither (int sum_dice,
 *			 int point_value)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Returns 0 for loss, 1 for win, -1 for neither
 * Input parameters: Sum_dice, point_value
 * Returns: Int for win, loss, neither
 * Preconditions: Start of program
 * Postconditions: Returns int
 *************************************************************/
int is_point_loss_or_neither (int sum_dice, int point_value)
{
	int value = 0;

	if (sum_dice == 7)
	{value = 0;}
	else if (point_value == sum_dice)
	{value = 1;}
	else
	{value = -1;}

	return value;
}

 /************************************************************
 * Function: chatter_messages (int number_rolls, int win_loss
 *			 neither, double initial_bank_balance, double
 *			 current_bank_balance)
 * Date Created: 10/7/15
 * Date Last Modified: 10/7/15
 * Description: Prints "dealer" chatter based on inputs
 * Input parameters: Number of rolls, win_loss_neither,
 *					 starting balance, current balance
 * Returns: New bank balance
 * Preconditions: Start of program
 * Postconditions: Returns bank balance					     
 *************************************************************/
void chatter_messages (int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
{
		// Doubled balance
		if (current_bank_balance >= (2*initial_bank_balance))
			{printf("DEALER: You've doubled your balance!\n");}

		// 50 rolls
		if (number_rolls == 50)
			{printf("DEALER: This is your 50th roll this game... you have a problem.\n");}

		// 10 rolls
		else if (number_rolls == 10)
			{printf("DEALER: This is your 10th roll this game... you may want to take a break!\n");}

		// Win on first roll
		if ((number_rolls == 1) && (win_loss_neither == 1))
			{printf ("DEALER: Nice! Winning on your first roll is a 20%% chance.\n");}

		// Just won the last roll
		else if (win_loss_neither == 1)
			{printf ("DEALER: Good roll!\n");}

		// Lost the last roll
		else if (win_loss_neither == 0)
			{printf("DEALER: Better luck next time. Keep rolling to try and win!\n");}


}
