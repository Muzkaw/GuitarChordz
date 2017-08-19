#pragma once

#include "Utility.h"
#include "Chord.h"

using namespace std;

struct ChordList
{
public:
	ChordList(string path);

	Chord getChord(string name);
	
	vector<Chord> chord;
};

