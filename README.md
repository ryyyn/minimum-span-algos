# minimum-span-algos
Two algorithms for solving the minimum spanning tree problem

</b>Building and running</b>
Compile with <code>g++ -std=c++11 -o MST MST.cpp</code> 
run with ./MST -ALGORITHM -INPUT_FILE [-OUTPUT_FILE]

ALGORITHM should be either "Prim", "Dijkstra", or the first letter of either
Unfortunately I did not have time to implement Sollin's

INPUT_FILE should be a test file containing a single number on the first line that represents the number of verticies, and subsequent lines containing the adjacency-matrix representation of the graph. No commas.

If no OUTPUT_FILE is specified, the program will just report the amount of time it took to generate the mst without writing any output.
The output will be the mst in adjacency-matrix representation.

-----------------

Random graph generator:
compile with g++ -std=c++11 -o GraphGen GraphGen.cpp
run with ./GraphGen -SIZE -METHOD -OUTPUT_FILE

SIZE is the number of verticies

METHOD should be either -1 or -2 (the two detailed in Dr. Spinrad's email)

OUTPUT_FILE will be formatted the same as INPUT_FILE for MST above

-----------------

Prim's algorithm was implemented using an array.  This is the most naive method, taking O(|V|^2) time.

Kruskal's algorithm was implemented using collapsing UNION-FIND.  However, the sorting algorithm used to sort the edges is STD::sort, a comparison-based sort. This means it cannot acheive the optimal running time of O(E α(V)) time, and instead the algorithm has a lower bound of E log|E|.

Times were as follows:
                    Kruskall's               Prim's
Input Size: 200   Running time: ~0    Running time: 0.7
Input Size: 400   Running time: .01   Running time: 4.94
Input Size: 800   Running time: .06   Running time: 20.78
Input Size: 1600  Running time: .20   Running time: ???
Input Size: 3200  Running time: .98   Running time: ???

Both generally follow their expected times.

Unfortunately, I didn't have time to implement Sollin's algorithm.
