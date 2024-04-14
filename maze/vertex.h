#include <vector>

using namespace std;

// A helper class implementing a vertex in 
// an adjacency-list-based graph.
class Vertex
{
        public:
                Vertex(int r, int c)
                {
                        row = r;
                        col = c;
                        marked = false;
                        path = false;
                        Vertex* bc = nullptr;
                        int weight = 0;
                }

                // Corresponding row and column location in maze
                int row;
                int col;

                // List of neighboring vertices
                vector<pair<Vertex*, int>> neighs;
                // vector<Vertex*> neighs;
                bool marked;
                Vertex* bc;
                bool path;
                int weight;
};
