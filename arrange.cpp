#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6262)
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

const int MAX = 120;

int arrange(int lineLength, istream& inf, ostream& outf);

void printWord(int& cFilled, const char tempWord[], int lineLen, int numSpaces, ostream& of);
bool isLongWord(const char tempWord[], int lineLen);
bool isParagraph(const char tempWord[]);
int charFollowingHyphen(char h);
bool specialPunct(const char tempWord[]);

int main()
{
	/*
	ifstream infile("case_ALL.txt");
	ofstream outfile("result_ALL.txt");
	cerr << "case_ALL returns: " << arrange(8, infile, outfile) << endl;

	ifstream in("LONG.txt");
	ofstream out("long_result.txt");
	cerr << "LONG returns: " << arrange(300, in, out) << endl; */
}

int arrange(int lineLength, istream& inf, ostream& outf) {
	if (lineLength < 1) {
		return 1;
	}

	char line[MAX];
	char word[MAX] = "";
	const char empty[MAX] = "";
	int wIndex = 0;
	int i;

	int charFilled = 0;

	bool lookingForSpace = false;//changed
	bool endOfLine = false;

	bool newPara = false;

	bool hyphenAtEnd = false;
	bool hyphenBefore = false;
	bool specPunctBefore = false;

	bool outFirstWord = false;

	int nSpaces = 1;
	int charAfterHyphen = 2;

	int error2 = 0;

	while (inf.getline(line, MAX))
	{
		int currentLineLen = strlen(line);

		for (i = 0; i < currentLineLen; i++) {

			if (charAfterHyphen == 0) {
				charAfterHyphen = charFollowingHyphen(line[i]);
			}

			if (!isspace(line[i])) {
				word[wIndex] = line[i];
				wIndex++;
				lookingForSpace = true;
			}

			endOfLine = (!isspace(line[i]) && (i + 1 == currentLineLen));
			hyphenAtEnd = (line[i] == '-');

			if ((hyphenAtEnd) || (endOfLine) || (isspace(line[i]) && lookingForSpace)) {
				if (isParagraph(word)) {
					if (outFirstWord) {
						newPara = true;
					}
				}

				else {
					outFirstWord = true;
					if (newPara) {
						outf << "\n\n";
						charFilled = 0;
						newPara = false;
						hyphenBefore = false;
						specPunctBefore = false;
					}

					//account for spacing
					if (hyphenBefore && charAfterHyphen == 1) {
						nSpaces = 0;
					}
					else if (specPunctBefore) {
						nSpaces = 2;
					}
					else {
						nSpaces = 1;
					}

					if (isLongWord(word, lineLength)) {
						error2 = 2;
					}

					printWord(charFilled, word, lineLength, nSpaces, outf);
				}


				//special cases
				if (hyphenAtEnd) {
					charAfterHyphen = 0;
					hyphenBefore = true;
				}
				else if (specialPunct(word)) {
					specPunctBefore = true;
				}
				else {
					hyphenBefore = false;
					specPunctBefore = false;
				}

				//reset word
				strncpy(word, empty, 120);
				wIndex = 0;
				lookingForSpace = false;
			}
		}

	}

	outf << "\n";
	return error2;
}


//HELPER FUNCTIONS
void printWord(int& cFilled, const char tempWord[], int lineLen, int numSpaces, ostream& of) {
	int wordLen = strlen(tempWord);

	if (!isLongWord(tempWord, lineLen)) {
		if ((cFilled == 0) && (cFilled + wordLen <= lineLen)) {
			of << tempWord;
			cFilled += wordLen;
		}

		else if (cFilled != 0) {
			if (cFilled + wordLen + numSpaces <= lineLen) {
				for (int j = 0; j < numSpaces; j++) {
					of << " "; //FIX TO BLANK SPACE LATER//
					cFilled++;
				}
				of << tempWord;
				cFilled += wordLen;
			}
			else {
				of << endl;
				of << tempWord;
				cFilled = wordLen;
			}

		}
	}

	else {
		char copy[MAX];
		strcpy(copy, tempWord);

		if (cFilled != 0) {
			of << endl;
			cFilled = 0;
		}

		for (int w = 0; w < wordLen; w++) {
			if (cFilled == lineLen) {
				cFilled = 0;
				of << endl;
			}
			of << tempWord[w];
			cFilled++;
		}
	}
}

bool isLongWord(const char tempWord[], int lineLen) {
	if (strlen(tempWord) > lineLen) {
		return true;
	}
	return false;
}

bool isParagraph(const char tempWord[]) {
	char para[] = "<P>";
	if (strcmp(para, tempWord) == 0) {
		return true;
	}
	return false;
}

int charFollowingHyphen(char h) {
	if (!isspace(h)) {
		return 1;
	}
	else {
		return 2;
	}
}

bool specialPunct(const char tempWord[]) {
	int len = strlen(tempWord);

	char p = tempWord[len - 1];

	switch (p) {
	case '?':
	case '.':
	case ':':
		return true;
	default:
		return false;
	}
}