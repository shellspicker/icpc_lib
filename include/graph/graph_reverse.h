template<typename graph>
class graph_reverse {
	graph &g;
	using node = typename graph::node;
	using edge = typename graph::edge;
public:
	graph_reverse(graph &_1) : g(_1) {}
	graph get() {
		graph ret;
		node *v;
		edge *e;
		ret.resize(g.size());
		fup_range (u, 0, g.size()) {
			ret[u].meta = g[u].meta;
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				ret.add(v->id(), u);
				ret.edges.back().meta = e->meta;
			}
		}
		return ret;
	}
};

