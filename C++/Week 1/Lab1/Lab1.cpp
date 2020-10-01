#include <iostream>
#include <string>

#define ARRAY_SIZE 5

using namespace std;

const int MAX = 3;
int numbersArray[MAX] = { 0 };

int* currentArrayNumber;
int* currentSortingNumber;
int* lastArrayNumber;
int lastInt = 0;

int greaterThanResult = 0;

float test1 = 5.5f;
double test2 = 4.40404040;


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

bool greaterThan(int a, int b) {
	return a > b;
}

struct SwapElementValues {
	int elementA;
	int elementB;
};

SwapElementValues swapElements(int elementA, int elementB) {
	SwapElementValues elements = { elementA,elementB };
	int tempElement = elementA;
	elementA = elementB;
	elementB = tempElement;

	return elements;
}

void sortArrayElements() {
	int selectedNumber = 4;
	for (int indexA = 0; indexA < MAX; indexA++) {
		for (int indexB = 0; indexB < MAX; indexB++) {
			currentSortingNumber = &numbersArray[indexA];
			lastArrayNumber = &numbersArray[selectedNumber--];

			greaterThanResult = greaterThan(*currentSortingNumber, *lastArrayNumber);

			/*if (result == 1) {
				SwapElementValues swappedResult = swapElements(*currentSortingNumber, *lastArrayNumber);
				cout << "\nResult of elementA: " << swappedResult.elementA << "\nResult of elementB";
				currentIndex++;
			}*/

			/*if (result == 1) {
				numbersArray[MAX - 1] = *currentSortingNumber;
				currentIndex++;
			}

			cout << "\nFirst number (a): " << *currentSortingNumber << "\nSecond number (b): " << *lastArrayNumber;*/
		}
		cout << "\nFirst number: " << *currentSortingNumber << "\nSecond number: " << *lastArrayNumber;
		cout << "\nResult of GreaterThan: " << greaterThanResult << "\n";
	}
}


void printArrayElements() {
	//Output
	//cout << "\n" << "Implementation with c.out with pointers. Comment and uncomment desired input method." << endl;
	cout << "\n";
	for (int i = 0; i < MAX; i++) {

		cout << "Value of array elements [" << i << "] = ";

		//Get array element address (pointer)
		currentArrayNumber = &numbersArray[i];

		//Convert to int with * and write console line out.
		cout << (*currentArrayNumber) << endl;
	}

	//cout << "\n" << "Implementation with scanf and printf" << endl;
	//for (int i = 0; i < MAX; i++) {

	//	//Get array element address (pointer)
	//	currentArrayNumber = &numbersArray[i];
	//	//Convert to int with * and print the line
	//	printf("The values of array = %u\n", *currentArrayNumber);
	//}
}

int main()
{
	cout << "\n" << "GIMME NUMBERS: " << endl;

	inputArrayElementCin();
	//inputArrayElementScanf();
	printArrayElements();

	cout << "\n" << "The numbers will now be sorted from high to low." << endl;

	sortArrayElements();

	printArrayElements();

	//Memory freeing causes an internal breakpoint to be triggered by VS, and the program to crash!
	//delete[] numbersArray;
}