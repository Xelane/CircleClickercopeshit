//The standard stuff
#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

using namespace std;

int main(){
	// Initializing window
	initwindow(1280, 720);

	//Initial screen generation
	srand(time(0));
	int CircleBoundX = 1160;
	int CircleBoundY = 600;
	int CircleX = (rand() % CircleBoundX) + 60;
	int CircleY = (rand() % CircleBoundY) + 60;
	circle(CircleX, CircleY, 50);
	outtextxy(610, 680, (char*)"Combo: ");
	outtextxy(675, 680, (char*)"0");
	outtextxy(610, 15, (char*)"Timer: ");
	outtextxy(665, 15, (char*)"10");
	outtextxy(465, 45, (char*)"Click as many circles within the time limit as possible");
	outtextxy(550, 75, (char*)"Timer starts on the first click");

	
	int MouseX, MouseY;
	int combo = 0;
	bool MouseDown = 0;
	bool FirstClick = 1;
	long Counter, TotalTime;
	
	while(1){
		
		MouseX = mousex();
		MouseY = mousey();

		//Detecting whether mouse input is inside circle or not		
		int MouseDistSq = (MouseX - CircleX) * (MouseX - CircleX) + (MouseY - CircleY) * (MouseY - CircleY);
		int MouseDist = sqrt(MouseDistSq);

		//Debugging stuff
		//cout << MouseX << " " << MouseY << " " << MouseDist << endl;
		//cout << time(0)<<endl;

		//Circle click condition
		if (GetAsyncKeyState(VK_LBUTTON) && MouseDown == 0) {
			if (MouseDist <= 50) {

				//Clearing previous circle
				cleardevice();

				//Generating new random circle
				CircleX = (rand() % CircleBoundX) + 60;
				CircleY = (rand() % CircleBoundY) + 60;
				circle(CircleX, CircleY, 50);

				//Updating time since circle generation
				if (FirstClick) {
					TotalTime = time(0) + 10;
					FirstClick = 0;
				}
				Counter = TotalTime - time(0);

				//Adding combo
				combo++;

				//Converting int to string
				char combostr[(((sizeof combo) * CHAR_BIT) + 2) / 3 + 2];
				sprintf_s(combostr, "%d", combo);
				char timerstr[(((sizeof Counter) * CHAR_BIT) + 2) / 3 + 2];
				sprintf_s(timerstr, "%d", Counter);

				outtextxy(610, 15, (char*)"Timer: ");
				outtextxy(665, 15, timerstr);

				outtextxy(610, 680, (char*)"Combo: ");
				outtextxy(675, 680, combostr);

				//Counter check
				if (Counter == 0) {
					outtextxy(580, 650, (char*)"The timer has ended");
					break;
				}
			}
			//Fail check
			else if (MouseDist > 50) {
				
				outtextxy(545, 650, (char*)"You clicked outside the circle");
				break;

			}
			MouseDown = 1;
		}
		if (!GetAsyncKeyState(VK_LBUTTON)) {
			MouseDown = 0;
		}
	}
	getch();								
	closegraph();
	return 0;
}						