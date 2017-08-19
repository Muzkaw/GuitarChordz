#include "Chord.h"

void Chord::print()
{
	cout << name << ": ";
	for (int i(0); i < note.size(); i++) {
		note[i].print(); cout << " ";
	}
	cout << endl;
}
Chord Chord::stringToChord(string name, string chord)
{
	stringstream ss(chord);
	vector<Note> note;

	while (ss.good())
	{
		string substr;
		getline(ss, substr, ',');
		note.push_back(Note::getNote(substr));
	}

	return Chord(name, note);
}