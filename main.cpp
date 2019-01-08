
//= ===========================================================================
//============================================================================
#include <bits/stdc++.h>
#include <iostream>
#include <numeric>
#include <cstring>
#include <cstdlib>
#include <cstdio>
//#include <filesystem>
using namespace std;
#define REP(i, n) for (int i = 0; i < int(n); i++)
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define FOR(i, a, b) for (int i = a; i < int(b); i++)
#define FOREACH(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define SIZE(v) ((int)(v).size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define mp make_pair
#define st first
#define nd second
#define ll long long
#define pii pair<int, int>
#define NCITIES 197769
#define DP 100
#define DP2 101
#define LKH_REPLACEMENT 102
#define LKH3 103
#define DP3 104
#define LS2OPT 105
#define LS2OPTPRIMES 106
#include "common.hpp"
#include "2opt.hpp"
void readParams(int *argc, char ***argv)
{
    strcpy(filename_instance, (*argv)[1]);
    strcpy(filename_oldSolution, (*argv)[2]);
    strcpy(filename_newSolution, (*argv)[3]);
}
int main(int argc, char **argv){
  ///////Prepare data and read information
    sieve(400000);// printf("End Sieve\n");
    readParams(&argc, &argv);
    readSolution();
    readInstance();
    f2opt(path, indexnPath); 
    saveNewSolution();
    printf("Score of old path: %f\n",evaluate(path));
    printf("Score of new path: %f\n",evaluate(nPath));
}
