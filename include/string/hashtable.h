#ifndef HASHTABLE_H
#define HASHTABLE_H 1

template<typename ktp, typename htp, size_t pon, size_t mod>
class hash_set {
	class node {
	public:
		ktp key;
		node *nxt;
		void extend(node *&h, ktp k) {
			nxt = h;
			h = this;
			key = k;
		}
	};
	allocator<node, pon> alloc;
#if USE_TICKS
	uint ticks;
#endif
	node *head[mod];
#if USE_TICKS
	uint timestamp[mod];
#endif
	function<htp(ktp)> func_hash;
public:
	hash_set(function<htp(ktp)> f) {
		func_hash = f;
#if USE_TICKS
		ticks = 0;
#endif
	}
	void clear() {
		alloc.clear();
#if USE_TICKS
		ticks++;
#endif
		memset(&head[0], 0, mod * 8);
	}
	node *insert(ktp k) {
		htp h = func_hash(k) % mod;
#if USE_TICKS
		if (timestamp[h] != ticks)
			head[h] = 0;
		timestamp[h] = ticks;
#endif
		node *now;
		for (now = head[h]; now && (now->key != k); now = now->nxt);
		if (!now) {
			now = alloc();
			now->extend(head[h], k);
		}
		return now;
	}
	node *search(ktp k) {
		htp h = func_hash(k) % mod;
#if USE_TICKS
		if (timestamp[h] != ticks)
			head[h] = 0;
		timestamp[h] = ticks;
#endif
		node *now;
		for (now = head[h]; now && (now->key != k); now = now->nxt);
		return now;
	}
};

template<typename ktp, typename vtp, typename htp, size_t pon, size_t mod>
class hash_map {
	class node {
	public:
		ktp key;
		vtp val;
		node *nxt;
		void extend(node *&h, ktp k, vtp v) {
			nxt = h;
			h = this;
			key = k;
			val = v;
		}
	};
	allocator<node, pon> alloc;
#if USE_TICKS
	uint ticks;
#endif
	node *head[mod];
#if USE_TICKS
	uint timestamp[mod];
#endif
	function<htp(ktp)> func_hash;
public:
	hash_map(function<htp(ktp)> f) {
		func_hash = f;
#if USE_TICKS
		ticks = 0;
#endif
	}
	void clear() {
		alloc.clear();
#if USE_TICKS
		ticks++;
#endif
		memset(&head[0], 0, mod * 8);
	}
	node *insert(ktp k, vtp v) {
		htp h = func_hash(k) % mod;
#if USE_TICKS
		if (timestamp[h] != ticks)
			head[h] = 0;
		timestamp[h] = ticks;
#endif
		node *now;
		for (now = head[h]; now && (now->key != k); now = now->nxt);
		if (!now) {
			now = alloc();
			now->extend(head[h], k, v);
		}
		return now;
	}
	node *search(ktp k) {
		htp h = func_hash(k) % mod;
#if USE_TICKS
		if (timestamp[h] != ticks)
			head[h] = 0;
		timestamp[h] = ticks;
#endif
		node *now;
		for (now = head[h]; now && (now->key != k); now = now->nxt);
		return now;
	}
};

#undef USE_TICKS

#endif
