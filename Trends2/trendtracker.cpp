#include "trendtracker.h"
#include <iostream>



Trendtracker::Trendtracker(string filename) {
    ifstream myFile(filename);
    string hashtag;
    Entry input;
    if (myFile.is_open()) {
        while (getline(myFile, hashtag)) {
            input.hashtag = hashtag;
            input.pop = 0;
            E.push_back(input);
        }
        myFile.close();
    }
    S.push_back(-1);
    S.push_back(-1);
    S.push_back(-1);
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
    cout << "TEST HERE!!!" << E[index].hashtag << E[index].pop << endl;
    int top = S[0];
    int second = S[1];
    int third = S[2];

    cout << "THIS IS AT THE TOP|| " << E[top].hashtag << ": " << E[top].pop << endl;
    S.push_back(top);
    S.push_back(second);
    S.push_back(third);

    if (E[index].pop > E[top].pop || top == -1) {
        third = second;
        second = top;
        top = index;
        S[0] = top;
        S[1] = second;
        S[2] = third;
        cout << "check 1" << endl;
        cout << top << second << third << endl;
        cout << E[index].pop << "|||| " << E[top].pop << endl; 
        for (int i = 0; i < E.size(); i++) {
            cout << E[i].hashtag << " pop: " << E[i].pop << endl;
        }
    }
    if (E[index].pop > E[second].pop || second == -1) {
        if (E[index].pop == E[top].pop) {
            return;
        }
        third = second;
        second = index;
        S[1] = second;
        S[2] = third;
        cout << "check 2" << endl;
        cout << top << second << third << endl;
    }
    if (E[index].pop > E[third].pop || third == -1) {
         if (E[index].pop == E[top].pop) {
            return;
         }
         if (E[index].pop == E[second].pop) {
            return;
         }
        third = index;
        S[2] = third;
        cout << "check 3" << endl;
        cout << top << second << third << endl;
    }
    cout << top << second << third << endl;
    cout << "S VECTOR: " << S[0] << S[1] << S[2] << endl;
    string one = "#z";
    string two = "#cs4all";

    if (one < two) {
        cout << "LESS THAN" << endl;
    }
    cout << E[top].hashtag << endl;


    // if (top != -1) {
    //     S.push_back(top);
    // }
    // if (second != -1) {
    //     S.push_back(second);
    // }
    // if (third != -1) {
    //     S.push_back(third);
    // }
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

    int top = S[0];
    int second = S[1];
    int third = S[2];

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



