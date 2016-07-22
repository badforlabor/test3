
#include <windows.h>
#include <iostream>

#include "../../mpglib\mpg123.h"
#include "../../mpglib\mpglib.h"
#include "../../MP3decoder.h"

int main()
{
	system("pause");
	MP3decoder mp3;	
	std::cout << "sound-length:" << (mp3.GetTotalTime("test.mp3") / 1000);
	std::vector<char> outRet;
	std::cout << "wav-length:" << mp3.GetBytes(outRet, "test.mp3");
	system("pause");
}