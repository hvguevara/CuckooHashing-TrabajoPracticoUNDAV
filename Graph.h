#ifndef GRAPH_H_
#define GRAPH_H_

namespace UndavGraph{
	struct Graph;

	/*
	 * Precondicion: -
	 * Postcondicion: Si @vertexSize es un numero mayor o igual que cero
	 * devuelve un grafo dirigido que tiene una cantidad de vertices igual a vertexSize
	 * Caso contrario, devuelve NULL
	 */
	Graph* CreateDirectedGraph(int vertexSize);

	/*
	 * Precondicion: -
	 * Postcondicion: Si @vertexSize es un numero mayor o igual que cero
	 * devuelve un grafo no dirigido que tiene una cantidad de vertices igual a vertexSize
	 * Caso contrario, devuelve NULL
	 */
	Graph* CreateUndirectedGraph(int vertexSize);

	/*
	 * Precondicion: @graph es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Si @graph es un grafo no dirigido, se agrega una relacion de adyacencia conmutativa entre @sourceVertex y @targetVertex (@sourceVertex es adyacente a @targetVertex y viceversa).
	 * Si @graph es un grafo dirigido, se agrega una relacion de adyacencia de @sourceVertex y @targetVertex (@sourceVertex es adyacente a @targetVertex)
	 * Si @sourceVertex o @targetVertex no pertenece al grafo no realiza ninguna accion
	 */
	void Connect(Graph* graph, int sourceVertex, int targetVertex);

	/*
	 * Precondicion: @graph es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Si @graph es un grafo no dirigido, se remueven las relaciones de adyacencia conmutativa entre @sourceVertex y @targetVertex.
	 * Si @graph es un grafo dirigido, se remueven las relaciones de adyacencia entre @sourceVertex y @targetVertex
	 * Si @sourceVertex no es adyacente a @targetVertex no realiza ninguna accion
	 */
	void Disconnect(Graph* graph, int sourceVertex, int targetVertex);

	/*
	 * Precondicion: @graph es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve true si @sourceVertex es adyacente a @targetVertex. Caso contrario devuelve false
	 */
	bool AreAdjacent(const Graph* graph, int sourceVertex, int targetVertex);

	/*
	 * Precondiciones: @graph es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Libera todos los recursos asociados a @graph
	 */
	void DestroyGraph(Graph* graph);
}

#endif
