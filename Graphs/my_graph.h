// =================== Support Code =================
// Graph.
//
//
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

// Create a neighbor data structure to server as the neighbor's list.
// In our case, we will stores 'integers' as our neighbors that 
// corresponding to the data that the actual nodes store.
typedef struct neighbor{
    int visited;
	int data;
	struct neighbor * next;
}neighbor_t;

// Create a node data structure to store data within
// our graph. In our case, we will stores 'integers'
// as our data in the nodes
typedef struct node{
    int visited;
	int data;
	struct node *next;
	struct neighbor * neighbor;
}node_t;

typedef struct queue 
{ 
    int front, back, size; 
    unsigned capacity; 
    int* data; 
}queue_t;

// Create a graph data structure
// Our graph keeps track of the number of nodes, the number of edges and an array
// of all the nodes in the graph, and the maximum number of nodes we store in our graph.
typedef struct graph{
	int numNodes;		
    int numEdges;
	node_t* nodes;	 //an array of nodes storing all of our nodes.
}graph_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
graph_t* create_graph(){
	
	graph_t* myGraph= (graph_t*)malloc(sizeof(graph_t));
    myGraph->numNodes = 0;
    myGraph->numEdges = 0;	

	return myGraph;
}

// Graph Empty
// Check if the graph is empty
// Returns >=0 if true (The graph is completely empty, i.e. numNodes == 0 )
// Returns -1 if false (the graph has at least one node)
int graph_empty(graph_t* g){
    if(g->numNodes == 0){
        return 0;
    }
    else{
	return -1;
    }
}

void addHead(graph_t* g, int item){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = item;
    g->nodes = newNode;
    g->nodes->neighbor = NULL;
    g->nodes->next = NULL;
    g->numNodes++;
}

// Adds a new node withe the correspoding item in the graph.
// Returns a -1 if the operation fails or has duplicate node. (otherwise returns >=0 on success) 
// (i.e. the memory allocation for a new node failed).
int graph_add_node(graph_t* g, int item){
    node_t* iter;
    iter = g->nodes;
    if(g->numNodes == 0){
        addHead(g, item);
        return 0;
    }

    //search if the node exists already.
    for(int i = 0; i < g->numNodes; i++){
        if(item == iter->data){
            return -1;
        }
        if(iter->next != 0){
        iter = iter->next;
        }    
        
    }

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
        newNode->data = item;
        newNode->next = g->nodes;
        g->nodes = newNode;
        g->nodes->neighbor = NULL;
        g->numNodes++;
    
	return 0; 
}

// Removes the node from the graph and the corresponding edges connected 
// to the node.
// Returns a -1 if the operation fails (otherwise returns >=0 on success).
// (the node to be removed doesn't exist in the graph).
int graph_remove_node(graph_t* g, int item){
	return -1; 
}


node_t* neighborHelper(node_t* sourceNode, node_t* destinationNode){
    neighbor_t* newNeighbor = (neighbor_t*)malloc(sizeof(neighbor_t));
    newNeighbor->data = destinationNode->data;
    
    
        if(sourceNode->neighbor != NULL){
        neighbor_t* iter;

        
         iter = newNeighbor;
         iter->next = sourceNode->neighbor;
         sourceNode->neighbor = iter;
         sourceNode->neighbor->visited = 0;

        }

        else{
        sourceNode->neighbor = newNeighbor;
        sourceNode->neighbor->visited = 0;
        sourceNode->neighbor->next = NULL;
        }

        return sourceNode;

}


node_t* set_source_node(graph_t* g, int source){
    
    node_t* iter = g->nodes;
    g->nodes = iter;
    node_t* sourceNode = NULL;
     for(int i = 0; i < g->numNodes; i++){
        
        if(source == iter->data){  
           sourceNode = iter;
        
        }

        if(iter->next != 0){
        iter = iter->next;
        }    

    }

    return sourceNode;

}

node_t* set_destination_node(graph_t* g, int destination){
    node_t* iter = g->nodes;
    node_t* destinationNode = NULL;
     for(int i = 0; i < g->numNodes; i++){
        
        if(destination == iter->data){
           destinationNode = iter;
        }
        if(iter->next != 0){
        iter = iter->next;
        }    

    }
    return destinationNode;

}

//Adds an edge from source to destination. 
//If source or desination is not found, or the edge already exists in the graph returns -1.
//Otherwise it returns >= 0
int graph_add_edge(graph_t * g, int source, int destination){
    node_t* sourceNode;
    node_t* destinationNode;


    sourceNode = set_source_node(g,source);
    destinationNode = set_destination_node(g, destination);

    if(sourceNode == NULL || destinationNode == NULL){
        return -1;
    }
  
    neighborHelper(sourceNode, destinationNode);
    g->numEdges++;


	return 0;
}

//Removes an edge from source to destination. 
//If source or desination is not found in the graph returns -1.
//If no such edge exists also returns -1.
//Otherwise it returns >=0
int graph_remove_edge(graph_t * g, int source, int destination){
     
    node_t* sourceNode;
    node_t* destinationNode;

    sourceNode = set_source_node(g,source);
    destinationNode = set_destination_node(g, destination);
    
    if(sourceNode == NULL || destinationNode == NULL){
        return -1;
    }
  
    node_t* cIter = sourceNode;
    while(cIter->neighbor->data != destination){
        cIter->neighbor = cIter->neighbor->next;
    }
    cIter->neighbor = NULL;
}


//Returns >=0 if the node with value is in the graph, otherwise returns -1;
int contains_node( graph_t * g, int value){
    node_t* sourceNode;
    sourceNode = set_source_node(g, value);

    if(sourceNode == NULL){
        return -1;
    }
    else{
        return 1;
    }
    
  
}

//Returns >=0 if an edge from source to destination exists, -1 otherwise.
int contains_edge( graph_t * g, int source, int destination){
    node_t sourceNode;

    sourceNode = *set_source_node(g, source);
  
   node_t cIter;
   cIter = sourceNode;
   
    while(cIter.neighbor != NULL){
        if(cIter.neighbor->data == destination){
            return 1;
        }
        else{
           cIter.neighbor = cIter.neighbor->next; 
        }
    }
	return -1;
}
//Returns an int array of all the neighbors of the node with data=value.
int* getNeighbors( graph_t * g, int value ){
    node_t sourceNode;

    sourceNode = *set_source_node(g, value);
    int i = 0;
    int neighborArray[g->numNodes];
  
   node_t cIter = sourceNode;
   
   
       while(cIter.neighbor != NULL){
        neighborArray[i] = cIter.neighbor->data;
        cIter.neighbor = cIter.neighbor->next;
        i++;
       }

        
    return neighborArray;

}

// Returns the number of neighbors for value.
int numNeighbors( graph_t * g, int value ){
    node_t sourceNode;
    sourceNode = *set_source_node(g, value);
    int numNeighbors = 0;
  
   node_t cIter = sourceNode;
   
    while(cIter.neighbor != NULL){
        cIter.neighbor = cIter.neighbor->next;
        numNeighbors++;
        
    }
	return numNeighbors;
}


// Helps find which elements in the graph are root elements (inDegree of zero).
// Returns an array containing said root elements.
int* root_helper(graph_t* g){
    node_t iter = *g->nodes;
    
    int log[g->numNodes];
    int rootArray[g->numNodes];
    int normArr[g->numNodes];
    int i = 0;
    int j = 0;

    for(int i = 0; i < g->numNodes; i++){
        normArr[i] = iter.data;
        

        if(i < g->numNodes -1){
        iter = *iter.next;
        }
    }

    iter = *g->nodes;
       
       while(i < g->numNodes){
        while(!iter.neighbor){
            iter = *iter.next;
            i++;
        }
         while(iter.neighbor != NULL){
             for(int i = 0; i < sizeof(normArr)/sizeof(normArr[0]); i++){
             if(normArr[i] == iter.neighbor->data){
                 normArr[i] = 0;
             }
             }
            log[j] = iter.neighbor->data;
            j++;
            iter.neighbor = iter.neighbor->next;
        }
        i++;
       }
    int z = 0;
    for(int i = 0; i < sizeof(normArr)/sizeof(normArr[0]); i++){
        if(normArr[i] != 0){
            rootArray[z] = normArr[i];
            z++;
        }
    }
      
    return rootArray;
}

// Helps enqueue elements for the graph_print function
void enqueue(queue_t* q, int item){
    q->data[q->front] = item;
	q->front = (q->front + 1) % q->capacity;  	
	q->size++;
}

// Helps dequeue elements for the graph_print function
int dequeue(queue_t* q){
    int data = q->data[q->back];
	q->back = (q->back + 1) % q->capacity;
	q->size--;
    return data;
}
	
// Prints the the graph using BFS
// For NULL or empty graph it should print nothing. 
void graph_print(graph_t * g){
    queue_t* myQueue = (queue_t*)malloc(sizeof(queue_t));
    myQueue->size = 0;
    myQueue->back = 0;
    int* rootArray;
    int check = has_cycle(g);
    
    if(g != NULL && check == -1){
        rootArray = root_helper(g);
    }
    else{
        return;
    }
    myQueue->capacity = g->numNodes;
    int myArray[myQueue->capacity];
    myQueue->data = myArray;
    

    for(int i = 0; i < sizeof(rootArray)/sizeof(rootArray[0]); i++){
        //Enqueue root node and print 
        node_t sourceNode = *set_source_node(g, rootArray[i]);
        enqueue(myQueue, sourceNode.data);
        sourceNode.visited = 1;
        printf("%d\n", dequeue(myQueue));
       
       //Iterate through a particualr root node's neighbors, match them to their node identity and set visited to 1 (true)
       //after enqueueing
        while(sourceNode.neighbor != NULL){
        node_t* nbNode = set_source_node(g, sourceNode.neighbor->data);

        if(nbNode->visited == 0){
        enqueue(myQueue, nbNode->data);
        nbNode->visited = 1;
        printf("%d\n", dequeue(myQueue));
        }

        sourceNode.neighbor = sourceNode.neighbor->next;
        }

    }

    free(myQueue);

}
// Graph Size
// Returns the number of nodes in the graph
// Returns -1 on failure.
int graph_num_nodes(graph_t* g){
    if(g->numNodes){
	return g->numNodes;
    }
    else{
        return -1;
    }
}

// Graph Size
// Returns the number of edges in the graph, 
// Returns -1 on failure. 
int graph_num_edges(graph_t* g){
	 if(g->numEdges){
	return g->numEdges;
    }
    else{
        return -1;
    }
}

// Returns 0 if I can reach the destination from source, -1 otherwise.
int is_reachable(graph_t * g, int source, int dest){

    node_t sourceNode = *set_source_node(g, source);
    
    while(sourceNode.neighbor != NULL){
        if(sourceNode.neighbor->data == dest){
            return 0;
        }
        
        sourceNode.neighbor = sourceNode.neighbor->next;

    }

    return -1;
}

// Returns 0 if there is a cycle in the graph, -1 otherwise
int has_cycle(graph_t * g){
    node_t iter = *g->nodes;

    while(iter.next != NULL){
        while(iter.neighbor != NULL){
            if(iter.neighbor->data == iter.data){
                return 0;
            }
            iter.neighbor = iter.neighbor->next;
        }

       iter = *iter.next;
       if(iter.next == NULL){
           while(iter.neighbor != NULL){
            if(iter.neighbor->data == iter.data){
                return 0;
            }
            iter.neighbor = iter.neighbor->next;
        }

       }
    }
        
return -1;
}


//prints any path from source to destination if there exists one
void print_path(graph_t * g, int source, int dest){
     if(contains_edge(g, source, dest) == -1){
        printf("Pathway not found!\n");
        return;
    }
    node_t sourceNode = *set_source_node(g, source);
   
    printf("%d\n", sourceNode.data);


    while(sourceNode.neighbor != NULL){
        if(sourceNode.neighbor->data == dest){
            printf("%d\n", sourceNode.neighbor->data);
            return;
        }
        printf("%d\n", sourceNode.neighbor->data);
        
        sourceNode.neighbor = sourceNode.neighbor->next;

    }

}




// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_graph(graph_t* g){
    node_t* temp;
    node_t* iter = g->nodes;
    neighbor_t* temp2;

    
    while(iter != NULL){
        while(iter->neighbor !=NULL){
            temp2 = iter->neighbor;
            free(temp2);
            iter->neighbor = iter->neighbor->next;
    }
        temp = iter;
        free(temp);
        iter = iter->next;
    }

    free(g);

}



#endif
