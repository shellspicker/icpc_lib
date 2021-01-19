#include "template.h"
#include "basic/zip.h"

void test_43()
{
	fio.msg("\n---test---\n");
	fio.msg("4 * 3 grid\n");
	zip_vector<int> arr({4,3});
	int t = 0;
	fup (i, 0, 4 - 1) {
		fup (j, 0, 3 - 1) {
			arr(i, j) = ++t;
		}
	}
	fup_range (i, 0, 4 * 3)
		fio.msg("%d%c", arr.data[i], " \n"[i == 4 * 3 - 1]);
	fup (idx, 0, 12 - 1) {
		auto dm = arr.dimension(idx);
		fio.msg("[%d]:", idx);
		fup_range (i, 0, 2)
			fio.msg("%d%c", dm[i], " \n"[i == 2 - 1]);
	}
	fio.msg("---PASS---\n");
}

const int dim = 5000;
vector<vector<int>> arr_vv(dim, vector<int>(dim, 0));
zip_vector<int> arr_zip({dim, dim});
int arr_normal[dim][dim];
void test_1000()
{
	fio.msg("\n---test---\n");
	fio.msg("for each\n");
	double t1, t2;

	fio.msg("vv arr\n");
	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_vv[i][j] = arr_vv[i][j] + 1;
		}
	}
	t2 = clock();
	fio.msg("%.4f\n", (t2 - t1) / 1000);

	fio.msg("vv arr inverse\n");
	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_vv[i][j] = arr_vv[i][j] + 1;
		}
	}
	t2 = clock();
	fio.msg("%.4f\n", (t2 - t1) / 1000);

	fio.msg("zip_vector arr\n");
	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_zip(i, j) = arr_zip(i, j) + 1;
		}
	}
	t2 = clock();
	fio.msg("%.4f\n", (t2 - t1) / 1000);

	fio.msg("zip_vector arr inverse\n");
	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_zip(i, j) = arr_zip(i, j) + 1;
		}
	}
	t2 = clock();
	fio.msg("%.4f\n", (t2 - t1) / 1000);

	fio.msg("normal arr\n");
	memset(arr_normal, 0, sizeof(arr_normal));
	t1 = clock();
	fup (i, 0, dim - 1) {
		fup (j, 0, dim - 1) {
			arr_normal[i][j] = arr_normal[i][j] + 1;
		}
	}
	t2 = clock();
	fio.msg("%.4f\n", (t2 - t1) / 1000);

	fio.msg("normal arr inverse\n");
	t1 = clock();
	fup (j, 0, dim - 1) {
		fup (i, 0, dim - 1) {
			arr_normal[i][j] = arr_normal[i][j] + 1;
		}
	}
	t2 = clock();
	fio.msg("%.4f\n", (t2 - t1) / 1000);
	fio.msg("---PASS---\n");
}

void test_constructor_zip()
{
	double t1, t2;
	fio.msg("\n---test---\n");
	fio.msg("constructor of zip_vector arr\n");
	t1 = clock();
	zip_vector<int> arr_zip({5000, 5000});
	t2 = clock();
	fio.msg("%.4f\n", (t2 - t1) / 1000);
	fio.msg("---PASS---\n");
}

void test_constructor_vv()
{
	double t1, t2;
	fio.msg("\n---test---\n");
	fio.msg("constructor of vv arr\n");
	t1 = clock();
	vector<vector<int>> arr_vv(5000, vector<int>(5000, 0));
	t2 = clock();
	fio.msg("%.4f\n", (t2 - t1) / 1000);
	fio.msg("---PASS---\n");
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
