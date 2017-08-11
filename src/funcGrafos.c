#include <stdio.h>
#include <stdlib.h>
#include "funcGrafos.h"

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */

Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
   return G;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz recebe valor val. */

int **MATRIXint( int r, int c, int val) { 
   vertex i, j;
   int **m = malloc( r * sizeof (int *));
   for (i = 0; i < r; ++i) 
      m[i] = malloc( c * sizeof (int));
   for (i = 0; i < r; ++i)
      for (j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */

void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHremoveArc() remove do grafo G o arco v-w. A função supõe que v e w são distintos, positivos e menores que G->V. Se não existe arco v-w, a função não faz nada. */

void GRAPHremoveArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHshow() imprime, para cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */

void GRAPHshow( Graph G) { 
   vertex v, w; 
   for (v = 0; v < G->V; ++v) {
      printf( "%2d:", v);
      for (w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1) 
            printf( " %2d", w);
      printf( "\n");
   }
}

/*Um grafo é  completo  se todo par ordenado de vértices distintos é um arco.  Portanto, um grafo completo com V vértices tem exatamente V (V−1) arcos. */

Graph GRAPHbuildComplete( int V) {
   Graph G;
   G = GRAPHinit( V);
   for (vertex v = 0; v < G->V; ++v)
      for (vertex w = 0; w < G->V; ++w)
         if (w != v)
            GRAPHinsertArc( G, v, w);
   return G;
}