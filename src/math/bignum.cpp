/*
 * 大整数模板
 * 构造函数必要参数: base, 表示进制.
 * 有个静态字符表, 需要手动指定一下, 表示数字的字符集.
 * 输入输出是字符串直接处理, 没有考虑进制的问题.
 * 有ibase->obase的进制转换, 把ibase下的[0,ibase]全用obase表示直接hash即可.
 * 如果计算时间卡得很短,
 * 那么需要10进制压位处理, 一般是4位(也就是10000进制), 现在暂时不考虑.
 * 有处理前导0的操作, 可以手动调用, 其实加减乘除里面已经调用了.
 *
 * 这里写了大数进制转换, 2019银川现场赛, 计蒜客上有题.
 */
#include <bits/stdc++.h>
using namespace std;
//这里是简单循环，特别的还是手写吧，或者有的循环用的全局变量也要手写
#define fup(i,a,b) for(long i=a; i<=b; ++i)
#define fwn(i,a,b) for(long i=b; i>=a; --i)
typedef long long ll;

struct bignum
{
	typedef bignum cnm;
	static string table;

	int base;
	vector<int> vd;
	bool sign;// 符号位.

	bignum() = delete;
	bignum(int bs) {
		base = bs;
		assert(2 <= base);
		clear();
	}
	bignum(const cnm &b) = default;
	bignum(cnm &&b) = default;
	// 较小的数值(个位数), 或10进制以下的数字用, 一般配合进制转换.
	bignum(ll x, int bs) {
		base = bs;
		assert(2 <= base);
		if (x == 0) {
			vd.assign(1, 0);
			sign = false;
			return;
		}
		while (x) {
			lldiv_t res = lldiv(x, base);
			x = res.quot;
			vd.push_back(res.rem);
		}
	}
	bignum(const string &s, int bs) {
		base = bs;
		assert(2 <= base);
		int len = s.length(), st, h = 0, xp = 1;// st是符号占位.
		clear();
		if (!isdigit(s[0])) {
			if (s[0] == '-')
				sign = true;
		}
		st = s.find_first_not_of("0");
		if (st == string::npos) {
			vd.assign(1, 0);
			return;
		}
		// 逆序扫描字符串, 从数的低位开始.
		fwn (i, st, len - 1) {
			vd.push_back(table.find(s[i]));
		}
		zero_justify();
	}
	void clear() {
		vd.clear();
		sign = false;// 默认正数.
	}
	// 清除前导0.
	void zero_justify() {
		while (vd.size() > 1 && vd.back() == 0)
			vd.pop_back();// 缩减位.
	}
	// 输出大数, 不带put10.
	void print() const {
		if (sign)
			cout << "-";
		fwn (i, 0, vd.size() - 1)
			cout << table[vd[i]];
	}
	bignum trans_base(int obase) {
		vector<bignum> xp(base + 1, bignum(obase));
		bignum ret(obase);
		new (&xp[0])bignum(0, obase);
		new (&xp[1])bignum(1, obase);
		ret = xp[0];
		if (vd.size() == 1 && vd[0] == 0)
			return ret;
		fup (i, 2, base) {
			xp[i] = xp[i - 1] + xp[1];
		}
		fwn (i, 0, vd.size() - 1) {
			ret = ret * xp[base] + xp[vd[i]];
		}
		return ret;
	}
	bool operator <(const cnm &b) const {
		if (sign != b.sign)
			return sign;
		if (vd.size() != b.vd.size())
			return (vd.size() < b.vd.size()) ^ sign;
		fwn (i, 0, vd.size() - 1) if (vd[i] != b.vd[i]) {
			return (vd[i] < b.vd[i]) ^ sign;
		}
		return 0;
	}
	bool operator >(const cnm &b) const {
		if (sign != b.sign)
			return b.sign;
		if (vd.size() != b.vd.size())
			return (vd.size() > b.vd.size()) ^ sign;
		fwn (i, 0, vd.size() - 1) if (vd[i] != b.vd[i]) {
			return (vd[i] > b.vd[i]) ^ sign;
		}
		return 0;
	}
	bool operator ==(const cnm &b) const {
		if (sign != b.sign)
			return false;
		if (vd.size() != b.vd.size())
			return false;
		fwn (i, 0, vd.size() - 1) if (vd[i] != b.vd[i]) {
			return false;
		}
		return true;
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
		return *this;
	}
	cnm operator +(const cnm &b) const {
		cnm c(base);
		if (sign ^ b.sign) {
			if (sign) {
				c = *this;
				c.sign = false;
				return c - b;
			} else {
				c = b;
				c.sign = false;
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
		cnm c(base);
		if (sign ^ b.sign) {
			c = *this;
			c = c + b;
			c.sign ^= 1;
			return c;
		}
		if (*this < b) {
			c = b;
			c = c - (*this);
			c.sign = true;
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
		cnm c(0, base), row = *this, tmp(base);
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
		cnm c(base), row(0), tb = b;
		c.sign = sign ^ b.sign;
		tb.sign = false;
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
		cnm c(1, base), xp = *this;
		while (n) {
			if (n & 1)
				c = c * xp;
			xp = xp * xp;
			n >>= 1;
		}
		return c;
	}
	cnm operator %(const cnm &b) const {
		cnm c(base);
		if (*this < b)
			return *this;
		if (*this == b)
			return c;
		c = (*this) - (*this) / b * b;
		return c;
	}
};
string bignum::table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main()
{
	int x, y;
	string x_str;
	cin >> x >> y >> x_str;
	bignum a(x_str, x);
	auto b = a.trans_base(y);
	b.print(); cout << '\n';
	return 0;
}
