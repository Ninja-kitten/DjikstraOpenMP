#include <iostream>
#include "graphgen.h"
#include "Djikstra.h"
#include <omp.h>
#include <time.h>
using namespace std;
int main(int argc, char** argv){

omp_set_num_threads(30);

clock_t end10,beg10,end100,beg100,end1000,beg1000;
//set up the problem for 10 vertices
graphgen graph10(10);
int** g10;
g10 = graph10.gengraph(0);
Djikstra d10(10);
//timestamps
beg10 = clock();
d10.execute(g10);
end10 = clock()-beg10;
//don't care about the output because we just want it to finish
//close timestamp

//set up problem for 100 vertices
graphgen graph100(100);
int** g100;
g100 = graph100.gengraph(0);
Djikstra d100(100);
//timestamps
beg100 = clock();
d100.execute(g100);
end100 = clock()-beg100;
//don't care about the output because we just want it to finish
//close timestamp

//set up problem for 100 vertices
graphgen graph1000(1000);
int** g1000;
g1000 = graph1000.gengraph(0);
Djikstra d1000(1000);
//timestamps
beg1000 = clock();
d1000.execute(g1000);
end1000 = clock()-beg1000;
//don't care about the output because we just want it to finish
//close timestamp


cout<<(float(end10)/CLOCKS_PER_SEC)<<endl;
cout<<(float(end100)/CLOCKS_PER_SEC)<<endl;
cout<<(float(end1000)/CLOCKS_PER_SEC)<<endl;
/*
int size[10] = {10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000};
clock_t time[10];
int decision = 0;
for(int i = 0; i<10; ++i){
  graphgen graph(size[i]);
  int** g;
  g = graph.gengraph(decision);
  Djikstra d(size[i]);
  //timestamps
  time[i] = clock();
  d1000.execute(g1000);
  time[i] = clock()-time[i];
  cout<<size<<"\t"<<time[i]<<endl;
}*/
}
