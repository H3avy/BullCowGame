#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	std::vector<FString> WordList();
	bool IsDifficultySet() const;

	void Reset(); 
	
	// counts bulls and cows, and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	FString Difficulty;
	bool bGameIsWon;
	bool bDifficultySet;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	
	FString ToLowercase(FString);
	FString SetHiddenWord(std::vector<FString>);
};