#include "Graph.h"
#include <iostream>

struct Node{
	int vertex;
	Node* next;
};

struct UndavGraph::Graph{
	int vertexSize;
	Node** adjacencyLists;
	bool isDirected;
};

//Precondicion: @next es una instancia valida o es NULL
//Postcondicion: Devuelve una instancia valida de Node, que contiene al vertice y esta enlazado con @next
Node* CreateNode(int vertex, Node* next);

//Precondicion: @graph es una instancia valida
//Postcondicion: Devuelve true si el vertice pertenece al rango de vertices del grafo. Caso contrario devuelve false
bool BelongsToGraph(const UndavGraph::Graph* graph, int vertex);

//Precondicion: @graph es una instancia valida
//Postcondicion: Devuelve true si el vertice esta aislado. Caso contrario devuelve false
bool IsIsolated(const UndavGraph::Graph* graph, int vertex);

//Precondicion: @graph es una instancia valida
//Postcondicion: Inserta una conexion o arista entre los dos vertices dados
void InsertEdge(UndavGraph::Graph* graph, int sourceVertex, int targetVertex);

//Precondicion: @graph es una instancia valida
//Postcondicion: Remueve las conexiones o aristas entre los vertices dados
void RemoveEdge(UndavGraph::Graph* graph, int sourceVertex, int targetVertex);

//Precondicion: @iterator es una instancia valida que representa una lista de adyacencia
//Postcondicion: Destruye todos los nodos de la lista de adyacencia
void DestroyAdjacencyList(Node* iterator);

Node* CreateNode(int vertex, Node* next){
	Node* newNode = new Node;
	newNode->vertex  = vertex;
	newNode->next = next;
	return newNode;
}

bool BelongsToGraph(const UndavGraph::Graph* graph, int vertex){
	return (vertex >= 0 && vertex < graph->vertexSize);
}

bool IsIsolated(const UndavGraph::Graph* graph, int vertex){
	return graph->adjacencyLists[vertex] == NULL;
}

void InsertEdge(UndavGraph::Graph* graph, int sourceVertex, int targetVertex){
	graph->adjacencyLists[sourceVertex] = CreateNode(targetVertex, graph->adjacencyLists[sourceVertex]);
}

void RemoveEdge(UndavGraph::Graph* graph, int sourceVertex, int targetVertex){
	Node* newAdjacencyList = NULL;
	for(Node* iterator = graph->adjacencyLists[sourceVertex]; iterator != NULL; iterator = iterator->next){
		if(iterator->vertex != targetVertex){
			newAdjacencyList = CreateNode(iterator->vertex, newAdjacencyList);
		}
	}
	graph->adjacencyLists[sourceVertex] = newAdjacencyList;
}

void DestroyAdjacencyList(Node* iterator){
	while(iterator != NULL){
		Node* aux = iterator;
		iterator = iterator->next;
		delete aux;
	}
}

UndavGraph::Graph* UndavGraph::CreateDirectedGraph(int vertexSize){
	if(vertexSize >= 0){
		Graph* newGraph = new Graph;
		newGraph->vertexSize = vertexSize;
		newGraph->adjacencyLists = new Node*[vertexSize];
		for(int index = 0; index < vertexSize; index++) newGraph->adjacencyLists[index] = NULL;
		newGraph->isDirected = true;
		return newGraph;
	} else return NULL;
}

UndavGraph::Graph* UndavGraph::CreateUndirectedGraph(int vertexSize){
	if(vertexSize >= 0){
		Graph* newGraph = CreateDirectedGraph(vertexSize);
		newGraph->isDirected = false;
		return newGraph;
	} else return NULL;
}

void UndavGraph::Connect(Graph* graph, int sourceVertex, int targetVertex){
	if(BelongsToGraph(graph, sourceVertex) && BelongsToGraph(graph, targetVertex)){
		InsertEdge(graph, sourceVertex, targetVertex);
		if(!graph->isDirected) InsertEdge(graph, targetVertex, sourceVertex);
	}
}

void UndavGraph::Disconnect(Graph* graph, int sourceVertex, int targetVertex){
	if(AreAdjacent(graph, sourceVertex, targetVertex)){
		RemoveEdge(graph, sourceVertex, targetVertex);
		if(!graph->isDirected) RemoveEdge(graph, targetVertex, sourceVertex);
	}
}

bool UndavGraph::AreAdjacent(const Graph* graph, int sourceVertex, int targetVertex){
	if(!BelongsToGraph(graph, sourceVertex) || !BelongsToGraph(graph, targetVertex)) return false;
	else if(IsIsolated(graph, targetVertex) && !graph->isDirected) return false;
	else {
		for(Node* iterator = graph->adjacencyLists[sourceVertex]; iterator != NULL; iterator = iterator->next){
			if(iterator->vertex == targetVertex) return true;
		}
		return false;
	}
}

void UndavGraph::DestroyGraph(Graph* graph){
	for(int index = 0; index < graph->vertexSize; index++){
		if(graph->adjacencyLists[index] != NULL){
			DestroyAdjacencyList(graph->adjacencyLists[index]);
		}
	}
	delete graph->adjacencyLists;
	delete graph;
}
