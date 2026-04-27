#include <iostream>
using namespace std;

const int SIZE = 10;
const int MAX_STATES = 10000;
const int MAX_FUEL = 20;
const int PATH_LIMIT = 500;

class State
{
public:
    int x;
    int y;
    int fuel;

    char c1,c2,c3,c4;

    void print()
    {
        cout<<"("<< x << ","<< y << ","<< fuel << ","<< c1 << ","<< c2 << ","<< c3 << ","<< c4 << ")";
    }

    bool isGoal()
    {
        if (x == 1 &&y == 1 &&c1 == 't' &&c2 == 't' &&c3 == 't' &&c4 == 't')
        {
            return true;
        }

        return false;
    }
};

class Node
{
public:
    State state;

    int parent;

    int g,h,f;
};

class GridGame
{
private:
    Node nodes[MAX_STATES];

    int nodeCount;

    int coinX[4] = {1, 2, 5, 6};
    int coinY[4] = {2, 5, 5, 9};

    int fuelX;
    int fuelY;

public:
    GridGame()
    {
        nodeCount = 0;

        fuelX = 6;
        fuelY = 6;
    }

    int absValue(int n)
    {
        if (n<0)
        {
            return -n;
        }

        return n;
    }

    int maxValue(int a, int b)
    {
        if (a>b)
        {
            return a;
        }

        return b;
    }
