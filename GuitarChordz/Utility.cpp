#include "Utility.h"

int sumByte(bitset<6> b)
{
	int result(0);
	for (int i(0); i < b.size(); i++) result += b[i];
	return result;
}

int maxArr(vector<int> arr)
{
	if (arr.size()>0)
	{
		int result = arr[0];
		for (int i(1); i < arr.size(); i++)
			if (result < arr[i] && arr[i] > 0) result = arr[i];

		return result;
	}
	else return 0;
}
int minArr(vector<int> arr)
{
	if (arr.size()>0)
	{
		int result = arr[0];
		for (int i(1); i < arr.size(); i++)
			if (arr[i] > 0 && (result == -1 || result > arr[i]))
				result = arr[i];
		if (result == -1)
			result = 1;
		return result;
	}
	else return 0;
}

int nbDgt(vector<int> dgt)
{
	int result = 0;
	for (int i(0); i < dgt.size(); i++)
		if (dgt[i] > 0) result++;
	return result;
}

int barre(vector<int> dgt)
{
	int result = 0;
	int key = dgt.back();

	for (int i(dgt.size() - 2); i >= 0; i--)
		if (dgt[i] == key) result++;
		else if (dgt[i] < key && dgt[i] >= 0) return 0;

	return result;
}

void printAcc(ofstream &file, vector<vector<int>> dgt, vector<vector<Note> > guitar, int usableFret)
{
	int chordPerLine = 6;
	for (int d(0); d < dgt.size(); d+= chordPerLine)
	{
		for (int w(0); w < chordPerLine; w++)
		{
			if (d + w < dgt.size())
			{
				for (int i(0); i < 11; i++)
					if (i % 2 == 0)
						if (dgt[d + w][i / 2] != -1 && dgt[d + w][i / 2] <10) file << dgt[d + w][i / 2] << "  ";
						else if (dgt[d + w][i / 2] != -1) file << dgt[d + w][i / 2] ;
						else file << "X  ";

						file << "     ";
						file << "  ";
			}
		}
		file << endl << endl;
		for (int w(0); w < chordPerLine; w++)
		{
			if (d + w < dgt.size())
			{
				for (int i(0); i < 11; i++)
					if (i % 2 == 0)
						if (dgt[d + w][i / 2] != 0) file << "   ";
						else if (dgt[d + w][i / 2] == 0)
						{
							file << guitar[i / 2.0][dgt[d + w][i / 2]].name;
							for (int s(0); s < 3 - guitar[i / 2.0][dgt[d + w][i / 2]].name.size(); s++) file << " ";
						}

						file << "     ";
						file << "  ";
			}
		}
		
		for (int i(0); i < 11; i++)
		{
			file << endl;
			for (int w(0); w < min(chordPerLine, (int)(dgt.size() - d)); w++)
			{
				if (d + w < dgt.size())
				{
					if (i % 2 == 0 && minArr(dgt[d + w]) + i / 2 == 1) file << "================     ";
					else if (i % 2 == 0) file << "----------------     ";
					else
					{
						for (int j(0); j < 11; j++)
							if (j % 2 == 0)
								if (dgt[d + w][j / 2] == (i + 1) / 2 + minArr(dgt[d + w]) - 1)
								{
									file << guitar[j / 2.0][dgt[d + w][j / 2]].name;
									for (int s(0); s < 3 - guitar[j / 2.0][dgt[d + w][j / 2]].name.size(); s++) file << " ";
								}
								else file << "|  ";

								file << minArr(dgt[d + w]) + (i - 1) / 2 << " ";
								if (minArr(dgt[d + w]) + (i - 1) / 2 < 10) file << " ";
					}
					file << "    ";
				}
			}
		}
		file << endl << endl<<endl<<endl;
	}
}



vector<string> readCfgFile(string path)
{
	ifstream cfg(path);
	string line;
	vector<string> result;
	string dataBuf;
	string strBuf;

	do
	{
		cfg >> strBuf >> dataBuf;
		result.push_back(dataBuf);
	} while (getline(cfg, line));

	return result;
}