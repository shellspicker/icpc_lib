/*
 * calc expression for basic arithmetic.
 * judge and deal illegal situation.
 * not use stringstream(it may be slow).
 * skip space use `isblank`, not `isspace`, so just read one-line.
 * if read multi-line expression... use `isspace`, good luck.
 */
template<typename tp>
class expression {
public:
	tp parse_calc(const string &exp) {
		stack<char> cop;
		stack<tp> nop;
		int cur = 0, len = exp.length(), minus = 1;
		char ch;
		bool flag = 1; // 0: accept numer. 1: accept operator.
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
			nop.push(ret);
		};
		auto can_push = [](char lef, char rig) {
			bool ok;
			string plus("+-"), multiply("*/%^");
			ok = rig != ')' && (lef == '(' || rig == '('
				|| (plus.find(lef) != string::npos && multiply.find(rig) != string::npos));
			return ok;
		};
		while (cur < len) {
			while (isblank(ch = exp[cur]))
				cur++;
			if (isdigit(ch)) {
				size_t ed = exp.find_first_not_of("0123456789", cur);
				if (ed == string::npos)
					ed = len;
				if (sizeof(tp) - 4)
					nop.push(stoll(exp.substr(cur, ed - cur)) * minus);
				else
					nop.push(stoi(exp.substr(cur, ed - cur)) * minus);
				flag = 0;
				minus = 1;
				cur = ed;
			} else {
				if (flag && ch == '-') {
					minus *= -1;
					goto end;
				}
				if (ch == ')') {
					flag = 0;
					minus = 1;
					while (!cop.empty() && cop.top() != '(')
						calc(cop, nop);
					if (cop.empty())
						goto end;
					cop.pop();
				} else {
					flag = 1;
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
};

