/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  wzyang @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Spring 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;
		int* degrees;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );
		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree(int) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();


	// Friends
	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();


struct edgeInfo{ 
	double weight;
	int vertexA; //Node i
	int vertexB; //Node j
};

/*Bubble Sort Algorithm*/

void BubbleSort(edgeInfo ** arr, int n) {
      bool swapped = true;
      int j = 0;
      edgeInfo* tmp;
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < n - j; i++) {
                  if (arr[i] -> weight > arr[i + 1] -> weight) {
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}

/* CONSTRUCTOR: Constructs a weighted undirected graph with n vertices (by default 50).
Assume that initially there are no connections in the graph (edges will be inserted with the “insert”
method). Throw an illegal_argument() exception if the argument is less than 0. */
Weighted_graph::Weighted_graph(int n ) {

	//cout << "a" << endl;

	if (n < 0){
		throw illegal_argument();
	}

	//cout << "b" << endl;

	graph = new double*[n];

	for (int i = 0; i < n; ++i) {
    	graph[i] = new double[n];
	}

	//cout << "d" << endl;

	degrees = new int[n];
	num_edges = 0;
	num_nodes = n;

	//cout << "e" << endl;


	for (int i = 0; i < num_nodes; i++){
		for (int j = 0; j < num_nodes; j++){
			graph[i][j] = INF;
		}
	}

	//cout << "f" << endl;

	for (int x = 0; x < num_nodes; x++){
		//cout << x << endl;
		degrees[x] = 0;
	}

}

// DESTRUCTOR: Cleans up any allocated memory
Weighted_graph::~Weighted_graph() {

    for( int i = 0; i< num_nodes; i++){
        
        delete [] graph[i];
    }
    
    delete [] graph;
    delete [] degrees;
 
}

/* Returns the degree of the vertex n. Throw an illegal_argument()
exception if the argument does not correspond to an existing vertex. */
int Weighted_graph::degree(int u) const {

	return degrees[u];

}

/* Returns the number of edges in the graph. */
int Weighted_graph::edge_count() const {

	return num_edges;
}

/* If an edge between nodes i and j exists, remove the edge. In this
case or if i equals j return true. Otherwise, if no edge exists, return false. If i or j are outside the
range of [0..n-1], throw an illegal_argument() exception. */
bool Weighted_graph::erase_edge(int i, int j) {

	if (i == j){
		return true;
	}

	if (i >= num_nodes || j >= num_nodes){
		throw illegal_argument();
	}

	if (graph[i][j] != INF && graph[j][i] != INF){
		graph[i][j] = INF;
		graph[j][i] = INF;
		degrees[i]--;
		degrees[j]--;
		num_edges--;

	}
	else{
		return false;
	}

	return true;
}

/* Removes all the edges from the graph. */
void Weighted_graph::clear_edges() {

	for (int i = 0; i < num_nodes; i++){
		for (int j = 0; j < num_nodes; j++){
			graph[i][j] = INF;
		}
	}
	num_edges = 0;
	return;
}

/* If i equals j and are in the graph, return false. Otherwise,
either add a new edge from vertex i to vertex j or, if the edge already exists, update the weight and
return true. Recall that the graph is undirected. If i or j are outside the range of [0..n-1] or if the
weight w is less than or equal to zero, throw an illegal_argument() exception. */
bool Weighted_graph::insert_edge( int i, int j, double d ) {

	/*If i or j are outside the range of [0..n-1] or if the
	weight w is less than or equal to zero, throw an illegal_argument() exception. */
	if (i > num_nodes-1 || j > num_nodes-1 || d < 0){
		throw illegal_argument();
	}

	if (i < 0 || j < 0) {
		throw illegal_argument();
	}

	/*If i equals j and are in the graph, return false.*/
	if (i == j && i < num_nodes && j < num_nodes){
		return false;
	}

	/*if the edge already exists or is getting created, update the weight and
	return true*/
	if(graph[i][j] != INF || graph[j][i] != INF){
	graph[i][j] = d;
	graph[j][i] = d;
	}
	else if (graph[i][j] == INF && graph[j][i] == INF){
	graph[i][j] = d;
	graph[j][i] = d;
	degrees[i]++;
	degrees[j]++;
	num_edges++;
	}

	return true;

}

/* Uses Kruskal’s algorithm to find the
minimum spanning tree. It returns the weight of the minimum spanning tree and the number of
edges that were tested for adding into the minimum spanning tree. */
std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
	
   	int eg_count = 0;				//edge traversal count
	double mst_weight = 0;			//tree weight
	int edges_tested = 0;
	double final_weight = 0.0;

	Disjoint_set sets(num_nodes);
	//Array of edge structures
	edgeInfo ** pointer = new edgeInfo*[num_edges];

	//Sort current edges inside of matrix into array from lowest to highest
	//Check only upper triangular of matrix
	int index = 0;

	for (int i = 0; i < num_nodes; i++){
		for (int j = i; j < num_nodes; j++){
			//If there's an edge then put it into the array
			if(graph[i][j] != INF){
				pointer[index] = new edgeInfo();
				pointer[index] -> weight = graph[i][j];
				pointer[index] -> vertexA = i;
				pointer[index] -> vertexB = j;
				index++;
			}
		}
	}

	//Now I have an array of edge structs I call quick sort to put them in order from
	//lowest to highest

	BubbleSort(pointer,num_edges);

	for (int i=0; i < num_edges; i++){
		cout << " " << pointer[i] -> weight;
	}

	cout << " " << endl;

	for (int i = 0; i < num_edges; i++){
		//int prev = sets.num_sets();
		cout << sets.num_sets() << endl;


		if (sets.num_sets() == 1 ){
			break;
		}

		//If the vertices aren't in the same set then put them together
		if (sets.find_set(pointer[i] -> vertexA) != sets.find_set(pointer[i] -> vertexB)){

			sets.union_sets(pointer[i] -> vertexA, pointer[i] -> vertexB);

			final_weight += pointer[i] -> weight;
			cout << final_weight << endl;

		}
		edges_tested++;


	}


	for (int i = 0; i < num_edges; i++){
			//If there's an edge then put it into the array
		delete pointer[i];
	}	

	delete[] pointer;

	return std::pair<double, int>(final_weight, edges_tested );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	
	// for (int i = 0; i < num_nodes; i++){
	// 	endl;
	// 	for (int j = i; j < num_nodes; j++){
	// 		cout << graph[i][j] << " ";
	// 	}
	// }	
	return out;
}


#endif
