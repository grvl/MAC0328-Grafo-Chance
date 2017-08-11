#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcGrafos.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define num 100

int visit[5000];

void reachR( Graph G, vertex v, int index) 
{ 
   visit[v] = index;
   for (vertex w = 0; w < G->V; ++w)
      if ((G->adj[v][w] == 1 || G->adj[w][v] == 1) && visit[w] == 0)
         reachR( G, w, index);
}

void GRAPHreach( Graph G) 
{ 
  int index = 1;
  for (vertex v = 0; v < G->V; ++v)
    visit[v] = 0;

  for (vertex t = 0; t < G->V; t++)
    if(visit[t] == 0){ 
      reachR( G, t, index);
      index++;
    }
}

Graph generateRandomGraph( int a, int v, int directed) {
  int v1, v2;
  Graph G = GRAPHinit(v); 

  if (v < 2) return G;

  while (a > 0){
    v1 = rand()%v;
    v2 = rand()%v;
    if (v1 == v2) v2 = (v2 + 1)%v;
    if ((!directed && G->adj[v1][v2] != 1 && G->adj[v2][v1] != 1) || (directed && G->adj[v1][v2] != 1)){
      a--;
      GRAPHinsertArc(G, v1, v2);
    }
  }
  return G;
}

int main(int argc, char *argv[]) {
  Graph G;
  int i, j, count, a, v, v1, v2;
  float percent[num], avg = 0., variancia = 0.;

  srand(time(NULL));

  if (argc != 3){
    printf("./grafo a v\n Com a o numero de arestas e v o numero de vertices (max 5000).\n");
    return 0;
  }

  a = atoi(argv[1]);
  v = atoi(argv[2]);

  for(j = 0; j < num; j++){
    G = generateRandomGraph(a, v, 0);
    //GRAPHshow(G);
    GRAPHreach(G);

    for (i = 0, count = 0; i < 5000; i++){
      v1 = rand()%v;
      v2 = rand()%v;
      if (v1 == v2) v2 = (v2 + 1)%v;
      if (visit[v1] == visit[v2]) count++;
    }

  // for (i = 0; i < v; i++)
  // printf("%d ", visit[i]);
  // printf("\n");

    percent[j] = count/5000.;
//    printf("%f %%\n", percent[j]);
  }

  for(j = 0; j < num; j++){
    avg += percent[j];
  }

  avg /= num;

  for(j = 0; j < num; j++){
    variancia += pow( percent[j] - avg, 2);
  }

  variancia /= num;
  variancia = 1.96 * sqrt(variancia/num); //95% confianca

  avg *= 100.;
  variancia *= 100.;

  printf("Em um grafo com %d arestas e %d vertices, tem (%f +- %f) %% chance de duas vertices estarem conectadas.\n", a, v, avg, variancia);

  return 0;
}