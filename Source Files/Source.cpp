void MainMenuDraw();
void MainMenuInput();
void MainMenuLogic();
bool fileNameValidity();
void WriteToFile(double, double, double);
void fileTransfer();
void setRandom();
void ResetInputVariables();
void drawTitle();
void hideCursor();
void drawArrow();
#include "Definitions.h"
int main() {
	hideCursor();
	system("MODE 120, 35"); // May need to be omitted for some compilations
	system("color F0");
	do {
		do {
			MainMenuDraw();
			MainMenuInput();
			MainMenuLogic();
			SetConsoleCursorPosition(console, coordinates);
		} while (!EXIT_MENU);
		if (!EXIT_OUTPUT) {
			infile.open("stats.txt");
			for (int i = 0; i < 4; i++)
				line[i].showValues(i);
			if (showShapes)
				line[0].showQuadInfo();
			EXIT_MENU = false;
			EXIT_OUTPUT = true;
			infile.close();
		}
	} while (!EXIT_PROGRAM);
	return 0;
}
