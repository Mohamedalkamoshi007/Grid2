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
int heuristic2(State s){
 int mx=manhattan(s.x,s.y,1,1);
 if(s.c1=='f'){
  mx=maxValue(mx,manhattan(s.x,s.y,coinX[0],coinY[0]));
 }
  if(s.c2=='f'){
  mx=maxValue(mx,manhattan(s.x,s.y,coinX[1],coinY[1]));
 }
  if(s.c3=='f'){
  mx=maxValue(mx,manhattan(s.x,s.y,coinX[2],coinY[2]));
 }
  if(s.c4=='f'){
  mx=maxValue(mx,manhattan(s.x,s.y,coinX[3],coinY[3]));
 }
 return mx;
}

void printPath(int indexx){
    int path[PATH_LIMIT];
    int length=0;
    
    while(indexx!=-1){
        path[length]=indexx;
        length++;
        indexx=nodes[indexx].parent;

    }
    cout<<"\nPATH:"<<endl;
    for(int i=length-1;1>=0;i--){
        nodes[path[i]].state.print();
        cout<<endl;

    }
    cout<<"\nCost = "<<length-1<<endl;
    cout<<"Visited States = "<<nodeCount<<endl;

}

int bestGreedy(){
    int best=-1;
    for(int i=0;i<nodeCount;i++){
    if(nodes[i].h!=1000){
      if(best==-1 || nodes[i].h<nodes[best].h){
        best=i;

      }
    }
}
return best;
}

int bestAstar(){
    int best=-1;
    for(int i=0;i<nodeCount;i++){
        if(nodes[i].f!=1000){
         if(best==-1 || nodes[i].f<nodes[best].f){
           best=i;
         }
      }

    }
    return best;
}

void Greedy(State start)
    {
        nodeCount=0;
        nodes[0].state=start;
        nodes[0].parent=-1;
        nodes[0].g=0;
        nodes[0].h=heuristic1(start);
        nodes[0].f=nodes[0].h;
        nodeCount++;

        while(true)
        {
            int current=bestGreedy();
            if(current==-1)
            {
                break;
            }

            State s=nodes[current].state;
            cout<<"Visited: ";
            s.print();
            cout<<endl;

            if(s.Goalcheck())
            {
                cout<<"\nGoal Found Using Greedy Search\n";
                printPath(current);
                return;
            }

            nodes[current].h=1000;
            nodes[current].f=1000;

            int dx[4]={-1,1,0,0};
            int dy[4]={0,0,-1,1};

            for(int i=0;i<4;i++)
            {
                State next=s;

                next.x +=dx[i];
                next.y +=dy[i];
                next.fuel--;

                if(
                    next.x<0 || next.x>=SIZE || next.y<0 || next.y>=SIZE)
                {
                    continue;
                }

                if(BlockedCheck(next.x,next.y))
                {
                    continue;
                }

                if(next.fuel<0)
                {
                    continue;
                }

                updateCoins(next);
                refillFuel(next);

                if(!visited(next))
                {
                    nodes[nodeCount].state=next;
                    nodes[nodeCount].parent=current;
                    nodes[nodeCount].g=nodes[current].g+1;
                    nodes[nodeCount].h=heuristic1(next);
                    nodes[nodeCount].f=nodes[nodeCount].h;
                    nodeCount++;
                }
            }
        }

        cout<<"No Solution\n";
    }

    void AStar(State start)
    {
        nodeCount=0;
        nodes[0].state=start;
        nodes[0].parent=-1;
        nodes[0].g=0;
        nodes[0].h=heuristic2(start);
        nodes[0].f=nodes[0].h;
        nodeCount++;

        while(true)
        {
            int current=bestAStar();

            if(current==-1)
            {
                break;
            }

            State s=nodes[current].state;

            cout<<"Visited: ";
            s.print();
            cout<<endl;

            if(s.Goalcheck())
            {
                cout<<"\nGoal Found Using A* Search\n";
                printPath(current);
                return;
            }

            nodes[current].f=1000;

            int dx[4]={-1,1,0,0};
            int dy[4]={0,0,-1,1};

            for(int i=0;i<4;i++)
            {
                State next=s;
                next.x +=dx[i];
                next.y +=dy[i];
                next.fuel--;

                if(next.x<0  next.x>=SIZE  next.y<0 || next.y>=SIZE)
                {
                    continue;
                }

                if(BlockedCheck(next.x,next.y))
                {
                    continue;
                }

                if(next.fuel<0)
                {
                    continue;
                }

                updateCoins(next);
                refillFuel(next);

                if(!visited(next))
                {
                    nodes[nodeCount].state=next;
                    nodes[nodeCount].parent=current;
                    nodes[nodeCount].g=nodes[current].g+1;
                    nodes[nodeCount].h=heuristic2(next);
                    nodes[nodeCount].f=nodes[nodeCount].g+nodes[nodeCount].h;
                    nodeCount++;
                }
            }
        }

        cout<<"No Solution\n";
    }
};
