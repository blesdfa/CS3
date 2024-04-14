#include <iostream>
#include <utility>
#include "vertex.h"
#include "solve.h"
#include "minpriorityqueue.h"
#include "limits.h"
#define toDigit(c) (c-'0')
using namespace std;

void clearData(unordered_map<string, Vertex*> &m) {
    for (auto x : m)
		{
			x.second->marked =false;
			x.second->bc = nullptr;
            x.second->path = false;
		}
}

void addDirectedEdge(string a, string b, unordered_map<string, Vertex*> &m, int w) {
    Vertex* aptr = m[a]; //O(1) a.c.
    Vertex* bptr = m[b];  //O(1) a.c.

    pair<Vertex*, int> newPair = make_pair(bptr, w);
    aptr->neighs.push_back(newPair);

}

void addBasicEdge(string a, string b, unordered_map<string, Vertex*> &m, int w) {
    addDirectedEdge(a, b, m, w);
    addDirectedEdge(b, a, m, w);
}

void bfs(string s, unordered_map<string, Vertex*> &m) {
    clearData(m);
    Vertex* start = m[s];
    queue<Vertex*> q;
    q.push(start);
    start->marked = true;
    
    while(!q.empty()) {
        Vertex* temp = q.front();
        q.pop();

        for (auto x : temp->neighs) {
            if (!x.first->marked) {
                x.first->marked = true;
                q.push(x.first);
                x.first->bc = temp;
            }
        }
    }
}

void dijsktras(unordered_map<string, Vertex*> &m, string s) {
    MinPriorityQueue<Vertex*> pq;
    for (auto x : m) {
        if (x.first == s) {
            pq.push(x.second, 0);
            // cout << "start vertex: " << s << endl;
        }
        else {
            x.second->weight = INT_MAX;
            pq.push(x.second, x.second->weight);
            // cout << "other vertex: " << x.first << endl;
        }
    }

    while(pq.size() != 0) {
        Vertex* x = pq.front();
        pq.pop();

        for (auto n : x->neighs) {
            if (x->weight + n.second < n.first->weight) {
                // cout << "updating weight" << endl;
                // cout << pq.size() << endl;
                n.first->weight = x->weight + n.second;
                n.first->bc = x;
                pq.decrease_key(n.first,n.first->weight);
            }
        }
    }

    // for (auto x : m) {
    //     cout << x.second->row << ", " << x.second->col << ": " << x.second->bc->row << ", " << x.second->bc->col << endl;
    // }
    // for (auto x : m) {
    //     cout << x.second->row << ", " << x.second->col << ": " << x.second->weight << endl;
    // }
}
void shortestPath(string start, string end, unordered_map<string, Vertex*> &m) {

    //Step 0: Get the start/end vertices
    Vertex* sPtr = m[start];
    Vertex* ePtr = m[end];
    sPtr->bc = nullptr;

    //Step 1: Run BFS on start vertex
    //to properly set breadcrumbs poineters
    //encoding shortest paths.
    // bfs(start, m);
    dijsktras(m, start);
    // cout << "check 2" << endl;

    //Step 2: Start at ePtr, following breadcrumbs
    //back to sPtr, return path of vertices you
    //visit.

    Vertex* current = ePtr;

        while (current != nullptr)
        {
            current->path = true;
            current = current->bc;
        }
}




string solve(string maze) {
    unordered_map<string, Vertex*> m;
    clearData(m);
    unordered_map<char, string> p;

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
    for(auto x : maze) {
        // cout << "[" << r << "]" << "[" << c << "]";
        if (x == ' ' || (x >= '0' && x <= '9')) {
            Vertex* v = new Vertex(r, c);
            string pos = to_string(r) + "," + to_string(c); // was failing on the biggest 18 by 40 maze because r,c 1,11 is the same as 11, 1 so the comma is neccesary took forever to debug
            m[pos] = v;
            if (c != 0) { //check left of pos
                leftPos = to_string(r) + "," + to_string(c - 1);
                if (m.find(leftPos) != m.end()) {
                    addBasicEdge(pos, leftPos, m, 1);
                }
            }

            if (r != 0) { //check above current pos
                upPos = to_string(r - 1) + "," + to_string(c);
                if (m.find(upPos) != m.end()) {
                    addBasicEdge(pos, upPos, m, 1);
                }
            }

            if (x >= '0' && x <= '9') {
                if (p.find(x) != p.end()) {
                    endPos = p[x];
                    addBasicEdge(pos, endPos, m, toDigit(x));
                }
                p[x] = pos;
            }
        }

        if (x == ' ') {
            if (flag == 0 && (c == 0 || r == 0 || c == maxCols - 1 || r == maxRows - 1)) {
                startPos = to_string(r) + "," + to_string(c);
                flag++;
            }
            else if (flag == 1 && (c == 0 || r == 0 || c == maxCols - 1 || r == maxRows - 1)) { //check all possible
                endPos = to_string(r) + "," + to_string(c);
                flag++;
            }
        }

        if (x == '\n') {
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

    shortestPath(startPos, endPos, m);
    // for (auto x : m) {
    //     if (x.second->marked) {
    //         cout << x.second->row << ", " << x.second->col << endl;
    //     }
    // }

    for (auto x : maze) {
        if (x == '\n') {
            r++;
            c = -1;
            testing = testing + x;
        }

        if (x == ' ') {
            string pos = to_string(r) + "," + to_string(c);
            Vertex* checker = m[pos];
            if (checker->path) {
                testing = testing + "o";
            }
            else {
                testing = testing + x;
            }
        }

        if (x >= '0' && x <= '9') {
            string pos = to_string(r) + "," + to_string(c);
            Vertex* checker = m[pos];
            if (checker->path) {
                testing = testing + "o";
            }
            else {
                testing = testing + x;
            }
        }
        if (x == '#') {
            testing = testing + x;
        }
        c++;
    }
    maze = testing;
    for (auto x : maze) {
        cout << x;
    }

    // for (auto x : m) {
    //     cout << x.first << ": ";
    //     for (auto i : x.second->neighs) {
    //         // cout << i.first->row << " " <<  i.first->col << ", ";
    //         cout << i.second << ",";
    //     }
    //     cout << endl;
    // }
    return maze;
}