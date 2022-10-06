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
enum tokentype {
VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS,
OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR,
WORD1, WORD2, PERIOD, ERROR,
EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {
"VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS",
"OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR",
"WORD1", "WORD2", "PERIOD", "ERROR",
"EOFM"
}; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.

string reservedwords[30] = {
  "masu", "masen", "mashita", "masendeshita", "desu", "deshita", //Verbs
  "o", "wa", "ni", //Particles
  "watashi", "anata", "kare", "kanojo", "sore", //Pronouns
  "mata", "soshite", "shikashi", "dakara" //Connector
  "eofm" //End of File Marker
}; 

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Raymond Quach
int scanner(tokentype& tt, string& w)
{ // ** Grab the next word from the file via fin
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

  //Call word function and if it is a word,
  //then check if it is a reserved word.
  //If it is then return the type,
  //else return if it is WORD1 or WORD2.
  if (word(w)) {
    //Reserved List Check
    bool resCheck = false;
    for (int i = 0; i < 19; i++) {
	    if (w == reservedwords[i]) {
        //If it is a reserved word, match the type
        switch (i) {
          case 0: //If the word is "masu"
            the_type = VERB;
            break;
          case 1: //If the word is "masen"
            the_type = VERBNEG;
            break;
          case 2: //If the word is "mashita"
            the_type = VERBPAST;
            break;
          case 3: //If the word is "masendeshita"
            the_type = VERBPASTNEG;
            break;
          case 4: //If the word is "desu"
            the_type = IS;
            break;
          case 5: //If the word is "deshita"
            the_type = WAS;
            break;
          case 6: //If the word is "o"
            the_type = OBJECT;
            break;
          case 7: //If the word is "wa"
            the_type = SUBJECT;
            break;
          case 8: //If the word is "ni"
            the_type = DESTINATION;
            break;
          //If the word is "watashi", "anata", "kare", "kanojo", or "sore"
          case 9: case 10: case 11: case 12: case 13:
            the_type = PRONOUN;
            break;
          //If the word is "mata", "soshite", "shikashi", or "dakara"
          case 14: case 15: case 16: case 17:
            the_type = CONNECTOR;
            break;
          case 18: //This should never happen...
            the_type = EOFM;
            break;
          default: //I sure as hell hope this never happens...
            the_type = ERROR;
            break;
        }
        //Since it is a reserved word, mark it as one
        resCheck = true;
        break; //Break out of the loop
      }
    }
	  
    //If the word is none of the reserved words, then it should be WORD1 or WORD2
    if (!resCheck) {
      //WORD1 scenario
      if (w[finalChar] == "a" || w[finalChar] == "e" || w[finalChar] == "i" ||
      w[finalChar] == "o" || w[finalChar] == "u")
        the_type = WORD1;
      //WORD2 scenario
      else if (w[finalChar] == "E" || w[finalChar] == "I")
        the_type = WORD2;
    }
  }

  //Check if it is a period, if it is then mark it as such
  else if (period(w)) 
    the_type = PERIOD;
  
  else //If it is neither a word nor a period, then it is an error
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
