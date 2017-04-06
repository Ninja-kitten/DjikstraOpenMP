#include <iostream>
#include "graphgen.h"
#include "Djikstra.h"
#include <omp.h>
#include <ctime>
using namespace std;
int main(int argc, char** argv){

omp_set_num_threads(30);

time_t end10,beg10,end100,beg100,end1000,beg1000;
//set up the problem for 10 vertices
graphgen graph10(10);
int** g10;
g10 = graph10.gengraph(0);
Djikstra d10(10);
//timestamps
beg10 = time(NULL);
d10.execute(g10);
end10 = time(NULL);
//don't care about the output because we just want it to finish
//close timestamp
double diff10 = difftime(end10,beg10);

//set up problem for 100 vertices
graphgen graph100(100);
int** g100;
g100 = graph100.gengraph(0);
Djikstra d100(100);
//timestamps
beg100 = time(NULL);
d100.execute(g100);
end100 = time(NULL);
//don't care about the output because we just want it to finish
//close timestamp
double diff100 = difftime(end100,beg100);

//set up problem for 100 vertices
graphgen graph1000(1000);
int** g1000;
g1000 = graph1000.gengraph(0);
Djikstra d1000(1000);
//timestamps
beg1000 = time(NULL);
d1000.execute(g1000);
end1000 = time(NULL);
//don't care about the output because we just want it to finish
//close timestamp
double diff1000 = difftime(end1000,beg1000);

cout<<diff10<<endl;
cout<<diff100<<endl;
cout<<diff1000<<endl;
}
