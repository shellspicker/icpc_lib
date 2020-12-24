// 差商, 这个结果不会很大.
double difference_quotient(vector<double> x, vector<double> y, int k)
{
	double result = 0;
	fup (i, 0, k) {
		double temp = 1;
		fup (j, 0, k)
			if (i ^ j)
				temp = temp / (x[i] - x[j]);
		temp = y[i] * temp;
		result += temp;
	}
	return result;
}
// 直接求值, 暂时不知道怎么求系数...
// double换成ull, 确定最高次不会爆2^64的话, 可以直接用.
ull newton_interpolation(vector<double> x, vector<double> y, ull X)
{
	ull result = y[0];
	fup (i, 1, x.size() - 1) {
		ull temp = 1;
		fup (j, 0, i - 1)
			temp *= (X - ll(x[j]));
		ull diff = difference_quotient(x, y, i);
		result += diff * temp;
	}
	return result;
}

