#ifndef _INCL_COMMON
#define _INCL_COMMON
const int MAX = 1001000;

struct city{
    int id;
    double x, y;
};
char filename_newSolution[100];
char filename_oldSolution[100];
char filename_instance[100];
vector<city> cities;
vector< vector< int > > Nearest;
vector<int> path, path_segment, indexnPath, nPath;
vector<int> primeIds;
priority_queue<pair<double, int> > prime_sorted;
bitset<MAX> used;
int K = 1;
int l, r, len;
long long INF = 1e6, currentCost;
int L = 10;
double C = INF;
int seed = 0;
vector<vector<long long> > distances;
bitset<1001000> isPrime;
long long sieve_size;
void Kneares(int k, int index, vector<int> &nindex)
{
	char filecity[1000];
	sprintf(filecity,"/tmp/50Nearest/%d.txt",index);
        FILE * file = fopen(filecity, "r");
	double distance;
	int indexc;
	int cont = 0;
	while(cont < k)	
	{
	   fscanf(file, "%lf %d\n", &distance, &indexc);
	   nindex[cont] = indexc;//.push_back(indexc);
	   cont++;
	}
        fclose(file);
}
void readInstance(){
    FILE *file = fopen(filename_instance, "r");
    int N = NCITIES;//n = 197769;
    double x, y;
    int id;
    char trash[100];
    fscanf(file, " %s\n", trash);
    cities.resize(NCITIES);
    Nearest.resize(NCITIES, vector<int>(20));
//    while(N--){
    
// #pragma omp parallel for
    for(int i= 0;i < NCITIES; i++)
    {
        fscanf(file, "%d,%lf,%lf\n", &id, &x, &y);
        cities[id].id = id;
        cities[id].x = x;
        cities[id].y = y;
	Kneares(20, id, Nearest[id]);
	if( !(N%1000))
	cout << N <<endl;
	if( isPrime[id]) 
	{
		primeIds.pb(id);
	}
    }
    fclose(file);
}
void readSolution(){
    FILE *file = fopen(filename_oldSolution, "r");
    char trash[100];
    fscanf(file, " %s\n", trash);
	path.resize(NCITIES);
	indexnPath.resize(NCITIES);
    for(int i = 0; i < NCITIES; i++){
	 fscanf(file, "%d\n", &path[i]);
	 indexnPath[path[i]] = i;
	}
    fclose(file);
}
void sieve(long long upperbound){
    sieve_size = upperbound + 1;
    isPrime.set();
    isPrime[0] = isPrime[1] = false;
	
    for(long long i = 2; i < sieve_size; i++) if(isPrime[i]){
        for(long long j = i*i; j < sieve_size; j += i) isPrime[j] = false;
    }
}
double dist(int c1, int c2){
    double d = (sqrt((cities[c1].x - cities[c2].x)*(cities[c1].x - cities[c2].x) + (cities[c1].y - cities[c2].y)*(cities[c1].y - cities[c2].y)));
    return d;
}
double distd(int pos, int c1, int c2){
    double d = (sqrt((cities[c1].x - cities[c2].x)*(cities[c1].x - cities[c2].x) + (cities[c1].y - cities[c2].y)*(cities[c1].y - cities[c2].y)));
    pos++; // Esta es la parte que agregue
    if(pos%L == 0){
        if(isPrime[c1]) return d;
        else return 1.1*d;
    }
    else return d;
}
void saveNewSolution()
{
  //  char fileSolution[1010];
  //  strcpy(fileSolution, (*argv)[5]);
  //  FILE * file = fopen(fileSolution, "w");
    FILE * file = fopen(filename_newSolution, "w");
	fprintf(file, "Path\n");
    for(int i = 0; i < NCITIES; i++) fprintf(file, "%d\n", nPath[i]);
    fclose(file);
}
void reversePath(int *pathc, int *invpath, int l, int r){
    reverse(pathc + l, pathc + r + 1);
    for(int i = l; i <= r; i++) invpath[pathc[i]] = i;
}
double evaluate(vector<int> &pathc){
    double len = 0.0;
    for(int i = 0; i < NCITIES; i++){
        int j = (i + 1)%NCITIES;
        len += distd(i, pathc[i], pathc[j]);
    }
    return len;
}
double evaluate(vector<int> &pathc, int l, int r){
    double len = 0.0;
    int i = (l - 1 + NCITIES)%NCITIES;
    while(true){
        int j = (i + 1)%NCITIES;
        len += distd(i, pathc[i], pathc[j]);
        if(i == r) break;
        i = j;
    }
    return len;
}
double evaluatereverse(int * pathc, int l, int r){
    double len = 0.0;
	len = distd(l-1, pathc[(l-1+NCITIES)%NCITIES], pathc[r]);
	for(int i = r, step=l; i >l; i--, step++)
	   len += distd(step, pathc[i], pathc[(i-1+NCITIES)%NCITIES]);
	len += distd(r, pathc[l], pathc[(r+1)%NCITIES]);
    return len;
}
double evaluate(vector<int> &pathc, vector<int> &indexes){
    double len = 0.0;
    for(int k = 0; k < indexes.size()-1; k++)
    {
       int i = (indexes[k] - 1 + NCITIES)%NCITIES;
       while(true){
        int j = (i + 1)%NCITIES;
        len += distd(i, pathc[i], pathc[j]);
        if(i == indexes[k+1]) break;
        i = j;
       }
    }
    return len;
}
double evaluate2(int * pathc, vector<int> &indexes){
    double len = 0.0;
    for(int k = 0; k < indexes.size()-1; k++)
    {
       int i = (indexes[k] - 1 + NCITIES)%NCITIES;
       while(true){
        int j = (i + 1)%NCITIES;
        len += distd(i, pathc[i], pathc[j]);
        if(i == indexes[k+1]) break;
        i = j;
       }
    }
    return len;
}
void swap(int *lpath, int a, int b){ int tmp = lpath[a]; lpath[a] = lpath[b]; lpath[b] = tmp;  }

#endif
