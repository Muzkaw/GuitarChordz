#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <sstream>
#include <string>
#include <fstream>
#include "Note.h"


using namespace std;

int sumByte(bitset<6> b);
int maxArr(vector<int> arr);
int minArr(vector<int> arr);
int nbDgt(vector<int> dgt);
int barre(vector<int> dgt);
void printAcc(ofstream &file, vector<vector<int>> dgt, vector<vector<Note> > guitar, int usableFret);

vector<string> readCfgFile(string path);
