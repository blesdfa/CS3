#include "trendtracker.h"
#include <iostream>



Trendtracker::Trendtracker(string filename) {
    ifstream myFile(filename);
    string hashtag;
    Entry input;
    int count = 0;
    if (myFile.is_open()) {
        while (getline(myFile, hashtag)) {
            input.hashtag = hashtag;
            input.pop = 0;
            E.push_back(input);
            if (count < 3) {
                S.push_back(count);
                count++;
            }
        }
        myFile.close();
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

    int index = search(ht);
    if (index != -1) {
        E[index].pop++;
    }
    
    int top = S[0];
    int second = S[1];
    int third = S[2];
    // cout << "Start of if blocks|| " << top << second << third << endl;

    if (E[index].pop > E[top].pop) {
        cout << "check 1" << endl;
        second = top;
        top = index;
        S[0] = top;
        S[1] = second;
    }
    else if (E[index].pop > E[second].pop) {
        if (E[index].hashtag == E[top].hashtag) {
            return;
        }
        cout << "check 2" << endl;
        third = second;
        second = index;
        S[1] = second;
        S[2] = third;
    }
    else if (E[index].pop > E[third].pop) {
        if (E[index].hashtag == E[second].hashtag) {
            return;
        }
        cout << E[index].hashtag << endl;
        cout << "check 3" << endl;
        third = index;
        S[2] = third;
    }
}

int Trendtracker::popularity(string name) {
    int index = search(name);
    if (index != -1) {
        return E[index].pop;
    }
    else {
        return -1;
    }
}

string Trendtracker::top_trend() {
    if (E.size() == 0) {
        return "";
    }
    int topIndex = S[0];
    return E[topIndex].hashtag;
}

void Trendtracker::top_three_trends(vector<string> &T) {
    T.clear();
    int top = S[0];
    int second = S[1];
    int third = S[2];
    cout << top << " | " <<  second << " | " << third << endl;

    if (E.size() == 1) {
        T.push_back(E[top].hashtag);
        return;
    }
    T.push_back(E[top].hashtag);
    T.push_back(E[second].hashtag);
    T.push_back(E[third].hashtag);
}



