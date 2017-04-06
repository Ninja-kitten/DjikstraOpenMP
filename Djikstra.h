#ifndef _djik_
#define _djik_
#include <cstdlib>
#include <omp.h>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

class Djikstra{

public:

Djikstra();
Djikstra(int s);
~Djikstra();
int *execute(int** graph);
void find_nearest(int s, int e, int* mind, bool* connected, int *d, int *v);
void update_mind(int s, int e, int mv, bool* connected, int** graph, int* mind);
private:
int size;
};

#endif

Djikstra::Djikstra(){ size = 10; }
Djikstra::Djikstra(int s){ size = s; }
Djikstra::~Djikstra(){}

int* Djikstra::execute(int** graph)
{
	bool *connected;
	//array representing which nodes have been connected or not
	
//*******************************************************************
	int *mind;
	int i, md, mv, my_first, my_id, my_last, my_md, my_mv, my_step, nth;
//*********************************************************************
//no idea why these variables are here as i type this, but hopefully that's cleared up
//as I continue to code. Came from source
//
	connected = new bool[size];
	connected[0] = true;
	for(i = 1; i< size; ++i){
		connected[i] = false;
	}

	//
	//md is minimum distane
	//initialize minimum distance to the one step distance
	//
	
	mind = new int[size];
	for( i = 0; i< size; ++i){
	mind[i] = graph[0][i];
	}
	
	#pragma omp parallel private(my_first,my_id,my_last,my_md,my_mv,my_step) \
	shared	(connected, md, mind, mv, nth, graph)
	{
		my_id = omp_get_thread_num();
		nth = omp_get_num_threads();
		my_first = (my_id*size)/nth;
		my_last = ((my_id+1)*size)/nth -1;
		//assigning each thread it's own little thing
		for(my_step = 1; my_step< size;++my_step){
		#pragma omp single
		{
			//timestamp here would probably be good
			//original code has i/o... don't feel like it
			md = -1;
			mv = -1;
		}
		//
		//each thread finds nearest unconnected node in its part
		//Some Threads might have no unconnected nodes
		//
		find_nearest(my_first,my_last, mind, connected, &my_md,&my_mv);
		//
		//in order to determin minimum we'll only do 1 for this block
		//
		#pragma omp critical
		{	if (md = -1){
				md = my_md;
				mv = my_mv;
			}
			else if(my_md < md){
				md = my_md;
				mv = my_mv;
			}
		}
		//barrier waits for all threads to do the critical block
		//MD and MV will have the right value
		#pragma omp barrier
		//if mv is -1. no thread found a node so we're done
		//if this happens we just wait for the iteration end.
		//otherwise we connect to the nearest node
		/*
		#pragma omp single
		{
			if(mv != -1)
			{
			 connected[mv] = true;
			
			}
		}
		*/
		//original code prints... but i'm gonna skip the i/o
		//
		if(mv != -1)
		{
		 update_mind(my_first, my_last, mv, connected, graph, mind);
		}
		//Before starting the next step we wait for everything to be updated
		//
		#pragma omp barrier
		}
		//end of for loop
	}
	delete [] connected;
	
	return mind;
}

void Djikstra::find_nearest(int s, int e, int* mind, bool* connected, int *d, int *v)
{
  int i;
  
  *d = -1;
  *v = -1;
  for ( i = s; i <= e; ++i )
  {
    if ( !connected[i] && *d == -1 )
    {
      *d = mind[i];
      *v = i;
    }
    if ( !connected[i] && mind[i] < *d )
    {
      *d = mind[i];
      *v = i;
    }
  }
  return;
}
/*
{
	int i;
	*d = -1;
	*v = -1;
	for (i = s; i <= e; ++i){
	  if(!connected[i] && *d == -1)
	  {
	    *d = mind[i];
	    *v = i;
 	  }
	 if(!connected[i] && mind[i] < *d)
	  {
	    *d = mind[i];
	    *v = i;
 	  }
	}
	return;
}
*/
void Djikstra::update_mind(int s, int e, int mv, bool* connected, int** graph, int* mind){
	int i;
	for( i = s; i<= e; ++i){
	 if(!connected[i]){
	  if(graph[mv][i] != -1){
	    if(mind[mv] + graph[mv][i] < mind[i]){
		mind[i] = mind[mv] + graph[mv][i];
	     }
	   }
	 }
	}
return;
}

