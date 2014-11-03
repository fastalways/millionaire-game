#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;

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
	ostringstream convert;   // stream used for the conversion
	convert << num;      // insert the textual representation of 'Number' in the characters in the stream
	return convert.str(); // set 'Result' to the contents of the stream
}
string floatToStr(float num)
{
	ostringstream convert;   // stream used for the conversion
	convert << num;      // insert the textual representation of 'Number' in the characters in the stream
	return convert.str(); // set 'Result' to the contents of the stream
}
string charToStr(char num)
{
	ostringstream convert;   // stream used for the conversion
	convert << num;      // insert the textual representation of 'Number' in the characters in the stream
	return convert.str(); // set 'Result' to the contents of the stream
}

int main(int argc, char* argv[])
{
	colorPrint cPrint;
	cPrint.cPrint(intToStr(123),"blue");
	return 0;
}