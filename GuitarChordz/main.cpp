#include "Utility.h"
#include "ChordList.h"

using namespace std;

int main()
{
	vector<string> data;
	data = readCfgFile("cfg.txt");

	ChordList chordList("chord_list.txt");

	Chord tuning = chordList.getChord(data[0]); //guitar tuning
	Chord chordRef = chordList.getChord(data[1]) ; //chord of reference

	string fileName = "Chord Chart " + chordRef.name + ".txt";
	ofstream file(fileName, ios::out);

	int usableFret = stoi(data[2]);
	int extension = min(stoi(data[3]),5);
	int continuousStringSet = stoi(data[4]);
	int minStringSet = stoi(data[5]);

	vector<vector<Note> > guitar; //representation of the notes on the guitar
	for (int i(0); i < 6; i++)
	{
		vector<Note> corde(usableFret, Note::null);
		guitar.push_back(corde);
	}

	for (int i(0); i < 6; i++) //setting notes on the guitar
	{
		guitar[i][0] = tuning.note[i];
		for (int j(1); j < usableFret; j++)
			guitar[i][j] = guitar[i][0]+j ;
	}

	for (int i(0); i < 6; i++) //selecting notes belonging to the reference chord on the guitar
	{
		for (int j(0); j < usableFret; j++)
		{
			int flag = 0;
			for (int k(0); k < chordRef.note.size(); k++)
				if (guitar[i][j] == chordRef.note[k])
					flag = 1;
			if (flag == 0) guitar[i][j] = Note::null;
		}
	}

	vector<vector<int> > fingering; //list of all fingering for the reference chord
	bitset<6> stringset; //a 6bit number that represent the combinations of strings on the guitar
	vector<int> fret(6); //the fret used in the current fingering to be represented on the chart
	for (int i(0); i < 64; i++) //for all string combinations (2^6=64)
	{
		stringset = i;

		int flagU(0), flagD(0), group(1);
		for (int j(0); j < 6; j++)
			if (stringset[j] == 1 && flagD == 0) flagU = 1;
			else if(stringset[j] == 0 && flagU == 1) flagD = 1;
			else if (stringset[j] == 1 && flagD == 1) group = 0;

		if (sumByte(stringset) >= max((int)chordRef.note.size(),minStringSet) && (group == 1 || continuousStringSet == 0)) //if our string combination has enough strings to play all the notes in the reference chord
		{
			for (fret[0] = 0; fret[0] <= (usableFret - 1) * stringset[0]; fret[0]++) //loop all the combinations
			for (fret[1] = 0; fret[1] <= (usableFret - 1) * stringset[1]; fret[1]++)
			for (fret[2] = 0; fret[2] <= (usableFret - 1) * stringset[2]; fret[2]++)
			for (fret[3] = 0; fret[3] <= (usableFret - 1) * stringset[3]; fret[3]++)
			for (fret[4] = 0; fret[4] <= (usableFret - 1) * stringset[4]; fret[4]++)
			for (fret[5] = 0; fret[5] <= (usableFret - 1) * stringset[5]; fret[5]++)
			{
				bool flag = true;
				for (int j(0); j < 6; j++) //if a string is played but doesnt have a matching note, we discard the chord
					if (stringset[j] && guitar[j][fret[j]] == Note::null) flag = false;
				
				if (flag)
				{
					bool flag2 = true;
					for (int j(0); j < chordRef.note.size(); j++) //if the generated chord doesnt contain at least 1 instance of each note from the reference chord, we discard the generated chord
						if ((stringset[0] == 0 || guitar[0][fret[0]] != chordRef.note[j]) && (stringset[1] == 0 || guitar[1][fret[1]] != chordRef.note[j]) &&
							(stringset[2] == 0 || guitar[2][fret[2]] != chordRef.note[j]) && (stringset[3] == 0 || guitar[3][fret[3]] != chordRef.note[j]) &&
							(stringset[4] == 0 || guitar[4][fret[4]] != chordRef.note[j]) && (stringset[5] == 0 || guitar[5][fret[5]] != chordRef.note[j]))
							flag2 = false;
		
					if (flag2)
					{
						vector<int> fingeringGen;

						for (int j(0); j < 6; j++)
							if (stringset[j]) fingeringGen.push_back(fret[j]); else fingeringGen.push_back(-1);

						if (maxArr(fingeringGen) - minArr(fingeringGen) < extension) //less than 5 fret hand extension
							if (nbDgt(fingeringGen) <= 4 || (nbDgt(fingeringGen) > 4 && nbDgt(fingeringGen) - barre(fingeringGen) <= 4)) //discard chords that require more than 4 fingers but keep bar chords
								fingering.push_back(fingeringGen);
					}
				}
			}
		}
	}

	file << fingering.size() << " fingerings found for the chord " << data[1] << endl << endl << endl;

	printAcc(file, fingering, guitar, usableFret);
	cout << "Done!" << endl;
	//system("pause");

	return 0;
}
