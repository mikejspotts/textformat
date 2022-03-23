#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;



/*---------------------- FUNCTIONS --------------------------------*/
/* Deletes unnecessary spaces in the current line */
string delSpace(string &str) {
  int size = str.length();
  for (int j = 0; j <= size; j++) {
    for (int i = 0; i <= j; i++) {
      if (str[i] == ' ' && str[i + 1] == ' ') {
        str.erase(str.begin() + i);
      } else if (str[0] == ' ') {
        str.erase(str.begin());
      } else if (str[i] == '\0' && str[i - 1] == ' ') {
        str.erase(str.end() - 1);
      }
    }
  }
  return str;
}

/* This function checks if the current line contains an answer indicator
   ex. A., B., etc. If it does, it returns true */
bool ansChk(string str) {
  size_t a = str.find("A.");
  size_t b = str.find("B.");
  size_t c = str.find("C.");
  size_t d = str.find("D.");
  size_t e = str.find("E.");
  size_t f = str.find("F.");
  size_t g = str.find("G.");
  size_t h = str.find("H.");
  size_t i = str.find("I.");

  if (str.length() != 2) {
    return false;
  } else {
    if ((a != string::npos) || (b != string::npos) || (c != string::npos) ||
        (d != string::npos) || (e != string::npos) || (f != string::npos) ||
        (g != string::npos) || (h != string::npos) || (i != string::npos)) {
      return true;
    } else {
      return false;
    }
  }
};

/* Function was used for testing different For Loops */
void test(int &lineCount, int &notSpaceCount, int &questionCount,
          int &answerCount, int &blankSpace, int &outCurrent) {
  cout << "\n-------------------\n";
  cout << "lineCount: " << lineCount << endl;
  cout << "notSpaceCount " << notSpaceCount << endl;
  cout << "questionCount " << questionCount << endl;
  cout << "answerCount " << answerCount << endl;
  cout << "blankSpace " << blankSpace << endl;
  cout << "outCurrent " << outCurrent << endl;
  cout << "-------------------" << endl;
};
