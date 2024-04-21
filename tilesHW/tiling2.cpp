
#include "tiling.h"
#include "vertex.h"
#include <string>

using namespace std;


// Finds a (shortest according to edge length) augmenting path
// from s to t in a graph with vertex set V.
// Returns whether there is an augmenting path.
bool augmenting_path(Vertex* s, Vertex* t, 
        unordered_set<Vertex*> V, vector<Vertex*> &P)
{
        // Check that s and t aren't nullptr
        if (s == nullptr || t == nullptr)
	{
		cerr << "augmenting_path() was passed nullptr s or t." << endl;
		abort();
	}

        // Check that s and t are in the graph
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "augmenting_path() was passed s or t not in V." << endl;
		abort();
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "augmenting_path() was passed invalid vertex." << endl;
				abort();
			}

        // Since augmenting paths should have the fewest edges,
	// not the minimum weight, run BFS.
	queue<Vertex*> Q;
	Q.push(s);

	unordered_set<Vertex*> R;
	R.clear(); 
	R.insert(s);

	unordered_map<Vertex*, Vertex*> prev;

	while (!Q.empty())
	{
		Vertex* cur = Q.front();
		Q.pop();

		for (Vertex* nei : cur->neighs)
		{
			// Must have positive edge weight
			if (cur->weights[nei] == 0)
				continue;

			if (R.find(nei) == R.end())
			{
				Q.push(nei);
				R.insert(nei);
				prev[nei] = cur; 
			}
		}
	}      

        // If BFS never reached t
        if (R.find(t) == R.end())
                return false;

        // Reconstruct shortest path backwards
        P.clear();
        P.push_back(t);
        while (P[P.size()-1] != s)
                P.push_back(prev[P[P.size()-1]]);

        // Reverse shortest path
        for (int i = 0; i < P.size()/2; ++i)
		swap(P[i], P[P.size()-1-i]);

        return true;
}

// Returns the maximum flow from s to t in a weighted graph with vertex set V.
// Assumes all edge weights are non-negative.
int max_flow(Vertex* s, Vertex* t, unordered_set<Vertex*> V)
{
// If s or t is invalid.
	if (s == nullptr || t == nullptr)
{
	cerr << "max_flow() was passed nullptr s or t." << endl;
	abort(); 
}

// If s or t is not in the vertex set.
	if (V.find(s) == V.end() || V.find(t) == V.end())
{
	cerr << "max_flow() was passed s or t not in V." << endl;
	abort(); 
}

// Check that every vertex has valid neighs/weights.
for (Vertex* v : V)
	for (Vertex* vn : v->neighs)
		if (v->weights.find(vn) == v->weights.end())
		{
			cerr << "max_flow() was passed invalid vertex." << endl;
			abort();
		}

	// Create a deep copy of V to use as the residual graph
	unordered_set<Vertex*> resV;
	unordered_map<Vertex*, Vertex*> C; // Maps vertices in V to copies in resV
	for (Vertex* vp : V)
	{
			string pos = "-1";
			Vertex* rp = new Vertex;
			resV.insert(rp);
			C[vp] = rp;
	}
	for (Vertex* vp : V)
			for (Vertex* np : vp->neighs)
			{
					C[vp]->neighs.insert(C[np]);
					C[vp]->weights[C[np]] = vp->weights[np];
			}
// Add any missing necessary "back" edges. 
	for (Vertex* vp : V)
			for (Vertex* np : vp->neighs)
	{
		if (C[np]->neighs.find(C[vp]) == C[np]->neighs.end())
		{
			C[np]->neighs.insert(C[vp]);
			C[np]->weights[C[vp]] = 0;
		}
	}

	// Run Edmonds-Karp
	while (true)
	{
			// Find an augmenting path
			vector<Vertex*> P;
			if (!augmenting_path(C[s], C[t], resV, P))
					break;  
			// Update residual graph
			for (int i = 0; i < P.size()-1; ++i)
			{
					--((*(resV.find(P[i])))->weights[P[i+1]]);
					++((*(resV.find(P[i+1])))->weights[P[i]]);
			}
	}

	// Compute actual flow amount
	int flow = 0;
	for (Vertex* snp : C[s]->neighs)
			flow += 1 - C[s]->weights[snp];

	// Delete residual graph
	for (Vertex* vp : resV)
			delete vp;

	return flow;
}

void addDirectedEdge(string a, string b, unordered_map<string, Vertex*> m, int w) {
    Vertex* aptr = m[a]; //O(1) a.c.
    Vertex* bptr = m[b];  //O(1) a.c.

	aptr->neighs.insert(bptr);
	aptr->weights[bptr] = 1;

    // pair<Vertex*, int> newPair = make_pair(bptr, w);
    // aptr->neighs.push_back(newPair);
	// aptr->neighs[a] = newPair

}

void addDirectedEdgeV(Vertex* a, Vertex* b) {
	a->neighs.insert(b);
	a->weights[b] = 1;
}

void addBasicEdge(string a, string b, unordered_map<string, Vertex*> m, int w) {
    addDirectedEdge(a, b, m, w);
    addDirectedEdge(b, a, m, w);
}


bool has_tiling(string floor) {
	unordered_set<Vertex*> V;
	unordered_map<string, Vertex*> G;
	unordered_map<string, Vertex*> R;
	unordered_map<string, Vertex*> m;

    int r = 0;
	int c = 0;
	bool color = true;
	// Green is True
	// Red is false

	string pos = "";
	string leftPos = "";
	string upPos = "";
	int maxRows = 0;
    int maxCols = 0;
    int counter = 0;
    int flagSize = 0;

	for (auto x : floor) {
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

    for (auto x : floor) {
        if (x == '#') {
            x = color ? 'G' : 'R';
            cout << x;
            color = !color;
        }
        if (x == ' ') {
            x = color ? 'G' : 'R';
            cout << x;
            pos = to_string(r) + "," + to_string(c);

            Vertex* v = new Vertex(color, pos);
            m[pos] = v;

            if (c != 0) {
                leftPos = to_string(r) + "," + to_string(c - 1);
                if (m.find(leftPos) != m.end()) {
                    if (color == false) {
                        // cout << "Adding edge if color is red" << leftPos << " to " << pos;
                        addDirectedEdge(leftPos, pos, m, 1);
                    }
                    else {
                        addDirectedEdge(pos, leftPos, m, 1);
                    }
                }
            }

            if (r != 0) {
                upPos = to_string(r - 1) + "," + to_string(c);
                if (m.find(upPos) != m.end()) {
                    if (color == false) {
                        // cout << "Adding edge if color is red" << pos << " to " << upPos << endl;
                        addDirectedEdge(upPos, pos, m, 1);
                    }
                    else {
                        // cout << "Adding edge if color is green" << pos << " to " << upPos << endl;
                        addDirectedEdge(pos, upPos, m, 1);
                    }
                }
            }

            if (v->color) {
                G[pos] = v;
            }
            else {
                R[pos] = v;
            }
            color = !color;
        }
        if (x == '\n') {
            if ( maxCols % 2 != 0) {
                cout << x;
                r++;
                c = 0;
                continue;
            }
            color = !color;
            r++;
            c = -1;
            cout << x;
        }
        c++;
        pos = "";
        upPos = "";
        leftPos = "";
    }

    for (auto x : m) {
        cout << x.second->pos << ": " << x.second->neighs.size() << endl;
    }
    cout << m.size() << endl;

    Vertex* s = new Vertex;
    Vertex* e = new Vertex;
    V.insert(s);
    V.insert(e);
    for (auto x : G) {
        addDirectedEdgeV(s, x.second);
    }

    for (auto x : R) {
        addDirectedEdgeV(x.second, e);
    }

    for (auto x : m) {
        V.insert(x.second);
    }
    cout << "G : " << G.size() << endl;
    cout << "R : " << R.size() << endl;
    cout << max_flow << endl;

    if (G.size() != R.size()) {
        return false;
    }

    return max_flow(s, e, V) == s->neighs.size();

 }


