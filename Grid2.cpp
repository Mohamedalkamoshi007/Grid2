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
        cout<<"("<<x<<","<<y<<","<<fuel<<","<<c1<<","<<c2<<","<<c3<<","<<c4<<")";
    }

    bool Goalcheck()
    {
        if(x==1 && y==1 && c1=='t' && c2=='t' && c3=='t' && c4=='t')
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

    int coinX[4]={1,2,5,6};
    int coinY[4]={2,5,5,9};

    int fuelX;
    int fuelY;

public:
    GridGame()
    {
        nodeCount=0;
        fuelX=6;
        fuelY=6;
    }

    int absValue(int n)
    {
        if(n<0)
        {
            return -n;
        }

        return n;
    }

    int maxValue(int a,int b)
    {
        if(a>b)
        {
            return a;
        }

        return b;
    }

bool sameState(State a,State b){
    if(a.x==b.x && a.y==b.y && a.fuel==b.fuel && a.c1==b.c1 && a.c2==b.c2 && a.c3==b.c3 && a.c4==b.c4){
        return true;
    }
    return false;

}

bool visited(State s){
    for(int i=0;i<nodeCount;i++){
        if(sameState(nodes[i].state,s)){
            return true;

        }

    }
    return false;

}

bool BlockedCheck(int x,int y){
    if((x==2 && y==2) || (x==3 && y==3) || (x==4 && y==4)){
        return true;

    }
    return false;

}

void updateCoins(State &s){
if(s.x==coinX[0] && s.y==coinY[0]){
    s.c1='t';
}
if(s.x==coinX[1] && s.y==coinY[1]){
    s.c2='t';
}
if(s.x==coinX[2] && s.y==coinY[2]){
    s.c3='t';
}
if(s.x==coinX[3] && s.y==coinY[3]){
    s.c4='t';
}
}

void refillFuel(State &s){
if(s.x==fuelX && s.y==fuelY){
s.fuel=20;
}
}

int manhattan(int x1,int y1,int x2,int y2){
return absValue(x1 - x2) + absValue(y1 - y2);
}

int heuristic1(State s){
    bool taken[4];
    taken[0]=(s.c1=='t');
    taken[1]=(s.c2=='t');
    taken[2]=(s.c3=='t');
    taken[3]=(s.c4=='t');
    int cx=s.x;
    int cy=s.y;
    int total=0;
    for(int step=0;step<4;step++){
        int dis=1000;
        int index=-1;
        for(int i=0;i<4;i++){
            if(!taken[i]){
                int d=manhattan(cx,cy,coinX[i],coinY[i]);
                if(d<dis){
                    dis=d;
                    index=i;

                }

            }

        }
        if(index==-1){
            break;

        }
        total+=dis;
        cx=coinX[index];
        cy=coinY[index];
        taken[index]=true;

    }
    total+=manhattan(cx,cy,1,1);
    return total;

}
};
