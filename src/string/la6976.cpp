#define FAST_IO 1

#include "template.h"
#include "string/hash.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	const ull seed = 3137;
	string json;
	int qn, cur;
	vector<ull> qs;
	vector<pair<int, int>> ans;
	map<ull, pair<int, int>> dict;
	void preprocess() {
		fio.set_output_float_digit(12);
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
		parse(0);
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
				fio.out(json.substr(ac.first, length(ac.first, ac.second)).data(), '\n');
				//fio.msg("%s\n",
				//json.substr(ac.first, length(ac.first, ac.second)).c_str());
			}
		}
	}
	void parse(ull pre_key) {
		cur++;
		while (cur < (int)json.length() && json[cur] != '}') {
			int rig = json.find_first_of(":}", cur);
			if (json[rig] == '}') {
				cur = rig;
				return;
			}
			ull sub_key = pre_key;
			fup (i, cur, rig - 1)
				sub_key = sub_key * seed + json[i];
			cur = ++rig;
			assert(inrange(rig, 0, json.size()));
			if (json[rig] == '{') {
				parse(sub_key * seed + '.');
			} else {
				cur = json.find('"', rig + 1);
				assert(inrange(cur, 0, json.length()));
			}
			dict[sub_key] = {rig, cur};
			assert(inrange(cur + 1, 0, json.size()));
			if (json[++cur] == ',')
				cur++;
		}
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
