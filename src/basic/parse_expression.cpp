#include <bits/stdc++.h>
using namespace std;

class parse {
public:
	int cur;
	string text, table = "0123456789";

	int get_int() {
		int st, ed;
		st = cur;
		ed = text.find_first_not_of(table, cur);
		if (ed == -1)
			ed = text.size();
		cur = ed;
		return stoul(text.substr(st, ed - st));
	}
	int val() {
		int v1, v2;
		char op;
		v1 = term();
		while (cur < text.size() && (text[cur] == '+' || text[cur] == '-')) {
			op = text[cur++];
			v2 = term();
			switch (op) {
			case '+':
				v1 = v1 + v2;
				break;
			case '-':
				v1 = v1 - v2;
				break;
			default:
				break;
			}
		}
		return v1;
	}
	int term() {
		int v1, v2;
		char op;
		v1 = factor();
		while (cur < text.size() && (text[cur] == '*' || text[cur] == '/')) {
			op = text[cur++];
			v2 = factor();
			switch (op) {
			case '*':
				v1 = v1 * v2;
				break;
			case '/':
				v1 = v1 / v2;
				break;
			default:
				break;
			}
		}
		return v1;
	}
	int factor() {
		if (cur < text.size()) {
			char first = text[cur];
			if (isdigit(first)) {
				return get_int();
			} else if (first == '(') {
				int ret;
				cur++;
				ret = val();
				assert(text[cur++] == ')');
				return ret;
			}
		}
		assert(0);
		return -1;
	}
};

int main()
{
	parse ac;
	while (cin >> ac.text) {
		ac.cur = 0;
		cout << ac.val() << endl;
	}
	return 0;
}
