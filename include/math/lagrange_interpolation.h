#ifndef LAGRANGE_INTERPOLATION_H
#define LAGRANGE_INTERPOLATION_H 1

vector<double> interpolate(vector<double> x, vector<double> y, int n)
{
	vector<double> res(n), tmp(n);
	assert(x.size() == y.size());
	fup (k, 0, n - 2) fup (i, k + 1, n - 1)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	double last = 0;
	tmp[0] = 1;
	fup (k, 0, n - 1) fup (i, 0, n - 1) {
		res[i] += y[k] * tmp[i];
		swap(last, tmp[i]);
		tmp[i] -= last * x[k];
	}
	return res;
}

#endif
