
#ifndef TRENDTRACKER_H
#define TRENDTRACKER_H


//You may not include any additional libraries for this assignment,
//other than those listed below.
#include <vector>
#include <string>

using namespace std;

class Trendtracker
{
	// For the mandatory running times below:
	// n is the number of hashtags in the Trendtracker.

	public:
		// Creates a new Trendtracker tracking no hashtags.
		//
		// Must run in O(1) time.
		Trendtracker() {};

		// Inserts a hashtag (tweeted 0 times) into the Trendtracker.
		// If the hashtag already is in Trendtracker, does nothing.
		//
		// Must run in O(n) time.
		void insert(string ht) {

            for (int i = 0; i < E.size(); i++) {
                if (E[i].hashtag == ht) {
                    return;
                }
            }
            Entry x;
            x.hashtag = ht;
            x.pop = 0;
            E.push_back(x);
        }

		// Return the number of hashtags in the Trendtracker.
		//
		// Must run in O(1) time.
		int size() {
            return E.size();
        }

		// Adds 1 to the total number times a hashtag has been tweeted.
		// If the hashtag does not exist in TrendTracker, does nothing.
		//
		// Must run in O(n) time.
		void tweeted(string ht) {
            for (int i = 0; i < E.size(); i++) {
                if (E[i].hashtag == ht) {
                    E[i].pop++;
                }
            }
        }

		// Returns the number of times a hashtag has been tweeted.
		// If the hashtag does not exist in Trendtracker, returns -1.
		//
		// Must run in O(n) time.
		int popularity(string name) {
            for (int i = 0; i < E.size(); i++) {
                if (E[i].hashtag == name) {
                    return E[i].pop;
                }
            }
            return -1;
        }

		// Returns a most-tweeted hashtag.
		// If the Trendtracker has no hashtags, returns "".
		//
		// Must run in O(n) time.
		string top_trend() {
            int biggest = E[0].pop;
            string topString = "";
            for (int i = 1; i < E.size(); i++) {
                if (biggest < E[i].pop) {
                    biggest = E[i].pop;
                    topString = E[i].hashtag;
                }
            }
            return "test";
        }

		// Fills the provided vector with the 3 most-tweeted hashtags,
		// in order from most-tweeted to least-tweeted.
		//
		// If there are fewer than 3 hashtags, then the vector is filled
		// with all hashtags (in most-tweeted to least-tweeted order).
		//
		// Must run in O(n) time.
		void top_three_trends(vector<string> &T);

		// Remove the given hashtag from the trendtracker.
		//
		// Must run in O(n) time.
		void remove(string ht);

		// Fills the provided vector with the k most-tweeted hashtags,
		// in order from most-tweeted to least-tweeted.
		//
		// If there are fewer than k hashtags, then the vector is filled
		// with all hashtags (in most-tweeted to least-tweeted order).
		//
		// Must run in O(nk) time.
		void top_k_trends(vector<string> &T, int k);

	private:
		// A simple class representing a hashtag and
		// the number of times it has been tweeted.
		class Entry
		{
			public:
				string hashtag;
				int pop;
		};


		// Entries containing each hashtag and its popularity.
		vector<Entry> E;
};

#endif
