/*
 * manacher, 最长回文串.
 *
 * 需要预处理原串, 开头添加'^', 每个字符左右添加'#', 末尾添加'$'.
 * 一共2 * len + 3长度.
 */
class manacher {
public:
	string insert(const string &s) {
		string ret = "^$";
		int len = s.length();
		if (!len)
			goto end;
		ret = "^#";
		fup_range (i, 0, len)
			ret += s[i], ret += '#';
		ret += '$';
end:
		return ret;
	}
	vector<int> gao(const string &s) {
		string pal = insert(s);
		int len = pal.length();
		vector<int> ret(len);
		for (int i = 1, c = 0, r = 0; i < len - 1; ++i) {
			int &qaq = ret[i];
			if (i <= r)
				qaq = min(length(i, r), (ll)ret[i - (i - c) * 2]);
			while (pal[i - qaq - 1] == pal[i + qaq + 1])
				++qaq;
			if (r < ltor(i, qaq))
				r = ltor(c = i, qaq);
		}
		return ret;
	}
};

