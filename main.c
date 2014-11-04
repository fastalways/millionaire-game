#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>

#include <ctime>


using namespace std;


/**********************************************************************
 *  clean stdin(linux) = fflush(unix)
 *
 **********************************************************************/
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

class player
{
public:
	string name;

};

class colorPrint
{
public:
	string red,cyan,green,blue,black,brown,magenta,gray,none;
	colorPrint(void)
	{

		/*cyan = "\033[1;36m";*/       
		/*black = "\033[0;30m";*/
		/*gray = "\033[0;37m";*/
	 
		red  = "\033[0;31m";        /* 0 -> normal ;  31 -> red */
		green = "\033[0;32m";        /* 4 -> underline ;  32 -> green */
		blue = "\033[0;34m";        /* 9 -> strike ;  34 -> blue */
		brown = "\033[0;33m";
		magenta = "\033[0;35m";
	 
		none  = "\033[0m";        /* to flush the previous property */

	}


	void cPrint(string msg,string color)
	{
	
		if(color=="red") color = red;
		/*else if(color=="cyan") color = cyan;*/
		else if(color=="green") color = green;
		else if(color=="blue") color = blue;
		/*else if(color=="black") color = black;*/
		else if(color=="brown") color = brown;
		else if(color=="magenta") color = magenta;
		/*else if(color=="gray") color = gray;*/
		else color = none;
		cout<<color<<msg<<none;
	}
};


/**********************************************************************
 *  ConvertTo String function
 *
 **********************************************************************/
string intToStr(int num)
{
	ostringstream convert;   
	convert << num;      
	return convert.str(); 
}
string floatToStr(float num)
{
	ostringstream convert;   
	convert << num;      
	return convert.str(); 
}
string charToStr(char num)
{
	ostringstream convert;   
	convert << num;      
	return convert.str(); 
}


/* Declare Global Variable */
	colorPrint cPrint;
	vector<player> players;
/*-------------------------*/

class coreGame
{
public:
		
	int randTurn;
	int num1,num2;
	char highlowValue;

	coreGame()
	{
		randTurn = 0;
	}

	int highlow(vector<player> players)
	{
		srand(time(0));
		int playerWin;
		while(true)
		{
			/*system("clear");*/
			clean_stdin();
			cout << "\nPlayer " << randTurn+1 << " :" << players[randTurn].name << " select h(high) or l(low) or e(equal) : ";
			char a;
			a = getchar();
			if(a=='h'||a=='l'||a=='e')
			{
				highlowValue = a;
				break;
			}
		}
		for(int i=0;i<30;i++)
		{
			num1 = rand() % 11;
			num2 = rand() % 11;
			cout << num1 << " " << num2 << endl;
			usleep((i+1)*10000);
		}
		/* Show result & return Hilow Winner */

		/*cout << "\nPlayer " << randTurn+1 << " :" << players[randTurn].name << " select ";
		if(highlowValue=='l')cout<<"low"; else if(highlowValue=='h') cout<<"high"; else cout<<"equal";*/

		if(num1 == num2 && highlowValue == 'e')
		{
			cPrint.cPrint("\nPlayer " + intToStr( randTurn+1 ) + " :" + players[randTurn].name + " won highlow!","red");
			playerWin = randTurn;
		}
		else if(num1 < num2 && highlowValue == 'l')
		{
			cPrint.cPrint("\nPlayer " + intToStr( randTurn+1 ) + " :" + players[randTurn].name + " won highlow!","red");
			playerWin = randTurn;
		}
		else if(num1 > num2 && highlowValue == 'h')
		{
			cPrint.cPrint("\nPlayer " + intToStr( randTurn+1 ) + " :" + players[randTurn].name + " won highlow!","red");
			playerWin = randTurn;
		}
		else
		{
			cPrint.cPrint("\nPlayer " + intToStr( randTurn+1 ) + " :" + players[randTurn].name + " lose highlow!","red");
			if(randTurn == 0) playerWin = 1;
			else playerWin = 0;
			
		}

		if(randTurn == 0) randTurn = 1;
		else randTurn = 0;

		return playerWin;

		
	}
	
};



/**********************************************************************
 *  Welcome Function
 *
 **********************************************************************/

 void welcome()
 {
 	cPrint.cPrint("\n\t\tWelcome To Millionaire Game\n\t\tThis is v0.1 -> 2player","blue");
 	cout << "\n\tEnter player 1 name:"; cin >> players[0].name;
 	cout << "\n\tEnter player 2 name:"; cin >> players[1].name;
 	cout << "\n\tWelcome " << players[0].name<< " & " << players[1].name << ", Enter to play game....";
 	clean_stdin();
 }

int main(int argc, char* argv[])
{
	system("clear");
	player addPlayer;
	players.push_back(addPlayer);	/* Add player 1 */
	players.push_back(addPlayer);	/* Add player 2 */
	welcome();
	coreGame game;
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	game.highlow(players);
	getchar();
	return 0;
}