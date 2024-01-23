#include "trendtracker.h"



Trendtracker::Trendtracker(string filename) {
    fstream myFile;
    string data;
    Entry input;
    myFile.open(filename, ios::in);
    while (getline(myFile, data)) {
        input.hashtag = data;
        E.push_back(input);
    }
}

int Trendtracker::search(string ht) {
    int s = 0;
    int e = E.size();

    while (s <= e) {
        int m = (s + e) / 2;
        if (E[m].hashtag == ht) {
            return m;
        }
        
        if (ht < E[m].hashtag) {
            e = m - 1;
        }
        else {
            s = m + 1;
        }
    }
    return -1; 
}

int Trendtracker::size() {
    return E.size();
}

void Trendtracker::tweeted(string ht) {

    if (search(ht) != -1) {
        E[search(ht)].pop++;
    }

    int top = -1;
    int second = -1;
    int third = -1;

    if (E[search(ht)].pop > top || top == -1) {
        S.push_back
    }
}

int Trendtracker::popularity(string name) {
    if (search(name) != -1) {
        return E[search(name)].pop;
    }
    else {
        return -1;
    }
}



