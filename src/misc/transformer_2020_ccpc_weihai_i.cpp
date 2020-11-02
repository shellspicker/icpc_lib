#define FAST_IO 1
#include <unistd.h>
#include "template.h"
#include "data_structure/allocator.h"
#include "math/gcd_lcm.h"
#include "string/utils.h"
#include "string/hash.h"
#include "string/hashtable.h"
#include "misc/transformer.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	vector<string> vs;
	using pm = permutation<24>;
	using vpm = vector<pm>;
	pm origin;
	vpm ys, face, body, body_comb, face_comb, all;
	unordered_map<ull, pair<int, int>> mmp;
	string clo = "YYYYOOOOBBBBRRRRGGGGWWWW";
	int ans;
	void preprocess() {
		fio.set_output_float_digit(12);
		pm::init();
		cube<pm>::init();
		ys.resize(1);
		face.resize(1);
		body.resize(2);
		ys[0].assign({0,1,2,3,4,5,8,9,12,13,16,17,6,7,10,11,14,15,18,19,20,21,22,23});
		face[0].assign({2,3,12,14,21,20,7,5,8,9,10,11}, {7,5,2,3,12,14,21,20,10,8,11,9});
		body[0].assign(
				{4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,1,2,3,20,21,22,23},
				{8,9,10,11,12,13,14,15,16,17,18,19,4,5,6,7,2,0,3,1,21,23,20,22});
		body[1].assign(
				{0,1,2,3,8,9,10,11,20,21,22,23,19,18,17,16,4,5,6,7,12,13,14,15},
				{8,9,10,11,20,21,22,23,19,18,17,16,0,1,2,3,5,7,4,6,14,12,15,13});
		level_bfs(body_comb, body, 233);
		cube<pm>::face_seq(face_comb, body_comb, face);
		level_bfs(all, face_comb, 233);
	}
	istream &in() {
		vs.clear();
		string line;
		fup_range (i, 0, 6) {
			fio.readline_noblank(line);
			vs.push_back(line);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		vector<string> sp = get_str(vs);
		ans = getans(sp);
	}
	void out() {
		fio.msg("%d\n", ans);
	}
	vector<string> get_str(vector<string> &vs) {
		auto split = [&](vector<string> &vs) {
			vector<string> ret;
			ret.resize(2);
			for (auto &s : vs) {
				vector<string> tok = get_token(s, " |");
				fup_range (g, 0, 2) {
					ret[g] += tok[g];
				}
			}
			return ret;
		};
		auto in2std = [&](const string &s) {
			string ret(s);
			vector<int> reid(ys[0].mat, ys[0].mat + 24);
			fup_range (i, 0, s.size()) {
				ret[reid[i]] = s[i];
			}
			return ret;
		};
		vector<string> ret = split(vs);
		fup_range (i, 0, ret.size())
			ret[i] = in2std(ret[i]);
		return ret;
	}
	int getans(vector<string> &vs) {
		pair<int, int> match[2];
		fup_range (i, 0, vs.size()) {
			string &s = vs[i];
			ull hs;
			for (auto &x : body_comb) {
				ull hs = perm2hash(x, s);
				if (mmp.count(hs)) {
					match[i] = mmp[hs];
					break;
				}
			}
		}
		pm tar[2];
		fup_range (i, 0, 2)
			tar[i] = all[match[i].second];
		tar[1].compos(tar[0], 1);
		int ret = mmp[perm2hash(tar[1], clo)].first;
		return ret;
	}
	string perm2str(pm &x, string &std) {
		string ret;
		ret.resize(24);
		fup_range (i, 0, std.size())
			ret[x.mat[i]] = std[i];
		return ret;
	}
	ull perm2hash(pm &x, string &std) {
		return hash_val(perm2str(x, std));
	}
	void level_bfs(vpm &comb, vpm &misc, int limit) {
		int tail = 0;
		auto expand = [&](int lev) {
			int cc = comb.size() - tail;
			while (cc--) {
				pm x = comb[tail++];
				for (auto &y : misc) {
					x.compos(y, 0);
					ull hs = perm2hash(x, clo);
					if (!mmp.count(hs)) {
						comb.push_back(x);
						mmp[hs] = {lev, comb.size() - 1};
					}
					x.compos(y, 1);
				}
			}
		};
		comb.push_back(origin);
		mmp[perm2hash(origin, clo)] = {0, comb.size() - 1};
		for (int lev = 1; lev < limit; ++lev) {
			if (!(comb.size() - tail))
				break;
			expand(lev);
		}
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
};

int main()
{
	new task(1);
	return 0;
}
