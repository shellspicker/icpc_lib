#pragma once

#pragma message \
usage_begin("") \
line("idref.h") \
line("synopsis:") \
line("\tidref<tp>;") \
line("\t\ttp到int的映射, 类似离散化(但是没有排序).") \
line("\t\t下标起始0.") \
line("public function:") \
line("\tvoid init();") \
line("\tint size();") \
line("\tbool count(tp);") \
line("\tint get_id(tp);") \
line("\ttp get_orig(int);") \
usage_end()

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
