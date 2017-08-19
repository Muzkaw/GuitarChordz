#include "ChordList.h"

ChordList::ChordList(string path)
{
	ifstream cfg(path);
	string line;
	string dataBuf;
	string strBuf;

	do
	{
		cfg >> strBuf >> dataBuf;
		strBuf.pop_back();
		
		chord.push_back(Chord::stringToChord(strBuf, dataBuf));

	} while (getline(cfg, line));

	vector<Chord> chordSav = chord;
	vector<Chord> chordBuf = chord;

	for (int i(1); i < Note::noteNb; i++)
	{
		for (int j(0); j < chordSav.size(); j++)
		{
			string name = chordSav[j].name;
			for (int k(0); k < chordSav[j].note.size(); k++) chordBuf[j].note[k] = chordSav[j].note[k] + Note::notes[i].nb ;
			vector<Note> note = chordBuf[j].note;

			name.replace(0, 1, Note::notes[i].name);

			chord.push_back(Chord(name, note));
		}
	}
}

Chord ChordList::getChord(string name)
{
	for (int i(0); i < chord.size(); i++)
		if (name == chord[i].name) return chord[i];

	cout << "Chord not found" << endl;
	return Chord(chord[0]);
}