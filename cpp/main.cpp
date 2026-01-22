#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int randomBetween(int low, int high)
{
    return low + rand() % (high - low + 1);
}

int main()
{ 
    srand(time(0)); 
    int intersections = 4;
    int NS_queue[intersections];
    int EW_queue[intersections];
    int NS_emergency[intersections];
    int EW_emergency[intersections];

    for (int i = 0; i < intersections; i++)
    {
        NS_queue[i] = randomBetween(6, 10);
        EW_queue[i] = randomBetween(6, 10);
        NS_emergency[i] = (randomBetween(1, 100) >= 80);
        EW_emergency[i] = (randomBetween(1, 100) >= 80);
    }

    while (true)
    {

        ofstream stateFile("state.csv");
        for (int i = 0; i < intersections; i++)
        {
            stateFile << NS_queue[i] << ","
                      << EW_queue[i] << ","
                      << NS_emergency[i] << ","
                      << EW_emergency[i];

            if (i != intersections - 1)
                stateFile << "\n";
        }
        stateFile.close();

        ifstream actionFile("action.txt");
        string action;
        actionFile >> action;
        actionFile.close();

        int cars_passed = 5;

        for (int i = 0; i < intersections; i++)
        {
            if (action == "NS")
            {
                int removed = min(cars_passed, NS_queue[i]);
                NS_queue[i] -= removed;
            }
            else if (action == "EW")
            {
                int removed = min(cars_passed, EW_queue[i]);
                EW_queue[i] -= removed;
            }
        }

        for (int i = 0; i < intersections; i++)
        {
            NS_queue[i] += randomBetween(1, 5);
            EW_queue[i] += randomBetween(1, 5);

            NS_emergency[i] = (randomBetween(1, 100) >= 80);
            EW_emergency[i] = (randomBetween(1, 100) >= 80);
        }

    }

    return 0;
}
