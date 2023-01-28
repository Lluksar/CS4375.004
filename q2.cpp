#include <iostream>

using namespace std;

struct AdjListNode
{
	int dest;
	struct AdjListNode* next;
};

struct AdjList
{
	struct AdjListNode* head;
};

class Graph
{
public:
	int V;
	struct AdjList* array;

	Graph(int V)
	{
		this->V = V;
		array = new AdjList[V];

		for (int i = 0; i < V; ++i)
			array[i].head = NULL;
	}

	AdjListNode* newAdjListNode(int dest)
	{
		AdjListNode* newNode = new AdjListNode;
		newNode->dest = dest;
		newNode->next = NULL;

		return newNode;
	}

	void addEdge(int src, int dest)
	{
		AdjListNode* newNode = newAdjListNode(dest);
		newNode->next = array[src].head;
		array[src].head = newNode;

		newNode = newAdjListNode(src);
		newNode->next = array[dest].head;
		array[dest].head = newNode;
	}

	void printGraph()
	{
		int v;

		for (v = 0; v < V; ++v)
		{
			AdjListNode* pCrawl = array[v].head;
			cout << "Adjacency list of vertex " << v << "\nhead";

			while (pCrawl)
			{
				cout << " -> " << pCrawl->dest;
				pCrawl = pCrawl->next;
			}

			cout << endl;
		}
	}
};

int main()
{
	Graph g(5);
	g.addEdge(0, 3);
	g.addEdge(0, 4);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(3, 4);

	g.printGraph();

	return 0;
}