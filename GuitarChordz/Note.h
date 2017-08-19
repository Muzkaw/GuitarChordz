#pragma once

#include <string>
#include <iostream>

using namespace std;

class Note
{
public:
	Note() : nb(0), name("A") {}
	Note(int _nb, string _name) : nb(_nb), name(_name) {}

	static const Note null;
	static const Note A ;
	static const Note As;
	static const Note Bb;
	static const Note B;
	static const Note C;
	static const Note Cs;
	static const Note Db;
	static const Note D;
	static const Note Ds;
	static const Note Eb;
	static const Note E;
	static const Note F;
	static const Note Fs;
	static const Note Gb;
	static const Note G;
	static const Note Gs;
	static const Note Ab;

	static const int noteNb = 17;
	static const Note notes[noteNb];

	static Note getNote(string _name);
	static Note getNote(int _nb);

	void print();

	string name;
	int nb;

	Note operator++(int);
	Note operator+=(int k);
};

bool operator==(Note const& a, Note const& b);
bool operator!=(Note const& a, Note const& b);
Note operator+(Note n, int k);
