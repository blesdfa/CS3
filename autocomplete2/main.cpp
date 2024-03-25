
#include <iostream>
#include <fstream>
#include <string>
#include "trie.h"
using namespace std;

int main()
{
	trie T;

	ifstream infile("words2.txt");

	string word;
	int freq;
	while (infile >> word)
	{
		infile >> freq;
		T.insert(word);
	}

	T.printAll();

	return 0;
}