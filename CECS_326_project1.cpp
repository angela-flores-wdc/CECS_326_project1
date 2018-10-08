// CECS 326 lab 1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>
using namespace std;

//declare global variable
const int currentSize = 20;

//define struct
struct Test{
	int intArray[20];
	char ** charArray;
};



//recursively initiate numbers in the integer array
void recursiveDefine(int array[], int n) {
	if (n == 0) {
		array[n] = 2700;
	}
	if (n < (currentSize-1)) {
		array[n + 1] = 2 * array[n];
		n++;
		recursiveDefine(array, n);
	}
}

//print out main menu
void printMenu() {
	cout << "\n      MAIN MENU\n";
	cout << "(1) Access a pointer\n";
	cout << "(2) List deallocated memory(index)\n";
	cout << "(3) Deallocate all memory\n";
	cout << "(4) Exit program\n";
}

//print out access pointer submenu
void subMenu() {
	cout << "\n(1) Print the first 10 char's in the chosen array\n";
	cout << "(2) Delete all the char's associated with this pointer\n";
	cout << "(3) Return to main menu\n";
}

//method to print out first ten characters associated with a pointer 
void printFirstTen(Test *temp, int index) {
	if (temp->charArray[index] != NULL) {
		for (int i = 0; i < 10; i++) {
			cout << (temp->charArray[index][i]) << " ";
		}
	}
	else {
		cout << "\nThe pointer at this index has no memory allocated to it\n";
	}
}

//method to deallocate a pointer's memory and set it to NULL
void deletePointerChars(Test *temp, int index) {
	delete[](temp->charArray[index]);
	temp->charArray[index] = NULL;
}

//method to check if a pointer is set to null, and if it is to reallocate memory to it and reinitialize characters 
void checkIfNull(Test *temp, int index) {
	if (temp->charArray[index] == NULL) {
		cout << "This pointer has no memory allocated to it!\nReallocating memory..."<< endl;
		temp->charArray[index] = new char[temp->intArray[index]];
		for (int x = 0; x < temp ->intArray[index]; x++) {
			*(temp->charArray[index] + x) = (char)('A' + rand() % 26);
		}
	}
}

//deallocate all pointer memory 
void deallocateAll(Test *temp) {

    //iterate through all char pointers
	for (int x = 0; x < currentSize; x++) {

        //deallocate memory assigned to this pointer
		delete[](temp->charArray[x]);

        //set pointer to NULL
		temp->charArray[x] = NULL;

	}//end for

}//end deallocateAll method


//method to list all pointers that have had their memory deallocated
void listDeallocated(Test *temp) {
	bool hasNull = false;
	cout << "Index(es) with deallocated memory: \n";

    //iterate through all pointers
	for (int k = 0; k < currentSize; k++) {

        //check if pointer is set to NULL
		if (temp->charArray[k] == NULL) {

            //print out NULL pointer
			cout << k << " ";

            //indicate that a NULL pointer was found
			hasNull = true;
		}//end if
	}//end for

    //check if all indexes were allocated memory
	if (hasNull == false) {
		cout << "There are no indexes with deallocated memory\n";
	}//end if
}//end listDeallocated method


//method to access a pointer
void accessPointer(Test *temp) {
	bool subGoAgain = true;
	int index, subChoice;
	cout << "Enter the index of the pointer you wish to manipulate: \n";
	cin >> index;

    //call method to check if pointer is null
    //and reallocate memory if it is
	checkIfNull(temp, index);

	//logic to print menu and get user input
	while (subGoAgain) {
		subMenu();
		cin >> subChoice;
		switch (subChoice) {
            
        //user chooses option 1 to print out first 10 chars
		case 1:
			cout << "Printing out first 10 char's... \n";
			printFirstTen(temp, index);
			break;

        //user chooses option 2 to delte char assoc. to pointer
		case 2:
			cout << "Deleting char's associated with this pointer...\n";
			deletePointerChars(temp, index);
			break;

        //user chooses to return to main menu
		case 3:
			subGoAgain = false;
			break;
		}//end switch
	}//end while
}//end access pointer method

int main()
{
	// creating struct and pointers and allocating memory
	Test* one = new Test();
	one->charArray = new char*[20];
	recursiveDefine(one->intArray, 0);

	cout << "Memory allocated\nInitializing characters...\n";


	//initialize character values
	for (int i = 0; i < currentSize; i++) {
       
		one->charArray[i] = new char[one->intArray[i]];
		for (int j = 0; j < one->intArray[i]; j++) {
			*(one->charArray[i] + j) = (char)('A' + rand() % 26);
		}
	}

	cout << "Chars initialized\n";

	int choice;
	bool goAgain = true;
	while (goAgain) {
		printMenu();
		cin >> choice;
		switch (choice) {
			// user wants to access a pointer
			case 1: 
				accessPointer(one);
				break;
		
			// user wants to list indexes with deallocated memory
			case 2:
				listDeallocated(one);
				break;
		
			//user wants to deallocate all memory
			case 3:
				deallocateAll(one);
				cout << "All memory has been deallocated\n";
				break;
			
			//user wants to exit the program
			case 4: 
				cout << "Exiting program...\n";
				goAgain = false;	
				deallocateAll(one);
				break;
		}
	}
	cout << "program terminated";
	exit(0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
