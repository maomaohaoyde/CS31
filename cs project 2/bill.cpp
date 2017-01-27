

#include <iostream>
#include <string>
using namespace std;
int main()
{
    int minutesUsed,textMessages,monthNumber;
    cout<<"Minutes used: ";
    cin>>minutesUsed;
    if (minutesUsed < 0)
    {
        cout<<"---"<<endl<<"The number of minutes used must be nonnegative."<<endl;
        return 1;
    }
    
    cout<<"Text messages: ";
    cin>>textMessages;
    if (textMessages < 0)
    {
        cout<<"---"<<endl<<"The number of text messages must be nonnegative."<<endl;
        return 1;
    }
    
    cout<< "Customer name: ";
    string customerName;
    cin. ignore (10000, '\n');
    getline(cin, customerName);
    if (customerName == "")
    {
        cout<<"---"<<endl<<"You must enter a customer name."<<endl;
        return 1;
    }
    
    cout<<"Month number (1=Jan, 2=Feb, etc.): ";
    cin>>monthNumber;
    if (monthNumber < 1 ||monthNumber > 12)
    {
        cout<<"---"<<endl<<"The month number must be in the range 1 through 12."<<endl;
        return 1;
    }
    
    
    
    cout<<"---"<<endl;
    double bill= 40.00;
    if (minutesUsed > 500)
        bill = bill + 0.45 * (minutesUsed - 500);
    if (textMessages > 400)
    {
        bill = bill + 0.11 * (textMessages - 400);
        textMessages = 400;
    }
    if (textMessages > 200)
    {
        if (monthNumber >= 10 || monthNumber<=5)
            bill = bill + 0.03 * (textMessages - 200);
        else bill = bill + 0.02 * (textMessages - 200);
    }
    cout.setf( ios:: fixed);
    cout.precision (2);
    cout<<"The bill for "<<customerName<<" is $"<<bill<<endl;
}