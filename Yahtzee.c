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

 /************************************************************
 * Function: main_gameplay (void)						     *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Runs the main gameplay for yahtzee	         *
 * Input parameters: none									 *
 * Returns: none									         *
 * Preconditions: Start of program                           *
 * Postconditions: none									     *
 *************************************************************/
void main_gameplay (void)
{
	// Declare variables
	int die[5] = {0}, p1_scores[13] = {0}, p1_combinations[13] = {0}, p2_scores[13] = {0}, p2_combinations[13] = {0}, player = 1, turn = 0;

	// Set rand string
	srand((unsigned int)time(NULL));

	while(gameplay_menu())
	{

		while(turn<14)
		{
			// PLAYER 1
			system("cls");
			printf("************************************************** PLAYER 1 ********************************************************\n");
			printf("************************************************** ROUND %d ********************************************************\n\n", turn);
			roll_dice(die, 5);
			print_die(die, 5, p1_combinations);
			reroll(die, 5, p1_combinations,1,turn);
			choose_combo(die, 5, p1_combinations, p1_scores,1,turn);
			
			system("cls");
			printf("************************************************** PLAYER 1 ********************************************************\n");
			printf("************************************************** ROUND %d ********************************************************\n\n", turn);
			print_score (p1_scores, 1);

			printf("\n\nPress any key to switch to player 2.");
			system("pause > nul");
			system("cls");



			// PLAYER 2
			system("cls");
			printf("************************************************** PLAYER 2 ********************************************************\n");
			printf("************************************************** ROUND %d ********************************************************\n\n", turn);
			roll_dice(die, 5);
			print_die(die, 5,p2_combinations);
			reroll(die, 5, p1_combinations,2,turn);
			choose_combo(die, 5, p2_combinations, p2_scores,2,turn);
			
			system("cls");
			printf("************************************************** PLAYER 2 ********************************************************\n");
			printf("************************************************** ROUND %d ********************************************************\n\n", turn);
			print_score (p2_scores, 2);

			system("pause\n");
			system("cls");


			turn++;

		}

		end_game(p1_scores, p2_scores);

	}
	printf("Goodbye!\n\n");
}

 /************************************************************
 * Function: gameplay_menu (void)						     *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Displays the main menu				         *
 * Input parameters: none									 *
 * Returns: none									         *
 * Preconditions: Start of program                           *
 * Postconditions: none									     *
 *************************************************************/
int gameplay_menu (void)
{
	int option = 0, play_game = 0;

	printf("************************************************ Welcome to Yahtzee! ************************************************\n\n");
	
	do
	{
		do
		{
			printf("Choose an option by entering the corresponding number:\n1. Print game rules\n2. Start a game of Yahtzee\n3. Exit\n");
			scanf("%d", &option);
		}
		while ((option != 1) && (option != 2) && (option != 3));

		switch (option)
		{
		case 1: //print game rules
			system("cls");
			printf("************************************************ Welcome to Yahtzee! ************************************************\n");
			
			printf("\nGame rules:\n\n");
			printf("The scorecard used for Yahtzee is composed of two sections. A upper section and a lower section. A total of\n");
			printf("thirteen boxes or thirteen scoring combinations are divided amongst the sections. The upper section consists\n");
			printf("of boxes that are scored by summing the value of the dice matching the faces of the box. If a player\n");
			printf("rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12. Once a player has\n");
			printf("chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\n");
			printf("If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are\n");
			printf("added to the players overall score as a bonus. The lower section contains a number of poker like combinations.\n\n");
			break;
		case 2: 
			play_game = 1;
			break;
		case 3:
			play_game = 0;
			break;
		default:
			printf("Enter a valid responce.\n");
		}
	}
	while ((option != 2) && (option != 3));
	system("cls");
	
	return play_game;
}

 /************************************************************
 * Function: roll_dice (int die[5], int size)			     *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Randomly rolls 5 die				         *
 * Input parameters: Die array and array size				 *
 * Returns: none									         *
 * Preconditions: Start of program                           *
 * Postconditions: updates die array					     *
 *************************************************************/
void roll_dice (int die[5], int size)
{
	char cont = 0;
	int index = 0;

	printf("Press any key to roll the dice.\n\n");
	system("pause > nul");
	

	for (index = 0; index < size; ++index)
	{			
		die[index] = rand() % 6 + 1;
	}

}

 /************************************************************
 * Function: print_die (int die[5], int size, int c_combos[13]
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Prints 5 dice in ascii				         *
 * Input parameters: die array, array size, and combo array	 *
 * Returns: none									         *
 * Preconditions: Start of program                           *
 * Postconditions: none									     *
 *************************************************************/
void print_die (int die[5], int size, int c_combos[13])
{
	int index = 0;
	int line = 1;

	// Prints 5 lines
	while (line <= 5)
	{
		// One line at a time
		switch (line)
		{	
		case 1:
			// Loops through each dice
			while(index<size)
			{
				switch(die[index])
				{
					case 1: 
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						printf("-----	");
						break;
						
				}
				index++;
			}
			printf("\n");
			line++;
			index = 0;
			break;
		case 2:
			while(index<size)
			{
				switch(die[index])
				{
					case 1: 
						printf("|   |	");
						break;	
					case 2:
						printf("|o  |	");
						break;
					case 3:
						printf("|o  |	");
						break;
					case 4:
						printf("|o o|	");
						break;
					case 5:
						printf("|o o|	");
						break;
					case 6:
						printf("|o o|	");
						break;
						
				}
				index++;
			}
			printf("\n");
			line++;
			index = 0;
			break;
		case 3:
			while(index<size)
			{
				switch(die[index])
				{
					case 1: 
						printf("| o |	");
						break;	
					case 2:
						printf("|   |	");
						break;
					case 3:
						printf("| o |	");
						break;
					case 4:
						printf("|   |	");
						break;
					case 5:
						printf("| o |	");
						break;
					case 6:
						printf("|o o|	");
						break;
						
				}
				index++;
			}
			printf("\n");
			line++;
			index = 0;
			break;
		case 4:
			while(index<size)
			{
				switch(die[index])
				{
					case 1: 
						printf("|   |	");
						break;	
					case 2:
						printf("|  o|	");
						break;
					case 3:
						printf("|  o|	");
						break;
					case 4:
						printf("|o o|	");
						break;
					case 5:
						printf("|o o|	");
						break;
					case 6:
						printf("|o o|	");
						break;
						
				}
				index++;
			}
			printf("\n");
			line++;
			index = 0;
			break;
		case 5:
			while(index<size)
			{
				switch(die[index])
				{
					case 1: 
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						printf("-----	");
						break;
						
				}
				index++;
			}
			printf("\n\n");
			line++;
			break;
		}
	}

	print_combos(c_combos);

}

 /************************************************************
 * Function: reroll (int die[5], int size, int c_combos[13], *
 *			 int player, int round)							 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Asks user for if/how many dice to reroll,    *
 *				then which ones, then updates array			 *
 * Input parameters: die array, array size, combo array	     *
 *					 player, and round						 *
 * Returns: none									         *
 * Preconditions: Start of program                           *
 * Postconditions: updates die array					     *
 *************************************************************/
void reroll (int die[5], int size, int c_combo[13], int player, int round)
{
	int number = 0;
	int index = 0;
	int reroll_index = 0;
	int die_reroll = 0;
	//int die_reroll[5] = {0};
	
	for (index = 0; index<2; index++)
	{
		do
		{
			printf("How many dice would you like to reroll? Or, enter 0 to use this roll. ");
			scanf("%d", &number);
	
		} while ((number!=1) && (number!=2) && (number!=3) && (number!=4) && (number!=5) && (number!=0));

		

		if (number != 0)
		{
			for (reroll_index = 0; reroll_index < number; reroll_index++)
			{
			
					do
					{
						printf("Enter a single die you would like to reroll: ");
						scanf("%d", &die_reroll);
						die[die_reroll-1] = rand() % 6 + 1;
					}
					while((die_reroll != 5) && (die_reroll != 1) && (die_reroll != 2) && (die_reroll != 3) && (die_reroll != 4));
			
			}
		}
		else
		{break;}
	system("cls");
	printf("************************************************** PLAYER %d ********************************************************\n", player);
	printf("************************************************** ROUND %d ********************************************************\n\n", round);
		
	print_die(die, 5,c_combo);
	}
}

 /************************************************************
 * Function: choose_combo (int die[5], int size,			 *
 *			 int c_combo[13], int scores[13],				 *
 *			 int player, int round)							 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Asks user to choose a combo, checks if used	 *
 * Input parameters: die array, array size, combo array	     *
 *					 player, and round						 *
 * Returns: none									         *
 * Preconditions: Start of program                           *
 * Postconditions: updates combo array					     *
 *************************************************************/
void choose_combo (int die[5], int size, int c_combo[13], int scores[13], int player, int round)
{
	int selection = 0, index = 0, is_combo_valid = 0;


	system("cls");
	printf("************************************************** PLAYER %d ********************************************************\n", player);
	printf("************************************************** ROUND %d ********************************************************\n\n", round);
	print_die(die, 5, c_combo);
	
	// Asks user for combination, repeat if combo has been used before
	do
	{
		printf("Enter the combination you would like to use: ");
		scanf("%d", &selection);

		switch(selection)
		{
		case 1:
			is_combo_valid = ones(die,c_combo,scores);
			break;
		case 2:
			is_combo_valid = twos(die,c_combo,scores);
			break;
		case 3:
			is_combo_valid = threes(die,c_combo,scores);
			break;
		case 4:
			is_combo_valid = fours(die,c_combo,scores);
			break;
		case 5:
			is_combo_valid = fives(die,c_combo,scores);
			break;
		case 6:
			is_combo_valid = sixes(die,c_combo,scores);
			break;
		case 7:
			is_combo_valid = three_of_a_kind(die,c_combo,scores);
			break;
		case 8:
			is_combo_valid = four_of_a_kind(die,c_combo, scores);
			break;
		case 9:
			is_combo_valid = full_house(die,c_combo, scores);
			break;
		case 10:
			is_combo_valid = sm_straight(die, c_combo, scores);
			break;
		case 11:
			is_combo_valid = lg_straight(die, c_combo, scores);
			break;
		case 12:
			is_combo_valid = yahtzee(die, c_combo, scores);
			break;
		case 13:
			is_combo_valid = chance(die, c_combo, scores);
			break;
		default:
			printf("Please enter a valid selection.\n\n");
			break;
		}

	}
	while(!is_combo_valid);

		

}

 /************************************************************
 * Function: print_combos (int c_combo[13])					 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: prints combo choices, with X if used    	 *
 * Input parameters: combo array							 *
 * Returns: none									         *
 * Preconditions: Start of program                           *
 * Postconditions:										     *
 *************************************************************/
void print_combos (int c_combo[13])
{
	// Prints all the combinations, or an X if it's been used
	if (c_combo[0] == 0)
	{printf ("1. Sum of 1s\n");}
	else {printf ("X. Sum of 1s\n");}

	if (c_combo[1] == 0)
	{printf ("2. Sum of 2s\n");}
	else {printf ("X. Sum of 2s\n");}

	if (c_combo[2] == 0)
	{printf ("3. Sum of 3s\n");}
	else {printf ("X. Sum of 3s\n");}

	if (c_combo[3] == 0)
	{printf ("4. Sum of 4s\n");}
	else {printf ("X. Sum of 4s\n");}

	if (c_combo[4] == 0)
	{printf ("5. Sum of 5s\n");}
	else {printf ("X. Sum of 5s\n");}

	if (c_combo[5] == 0)
	{printf ("6. Sum of 6s\n");}
	else {printf ("X. Sum of 6s\n");}

	if (c_combo[6] == 0)
	{printf ("7. Three of a kind\n");}
	else {printf ("X. Three of a kind\n");}

	if (c_combo[7] == 0)
	{printf ("8. Four of a kind\n");}
	else {printf ("X. Four of a kind\n");}

	if (c_combo[8] == 0)
	{printf ("9. Full house\n");}
	else {printf ("X. Full house\n");}

	if (c_combo[9] == 0)
	{printf ("10. Small Straight\n");}
	else {printf ("X. Small Straight\n");}

	if (c_combo[10] == 0)
	{printf ("11. Large Straight\n");}
	else {printf ("X. Large Straight\n");}

	// Can be used an unlimited amount of times
	printf ("12. YAHTZEE\n");

	if (c_combo[12] == 0)
	{printf ("13. Chance\n\n");}
	else {printf ("X. Chance\n\n");}
}

 /************************************************************
 * Function: print_score (int scores[13], int player)		 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: prints player score					    	 *
 * Input parameters: scores array, player					 *
 * Returns: none									         *
 * Preconditions: Start of program                           *
 * Postconditions:										     *
 *************************************************************/
void print_score (int scores[13], int player)
{
	int sum = 0, index = 0;
	for (index= 0; index<13; index++)
	{
		sum = scores[index] + sum;
	}
	printf("Player %d's score is now %d.\n", player, sum);
}

 /************************************************************
 * Function: ones (int die[5], int c_combo[13], int points[13])
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Adds sum of 1s, adds to scores array		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int ones (int die[5], int c_combo[13], int points[13])
{
	int index = 0, sum = 0, value = 0;

	if (c_combo[0] == 0)
	{
		c_combo[0] = 1;
		value = 1;
		for (index= 0; index<5; index++)
		{
			if(die[index] == 1)
			{sum = sum + 1;}
		}
		points[0] = sum;
	}
	return value;
}

 /************************************************************
 * Function: twos (int die[5], int c_combo[13], int points[13])
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Adds sum of 2s, adds to scores array		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int twos (int die[5], int c_combo[13], int points[13])
{
	int index = 0, sum = 0, value = 0;

	if (c_combo[1] == 0)
	{
		c_combo[1] = 1;
		value = 1;
		for (index= 0; index<5; index++)
		{
			if(die[index] == 2)
			{sum = sum + 1;}
		}
		points[1] = sum*2;
	}
	return value;
}

 /************************************************************
 * Function: threes (int die[5], int c_combo[13], int points[13])
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Adds sum of 3s, adds to scores array		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int threes (int die[5], int c_combo[13], int points[13])
{
	int index = 0, sum = 0, value = 0;

	if (c_combo[2] == 0)
	{
		c_combo[2] = 1;
		value = 1;
		for (index= 0; index<5; index++)
		{
			if(die[index] == 3)
			{sum = sum + 1;}
		}
		points[2] = sum*3;
	}
	return value;
}

 /************************************************************
 * Function: fours (int die[5], int c_combo[13], int points[13])
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Adds sum of 4s, adds to scores array		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int fours (int die[5], int c_combo[13], int points[13])
{
	int index = 0, sum = 0, value = 0;

	if (c_combo[3] == 0)
	{
		c_combo[3] = 1;
		value = 1;
		for (index= 0; index<5; index++)
		{
			if(die[index] == 4)
			{sum = sum + 1;}
		}
		points[3] = sum*4;
	}
	return value;
}

 /************************************************************
 * Function: fives (int die[5], int c_combo[13], int points[13])
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Adds sum of 5s, adds to scores array		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int fives (int die[5], int c_combo[13], int points[13])
{
	int index = 0, sum = 0, value = 0;

	if (c_combo[4] == 0)
	{
		c_combo[4] = 1;
		value = 1;
		for (index= 0; index<5; index++)
		{
			if(die[index] == 5)
			{sum = sum + 1;}
		}
		points[4] = sum*5;
	}
	return value;
}

 /************************************************************
 * Function: sixes (int die[5], int c_combo[13], int points[13])
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Adds sum of 6s, adds to scores array		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int sixes (int die[5], int c_combo[13], int points[13])
{
	int index = 0, sum = 0, value = 0;

	if (c_combo[5] == 0)
	{
		c_combo[5] = 1;
		value = 1;
		for (index= 0; index<5; index++)
		{
			if(die[index] == 6)
			{sum = sum + 1;}
		}
		points[5] = sum*6;
	}
	return value;
}

 /************************************************************
 * Function: three_of_a_kind (int die[5],					 *
 *		 	 int c_combo[13], int points[13])				 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Checks if 3OAK, then adds sum of die		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int three_of_a_kind (int die[5], int c_combo[13], int points[13])
{
	int number = 0, result = 0, sum = 0;

	// Checks if combo has been used before
	if (c_combo[6] == 0)
	{
		result = 1;
		c_combo[6] = 1; // Sets combo to used
		for (number = 1; number<7; number++)
		{
			sum = 0;

			if (die[0] == number)
			{sum = sum +1;}
			if (die[1] == number)
			{sum = sum +1;}
			if (die[2] == number)
			{sum = sum +1;}
			if (die[3] == number)
			{sum = sum +1;}
			if (die[4] == number)
			{sum = sum +1;}
			
			// Adds points if three of a kind
			if (sum>= 3)
			{
				points[6] = die [0] + die[1] + die[2] + die[3] + die[4];
				break;
			}		
		}
		
	}
	return result;
}

 /************************************************************
 * Function: four_of_a_kind (int die[5],					 *
 *		 	 int c_combo[13], int points[13])				 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Checks if 4OAK, then adds sum of die		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int four_of_a_kind (int die[5], int c_combo[13], int points[13])
{
	int number = 0, result = 0, sum = 0;

	// Check if combo has been used before
	if (c_combo[7] == 0)
	{
		c_combo[7] = 1; // Sets combo to used
		// Checks if a die matches a number, if it does then adds to a variable "sum". If sum = 3, then it breaks. Otherwise repeat with number+1. 
		for (number = 1; number>5; number++)
		{
			sum = 0;

			if (die[0] == number)
			{sum = sum +1;}
			if (die[1] == number)
			{sum = sum +1;}
			if (die[2] == number)
			{sum = sum +1;}
			if (die[3] == number)
			{sum = sum +1;}
			if (die[4] == number)
			{sum = sum +1;}

			if (sum>= 4)
			{
				points[7] = die [0] + die[1] + die[2] + die[3] + die[4];
				break;
			}
		}
		result = 1;
	}

	return result;
}

 /************************************************************
 * Function: full_house	 (int die[5],			    		 *
 *		 	 int c_combo[13], int points[13])				 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Checks if FH, then gives 25 points			 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int full_house (int die[5], int c_combo[13], int points[13])
{
	int number = 0, result = 0, sum1 = 0, sum2 = 0, three=0, two=0, number2 = 0;

	// Checks if combo has been used before
	if (c_combo[8] == 0)
	{
		c_combo[8] = 1; // Sets combo to used

		// Sets return value (if used or not) to 1
		result = 1;

		//Checks for a three of a kind
		for (number = 1; number<7; number++)
		{
			sum1 = 0;

			if (die[0] == number)
			{sum1 = sum1 +1;}
			if (die[1] == number)
			{sum1 = sum1 +1;}
			if (die[2] == number)
			{sum1 = sum1 +1;}
			if (die[3] == number)
			{sum1 = sum1 +1;}
			if (die[4] == number)
			{sum1 = sum1 +1;}
			
			if (sum1== 3)
			{
				break;
			}	
		}

		// Checks for a two of a kind
		for (number2 = 1; number2<7; number2++)
		{
			sum2 = 0;

			if (die[0] == number2)
			{sum2 = sum2 +1;}
			if (die[1] == number2)
			{sum2 = sum2 +1;}
			if (die[2] == number2)
			{sum2 = sum2 +1;}
			if (die[3] == number2)
			{sum2 = sum2 +1;}
			if (die[4] == number2)
			{sum2 = sum2 +1;}

			// If the two of the kind is the same number as three of a kind, ignore it
			if (number2 == number)
			{sum2 = 0;}
			
			if (sum2== 2)
			{
				if (sum2 + sum1 == 5)
				{points[8] = 25;} 
				break;
			}	
		}
	}
	return result;
	
}

 /************************************************************
 * Function: sm_straight	 (int die[5],			    	 *
 *		 	 int c_combo[13], int points[13])				 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Checks if sm straight, then gives 30 points	 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int sm_straight (int die[5], int c_combo[13], int points [13])
{
	int index = 0, temp = 0, passes = 0, sum=0, result=0;
	
	// Checks if combo has been used
	if (c_combo[9] == 0)
	{
		result = 1;
		
		c_combo[9] = 1;
		// Sort by ascending order (taken from Andy's code)
		for (passes = 1; passes < 5; passes++)
		{
			for (index = 0; index < 5 - passes; index++)
			{
				if (die[index] > die[index + 1])
					{// swap
					temp = die[index];
					die[index] = die[index+1];
					die[index+1] = temp;
				}
			}
		}
 
	// Check for small straight
	for (index = 4; index>0; index--)
		{
			if (die[index] == die[index -1] + 1)
			{sum++;}

		}

	// Give points
	if (sum>=3)
	{points[9] = 30;}
	}

	return result;
}

 /************************************************************
 * Function: lg_straight	 (int die[5],			    	 *
 *		 	 int c_combo[13], int points[13])				 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Checks if sm straight, then gives 40 points	 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int lg_straight (int die[5], int c_combo[13], int points [13])
{
	int index = 0, temp = 0, passes = 0, sum=0, result=0;
	
	// Checks if combo has been used
	if (c_combo[10] == 0)
	{
		result = 1;
		c_combo[10]=1;
		// Sort by ascending order (taken from Andy's code)
		for (passes = 1; passes < 5; passes++)
		{
			for (index = 0; index < 5 - passes; index++)
			{
				if (die[index] > die[index + 1])
					{// swap
					temp = die[index];
					die[index] = die[index+1];
					die[index+1] = temp;
				}
			}
		}
 
	// Check for small straight
	for (index = 4; index>0; index--)
		{
			if (die[index] == die[index -1] + 1)
			{sum++;}

		}

	// Give points
	if (sum>=4)
	{points[10] = 30;}
	}

	return result;
}

 /************************************************************
 * Function: lg_straight	 (int die[5],			    	 *
 *		 	 int c_combo[13], int points[13])				 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Checks if yahtzee, then gives 50 points		 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int yahtzee (int die[5], int c_combo[13], int points[13])
{
	int number = 0, result = 0, sum = 0;

	// Check if combo has been used before
	if (c_combo[11] == 0)
	{
		c_combo[11] = 1; // Sets combo to used
			
		for (number=0;number<5;number++)
		{	
			sum =0;
			
			if (die[0] == number)
			{sum = sum +1;}
			if (die[1] == number)
			{sum = sum +1;}
			if (die[2] == number)
			{sum = sum +1;}
			if (die[3] == number)
			{sum = sum +1;}
			if (die[4] == number)
			{sum = sum +1;}

			if (sum== 5)
			{
				points[11] = 50;
			}
		}
		result = 1;
	}

	return result;
}

 /************************************************************
 * Function: lg_straight	 (int die[5],			    	 *
 *		 	 int c_combo[13], int points[13])				 *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Adds up sum of all die as points			 *
 * Input parameters: die array, combo array, points array	 *
 * Returns: 1 if combo has been used, 0 if not			     *
 * Preconditions: Start of program                           *
 * Postconditions: updates points and combo arrays		     *
 *************************************************************/
int chance (int die[5], int c_combo[13], int points[13])
{
	int result = 0, sum =0;

	if (c_combo[12] == 0)
	{
		c_combo[12] = 1;
		result = 1;
		sum = die[0] + die[1] + die[2] + die[3] + die[4];
	
		points[12] = sum;
	}



	return result;
}

 /************************************************************
 * Function: end_game (int p1_points[13], int p2_points[13]) *
 * Date Created: 10/23/15                                    *
 * Date Last Modified: 10/23/15                              *
 * Description: Adds extra 35 points if applicable, shows winner
 * Input parameters: player 1 and 2 point arrays			 *
 * Returns:												     *
 * Preconditions: Start of program                           *
 * Postconditions:										     *
 *************************************************************/
void end_game (int p1_points[13], int p2_points[13])
{
	int sum1 = 0, sum2 = 0, winner = 0, index=0;

	printf("************************************************ GAME OVER ******************************************************\n");
	
	for (index = 0; index<5; index++)
	{
		sum1 = p1_points[index] + sum1;
	}
	for (index = 0; index<5; index++)
	{
		sum2 = p2_points[index] + sum2;
	}


	if ((p1_points[0]+p1_points[1]+p1_points[2]+p1_points[3]+p1_points[4]+p1_points[5])>63)
	{sum1 = sum1+35;}
	if ((p2_points[0]+p2_points[1]+p2_points[2]+p2_points[3]+p2_points[4]+p1_points[5])>63)
	{sum2 = sum2+35;}

	if (sum2>sum1)
	{
		winner=2;
	}

	if (sum1>sum2)
	{
		winner =1;
	}
	
	if (sum1 == sum2)
	{
		winner = -1;
	}

	switch (winner)
	{
	case 1:
		printf("\n\nPlayer 1 wins with %d points!\nPlayer 2 has %d points.\n\n", sum1, sum2);
		break;
	case 2:
		printf("\n\nPlayer 2 wins with %d points!\nPlayer 1 has %d points.\n\n", sum2, sum1);
		break;
	case -1:
		printf("It's a tie! Both players have %d points.\n\n", sum1);
		break;
	default:
		printf("Error");
	}

	system("pause");
	system("cls");

}


