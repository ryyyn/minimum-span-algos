# minimum-span-algos
Two algorithms for solving the minimum spanning tree (MST) problem

<b>Building and running</b>

Compile: <code>g++ -std=c++11 -o MST MST.cpp</code> 

Run: <code>./MST -ALGORITHM -INPUT_FILE [-OUTPUT_FILE]</code>

ALGORITHM: either "Prim", "Dijkstra", or the first letter of either

INPUT_FILE: a test file containing a single number on the first line that represents the number of verticies, and subsequent lines containing the adjacency-matrix representation of the graph. No commas.

OUTPUT_FILE: if none is specified, the program will simply report the amount of time it took to generate the MST without writing

The output will be the MST in adjacency-matrix representation.

<b>Random graph generator</b>

Compile: <code>g++ -std=c++11 -o GraphGen GraphGen.cpp</code>

Run: <code>./GraphGen -SIZE -OUTPUT_FILE</code>

SIZE: the number of verticies

OUTPUT_FILE will be formatted the same as INPUT_FILE for MST above


<b>Algorithm comparison</b>

Prim's algorithm is naive, taking O(|V|^2) time.

Kruskal's algorithm is implemented using collapsing UNION-FIND, and runs in O(E α(V)) time.

                      Kruskall's  Prim's
    Input Size: 200     ~0.0       0.7
    Input Size: 400      0.01      4.94
    Input Size: 800      0.06     20.78
    Input Size: 1600     0.20      ???
    Input Size: 3200     0.98      ???
                          Runtime, s
