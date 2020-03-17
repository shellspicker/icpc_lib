#include "template.h"
#include "string/hash.h"
#include "misc/transformer.h"

class data {
	ll n, p, mod, ans;
	vpm<30> face, buf;
	int mmp[35];
public:
	bool in() {
		cin >> n >> p;
		return !cin.eof();
	}
	void preprocess() {
		cube<30>::init();
		face.resize(3);
		face[0].assign(
			{9,10,11,12,13,14,15,16,17,0,1,2,3,4,5,6,7,8,20,19,18,29,28,27,26,25,24,23,22,21});
		face[1].assign(
			{2,5,8,1,4,7,0,3,6,15,12,9,16,13,10,17,14,11,21,22,23,24,25,26,27,28,29,18,19,20});
		face[2].assign(
			{9,10,11,3,4,5,6,7,8,0,1,2,12,13,14,15,16,17,20,19,18,29,22,23,24,25,26,27,28,21});
		cube<30>::level_bfs(face, 100233, buf);
		memset(mmp, 0, sizeof mmp);
		fup (ci, 0, buf.size() - 1) {
			auto xp = buf[ci];
			mmp[xp.cycn]++;
		}
	}
	void deal() {
		ans = 0;
		mod = p * buf.size();
		for (int x = 1; x <= 30; ++x) {
			ans = (ans + mmp[x] * pow_mod(n, x, mod) % mod) % mod;
		}
		ans /= buf.size();
	}
	void out() {
		cout << ans << '\n';
	}
} gkd;

class task {
	int testcase = 1 << 30;
	stringstream tid;
	data &gao = gkd;
public:
	task(
		bool multicase = false,
		bool testid = false,
		bool blankline = false) {
		ios::sync_with_stdio(0);
		cin.tie(0);
		cout.setf(ios::fixed);
		cout.precision(20);
		if (multicase)
			cin >> testcase;
		for (int ti = 1; ti <= testcase && gao.in(); ++ti) {
			gao.deal();
			if (blankline && 1 < ti)
				cout << endl;
			tid << "Case #" << ti << ": ";
			if (testid)
				cout << tid.str();
			gao.out();
			tid.str("");
		}
	}
};

__attribute__((optimize("-Ofast"))) int main()
{
	gkd.preprocess();
	task gao(1, 0, 0);
	return 0;
}
