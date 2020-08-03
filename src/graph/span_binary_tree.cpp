#define FAST_IO 1
#include "template.h"
#include "basic/rand.h"

int main()
{
	random_binary_tree bt;
	bt.resize(50);
	bt.gao();
	bt.print();
	return 0;
}
