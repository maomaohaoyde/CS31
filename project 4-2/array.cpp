#include <iostream>
#include <string>
#include <cassert>
using namespace std;
int appendToAll(string a[], int n, string value)
{   //n can't be negative
    if (n<0)
    return -1;
    //add value to each of string in the array
    for (int i=0; i<n; i++) {
        a[i]+=value;
    }
    return n;
}

int lookup(const string a[], int n, string target)
{   //scan through every string to find the first match
    for (int i=0; i<n; i++) {
    if (a[i]==target)
        return i;
    
}
    //whatever the other situations are, return -1
    return -1;
}

int positionOfMax(const string a[], int n)
{   int j=0;
    //initialize max to the first string
    string max=a[0];
    //n can be negative
    if (n<=0)
        return -1;
    //compare each string in the rest of the array
    //if the string is larger
    //set max to that string
    //j is used to record the position of maxium string
    for (int i=1; i<n; i++) {
        if (a[i]>max) {
            max=a[i];
            j=i;
        }
    }
    return j;
}

int rotateLeft(string a[], int n, int pos)
{   //position can't be larger than the position of the last string
    //it doesn't make sense if the array is empty
    //n can't be negative
    if (pos>n-1 || n<=0)
        return -1;
    //store the value of designated string
    string desi=a[pos];
    for (int i=pos; i<n-1; i++) {
        a[i]=a[i+1];
    }
    //set the last string in the array to the stored value
    a[n-1]=desi;
    return pos;
}

int rotateRight(string a[], int n, int pos)
{   //position can't be larger than the position of the last string
    //it doesn't make sense if the array is empty
    //n can't be negative
    if (pos>n-1 || n<=0)
        return -1;
    //store the value of designated string
    string desi=a[pos];
    for (int i=pos; i>0; i--) {
        a[i]=a[i-1];
    }
    //set the first string in the array to the stored value
    a[0]=desi;
    return pos;
}
int flip(string a[], int n)
{   //n can't be negative
    if (n<0)
    return -1;
    //a string to store the value temporarily
    string temp;
    for (int i=0; i<n/2; i++) {
    //exchange the strings that are symmetrical to the mid of the array
        temp=a[i];
        a[i]=a[n-1-i];
        a[n-1-i]=temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    //neither of n1 nor n2 can be negative
    if (n1<0 || n2<0) {
        return -1;
    }
    int n;
    //choose the smaller of n1 and n2
    if (n1<=n2)
        n=n1;
    else
        n=n2;
    //compare the first n strings in the array
    for (int i=0; i<n; i++)
        if (a1[i]!=a2[i])
            return i;
    return n;
    
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{   //n2 can't be larger than n1
    //neither of n1 nor n2 can be negative
    if (n1<0 || n2<0 || n1<n2)
        return -1;
    bool iden=false;
    //if a2 is empty, it is the substring of a1,return postion 0
    if (n2==0)
        return 0;
    for(int i=0;i<n1;i++)
    {
            for (int j=0;j<n2;j++)
                //if find first match of string check the following n2-1 terms
                if(a1[i]==a2[j])
                {
                    iden=true;
                    for (int k=1; k<n2; k++)
                    {
                        if (a1[i+k]!=a2[j+k]) {
                            iden=false;
                        }
                    }
            if(iden)
                return i;
                }
    }
    
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{   //n2 can't be larger than n1
    //neither of n1 nor n2 can be negative
    if (n1<0 || n2<0 || n1<n2)
        return -1;
    //compare every string in two arrays
    for(int i=0;i<n1;i++)
        for (int j=0; j<n2; j++)
        {
            if (a1[i]==a2[j])
            {
                return i;
            }
        }
    return -1;
}

int separate(string a[], int n, string separator)
{   //n can't be negative
    if (n<0)
    return -1;
    string temp;
    //sort the array in an order from the smallest to the largest
    for(int i=0;i<n;i++)
for(int j=0;j<n-1-i;j++)
if(a[j]>a[j+1])
{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
}
    //find the first string that is not smaller than separator
    for (int i=0; i<n; i++)
    {
        if (a[i]>=separator)
            return i;
 
    }
    //if separator is larger than all the strings in the array
    return n;
}

int main()
{
    string h[7] = { "glenn", "carl", "carol", "rick", "", "maggie", "daryl" };
    assert(lookup(h, 7, "maggie") == 5);
    assert(lookup(h, 7, "carol") == 2);
    assert(lookup(h, 2, "carol") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "glenn", "carl", "rick", "maggie" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "glenn?" && g[3] == "maggie?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "rick?" && g[3] == "carl?");
    
    string e[4] = { "carol", "rick", "", "maggie" };
    assert(subsequence(h, 7, e, 4) == 2);
    assert(rotateRight(e, 4, 1) == 1 && e[0] == "rick" && e[2] == "");
    
    string f[3] = { "rick", "carol", "tara" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tara" && f[2] == "rick");
    assert(separate(h, 7, "daryl") == 3);
    
    
    cout << "All tests succeeded" << endl;
}
