#pragma once

#include "Utility.h"
#include "Note.h"

using namespace std;

class Chord
{
public:
	Chord(string _name, vector<Note> _note) : name(_name), note(_note) {}
	
	void print();

	static Chord stringToChord(string name, string chord);

	string name;
	vector<Note> note;
};


