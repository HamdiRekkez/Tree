
/** @file dict_utils.cpp
 * @brief A utility tree dictionary functions implementation.
 *
 * @author Hamdi Rakkez
 */

#include "dict_utils.hpp"
#include "string_utils.hpp"

using namespace std;

vector<string> searchForWords(const string& word, const tree<char>& dict,
	const size_t Ne, const size_t Ns, const size_t Na)
{
	// Getting start clock.
	int start = clock();

	// The list of found results.
	vector<string> res;

	/* We do some input control and return an empty vector with those rules :
	 * If the Ns is bigger or equal to the word length.
	 * If the the word's length is bigger than the tree's maximum depth. */
	if (Ns >= word.length() || word.length() > (unsigned)dict.max_depth()
		+ Na + 1) {
		return vector<string>();
	}

	// Getting the minimum accepted length for the searched word.
	size_t minLength = word.length() - Ns;

	// Getting the maximum accepted length of the searched word.
	size_t maxLength = word.length() + Na;

	// Iterate all possible nodes depths from minLength to maxLength.
	for (size_t i = minLength; i <= maxLength; i++) {
		/* When the wanted depth is bigger than than the dictionary's depth
		 * we must get out and return the vector. */
		if (i > (unsigned)dict.max_depth() + 1) {
			return res;
		}

		tree<char>::fixed_depth_iterator itDepth = dict.begin_fixed(
			dict.begin(), i - 1);
		while(dict.is_valid(itDepth)) {
			if (itDepth.number_of_children() == 0) {
				string wordTmp;
				wordTmp.push_back(itDepth.node->data);
				tree<char>::iterator parent = itDepth.node->parent;
				while (parent != NULL) {
					wordTmp = parent.node->data + wordTmp;
					parent = parent.node->parent;
				}

				if ((levenshteinDistance(word, wordTmp))
					<= (Ne + lengthDistance(word, wordTmp))) {
					res.push_back(wordTmp);
				}
			}
			++itDepth;
		}
	}

	// Getting stop clock.
	int stop = clock();

	// Printing execution time in ms.
	cout << "[LOG_CHRONO] Searching for the word '" << word << "' took: "
		<< (stop - start) / double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;

	// Return the words matching the search criteria.
	return res;
}

bool insertWord(const string& word, tree<char>& dict, const bool showLog)
{
	// Getting start clock.
	int start = clock();

	// The tree iterators.
	tree<char>::leaf_iterator it;
	tree<char>::sibling_iterator itBegin = dict.begin();
	tree<char>::sibling_iterator itEnd = dict.end();
	
	for (size_t i = 0; i < word.length(); i++) {
		// We iterate the characters in the word.
		char node = word.at(i);

		// The tree leaf iterator at the the wanted node.
		it = find(itBegin, itEnd, node);

		// If the current node exist and don't have children.
		if (it != itEnd && it.number_of_children() != 0) {
			if(i == word.length() - 1) {
				dict.insert(itEnd, node);
			} else {
				itBegin = it.begin();
				itEnd = it.end();
				continue;
			}
		// If the current node don't exist.
		} else {
			tree<char>::leaf_iterator iter ;
			// We create the node as a child of the root node.
			if (itBegin.node->data == '.') {
				iter = dict.insert(itEnd, node);
			} else {
				iter = dict.insert(itBegin, node);
			}

			/* We insert all the remaining nodes.(The remaining letters
			 * in the word). */
			for (size_t x = i + 1; x < word.length(); x++, iter++) {
				dict.insert(iter.end(), word.at(x));
			}
			// No need to go further, we have inserted all the siblings.
			break;
		}
	}

	// Getting stop clock.
	int stop = clock();

	if (showLog) {
		// Printing execution time in ms.
		cout << "[LOG_CHRONO] Inserting the word '" << word << "' took: "
			<< (stop - start) / double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;
	}

	return true;
}

bool insertWords(const string& words, tree<char>& dict)
{
	// Getting start clock.
	int start = clock();

	if (words.empty()) {
		cout << endl << "[LOG_INFO] No words to add were found!" << endl;
		return false;
	} else {
		vector<string> strVect = splitString(words);
		cout << endl << "[LOG_INFO] " << strVect.size() <<
			" Words will be added to the dictionary." << endl << endl;
		for (vector<string>::const_iterator it = strVect.begin();
			it != strVect.end(); it++) {
			insertWord((*it), dict);
		}

		// Getting stop clock.
		int stop = clock();

		// Printing execution time in ms.
		cout << "[LOG_CHRONO] Inserting '" << strVect.size() << "' words in "
			"the dictionary took: " << (stop - start) / double(CLOCKS_PER_SEC)
			* 1000 << " ms" << endl;

		return true;
	}
}