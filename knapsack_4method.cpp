#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <chrono>
#include <queue>
using namespace std;

//----------------------------------------------GREEDY ALGORITHM--------------------------------------

int knapsackgreedy(int c,  int v[], int w[],int n , int s[])
{
	int x[500];
	float ratio[500]; 
	float totalprofit;
	float y;
	int temp;
	int i,j;
	y=c;
	totalprofit=0;

for (i = 0; i < n; i++) {
      ratio[i] = v[i] / w[i];
   }
 
   for (i = 0; i < n; i++) {
      for (j = i + 1; j < n; j++) {
         if (ratio[i] < ratio[j]) {
            temp = ratio[j];
            ratio[j] = ratio[i];
            ratio[i] = temp;
 
            temp = w[j];
            w[j] = w[i];
            w[i] = temp;
 
            temp = v[j];
            v[j] = v[i];
            v[i] = temp;
	    temp=s[j];
	    s[j]=s[i];
	    s[i]=temp;

         }
      }
   }

	for(i=0;i < n;i++)
		x[i]=0.0;
	for(i=0;i < n;i++)
	{
		if(w[i] > y)
			break;
		else
		{
			x[i]=1.0;
			totalprofit=totalprofit+v[i];
			y=y-w[i];
		}
	}
	if(i < n)	
		x[i]=y/w[i];
	totalprofit=totalprofit+(x[i]*v[i]);





	return totalprofit;			 

}


//------------------DYNAMIC PROGRAMMING--------------------------------------------------------------

int dynamic(int c,int n,int w[],int v[]){
int dp[c+1];
int solve();

    memset(dp, 0, sizeof(dp));
    for(int i =1; i <= n; i++) {
        for(int j = c; j >= w[i]; j--) {
             dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
        }
    }
    return dp[c];
}

//----------------------------------bound-------------------------------------------------------------
struct node
{
    int level;
    int profit;
    int weight;
    int bound;
};

int bound(node u, int n, int c, vector<int> pVa, vector<int> wVa)
{
    int j = 0, k = 0;
    int totweight = 0;
    int result = 0;

    if (u.weight >= c)
    {
        return 0;
    }
    else
    {
        result = u.profit;
        j = u.level + 1;
        totweight = u.weight;

        while ((j < n) && (totweight + wVa[j] <= c))
        {
            totweight = totweight + wVa[j];
            result = result + pVa[j];
            j++;
        }

        k = j;

        if (k < n)
        {
            result = result + (c - totweight) * pVa[k]/wVa[k];
        }
        return result;
    }
}

int knapsackbound(int n, int v[], int w[], int c)
{
    queue<node> Q;
    node u, nn;
    vector<int> pV;
    vector<int> wV;
    Q.empty();

    for (int i = 0; i < n; i++)
    {
        pV.push_back(v[i]);
        wV.push_back(w[i]);
    }

    nn.level = -1;
    nn.profit = 0;
    nn.weight = 0;

    int maxProfit = 0;

    nn.bound = bound(nn, n, c, pV, wV);
    Q.push(nn);

    while (!Q.empty())
    {
        nn = Q.front();
        Q.pop();

        if (nn.level == -1)
        {
            u.level = 0;
        }
        else if (nn.level != (n - 1))
                                                                  {
            u.level = nn.level + 1;
        }

        u.weight = nn.weight + w[u.level];
        u.profit = nn.profit + v[u.level];

        u.bound = bound(u, n, c, pV, wV);

        if (u.weight <= c && u.profit > maxProfit)
        {
            maxProfit = u.profit;
        }

        if (u.bound > maxProfit)
                                          
   {
            Q.push(u);
        }
    }
    return maxProfit;
}



//-----------------------------------------------BRUTE FORCE--------------------------------------------------

int bruteforce(int v[], int w[], int n, int c)
{
	float timen;
	timen=clock();
    int *A = (int *) calloc(n, sizeof(int));
    int i;
    int val=0;

    for (i = 0; ; i++) {
        int j = n;
        int tempWeight = 0;
        int tempValue = 0;
        int k;

        k = 1;
        for (j = 0; j < n; j++) {
            A[j] += k;

            k = A[j] / 2;
            A[j] = A[j] % 2;
	if ((clock()-timen)/CLOCKS_PER_SEC>=10)
		break;
        }
        if (k) break;

        for (k = 0; k < n; k++) {
            if (A[k] == 1) {
                tempWeight = tempWeight + w[k];
                tempValue = tempValue + v[k];

            }
        }

        if (tempValue > val && tempWeight <= c) {
            val = tempValue;

        }

}

    free(A);
    return val;
}



//--------------------------------MAIN-------------------------------------------


//int main(int argc,char *argv[]) {
int main() {
	int i,n,s[5000],v[5000],w[5000];
	int c;

    string name ;
    ifstream fileC;
    ofstream outfile;
     outfile.open("results-4meth.csv");


	outfile<<"problem_id            "<<'\t'<<'\t'<<"greedy"<<'\t'<<"greedy-time"<<'\t'<<"dynamic"<<'\t'<<"dynamic-time"<<'\t'<<"bb"

                                                 <<'\t'<<"bb-time"<<'\t'<<"bf"<<'\t'<<"bf-time"<<endl;
for (int n1 : {10,50,100,500}){ 
	for (int r1 : {50,100,500,1000}) {
		for (int type : {1,2,3,4}) {
			for (int id=1; id<=5;id++) 
			{
			string filename="problem_"+to_string(n1)+"_" +to_string(r1)+"_"+to_string(type)+"_"+to_string(id)+"_5.txt";
    fileC.open(filename.c_str());
	
		if (fileC.is_open()){
	fileC>>n;
	for (i=0;i<n;i++)	
	fileC>>s[i]>>v[i]>>w[i];
	}
	fileC>>c;
	fileC.close();


outfile<<filename<<'\t'<<'\t';

//--------------------------greedy & time------------------------------

auto start1 = chrono::steady_clock::now();
        double clStart1 = clock();

outfile<<    knapsackgreedy(c, v, w, n , s);
auto end1 = chrono::steady_clock::now();
double clEnd1 = clock();

auto difTime1 = end1-start1;
double tim1 = chrono::duration <double,nano> (difTime1).count();
double time1 = clEnd1-clStart1;

  outfile <<'\t'<<'\t'<<time1 <<'\t';




//--------------------------dynamic & time------------------------------


  auto start2 = chrono::steady_clock::now();
	double clStart2 = clock();

outfile<<dynamic(c,n,w,v)<<'\t'<<'\t';
auto end2 = chrono::steady_clock::now();
double clEnd2 = clock();

auto difTime2 = end2-start2;
double tim2 = chrono::duration <double,nano> (difTime2).count();
double time2 = clEnd2-clStart2;

  outfile <<time2 <<'\t';


//--------------------------bound & time------------------------------

 auto start3 = chrono::steady_clock::now();
        double clStart3 = clock();


outfile<< knapsackbound( n, v,  w,  c)<<'\t'<<'\t';
auto end3 = chrono::steady_clock::now();
double clEnd3 = clock();

auto difTime3 = end3-start3;
double tim3 = chrono::duration <double,nano> (difTime3).count();
double time3 = clEnd3-clStart3;

  outfile <<time3 <<'\t';

//--------------------------brute force & time------------------------------


  auto start4 = chrono::steady_clock::now();
        double clStart4 = clock();

outfile<<bruteforce(v,w, n, c);
auto end4 = chrono::steady_clock::now();
double clEnd4 = clock();

auto difTime4 = end4-start4;
double tim4 = chrono::duration <double,nano> (difTime4).count();
double time4 = clEnd4-clStart4;

   outfile <<'\t'<<'\t'<<time4 <<endl;



}}}}
 outfile.close();


	return 0;
}

