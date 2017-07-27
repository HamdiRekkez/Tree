
/** @file main.cpp
 * @brief The main entry point.
 *
 * @author Hamdi Rakkez
 */

// Standard includes.
#include <cstdlib>
#include <limits>
#include <ctype.h>

// Other includes.
#include "dict_utils.hpp"
#include "string_utils.hpp"

// For progress.
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

using namespace std;

/**
 * Prints the results along with the search criteria used.
 *
 * @param res The vector containing the results.
 * @param Ne The accepted number of errors in characters. 0 by default.
 * @param Ns The accepted number of missing characters. 0 by default.
 * @param Na The accepted number of extra characters. 0 by default.
 */
void printResults(const vector<string> res, const size_t Ne = 0,
	const size_t Ns = 0, const size_t Na = 0);

/*
 * Main Entry point.
 */
int main()
{
	// The tree structure.
	tree<char> tr;

	// The tree root node.
	//tr.insert(tr.begin(), '.');
	tr.set_head('.');

	// The choice to navigate through the program's Menu.
	char choice;

	do {
		cout << "___________                      " << endl;
		cout << "\\__    ___/______   ____   ____  " << endl;
		cout << "  |    |  \\_  __ \\_/ __ \\_/ __ \\ " << endl;
		cout << "  |    |   |  | \\/\\  ___/\\  ___/ " << endl;
		cout << "  |____|   |__|    \\___  >\\___  >" << endl;
		cout << "                       \\/     \\/" << endl << endl;
		cout << " 1 - Load dictionary from file(Word/Line)." << endl;
		cout << " 2 - Search for a word in the dictionary." << endl;
		cout << " 3 - Add a word to the dictionary." << endl;
		cout << " 4 - Add list of words to the dictionary." << endl;
		cout << " 5 - Show/Print current dictionary." << endl;
		cout << " 6 - Clear the current dictionary." << endl;
		cout << " 7 - Exit." << endl << endl;
		cout << "[INPUT] Enter your choice and press Enter: ";
		cin >> choice;
		system("clear");

		switch (choice) {
		// Loading dictionary.
		case '1': {
			string path = "";
			cout << "[INPUT] Enter the name or the full path for the "
				"dictionary." << endl;
			cin >> path;
			system("clear");
			size_t wordsNumber = 0;

			ifstream file(path);

			// When the file don't exist.
			if (!file.is_open()) {
				cout << "[LOG_WARNING] Invalid path for dictionary!" << endl;
				break;
			}

			/* The string which will be holding each word to insert into
			 * the dictionary. */
			string str;

			cout << "[LOG_INFO] Loading dictionary '" << path <<
				"' in the tree..." << endl;
			cout << "[LOG_INFO] This can take some time depending on the "
				"dictionary" << endl;
			// Getting start clock.
			int start = clock();

			while (getline(file, str)) {
				// Convert the word to lower case first.
				toLower(str);

				// Insert the word. Don't show log.
				insertWord(str, tr, false);
				wordsNumber++;
			}

			// Getting stop clock.
			int stop = clock();

			// Printing execution time in ms.
			cout << endl << "[LOG_CHRONO] Inserting '" << wordsNumber <<
				"' words in the dictionary took: " << (stop - start) /
				double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;

			cout << "[LOG_INFO] The dictionary '" << path <<
				"' was loaded into the tree !" << endl;
			cout << endl << "[LOG_INFO] " << wordsNumber << " word(s) added to "
				"the tree dictionary." << endl;
			cout << endl << "[LOG_INFO] " << "The dictionary's depth is : "
				<< tr.max_depth() << endl;
		}
			break;
		case '2': {
			// We make sure the dictionary is not empty.
			if (tr.empty()) {
				cout << "[LOG_WARNING] The dictionary is empty!" << endl;
				cout << "[LOG_INFO] Load a dictionary or add words first." << endl;
				break;
			}

			string word = "";
			cout << "[INPUT] Enter a word to search for." << endl;
			cin >> word;
			system("clear");

			// Converts the word to lower case.
			toLower(word);

			char searchCriteria;
			do {
				cout << "[INPUT] Do you want to set a search criteria for '"
					<< word << "' ? (y/n) ";
				cin >> searchCriteria;
				system("clear");

				if (searchCriteria == 'n') {
					// Call searchForWords without any criteria.
					vector<string> res = searchForWords(word, tr);
					printResults(res);
				} else if (searchCriteria == 'y') {
					size_t wrongCharacters;
					size_t addedCharacters;
					size_t missingCharacters;
					cout << "[INPUT] Enter the N° of accepted wrong "
						"characters for '" << word << "' :  ";
					cin >> wrongCharacters;
					cout << "[INPUT] Enter the N° of accepted added "
						"characters for '" << word << "' :  ";
					cin >> addedCharacters;
					cout << "[INPUT] Enter the N° of accepted missing "
						"characters for '" << word << "' :  ";
					cin >> missingCharacters;
					system("clear");
					// Call searchForWords with the given criteria.
					vector<string> res = searchForWords(word, tr,
						wrongCharacters, missingCharacters, addedCharacters);
					printResults(res, wrongCharacters, missingCharacters,
						addedCharacters);
				}
			} while ((searchCriteria != 'y') && (searchCriteria != 'n'));
		}
			cout << endl << "[INPUT] Press [r] then [Enter] to return "
				"to the Menu ..." << endl;
			cin.ignore(numeric_limits<streamsize>::max(),'r');
			system("clear");
			break;
		case '3': {
			string word = "";
			cout << "[LOG_INPUT] Enter a word to add to the dictionary." << endl;
			cin >> word;

			// Converts the word to lower case.
			toLower(word);

			// We add the word.
			insertWord(word, tr);

			cout << endl << "[INPUT] Press [r] then [Enter] to return "
				"to the Menu ..." << endl;
			cin.ignore(numeric_limits<streamsize>::max(),'r');
		}
			system("clear");
			break;
		case '4': {
			string word = "";
			cout << "[LOG_INPUT] Enter the list of words to add to the "
				"dictionary." << endl;
			cout << "[LOG_INFO] Words should be separated by a comma ','"
				<< endl << endl;
			cin >> word;

			// Converts the word to lower case.
			toLower(word);

			// We add the word.
			insertWords(word, tr);

			cout << endl << "[INPUT] Press [r] then [Enter] to return to "
				"the main Menu ..." << endl;
			cin.ignore(numeric_limits<streamsize>::max(),'r');
		}
			system("clear");
			break;
		case '5': {
			// We make sure the dictionary is not empty.
			if (tr.empty()) {
				cout << "[LOG_WARNING] The dictionary is empty!" << endl;
				cout << "[LOG_INFO] Load a dictionary or add words first." << endl;
				break;
			}
			cout << "[LOG_INFO] The loaded dictionary :" << endl;
			kptree::print_tree_bracketed(tr, cout);
			cout << endl;
			cout << endl << "[INPUT] Press [r] then [Enter] to return to "
				"the main Menu ..." << endl;
			cin.ignore(numeric_limits<streamsize>::max(),'r');
		}
			system("clear");
			break;
		case '6': {
			tr.clear();
			cout << "[LOG_INFO] The dictionary is cleared." << endl;
			cout << endl;
			cout << endl << "[INPUT] Press [r] then [Enter] to return to "
				"the main Menu ..." << endl;
			cin.ignore(numeric_limits<streamsize>::max(),'r');
		}
			system("clear");
			break;
		case '7':
			// End of program.
			return EXIT_SUCCESS;
		default:
			cout << "[LOG_WARNING] You have entered an invalid choice!" << endl
				<< "[INPUT] Please choose again !" << endl << endl;
			continue;
		}

	} while (1);

	return EXIT_SUCCESS;
}

void printResults(const vector<string> res, const size_t Ne, const size_t Ns,
	const size_t Na)
{
	if (!res.empty()) {
		cout << "[LOG_INFO] We found " << res.size() << " result(s)." << endl;
		cout << "[LOG_INFO] Search criteria is : " << endl;
		cout << "    - Accepted wrong characters : " << Ne <<  endl;
		cout << "    - Accepted extra characters : " << Na <<  endl;
		cout << "    - Accepted missing characters : " << Ns <<  endl;
		cout << "[LOG_INFO] Results : " << endl;
		// Print results.
		for (vector<string>::const_iterator it = res.begin(); it != res.end();
			it++) {
			cout << "    - " << (*it) << endl;
		}
	} else {
		cout << "[LOG_INFO] No results were found matching your search!"
			<< endl;
	}
}