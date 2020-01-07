#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <chrono>
#include <queue>
#include "../include/ortools/algorithms/knapsack_solver.h"


using namespace std;



//--------------------or tools knapnask -----------------------------------------------

namespace operations_research
{
int KnapsackExample(int c,int n,int v[],int w[])
{
    KnapsackSolver solver(KnapsackSolver::KNAPSACK_DYNAMIC_PROGRAMMING_SOLVER,
                          "SimpleKnapsackExample");

    std::vector<int64> values ;
    std::vector<int64> we1 ;
    std::vector<std::vector<int64>> weights;
    std::vector<int64> capacities ;


for (int i = 0; i < n; i++)
    {
        values.push_back(v[i]);
        we1.push_back(w[i]);
        weights = { we1 };
        capacities.push_back(c);
    }


    solver.Init(values, weights, capacities);
    int64 computed_value = solver.Solve();

    return computed_value ;

}
}



//--------------------------------MAIN-------------------------------------------


int main() {
        int i,s[5000],v[5000],w[5000];
        int c,n;

  
    ifstream fileC;
    ofstream outfile;
    outfile.open("knap-ortools-dp.csv");
   

        outfile<<"      problem_id       "<<'\t'<<'\t'<<"knap-ort-dp"<<'\t'<<"time-ortools"<<endl;
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
        outfile<< filename << '\t' << '\t';
        auto start5 = chrono::steady_clock::now();
        double clStart5 = clock();

        outfile << operations_research::KnapsackExample(c, n, v, w);
        auto end5 = chrono::steady_clock::now();
        double clEnd5 = clock();

        auto difTime5 = end5 - start5;
        double diff5 = chrono::duration <double, nano>(difTime5).count();
        double diffTicks5 = clEnd5 - clStart5;

        outfile << '\t' << diffTicks5 << '\t' << endl;

}}}}

        return 0;
}
