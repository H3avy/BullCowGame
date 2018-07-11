/* This is the console executable, that makes use of the BullCow class. 
This acts as the view in a MVC pattern, and is responsible for all user interaction. 
For game logic see FBullCowGame class.
*/


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <Windows.h>
#include "FBullCowGame.h"

using FText = FString;
using int32 = int;

//Function declarations

void intro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void TypeWriter(const FText, unsigned int);

//instantiate a new game
FBullCowGame BCGame;

int main()
{
	bool bPlayAgain = false;
	do 
	{
		intro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}

//Functions
void intro()
{
	//Short intro to the Game
	FText intro1 = "Welcome to Bulls and Cows, a fun Word game. \nCan you guess the ";
	FText intro2 = " letter isogram I'm thinking of?\n\n";
	FText Logo[3] = { " ____    _    _   _        _         _____                                _____    ____   __          __   _____  \n"
				      "|  _ \\  | |  | | | |      | |       / ____|                              / ____|  / __ \\  \\ \\        / /  / ____| \n"
				      "| |_) | | |  | | | |      | |      | (___                               | |      | |  | |  \\ \\  /\\  / /  | (___   \n",
				      "|  _ <  | |  | | | |      | |       \\___ \\                        _     | |      | |  | |   \\ \\/  \\/ /    \\___ \\  \n"
				      "| |_) | | |__| | | |____  | |____   ____) |                      | |    | |____  | |__| |    \\  /\\  /     ____) | \n"
				      "|____/   \\____/  |______| |______| |_____/     __ _   _ __     __| |     \\_____|  \\____/      \\/  \\/     |_____/  \n",
				      "                                              / _` | | '_ \\   / _` |                                              \n"
				      "                                             | (_| | | | | | | (_| |                                              \n "
				      "                                             \\__,_| |_| |_|  \\__,_|                                              \n"
		              "                                                                                                                  \n\n" };
	//get Handle for console maipulation
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//wait xxxx milliseconds before outputting the Intro, used for Videocapturing to position screen.
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	SetConsoleTextAttribute(hConsole, 4); // 4 sets cosnole Text to red
	for (auto line : Logo)
	{
		TypeWriter(line, 1);
	}
	
	SetConsoleTextAttribute(hConsole, 7); // 7 sets console Text back to white
	TypeWriter(intro1, 30);
	std::cout << BCGame.GetHiddenWordLength();
	TypeWriter(intro2, 30);
	return;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{		
		FText Guess = GetValidGuess();
		// Submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop til the user inputs a valid guess!
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		//get the guess from Player
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	
		getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your word in lowercase.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //Keep looping until we get no error.
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with another hidden word? (Y/N)";
	FText Response = "";
	getline(std::cin, Response);

	std::cout << std::endl;
	//Return true if answer == Y || y
	if (tolower(Response[0]) == 'y')
	{
		BCGame.Reset();
	}
	return (tolower(Response[0]) == 'y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())	{ std::cout << "WELL DONE - YOU WIN !\n"; }
	else { std::cout << "Better luck next time! \n"; }
}

void TypeWriter(const FText intro, unsigned int MilisecondsPerChar)
{
	for (const auto c : intro)
	{
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(MilisecondsPerChar));
	}
}

