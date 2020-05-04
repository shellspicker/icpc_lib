#ifndef AC_AM_H
#define AC_AM_H 1

#ifndef FIND_MODE
#define FIND_MODE LIST
#endif

#ifdef AM_COMPLETE
#define FIND_MODE TABLE
#endif

#define MAP 0
#define LIST 1
#define TABLE 2

/*
 * 字典树, 包含ac自动机功能.
 * 宏: FIND_MODE(MAP, LIST, TABLE), FUNC_AM, AM_COMPLETE.
 *
 * FUNC_AM.
 * ac自动机功能开启.
 *
 * FIND_MODE.
 * 设置查找方式, 结点结构.
 * 默认LIST.
 * 各个mode的适用场景.
 * MAP: 卡空间.
 * LIST: 卡时间, 空间.
 * TABLE: 时间空间充足, 或者是完全自动机做dp.
 *
 * AC_COMPLETE.
 * 完全自动机dp用, 绑定FIND_MODE = TABLE.
 * 其他mode下, 暂时不知道如何实现.
 * 不过如果dp题, 逻辑要写在这个class里面, 其他mode应该也能实现.
 */

#if FIND_MODE == TABLE
template<size_t pon, size_t sigma = 26, class func = function<int(char)>>
#else
template<size_t pon, size_t sigma = 26>
#endif
class ac_am {
#if FIND_MODE == TABLE
	static func ys;
#endif
	class node {
	public:
		static node *null;
#if FUNC_AM
		node *suf, *last;
#endif
#if FIND_MODE == MAP
		map<int, node *> nxt;
#endif
#if FIND_MODE == LIST
		int ch;
		node *dwn, *rig;
#endif
#if FIND_MODE == TABLE
		node *nxt[sigma];
#endif
		int id, cnt;
		node(char c = -1) {
#if FIND_MODE == MAP
			nxt.clear();
#endif
#if FIND_MODE == LIST
			ch = c;
			dwn = rig = null;
#endif
#if FIND_MODE == TABLE
			fill_n(nxt, sigma, null);
#endif
			id = 0;
			cnt = 0;
		}
#if FIND_MODE == TABLE
		node *&find(char ch) {
#else
		node *find(char ch) {
#endif
#if FIND_MODE == MAP
			if (!nxt.count(ch))
				return null;
			return nxt[ch];
#endif
#if FIND_MODE == LIST
			node *now;
			for (now = dwn; now != null && now->ch != ch; now = now->rig);
			return now;
#endif
#if FIND_MODE == TABLE
			return nxt[ys(ch)];
#endif
		}
#if FIND_MODE == LIST
		void extend(node *x) {
			x->rig = dwn;
			dwn = x;
		}
#endif
	};
	allocator<node, pon> alloc;
public:
	node *root, *&null = node::null;
	int id_cnt;
	bool is_find;
#if FIND_MODE == TABLE
	ac_am(func f) { ys = f; }
#endif
	void init() {
		alloc.clear();
		null = new (alloc()) node();
		root = new (alloc()) node();
#if FIND_MODE == LIST
		null->dwn = null;
#endif
#if FUNC_AM
		root->suf = root->last = null;
#endif
#if FUNC_AM && FIND_MODE == TABLE
		fup_range (ch, 0, sigma)
			null->nxt[ch] = root;
#endif
		id_cnt = 0;
	}
	void insert(const string &s) {
		int len = s.length();
		node *o = root;
		o->cnt++;
		fup_range (i, 0, len) {
			int nc = s[i];
#if FIND_MODE == TABLE
			node *&nxt = o->find(nc);
#else
			node *nxt = o->find(nc);
#endif
			if (nxt == null) {
				nxt = new (alloc()) node(nc);
#if FIND_MODE == MAP
				o->nxt[nc] = nxt;
#endif
#if FIND_MODE == LIST
				o->extend(nxt);
#endif
			}
			o = nxt;
			o->cnt++;
		}
		if (!o->id)
			o->id = ++id_cnt;
	}
	node *find(const string &s) {
		int len = s.length();
		node *o = root;
#if FUNC_AM
		is_find = 0;
		auto count = [&](node *o, int i) {
			for (; o != null; o = o->last) {
				is_find = 1;
			}
		};
#endif
		fup_range (i, 0, len) {
			int nc = s[i];
#if FUNC_AM
#if !AM_COMPLETE
			while (o != null && o->find(nc) == null)
				o = o->suf;
#endif
			o = o->find(nc);
#if FIND_MODE != TABLE
			if (o == null)
				o = root;
#endif
			if (o->id)
				count(o, i);
			else
				count(o->last, i);
#else
			if (o->find(nc) == null)
				return null;
			o = o->find(nc);
#endif
		}
		return o;
	}
#if FUNC_AM
	void build() {
		queue<node *> level;
		level.push(root);
		while (!level.empty()) {
			node *o = level.front();
			level.pop();
#if FIND_MODE == MAP
			for (auto it : o->nxt) {
				char ch = it.first;
				node *xyb = it.second;
#endif
#if FIND_MODE == LIST
			for (node *xyb = o->dwn; xyb != null; xyb = xyb->rig) {
				char ch = xyb->ch;
#endif
#if FIND_MODE == TABLE
			fup_range (ch, 0, sigma) {
				node *&xyb = o->nxt[ch];
				if (xyb == null) {
#if AM_COMPLETE
					xyb = o->suf->nxt[ch];
#endif
					continue;
				}
#endif
				level.push(xyb);
				node *uyb = o->suf;
#if FIND_MODE == TABLE
				while (uyb != null && uyb->nxt[ch] == null)
#else
				while (uyb != null && uyb->find(ch) == null)
#endif
					uyb = uyb->suf;
#if FIND_MODE == TABLE
				xyb->suf = uyb->nxt[ch];
#else
				uyb = uyb->find(ch);
				if (uyb == null)
					xyb->suf = root;
				else
					xyb->suf = uyb;
#endif
				xyb->last = xyb->suf->id ? xyb->suf : xyb->suf->last;
			}
		}
	}
#endif
};
#if FIND_MODE == TABLE
template<size_t pon, size_t sigma, class func>
typename ac_am<pon, sigma, func>::node *ac_am<pon, sigma, func>::node::null;
template<size_t pon, size_t sigma, class func>
func ac_am<pon, sigma, func>::ys;
#else
template<size_t pon, size_t sigma>
typename ac_am<pon, sigma>::node *ac_am<pon, sigma>::node::null;
#endif

#undef FIND_MODE
#undef MAP
#undef LIST
#undef TABLE
#undef FUNC_AM
#undef AM_COMPLETE

#endif
