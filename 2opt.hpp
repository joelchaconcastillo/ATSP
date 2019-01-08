#ifndef _INCL_2OPT
#define _INCL_2OPT
//Reverse_Segment(2, 5)---->
//pos    0 1 2 3 4 5 6 7
//before A-B-C-D-E-F-G-H
//after  A-B-F-E-D-C-G-H
void Reverse_Segment(vector<int> &tour, vector<int> &position, int startIndex, int endIndex)
{
   int N = tour.size();
   int inversionSize = ((N+endIndex-startIndex+1) % N) / 2;
   int left = startIndex;
   int right = endIndex;
   for(int counter = 1; counter <= inversionSize; counter++)
   {	
	iter_swap(tour.begin()+left, tour.begin()+right);
	position[tour[left]] = left;
	position[tour[right]] = right;
	left = (left+1)%N;
	right = (N + right-1) %N;
   }
}
void Make_2_Opt_Move(vector<int> &tour, vector<int> &position, int i, int j)
{
   Reverse_Segment(tour, position, (i+1)%N, j);
}
double Gain_From_2_Opt(int X1, int X2,int Y1, int Y2, vector<int> &tour, vector<int> &position)
{
   double del = dist(tour[X1], tour[X2]) +dist(tour[Y1], tour[Y2]);
   for(int i = ((position[tour[X2]]/10)+1)*10-1; i < position[tour[Y1]]; i+=10)  del += 0.1*dist(tour[i-1], tour[i]);
   double add = dist(tour[X1], tour[Y1]) +dist(tour[X2], tour[Y2]);
   
   return (del - add); 
}
void LS_2_Opt(vector<int> tour, vector<int> position)
{
   int N = tour.size();
   bool locallyOptimal = false;
   while(!locallyOptimal)
   {
      locallyOptimal = true;
      for(int i = 0; i <= N-3; i++)
      {
	int X1 = tour[i];
	int X2 = tour[(i+1)%N];
	int cont2_limit = ( i == 0)?N-2:N-1; //avoid consecutive cities (with zero index)..
	for(int j = (i+2); j <= cont2_limit; j++)
        {
	   int Y1 = tour[j];
	   int Y2 = tour[(j+1)%N];
	   if( Gain_From_2_Opt(X1, X2, Y1, Y2, tour, position) > 0)
	   {
		Make_2_Opt_Move(tour, position,  i, j);
	        locallyOptimal = false;
		//restart search...
		cont1=0;
		break;
  	   }
        }
      }
   }
}
void LS_2_Opt_Take_Best(vector<int> tour, vector<int> position)
{
  bool locallyOptimal = false;
  int N = tour.size();
  vector<int> bestMove(4);
  double bestgain = -DBL_MAX;
   while(!locallyOptimal)
   {
	for(int i = 0; i <= N-3; i++)
	{
	   int X1 = tour[i];
	   int X2 = tour[(i+1)%N];
	   int cont2_limit = ( i == 0)?N-2:N-1;
	   for(int j = i+2; j <= cont2_limit; j++)
	   {
	     int Y1 = tour[j];	
	     int Y2 = tour[(j+1)%N];	
	     double gainExpected = Gain_From_2_Opt(X1, X2, Y1, Y2)
	     if(gainExpected > bestgain)
	     {
		bestMove[0] = X1;
		bestMove[1] = X2;
		bestMove[2] = Y1;
		bestMove[3] = Y2;
		locallyOptimal = false;
		bestgain = gainExpected;
   	     }
	   }
	}
	if(!locallyOptimal)//apply the 2opt movement...
	{
	   Make_2_Opt_Move(tour, position, bestMove[0], bestMove[1], bestMove[2], before[3]);
	}
   }
}
#endif	
