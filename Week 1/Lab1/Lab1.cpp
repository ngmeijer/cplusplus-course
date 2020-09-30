#include <iostream>
#include <string>

#define ARRAY_SIZE 5

using namespace std;

const int MAX = 3;
int numbersArray[MAX] = { };

int* currentArrayNumber;
int lastInt = 0;

void debugLine(const char* testString, int exampleNumber, const char* testString2) {
	std::cout << testString << exampleNumber << testString2;
	return;
}

void doubleInput() {
	cout << "GIVE VALUE BITCH! : ";

	int valueGiven;
	cin >> valueGiven;

	int result = valueGiven * 2;
	cout << result;
}

void inputArrayElementCin() {
	//User input
	for (int i = 0; i < MAX; i++) {
		cin >> numbersArray[i];
	}
}

void inputArrayElementScanf() {
	//User input
	for (int i = 0; i < MAX; i++) {
		scanf_s("%d", &numbersArray[i]);
	}
}

void sortArrayElements() {
	for (int index = 0; index < MAX; index++) {

		greaterThan(lastInt, numbersArray[index]);

		if (greaterThan(lastInt, numbersArray[index]) == true) {
			numbersArray[index] = MAX;
		}
	}
}

bool greaterThan(int a, int b) {
	return a > b;
}

void printArrayElements() {
	//Output
	cout << "\n" << "Implementation with c.out with pointers. Comment and uncomment desired input method." << endl;
	for (int i = 0; i < MAX; i++) {

		cout << "Value of array elements [" << i << "] = ";

		//Get array element address (pointer)
		currentArrayNumber = &numbersArray[i];

		////Convert to int with * and write console line out.
		cout << (*currentArrayNumber) << endl;
	}

	cout << "\n" << "Implementation with scanf and printf" << endl;
	for (int i = 0; i < MAX; i++) {

		//Get array element address (pointer)
		currentArrayNumber = &numbersArray[i];
		//Convert to int with * and print line
		printf("The values of array = %u\n", *currentArrayNumber);
	}
}

int main()
{
	cout << "\n" << "GIMME NUMBERS: " << endl;

	inputArrayElementCin();
	//inputArrayElementScanf();
	printArrayElements();

	sortArrayElements();

	cout << "\n" << "The numbers will now be sorted from high to low." << endl;

	printArrayElements();

	//Memory freeing causes a breakpoint to be triggered by VS, and the program to crash!
	//delete[] numbersArray;
}


/////////////////
//https://stackoverflow.com/questions/10865957/printf-with-stdstring 
//Ask this in next lab; explanation about preference for printf over std::cout << "".
/////////////////