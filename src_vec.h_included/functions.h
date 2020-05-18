//#ifndef FUNCTIONS_H
//#define FUNCTIONS_H

#define pragma once

#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include "vector.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <exception>
#include <chrono>
#include <random>
#include <cctype> //skirtas patikrinti, ar tinkamai suvestas vardas/pavarde
#include "struct.h"

using namespace std;
//double median (vector<int> &A);
//double average (vector<int> &A);
void calculate(vector<student> &M);
double vidurkis (vector<int> L);
double mediana (vector<int> L);
void output (int n, vector <student> &B);
void generateFile(int kiekis, int nddydis, string &a);
int displayHelper (int number);
void readFile(vector<student> &M, string name);
void distributeFile(int numOfStudents, vector<student> &M, vector<student> &kvaili);

//#endif// FUNCTIONS_H
