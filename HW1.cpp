//Program to analyze a text file of a book to determine book's title,
//author's name, word count, letter frequency, and line count.
//
//Text file should include title and author's name in first and second lines, respectively
//Book information will be saved to text file named "CardCatalog.txt"
//
//Program by Ian Doemling and Grant Galinger

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {
	struct book {
		string title;
		string authorName;
		int wordCount;
		double letterFrequency[26] = { 0 };
		int lineCount;
	};

	string userInput;
	string line;
	fstream txtFile;
	fstream bookList;
	book myBook;
	string word;
	bool cont = 1;
	bool anotherBook = 1;
	int i;
	int totalLetters = 0;
	char c;

	//Loop until user does not want to enter any more books
	while (anotherBook) {
		cout << "What is the name of the file you would like to open?" << endl;
		cin >> userInput;

		txtFile.open(userInput, ios::in);

		//Checks to see if user-entered file name is valid
		while (txtFile.fail()) {
			cout << "File does not exist, please enter another file name." << endl;
			cin >> userInput;
			txtFile.open(userInput, ios::in);
		}

		//Saves book title and author's name to structure
		getline(txtFile, myBook.title);
		getline(txtFile, myBook.authorName);

		//Gets to beginning of the book
		while (cont) {
			getline(txtFile, line);
			if (line.substr(0, 9) == "Contents:") {
				cont = 0;
			}
		}

		//Loops through each word, counting words and letters
		i = 0;
		while (!txtFile.eof()) {
			txtFile >> word;
			for (int j = 0; j < word.length(); j++) {
				for (char c = 'A'; c <= 'Z'; c++) {
					if ((word[j] == c) | (word[j] == c + 32)) {
						myBook.letterFrequency[c - 65] += 1; //Enters letter frequency to structure's array
					}
				}
			}
			i++;
		}
		myBook.wordCount = i; //Saves word count to structure

		//Closes and re-opens file to get back to beginning
		txtFile.close();
		txtFile.open(userInput, ios::in);

		//Finds beginning of the actual book (where "Contents:" is)
		cont = 1;
		while (cont) {
			getline(txtFile, line);
			if (line.substr(0, 9) == "Contents:") {
				cont = 0;
			}
		}

		//Loops through lines until end, counting how many there are
		i = 0;
		while (!txtFile.eof()) {
			getline(txtFile, line);
			i++;
		}
		myBook.lineCount = i; //Saves line count to structure

		//Opens text file to write structure data to, and writes data to it
		bookList.open("CardCatalog.txt", ios::app);

		bookList << "Title:\t\t\t" << myBook.title << endl;
		bookList << "Author Full Name:\t" << myBook.authorName << endl;
		bookList << "Author First Name:\t" << myBook.authorName.substr(0, myBook.authorName.find(" ")) << endl;
		bookList << "Author Last Name:\t" << myBook.authorName.substr(myBook.authorName.find(" ") + 1) << endl;
		bookList << "Word Count:\t\t" << myBook.wordCount << endl;
		bookList << "Line Count:\t\t" << myBook.lineCount << endl << endl;

		cout << "Would you like to see the letter frequecy of " << myBook.title << "?" << endl;
		cin >> userInput;

		//Calculates and displays letter frequency in percentages if prompted by user
		if (userInput == "Yes" | userInput == "yes") {
			for (int i = 0; i < 26; i++) {
				totalLetters += myBook.letterFrequency[i];
			}
			cout << myBook.title << " Letter Frequency:" << endl;
			for (int i = 0; i < 26; i++) {
				c = i + 97;
				cout << c << ": " << 100.0 * myBook.letterFrequency[i] / totalLetters << "%" << endl;
			}
		}

		txtFile.close();
		bookList.close();
		
		//Changes boolean value to stop while loop if user is done entering books
		cout << "Do you want to process another book?" << endl;
		cin >> userInput;
		if (userInput == "No" | userInput == "no") {
			anotherBook = 0;
		}
	}
	return 0;
}