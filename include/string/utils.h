#pragma once

vector<int> naive_search(string &big, string &small) {
	vector<int> ret;
	int pre = 0;
	fup_range (cur, 0, big.length()) {
		if (big[cur] != small[pre])
			cur -= pre, pre = -1;
		if (++pre == small.length())
			ret.push_back(rtol(cur, small.length()));
	}
	return ret;
}
vector<string> get_token(const string &text, const string &delim)
{
	vector<string> ret;
	char *scp = strdup(text.data()), *cur = scp, *token;
	for (; token = strtok(cur, delim.data()); cur = NULL)
		ret.push_back(string(token));
	free(scp);
	return ret;
}
