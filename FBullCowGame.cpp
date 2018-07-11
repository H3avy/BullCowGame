#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
bool FBullCowGame::IsDifficultySet() const { return bDifficultySet; }


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;
	const FString HIDDEN_WORD = SetHiddenWord(WordList());
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	bDifficultySet = false;
	
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}



//receives a VALID guess, incriments try, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		// compare letters against the Guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (MyHiddenWord[GChar] == Guess[MHWChar]) 
			{
				if (MHWChar == GChar) // incriment bulls if they are in the same place
				{
					BullCowCount.Bulls++;
				}
				else // incriment cows if not
				{
					BullCowCount.Cows++; 
				}
			}				
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true;  }

	// setup our map
	TMap <char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])	{ return false; }
		else { LetterSeen[Letter] = true; }
	}
	return true; 
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false;	}
	}
	return true;
}



FString FBullCowGame::ToLowercase(FString Word)
{
	FString TempWord = "";
	int WordLength = Word.length();
	for (int count = 0; count < WordLength; count++)
	{
		TempWord += tolower(Word[count]);
	}
	return TempWord;
}

FString FBullCowGame::SetHiddenWord(std::vector<FString> WordList)
{
	FString HiddenWord = "";
	HiddenWord = WordList[10];
	return HiddenWord;
}

std::vector<FString> FBullCowGame::WordList()
{
	std::vector<FString> WordList;
	if (!FBullCowGame::IsDifficultySet())
	{
		bDifficultySet = true;
		FString Difficulty = "";
		std::cout << "Please select your difficultylevel!\n" << "EASY" << "\tMEDIUM" << "\tHARD" << "\tVERY HARD" << std::endl;
		std::cout << "Please enter your difficulty: " << std::endl;
		getline(std::cin, Difficulty);
		Difficulty = ToLowercase(Difficulty);
		FString Word = "";
		std::ifstream easy("EasyDifficulty.txt");
		std::ifstream medium("MediumDifficulty.txt");
		std::ifstream hard("HardDifficulty.txt");
		std::ifstream veryhard("VeryHardDifficulty.txt");
		//TODO convert to switch!
		if (Difficulty == "easy")
		{
			if (easy.is_open())
			{
				std::cout << "Loading" << std::endl;
				while (getline(easy, Word))
				{
					Word = ToLowercase(Word);
					WordList.push_back(Word);
					Word = "";
				}
			}
		}
		else if (Difficulty == "medium")
		{
			if (medium.is_open())
			{
				std::cout << "Loading" << std::endl;
				while (getline(medium, Word))
				{
					Word = ToLowercase(Word);
					WordList.push_back(Word);
					Word = "";
				}
			}
		}
		else if (Difficulty == "hard")
		{
			if (hard.is_open())
			{
				std::cout << "Loading" << std::endl;
				while (getline(hard, Word))
				{
					Word = ToLowercase(Word);
					WordList.push_back(Word);
					Word = "";
				}
			}
		}
		else if (Difficulty == "very hard")
		{
			if (veryhard.is_open())
			{
				std::cout << "Loading" << std::endl;
				while (getline(veryhard, Word))
				{
					Word = ToLowercase(Word);
					WordList.push_back(Word);
					Word = "";
				}
			}
		}
		
		return WordList;
	}
	else
	{
		return WordList;
	}

	
}
