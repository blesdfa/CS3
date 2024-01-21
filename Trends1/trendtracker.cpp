#include "trendtracker.h"

Trendtracker::Trendtracker() {}

void Trendtracker::insert(string ht) {

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

void Trendtracker::insert(string ht) {
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