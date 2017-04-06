
#ifndef _Graph_
#define _Graph_
#include <iostream>
#include <stdlib.h>
using namespace std;
class graphgen{
public:
	graphgen();
	~graphgen();
	graphgen(int s);
	int** gengraph(int d);
private:
	int size;
};
#endif

graphgen::graphgen(){
	size = 10;
	
}

graphgen::~graphgen(){}

graphgen::graphgen(int s){
	size = s;
}

int** graphgen::gengraph(int d){

int** graph = new int*[size];
for(int i = 0; i < size; ++i){
	graph[i]= new int[size];
}

if(d==0){
//directed graph
	int connect = 0;
	for(int i = 0; i<size; ++i){
	for(int j = 0; j<size; ++j){
		connect = rand()%2;			
		if(connect == 1){
			graph[i][j] = (rand()%9)+1;
			if (graph[i][j] == 0){
				cout<<"error"<<endl;
				exit(1);}
		}
		else{
			graph[i][j] = -1;		
		}
	}
	}
	return graph;
}

if(d==1){
//non-directed graph
int connect = 0;
	for(int i = 0; i<size/2; ++i){
	for(int j = 0; j<size; ++j){
		connect = rand()%2;
		if(connect == 1&& graph[i][j]!=0){
			graph[i][j] = rand()%9+1;
			graph[j][i] = graph[i][j];
		}
	}
	}
cout<<"hello"<<endl;
return graph;
}
}


