#include "header.h"

void minHeapify(MinHeap *M, int Index)									// Min-heapify the heap at Index.
{
	int smallest, l, r;
	smallest = Index;
	l = 2 * Index + 1;
	r = 2 * Index + 2;

	if (l < M->remainVertexNumber && M->vertexList[l]->key < M->vertexList[smallest]->key)
		smallest = l;

	if (r < M->remainVertexNumber && M->vertexList[r]->key < M->vertexList[smallest]->key)
		smallest = r;

	if (smallest != Index) {
		
		//The vertex to be swapped in minheap
		Vertex *smallestVertex = M->vertexList[smallest];
		Vertex *indexVertex = M->vertexList[Index];

		// Swap positions
		M->position[smallestVertex->name] = Index;
		M->position[indexVertex->name] = smallest;

		//Swap Vertex
		swapVertex(&M->vertexList[smallest], &M->vertexList[Index]);

		minHeapify(M, smallest);
	}

}


// Extract minimum vertex from heap and return it.
Vertex *extractMin(MinHeap *M)											 
{
	if (isEmptyHeap(M))
		return NULL;

	//Store the root node
	Vertex* root = M->vertexList[0];

	//Repalce root vertex with last vertex
	Vertex* lastVertex = M->vertexList[M->remainVertexNumber - 1];
	M->vertexList[0] = lastVertex;

	//Update position of last Vertex
	M->position[root->name] = M->remainVertexNumber - 1;
	M->position[lastVertex->name] = 0;

	//Reduce heap size and heapify root
	--M->remainVertexNumber;
	minHeapify(M, 0);

	return root;

}




// Function to decreasy key value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(MinHeap *M, int V, int Key)							// Decrease key value of vertex V.
{
	//Get the index of V in vertexList
	int i = M->position[V];

	//Get the vertex and update its key value
	M->vertexList[i]->key = Key;

	// Travel up while the complete tree is not hepified.
	while (i&&M->vertexList[i]->key < M->vertexList[(i - 1) / 2]->key) {

		//Swap this vertex with its parent
		M->position[M->vertexList[i]->name] = (i - 1) / 2;
		M->position[M->vertexList[(i - 1) / 2]->name] = i;
		swapVertex(&M->vertexList[i], &M->vertexList[(i - 1) / 2]);

		//move to parent index
		i = (i - 1) / 2;
	}

}

void addVertexToHeap(MinHeap *M, Graph *G, int V)						// Get Vertex from graph and add it to heap.
{

	M->vertexList[V] = G->vertexList[V];
	M->position[V] = V;

}


int primAlgorithm(Graph *G)											// Run Prim's algorithm and return sum of MSP's edge weights.
{
	int k[100];		//Stores the key value with minimum weight according to name value
	int V = G->totalVertexNumber;
	
	//Initialize minheap with all vertices.
	MinHeap* minHeap = initMinHeap(V);
	
	for (int v = 1; v < V; ++v) {
		addVertexToHeap(minHeap, G, v);
		k[v] = INT_MAX;
	}
	
	
	//Let the 0th vertex be selected first.
	k[0] = 0;
	G->vertexList[0]->key = 0;
	minHeap->vertexList[0] = G->vertexList[0];
	minHeap->position[0] = 0;

	minHeap->remainVertexNumber = V;

	int sum = 0;

	//Update the key value by moving all vertices adjacent to u.
	while (!isEmptyHeap(minHeap))
	{
		Vertex* minHeapVertex = extractMin(minHeap);
		int u = minHeapVertex->name;

		for (int a = 0; a < V; a++) {
			
			if (isInMinHeap(minHeap, a) && minHeapVertex->connectedVertexWeights[a] < k[a])
			{
				k[a] = minHeapVertex->connectedVertexWeights[a];
				decreaseKey(minHeap, a, k[a]);
			}

		}
	}

	//Add each vertext key values
	for (int q = 0; q < V; q++)
		sum += k[q];

	return sum;

}
