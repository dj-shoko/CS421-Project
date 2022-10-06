#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 12
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: 
// RE:   **

bool word (string s)
{
  int state = 0;
  int charpos = 0;
  /* replace the following todo the word dfa  **
  while (s[charpos] != '\0') 
    {
      if (state == 0 && s[charpos] == 'a')
      state = 1;
      else
      if (state == 1 && s[charpos] == 'b')
      state = 2;
      else
      if (state == 2 && s[charpos] == 'b')
      state = 2;
      else
	  return(false);
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
  */
}

// PERIOD DFA 
// Done by: Raymond Quach
bool period (string s)
{  // complete this **
  //If the string is a period, return true
  if (s == ".")
    return true;
  else
    return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Raymond Quach

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS,
OBJECT, SUBJECT, DESTINATION,
PRONOUN, PRONOUN, PRONOUN, PRONOUN, PRONOUN,
CONNECTOR, CONNECTOR, CONNECTOR, CONNECTOR,
WORD1, WORD2, PERIOD, ERROR,
EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {
"masu", "masen", "mashita", "masendeshita", "desu", "deshita", //Verbs
"o", "wa", "ni", //Particles
"watashi", "anata", "kare", "kanojo", "sore", //Pronouns
"mata", "soshite", "shikashi", "dakara" //Connector
"eofm" //End of File Marker
}; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.


// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Raymond Quach
int scanner(tokentype& tt, string& w)
{

  // ** Grab the next word from the file via fin
  fin >> w;
  int finalChar = w.length() - 1; //Final character of the string

  // 1. If it is eofm, return right now.   
  if (w == "eofm")
    return 0;

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
     3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.
     4. Return the token type & string  (pass by reference)
  */
  if (word(w)) {
    //Reserved List Check
    if (w == tokenName[0]) //Check if the word is a verb
      the_type = VERB;
    else if (w == tokenName[1]) //Check if the word is a verb negative
      the_type = VERBNEG;
    else if (w == tokenName[2]) //Check if the word is a verb past
      the_type = VERBPAST;
    else if (w == tokenName[3]) //Check if the word is a verb past negative
      the_type = VERBPASTNEG;
    else if (w == tokenName[4]) //Check if the word is "is"
      the_type = IS;
    else if (w == tokenName[5]) //Check if the word is "was"
      the_type = WAS;
    else if (w == tokenName[6]) //Check if the word is a object
      the_type = OBJECT;
    else if (w == tokenName[7]) //Check if the word is a subject
      the_type = SUBJECT;
    else if (w == tokenName[8]) //Check if the word is a destination
      the_type = DESTINATION;
    for (int i = 9; i < 13; i++) { //Check if the word is a pronoun
      if (w == tokenName[i]) {
        the_type = PRONOUN;
        break;
      }
    }
    for (int i = 14; i < 17; i++) { //Check if the word is a connector
      if (w == tokenName[i]) {
        the_type = CONNECTOR;
        break;
      }
    }
    //If the word is none of the reserved words, then it should be WORD1 or WORD2
    //WORD1 scenario
    else if (w[finalChar] == "a" || w[finalChar] == "e" || w[finalChar] == "i" ||
    w[finalChar] == "o" || w[finalChar] == "u") {
      the_type = WORD1;
    }
    //WORD2 scenario
    else if (w[finalChar] == "E" || w[finalChar] == "I") {
      the_type = WORD2;
    }
  }
  else if (period(w)) //Check if it is a period
    the_type = PERIOD;
  else //If it is not a word or period, then it is an error
      the_type = ERROR;
}//the end of scanner



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

