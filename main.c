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
	int coins;
	class pitem
	{
	public:
		uint id;
		uint amount;
		pitem(uint uintid, uint uintamount=1)
		{
			id=uintid;amount=uintamount;
		}
	};
	class itemsClass
	{
	public:
		vector<pitem> item;
		int add(uint uintid, uint uintamount=1)
		{
			/*check already*/
			bool already=false;
			for(uint i=0;i<item.size();i++)
			{
				if(uintid==item[i].id)
				{
					item[i].amount+=uintamount;
					already=true;
					break;
				}
			}
			/*new slot*/
			if(!already)
			{
				item.push_back(pitem(uintid,uintamount));
			}
			return 0;
		}
		int del(uint uintid, uint uintamount=1)
		{
			/*check already*/
			bool already=false;
			for(uint i=0;i<item.size();i++)
			{
				if(uintid==item[i].id)
				{
					if(uintamount<=item[i].amount)
					{
						item[i].amount-=uintamount;
						already=true;
						if(item[i].amount<=0)
						{
							item.erase(item.begin()+i);
						}
					}
					else
					{ return -1; }

					break;
				}
			}
			if(!already)
			{
				return -1;
			}
			return 0;
		}
	};
	itemsClass box;
	
	player()
	{
		coins=20000000;
	}

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
	int winner;
	int num1,num2;
	vector <uint> player1Choose;
	vector <uint> player2Choose;
	char highlowValue;
	int prob;

	class item
	{
	public:
		string name;
		string type;
		int value;
		int minProb;
		item(string strname, string strtype, int intvalue, int intminProb=0)
		{
			name = strname;
			type = strtype;
			value = intvalue;
			minProb = intminProb;
		}
	};

	class itemPrototype
	{
	public:
	/*------------------------*/
		vector<string> types;
		class prototype
		{
		public:
			string name;
			int value;
			prototype(string strname,int intvalue)
			{
				name = strname;
				value = intvalue;
			}
		};
		vector<prototype> cars;
		vector<prototype> houses;
		vector<prototype> criticals;


		itemPrototype()
		{
			
			types.push_back("coin");
			types.push_back("car");
			types.push_back("house");
			types.push_back("critical");
			/*------------------------------*/
			cars.push_back(prototype("Ferrari",25000000));
			cars.push_back(prototype("Lamborghini",15000000));
			cars.push_back(prototype("Chevrolet Camaro",18000000));
			cars.push_back(prototype("Audi RS 7",10000000));
			cars.push_back(prototype("Ford Mustang",30000000));
			cars.push_back(prototype("Porsche Cayman",12000000));
			/*------------------------------*/
			houses.push_back(prototype("Hawaii,USA",35000000));
			houses.push_back(prototype("Toyko,Japan",10000000));
			houses.push_back(prototype("Bangkok,Thailand",2000000));
			houses.push_back(prototype("New York,USA",20000000));
			houses.push_back(prototype("Rome,Italy",80000000));
			houses.push_back(prototype("Sydney,Australia",200000000));
			/*------------------------------*/
			//criticals.push_back(prototype("Lost All House",50));	/* Value are minimum num required prob to gen it */
			//criticals.push_back(prototype("Lost All car",30));
			//criticals.push_back(prototype("Lost All gold",40));
			//criticals.push_back(prototype("Lost All house & car",80));
			//criticals.push_back(prototype("Steal Car",50));
			//criticals.push_back(prototype("Steal House",70));
			//criticals.push_back(prototype("Bankrupt",90));


			criticals.push_back(prototype("Lost All House",100));	/* Value are minimum num required prob to gen it */
			criticals.push_back(prototype("Lost All car",100));
			criticals.push_back(prototype("Lost All gold",100));
			criticals.push_back(prototype("Lost All house & car",100));
			criticals.push_back(prototype("Steal Car",100));
			criticals.push_back(prototype("Steal House",100));
			criticals.push_back(prototype("Bankrupt",30));

		}
	};



	vector<item> itemMap;
	itemPrototype prototypeItem;
	vector<int> randomItems;

	coreGame()
	{
		randTurn = 0;
		prob = 0;
		generate_itemMap();
		player1Choose.push_back(0);/*[0] for me ,[1] for challenger*/
		player1Choose.push_back(0);
		player2Choose.push_back(0);
		player2Choose.push_back(0);
		while(true)
		{

			showItem_player();
			randomItems.empty();
			randomItems=random_item();
			showRandom_item(true);
			chooseItem();

			winner = highlow();
			if(winner==0)
			{
				getItem(0,player1Choose[0]);// player 1 won get my item
				getItem(1,player1Choose[1]);// player 2 lose get item's Player 1 selected
			}
			else
			{
				getItem(1,player2Choose[0]);// player 2 won get my item
				getItem(0,player2Choose[1]);// player 1 lose get item's Player 2 selected
			}
			
			
		}
		
	}

	void getItem(uint player,uint item)
	{
		string name = itemMap[item].name;
		string type = itemMap[item].type;
		int value = itemMap[item].value;

		if(type == "coin")/* tested by gorn */
		{
			players[player].coins+=value;
			if(value<=0)cout << "\n\tPlayer " << intToStr(player)<< ": " << players[player].name << " Lost " << intToStr(value*(-1)) << "("<< intToStr(value / 1000000) <<"M)"<<" coins";
			else cout << "\n\tPlayer " << intToStr(player)<< ": " << players[player].name << " Got " << intToStr(value) << "("<< intToStr(value / 1000000) <<"M)" <<" coins";
		}
		else if(type == "car" || type == "house")/* tested by gorn */
		{
			players[player].box.add(item,1);
			cout << "\n\tPlayer " << intToStr(player)<< ": " << players[player].name << " got " << name;
		}
		else
		{
			if(name=="Lost All House")/* tested by gorn */
			{
				for(int i=0;i<(int)players[player].box.item.size()&&i>=0;i++)
				{
					if(itemMap[players[player].box.item[i].id].type=="house")
					{
						players[player].box.item.erase(players[player].box.item.begin()+i);
						i--;
					}
				}
				cout << "\n\tPlayer " << intToStr(player)<< ": " << players[player].name << " Lost All House!";
			}
			else if(name=="Lost All car")/* tested by gorn */
			{
				for(int i=0;i<(int)players[player].box.item.size()&&i>=0;i++)
				{
					if(itemMap[players[player].box.item[i].id].type=="car")
					{
						players[player].box.item.erase(players[player].box.item.begin()+i);
						i--;
					}
				}
				cout << "\n\tPlayer " << intToStr(player)<< ": " << players[player].name << " Lost All Car!";
			}
			else if(name=="Lost All gold")/* tested by gorn */
			{
				players[player].coins=0;
				cout << "\n\tPlayer " << intToStr(player)<< ": " << players[player].name << " Lost All Coins!";
			}
			else if(name=="Steal Car")/* tested by gorn */
			{
				vector<int> car; uint challenger,choose;
				if(player==0)challenger=1; else challenger=0;
				cout << "\n\t" << "Player " << intToStr(player+1)<< ": " << players[player].name;
				cout << " got right to Steal one car of challenger -> " << players[challenger].name;
				
				
				

				for(uint i=0;i<players[challenger].box.item.size();i++)
				{
					if(itemMap[players[challenger].box.item[i].id].type=="car")
					{
						
						car.push_back(players[challenger].box.item[i].id);
						cout << "\n\t(" << intToStr(car.size()) << ") " << itemMap[players[challenger].box.item[i].id].name << " x " << intToStr(players[challenger].box.item[i].amount);
						
					}
					
				}
				if(car.size()<=0)
				{
					cout << "\nsorry, but challenger didn't have any car.";
				}
				else
				{
					while(true)
					{
						cPrint.cPrint("\n\n\tplease select car... (1-" + intToStr(car.size()) + ")> ","red");
						cin >> choose;
						choose--;
						if(choose>=0&&choose<=car.size()-1)
							{break;}
					}
					players[challenger].box.del(car[choose],1);
					players[player].box.add(car[choose],1);
					cout << "\n\t" << "Player " << intToStr(player)<< ": " << players[player].name;
					cout << " stolen  " << itemMap[car[choose]].name << " x 1" << " of "<< players[challenger].name;
						
				}

			}
			else if(name=="Steal House")/* tested by gorn */
			{
				vector<int> house; uint challenger,choose;
				if(player==0)challenger=1; else challenger=0;
				cout << "\n\t" << "Player " << intToStr(player+1)<< ": " << players[player].name;
				cout << " got right to Steal one house of challenger -> " << players[challenger].name;
				
				
				

				for(uint i=0;i<players[challenger].box.item.size();i++)
				{
					if(itemMap[players[challenger].box.item[i].id].type=="house")
					{
						
						house.push_back(players[challenger].box.item[i].id);
						cout << "\n\t(" << intToStr(house.size()) << ") " << itemMap[players[challenger].box.item[i].id].name << " x " << intToStr(players[challenger].box.item[i].amount);
						
					}
					
				}
				if(house.size()<=0)
				{
					cout << "\nsorry, but challenger didn't have any house.";
				}
				else
				{
					while(true)
					{
						cPrint.cPrint("\n\n\tplease select house... (1-" + intToStr(house.size()) + ")> ","red");
						cin >> choose;
						choose--;
						if(choose>=0&&choose<=house.size()-1)
							{break;}
					}
					players[challenger].box.del(house[choose],1);
					players[player].box.add(house[choose],1);
					cout << "\n\t" << "Player " << intToStr(player)<< ": " << players[player].name;
					cout << " stolen  " << itemMap[house[choose]].name << " x 1" << " of "<< players[challenger].name;
						
				}

			}
			else if(name=="Lost All house & car")/* tested by gorn */
			{
				players[player].box.item.clear();
				cout << "\n\tPlayer " << intToStr(player)<< ": " << players[player].name << " Lost All house & car!";
			}
			else if(name=="Bankrupt")/* tested by gorn */
			{
				players[player].coins=0;
				players[player].box.item.clear();
				cout << "\n\tPlayer " << intToStr(player)<< ": " << players[player].name << " Bankrupted ,Lost All coins & house & car!";
			}

		}

	}

	void chooseItem(void)
	{
		cPrint.cPrint("\nPlayer 1 :" + players[0].name,"red") ;
		while(true)
		{
			cout << "\n" << " select item for me (1-8)>";
			cin >> player1Choose[0];
			player1Choose[0]--;
			if(player1Choose[0]>=0&&player1Choose[0]<=7)
				{break;}
		}
		while(true)
		{
			cout << "\n" << " select item for challenger (1-8)>";
			cin >> player1Choose[1];
			player1Choose[1]--;
			if(player1Choose[1]>=0&&player1Choose[1]<=7)
				{break;}
		}

		cPrint.cPrint("\nPlayer 2 :" + players[1].name,"red") ;
		while(true)
		{
			cout << "\n" << " select item for me (1-8)>";
			cin >> player2Choose[0];
			player2Choose[0]--;
			if(player2Choose[0]>=0&&player2Choose[0]<=7)
				{break;}
		}
		while(true)
		{
			cout << "\n" << " select item for challenger (1-8)>";
			cin >> player2Choose[1];
			player2Choose[1]--;
			if(player2Choose[1]>=0&&player2Choose[1]<=7)
				{break;}
		}

		/*Convert to mapitem [1-8] to map[0-n]*/
		player1Choose[0]=randomItems[player1Choose[0]];
		player1Choose[1]=randomItems[player1Choose[1]];
		player2Choose[0]=randomItems[player2Choose[0]];
		player2Choose[1]=randomItems[player2Choose[1]];

		//cout << endl << player1Choose[0] << "," << player1Choose[1];
		//cout << endl << player2Choose[0] << "," << player2Choose[1];


	}

	int highlow(void)
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
			if(i!=29)cout << num1 << " " << num2 << endl;
			else cPrint.cPrint(intToStr(num1)+" "+intToStr(num2),"green");
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

	vector<int> random_item(void)
	{
		int a,b,c;
		vector<int> ritem;
		/*Generate lost coin 2*/
		a = (rand() % 20);
		b = (rand() % 20);
		ritem.push_back(a);
		ritem.push_back(b);
		/*Generate coin 3*/
		a = (rand() % 20)+20;
		b = (rand() % 20)+20;
		c = (rand() % 20)+20;
		ritem.push_back(a);
		ritem.push_back(b);
		ritem.push_back(c);
		/*Generate car 1*/
		a = (rand() % 6)+40;
		ritem.push_back(a);
		/*Generate house 1*/
		a = (rand() % 6)+46;
		ritem.push_back(a);
		/*Generate critical 1*/
		if(prob>=30)
		{
			while(true)
			{
				a = (rand() % 7)+52;
				if(prob>=itemMap[a].minProb)
				{
					ritem.push_back(a);
					break;
				}
			}
		}
		else
		{
				a = (rand() % 20)+20;
				ritem.push_back(a);
		}

		prob+=10;
		/* Swap item 20 rounds*/
		for(int i=0;i<20;i++)
		{
			int temp;
			a = (rand() % 8);
			temp=ritem[0];
			ritem[0]=ritem[a];
			ritem[a]=temp;
		}
		return ritem;

	}

	void showRandom_item(bool noSecret=false)
	{
		uint a,b,c,d,e;
		a = (rand() % 8);
		b = (rand() % 8);
		c = (rand() % 8);
		d = (rand() % 8);
		e = (rand() % 8);
		cout<<"\n";
		for(uint i=0;i<randomItems.size();i++)
		{
			if(i==a||i==b||i==c||i==d||i==e)
			{
				if(!noSecret)cPrint.cPrint("\t("+intToStr(i+1)+") ???Secret item???","red");
				else cPrint.cPrint("\t("+intToStr(i+1)+") "+itemMap[randomItems[i]].name,"magenta");
			}
			else
			{
				cPrint.cPrint("\t("+intToStr(i+1)+") "+itemMap[randomItems[i]].name,"magenta");
			}
			if(i==3)cout<<endl;
		}

	}
	void showItem_player(void)
	{
		cout << "\n\t____________________________________________________________________";
		cout << "\n\t" << players[0].name<< "\t\t\t\t\t" << players[1].name;
		cout << "\n\t" << players[0].coins << "("<< intToStr(players[0].coins / 1000000) <<"M)" << " coins"; 
		cout << "\t\t\t" << players[1].coins << "("<< intToStr(players[1].coins / 1000000) <<"M)" << " coins";
		uint maxLine;
		if(players[0].box.item.size()>players[1].box.item.size()){maxLine=players[0].box.item.size();}
		else{maxLine=players[1].box.item.size();}
		for(uint i=0;i<maxLine;i++)
		{
			if(i<players[0].box.item.size())
			{
				cout << "\n\t" << itemMap[players[0].box.item[i].id].name << " x " << intToStr(players[0].box.item[i].amount);
			}
			else
			{
				cout << "\n\t\t\t";
			}
			if(i<players[1].box.item.size())
			{
				cout << "\t\t\t" << itemMap[players[1].box.item[i].id].name << " x " << intToStr(players[1].box.item[i].amount);
			}

		}
		cout << "\n\t____________________________________________________________________";
	}

	void generate_itemMap(void)
	{
		/*
		=====================================
		0-19 = lost coins
		20-39 = get coins
		40-45 = get car
		46-51 = get house
		52-58 = critical
		=====================================
		*/
		/*---------------------------------*/
		/*Generate coin & lost coin		   */
		for(int i =1;i<=20;i++)
		{
			itemMap.push_back(item("Lost Coin "+intToStr(i)+"M", prototypeItem.types[0], i*1000000*(-1)));
		}
		for(int i =1;i<=20;i++)
		{
			itemMap.push_back(item("Get  Coin "+intToStr(i)+"M", prototypeItem.types[0], i*1000000));
		}
		/*---------------------------------*/
		/*Generate car 				  	   */
		for(int i =0;i<=5;i++)
		{
			itemMap.push_back(item("(Car)"+prototypeItem.cars[i].name, prototypeItem.types[1], prototypeItem.cars[i].value));
		}
		/*---------------------------------*/
		/*Generate house 				   */
		for(int i =0;i<=5;i++)
		{
			itemMap.push_back(item("(House)"+prototypeItem.houses[i].name, prototypeItem.types[2], prototypeItem.houses[i].value));
		}
		/*---------------------------------*/
		/*Generate critical 			   */
		for(int i =0;i<=6;i++)
		{
			itemMap.push_back(item(prototypeItem.criticals[i].name, prototypeItem.types[3], 0, prototypeItem.criticals[i].value));
		}
		/*---------------------------------*/

		for(uint i=0;i<itemMap.size();i++)
		{
				cout<<i<<" "<<itemMap[i].name<<" "<<itemMap[i].type<<" "<<itemMap[i].value<<" "<<itemMap[i].minProb<<endl;
		}
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

	return 0;
}