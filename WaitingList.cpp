#include <iostream>
#include <queue>

using namespace std;

// WaitingList.cpp
// Includes the code for the queue meant to be implemented as the Waiting List. For now, uses the built-in C++ queue library that maybe(?) will only use student's name from Resource class to represent student in waiting list.
// Should the standard queue implemented here not be enough I can make a more complicated queue using classes.

int main {

        // Declare queue
        queue<string> WaitingList;

        // Add and remove sample students from the queue
        string Name1, Name2, Name3, Name4, Name5;
        Name1 = "Eric";
        Name2 = "William";
        Name3 = "Elizabeth";
        Name4 = "Whitney";
        Name5 = "Douglas";
        WaitingList.push(Name1);
        WaitingList.push(Name2);
        WaitingList.push(Name3);
        WaitingList.push(Name4);
        WaitingList.pop();
        WaitingList.push(Name5);

        // To traverse: make copy of queue to print and remove elements from
        queue<string> CopyList = WaitingList;

        cout << "Elements of WaitingList: ";
        while(!CopyList.empty()) {
                cout << CopyList.front() << " ";
                CopyList.pop();
        }

        return 0;

}
