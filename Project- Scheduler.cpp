#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<string>
#include <thread>
#include <chrono>
#include<sstream>
using namespace std;
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
string checker;
char c;
bool b=true;
void pointer(int x)
{
    int count=x;
    string dots=".........";
    cout << "\033[?25l";
    int size=dots.size();
    for(int i=0; i<count; i++)
    {
        for (int i=0; i<size; i++)
        {
            char c=dots[i];
            cout <<YELLOW << c <<RESET;
            this_thread::sleep_for(chrono::milliseconds(80));
        }
        this_thread::sleep_for(chrono::milliseconds(40));
        for (int i=size-1; i>=0; i--)
        {
            cout << "\b \b" ;
            this_thread::sleep_for(chrono::milliseconds(80));
        }

    }
    for (int i=0; i<size; i++)
    {
        char c=dots[i];
        cout <<YELLOW << c <<RESET;
        this_thread::sleep_for(chrono::milliseconds(80));
    }
    this_thread::sleep_for(chrono::milliseconds(200));
    cout<<endl;
    char a = 176, b = 219;
    for (int i = 0; i <= 30; i++)
    {
        cout << "\r";
        for (int j = 0; j < i; j++)
            cout <<YELLOW << b <<RESET;

        for (int j = i; j < 30; j++)
            cout <<YELLOW << a <<RESET;
        cout <<YELLOW<< (i * 100) / 30<< "%" <<RESET << flush;
        this_thread::sleep_for(chrono::milliseconds(80));
    }
    this_thread::sleep_for(chrono::milliseconds(50));
    cout<<endl;
    cout << "\033[?25h";
}

void addSchedule()
{
    int actCount;
    int hour;
    int minute;
    cout << "\033[?25l";
    string message = "WELCOME TO SCHEDULER PROGRAM";
    stringstream ss;
    int size=message.size();
    for (int i=0; i<size; i++)
    {
        char c=message[i];
        cout <<GREEN << c <<RESET;
        this_thread::sleep_for(chrono::milliseconds(60));
    }
    string teacherName;
    cout << "\033[?25h";
    cout<<endl<<"Enter teacher's name: ";
    cin.ignore();
    getline(cin, teacherName);
    while(teacherName.size()>200)
    {
        cout<<"Invalid input, try again"<<endl;
        getline(cin,teacherName);
    }
    ifstream name("namelist.txt");
    vector<string>namelist;
    string temp;
    while(getline(name,temp))
    {
        namelist.push_back(temp);
    }
    name.close();

        do
        {
            b=true;

            for(int i=0; i<namelist.size(); i++)
            {
                if(teacherName==namelist[i])
                {
                    b=false;
                    cout<<"This name is already taken, try another : ";
                    getline(cin,teacherName);
                    break;
                }
                else
                {
                    b=true;
                }
            }
        }
        while(b==false);

    do
    {
        cout<<"Insert how many activities will be there: ";
        cin>>checker;
        b=true;
        for(int i=0; i<checker.size(); i++)
        {
            c=checker[i];
            if(isdigit(c) && checker.size()<10 )
            {
                b=true;
            }
            else
            {
                cout << "Invalid choice, ";
                b=false;
                break;
            }
        }
    }
    while(b==false );
    ss<<checker;
    ss>>actCount;
    ss.clear();
    if(actCount>0)
    {
        int actTimes[actCount + 1];
        string activities [actCount];
        // Time for first activity
        cout<<"Add time for activity 1 :" << endl << "Hour: ";
        do
        {
            cin>>checker;
            b = true;

            for(int i = 0; i < checker.size(); i++)
            {
                c = checker[i];
                if (!isdigit(c) || checker.size()>9 )
                {
                    b = false;
                    cout << "Invalid input, try again: ";
                    break;
                }
            }
            if (b)
            {

                ss<<checker;
                ss>>hour;
                ss.clear();
                if (hour < 1 || hour > 12)
                {
                    b = false;
                    cout << "Invalid input, hour limit is from 1 to 12, try again: ";
                }
            }
        }
        while (!b);

        cout<<"Minute: ";
        do
        {
            cin>>checker;
            b = true;

            for(int i = 0; i < checker.size(); i++)
            {
                c = checker[i];
                if (!isdigit(c)  || checker.size()>9)
                {
                    b = false;
                    cout << "Invalid input, try again: ";
                    break;
                }
            }
            if (b)
            {

                ss<<checker;
                ss>>minute;
                ss.clear();
                if (minute < 0 || minute > 59)
                {
                    b = false;
                    cout << "Invalid input, minute limit is from 0 to 59, try again: ";
                }
            }
        }
        while (!b);
        int M;
        cout<<"1.AM \n2.PM"<<endl;
        do
        {
            cout<<"Enter your choice :";
            cin>>checker;
            b = true;

            for(int i = 0; i < checker.size(); i++)
            {
                c = checker[i];
                if (!isdigit(c)  || checker.size()>9)
                {
                    b = false;
                    cout << "Invalid input, try again: ";
                    break;
                }
            }
            if (b)
            {

                ss<<checker;
                ss>>M;
                ss.clear();
                if (M < 1 && M > 2)
                {
                    b = false;
                    cout << "Invalid input, try again: ";
                }
            }
        }
        while (!b);


        if(M==1 && hour==12)
        {
            hour=0;
        }
        else if(M==2 && hour>=1 && hour<=11 )
        {
            hour+=12;
        }
        actTimes[0] = hour * 60 + minute;
        cout<<"Add description for activity 1: ";
        cin.ignore();
        getline(cin, activities[0]);

        // Time for other activities
        for(int i = 1; i <= actCount; i++)
        {
            int tempTime;
            do
            {
                if(i<actCount)
                {
                    cout<<"Add time for activity "<< i + 1 <<" :"<< endl << "Hour: ";
                }
                else if (i=actCount)
                {
                    cout<<"Add end time :"<<endl<<"Hour: ";
                }
                do
                {
                    cin>>checker;
                    b = true;

                    for(int i = 0; i < checker.size(); i++)
                    {
                        c = checker[i];
                        if (!isdigit(c)  || checker.size()>9)
                        {
                            b = false;
                            cout << "Invalid input, try again: ";
                            break;
                        }
                    }
                    if (b)
                    {

                        ss<<checker;
                        ss>>hour;
                        ss.clear();
                        if (hour < 1 || hour > 12)
                        {
                            b = false;
                            cout << "Invalid input, hour limit is from 1 to 12, try again: ";
                        }
                    }
                }
                while (!b);
                cout<<"Minute: ";
                do
                {
                    cin>>checker;
                    b = true;

                    for(int i = 0; i < checker.size(); i++)
                    {
                        c = checker[i];
                        if (!isdigit(c)  || checker.size()>9)
                        {
                            b = false;
                            cout << "Invalid input, try again: ";
                            break;
                        }
                    }
                    if (b)
                    {

                        ss<<checker;
                        ss>>minute;
                        ss.clear();
                        if (minute < 0 || minute > 59)
                        {
                            b = false;
                            cout << "Invalid input, minute limit is from 0 to 59, try again: ";
                        }
                    }
                }
                while (!b);
                cout<<"1.AM \n2.PM"<<endl;

                do
                {
                    cout<<"Enter your choice :";
                    cin>>checker;
                    b = true;

                    for(int i = 0; i < checker.size(); i++)
                    {
                        c = checker[i];
                        if (!isdigit(c)  || checker.size()>9)
                        {
                            b = false;
                            cout << "Invalid input, try again: ";
                            break;
                        }
                    }
                    if (b)
                    {

                        ss<<checker;
                        ss>>M;
                        ss.clear();
                        if (M < 1 && M > 2)
                        {
                            b = false;
                            cout << "Invalid input, try again: ";
                        }
                    }
                }
                while (!b);


                if(M==1 && hour==12)
                {
                    hour=0;
                }
                else if(M==2 && hour>=1 && hour<=11 )
                {
                    hour+=12;
                }
                tempTime = hour * 60 + minute;
                if(tempTime <= actTimes[i - 1])
                {
                    cout<<"Invalid input, end time can't be smaller than start time or equal with start time, try again "<<endl;
                }
            }
            while(tempTime <= actTimes[i - 1]);

            actTimes[i] = hour * 60 + minute;
            if(i == actCount)
            {
                break;
            }
            cout<<"Add description for activity " << i + 1 << ": ";
            cin.ignore();
            getline(cin, activities[i]);
        }
        string filename = teacherName + ".txt";
        ofstream file(filename);
        file << teacherName << endl;
        for(int i = 0; i <= actCount; i++)
        {
            file << actTimes[i] << endl;
            if(i == actCount)
            {
                break;
            }
            file << activities[i] << endl;
        }
        ofstream name1("namelist.txt", ios::app);
        name1 << teacherName << endl;

        message = "Creating schedule";
        size=message.size();
        cout << "\033[?25l";
        for (int i=0; i<size; i++)
        {
            char c=message[i];
            cout<<YELLOW<<c<<RESET;
            this_thread::sleep_for(chrono::milliseconds(60));
        }
        cout << "\033[?25h";
        pointer(1);
        message = "New schedule is added successfully.";
        size=message.size();
        for (int i=0; i<size; i++)
        {
            char c=message[i];
            cout<<YELLOW<<c<<RESET;
            this_thread::sleep_for(chrono::milliseconds(40));
        }
        cout<<endl;
    }
    else
    {
        cout<<"Invalid input, amount of activities can't be less than 1"<<endl;
    }
}
void displayMenu()
{

    string text="1. Add Schedule\n2. Print Schedule (Any Time)\n3. Print Schedule (Current Time)\n4. Delete Schedule\n5. End Program\n6. Menu\n";
    cout<<text;


}

void printSchedule(vector<string> schedule)
{
    int actCount = schedule.size();
    int actTimes [actCount / 2];
    string activities [actCount / 2];
    int i, j, endTime;
    stringstream ss;
    for(i = 0, j = 0; i < actCount; j++, i = i + 2)
    {
        activities[j] = schedule[i];
    }
    for(i = 1, j = 0; i < actCount; j++, i = i + 2)
    {
        actTimes[j] = stoi(schedule[i]);
        endTime = actTimes[j];
    }
    cout << "Enter time:" << endl;
    int hour, minute, time;
    cout << "Hour: ";
    do
    {
        cin>>checker;
        b = true;

        for(int i = 0; i < checker.size(); i++)
        {
            c = checker[i];
            if (!isdigit(c)  || checker.size()>9)
            {
                b = false;
                cout << "Invalid input, try again: ";
                break;
            }
        }
        if (b)
        {
            ss<<checker;
            ss>>hour;
            ss.clear();
            if (hour < 1 || hour > 12)
            {
                b = false;
                cout << "Invalid input, hour limit is from 1 to 12, try again: ";
            }
        }
    }
    while (!b);
    cout<<"Minute: ";
    do
    {
        cin>>checker;
        b = true;

        for(int i = 0; i < checker.size(); i++)
        {
            c = checker[i];
            if (!isdigit(c)  || checker.size()>9)
            {
                b = false;
                cout << "Invalid input, try again: ";
                break;
            }
        }
        if (b)
        {
            ss<<checker;
            ss>>minute;
            ss.clear();
            if (minute < 0 || minute > 59)
            {
                b = false;
                cout << "Invalid input, minute limit is from 0 to 59, try again: ";
            }
        }
    }
    while (!b);
    cout<<"1.AM \n2.PM"<<endl;
    int M;
    do
    {
        cout<<"Enter your choice :";
        cin>>checker;
        b = true;

        for(int i = 0; i < checker.size(); i++)
        {
            c = checker[i];
            if (!isdigit(c)  || checker.size()>9)
            {
                b = false;
                cout << "Invalid input, try again: ";
                break;
            }
        }
        if (b)
        {

            ss<<checker;
            ss>>M;
            ss.clear();
            if (M < 1 && M > 2)
            {
                b = false;
                cout << "Invalid input, try again: ";
            }
        }
    }
    while (!b);

    if(M==1 && hour==12)
    {
        hour=0;
    }
    else if(M==2 && hour>=1 && hour<=11 )
    {
        hour+=12;
    }
    time = hour * 60 + minute;
    int actIndex = 0;
    for(int i = 0; i < actCount / 2; i++)
    {
        if(time >= actTimes[i])
        {
            actIndex++;
        }
        else if(time < actTimes[i])
        {
            break;
        }
    }
    if(actIndex != 0 && time < endTime)
    {
        cout <<YELLOW << "Activity: " << activities[actIndex] <<RESET << endl;
    }
    else
    {
        cout << "No activity found" << endl;
    }
}
void printSchedule1(vector<string> schedule)
{
    int actCount = schedule.size();
    int actTimes [actCount / 2];
    string activities [actCount / 2];
    int i, j, endTime;
    for(i = 0, j = 0; i < actCount; j++, i = i + 2)
    {
        activities[j] = schedule[i];
    }
    for(i = 1, j = 0; i < actCount; j++, i = i + 2)
    {
        actTimes[j] = stoi(schedule[i]);
        endTime = actTimes[j];
    }
    time_t currentTime = time(nullptr);
    struct tm now = *localtime(&currentTime);
    int time = now.tm_hour * 60 + now.tm_min;
    int actIndex = 0;
    for(int i = 0; i < actCount / 2; i++)
    {
        if(time >= actTimes[i])
        {
            actIndex++;
        }
        else if(time < actTimes[i])
        {
            break;
        }
    }

    if(actIndex != 0 && time < endTime)
    {
        cout <<YELLOW << "Activity: " << activities[actIndex] <<RESET<< endl;
    }
    else
    {
        cout << "No activity found" << endl;
    }
}
int main()
{
    vector<string> schedule;
    vector<string> namelist;
    string userInput;
    string temp;
    const string PASSWORD = "123123.del";
    stringstream strc;
    displayMenu();
    int userChoice;
    do
    {
        do
        {
            cout <<RED<< "Main menu "<<RESET <<"- Enter your choice: ";
            cin>>checker;
            b=true;
            for(int i=0; i<checker.size(); i++)
            {
                c=checker[i];
                if(isdigit(c)  && checker.size()<10)
                {
                    b=true;
                }
                else
                {
                    cout << "Invalid choice, try again"<<endl;
                    b=false;
                    break;
                }
            }
        }
        while(b==false);
        strc<<checker;
        strc>>userChoice;
        strc.clear();
        switch(userChoice)
        {
        case 1:
            addSchedule();
            break;
        case 2:
        {
            ifstream name("namelist.txt");
            if(name.is_open())
            {
                namelist.clear();
                while(getline(name,temp))
                {
                    namelist.push_back(temp);
                }
                name.close();
                if(!namelist.empty())
                {
                    for(int i = 0; i < namelist.size(); i++)
                    {
                        cout << i + 1 << ". " << namelist[i] << endl;
                    }
                    int choice;
                    do
                    {
                        cout << "Enter your choice: ";
                        cin>>checker;
                        b=true;
                        for(int i=0; i<checker.size(); i++)
                        {
                            c=checker[i];
                            if(isdigit(c)  && checker.size()<10 )
                            {
                                b=true;
                            }
                            else
                            {
                                cout << "Invalid choice, ";
                                b=false;
                                break;
                            }
                        }
                    }
                    while(b==false);
                    strc<<checker;
                    strc>>choice;
                    strc.clear();
                    if(choice <= namelist.size())
                    {
                        string filename = namelist[choice - 1] + ".txt";
                        ifstream file(filename);
                        if(file.is_open())
                        {
                            schedule.clear();
                            while(getline(file,temp))
                            {
                                schedule.push_back(temp);
                            }
                            file.close();

                            printSchedule(schedule);
                        }
                        else
                        {
                            cout<<"No schedule is found"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"Invalid choice"<<endl;
                    }

                }
                else
                {
                    cout<<"No schedule is found"<<endl;
                }
            }
            else
            {
                cout<<"No schedule is found"<<endl;
            }
        }
        break;
        case 3:
        {
            ifstream name("namelist.txt");
            if(name.is_open())
            {
                namelist.clear();
                while(getline(name,temp))
                {
                    namelist.push_back(temp);
                }
                name.close();
                if(!namelist.empty())
                {
                    cout << "List of teachers name:" << endl;
                    for(int i = 0; i < namelist.size(); i++)
                    {
                        cout << i + 1 << ". " << namelist[i] << endl;
                    }
                    int choice;
                    do
                    {
                        cout << "Enter your choice: ";
                        cin>>checker;
                        b=true;
                        for(int i=0; i<checker.size(); i++)
                        {
                            c=checker[i];
                            if(isdigit(c)  && checker.size()<10 )
                            {
                                b=true;
                            }
                            else
                            {
                                cout << "Invalid choice, ";
                                b=false;
                                break;
                            }
                        }
                    }
                    while(b==false);
                    strc<<checker;
                    strc>>choice;
                    strc.clear();
                    if(choice <= namelist.size())
                    {
                        string filename = namelist[choice - 1] + ".txt";
                        ifstream file(filename);
                        if(file.is_open())
                        {
                            schedule.clear();
                            while(getline(file,temp))
                            {
                                schedule.push_back(temp);
                            }
                            file.close();
                            printSchedule1(schedule);
                        }
                        else
                        {
                            cout<<"No schedule is found"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"Invalid choice"<<endl;
                    }
                }
                else
                {
                    cout<<"No schedule is found"<<endl;
                }
            }
            else
            {
                cout<<"No schedule is found"<<endl;
            }
        }
        break;
        case 4:
        {
            string tempPassword;
            cout << "Enter password: ";
            cin.ignore();
            getline(cin, tempPassword);
            if(tempPassword == PASSWORD)
            {
                ifstream name("namelist.txt");
                if(name.is_open())
                {
                    namelist.clear();
                    while(getline(name,temp))
                    {
                        namelist.push_back(temp);
                    }
                    name.close();
                    if(!namelist.empty())
                    {
                        cout << "List of teachers name:" << endl;
                        for(int i = 0; i < namelist.size(); i++)
                        {
                            cout << i + 1 << ". " << namelist[i] << endl;
                        }
                        int choice;
                        do
                        {
                            cout << "Enter your choice: ";
                            cin>>checker;
                            b=true;
                            for(int i=0; i<checker.size(); i++)
                            {
                                c=checker[i];
                                if(isdigit(c)  && checker.size()<10)
                                {
                                    b=true;
                                }
                                else
                                {
                                    cout << "Invalid choice, ";
                                    b=false;
                                    break;
                                }
                            }
                        }
                        while(b==false);
                        strc<<checker;
                        strc>>choice;
                        strc.clear();
                        if(choice <= namelist.size())
                        {
                            string filename = namelist[choice - 1] + ".txt";
                            remove(filename.c_str());
                            cout << "Schedule of " << namelist[choice - 1] << " is successfully deleted." << endl;
                            namelist.erase(namelist.begin() + (choice - 1));
                            ofstream del("namelist.txt", ios::trunc);
                            for(int i = 0; i < namelist.size(); i++)
                            {
                                del << namelist[i]<<endl;
                            }
                        }
                        else
                        {
                            cout<<"Invalid choice"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"No schedule is found"<<endl;
                    }
                }
                else
                {
                    cout<<"No schedule is found"<<endl;
                }
            }
            else
            {
                cout << "Wrong password" << endl;
            }
        }
        break;
        case 5:
        {
            string message = "Terminating";
            int size=message.size();
            cout << "\033[?25l";
            for (int i=0; i<size; i++)
            {
                char c=message[i];
                cout <<YELLOW << c <<RESET;
                this_thread::sleep_for(chrono::milliseconds(60));
            }
            cout << "\033[?25h";
            pointer(1);
            message = "Program is ended successfully";
            size=message.size();
            for (int i=0; i<size; i++)
            {
                char c=message[i];
                cout <<YELLOW << c <<RESET;
                this_thread::sleep_for(chrono::milliseconds(40));
            }
            cout<<endl;
        }
        break;
        case 6:
            displayMenu();
            break;
        default:
            cout << "Invalid choice, try again "<<endl;
        }
    }
    while(userChoice != 5);
    return 0;
}
