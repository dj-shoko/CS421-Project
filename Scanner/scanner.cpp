#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define DEBUG "DEBUG: RESERVED WORD TYPE IS "

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 12
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: Raymond Quach
// RE:   **

bool word (string s)
{
  int state = 0; // Initialize the state as 0 as the starting state
  int charpos = 0; // Initialize the character position as the first letter in string

  // Loop to go through each letter in the string
  while (s[charpos] != '\0')
    {
      // State 0 block
      // Check if it is a vowel state
      if (state == 0 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;

      // Consanant check, non-pair state
      else if (state == 0 && (s[charpos] == 'd' || s[charpos] == 'j' ||
      s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
        state = 2;

      // Consanant check, pair allowed state
      else if (state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' ||
      s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' ||
      s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r'))
        state = 3;

      // Special consanant in case of "ch" state
      else if (state == 0 && s[charpos] == 'c')
        state = 4;

      // Consanant 's' case this is a consonant pair state
      else if (state == 0 && s[charpos] == 's')
        state = 5;

      // Consanant 't' case this is a consonant pair state
      else if (state == 0 && s[charpos] == 't')
        state = 6;
      // End of state 0 block



      // State 1 block
      // Check if it is a vowel state
      else if (state == 1 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;

      // Consanant check, non-pair state (qsa)
      else if (state == 1 && (s[charpos] == 'd' || s[charpos] == 'j' ||
      s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
        state = 2;

      // Consanant check, pair allowed state
      else if (state == 1 && (s[charpos] == 'b' || s[charpos] == 'g' ||
      s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' ||
      s[charpos] == 'p' || s[charpos] == 'r'))
        state = 3;

      // Special consanant in case of "ch" state
      else if (state == 1 && s[charpos] == 'c')
        state = 4;

      // Consanant 's' case this is a consonant pair state
      else if (state == 1 && s[charpos] == 's')
        state = 5;

      // Consanant 't' case this is a consonant pair state
      else if (state == 1 && s[charpos] == 't')
        state = 6;

      // Is it a vowel followed up by an n
      else if (state == 1 && s[charpos] == 'n') {
        if (s[charpos-1] != 'n') // If it is a vowel+'n'
          state = 1;
        else // If it was previously a vowel+'n' followed up by another 'n'
          state = 3;
      }

      // Consonant Pair State Block
      else if (state == 3 && s[charpos] == 'y' ||
      (state == 4 || state == 5) && s[charpos] == 'h' ||
      state == 6 && s[charpos] == 's')
        state = 2;
      // End of state 1 block



      // State 2 block
      //Is any consonant followed up by a vowel?
      else if ((state == 2 || state == 3 || state == 4 || state == 5 || state == 6) &&
      (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;
      // End of state 2 block



      else {
        // Debugging
        // if (s != ".")
        //  cout << "DEBUG:\n\tString: " << s << ", Char: " << s[charpos] << charpos << endl;
	      return(false);
      }
      charpos++;
    }

  // where did I end up????
  if (state == 1) // end in a final state
    return(true);
  else
    return(false);
}

// PERIOD DFA
// Done by: Raymond Quach
bool period (string s)
{
  // complete this **
  //If the string is a period, return true
  if (s == ".")
    return true;
  else //If the string is not a period, return false
    return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Raymond Quach

// Table for the token type.
enum tokentype {
VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS,
OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR,
WORD1, WORD2, PERIOD, ERROR,
EOFM};

// String table for the display names of tokens, same order as "tokentype" table
string tokenName[30] = {
"VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS",
"OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR",
"WORD1", "WORD2", "PERIOD", "ERROR",
"EOFM"
};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.

// String table for reserved words
string reservedwords[30] = {
  "masu", "masen", "mashita", "masendeshita", "desu", "deshita", //Verbs
  "o", "wa", "ni", //Particles
  "watashi", "anata", "kare", "kanojo", "sore", //Pronouns
  "mata", "soshite", "shikashi", "dakara", //Connector
  "eofm" //End of File Marker
};

// ------------ Scanner and Driver -----------------------

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Raymond Quach
int scanner(tokentype& tt, string& w)
{
  // Grab the next word from the file via fin
  fin >> w;

  // If the word is "eofm" then return right now.
  if (w == "eofm")
    return 0;

  // Check if it is a period, return the type as period if it is.
  else if (period(w))
    tt = PERIOD;

  // Call word function and if it is a word
  // And if it is then check if it is a reserved word.
  // If it is a reserved word then return the type.
  // If it is not then return the type as either WORD1 or WORD2.
  else if (word(w)) {
    //Reserved List Check
    for (int i = 0; i < 19; i++) {
      if (w == reservedwords[i]) {
        //If it is a reserved word, match the type
        switch (i) {
          case 0: //If the word is "masu", return type as "VERB"
            tt = VERB;
            return 0;
          case 1: //If the word is "masen", return type as "VERBNEG"
            tt = VERBNEG;
            return 0;
          case 2: //If the word is "mashita", return type as "VERBPAST"
            tt = VERBPAST;
            return 0;
          case 3: //If the word is "masendeshita", return type as "VERBPASTNEG"
            tt = VERBPASTNEG;
            return 0;
          case 4: //If the word is "desu", return type as "IS"
            tt = IS;
            return 0;
          case 5: //If the word is "deshita", return type as "WAS"
            tt = WAS;
            return 0;
          case 6: //If the word is "o", return type as "OBJECT"
            tt = OBJECT;
            return 0;
          case 7: //If the word is "wa", return type as "SUBJECT"
            tt = SUBJECT;
            return 0;
          case 8: //If the word is "ni", return type as "DESTINATION"
            tt = DESTINATION;
            return 0;
          //If the word is "watashi", "anata", "kare", "kanojo", or "sore",
          //return type as "PRONOUN"
          case 9: case 10: case 11: case 12: case 13:
            tt = PRONOUN;
            return 0;
          //If the word is "mata", "soshite", "shikashi", or "dakara",
          //return type as "CONNECTOR
          case 14: case 15: case 16: case 17:
            tt = CONNECTOR;
            return 0;
          case 18: //This should never happen...
            cout << DEBUG << "EOFM" << endl;
            tt = EOFM;
            return 0;
          default: //I sure as hell hope this never happens...
            cout << DEBUG << "ERROR" << endl;
            tt = ERROR;
            return 0;
        }
      }
    }

    int finalChar = w.length() - 1; // Final character of the string

    // If the word is none of the reserved words, then it should be WORD1 or WORD2
    // WORD1 scenario (if it ends with a lower case vowel or vowel+'n')
    if (w[finalChar] == 'a' || w[finalChar] == 'e' || w[finalChar] == 'i' ||
    w[finalChar] == 'o' || w[finalChar] == 'u' || w[finalChar] == 'n')
      tt = WORD1;
    // WORD2 scenario (if it ends with an uppercase 'E' or 'I'
    else if (w[finalChar] == 'E' || w[finalChar] == 'I')
      tt = WORD2;
  }

  else // If it is neither a word nor a period, then it is an error
    tt = ERROR;
} //the end of scanner



// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Louis
int main()
{
  tokentype thetype;
  string theword;
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;
    }

   cout << "End of file is encountered." << endl;
   fin.close();
}// end
