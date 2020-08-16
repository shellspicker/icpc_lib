#define FAST_IO 1

#include "template.h"
#include "string/hash.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	char buf[1000233];
	const ull seed = 3137;
	string json;
	int qn, cur;
	vector<ull> qs;
	vector<pair<int, int>> ans;
	map<ull, pair<int, int>> dict;
	void preprocess() {
		fio.set_output_float_digit(12);
		fio.set_g_buf(buf);
	}
	istream &in() {
		fio.in(json);
		fio.in(qn);
		qs.resize(qn);
		fup_range (i, 0, qn) {
			string tmp;
			fio.in(tmp);
			qs[i] = bkdr_hash_once(tmp, seed);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		cur = 0;
		dict.clear();
		parse_json(0);
		ans.resize(qn);
		fup_range (i, 0, qn) {
			ans[i] = get_ans(qs[i]);
		}
	}
	void out() {
		fup_range (i, 0, qn) {
			auto ac = ans[i];
			if (ac.first == -1 || ac.second == -1) {
				fio.msg("Error!\n");
			} else {
				fio.msg("%s\n",
				json.substr(ac.first, length(ac.first, ac.second)).data());
			}
		}
	}
	pair<int, int> parse_json(ull pre) {
		pair<int, int> ret;
		ret.first = cur++;
		if (json[cur] == '}') {
			ret.second = cur++;
			return ret;
		}
		parse_kv(pre);
		while (cur < json.size() && json[cur] == ',') {
			cur++;
			parse_kv(pre);
		}
		ret.second = cur++;
		return ret;
	}
	void parse_kv(ull pre) {
		ull key;
		pair<int, int> val;
		key = parse_key(pre);
		cur++;
		val = parse_val(key);
		dict[key] = val;
	}
	ull parse_key(ull pre) {
		ull ret = pre;
		int p1, p2;
		p1 = cur++;
		p2 = json.find('"', cur);
		fup (i, p1, p2)
			ret = ret * seed + json[i];
		cur = p2 + 1;
		return ret;
	}
	pair<int, int> parse_val(ull pre) {
		pair<int, int> ret;
		if (json[cur] == '{')
			return parse_json(pre * seed + '.');
		ret.first = cur++;
		ret.second = json.find('"', cur);
		cur = ret.second + 1;
		return ret;
	}
	pair<int, int> get_ans(ull hs) {
		if (dict.count(hs))
			return dict[hs];
		return {-1, -1};
	}
public:
	task(
		bool multicase = 0,
		const char *fmt_case = 0,
		bool blankline = 0) {
		static int testcase = 1 << 30;
		static stringstream tid;
		preprocess();
		if (multicase)
			fio.in(testcase);
		for (int ti = 1; ti <= testcase && in(); ++ti) {
			deal();
			if (blankline && 1 < ti)
				fio.out('\n');
			if (fmt_case)
				fio.msg(fmt_case, ti);
			out();
		}
	}
#undef ioend
} gkd(1);

int main()
{
	return 0;
}
