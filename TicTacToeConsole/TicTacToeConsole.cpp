// TicTacToeConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool gameOver(std::vector<std::vector<std::string>>& ticTacToe, std::string &tokenType, const int &boardVecSize);

int main()
{
	enum class GameState { IDLE, GAME_END, VALIDATE_INPUT, QUIT };
	GameState gameState = GameState::IDLE;

	while (gameState != GameState::QUIT)
	{
		gameState = GameState::IDLE;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		const int colorDefault = 7;
		const int colorXs = 6;
		const int colorOs = 3;

		enum class TurnState { PLAY_Xs, PLAY_Os };
		TurnState turnState = TurnState::PLAY_Xs;

		std::string blank = "| |";
		std::string tokenX = "|X|";
		std::string tokenO = "|O|";

		// Set initial values of TicTacToe board and print it to the console.
		std::vector<std::vector<std::string>> ticTacToe{ { blank, blank, blank },{ blank, blank, blank },{ blank, blank, blank } };
		std::vector<int> positions{ 1,2,3,1,2,3,1,2,3 };
		std::vector<char> rowIds{ 'a','b','c' };
		const int boardVecSize = 3;
		int count = 0;
		for (int row = 0; row < boardVecSize; row++)
		{
			std::cout << rowIds[row] << " ";
			for (int col = 0; col < boardVecSize; col++)
			{
				ticTacToe[row][col] = ('|' + std::to_string(positions[count]) + '|');
				std::cout << ticTacToe[row][col];
				count++;
			}
			std::cout << std::endl;
		}

		// Loop getting user input until game end condition is met.
		while (gameState != GameState::GAME_END)
		{
			// Loop getting user input for turn until valid input is entered.
			gameState = GameState::VALIDATE_INPUT;
			while (gameState == GameState::VALIDATE_INPUT)
			{
				// Print unique turn info depending on whose turn it is, so that it's clear to players.
				if (turnState == TurnState::PLAY_Xs)
				{
					SetConsoleTextAttribute(hConsole, colorXs);
					std::cout << "It is X's turn." << std::endl;
					SetConsoleTextAttribute(hConsole, colorDefault);
				}
				else if (turnState == TurnState::PLAY_Os)
				{
					SetConsoleTextAttribute(hConsole, colorOs);
					std::cout << "It is O's turn." << std::endl;
					SetConsoleTextAttribute(hConsole, colorDefault);
				}

				// Get input and validate it for errors.
				int moveChoiceRow;
				int moveChoiceCol;
				std::string userInputStr;
				std::getline(std::cin, userInputStr);

				if (userInputStr.length() == 2 &&
					userInputStr.find_first_of("abc") != std::string::npos &&
					userInputStr.find_first_of("123") != std::string::npos)
				{
					// Set input as readable array numbers.
					if (userInputStr.find("a") != std::string::npos)
					{
						moveChoiceRow = 1;
					}
					else if (userInputStr.find("b") != std::string::npos)
					{
						moveChoiceRow = 2;
					}
					else if (userInputStr.find("c") != std::string::npos)
					{
						moveChoiceRow = 3;
					}

					if (userInputStr.find("1") != std::string::npos)
					{
						moveChoiceCol = 1;
					}
					else if (userInputStr.find("2") != std::string::npos)
					{
						moveChoiceCol = 2;
					}
					else if (userInputStr.find("3") != std::string::npos)
					{
						moveChoiceCol = 3;
					}

					// Place X or O token on board if the chosen square isn't occupied.
					if (turnState == TurnState::PLAY_Xs)
					{
						if (ticTacToe[moveChoiceRow - 1][moveChoiceCol - 1] == tokenX ||
							ticTacToe[moveChoiceRow - 1][moveChoiceCol - 1] == tokenO)
						{
							std::cout << "That square is already occupied. Try another one." << std::endl;
							std::cout << std::endl;
						}
						else
						{
							ticTacToe[moveChoiceRow - 1][moveChoiceCol - 1] = tokenX;
							gameState = GameState::IDLE;
						}
					}
					else if (turnState == TurnState::PLAY_Os)
					{
						if (ticTacToe[moveChoiceRow - 1][moveChoiceCol - 1] == tokenX ||
							ticTacToe[moveChoiceRow - 1][moveChoiceCol - 1] == tokenO)
						{
							std::cout << "That square is already occupied. Try another one." << std::endl;
							std::cout << std::endl;
						}
						else
						{
							ticTacToe[moveChoiceRow - 1][moveChoiceCol - 1] = tokenO;
							gameState = GameState::IDLE;
						}
					}
				}
				else
				{
					// Something was invalid. Repeat the loop, asking for input again.
					std::cout << "That is not a valid option. Options are (examples): a1, b3, c2" << std::endl;
					std::cout << std::endl;
				}

				// Reprint ticTacToe board.
				for (int row = 0; row < boardVecSize; row++)
				{
					std::cout << rowIds[row] << " ";
					for (int col = 0; col < boardVecSize; col++)
					{
						if (ticTacToe[row][col] == tokenX)
						{
							SetConsoleTextAttribute(hConsole, colorXs);
							std::cout << ticTacToe[row][col];
							SetConsoleTextAttribute(hConsole, colorDefault);
						}
						else if (ticTacToe[row][col] == tokenO)
						{
							SetConsoleTextAttribute(hConsole, colorOs);
							std::cout << ticTacToe[row][col];
							SetConsoleTextAttribute(hConsole, colorDefault);
						}
						else
						{
							std::cout << ticTacToe[row][col];
						}
					}
					std::cout << std::endl;
				}
			}

			// Current turn is complete, so switch to other player.
			if (turnState == TurnState::PLAY_Xs)
			{
				turnState = TurnState::PLAY_Os;
			}
			else if (turnState == TurnState::PLAY_Os)
			{
				turnState = TurnState::PLAY_Xs;
			}

			// Check if win condition is met.
			if (gameOver(ticTacToe, tokenX, boardVecSize))
			{
				gameState = GameState::GAME_END;
				std::cout << "Xs won!" << std::endl;
			}
			else if (gameOver(ticTacToe, tokenO, boardVecSize))
			{
				gameState = GameState::GAME_END;
				std::cout << "Os won!" << std::endl;
			}
		}

		// See if user wants to play again or quit.
		std::string resetChoice = " ";
		while (resetChoice != "y" && resetChoice != "n")
		{
			std::cout << "Game Over" << std::endl;
			std::cout << "Play again?" << std::endl;
			std::cout << "[y][n]" << std::endl;
			std::getline(std::cin, resetChoice);
			if (resetChoice == "y")
			{
				std::cout << "Resetting game..." << std::endl;
			}
			else if (resetChoice == "n")
			{
				gameState = GameState::QUIT;
				std::cout << "Thanks for playing!" << std::endl;
			}
		}
	}

	std::cin.ignore();
	std::cin.get();
	return 0;
}

bool gameOver(std::vector<std::vector<std::string>>& ticTacToe, std::string &tokenType, const int &boardVecSize)
{
	// Horizontal/Vertical win condition check.
	int acrossCount = 0;
	std::vector<int> downCount{ 0,0,0 };
	for (int row = 0; row < boardVecSize; row++)
	{
		for (int col = 0; col < boardVecSize; col++)
		{
			if (ticTacToe[row][col] == tokenType)
			{
				downCount[col]++;
				acrossCount++;
				if (acrossCount == 3 || downCount[col] == 3)
				{
					return true;
				}
			}
		}
		acrossCount = 0;
	}

	// Diagonal win condition check.
	if (ticTacToe[0][0] == tokenType &&
		ticTacToe[1][1] == tokenType &&
		ticTacToe[2][2] == tokenType)
	{
		return true;
	}
	else if (ticTacToe[0][2] == tokenType &&
		ticTacToe[1][1] == tokenType &&
		ticTacToe[2][0] == tokenType)
	{
		return true;
	}

	return false;
}