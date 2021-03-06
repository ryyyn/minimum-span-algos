/*
/  Generate a grqph in adjacency matrix style. 
*/

#include <stdexcept>
#include <vector>
#include <fstream>
#include <iostream>

#define ZBASED_1D_POS(r,c,num_cols) (r*num_cols+c)

/*
/  params: size, and outfile
*/
int main(int argc, char*argv[]) {
    if (argc != 3)
        throw std::invalid_argument("Incorrect amount of parameters.");

    int range = 5000;
    int size = atoi(argv[1]);

    std::vector<int> data (size*size);
  
    srand(time(NULL));
    int offset=1;
    for(int i=0; i<size; ++i) {
        for(int j=offset; j<size; ++j)
            if((double)rand()/(double)RAND_MAX < .1) { //10% chance of any 2 verticies being connected
                int distance = rand() % range;
                data.at(ZBASED_1D_POS(i, j, size)) = distance;
                data.at(ZBASED_1D_POS(j, i, size)) = distance;
	    }
	    ++offset;
    }
  
    std::ofstream outfile;
    outfile.open(argv[3]);

    outfile << size << "\n";

    for(int i=0; i<=(size*size-1); ++i) {
        if((i+1)%size)
            outfile<<data.at(i)<<" ";
        else
            outfile<<data.at(i)<<"\n";
    }  
    outfile.close();
}
