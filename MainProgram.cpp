/*
==========================================================================
 LAB: Strings and File Operations
 COURSE: CMP1001 - Introduction to Programming (C++)
 DURATION: 60 minutes
--------------------------------------------------------------------------
 DESCRIPTION:
   In this lab you will practice working with C++ strings (the std::string
   class) and reading/writing text files (ifstream / ofstream). You will
   build small functions that manipulate text and persist data to disk.

 INSTRUCTIONS:
   - Read each section carefully. Comments explain what to do.
   - Replace every // TODO with your own code.
   - Do NOT rename the functions: the autograder relies on these names.
   - Everything stays in THIS single file. No headers, no extra files.
   - Compile with:   g++ MainProgram.cpp -o lab
   - Run with:       ./lab
==========================================================================
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// ========================================================================
// SECTION 2 & 3 & 4 FUNCTIONS
// (You will implement these. main() at the bottom demonstrates them.)
// ========================================================================

// ------------------------------------------------------------------------
// Section 2 - Core Concept: basic string handling
// ------------------------------------------------------------------------

// countVowels: return how many vowels (a,e,i,o,u, upper or lower case)
// appear in the given string.
int countVowels(const string& text) {
    int vowel_count = 0;
    // TODO: loop over each character and count vowels.
    // Hint: compare against "aeiouAEIOU" or lowercase the char first.
    for (char c: text) {
        //if (std::strchr("aeiou", std::tolower(c)));
        for (char vowel: "aeiou") {
            if (vowel == std::tolower(c)) vowel_count++;
        }
    }
    return vowel_count;
}

// toUpperCase: return a NEW string with every letter converted to uppercase.
// Non-letter characters stay unchanged.
string toUpperCase(const string& text) {
    // TODO: build a result string. For each char, if it is 'a'..'z',
    // convert it to uppercase by subtracting 32 (or use toupper).
    std::string copy(text);
    for (size_t i = 0; i < copy.length(); i++) {
        copy[i] = std::toupper(copy[i]);
    }
    return copy;
}

// ------------------------------------------------------------------------
// Section 3 - Guided Exercises
// ------------------------------------------------------------------------

// Exercise 1
// reverseString: return the reverse of the given string.
// Example: "hello" -> "olleh"
string reverseString(const string& text) {
    // TODO: build the reversed string (loop from the end, or swap).
    std::string copy(text);
    for (size_t i = 0, j = copy.length() - 1; i < copy.length() / 2; i++, j--) {
        char tmp = copy[i];
        copy[i] = copy[j];
        copy[j] = tmp;
    }
    return copy;
}

// Exercise 2
// isPalindrome: return true if the string reads the same forwards and
// backwards. Treat it case-SENSITIVELY and consider ALL characters
// (do not strip spaces). Example: "level" -> true, "Level" -> false.
bool isPalindrome(const string& text) {
    for (size_t i = 0, j = text.length() - 1; i < text.length() / 2; i++, j--) {
        if (text[i] != text[j]) return false;
    }
    return true;
}

// Exercise 3
// countWords: return the number of words in the string. Words are
// separated by one or more spaces. Leading/trailing spaces must not
// create empty words. Example: "  hi   there  " -> 2.
int countWords(const string& text) {
    size_t word_count = 0;
    bool inWord = false;
    for (char c : text) {
        if (std::isspace(c)) {
            inWord = false;
        } else {
            if (!inWord) {
                word_count++;
                inWord = true;
            }
        }
    }
    return word_count;
}

// Exercise 4
// replaceChar: return a NEW string where every occurrence of character
// 'from' is replaced by character 'to'.
// Example: replaceChar("banana", 'a', 'o') -> "bonono"
string replaceChar(const string& text, char from, char to) {
    // TODO: copy the string and swap matching characters.
    std::string copy(text);
    for (size_t i = 0; i < copy.length(); i++) {
        if (copy[i] == from) copy[i] = to;
    }
    return copy;
}

// ------------------------------------------------------------------------
// Section 3/4 - File Operations
// ------------------------------------------------------------------------

// Exercise 5
// writeLines: write each string in 'lines' to the file 'filename',
// one per line (each followed by a newline). Overwrite if it exists.
// Return true on success, false if the file could not be opened.
bool writeLines(const string& filename, const vector<string>& lines) {
    // TODO: open an ofstream, check is_open(), write each line + "\n".
    std::ofstream stream(filename);
    if(!stream.is_open()) return false;
    for (const std::string &line : lines) {
        //stream.write(line.c_str(), line.length());
        //stream.write("\n", 1);
        stream << line << "\n";
    }
    stream.close();
    return true;
}

// Exercise 6
// readLines: read every line from 'filename' into a vector<string>
// (without the trailing newline characters) and return it. If the file
// cannot be opened, return an empty vector.
vector<string> readLines(const string& filename) {
    vector<string> result;
    // TODO: open an ifstream, use getline() in a loop to fill 'result'.
    std::ifstream stream(filename);
    if (!stream.is_open()) return result;
    std::string line;
    while (std::getline(stream, line)) {
        result.emplace_back(line);
    }
    stream.close();
    return result;
}

// Exercise 7
// countLinesInFile: return the number of lines in the file. If the file
// cannot be opened, return -1.
int countLinesInFile(const string& filename) {
    // TODO: open the file, count lines with getline(). Return -1 on fail.
    std::ifstream stream(filename);
    if (!stream.is_open()) return -1;
    std::string line; size_t line_count = 0;
    while (std::getline(stream, line)) { line_count++; }
    stream.close();
    return line_count;
}

// ------------------------------------------------------------------------
// Section 4 - Challenge
// ------------------------------------------------------------------------

// Challenge A
// wordCountInFile: open 'filename', read all of it, and return the TOTAL
// number of words across all lines (words separated by spaces). If the
// file cannot be opened, return -1.
// Tip: you may reuse countWords() and readLines().
int wordCountInFile(const string& filename) {
    // TODO: read the file and sum the word counts of each line.
    auto lines = readLines(filename);
    if (lines.empty()) return -1;

    size_t word_count = 0;
    for (const std::string &line : lines) {
        word_count += countWords(line);
    }
    
    return word_count;
}

// Challenge B
// censorWord: read 'filename' line by line and return a single string
// (lines joined by '\n', no trailing newline) where every exact, whole
// occurrence of 'target' is replaced by a string of '*' the same length.
// For simplicity, treat the text as space-separated tokens: replace a
// token ONLY if it equals 'target' exactly (case-sensitive).
// If the file cannot be opened, return "" (empty string).
// Example: file "the cat sat" with target "cat" -> "the *** sat"
string censorWord(const string& filename, const string& target) {
    ifstream in(filename);
    if (!in.is_open()) return "";
    in.close();
 
    vector<string> lines = readLines(filename);
    string output;
    for (size_t li = 0; li < lines.size(); li++) {
        const string& line = lines[li];
        string rebuilt;
        string token;
        // walk the line and split on spaces, preserving single-space joins
        for (size_t i = 0; i <= line.size(); i++) {
            if (i == line.size() || line[i] == ' ') {
                if (!token.empty()) {
                    if (token == target)
                        rebuilt += string(target.size(), '*');
                    else
                        rebuilt += token;
                    token.clear();
                }
                if (i < line.size()) rebuilt += ' ';
            } else {
                token += line[i];
            }
        }
        output += rebuilt;
        if (li + 1 < lines.size()) output += "\n";
    }
    return output;
}

// ========================================================================
// main() - demonstrates your functions. You may edit freely to test.
// The autograder tests the functions above, not this main().
// ========================================================================
int main() {
    // ---- Section 1: Warm-up (5-10 min) ------------------------------
    // Goal: recall cin/cout, variables, simple arithmetic & conditions.

    // TODO (Warm-up 1): declare a string variable called 'name', ask the
    //   user "Enter your name: ", read it with getline, then print
    //   "Hello, <name>!".

    // TODO (Warm-up 2): declare two int variables a and b, read them from
    //   the user, and print their sum and which one is larger
    //   (or "equal").

    // ---- Demonstrations of implemented functions --------------------
    cout << "Vowels in 'Programming': " << countVowels("Programming") << "\n";
    cout << "Upper: " << toUpperCase("hello123") << "\n";
    cout << "Reverse: " << reverseString("hello") << "\n";
    cout << "Palindrome 'level': " << isPalindrome("level") << "\n";
    cout << "Words in '  hi   there  ': " << countWords("  hi   there  ") << "\n";
    cout << "Replace: " << replaceChar("banana", 'a', 'o') << "\n";

    vector<string> demo = {"line one", "line two", "the cat sat"};
    writeLines("demo.txt", demo);
    cout << "Lines in demo.txt: " << countLinesInFile("demo.txt") << "\n";
    cout << "Words in demo.txt: " << wordCountInFile("demo.txt") << "\n";
    cout << "Censored: " << censorWord("demo.txt", "cat") << "\n";

    return 0;
}
