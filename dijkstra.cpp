#include <iostream>
#include<stdio.h>
#include <cfloat>
#include<stdlib.h>
using namespace std;

bool allVisited();

//Creamos la matriz que representa el grafo
double **graph=NULL;
double *minDist=NULL;
int *parents=NULL;
int *visited=NULL;
int num=0;
//Nodo Inicial
int iniNode=0;

int main(int argc, char const *argv[]) {
  //Creamos un puntero de tipo FILE
	FILE *fp;
	//Abrimos el archivo a leer
 	if((fp = fopen ("graphs\\bcs.txt", "r" ))==NULL){
 		printf("No se pudo leer el archivo\n");
 		return 0;
 	}
	//leemos los datos
 	fscanf(fp, "%d" ,&num);
    //Incializa los arreglos
 	graph = (double**)malloc(num*sizeof(double*));
  minDist=(double*)malloc(num*sizeof(double));
  parents=(int *)malloc(num*sizeof(int));
  visited=(int *)malloc(num*sizeof(int));
	// Crea las columnas
	for(int i=0;i<num;i++){
		graph[i] = (double*)malloc(num*sizeof(double));
		for(int j=0;j<num;j++){
      // Inicializa la matriz en infinito (Max double)
			graph[i][j]=DBL_MAX;
		}
    // Inicializa el vector en infinito (Max double)
    minDist[i]=DBL_MAX;
    parents[i]=i;
    visited[i]=0;
	}
  int a,b;
  double d;
 	//Leemos las aristas de cada vertice
 	while(feof(fp)==0){
 		fscanf(fp,"%d\t%d\t%lf",&a,&b,&d);
 		graph[a-1][b-1]=d;
    graph[b-1][a-1]=d;
 	}
 	//Imprimimos el grafo
 	for(int i = 0; i < num; i++){
 		for (int j = 0; j < num; ++j){
      if(graph[i][j]!=DBL_MAX)
        printf("%.2f\t",graph[i][j]);
      else
        printf("INF\t");
    }
    printf("\n");
 	}
  //Algoritmo Dijkstra
    //1.Selecciona el nodo Inicial como nodo actual
  int act=iniNode;
    //2.Asigna como padre del nodo inicial en -1
  parents[act]=-1;
    //3.Asigna la distancia minima desde el nodo inicial al
    //  nodo inicial como 0
  minDist[act]=0;
    //4.Mientras aun hay nodos por visitar, hacer
  while(!allVisited()){
    printf("Actual %d\n",act);
    for(int i=0;i<num;i++){
      if(graph[act][i]<DBL_MAX){
        if((graph[act][i]+minDist[act])<minDist[i]){
          minDist[i]=graph[act][i]+minDist[act];
          parents[i]=act;
        }
      }
    }
    visited[act]=1;
    double min=DBL_MAX;
    int index=0;
    for(int i=0;i<num;i++){
      if(visited[i]!=1 && minDist[i]<min){
        min=minDist[i];
        index=i;
      }
    }
    act=index;
  }

  for(int i=0;i<num;i++){
    printf("%.2f ",minDist[i]);
  }
  printf("\n");
  for(int i=0;i<num;i++){
    printf("%d ",parents[i]);
  }

  free(fp);
  free(graph);
  free(minDist);
  return 0;
}
bool allVisited(){
  int aux=0;
  for(int i=0;i<num;i++)
    aux+=visited[i];

  if(aux==num)
    return true;
  else
    return false;
}
