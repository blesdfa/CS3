
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
	// (they are average case, but not worst-case).

	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
			
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size()
		{
            return H.size();
		}	

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
            H.push_back(make_pair(x, p));
			I[x] = H.size() - 1;
            bubbleUp(H.size() - 1);
		}

		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front()
		{
			// TODO
			if (H.size() != 0) {
            	return H[0].first;	
			}
		}

		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop() {
			if (!H.size() == 0) {
				H[0] = H.back();
				H.pop_back();
				bubbleDown(0);
			}
		}


		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			// TODO
			if (I[x]) {
				H[I[x]].second = new_p;
				bubbleUp(I[x]);
			}
		}

		void getKey(T x) {
			cout << H[I[x]].first << endl;
		}



	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.

        int parent(int i) {
            return (i - 1) / 2;
        }

		int lChild(int i) {
			return (i * 2) + 1;
		}

		int rChild(int i) {
			return (i * 2) + 2;
		}

        void bubbleUp(int i) {
            while (H[i].second < H[parent(i)].second) {
				I[H[parent(i)].first] = i;
				I[H[i].first] = parent(i);

                swap(H[i], H[parent(i)]);
                i = parent(i);
            }
        }

		void bubbleDown(int i) {
			while (true) {
				int smaller = i;
				if (lChild(i) < H.size() && H[lChild(i)].second < H[smaller].second) {
					smaller = lChild(i);
				}
				if (rChild(i) < H.size() && H[rChild(i)].second < H[smaller].second) {
					smaller = rChild(i);
				}

				if (smaller == i) {
					break;
				} else {
					I[H[i].first] = smaller;
					I[H[smaller].first] = i;

					swap(H[i], H[smaller]);
					i = smaller;
				}
			}
		}

};

#endif 
