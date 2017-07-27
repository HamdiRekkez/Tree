
/** @file string_utils.cpp
 * @brief Utility functions for string manipulation implementation.
 *
 * @author Hamdi Rakkez
 */

#include "string_utils.hpp"

using namespace std;

size_t levenshteinDistance(const string& s1, const string& s2)
{
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<unsigned int> col(len2 + 1), prevCol(len2 + 1);

	for (size_t i = 0; i < prevCol.size(); i++)
		prevCol[i] = i;
	for (size_t i = 0; i < len1; i++) {
		col[0] = i + 1;
		for (size_t j = 0; j < len2; j++) {
			col[j + 1] = min({ prevCol[1 + j] + 1, col[j] + 1, prevCol[j] +
			(s1[i] == s2[j] ? 0 : 1) });
		}
		col.swap(prevCol);
	}

	return prevCol[len2];
}

size_t lengthDistance(const string& s1, const string& s2)
{
	int l1 = s1.length();
	int l2 = s2.length();
	return abs(l1 - l2);
}

void toLower(string& str)
{
	transform((str).begin(), (str).end(), (str).begin(), ::tolower);
}

vector<string> splitString(const string& str)
{
	vector<string> res;
	size_t start = 0;
	size_t pos = 0;
	size_t length = str.length();
	string token;
	while (pos < length) {
		pos = str.find(",", start);
		token = str.substr(start, pos - start);
		if (!token.empty()) {
			res.push_back(token);
		}
		start = pos + 1;
	}
	return res;
}