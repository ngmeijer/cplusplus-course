#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#define ARRAY_SIZE 5

using namespace std;

const int MAX = 3;
int numbersArray[MAX] = { 0 };
int* currentArrayNumber;

std::vector<string> stringArray;
std::vector<char> firstLetters;

void inputIntArrayElementCin() {
	//User input
	for (int i = 0; i < MAX; i++) {
		cin >> numbersArray[i];
	}
}

void inputIntArrayElementScanf() {
	//User input
	for (int i = 0; i < MAX; i++) {
		scanf_s("%d", &numbersArray[i]);
	}
}

void inputStringArrayElementCin() {
	//User input
	string input;

	while (cin >> input && input != "quit" && input.length() <= 30) {
		stringArray.push_back(input);
	}
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

void sortIntArrayElements() {
	std::vector<int> intVec(numbersArray, numbersArray + MAX);

	std::sort(intVec.begin(), intVec.end(), std::greater<int>());

	std::cout << "The array with sorted numbers contains:";
	for (std::vector<int>::iterator it = intVec.begin(); it != intVec.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

bool comparer(string a, string b)
{
	return a < b;
}

void sortStringDynArrayElements() {
	cout << "\n" << "The strings will now be sorted alphabetically, based on the first letter of the string." << endl;

	int firstLetterArraySize = firstLetters.size();

	sort(stringArray.begin(), stringArray.end());

	//int stringArraySize = stringArray.size();
	//std::vector<string> stringVec(stringArray, stringArray.operator=);

	//std::sort(stringVec.begin(), stringVec.end(), std::greater<string>());
}



void printIntArrayElements() {
	//Output
	//cout << "\n" << "Implementation with c.out with pointers. Comment and uncomment desired input method." << endl;
	cout << "\n";
	for (int i = 0; i < MAX; i++) {

		cout << "Value of int array elements [" << i << "] = ";

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

void printStringArrayElements() {
	cout << "\n";
	for (string& givenString : stringArray) {
		cout << givenString << endl;
	}
}

int main()
{
	cout << "\n" << "GIMME NUMBERS: " << endl;
	inputIntArrayElementCin();
	//inputIntArrayElementScanf();

	cout << "\n" << "NOW GIMME WORDS" << endl;
	inputStringArrayElementCin();

	
	cout << "\nRESULTS OF EVERYTHING" << endl;
	printIntArrayElements();
	printStringArrayElements();

	sortIntArrayElements();

	sortStringDynArrayElements();

	printStringArrayElements();

	//Memory freeing causes an internal breakpoint to be triggered by VS, and the program to crash!
	//delete[] numbersArray;
}