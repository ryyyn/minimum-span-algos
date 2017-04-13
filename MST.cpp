#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
#include <ctime>

#define ZBASED_1D_POS(r,c,num_cols) (r*num_cols+c)

int size;

void read(char* filename, std::vector<int>& data)
{
  std::ifstream infile;
  infile.open(filename);

  if (infile.fail())
    throw std::invalid_argument("File cannot be read.");

  infile >> size;

  data.resize(size*size);

  for(int i=0; i<=(size*size-1); ++i)
    infile >> data.at(i);
  
  infile.close();
}

void write(char* filename, std::vector<int>& data)
{
  std::ofstream outfile;
  outfile.open(filename);

  for(int i=0; i<=(size*size-1); ++i)
    {
      if((i+1)%size)
	outfile<<data.at(i)<<" ";
      else
	outfile<<data.at(i)<<"\n";
    }

  outfile.close();
}

void prim(std::vector<int>& data, std::vector<int>& sol)
{
  std::vector<bool> added(size);
  added.at(0) = true;
  
  int solSize = 0;
  while(solSize < size-1)
    {
      int minCost = INT_MAX;
      int minEdgeR, minEdgeC;

      for(int i=0; i<size; ++i)
	{
	  if(added.at(i))
	    {
	      for(int j=0; j<size; ++j)
		if(!added.at(j))
		  {
		    int cost = data.at(ZBASED_1D_POS(i,j,size));
  		    if(cost!=0 && cost<minCost)
		      minCost = cost, minEdgeR = i, minEdgeC = j;
		  }
	    }
	}

      added.at(minEdgeC) = true;
      sol.at(ZBASED_1D_POS(minEdgeR, minEdgeC, size)) = minCost;
      sol.at(ZBASED_1D_POS(minEdgeC, minEdgeR, size)) = minCost;
      ++solSize;
    }
}

struct TreeNode
{
  int num;
  TreeNode* parent;
  int rank;
  
  TreeNode(int i) : num(i), parent(this), rank(0)
  { }  
};

TreeNode* find(TreeNode* v)
{
  if(v->parent != v)
    v->parent = find(v->parent);
  return v->parent;
}

void union2(TreeNode* u, TreeNode* v)
{
  TreeNode* uRoot = find(u);
  TreeNode* vRoot = find(v);
  
  if(uRoot->rank < vRoot->rank)
    {
      uRoot->parent = vRoot;
      vRoot->rank+=uRoot->rank;
    }
  else
    {
      vRoot->parent = uRoot;
      uRoot->rank+=vRoot->rank;
    }
}

struct Edge
{
  int weight;
  int u;
  int v;
  Edge(int weight, int u, int v) : weight(weight), u(u), v(v)
  { }
  //make op<
};

void kruskal(std::vector<int>& data, std::vector<int>& sol)
{
  std::vector<Edge*> edges (size*size);
  int offset=1, pos=0;
  for(int i=0; i<size; ++i)
    {
      for(int j=offset; j<size; ++j)
	if(data.at(ZBASED_1D_POS(i,j,size))!=0)
	  edges.at(pos++) = new Edge(data.at(ZBASED_1D_POS(i,j,size)),i,j);
      ++offset;
    } 

  edges.resize(pos);
  edges.shrink_to_fit();

  //sort edges
  std::sort(edges.begin(), edges.end(), [&](Edge* a, Edge* b){return (a->weight < b->weight);});
    
  std::vector<TreeNode*> verticies (size);
  for(int i=0; i<size; ++i)
    verticies.at(i) = new TreeNode(i);
  
  //could be a for_each w/ lambda, but eh
  for(int i=0; i<edges.size(); ++i)
    {
      Edge* tmp = edges.at(i);
      int u = tmp->u, v = tmp->v;
      if(find(verticies.at(u))!=find(verticies.at(v)))
        {
	  union2(verticies.at(u),verticies.at(v));
	  sol.at(ZBASED_1D_POS(u, v, size)) = tmp->weight;
	  sol.at(ZBASED_1D_POS(v, u, size)) = tmp->weight;
	}
    }
}

void sollin(std::vector<int>& data, std::vector<int>& sol)
{
  std::vector<std::vector<int>> sets(size);
  for(int i=0; i<size; ++i)
    sets.at(i)=std::vector<int>{i};
  
  int newSize = size;

  std::vector<TreeNode*> verticies (size);
  for(int i=0; i<size; ++i)
    verticies.at(i) = new TreeNode(i);
  
  while(0)
    {
      for(int n=0; n<size; ++n)
	{
	  for(int i=0; i<verticies.at(n)->rank; ++i)
	    //if in same set search
	    //if(find(verticies.at(u))!=find(verticies.at(v)))
	      {
		
		//union2(verticies.at(u),verticies.at(v));
		//sol.at(ZBASED_1D_POS(u, v, size)) = tmp->weight;
		//sol.at(ZBASED_1D_POS(v, u, size)) = tmp->weight;
	      } 
	}
    }
}

int main(int argc, char*argv[])
{
  if (argc < 3)
    throw std::invalid_argument("Incorrect amount of parameters passed to main.");

  char c = argv[1][1];
  
  std::vector<int> data;

  read(argv[2], data);

  std::vector<int> sol(size*size, 0);

  std::clock_t start;
  double duration;
  
  start = std::clock();
  
  if (c=='P' || c=='p')
    prim(data, sol);
    
  if (c=='K' || c=='k')
    kruskal(data, sol);
  
  if (c=='S' || c=='s' || c=='B' || c=='b')
    sollin(data, sol);


  duration = (std::clock()-start) / (double)CLOCKS_PER_SEC;
  
  std::cout<<"The algorithm took "<< duration <<"seconds.\n";

  if(argc==4)
    write(argv[3], sol);
}
