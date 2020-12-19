# kruskal_minimum_spanning_tree

* Given a connected and undirected graph, a spanning tree of that graph is a subgraph that is a tree and connects all the vertices together.  
* A single graph can have many diffetent spanning trees.  
* A minimum spanning tree or minimum weight spanning tree for a weighted, connected and undirected graph is a spanning tree with weight less than or equal to the weight of every other spanning tree.  
* The weight of a spanning tree is the sum of weights given to each edge of the spanning tree.  

1. Sort all the edges in non-decreasing order of their weight.
2. Pick the smallest edge. Check if forms a cycle with the spanning tree formed so far.
3. If cycle is not formed, include this edge. Else, discard it.  
4. Repeat step #2 until there are (V-1) edges in the spanning tree.
