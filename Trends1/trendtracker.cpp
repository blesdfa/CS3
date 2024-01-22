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

int Trendtracker::size() {
    return E.size();
}

void Trendtracker::tweeted(string ht) {
    for (int i = 0; i < E.size(); i++) {
        if (ht == E[i].hashtag) {
            E[i].pop++;
        }
    }
}

int Trendtracker::popularity(string name) {
    for (int i = 0; i < E.size(); i++) {
        if (E[i].hashtag == name) {
            return E[i].pop;
        }
    }
    return -1;
}

string Trendtracker::top_trend() {
    if (E.size() == 0) {
        return "";
    }

    int biggest = 0;
    string topString = "";
    for (int i = 0; i < E.size(); i++) {
        if (E[i].pop >= biggest) {
            biggest = E[i].pop;
            topString = E[i].hashtag;
        }
    }
    return topString;
}

void Trendtracker::top_three_trends(vector<string> &T) {
    T.clear();
    if (E.size() == 0) {
        return;
    }

    int top = -1;
    int second = -1;
    int third = -1;

    for (int i = 0; i < E.size(); i++) {
        if (E[i].pop > E[top].pop || top == -1) {
            third = second;
            second = top;
            top = i;
        }
        else if (E[i].pop > E[second].pop || second == -1) {
            third = second;
            second = i;
        }
        else if (E[i].pop > E[third].pop || third == -1) {
            third = i;
        }
    }

    if (top != -1) {
        T.push_back(E[top].hashtag);
    }
    if (second != -1) {
        T.push_back(E[second].hashtag);
    }
    if (third != -1) {
        T.push_back(E[third].hashtag);
    }
}


void Trendtracker::remove(string ht) {
    for (int i = 0; i < E.size(); i++) {
        if (E[i].hashtag == ht) {
            E.erase(E.begin() + i);
        }
    }
}

void Trendtracker::top_k_trends(vector<string> &T, int k) {
    vector<Entry> TOP;

    for (auto i : E) {
        TOP.push_back(i);
        int x = TOP.size() - 1;
        while ( x > 0 && TOP[x].pop > TOP[x - 1].pop) {
            swap(TOP[x], TOP[x - 1]);
            x--;
        }

        if (TOP.size() > k) {
            TOP.pop_back();
        }
    }
    T.clear();
    for (int i = 0; i < TOP.size(); i++) {
        T.push_back(TOP[i].hashtag);
    }
}
