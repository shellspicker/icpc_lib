#include "template.h"

debuger bug;

void test_43()
{
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
}

const int dim = 5000;
vector<vector<int>> arr_vv(dim, vector<int>(dim, 0));
zip<int> arr_zip({dim, dim});
int arr_normal[dim][dim];
void test_1000()
{
	double t1, t2;

	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_vv[i][j] = arr_vv[i][j] + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_vv[i][j] = arr_vv[i][j] + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_zip(i, j) = arr_zip(i, j) + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_zip(i, j) = arr_zip(i, j) + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	memset(arr_normal, 0, sizeof(arr_normal));
	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_normal[i][j] = arr_normal[i][j] + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);

	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_normal[i][j] = arr_normal[i][j] + 1;
		}
	}
	t2 = clock();
	bug((t2 - t1) / 1000);
}

int main()
{
	test_43();
	test_1000();
	return 0;
}
