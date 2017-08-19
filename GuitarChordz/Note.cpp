#include "Note.h"

const Note Note::null(-1, "");
const Note Note::A(0, "A");
const Note Note::As(1, "A#");
const Note Note::Bb(1, "Bb");
const Note Note::B(2, "B");
const Note Note::C(3, "C");
const Note Note::Cs(4, "C#");
const Note Note::Db(4, "Db");
const Note Note::D(5, "D");
const Note Note::Ds(6, "D#");
const Note Note::Eb(6, "Eb");
const Note Note::E(7, "E");
const Note Note::F(8, "F");
const Note Note::Fs(9, "F#");
const Note Note::Gb(9, "Gb");
const Note Note::G(10, "G");
const Note Note::Gs(11, "G#");
const Note Note::Ab(11, "Ab");

const Note Note::notes[noteNb] = { A,As,Bb,B,C,Cs,Db,D,Ds,Eb,E,F,Fs,Gb,G,Gs,Ab } ;

Note Note::getNote(string _name)
{
	for (int i(0); i < noteNb; i++)
		if (_name == notes[i].name) return notes[i];
	
	cout << "Note not found" << endl;
	return A;
}
Note Note::getNote(int _nb)
{
	for (int i(0); i < noteNb; i++)
		if (_nb == notes[i].nb) return notes[i];

	cout << "Note not found" << endl;
	return A;
}

void Note::print()
{
	cout << nb << name ;
}

Note Note::operator++(int)
{
	Note n;
	n = getNote((nb + 1) % 12);
	nb = n.nb; name = n.name;
	return n ;
}
Note Note::operator+=(int k)
{
	Note n;
	for (int i(0); i < k; i++)
	{
		n = getNote((nb + 1) % 12);
		nb = n.nb; name = n.name;
	}
	return n;
}
bool operator==(Note const& a, Note const& b)
{
	return a.nb == b.nb;
}
bool operator!=(Note const& a, Note const& b)
{
	return a.nb != b.nb;
}
Note operator+(Note n, int k)
{
	return (n += k) ;
}