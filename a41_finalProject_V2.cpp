#include <iostream>
#include <cstdlib>

using namespace std;

enum enPlayersStatus { playerWon = 1, machineWon = 2, draw = 3 };

enum enGameChoice { paper = 1, stone = 2, scissors = 3 };

struct strGameInfo {
    short playerWinningTimes{};
    short PCWinningTimes{};
    short drawTimes{};
    string finalWinner{""};
    enPlayersStatus playersStatus;
    enGameChoice playerChoice;
    enGameChoice machineChoice;
};

int readInRnage(int from, int to, string message, string warning) {
    int numOfRounds{};
    do {
        cout << endl << message << " : ";
        cin >> numOfRounds;
        if (numOfRounds < from || numOfRounds > to) {
            cout << endl << "\a" << warning;
        }
            
    } while (numOfRounds < from || numOfRounds > to);
    return numOfRounds;
}

int readRandomNumber(int from, int to) {
      return rand() % (to - from + 1) + from;
}

enGameChoice getChoice(int choice) {
    return (enGameChoice)choice;
}

string showGameChoice(enGameChoice gameChoice) {
    string choices[] = { "paper","stone","scissors" };
    return choices[gameChoice - 1];
}

enPlayersStatus getPlayersStatus(enGameChoice playerChoice, enGameChoice machineChoice) {
    // tie situation
    if (playerChoice == machineChoice)
        return enPlayersStatus::draw;

    // winning situation
    switch (playerChoice) {
    case enGameChoice::paper:
        if (machineChoice == enGameChoice::scissors) {
            return enPlayersStatus::machineWon;
        }
        break;
    case enGameChoice::stone:
        if (machineChoice == enGameChoice::paper) {
            return enPlayersStatus::machineWon;
        }
        break;
    case enGameChoice::scissors:
        if (machineChoice == enGameChoice::stone) {
            return enPlayersStatus::machineWon;
        }
        break;
    }

    // lost situation
    return enPlayersStatus::playerWon;
}

string whoWonTheRound(enGameChoice playerChoice, enGameChoice machineChoice) {
    string whoWon[] = {"Player", "Machine", "no winner"};
    return whoWon[getPlayersStatus(playerChoice, machineChoice) - 1];
}

void showRoundInfo(enGameChoice playerChoice, enGameChoice machineChoice) {
    cout << endl << "player choice: " << showGameChoice(playerChoice) << endl;
    cout << endl << "Machine choice: " << showGameChoice(machineChoice) << endl;
    cout << endl << "Round winner: " << whoWonTheRound(playerChoice, machineChoice) << endl;
}

void playARound(strGameInfo& gameInfo) {
    string message = "your choice: [1]- paper, [2]- stone, [3]- scissors";
    enGameChoice playerChoice = getChoice(readInRnage(1, 3, message, "Invalid input"));
    enGameChoice machineChoice = getChoice(readRandomNumber(1, 3));
    showRoundInfo(playerChoice, machineChoice);

    gameInfo.playerChoice = playerChoice;
    gameInfo.machineChoice = machineChoice;
    gameInfo.playersStatus = getPlayersStatus(playerChoice, machineChoice);
}

string finalWinner(strGameInfo gameInfo) {
    if (gameInfo.playerWinningTimes > gameInfo.PCWinningTimes)
        return "Player";
    else if (gameInfo.PCWinningTimes > gameInfo.playerWinningTimes)
        return "PC";
    else
        return "[no winner]";
}

void getScreenColor(enPlayersStatus playersStatus) {
    switch (playersStatus) {
    case enPlayersStatus::machineWon:
        system("Color 4F");
        cout << "\a";
        break;
    case enPlayersStatus::playerWon:
        system("Color 2F");
        break;
    default:
        system("Color 6F");
        break;
    }
}

void roundEndResult(strGameInfo& gameInfo) {

    getScreenColor(gameInfo.playersStatus);

    switch (gameInfo.playersStatus) {
    case enPlayersStatus::machineWon:
        gameInfo.PCWinningTimes++;
        break;
    case enPlayersStatus::playerWon:
        gameInfo.playerWinningTimes++;
        break;
    default:
        gameInfo.drawTimes++;
    }
    gameInfo.finalWinner = finalWinner(gameInfo);
}

string repearString(string str, int numOfRepeatition) {
    string key{""};
    for (int number = 0; number < numOfRepeatition; number++)
        key += str;
    return key;
}

void gameOverScreen() {
    cout << '\n' << repearString("\t",4) << repearString("_", 60) << '\n';
    cout << '\n' << repearString("\t", 5) << "+++ Game Over +++\n";
    cout << '\n' << repearString("\t", 4) << repearString("_", 60) << '\n';
}

void showRoundsSummary(strGameInfo gameInfo) {
    gameOverScreen();
    cout << endl << repearString("\t",5) << "Player won: " << gameInfo.playerWinningTimes << " time(s)\n";
    cout  << repearString("\t", 5) << "PC won: " << gameInfo.PCWinningTimes << " time(s)\n";
    cout  << repearString("\t", 5) << "draw happened: " << gameInfo.drawTimes << " time(s)\n";
    cout << repearString("\t", 5) << "final winner: " << gameInfo.finalWinner << endl;
}

void resetScreen() {
    system("cls");
    system("color 0F");
}

void resetGame(strGameInfo& gameInfo) {
    gameInfo.drawTimes = 0;
    gameInfo.PCWinningTimes = 0;
    gameInfo.playerWinningTimes = 0;
    resetScreen();
}

bool doesPlayAgain() {
    char ans;
    cout << '\n' << repearString("\t",4) << "Do you want to play again ? (y - n) : ";
    cin >> ans;

    if (ans == 'Y' || ans == 'y')
        return true;

    return false;
}

void playMultipleRounds() {
    strGameInfo gameInfo;
    bool playAgain{};
    int numOfRounds{};
    do {
        numOfRounds = readInRnage(1, 10, "How many rounds do you want to play? (1-10)", "Invalid input");
        for (int round = 0; round < numOfRounds; round++) {
            playARound(gameInfo);
            roundEndResult(gameInfo);
        }
        showRoundsSummary(gameInfo);

        playAgain = doesPlayAgain();

        if (playAgain)
            resetGame(gameInfo);
            

    } while (playAgain);
}

int main()
{
    srand((unsigned)time(NULL));
    
    playMultipleRounds();

}
