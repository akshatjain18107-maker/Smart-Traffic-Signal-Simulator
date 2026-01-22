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

    int NS_queue = randomBetween(6, 10);
    int EW_queue = randomBetween(6, 10);

    int chance_NS = randomBetween(1, 100);
    int chance_EW = randomBetween(1, 100);

    int NS_emergency = (chance_NS >= 80) ? 1 : 0;
    int EW_emergency = (chance_EW >= 80) ? 1 : 0;

    while (true)
    {
        ofstream stateFile("state.csv");
        stateFile << NS_queue << ","
                  << EW_queue << ","
                  << NS_emergency << ","
                  << EW_emergency;
        stateFile.close();

        ifstream actionFile("action.txt");
        string action;
        actionFile >> action;
        actionFile.close();

        int cars_passed = 5;

        if (action == "NS")
        {
            int removed = min(cars_passed, NS_queue);
            NS_queue -= removed;
        }
        else if (action == "EW")
        {
            int removed = min(cars_passed, EW_queue);
            EW_queue -= removed;
        }

        int NS_new = randomBetween(1, 5);
        int EW_new = randomBetween(1, 5);

        NS_queue += NS_new;
        EW_queue += EW_new;

        chance_NS = randomBetween(1, 100);
        chance_EW = randomBetween(1, 100);

        NS_emergency = (chance_NS >= 80) ? 1 : 0;
        EW_emergency = (chance_EW >= 80) ? 1 : 0;
    }

    return 0;
}
