#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

enum enChoises { Stone = 1, Paper = 2, Scessors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enChoises PlayerChoise;
	enChoises ComputerChoise;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults
{
	short GameRound = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string WinnerName = "";
};

enChoises ReadPlayerChoise()
{
	short Choise = 1;

	do
	{
		cout << "What Is Your Choise [1]:Stone , [2]:Paper , [3]:Scissor ? ";
		cin >> Choise;
	} while (Choise <= 0 || Choise > 3);

	return enChoises(Choise);
}

int RandomNumber(int From, int To)
{
	int RandNumber = rand() % (To - From + 1) + From;

	return RandNumber;
}

enChoises GetComputerChoise()
{
	return enChoises(RandomNumber(1, 3));
}

string ChoiseName(enChoises Choise)
{
	string ArrChoises[3] = { "Stone", "Paper", "Scissors" };

	return ArrChoises[Choise - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoise == RoundInfo.ComputerChoise)
		return enWinner::Draw;

	switch (RoundInfo.PlayerChoise)
	{
	case enChoises::Stone:
		if (RoundInfo.ComputerChoise == enChoises::Paper)
			return enWinner::Computer;
		break;
	case enChoises::Scessors:
		if (RoundInfo.ComputerChoise == enChoises::Stone)
			return enWinner::Computer;
		break;
	case enChoises::Paper:
		if (RoundInfo.ComputerChoise == enChoises::Scessors)
			return enWinner::Computer;
		break;
	}

	return enWinner::Player;
}

string WinnerName(enWinner Winner)
{
	string ArrWinner[3] = { "Player", "Computer", "No Winner" };

	return ArrWinner[Winner - 1];
}

string Tabs(short NumberOfTabs)
{
	string t = "";

	for (int i = 1; i <= NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}

	return t;
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case Player:
		system("color 2F");
		break;
	case Computer:
		system("color 4F");
		cout << "\a";
		break;
	case Draw:
		system("color 6F");
		break;
	}
}

void GameOverScreen()
{
	cout << Tabs(2) << "----------------------------------------------------------\n\n";
	cout << Tabs(2) << "                      +++ Game Over +++\n\n";
	cout << Tabs(2) << "----------------------------------------------------------\n\n";
}

short ReadHowManyRounds()
{
	short HowManyRounds = 1;

	do
	{
		cout << "How Many Rounds From 1 To 10 ? ";
		cin >> HowManyRounds;
	} while (HowManyRounds <= 0 || HowManyRounds > 10);

	return HowManyRounds;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n-------------Round [" << RoundInfo.RoundNumber << "]---------------\n\n";
	cout << "Player Choise        : " << ChoiseName(RoundInfo.PlayerChoise) << endl;
	cout << "Computer Choise      : " << ChoiseName(RoundInfo.ComputerChoise) << endl;
	cout << "Round Winner         : " << RoundInfo.WinnerName << endl;
	cout << "------------------------------------------------------\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (ComputerWinTimes > PlayerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillFinalResults(short HowManyRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRound = HowManyRounds;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.Winner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(WhoWonTheGame(PlayerWinTimes, ComputerWinTimes));

	return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		RoundInfo.RoundNumber++;
		cout << "\nRound [" << GameRound << "] Begins : \n";
		RoundInfo.PlayerChoise = ReadPlayerChoise();
		RoundInfo.ComputerChoise = GetComputerChoise();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return FillFinalResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void ShowFinalResults(stGameResults GameResults)
{
	cout << Tabs(2) << "----------------------[ Game Results ]---------------------\n\n";
	cout << Tabs(2) << "Game Rounds            : " << GameResults.GameRound << endl;
	cout << Tabs(2) << "Player Won Times       : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer Won Times     : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times             : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner           : " << GameResults.WinnerName << endl;

	cout << Tabs(2) << "-----------------------------------------------------------------\n";

	SetWinnerScreenColor(GameResults.Winner);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		GameOverScreen();
		ShowFinalResults(GameResults);

		cout << endl << Tabs(3) << "Do You Want To Play Again Y/N ? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}