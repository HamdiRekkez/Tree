
/** @file dict_utils.hpp
 * @brief A utility tree dictionary functions.
 *
 * @author Hamdi Rakkez
 */

#ifndef DICT_UTILS_HPP
#define DICT_UTILS_HPP

// Tree includes.
#include "tree.hh"

// Standard includes.
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Search for a words inside a given tree dictionary.
 * The function will return a list of words matching the search criteria.
 *
 * @param word The given word as string to look for.
 * @param dict The given dictionary.
 * @param Ne The accepted number of errors in characters. 0 by default.
 * @param Ns The accepted number of missing characters. 0 by default.
 * @param Na The accepted number of extra characters. 0 by default.
 *
 * @return The list of strings matching the search criteria. May be empty.
 * PS: When the word don't exists or the dictionary is not valid, the function
 * will return an empty strings list and print some logs.
 */
vector<string> searchForWords(const string& word, const tree<char>& dict,
	const size_t Ne = 0, const size_t Ns = 0, const size_t Na = 0);

/**
 * Add a new word to a given dictionary.
 *
 * @param word The word to add into the dictionary.
 * @param dict The given tree format dictionary.
 * @param showLog enable/disable showing chronometer log for each word. This
 * will help to disable the log when adding a huge number of words.
 *
 * @return True when the word was successfully added, False when the word
 * already exists or the dictionary is not valid.
 */
bool insertWord(const string& word, tree<char>& dict,
	const bool showLog = true);

/**
 * Insert a bunch of words separated by a comma in the dictionary.
 *
 * @param words The string of words separated by a comma. word1,word2...
 * @param dict The given dictionary.
 *
 * @return Returns true when the insertion when done with success. When no word
 * was found in the given string this will return false.
 */
bool insertWords(const string& words, tree<char>& dict);

#endif /* DICT_UTILS_HPP */
