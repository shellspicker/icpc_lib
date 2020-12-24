// 求多项式系数.
vector<double> lagrange_interpolate(vector<double> x, vector<double> y)
{
	assert(x.size() == y.size());
	int n = x.size();
	vector<double> res(n), tmp(n);
	fup (k, 0, n - 2) fup (i, k + 1, n - 1)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	double last = 0;
	tmp[0] = 1;
	fup_range (k, 0, n) fup_range (i, 0, n) {
		res[i] += y[k] * tmp[i];
		swap(last, tmp[i]);
		tmp[i] -= last * x[k];
	}
	return res;
}

