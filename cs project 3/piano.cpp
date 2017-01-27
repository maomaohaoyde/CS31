#include <iostream>
#include <string>
using namespace std;

//create a function that tests if the character is one of capital letters from 'A' to 'G'
//return a bool value
bool isABCDEFG(char a)
{
    switch (a) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
            return true;
            
        default:
            return false;
    }
}

//create a function that returns integer value of characters '1','2','3','4','5','6'
int translateNumbers(char b)
{
    switch (b) {
            
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '1':
            return 1;
        case '6':
            return 6;
        default:
            return 0;
    }


}

char translateNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** translateNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}


bool isTuneWellFormed(string tune)
{   int i;
    // an empty string is well-formed
    if(tune=="")
        return true;
    //the last character must be a slash
    if (tune[tune.size()-1]!='/')
        return false;
    //the first character should be either one of the capital letters from 'A' to 'G' or a slash
    if ((!isABCDEFG(tune[0])) && tune[0]!='/' )
        return false;
    for (i=1;i<tune.size()-1 ; i++) {
    //the characters in the middle can be one of the capital letters from 'A' to 'G'
        if (isABCDEFG(tune[i]));
    //or '#' or 'b' following one of the capital letters from 'A' to 'G'
        else  if ((tune[i]== '#'|| tune[i]=='b')&&(isABCDEFG(tune[i-1])));
    //or a digit following either '#' or 'b' or one of the capital letters from 'A' to 'G'
        else if (isdigit(tune[i])&& (tune[i-1]=='#' || (tune [i-1]== 'b' ||(isABCDEFG(tune[i-1])))));
    //or a slash
        else if (tune[i]=='/');
        else return false;
        
    }return true;
}


//define a function that returns if the tune is playable when it is well-formed
bool isPlayable(string tune, int& badnote)
{   int i;
    for (i=0; i<tune.size(); i++) {
        if (isdigit(tune[i]))
            //digits should be 2,3,4,5 except "Cb2" is not playable
            if ((translateNumbers(tune[i])<=5 && translateNumbers(tune[i])>=2) && (tune[i-1]!='b'|| tune[i-2]!='C'));
        //"C6" is playable
            else if (tune[i]=='6' && tune[i-1]=='C');
        //"Cb6" is playable
            else if (tune[i]=='6' && tune[i-1]=='b' && tune[i-2]=='C');
        // "B#1" is playable
            else if (tune[i]=='1' && tune[i-1]=='#' && tune[i-2]=='B');
        //otherwise tune is not playable
            else { badnote=i;
                return false;}
    }
    return true;}

int translateTune(string tune, string& instructions, int& badBeat)
{
    //h is the counter for string bracket
    //c records the badbeat
    //k is the counter for while loop
    //j is the counte for recording "[]"
    int j=0,k=0,h=0,c=0;
    bool a=false;
    //create a string that records if each beat needs "[]" when the tune is translated
    string bracket="";
    //count the number of '/'s (number of beats)

    // record if each beat needs "[]" when the tune is translated into the string
    // '1' stands for "[]" need; '0' stands for otherwise
    for (int i=0; i<tune.size(); i++) {
        if(isABCDEFG(tune[i]))
            j++;
        if (tune[i]=='/' ) {
            if (j>1)
                bracket+='1';
            else
                bracket+='0';
            j=0; }}
    
    
    //first situation: when the tune is both well-formed and playable
    if (isTuneWellFormed(tune)&& isPlayable(tune,c)) {
        instructions="";
        if (tune[0]=='/') {
            instructions+=' ';
            h++;
            k++;
        }
        while (k<tune.size()) {
            //print "["s
            if (bracket[h]=='1' && !a)
            { instructions+='[';
                a=true;
            }
            //print "]"s
            if (tune[k]=='/')
            {    h++;
                if (a) {
                    instructions+=']';
                a=false;
                }
                if (tune[k-1]=='/') {
                    instructions+=' ';
                }
                k++;
                }
                else {
                    //since the first character is not a slash, it's a letter
                    //octave is initialized as 4
                    int octave=4;
                char noteLetter=tune[k],accidentalSign=' ';
                    //if the next character is a digit, octave is that digit
                if (isdigit(tune[k+1])) {
                    octave=translateNumbers(tune[k+1]);
                    instructions+=translateNote(octave,noteLetter,accidentalSign);
                    k+=2;
                }
                    //if the next character is either of a '#' or a 'b' followed by a digit
                else if ((tune[k+1]=='#' || tune[k+1]=='b')&& isdigit(tune[k+2]))
                {
                    accidentalSign=tune[k+1];
                    octave=translateNumbers(tune[k+2]);
                    instructions+=translateNote(octave,noteLetter,accidentalSign);

                    k+=3;
                }
                    // if the next character is either of a '#' or a 'b'
                else if (tune[k+1]=='#' || tune[k+1]=='b')
                {accidentalSign=tune[k+1];
                    instructions+=translateNote(octave,noteLetter,accidentalSign);
                    k+=2;
                }
                    //otherwise the octave is regarded as 4 as initialized
                else
                {
                    instructions+=translateNote(octave,noteLetter,accidentalSign);
                    k++;
                }
            }
            
        }
        // after translation, return 0 for the first situation
        return 0;
    }
    //second situation: the input is not well-formed
    //return 1
    else if (!isTuneWellFormed(tune))
        return 1;
    //third situation: the input is well-formed but not playable
    else { badBeat=1;
        for (int o=0; o<tune.size();o++)
        {
            //c records where first unplayable note is
            if (o==c)
            break;
            //badBeat records the number of beat
            if (tune[o]=='/')
                badBeat++;
        }
        return 2;
        
    }
}


int main()
{
   string t;
    getline(cin,t);
  string instrs;
   int bb;
   switch (translateTune(t,instrs,bb))
   { case 0:
   cout<<"the translation is "<< instrs<<endl;
    break;
   case 1:
    cout<<"The tune is not well-formed." <<endl;
    break;
   case 2:
 cout<<"Not playable; first bad beat number is "<<bb <<endl;
    break;
   default:
     cout<<"Internal program error! We shouldn't get there" <<endl;
       break;}

    
}
