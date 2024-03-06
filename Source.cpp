#include <iostream> 
using namespace std;

enum enChoice { Stone = 1, Paper, Scissor };

string enChoiceString(enChoice String)
{
    switch (String)
    {
    case enChoice::Stone:
        return "Stone";
    case enChoice::Paper:
        return "Paper";
    case enChoice::Scissor:
        return "Scissor";
    }
    return "";
}

int ReadNumberInRange(int i = INT_MIN, int y = INT_MAX, string message = "Enter the number")
{
    int temp;

    cout << message;
    cin >> temp;

    while (temp < i || temp >y)
    {
        cout << "Please enter a valid number ?\n";
        cin >> temp;
    }

    return temp;
}

int RandomNumberInRange(int From, int To)//Fn to generate a random number
{
    return (From < To) ? (rand() % (To - From + 1) + From) : (rand() % (From - To + 1) + To);
}

void RoundCycle(int RoundNumber, int& DrawCount, int& ComputerCount, int& UserCount, int& difficulty)
{
    cout << "\nRound [" << RoundNumber << "] begins:\n";
    
    enChoice UserChoice = (enChoice)ReadNumberInRange(1, 3, "Your Choice : [1]Stone, [2]Paper, [3]Scissor?\n");
    enChoice ComputerChoice = (enChoice)RandomNumberInRange(1, 3);
    
    if (difficulty == 1 and (RoundNumber & 1) and (UserChoice != ComputerChoice))
    {
        if ((UserChoice == enChoice::Stone and ComputerChoice == enChoice::Paper)
            or (UserChoice == enChoice::Paper and ComputerChoice == enChoice::Scissor)
            or (UserChoice == enChoice::Scissor and ComputerChoice == enChoice::Stone))
            ComputerChoice = (enChoice)RandomNumberInRange(1, 3);
    }
    else if (difficulty == 3 and (RoundNumber & 1) and (UserChoice != ComputerChoice))
    {
        if ((UserChoice == enChoice::Paper and ComputerChoice == enChoice::Stone)
            or (UserChoice == enChoice::Scissor and ComputerChoice == enChoice::Paper)
            or (UserChoice == enChoice::Stone and ComputerChoice == enChoice::Scissor))
            ComputerChoice = (enChoice)RandomNumberInRange(1, 3);
    }
    
    cout << "__________Round [" << RoundNumber << "] __________\n";
    if (UserChoice == ComputerChoice)
    {
        string BothChoice = enChoiceString(UserChoice);

        system("color E");
        cout << "Player Choice\t : " << BothChoice <<
            "\nComputer Choice\t : " << BothChoice <<
            "\nRound Winner\t : [No Winner]";

        DrawCount++;
    }
    else if ((UserChoice == enChoice::Stone && ComputerChoice == enChoice::Paper) ||
        (UserChoice == enChoice::Scissor && ComputerChoice == enChoice::Stone) ||
        (UserChoice == enChoice::Paper && ComputerChoice == enChoice::Scissor))
    {

        system("color F4");
        cout << "\a";
        cout << "Player Choice\t : " << enChoiceString(UserChoice) <<
            "\nComputer Choice\t : " << enChoiceString(ComputerChoice) <<
            "\nRound Winner\t : Computer";

        ComputerCount++;
    }
    else if ((UserChoice == enChoice::Paper && ComputerChoice == enChoice::Stone) ||
        (UserChoice == enChoice::Stone && ComputerChoice == enChoice::Scissor) ||
        (UserChoice == enChoice::Scissor && ComputerChoice == enChoice::Paper))
    {
        system("color F2");
        cout << "Player Choice\t : " << enChoiceString(UserChoice) <<
            "\nComputer Choice\t : " << enChoiceString(ComputerChoice) <<
            "\nRound Winner\t : Player";

        UserCount++;
    }
    cout << "\n_____________________________________\n";
}

void GameResultsHeader()
{
    cout << "\t_______________________________________________________________\t\t\n";
    cout << "\t\t\t+++ G a m e  O v e r +++\t\t\t\t\n";
    cout << "\t_______________________________________________________________\t\t\n";

    cout << "\t________________________[Game Results  ]_______________________\t\t\n";
}

void GameResult(int Rounds, int DrawCount, int ComputerCount, int UserCount)
{


    cout << "\tGame rounds \t\t:\t" << Rounds << endl;
    cout << "\tPlayer won times \t:\t" << UserCount << endl;
    cout << "\tComputer won times \t:\t" << ComputerCount << endl;
    cout << "\tDraw times \t\t:\t" << DrawCount << endl;

    cout << "\tFinal Winner \t\t:";
    if (UserCount == ComputerCount)
    {
        system("color E");
        cout << "\tNo Winner\n";
    }
    else if (UserCount > ComputerCount)
    {
        system("color F2");
        cout << "\tThe Player\n";
    }
    else
    {
        system("color F4");
        cout << "\tThe Computer\n";
    }
}

int main()
{
    //Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));//if you put it in other Fn it will return the same value

    char Continue;
    do
    {
        system("color 2");
        system("cls");
        int Rounds = ReadNumberInRange(1, 10, "How many Rounds ? (1 --> 10)\n");

        cout << "Choose the level of difficulty : \n[1] Easy\n[2] Medium\n[3] Hard\n";
        int difficulty = ReadNumberInRange(1, 3, "");
        int DrawCount = 0, ComputerCount = 0, UserCount = 0;

        for (int RoundNumber = 1; RoundNumber <= Rounds; RoundNumber++)
            RoundCycle(RoundNumber, DrawCount, ComputerCount, UserCount, difficulty);

        GameResultsHeader();

        GameResult(Rounds, DrawCount, ComputerCount, UserCount);

        cout << "\t_______________________________________________________________\t\t\n";

        cout << "\tDo you want play again ? (Y / N)\n";
        cin >> Continue;
    } while (Continue == 'y' || Continue == 'Y');


    system("cls");
    cout << "The Game Ended ! :)\n";
    return 0;
}