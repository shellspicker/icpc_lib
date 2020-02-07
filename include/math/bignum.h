/*
 * 大整数模板
 * 含有进制, 默认10, 可以设置成2~62.
 * 有个静态字符表, 需要手动指定一下, 表示数字的字符集.
 * 输入输出是字符串直接处理, 没有考虑进制的问题.
 * 有处理前导0的操作, 可以手动调用, 其实加减乘除里面已经调用了.
 * 有ibase->obase的进制转换, 把ibase下的[0,ibase]全用obase表示直接hash即可.
 * 如果计算时间卡得很短, 乘法和除法, 可以加上多项式fft or fnt操作.
 *
 * 这里写了大数进制转换, 2019银川现场赛, 计蒜客上有题.
 */
struct bignum {
	typedef bignum cnm;
	static string table;
	int base = 10;
	vector<int> vd;
	bool sign = 0;// 符号位, 默认为正.
	bignum() { clear(); }
	bignum(const cnm &b) = default;
	bignum(cnm &&b) = default;
	void clear() {
		vd.clear();
		sign = 0;// 默认正数.
	}
	// 清除前导0.
	void zero_justify() {
		while (vd.size() > 1 && vd.back() == 0)
			vd.pop_back();// 缩减位.
	}
	void set_base(int bs) {
		base = bs;
		assert(2 <= base);
	}
	// 较小的数值(个位数), 或10进制以下的数字用, 一般配合进制转换.
	void operator ()(ll x) {
		clear();
		if (x == 0) {
			vd.assign(1, 0);
			return;
		}
		while (x) {
			lldiv_t res = lldiv(x, base);
			x = res.quot;
			vd.push_back(res.rem);
		}
	}
	void operator ()(const string &s) {
		int len = s.length(), st;
		clear();
		if (!isdigit(s[0])) {
			if (s[0] == '-')
				sign = 1;
		}
		st = s.find_first_not_of("0"); // 前导0.
		if (st == -1llu) {
			vd.assign(1, 0);
			return;
		}
		// 逆序扫描字符串, 从数的低位开始.
		fwn (i, st, len - 1)
			vd.push_back(table.find(s[i]));
		zero_justify();
	}
	bignum trans_base(int obase) {
		vector<bignum> xp(base + 1); //[0, ibase] -> obase.
		bignum ret;
		ret.set_base(obase);
		for (auto &x : xp)
			x.set_base(obase);
		xp[0](0);
		xp[1](1);
		ret = xp[0];
		if (vd.size() == 1 && vd[0] == 0)
			return ret;
		fup (i, 2, base)
			xp[i] = xp[i - 1] + xp[1];
		fwn (i, 0, vd.size() - 1)
			ret = ret * xp[base] + xp[vd[i]];
		return ret;
	}
	bool operator <(const cnm &b) const {
		if (sign ^ b.sign)
			return sign;
		if (vd.size() ^ b.vd.size())
			return (vd.size() < b.vd.size()) ^ sign;
		fwn (i, 0, vd.size() - 1)
			if (vd[i] ^ b.vd[i])
				return (vd[i] < b.vd[i]) ^ sign;
		return 0;
	}
	bool operator >(const cnm &b) const {
		if (sign ^ b.sign)
			return b.sign;
		if (vd.size() ^ b.vd.size())
			return (vd.size() > b.vd.size()) ^ sign;
		fwn (i, 0, vd.size() - 1)
			if (vd[i] ^ b.vd[i])
				return (vd[i] > b.vd[i]) ^ sign;
		return 0;
	}
	bool operator ==(const cnm &b) const {
		if (sign ^ b.sign)
			return 0;
		if (vd.size() ^ b.vd.size())
			return 0;
		fwn (i, 0, vd.size() - 1)
			if (vd[i] ^ b.vd[i])
				return 0;
		return 1;
	}
	cnm operator <<(int d) const {
		cnm b = *this;
		if (vd.size() == 1 && vd[0] == 0)
			return *this;
		int sz = vd.size();
		b.vd.resize(vd.size() + d);
		fwn (i, 0, sz - 1)
			b.vd[i + d] = b.vd[i];
		fup (i, 0, d - 1)
			b.vd[i] = 0;
		return b;
	}
	cnm operator =(const cnm &b) {
		vd = b.vd;
		sign = b.sign;
		base = b.base;
		return *this;
	}
	cnm operator +(const cnm &b) const {
		cnm c;
		c.set_base(base);
		if (sign ^ b.sign) {
			if (sign) {
				c = *this;
				c.sign = 0;
				return c - b;
			} else {
				c = b;
				c.sign = 0;
				return *this - c;
			}
		}
		if (vd.size() < b.vd.size()) {
			c = b;
			return c + (*this);
		}
		int carry = 0;
		c.sign = sign;
		c.vd.assign(vd.size(), 0);
		fup (i, 0, b.vd.size() - 1) {
			int add = vd[i] + b.vd[i] + carry;
			c.vd[i] = add % base;
			carry = add / base;
		}
		fup (i, b.vd.size(), vd.size() - 1) {
			int add = vd[i] + carry;
			c.vd[i] = add % base;
			carry = add / base;
		}
		if (carry)
			c.vd.push_back(carry);
		c.zero_justify();
		return c;
	}
	cnm operator -(const cnm &b) const {
		// 有任何一个负数, 转化为a + (-b).
		/*
		 * (a - b)中a < 0 or b < 0, 变成a + (-b).
		 * a < 0, b > 0的情况相当于负的加法.
		 * a > 0, b < 0的情况相当于正数加法.
		 * a < 0, b < 0的情况相当于异号加法, 然后再化为异号减法, 转化为上面2种.
		 */
		cnm c;
		c.set_base(base);
		if (sign ^ b.sign) {
			c = *this;
			c = c + b;
			c.sign ^= 1;
			return c;
		}
		if (*this < b) {
			c = b;
			c = c - (*this);
			c.sign = 1;
			return c;
		}
		int borrow = 0, sub;
		c.vd.resize(vd.size());
		fup (i, 0, b.vd.size() - 1) {
			sub = vd[i] - b.vd[i] - borrow;
			borrow = sub < 0;
			c.vd[i] = (sub + base) % base;
		}
		fup (i, b.vd.size(), vd.size() - 1) {
			sub = vd[i] - borrow;
			borrow = sub < 0;
			c.vd[i] = (sub + base) % base;
		}
		c.zero_justify();
		return c;
	}
	cnm operator *(const cnm &b) const {
		cnm c, row = *this, tmp;
		c.set_base(base);
		tmp.set_base(base);
		c(0);
		fup (i, 0, b.vd.size() - 1) {
			int carry = 0, mul;
			tmp.vd.assign(row.vd.size(), 0);
			fup (j, 0, row.vd.size() - 1) {
				mul = row.vd[j] * b.vd[i] + carry;
				tmp.vd[j] = mul % base;
				carry = mul / base;
			}
			if (carry)
				tmp.vd.push_back(carry);
			c = c + tmp;
			row = row << 1;
		}
		c.sign = sign ^ b.sign;
		c.zero_justify();
		return c;
	}
	cnm operator /(const cnm &b) const {
		cnm c, row, tb = b;
		c.set_base(base);
		row.set_base(base);
		row(0);
		c.sign = sign ^ b.sign;
		tb.sign = 0;
		c.vd.assign(vd.size(), 0);
		fwn (i, 0, vd.size() - 1) {
			row = row << 1;
			row.vd[0] = vd[i];
			while (!(row < tb)) {
				c.vd[i]++;
				row = row - tb;
			}
		}
		c.zero_justify();
		return c;
	}
	cnm operator ^(int n) const {
		cnm c, xp = *this;
		c.set_base(base);
		c(1);
		while (n) {
			if (n & 1)
				c = c * xp;
			xp = xp * xp;
			n >>= 1;
		}
		return c;
	}
	cnm operator %(const cnm &b) const {
		cnm c;
		c.set_base(base);
		if (*this < b)
			return *this;
		if (*this == b)
			return c;
		c = (*this) - (*this) / b * b;
		return c;
	}
	foutput(os, cnm, o) {
		if (o.sign)
			os << "-";
		fwn (i, 0, o.vd.size() - 1)
			os << table[o.vd[i]];
		return os;
	}
};
string bignum::table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
