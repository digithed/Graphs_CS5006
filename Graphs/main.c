// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
    graph_t * testGraph = create_graph();

    // Add nodes
    graph_add_node(testGraph, 5);
    graph_add_node(testGraph, 3);
    graph_add_node(testGraph, 4);
    graph_add_node(testGraph, 7);

    // Add edges
    graph_add_edge(testGraph, 5, 4);
    graph_add_edge(testGraph, 3, 7);
    graph_add_edge(testGraph, 3, 4);

    graph_print(testGraph);

    // Test cyclic aspect of graph by adding an edge between a node and itself
    graph_add_edge(testGraph, 5, 5);
    
    //Test getting the number of neighbors, test if a node contains a certain edge,
    //Test if two nodes are reachable and test if there is a cycle in the graph.
    //Print out a pathway between two nodes and test free graph.
    getNeighbors(testGraph, 3);
    printf("Num edges: %d\n", numNeighbors(testGraph, 3));
    printf("Contains? %d\n", contains_edge(testGraph, 3, 7));
    printf("Reachable? %d\n", is_reachable(testGraph, 3, 5));
    printf("Has cycle? %d\n", has_cycle(testGraph));
    print_path(testGraph, 5, 5);
    free_graph(testGraph);
   
    return 0;
}