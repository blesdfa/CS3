#include <iostream>
#include <utility>
#include "vertex.h"
#include "solve.h"
using namespace std;

void clearData(unordered_map<string, Vertex*> &m) {
    for (auto x : m)
		{
			x.second->marked =false;
			x.second->bc = nullptr;
            x.second->path = false;
            cout << "clearing data" << endl;
		}
}

void addDirectedEdge(string a, string b, unordered_map<string, Vertex*> &m) {
    Vertex* aptr = m[a]; //O(1) a.c.
    Vertex* bptr = m[b];  //O(1) a.c.

    aptr->neighs.push_back(bptr);
}

void addBasicEdge(string a, string b, unordered_map<string, Vertex*> &m) {
    addDirectedEdge(a, b, m);
    addDirectedEdge(b, a, m);
}

void bfs(string s, unordered_map<string, Vertex*> &m) {
    clearData(m);
    Vertex* start = m[s];
    cout << "check 1" << endl;
    queue<Vertex*> q;
    cout << "check" << endl;
    q.push(start);
    cout << "check 3" << endl;
    start->marked = true;
    cout << "check 4" << endl;
    

    while(!q.empty()) {
        Vertex* temp = q.front();
        q.pop();

        for (auto x : temp->neighs) {
            if (!x->marked) {
                x->marked = true;
                q.push(x);
                x->bc = temp;
            }
        }
    }
}

string shortestPath(string start, string end, unordered_map<string, Vertex*> &m) {

    //Step 0: Get the start/end vertices
    Vertex* sPtr = m[start];
    Vertex* ePtr = m[end];

    //Step 1: Run BFS on start vertex
    //to properly set breadcrumbs poineters
    //encoding shortest paths.
    bfs(start, m);

    //Step 2: Start at ePtr, following breadcrumbs
    //back to sPtr, return path of vertices you
    //visit.
    string output;

    Vertex* current = ePtr;

    if (current->marked) {
        while (current != nullptr)
        {
            output = "[" + to_string(current->row) + "]" + "[" + to_string(current->col) + "]" + output;
            current->path = true;
            current = current->bc;
        }
    } else {
        output = "No path exists";
    }

    return output;
}


string solve(string maze) {
    unordered_map<string, Vertex*> m;

    int c = 0;
    int r = 0;
    int flag = 0;
    int maxRows = 0;
    int maxCols = 0;
    int counter = 0;
    int flagSize = 0;
    string leftPos = "";
    string upPos = "";
    string startPos = "";
    string endPos = "";

    for (auto x : maze) {
        if (x == '\n') {
            maxRows++;
            flagSize++;
        }
        if (flagSize == 1) {
            maxCols = counter;
            flagSize++;
        }
        counter++;
    }
    cout << maxRows << " by " << maxCols << endl;

    for(auto x : maze) {
        cout << "[" << r << "]" << "[" << c << "]";
        if (x == ' ') {
            Vertex* v = new Vertex(r, c);
            string pos = to_string(r) + to_string(c);
            m[pos] = v;
            if (r != 0 and c != 0) { //check left of pos
                leftPos = to_string(r) + to_string(c - 1);
                if (m.find(leftPos) != m.end()) {
                    addBasicEdge(pos, leftPos, m);
                }
            }

            if (r != 0) { //check above current pos
                upPos = to_string(r - 1) + to_string(c);
                if (m.find(upPos) != m.end()) {
                    addBasicEdge(pos, upPos, m);
                }
            }
        }

        if (x == ' ') {
            if (c == 0 || r == 0) {
                startPos = to_string(r) + to_string(c);
                flag++;
                cout << "found opening" << startPos;
            }

            if (c == maxCols - 1 || r == maxRows - 1) {
                endPos = to_string(r) + to_string(c);
                flag++;
                cout << "found opening" << endPos;
            }
        }

        if (x == '\n') {
            cout << "\n";
            r++;
            c = -1;
        }
        c++;
        leftPos = "";
        upPos = "";
    }
    r = 0;
    c = 0;
    string testing = "";
    int verCount = 0;
    // for (auto x : m) {
    //     cout << x.second->row << x.second->col << endl;
    //     verCount++;
    // }
    // cout << verCount;
    bfs(startPos, m);
    // cout << shortestPath(startPos, endPos, m) << endl;
    // for (auto x : maze) {
    //     if (x == '\n') {
    //         r++;
    //         c = -1;
    //         testing = testing + x;
    //     }
    //     if (x == ' ') {
    //         Vertex* checker = m[startPos];
    //         if (checker->path) {
    //             testing = testing + "o";
    //         }
    //     }

    //     if (x == '#') {
    //         testing = testing + x;
    //     }
    //     c++;
    // }
    maze = testing;
    for (auto x : maze) {
        cout << x;
    }
    return maze;
}