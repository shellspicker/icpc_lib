template <typename tp>
class idref {
	int cnt;
	unordered_map<tp, int> mmp;
	unordered_map<int, tp> orig;
public:
	void init() {
		cnt = 0;
		mmp.clear();
		orig.clear();
	}
	int size() {
		return cnt;
	}
	bool count(tp o) {
		return mmp.count(o);
	}
	int get_id(tp o)
	{
		if (count(o))
			return mmp[o];
		int ret;
		mmp[o] = ret = cnt++;
		orig[ret] = o;
		return ret;
	}
	tp get_orig(int id) {
		assert(orig.count(id));
		return orig[id];
	}
};

