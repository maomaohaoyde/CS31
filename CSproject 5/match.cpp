#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

const int MAX_WORD_LENGTH = 20;

int standardizeRules (int distance[], char word1[][MAX_WORD_LENGTH+1],char word2[][MAX_WORD_LENGTH+1],int nRules)
{   if (nRules<0) // treat non-positive number of rules as 0
{
    nRules=0;
}
    for (int i=0; i<nRules; i++)
    {
        bool badRule = !word1[i][0]||!word2[i][0]|| distance[i]<1; // Apply deletion qualifiers : zero length?
        //strcmp(word1[i], "");
        for (int char_index = 0; word1[i][char_index]; char_index++) // Any non-alpha char(s)?(convert tolower otherwise)
        {
            badRule |= !isalpha(word1[i][char_index]);
            word1[i][char_index]=tolower(word1[i][char_index]);
        }
        for (int char_index = 0; word2[i][char_index]; char_index++)// Any non-alpha char(s)?(convert tolower otherwise)
            
        {
            badRule |= !isalpha(word2[i][char_index]);
            word2[i][char_index]=tolower(word2[i][char_index]);
        }
        bool repetition;
        for (int backward=i-1; !badRule && backward>=0; backward--)// Any repetition of word?
        {
            repetition=(!strcmp(word1[i], word1[backward])&& !strcmp(word2[i], word2[backward]))||(!strcmp(word1[i], word2[backward])&& !strcmp(word2[i], word1[backward]));
            badRule |= repetition;
            if (repetition && distance[i]>distance[backward])// If there is a repetition, put the smaller distance to the rule of deletion
            {
                distance[backward]=distance[i];
            }
        }
        if (badRule)  //deletion of the bad rule
        {
            strcpy(word1[i], word1[nRules-1]);
            strcpy(word2[i], word2[nRules-1]);
            distance[1]=distance[nRules-1];
            nRules--;
            i--;
        }
        
    }
    return nRules;
}
int determineQuality(const int distance[],
                     const char word1[][MAX_WORD_LENGTH+1],
                     const char word2[][MAX_WORD_LENGTH+1],
                     int nRules,
                     const char document[])
{
    const int MAX_DOC=200;
    char cleardoc[MAX_DOC+1];
    int Index=0,nMatch=0;
    for (int docIndex=0; document[docIndex]; docIndex++)
    {
        if (isalpha(document[docIndex])||document[docIndex]==' ')//delete other characters
        {
            cleardoc[Index]=tolower(document[docIndex]);
            Index++;
        }
        
    }
    char words[MAX_DOC+1][MAX_WORD_LENGTH]={};
    int wordCount=0,letterCount=0;
    for (int i=0; i<Index; i++)// put the cleared document into a 2D array
    {   if (isalpha(cleardoc[i]))
     {
        words[wordCount][letterCount]=cleardoc[i];
        letterCount++;
     }
        else if(letterCount)//when one or more spaces are met, start a new array of characters
        {
            wordCount++;
            letterCount=0;
        }
    }
    for (int rule=0; rule<nRules; rule++)//compare each word in 2D array with the words in rules
    {
        bool match=false;
        for (int i=0; i<wordCount; i++)
        {   for(int k=1;k<distance[rule]+1;k++)//the distance k is less than or equal to assigned distance
        {
            match|=((!strcmp(word1[rule], words[i]))&&(!strcmp(word2[rule], words[i+k])))||(!strcmp(word2[rule], words[i])&&(!strcmp(word1[rule], words[i+k])));
        }
        }
        nMatch+=match;
    }
    return nMatch;
}

int main()
{
    const int TEST1_NCRITERIA = 4;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    cout<<determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                           "The mad UCLA scientist unleashed a deranged evil giant robot.")<<endl;
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed    a deranged robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "**** 2014 ****") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "  That plot: NEFARIOUS!") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "deranged deranged robot deranged robot robot") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "Two mad scientists suffer from deranged-robot fever.") == 0);
    cout << "All tests succeeded" << endl;
}