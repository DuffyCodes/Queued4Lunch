#include <iostream>
#include <list>
//#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct Passes{

    int door1 = 0, door2=0;
public:
    Passes(int n, int m):door1(n),door2(m){};
    Passes(const Passes& p):door1(p.door1),door2(p.door2){};
    Passes(){
        door1= 0;
        door2 = 0;
    };
    typedef typename std::list<Passes>::iterator iterator;
    typedef typename std::list<Passes>::const_iterator const_iterator;


    iterator begin() { return iterator( begin() ); }
    iterator end() { return iterator( end() ); }
    const_iterator begin() const { return const_iterator( begin() ); }
    const_iterator end() const { return const_iterator( end() ); }
    bool operator==(const Passes &p)
    {
        if(door1 == p.door1 && door2 ==p.door2)
            return true;
        else
            return false;
    };
    bool operator<(const Passes &p)
    {
        if(door1<p.door1)
            return true;
        else
            return false;
    };
};

/*
**    Print function to print out the list of passages.
*/

/**
 *  Find the shortest path from start to dest, returning the minimum number
 *  of doors you must pass through.  If no path exists, return -1.
 */
int findShortestPathBetween(int start, int dest, list<Passes> &p, int N)
{
  vector<int>distance (N,(N+1));
    distance[start-1]=0;

    int k = 1;
    queue<int> yetToCheck;
    while (k <= N)
    {
        yetToCheck.push(k);
        k++;
    }
    int overall = 0;
    while((!yetToCheck.empty() || distance[dest-1]>N) && overall!=N)
    {
        int que = yetToCheck.front();
       // cout<<"que: "<<que<<endl;
        auto it = p.begin();
        if(it == p.end())
            return -1;
        while(it != p.end()&&it->door1 != que )
            if(it!=p.end())
                it++;
        //cout<<"Door1: "<<it->door1<<endl;
        int counter = 0;
        if(it != p.end()){
            while(counter != N && it!=p.end() )
            {
            //cout<<"Entered while loop. Door1 is: "<<it->door1<<" with distance: "<<distance[it->door1-1]
            //<<"Door2 is: "<< it->door2<<" with distance: "<<distance[it->door2-1]<<" and que is: "<<que<<endl;
                if(distance[(it->door2-1)]>(distance[it->door1-1]+1))
                {
                    distance[it->door2-1]=(distance[it->door1 - 1]+1);
                    yetToCheck.push(it->door2);
                //cout<<"Door2 distance: "<<distance[it->door2-1]<<endl;
                }
                if (it != p.end())
                    it++;
            counter++;
        }}
        yetToCheck.pop();
        overall++;
    }
    if(distance[dest-1]<N)
        return distance[dest-1];
    else
        return -1;
}




void solve (istream& in)
{
    int nRooms = 0, nDoors = 0, start =0,stop=0;
    in >> nRooms >> nDoors;

    //RoomNum start, stop;

    in >> start >> stop;

    list<Passes> passages;


    for (int i = 0; i < nDoors; ++i)
    {
        int from = 0, into = 0;
        in >> from >> into;
        Passes temp(from,into);
        passages.push_back(temp);
    }


    passages.sort();


    int length = findShortestPathBetween (start, stop, passages, nRooms);
    cout << length << endl;
}


int main (int argc, char** argv)
{
  // The problem statements call for input to be taken from cin.
  // During debugging, however, I often find it easier to keep my
  // input in a file. This code below will check to see if a file name
  // has been given on the command line. If so, it reads from the
  // file. If not, it reads from cin.
  if (argc > 1) {
    ifstream in (argv[1]);
    solve(in);
  } else {
    solve (cin);
  }
}
