#include "template.h"

debuger bug;

void test_43()
{
	bug("\n---test---");
	bug("4 * 3 grid");
	zip<int> arr({4,3});
	int t = 0;
	fup (i, 0, 4 - 1) {
		fup (j, 0, 3 - 1) {
			arr(i, j) = ++t;
		}
	}
	bug(arr.data);
	fup (i, 0, 12 - 1) {
		bug(arr.get_dim(i));
	}
	bug("---PASS---");
}

const int dim = 5000;
vector<vector<int>> arr_vv(dim, vector<int>(dim, 0));
zip<int> arr_zip({dim, dim});
int arr_normal[dim][dim];
void test_1000()
{
	bug("\n---test---");
	bug("for each");
	double t1, t2;

	bug("vv arr");
	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_vv[i][j] = arr_vv[i][j] + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	bug("vv arr inverse");
	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_vv[i][j] = arr_vv[i][j] + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	bug("zip arr");
	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_zip(i, j) = arr_zip(i, j) + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	bug("zip arr inverse");
	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_zip(i, j) = arr_zip(i, j) + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	bug("normal arr");
	memset(arr_normal, 0, sizeof(arr_normal));
	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_normal[i][j] = arr_normal[i][j] + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	bug("normal arr inverse");
	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_normal[i][j] = arr_normal[i][j] + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);
	bug("---PASS---");
}

void test_constructor_zip()
{
	double t1, t2;
	bug("\n---test---");
	bug("constructor of zip arr");
	t1 = clock();
	zip<int> arr_zip({5000, 5000});
	t2 = clock();
	bug((t2 - t1) / 1000);
	bug("---PASS---");
}

void test_constructor_vv()
{
	double t1, t2;
	bug("\n---test---");
	bug("constructor of vv arr");
	t1 = clock();
	vector<vector<int>> arr_vv(5000, vector<int>(5000, 0));
	t2 = clock();
	bug((t2 - t1) / 1000);
	bug("---PASS---");
}


void test_constructor()
{
	test_constructor_vv();
	test_constructor_zip();
}

int main()
{
	test_43();
	test_constructor();
	test_1000();
	return 0;
}
