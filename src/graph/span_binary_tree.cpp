#define FAST_IO 1
#include "template.h"
#include "basic/rand.h"
#include "data_structure/dsu.h"
#include "graph/graph.h"
#include "basic/rand_binary_tree.h"

int main()
{
	random_binary_tree bt;
	bt.resize(50);
	bt.gao();
	bt.print();
	return 0;
}
