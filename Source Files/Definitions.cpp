#pragma once

#ifndef FILENAME_H
#define FILENAME_H

#include "Class.h"

// Libaries //
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>

// Namespaces //
using namespace std;

// Global Variables, Constants and Related //
const int ZERO = .00000000000000001; // Constant value to be returned if slope is ZERO
const int UNDEFINED = .00000000000000002; // Constant value to be returned if slope is UNDEFINED
double lines[4][3]; // Up to four lines can worked with at once

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Output handle
COORD coordinates; // Coordinate object for SetConsoleCursorPosition();

enum input { ENTER, UP, DOWN, LEFT, RIGHT, BACK, NONE }; // Enumerator for input variables
input MainMenu_Input = NONE; // Variable to store user input
input LAST_MainMenu_Input = NONE; // Data to store the most recent user input

ifstream infile; // Read from file
ofstream outfile; // Write from file
string fileName; // Variable for storing file name

COLORREF black = RGB(0, 0, 0); // COLORREF used for SetPixel graphing

bool EXIT_PROGRAM = false; // When true, program will exit
bool EXIT_MENU = false; // When true, menu will exit
bool EXIT_OUTPUT = true; // When true, output will exit
bool SpecialClear = true; // When true, screen will be cleared again before input and logic functions begin

int MainMenu_OptionSelected = 1; // Counter for Main Menu
int OptionThree_OptionSelected = 1; // Counter for Option Three
int OptionTwo_OptionSelected = 1; // Counter for Option Two
int OptionTwo_OptionChosen = 0; // int for Option selected from listed choices on Option Two

bool on_MainMenu = true; // When true, user is on the Main Menu
bool on_OptionThree = false; // When true, user is on Option Three
bool on_OptionTwo = false; // When true, user is on Option Two
bool on_SetFile = false; // When true, user is on Set File Screen
bool on_InputData = false; // When true, user is on Input Line Data Screen
bool on_Random = false; // WHen true, user is on Set Number of Random Lines screen

bool showSlope = true; // When true, output will show slope info
bool showIntercept = true; // When true, output will show intercept info
bool showIntersections = true; // When true, output will show intersection info
bool showParallels = true; // When true, output will show parallel info
bool showPerpendiculars = true; // When true, output will show perpendicular info
bool showEquals = true; // When true, output will show equal line info
bool showShapes = true; // When true, output will show info related to quadrilaterals

lineType line[4];

double lineType::slope() { // Calculates slope and returns it's value
	if (b == 0)
		return UNDEFINED;
	else if (a == 0)
		return ZERO;
	else
		return -1 * 
		(a / b);
}
// Following math all done by quad and math teams
bool lineType::equal(lineType line1, lineType line2) {
	if ((line1.a == line2.a && line1.b == line2.b && line1.c == line2.c) || (line1.a / line2.a == line1.b / line2.b == line1.c / line2.c))
		return true;
	else
		return false;
}
bool lineType::parallel(lineType line1, lineType line2) {
	if (line1.slope() == line2.slope())
		return true;
	else
		return false;
}
double distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}
bool lineType::perpendicular(lineType line1, lineType line2) {
	if ((line1.a == 0 && line2.b == 0) || (line2.a == 0 && line1.b == 0) || (line1.slope() * line2.slope() == -1))
		return true;
	else
		return false;
}
void lineType::pointOfIntersection(lineType line1, lineType line2, double& x_int, double& y_int) {


	x_int = (((-(line1.c / line1.b)) + (line2.c / line2.b)) / ((-(line1.a / line1.b)) + (line2.a / line2.b)));

	y_int = ((-(line1.a / line1.b)) * x_int) + (line1.c / line1.b);

	
}
int lineType::quadrilateral() {
	double x_int1;
	double y_int1;
	double x_int2;
	double y_int2;

	double side_1;
	double side_2;
	double side_3;
	double side_4;

	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (equal(line[i], line[j]))
				return 0;
		}
	}
	int p_count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (parallel(line[i], line[j]))
				p_count++;
		}
	}
	if (p_count > 2)
		return 0;
	if (parallel(line[0], line[1])) {
		pointOfIntersection(line[0], line[2], x_int1, y_int1);
		pointOfIntersection(line[0], line[3], x_int2, y_int2);
		side_1 = distance(x_int1, y_int1, x_int2, y_int2);

		pointOfIntersection(line[1], line[2], x_int1, y_int1);
		pointOfIntersection(line[1], line[3], x_int2, y_int2);
		side_2 = distance(x_int1, y_int1, x_int2, y_int2);

		pointOfIntersection(line[2], line[0], x_int1, y_int1);
		pointOfIntersection(line[2], line[1], x_int2, y_int2);
		side_3 = distance(x_int1, y_int1, x_int2, y_int2);

		pointOfIntersection(line[3], line[0], x_int1, y_int1);
		pointOfIntersection(line[3], line[1], x_int2, y_int2);
		side_4 = distance(x_int1, y_int1, x_int2, y_int2);

		if (perpendicular(line[0], line[2]) && perpendicular(line[0], line[3])) {
			if (side_1 == side_2 && side_1 == side_3 && side_1 == side_4 && side_2 == side_3 && side_2 == side_4 && side_3 == side_4) {
				return 1;
			}
			else {
				return 3;
			}

		}

		else {
			if ((parallel(line[2], line[3]) && line[3].parallel(line[3], line[2]))) {
				if (side_1 == side_2 && side_1 == side_3 && side_1 == side_4 && side_2 == side_3 && side_2 == side_4 && side_3 == side_4) {
					return 2;
				}
				else {
					return 4;
				}

			}
			else {
				return 5;
			}

		}
	}

	else if (parallel(line[2], line[3])) {

		pointOfIntersection(line[0], line[2], x_int1, y_int1);
		pointOfIntersection(line[0], line[3], x_int2, y_int2);
		side_1 = distance(x_int1, y_int1, x_int2, y_int2);

		pointOfIntersection(line[1], line[2], x_int1, y_int1);
		pointOfIntersection(line[1], line[3], x_int2, y_int2);
		side_2 = distance(x_int1, y_int1, x_int2, y_int2);

		pointOfIntersection(line[2], line[0], x_int1, y_int1);
		pointOfIntersection(line[2], line[1], x_int2, y_int2);
		side_3 = distance(x_int1, y_int1, x_int2, y_int2);

		pointOfIntersection(line[3], line[0], x_int1, y_int1);
		pointOfIntersection(line[3], line[1], x_int2, y_int2);
		side_4 = distance(x_int1, y_int1, x_int2, y_int2);

		if (perpendicular(line[2], line[0]) && perpendicular(line[2], line[1])) {
			if (side_1 == side_2 && side_1 == side_3 && side_1 == side_4 && side_2 == side_3 && side_2 == side_4 && side_3 == side_4) {
				return 1;
			}
			else {
				return 3;
			}
		}
		else {
			if (parallel(line[0], line[1]) && parallel(line[1], line[0])) {
				if (side_1 == side_2 && side_1 == side_3 && side_1 == side_4 && side_2 == side_3 && side_2 == side_4 && side_3 == side_4) {
					return 2;
				}
				else {
					return 4;
				}
			}
			else {
				return 5;
			}
		}
	}
	else {
	return 0;
	}
}
#include "Class.h"


void MainMenuDraw() { // Draws screen
	drawTitle();
	cout << "\n\n";
	cout << "\t\t\t\t1. Calculate!";
	if (MainMenu_OptionSelected == 1) {
		drawArrow();
	}
	cout << endl;
	cout << "\t\t\t\t2. Set Data Source";
	if (MainMenu_OptionSelected == 2) {
		drawArrow();
	}
	cout << endl;
	// OptionTwo Menu output
	if (on_OptionTwo) {
		cout << "\t\t\t\t\t[";
		if (OptionTwo_OptionChosen == 1)
			cout << "x";
		else
			cout << " ";
		cout << "] Randomly Generate Data";
		if (OptionTwo_OptionSelected == 1) {
			drawArrow();
		}
		cout << endl;
		// Set Random Output
		if (on_Random) {
			system("CLS");
			on_Random = false;
			setRandom();
			cout << "\n\n\n\t\t\t\tRandom Values Set!\n\t\t\t\t";
			system("PAUSE");
			SpecialClear = true;
		}
		cout << "\t\t\t\t\t[";
		if (OptionTwo_OptionChosen == 2)
			cout << "x";
		else
			cout << " ";
		cout << "] Grab From Specified File";
		if (OptionTwo_OptionSelected == 2) {
			drawArrow();
		}
		cout << endl;
		// Set File output
		if (on_SetFile) {
			system("CLS");
			cout << "\n\n\t\tFile must be formated \"a b c\" \n\t\tbased on the standard formula, ax + by = c" << endl;
			cout << "\t\tEnter file name and extension\n\n";
			cout << "\t\t\t\t\tFile Name: ";
			getline(cin, fileName);
			on_SetFile = false;
			SpecialClear = true;
			if (fileNameValidity())
				fileTransfer();
		}
		cout << "\t\t\t\t\t[";
		if (OptionTwo_OptionChosen == 3)
			cout << "x";
		else
			cout << " ";
		cout << "] Input Data Manually";
		if (OptionTwo_OptionSelected == 3) {
			drawArrow();
		}
		cout << endl;
		// Input Data Output
		if (on_InputData) {
			int line = 1; char choice = 0;
			outfile.open("stats.txt");
			while (on_InputData) {
				double t_a = NULL, t_b = NULL, t_c = NULL;
				system("CLS");
				SpecialClear = true;
				cout << "\n\n\n\n\t\tEnter in a, b, and c from the standard formula of a line (ax + by = c) for AT LEAST four lines:" << endl;
				cout << "\t\tLine " << line << endl;
				cout << "\t\ta: "; cin >> t_a;
				cout << "\n\t\tb: "; cin >> t_b;
				cout << "\n\t\tc: "; cin >> t_c;
				if (!cin.fail())
					WriteToFile(t_a, t_b, t_c);
				system("CLS");
				if (line == 4) {
					outfile << endl;
					outfile.close();
					on_InputData = false;
				}
				else if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\t\t\t\tPlease enter a valid number!\n\t\t\t\t";
					system("PAUSE");
					line--;
				}
				line++;
			}
		}
	}
	cout << "\t\t\t\t3. Set Output";
	if (MainMenu_OptionSelected == 3) {
		drawArrow();
	}
	// OptionThree Menu output
	if (on_OptionThree) {
		cout << endl;
		cout << "\t\t\t\t\t[";
		if (showSlope)
			cout << "x";
		else
			cout << " ";
		cout << "] Slope";
		if (OptionThree_OptionSelected == 1) {
			drawArrow();
		}
		cout << endl;
		cout << "\t\t\t\t\t[";
		if (showIntercept)
			cout << "x";
		else
			cout << " ";
		cout << "] Y-Intercept";
		if (OptionThree_OptionSelected == 2) {
			drawArrow();
		}
		cout << endl;
		cout << "\t\t\t\t\t[";
		if (showIntersections)
			cout << "x";
		else
			cout << " ";
		cout << "] Any Intersections";
		if (OptionThree_OptionSelected == 3) {
			drawArrow();
		}
		cout << endl;;
		cout << "\t\t\t\t\t[";
		if (showParallels)
			cout << "x";
		else
			cout << " ";
		cout << "] Any Parallel Lines";
		if (OptionThree_OptionSelected == 4) {
			drawArrow();
		}
		cout << endl;
		cout << "\t\t\t\t\t[";
		if (showPerpendiculars)
			cout << "x";
		else
			cout << " ";
		cout << "] Any Perpendicular Lines";
		if (OptionThree_OptionSelected == 5) {
			drawArrow();
		}
		cout << endl;
		cout << "\t\t\t\t\t[";
		if (showEquals)
			cout << "x";
		else
			cout << " ";
		cout << "] Any Equal Lines";
		if (OptionThree_OptionSelected == 6) {
			drawArrow();
		}
		cout << endl;
		cout << "\t\t\t\t\t[";
		if (showShapes)
			cout << "x";
		else
			cout << " ";
		cout << "] Any Formed Quadrilaterals";
		if (OptionThree_OptionSelected == 7) {
			drawArrow();
		}
		cout << endl;
	}
	cout << endl;
	cout << "\t\t\t\t4. Exit";
	if (MainMenu_OptionSelected == 4) {
		drawArrow();
	}
	else
		cout << "    ";
	// Controls output
	cout << "\n\n\n\n";
	cout << "\t\t            ";
	if (LAST_MainMenu_Input == UP)
		SetConsoleTextAttribute(console, 242);
	cout << "^";
	cout << "        w                                                    " << endl;
	SetConsoleTextAttribute(console, 240);
	cout << "\t\tControls: ";
	if (LAST_MainMenu_Input == LEFT)
		SetConsoleTextAttribute(console, 242);
	cout << "< ";
	SetConsoleTextAttribute(console, 240);
	if (LAST_MainMenu_Input == DOWN)
		SetConsoleTextAttribute(console, 242);
	cout << "v";
	SetConsoleTextAttribute(console, 240);
	cout << " ";
	if (LAST_MainMenu_Input == RIGHT)
		SetConsoleTextAttribute(console, 242);
	cout << ">";
	SetConsoleTextAttribute(console, 240);
	cout << " or ";
	if (LAST_MainMenu_Input == LEFT)
		SetConsoleTextAttribute(console, 242);
	cout << "a ";
	SetConsoleTextAttribute(console, 240);
	if (LAST_MainMenu_Input == DOWN)
		SetConsoleTextAttribute(console, 242);
	cout << "s";
	SetConsoleTextAttribute(console, 240);
	if (LAST_MainMenu_Input == RIGHT)
		SetConsoleTextAttribute(console, 242);
	cout << " d";
	SetConsoleTextAttribute(console, 240);
	cout << " to move\n\t\t";
	if (LAST_MainMenu_Input == BACK)
		SetConsoleTextAttribute(console, 242);
	cout << "Backspace or Escape";
	SetConsoleTextAttribute(console, 240);
	cout << " to go back, and ";
	if (LAST_MainMenu_Input == ENTER)
		SetConsoleTextAttribute(console, 242);
	cout << "Enter." << endl;
	SetConsoleTextAttribute(console, 240);
	cout << "\n\n";
	if (!fileNameValidity() && OptionTwo_OptionChosen == 2) {
		SetConsoleTextAttribute(console, 244);
		cout << "\t\t\t\tError: Cannot find file \"" << fileName << "\"" << endl;
	}
	else if (fileNameValidity() && OptionTwo_OptionChosen == 2) {
		SetConsoleTextAttribute(console, 241);
		cout << "\t\t\t\tFile Found, program will attempt to use" << endl;
	}
	if (OptionTwo_OptionChosen == 0) {
		SetConsoleTextAttribute(console, 249);
		cout << "\t\t\t\tWarning: No data option selected. Necessary to calculate." << endl;
	}
	SetConsoleTextAttribute(console, 240);
	if (SpecialClear) { // Used specifically to clear other half of output after cin is used for on_SetFile, keep on bottom
		SpecialClear = false;
		system("CLS");
	}
}
void MainMenuInput() { // Gets inputs and sets Input Variables
	if (MainMenu_Input != NONE)
		LAST_MainMenu_Input = MainMenu_Input;
	ResetInputVariables();
	if (_kbhit()) {
		system("CLS");
		switch (_getch()) {
		case 13: // ENTER
			MainMenu_Input = ENTER;
			break;
		case 27: // ESC
		case 8: // Backspace
			MainMenu_Input = BACK;
			break;
		case 'w':
		case 72: // UP ARROW
			MainMenu_Input = UP;
			break;
		case 's':
		case 80: // DOWN ARROW
			MainMenu_Input = DOWN;
			break;
		case 'a':
		case 75: // LEFT ARROW
			MainMenu_Input = LEFT;
			break;
		case 'd':
		case 77: // RIGHT ARROW
			MainMenu_Input = RIGHT;
			break;
		}
	}
}
void MainMenuLogic() { // Applies logic
	if (on_MainMenu && on_OptionThree) { // If on Option Three
		switch (MainMenu_Input) {
		case UP:
			OptionThree_OptionSelected--;
			break;
		case DOWN:
			OptionThree_OptionSelected++;
			break;
		case ENTER:
			switch (OptionThree_OptionSelected) {
			case 1:
				showSlope = !showSlope;
				break;
			case 2:
				showIntercept = !showIntercept;
				break;
			case 3:
				showIntersections = !showIntersections;
				break;
			case 4:
				showParallels = !showParallels;
				break;
			case 5:
				showPerpendiculars = !showPerpendiculars;
				break;
			case 6:
				showEquals = !showEquals;
				break;
			case 7:
				showShapes = !showShapes;
				break;
			}
			break;
		case BACK:
			on_OptionThree = false;
			break;
		}
	}
	if (on_MainMenu && on_OptionTwo) { // If on Option Two
		switch (MainMenu_Input) {
			if (!on_SetFile && !on_InputData && !on_Random) {
		case UP:
			if (!on_SetFile && !on_InputData && !on_Random)
				OptionTwo_OptionSelected--;
			break;
		case DOWN:
			if (!on_SetFile && !on_InputData && !on_Random)
				OptionTwo_OptionSelected++;
			break;
		case ENTER:
			switch (OptionTwo_OptionSelected) {
			case 1:
				OptionTwo_OptionChosen = 1;
				on_Random = true;
				break;
			case 2:
				OptionTwo_OptionChosen = 2;
				on_SetFile = true;
				break;
			case 3:
				OptionTwo_OptionChosen = 3;
				on_InputData = true;
				break;
			}
			break;
			}
		case BACK:
			if (!on_SetFile && !on_InputData && !on_Random)
				on_OptionTwo = false;
			break;
		}
	}
	if (on_MainMenu && (!on_OptionThree && !on_OptionTwo)) { // If no option is selected
		switch (MainMenu_Input) {
		case UP:
			MainMenu_OptionSelected--;
			break;
		case DOWN:
			MainMenu_OptionSelected++;
			break;
		case ENTER:
			if (MainMenu_OptionSelected == 4) {
				EXIT_PROGRAM = true;
				EXIT_MENU = true;
			}
			if (MainMenu_OptionSelected == 1 && OptionTwo_OptionChosen != 0) {
				EXIT_MENU = true;
				EXIT_OUTPUT = false;
			}
			if (MainMenu_OptionSelected == 3)
				on_OptionThree = true;
			if (MainMenu_OptionSelected == 2)
				on_OptionTwo = true;
			break;
		}
	}
	// Bounds of MainMenu_OptionSelected
	if (MainMenu_OptionSelected > 4)
		MainMenu_OptionSelected = 4;
	if (MainMenu_OptionSelected < 1)
		MainMenu_OptionSelected = 1;
	// Bounds of OptionThree_OptionSelected
	if (OptionThree_OptionSelected < 1)
		OptionThree_OptionSelected = 1;
	if (OptionThree_OptionSelected > 7)
		OptionThree_OptionSelected = 7;
	// Bounds of OptionTwo_OptionSelected
	if (OptionTwo_OptionSelected < 1)
		OptionTwo_OptionSelected = 1;
	if (OptionTwo_OptionSelected > 3)
		OptionTwo_OptionSelected = 3;
}
void ResetInputVariables() { // Resets input variable
	MainMenu_Input = NONE;
}
void drawTitle() {  // Draws the title
	SetConsoleTextAttribute(console, 241);
	cout << "\n\n";
	cout << "\t\t\t  _     _          __        __         _    " << endl;
	cout << "\t\t\t | |   (_)_ __   __\\ \\      / /__  _ __| | __" << endl;
	cout << "\t\t\t | |   | | '_ \\ / _ \\ \\ /\\ / / _ \\| '__| |/ /" << endl;
	cout << "\t\t\t | |___| | | | |  __/\\ V  V / (_) | |  |   < " << endl;
	cout << "\t\t\t |_____|_|_| |_|\\___| \\_/\\_/ \\___/|_|  |_|\\_\\" << endl;
	SetConsoleTextAttribute(console, 240);
}
void lineType::showValues(int currentLine) { // Draws the Output screen
	for (int i = 0; i < 4; i++) {
		infile >> line[i].a;
		infile >> line[i].b;
		infile >> line[i].c;
	}
	cout << "\n\n\t\tLine " << currentLine + 1 << ": " << fixed << setprecision(2) << a << "x + " << fixed << setprecision(2) << b << "y = " << fixed << setprecision(2) << c << endl;
	if (showSlope && (slope() != UNDEFINED && slope() != ZERO))
		cout << "\n\t\tSlope: " << fixed << setprecision(2) << slope() << endl;
	else if (showSlope && slope() == UNDEFINED)
		cout << "\n\t\tSlope: UNDEFINED" << endl;
	else if (showSlope && slope() == ZERO)
		cout << "\n\t\tSlope: ZERO" << endl;
	if (showIntercept && b != 0)
		cout << "\n\t\tY-Intercept: " << fixed << setprecision(2) << c / b << endl;
	else if (showIntercept && b == 0)
		cout << "\n\t\tY-Intercept ERROR: Divide By Zero" << endl;
	cout << endl;
	if (showEquals) {
		for (int i = 0; i < 4; i++)
			if (currentLine != i)
				if (equal(line[currentLine], line[i]))
					cout << "\t\tLine " << currentLine + 1 << " is equal to line " << i + 1 << endl;
		cout << endl;
	}
	if (showParallels) {
		for (int i = 0; i < 4; i++)
			if (currentLine != i)
				if (parallel(line[currentLine], line[i]))
					cout << "\t\tLine " << currentLine + 1 << " is parallel to line " << i + 1 << endl;
		cout << endl;
	}
	if (showPerpendiculars) {
		for (int i = 0; i < 4; i++)
			if (currentLine != i)
				if (perpendicular(line[currentLine], line[i]))
					cout << "\t\tLine " << currentLine + 1 << " is perpendicular to line " << i + 1 << endl;
		cout << endl;
	}
	if (showIntersections) {
		double x, y;
		for (int i = 0; i < 4; i++)
			if (currentLine != i)
				if (!parallel(line[currentLine], line[i])) {
					pointOfIntersection(line[currentLine], line[i], x, y);
					cout << "\t\tLine " << currentLine + 1 << " intersects line " << i + 1 << " at point (" << x << ", " << y << ")" << endl;
				}
		cout << endl;
	}
	cout << "\n\t\t";
	system("PAUSE");
	system("CLS");
}
void lineType::showQuadInfo() {
	cout << "\n\n\t\tThis set of four lines forms:\n\n\t\t";
	switch (quadrilateral()) {
	case 0:
		cout << "No shape.\n\n\t\t";
		break;
	case 1:
		cout << "A Square!\n\n\t\t";
		break;
	case 2:
		cout << "A Rhombus!\n\n\t\t";
		break;
	case 3:
		cout << "A Rectangle!\n\n\t\t";
		break;
	case 4:
		cout << "A Paralellogram!\n\n\t\t";
		break;
	case 5:
		cout << "A Trapezoid!\n\n\t\t";
		break;
	}
	system("PAUSE");
	system("CLS");
}
// hideCursor() hides the drawing cursor permenantly as one of the programs first
// few instructions
void hideCursor() {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(console, &info);
}
// drawArrow() draws the arrow following each menu option
void drawArrow() {
	SetConsoleTextAttribute(console, 241);
	cout << " <--";
	SetConsoleTextAttribute(console, 240);
}
// fileNameValidity() returns a bool value depending on if the fileName variable is a valid file name
bool fileNameValidity() { 
	ifstream check(fileName);
	if (check)
		return true;
	else
		return false;
}
// fileTransfer() transfers the data from the given file, fileName, to stats.txt
void fileTransfer() {
	double t_a = 0, t_b = 0, t_c = 0;
	infile.open(fileName);
	outfile.open("stats.txt");
	for (int i = 0; i < 4; i++) {
		infile >> t_a >> t_b >> t_c;
		outfile << t_a << ' ' << t_b << ' ' << t_c << endl;
	}
	outfile.close();
	infile.close();
}
// WriteToFile() writes the data input by a user to stats.txt
void WriteToFile(double a, double b, double c) {
	outfile << a << ' ' << b << ' ' << c << '\n';
}
// setRandom() sets random line a b c data based on the number of lines, rl, argument passed by value
void setRandom() {
	srand(time(nullptr));
	outfile.open("stats.txt");
	double number = NULL;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			number = rand() % 31;
			if (rand() % 2 == 1)
				number *= -1;
			if (rand() % 2 + 1 == 2)
				number /= rand() % 100 + 1;
			outfile << number << ' ';
		}
		outfile << endl;
	}
	outfile.close();
}

#endif
