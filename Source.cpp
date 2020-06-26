// C++program to check if a connected 
// graph is bipartite or not using DFS 
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>
using namespace std;

// function to store the connected nodes 
void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

// function to check whether a graph is bipartite or not 
bool isBipartite(vector<int> adj[], int v,
	vector<bool>& visited, vector<int>& color)
{

	for (int u : adj[v]) {

		// if vertex u is not explored before 
		if (visited[u] == false) {

			// mark present vertex as visited 
			visited[u] = true;

			// mark its color opposite to its parent 
			color[u] = !color[v];

			// if the subtree rooted at vertex v is not bipartite 
			if (!isBipartite(adj, u, visited, color))
				return false;
		}

		// if two adjacent are colored with same color then 
		// the graph is not bipartite 
		else if (color[u] == color[v])
			return false;
	}
	return true;
}

// Driver Code 
int main()
{	
	ifstream myfile("graph.txt");
	if (!myfile.is_open()) {
		std::cout << "Unable to open file";
		return 0;
	}
		
	string line;
	int V;
	int first, second;
	cout << "G(V,E)" << endl;
		getline(myfile, line);
		V = stoi(line);
		cout <<"V = "<< V << endl;


		vector<int> *adj = new vector<int>[V + 1];
		string intermediate;
		cout << "E = { ";
			while (getline(myfile,line)){

				std::stringstream str(line);
				getline(str, intermediate, '-');
				first = stoi(intermediate);
				getline(str, intermediate);
				second = stoi(intermediate);
				// to maintain the adjacency list of graph 
				addEdge(adj, first, second);
				cout << "{" << first << "," << second << "} ";
				
			}
			cout << "}" << endl;
			myfile.close();
	

	// to keep a check on whether 
	// a node is discovered or not 
	vector<bool> visited(V + 1);

	// to color the vertices 
	// of graph with 2 color 
	vector<int> color(V + 1);


	// adding edges to the graph 

	// marking the source node as visited 
	visited[1] = true;

	// marking the source node with a color 
	color[1] = 0;

	// Function to check if the graph 
	// is Bipartite or not 
	if (isBipartite(adj, 1, visited, color)) {
		cout << "Graph is Bipartite" << endl;
	}
	else {
		cout << "Graph is not Bipartite" << endl;
	}

	return 0;
}