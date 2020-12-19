#include <bits/stdc++.h>
using namespace std;

// weighted edge in graph
class Edge {
public:
    int src, dest, weight;
};

// connected, undirected and weighted graph
class Graph {
public:
    int V; // number of vertices
    int E; // number of edges

    // graph is represented as an array of edges
    Edge* edge;
};

// create a graph with V vertices and E edges
Graph* create_graph(int V, int E) {
    Graph* graph = new Graph;

    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];

    return graph;
}

// how to compare two edges according to their weights
int compare_edge(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;

    return a1->weight > b1->weight;
}

// subset for union-find
class Subset {
public:
    int parent;
    int rank;
};

// find set of an element i
int find(Subset subsets[], int i) {
    // find root and make root as parent of i
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }

    return subsets[i].parent;
}

// union of two sets of x and y
void union_set(Subset subsets[], int x, int y) {
    int x_root = find(subsets, x);
    int y_root = find(subsets, y);

    // attach smaller rank
    if (subsets[x_root].rank < subsets[y_root].rank) {
        subsets[x_root].parent = y_root;
    } else if (subsets[x_root].rank > subsets[y_root].rank) {
        subsets[y_root].parent = x_root;
    } else {
        subsets[y_root].parent = x_root;
        subsets[x_root].rank++;
    }
}

// minimum spanning tree using Kruskal's algorithm
void kruskal_minimum_spanning_tree(Graph* graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0; // index used for result[]
    int i = 0; // index used for sorted edges

    // sort all edges in non-decreasing order of weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare_edge);

    // allocate memory for creating V subsets
    Subset* subsets = new Subset[(V * sizeof(Subset))];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E) {
        // pick smallest edge
        // increment index for next
        Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // doesn't cause cycle
        if (x != y) {
            result[e++] = next_edge;
            union_set(subsets, x, y);
        }
    }

    cout << "Following ara the edges in the constructed MST\n";
    int minimum_cost = 0;
    for (i = 0; i < e; ++i) {
        cout << result[i].src << " -- " << result[i].dest
             << " == " << result[i].weight << endl;
        minimum_cost = minimum_cost + result[i].weight;
    }

    cout << "Minimum Cost Spanning Tree: " << minimum_cost << endl;
}

int main() {
    int V = 9;
    int E = 14;
    Graph* graph = create_graph(V, E);

    // add edge
    // 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 4;

    // 0-7
    graph->edge[1].src = 0;
    graph->edge[1].dest = 7;
    graph->edge[1].weight = 8;

    // 1-7
    graph->edge[2].src = 1;
    graph->edge[2].dest = 7;
    graph->edge[2].weight = 11;

    // 1-2
    graph->edge[3].src = 1;
    graph->edge[3].dest = 2;
    graph->edge[3].weight = 8;

    // 7-8
    graph->edge[4].src = 7;
    graph->edge[4].dest = 8;
    graph->edge[4].weight = 7;

    // 7-6
    graph->edge[5].src = 7;
    graph->edge[5].dest = 6;
    graph->edge[5].weight = 1;

    // 8-2
    graph->edge[6].src = 8;
    graph->edge[6].dest = 2;
    graph->edge[6].weight = 2;

    // 8-6
    graph->edge[7].src = 8;
    graph->edge[7].dest = 6;
    graph->edge[7].weight = 6;

    // 2-3
    graph->edge[8].src = 2;
    graph->edge[8].dest = 3;
    graph->edge[8].weight = 7;

    // 2-5
    graph->edge[9].src = 2;
    graph->edge[9].dest = 5;
    graph->edge[9].weight = 4;

    // 6-5
    graph->edge[10].src = 6;
    graph->edge[10].dest = 5;
    graph->edge[10].weight = 2;

    // 3-5
    graph->edge[11].src = 3;
    graph->edge[11].dest = 5;
    graph->edge[11].weight = 14;

    // 3-4
    graph->edge[12].src = 3;
    graph->edge[12].dest = 4;
    graph->edge[12].weight = 9;

    // 5-4
    graph->edge[13].src = 5;
    graph->edge[13].dest = 4;
    graph->edge[13].weight = 10;

    kruskal_minimum_spanning_tree(graph);

    return 0;
}
