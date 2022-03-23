#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

class Timer {
private:
  // Type aliases to make accessing nested type easier
  using clock_type = std::chrono::steady_clock;
  using second_type = std::chrono::duration<double, std::ratio<1>>;
  std::chrono::time_point<clock_type> m_beg{clock_type::now()};

public:
  void reset() { m_beg = clock_type::now(); }

  double elapsed() const {
    return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg)
        .count();
  }
};

using namespace std;

namespace parse {
int lineCount, noSpaceCount, questionCount, answerCount, blankSpace,
    outCurrent = 0;
string tLine[5000];
string aLine[5000];
string qLine[5000];
string allLine[5000];
string outArr[5000];
bool doUpdate = false; // True gives verbose printout
} // namespace parse

/* ADD TO parse_functions.cpp BEFORE COMPILING ////////////////////////
/* FUNCTION HEADERS */                                              //
void test(int &lineCount, int &noSpaceCount, int &questionCount, //
          int &answerCount, int &blankSpace, int &outCurrent);   //
string delSpace(string &str);                                    //
bool ansChk(string str);                                         //
/////////////////////////////////////////////////////////////////

/* PROGRAM START */
int main() {
  fstream nameFile, inFile;
  string currentLine, testLine, fileName;

  // Ask for file name and open
  cout << "What is the name of the file you wish to search?\n";
  cin >> fileName;
  ifstream file(fileName);

  // Opens File; gives error if file cannot be opened
  nameFile.open(fileName, ios::in | ios::app);
  if (!nameFile) {
    cout << "File open error." << endl;
    return 0;
  }

  // Begins timer for formatting operation
  Timer t;

  // Iterates over file; saves lines to tLine array and counts lines
  while (getline(file, currentLine)) {
    int &count = parse::lineCount;
    parse::tLine[parse::lineCount] = currentLine;
    count += 1;
  }

  // Iterates through tLine to eliminate blank lines
  for (int i = 0; i <= parse::lineCount; i++) {
    string currentLine = parse::tLine[i];
    string testLine = delSpace(currentLine);

    if (testLine.length() != 0) {
      parse::allLine[parse::noSpaceCount] = currentLine;
      parse::noSpaceCount += 1;
    } else {
    }
  }

  // Checks lines for Question/Answer to add to own array
  for (int i = 0; i <= parse::lineCount; i++) {
    int &q = parse::questionCount;
    int &a = parse::answerCount;

    string currentLine = parse::allLine[i];
    size_t questionFound = currentLine.find("QUESTION");
    size_t answerFound = currentLine.find("Answer");
    size_t skipFound = currentLine.find("SKIP");

    if (questionFound != string::npos) {
      parse::qLine[q] = currentLine;
      q += 1;

      if (skipFound != string::npos) {
        parse::aLine[a] = "";
        a += 1;
      }
    } else if (answerFound != string::npos) {
      parse::aLine[a] = currentLine;
      a += 1;
    } else {
    }
  }

  // Looks for Question/Answer. Adds all but 'Answer' to new array
  for (int i = 0; i <= parse::lineCount; i++) {
    int &x = parse::outCurrent;
    string currentLine = parse::allLine[i];
    string testLine = delSpace(currentLine);
    size_t questionFound = currentLine.find("QUESTION");
    size_t answerFound = currentLine.find("Answer");

    if (answerFound != string::npos) {
      parse::outArr[x] = "";
    } else if (questionFound != string::npos) {
      parse::outArr[x] = "";
      x += 1;
      parse::outArr[x] = currentLine;
      x += 1;
    } else {
      parse::outArr[x] = currentLine;
      x += 1;
    }
  }

  // Opens Q/A file to be written
  ofstream outfile1("qa_" + fileName);
  for (int i = 0; i <= parse::questionCount; i++) {
    string currentQ = parse::qLine[i];
    string currentA = parse::aLine[i];

    outfile1 << currentQ << " - " << currentA << endl;

    if (parse::doUpdate) {
      cout << currentQ << " - " << currentA << endl;
    }
  }

  // Closes Q/A file
  outfile1.close();

  // Opens Output file
  ofstream outfile2("output_" + fileName);

  // Iterates through output array and writes to file
  for (int i = 0; i <= (parse::noSpaceCount + 5); i++) {
    string currentLine = parse::outArr[i];
    string testLine = delSpace(currentLine);
    bool isAnswer = ansChk(testLine);

    if (isAnswer) {
      string oldLine = currentLine;
      i += 1;
      currentLine = parse::outArr[i];
      string newLine = "   " + oldLine + " " + currentLine;
      outfile2 << newLine << endl;

      if (parse::doUpdate) {
        cout << newLine << endl;
      }
    } else {
      outfile2 << currentLine << endl;

      if (parse::doUpdate) {
        cout << currentLine << endl;
      }
    }
  }

  // Closes output file
  outfile2.close();

  cout << "\nOutput complete in " << t.elapsed() << " seconds\n";
}
/* PROGRAM END */

/////////////// ADD TO parse_functions.cpp BEFORE COMPILING////////////////////
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
};

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
