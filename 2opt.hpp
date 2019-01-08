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
   int N = tour.size();
   Reverse_Segment(tour, position, (i+1)%N, j);
}
double Gain_From_2_Opt(int X1, int X2,int Y1, int Y2, vector<int> &tour, vector<int> &position)
{
   double del = dist(X1, X2) +dist(Y1, Y2); 
//    if( !(position[X2]%10) if(!isPrime[X1]) add += dist(X1, X2)*0.1;
//    if( !(position[Y2]%10) )if(!isPrime[Y1]) add += dist(Y1, Y2)*0.1;
   for(int i = ((position[X1]/10)+1)*10; i <= position[Y2]; i+=10) if(!isPrime[tour[i-1]]) del+= 0.1*dist(tour[i-1], tour[i]);

   double add = dist(X1, Y1) +dist(X2, Y2);
    if( !(position[Y1]%10)) if(!isPrime[X1]) add += dist(X1, Y1)*0.1;
    if( !(position[Y2]%10)) if(!isPrime[X2]) add += dist(X2, Y2)*0.1;

   for(int i = ((position[X2]/10)+1)*10; i <= position[Y1]; i+=10)
	{
	   int ii = position[Y1]-(i-position[X2]);
	   if(!isPrime[tour[ii+1]]) add+= 0.1*dist(tour[ii+1], tour[ii]);
	}
//for(int i = position[Y1], step = position[Y1]; i >= position[X2]; i--, step++)
//	{
//	   if( ((step+1)%10))continue;
//	   if(!isPrime[tour[i]]) add+= 0.1*dist(tour[i], tour[i-1]);
//	}
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
	if(!(i%1))
	cout << "i: "<< i<<endl;
	int X1 = tour[i];
	int X2 = tour[(i+1)%N];
	int cont2_limit = ( i == 0)?N-2:N-1; //avoid consecutive cities (with zero index)..
	for(int j = (i+2); j <= cont2_limit; j++)
        {

	   int Y1 = tour[j];
	   int Y2 = tour[(j+1)%N];
	if(!(j%1000))
	{
	cout <<"i: "<<i<<" j: "<< j<<endl;
//		cout << Gain_From_2_Opt(X1, X2, Y1, Y2, tour, position);
	}
	   if( Gain_From_2_Opt(X1, X2, Y1, Y2, tour, position) > 0)
	   {
		Make_2_Opt_Move(tour, position,  i, j);
	        locallyOptimal = false;
		//restart search...
		i=0;
		printf("%lf %lf\n",evaluate(tour), Gain_From_2_Opt(X1, X2, Y1, Y2, tour, position) );
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
  vector<int> bestMove(2);
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
	     double gainExpected = Gain_From_2_Opt(X1, X2, Y1, Y2, tour, position);
	     if(gainExpected > bestgain)
	     {
		bestMove[0] = i;
		bestMove[1] = j;
		locallyOptimal = false;
		bestgain = gainExpected;
   	     }
	   }
	}
	if(!locallyOptimal)//apply the 2opt movement...
	{
	   Make_2_Opt_Move(tour, position, bestMove[0], bestMove[1]);
	}
   }
}

void LS_2_Opt_N(vector<int> tour, vector<int> position)
{
   int N = tour.size();
   int NN = 20;
   bool locallyOptimal = false;
   while(!locallyOptimal)
   {
      locallyOptimal = true;
      for(int baseindex = 1; baseindex < N-1; baseindex++)
      {
	for(int direction= -1; direction <= 1; direction +=2)
	{
	   int i, X1, X2;
	   if( direction == -1)
	   {
		i = baseindex;
		X1 = tour[i];
		X2 = tour[ (i+1)%N];
	   }	
	   else if(direction == 1)
	   {
		i = (N+baseindex-1)%N;
		X2 = tour[i];
		X1 = tour[ (i+1)%N];
	   }
		if(!(baseindex%1000))
		cout << "i: "<< baseindex<<endl;
		for(int neighbor_number = 0; neighbor_number < NN; neighbor_number++)
		{
		   int j, Y2;
		   int Y1 = Nearest[i][neighbor_number];
			
		   if(direction == -1)
		   {
			j = position[Y1];
			Y2 = tour[ (j+1) % N ];
		   }
		   else if(direction == 1)
		   {
			j = (N + position[Y1]-1) % N;
			Y2 = tour[j];
		   }
		   if( X2 == Y1 || Y2 == X1) continue;

//		if(!(j%1000))
//		{
//		   cout <<"i: "<<i<<" j: "<< j<<endl;
//		}
		   if( Gain_From_2_Opt(X1, X2, Y1, Y2, tour, position) > 0)
		   {
			Make_2_Opt_Move(tour, position,  i, j);
			locallyOptimal = false;
			//restart search...
			i=0;
			printf("%lf %lf\n",evaluate(tour), Gain_From_2_Opt(X1, X2, Y1, Y2, tour, position) );
			break;
		   }
        	}
	}
      }
   }
}
#endif	
