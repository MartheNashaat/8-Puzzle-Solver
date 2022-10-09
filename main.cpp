#include <iostream>
#include<conio.h>
#include <list>
#include <bits/stdc++.h>
#include <unordered_map>
#include <string>
#define N 3
#include <math.h>


using namespace std;

class State
{
public:
   // int puzzle[N][N],gcost,hcost,fcost;
    vector<string> BFS(string puzzle);
    vector<string> DFS(string puzzle);
    vector<string> Astar(string puzzle, int m);
};

string goal= "012345678";

void print(string puzzle)
{
    int puzzlematrix[N][N];

    for (int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            puzzlematrix[i][j]= puzzle[i*3+j] -48;
            cout << puzzlematrix[i][j]<< " " ;

        }
        cout <<endl;
    }
    cout<< endl <<endl;
}


double indexing(string puzzle,int m)
{
    int puzzlematrix[N][N];
    int goalmatrix[N][N];
    int icurr=0,jcurr=0,iideal=0,jideal=0;
    double h=0,h1=0;
    for (int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            puzzlematrix[i][j]= puzzle[i*3+j] -48;
            goalmatrix[i][j]= goal[i*3+j] -48;
        }
    }
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if (puzzlematrix[i][j]!=0)
            {
                jideal =puzzlematrix[i][j]%3; //column place
                if (puzzlematrix[i][j] < 3) //row place
                    iideal=0;
                else if (puzzlematrix[i][j] >5)
                    iideal=2;
                else
                    iideal=1 ;
                icurr=i;
                jcurr=j;

            }

            h=h+abs(iideal-icurr)+abs(jideal -jcurr);

            h1=h1+sqrt( pow( ( icurr - iideal),2)+pow((jcurr - jideal),2) );

        }

    }
    if (m==0)
    {
        return h;
    }
    if (m==1)
    {
        return h1;
    }

}


vector<string> Getchildren(string puzzle)
{
    vector<string> children(4);
    int right,left,up,down;
    string upflag,leftflag,rightflag,downflag;
    string temp= puzzle;
    int index= puzzle.find('0');
    int tempindex= temp.find('0');

    if (index == 0 ||index ==  3 ||index ==  6 ||index ==  1 || index == 4 || index == 7) //move right
    {
        rightflag=" Right ";
        temp= puzzle;
        right=tempindex+1;
        swap(temp[right],temp[tempindex]);
        children.push_back(temp);
    }
    if (index == 1 ||index ==  4 ||index ==  7 ||index ==  2 || index == 5 || index == 8) //mpve left
    {
        leftflag= " Left ";
        temp= puzzle;
        left=tempindex-1;

        swap(temp[left],temp[tempindex]);

        children.push_back(temp);

    }
    if (index == 3 || index == 4 || index == 5 || index == 6 || index == 7 ||index ==  8) //move up
    {
        upflag= " Up ";
        temp= puzzle;
        up=tempindex-3;

        swap(temp[up],temp[tempindex]);

        children.push_back(temp);
    }
    if (index == 0 || index == 1 ||index ==  2 || index == 3 ||index ==  4 || index == 5)// move down
    {
        downflag=" Down ";
        temp= puzzle;
        down=tempindex+3;

        swap(temp[down],temp[tempindex]);

        children.push_back(temp);
    }
    return children;
}

vector<string> State::BFS(string puzzle)
{
    string parent = puzzle;
    unordered_map <string,string> visited;  //value = string:puzzle , key ==parent
    unordered_set<string> expand;
    vector<string> path;
    vector<string> pathDirections;
    string temp;
    int expanded=0;
    queue<string> q ;
    visited.insert(make_pair(puzzle,"null")); //mark as visited & enqueue , first one has no parent(null)
    q.push(parent);

    while (!q.empty())
    {

        parent=q.front();
        q.pop();
        expanded++;

        if (parent==goal)
        {
            temp=parent;
            expanded=expanded-1;
            path.push_back(temp);
            while (temp!= "null")
            {
                temp=visited[temp];
                path.push_back(temp);
            }
            path.pop_back();
            reverse(path.begin(),path.end());

            int x,y;
            for (int j=0; j<path.size(); j++)
            {

                cout<<endl;
                x=path[j].find('0');
                y=path[j+1].find('0');
                print(path[j]);

                if (j!=path.size()-1)
                {
                    if ((y-x)==-3)
                        pathDirections.push_back("Up");
                    if ((y-x)==3)
                        pathDirections.push_back("Down");
                    if ((y-x)==-1)
                        pathDirections.push_back("Left");
                    if ((y-x)==1)
                        pathDirections.push_back("Right");
                }

            }

            cout << "Path to Goal= [";
            for (int i=0; i<pathDirections.size(); i++)
            {
                cout << pathDirections[i];
                if (i!=pathDirections.size()-1)
                    cout <<", ";
            }
            cout <<"]"<<endl;

            cout<<"Cost of path= " <<path.size()-1 <<endl;
            cout <<"Expanded nodes= "<<expanded<<endl;
            cout << "Search depth= " << path.size() <<endl;
            return path;
        }
        vector<string> children = Getchildren(parent);
        for (auto i=children.begin(); i != children.end(); ++i)
        {
            if( visited.find(*i) == visited.end() ) //not found
            {
                visited.insert(make_pair(*i,parent));
                q.push(*i);
            }
        }
    }
}

vector<string> State::DFS(string puzzle)
{
    string parent = puzzle;
    unordered_map <string,string> visited;
    visited.insert(make_pair(puzzle,"null")); //mark as visited & enqueue
    vector<string> path;
    vector<string> pathDirections;
    string temp;
    int expanded=0;
    stack<string> s ;
    s.push(parent);

    while (!s.empty())
    {
        parent=s.top();
        s.pop();
        expanded++;
        if (parent==goal)
        {
            temp=parent;
            expanded=expanded-1;
            path.push_back(temp);
            while (temp!= "null")
            {
                temp=visited[temp];
                path.push_back(temp);
            }
            path.pop_back();
            reverse(path.begin(),path.end());

            int x,y;
            for (int j=0; j<path.size(); j++)
            {

                if (path.size()<25)
                    print(path[j]);
                else
                {
                    cout <<"Path too big.. ";
                    break;
                }
                cout<<endl;
                x=path[j].find('0');
                y=path[j+1].find('0');
                //  print(path[j]);
//                if (j>=1)
//                {
                if (j!=path.size()-1)
                {
                    if ((y-x)==-3)
                        pathDirections.push_back("Up");
                    if ((y-x)==3)
                        pathDirections.push_back("Down");
                    if ((y-x)==-1)
                        pathDirections.push_back("Left");
                    if ((y-x)==1)
                        pathDirections.push_back("Right");
                }

            }
            if (path.size()<25)
            {
                cout << "Path to Goal= [";
                for (int i=0; i<pathDirections.size(); i++)
                {
                    cout << pathDirections[i];
                    if (i!=pathDirections.size()-1)
                        cout <<", ";
                }
                cout <<"]"<<endl;
            }

            cout<<endl <<"Expanded nodes= "<<expanded<<endl;
            cout <<"Cost of path= " <<path.size()-1 <<endl;
            cout << "Search depth " << path.size() <<endl;
            return path;
        }

        vector<string> children = Getchildren(parent);
        for (auto i=children.begin(); i != children.end(); ++i)
        {
            if( visited.find(*i) == visited.end() ) //not found
            {
                visited.insert(make_pair(*i,parent)); //key = parent
                s.push(*i);
            }
        }
    }
}


vector<string>  State::Astar(string puzzle, int m)
{
    string parent = puzzle;
    double cost=0;
    int realcost=0;
    int explored=0;
    int level=0;
    int expanded=0;
    double score;
    unordered_map <string,pair<int,string> > visited; //string = current state,, int =cost , string =parent
    unordered_set<string> expand;
    vector<string> path;
    vector<string> pathDirections;
    vector<string>::iterator itr1,itr2;
    pair<int,string> temp;
    priority_queue< pair<int,string>, vector <pair <int,string> >, greater < pair<int,string> > > pqueue; //int= cost , string= state
    //--gets min and puts it at the front
    pqueue.push(make_pair(cost,parent));

    vector<string> children;
    visited.insert(make_pair(puzzle,make_pair(realcost,"null")) );//key , val

    while (!pqueue.empty())
    {
        parent=pqueue.top().second;

        pqueue.pop();
        expand.insert(parent);
        realcost=visited[parent].first; //node cost +1

        if (parent==goal) //break if goal is found
        {

            path.push_back(parent);
            while (parent!= "null")
            {
                parent=visited[parent].second;
                path.push_back(parent);
            }
            path.pop_back();
            reverse(path.begin(),path.end());
            expanded=expand.size();
            int x,y;
            for (int j=0; j<path.size(); j++)
            {

                cout<<endl;
                x=path[j].find('0');
                y=path[j+1].find('0');
                print(path[j]);

                if (j!=path.size()-1)
                {
                    if ((y-x)==-3)
                        pathDirections.push_back("Up");
                    if ((y-x)==3)
                        pathDirections.push_back("Down");
                    if ((y-x)==-1)
                        pathDirections.push_back("Left");
                    if ((y-x)==1)
                        pathDirections.push_back("Right");
                }

            }

            cout << "Path to Goal= [";
            for (int i=0; i<pathDirections.size(); i++)
            {
                cout << pathDirections[i];
                if (i!=pathDirections.size()-1)
                    cout <<", ";
            }
            cout <<"]"<<endl;

            cout << "Path cost= " << path.size()-1 <<endl;
            cout <<"Expanded= "<< expand.size() <<endl;
            cout << "Search depth " << path.size() <<endl;
            if (m==0)
            {
                cout <<"Total Manhattan cost= " << score <<endl;
            }
            if (m==1)
            {
                cout <<"Total Euclidean cost= " <<  score<<endl;
            }
            return path;
        }
        children = Getchildren(parent);
        for(string str: children)
        {
            score=indexing(str,m);
            if(visited.find(str)==visited.end())
            {
                pqueue.push(make_pair(cost+score,str));
                visited[str]=make_pair((cost+1),parent);
            }
            else
            {
                if(cost+1<visited[str].first)
                {
                    pqueue.push(make_pair(cost+score,str));
                    visited[str]=make_pair((cost+1),parent);
                }
            }
        }
    }
}

int main()
{

    clock_t time;

    int choice,m;
    State parent;
    string puzzle;
    do
    {
        cout << "Enter 9 digits for your puzzle= " ;
        cin >> puzzle;
        if (puzzle.length()!=9)
        {
            cout <<"wrong entry";
            exit(0);
        }
        cout << endl << "0: BFS" << endl << "1: DFS" << endl<< "2: Astar" <<endl << "3: Exit" <<endl;
        cout << "Enter ur choice: ";
        cin >> choice;
        cout<<endl;

        switch(choice)
        {
        case 0 :

            time=clock();
            parent.BFS(puzzle);
            time = clock() - time;

            cout << "Time=" << time /1000.0 <<endl;
            break;

        case 1:

            time=clock();
            parent.DFS(puzzle);
            time = clock() - time;

            cout << "Time=" << time /1000.0 <<endl;

            break;

        case 2:
            cout << "1: Euclidean   " << "0: Manhattan" <<endl <<"Choice=";
            cin >> m;
            cout<<endl;

            time=clock();
            parent.Astar(puzzle,m);
            time = clock() - time;

            cout << "Time=" << time /1000.0 <<endl;
            break;

        case 3:

            exit(0);
            break;

        default:
            cout <<"Invalid Entry.. " ;
            break;
        }
    }
    while(true);
    getch();
    return 0;
}
