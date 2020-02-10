#ifndef EXPRESSION_H
#define EXPRESSION_H 1

/*
 * calc expression for basic arithmetic.
 * judge and deal illegal situation.
 * not use stringstream(it may be slow).
 * skip space use `isblank`, not `isspace`, so just read one-line.
 * if read multi-line expression... use `isspace`, good luck.
 */
template<typename tp>
class expression {
	tp mod = 0;
public:
	void set_mod(int m) {
		mod = m;
	}
	tp parse_calc(const string &exp) {
		stack<char> cop;
		stack<tp> nop;
		int cur = 0, len = exp.length(), minus = 1;
		char ch;
		bool flag = 0;
		auto push_num = [&](stack<tp> &nop, tp x) {
			nop.push(x);
			flag = 1;
		};
		auto calc = [&](stack<char> &cop, stack<tp> &nop) {
			tp ret, e1, e2;
			char op;
			bool ok = 1 <= cop.size() && 2 <= nop.size();
			if (!ok)
				return;
			op = cop.top(); cop.pop();
			e2 = nop.top(); nop.pop();
			e1 = nop.top(); nop.pop();
			switch (op) {
				case '+':
					ret = e1 + e2;
					break;
				case '-':
					ret = e1 - e2;
					break;
				case '*':
					ret = e1 * e2;
					break;
				case '/':
					ret = e1 / e2;
					break;
				case '%':
					ret = e1 % e2;
					break;
				case '^':
					ret = pow(e1, e2);
					break;
				default:
					ok = 0;
					break;
			}
			if (mod) {
				if (ret < 0)
					ret += mod;
				if (mod < ret)
					ret %= mod;
			}
			if (ok)
				push_num(nop, ret);
		};
		auto can_push = [](char lef, char rig) {
			bool ok;
			string plus("+-"), multiply("*/%^");
			ok = rig != ')' && (lef == '(' || rig == '('
				|| (plus.find(lef) != -1ull && multiply.find(rig) != -1ull));
			return ok;
		};
		while (cur < len) {
			while (isblank(ch = exp[cur]))
				cur++;
			if (isdigit(ch)) {
				size_t ed = exp.find_first_not_of("0123456789", cur);
				if (ed == -1ull)
					ed = len;
				if (sizeof(tp) - 4)
					push_num(nop, stoll(exp.substr(cur, ed - cur)) * minus);
				else
					push_num(nop, stoi(exp.substr(cur, ed - cur)) * minus);
				minus = 1;
				cur = ed;
			} else {
				if (ch == '-' && !flag) {
					flag = 0;
					minus *= -1;
					goto end;
				}
				if (ch == ')') {
					while (!cop.empty() && cop.top() != '(')
						calc(cop, nop);
					if (cop.empty())
						goto end;
					cop.pop();
				} else {
					if (ch != '(')
						while (!cop.empty() && !can_push(cop.top(), ch))
							calc(cop, nop);
					cop.push(ch);
				}
end:
				cur++;
			}
		}
		while (!cop.empty()) {
			if (cop.top() == '(')
				cop.pop();
			else
				calc(cop, nop);
		}
		assert(nop.size() == 1);
		return nop.top();
	}
	tp va_exp(const char *fmt, ...) {
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsprintf(buf, fmt, args);
		va_end(args);
		return parse_calc(buf);
	}
};

#endif
