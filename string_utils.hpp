
/** @file string_utils.hpp
 * @brief Utility functions for string manipulation.
 *
 * @author Hamdi Rakkez
 */

#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

// Standard includes.
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

/**
 * Calculates the Levenshtein distance between two given string.
 *
 * @param s1 The first input string.
 * @param s2 The second input string.
 *
 * @return The Levenshtein distance between the two strings.
 * PS: This will return 0 when the two string matches.
 */
size_t levenshteinDistance(const string& s1, const string& s2);

/**
 * Match two given strings according to a set of criteria.
 *
 * @param s1 The first input string.
 * @param s2 The second input string.
 * @param Ne The number of allowed different characters between the two strings.
 * @param Ns The number of allowed missing characters between the two strings.
 * @param Na The number of allowed added characters between the two strings.
 *
 * @return True when the two string match the criteria, False if it is not.
 */
bool matchString(const string& s1, const string& s2, size_t Ne, size_t Ns,
	size_t Na);

/**
 * Get the length difference between two strings.
 *
 * @param s1 The first input string.
 * @param s2 The second input string.
 *
 * @return The difference in length. Always positive.
 */
size_t lengthDistance(const string& s1, const string& s2);

/**
 * Converts all the chars in the input string to lower case.
 *
 * @param str The input string.
 *
 * @return The lower case string.
 */
void toLower(string& str);

/**
 * Splits the string to a vector of strings based on the comma ',' delimeter.
 *
 * @param input The entry string to split.
 *
 * @return The vector of strings.
 */
vector<string> splitString(const string& str);

#endif /* STRING_UTILS_HPP */
