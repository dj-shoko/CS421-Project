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
// Done by: Raymond Quach
// RE:   **

bool word (string s)
{
  int state = 0;
  int charpos = 0;

  //Currently hardcoded/placeholder, based on NFA diagram
  while (s[charpos] != '\0') 
    {
      //State 0 block
      //Check if it is a vowel state
      if (state == 0 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;
      
      //Consanant check, non-pair state
      else if (state == 0 && (s[charpos] == 'd' || s[charpos] == 'j' ||
      s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
        state = 2;

      //Consanant check, pair allowed state
      else if (state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' ||
      s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' ||
      s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r'))
        state = 3;

      //Special consanant in case of "ch" state
      else if (state == 0 && s[charpos] == 'c')
        state = 4;
      
      //Consanant 's' case this is a consonant pair state
      else if (state == 0 && s[charpos] == 's')
        state = 5;
        
      //Consanant 't' case this is a consonant pair state
      else if (state == 0 && s[charpos] == 't')
        state = 6;
      //End of state 0 block



      //State 1 Block
      //Check if it is a vowel state
      else if (state == 1 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;
      
      //Consanant check, non-pair state
      else if (state == 1 && (s[charpos] == 'd' || s[charpos] == 'j' ||
      s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
        state = 2;

      //Consanant check, pair allowed state
      else if (state == 1 && (s[charpos] == 'b' || s[charpos] == 'g' ||
      s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' ||
      s[charpos] == 'p' || s[charpos] == 'r'))
        state = 3;

      //Special consanant in case of "ch" state
      else if (state == 1 && s[charpos] == 'c')
        state = 4;
      
      //Consanant 's' case this is a consonant pair state
      else if (state == 1 && s[charpos] == 's')
        state = 5;
        
      //Consanant 't' case this is a consonant pair state
      else if (state == 1 && s[charpos] == 't')
        state = 6;

      //Is it a vowel followed up by an n
      else if (state == 1 && s[charpos] == 'n')
        state = 1;
      //End of state 1 Block



      //State 2 Block (Consonant Scenarios or consonant pairs if they are such)
      //Check if it is a vowel
      else if (state == 2 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;
      //End of state 2 Block
    


      //State 3 Block (Consonants that can be pairs)
      else if (state == 3 && s[charpos] == 'y')
        state = 2;
      else if (state == 3 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;
      //End of state 3 Block



      //State 4 Block (char 'c')
      else if (state == 4 && s[charpos] == 'h')
        state = 2;
      //End of state 4 Block



      //State 5 Block (char 's')
      else if (state == 5 && s[charpos] == 'h')
        state = 2;
      else if (state == 5 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;
      //End of state 5 Block



      //State 6 Block (char 't')
      else if (state == 6 && s[charpos] == 's')
        state = 2;
      else if (state == 6 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' ||
      tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
        state = 1;
      //End of state 6 Block
      else {
        //Debugging
        //if (s != ".")
        //  cout << "DEBUG:\nString: " << s << ", Char: " << s[charpos] << charpos << endl;
	      return(false);
      }
      charpos++;
    }

  // where did I end up????
  if (state == 1) return(true);  // end in a final state
   else return(false);
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

  //Call word function and if it is a word,
  //then check if it is a reserved word.
  //If it is then return the type,
  //else return if it is WORD1 or WORD2.
  if (word(w)) {
    //Reserved List Check
    bool resCheck = false; //Variable to determine if it is a reserved word or not
    for (int i = 0; i < 19; i++) {
      if (w == reservedwords[i]) {
        //If it is a reserved word, match the type
        switch (i) {
          case 0: //If the word is "masu", return type as "VERB"
            tt = VERB;
            break;
          case 1: //If the word is "masen", return type as "VERBNEG"
            tt = VERBNEG;
            break;
          case 2: //If the word is "mashita", return type as "VERBPAST"
            tt = VERBPAST;
            break;
          case 3: //If the word is "masendeshita", return type as "VERBPASTNEG"
            tt = VERBPASTNEG;
            break;
          case 4: //If the word is "desu", return type as "IS"
            tt = IS;
            break;
          case 5: //If the word is "deshita", return type as "WAS"
            tt = WAS;
            break;
          case 6: //If the word is "o", return type as "OBJECT"
            tt = OBJECT;
            break;
          case 7: //If the word is "wa", return type as "SUBJECT"
            tt = SUBJECT;
            break;
          case 8: //If the word is "ni", return type as "DESTINATION"
            tt = DESTINATION;
            break;
          //If the word is "watashi", "anata", "kare", "kanojo", or "sore",
          //return type as "PRONOUN"
          case 9: case 10: case 11: case 12: case 13:
            tt = PRONOUN;
            break;
          //If the word is "mata", "soshite", "shikashi", or "dakara",
          //return type as "CONNECTOR
          case 14: case 15: case 16: case 17:
            tt = CONNECTOR;
            break;
          case 18: //This should never happen...
            tt = EOFM;
            break;
          default: //I sure as hell hope this never happens...
            tt = ERROR;
            break;
        }
        //Since it is a reserved word, mark it as one
        resCheck = true;
        break;
      }
    }
	  
    //If the word is none of the reserved words, then it should be WORD1 or WORD2
    if (!resCheck) {
      //WORD1 scenario
      if (w[finalChar] == 'a' || w[finalChar] == 'e' || w[finalChar] == 'i' ||
      w[finalChar] == 'o' || w[finalChar] == 'u' || w[finalChar] == 'n')
        tt = WORD1;
      //WORD2 scenario
      else if (w[finalChar] == 'E' || w[finalChar] == 'I')
        tt = WORD2;
    }
  }

  //Check if it is a period, if it is then mark it as such
  else if (period(w)) 
    tt = PERIOD;
  
  else //If it is neither a word nor a period, then it is an error
    tt = ERROR;
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
