/*
	This file contains code of heavy-light decomposition.
	It also contains code for LCA. Calling init function also
	computes up array which can answer LCA queries in O(log n).
	A query function is also included which finds maximum weight
	edge on path from a to b. You will also need to use some DS like
	segment tree or sparse tables to answer queries.
*/

#include "bits/stdc++.h"
using namespace std;


vector<int> intime;
vector<int> outtime;
vector<vector<int>> up;
int Time = -1;

const int l = 20; // Initialise l with ceil(log(n)) where n is the number of vertices

void dfs_lca(int s, int p, vector<vector<int>> const& adj){
	Time++;
	intime[s] = Time;
	up[s][0] = p;
	for(int i = 1; i <= l; i++){
		up[s][i] = up[up[s][i - 1]][i - 1];
	}
	for(int u: adj[s]){
		if(u != p){
			dfs_lca(u, s, adj);
		}
	}
	Time++;
	outtime[s] = Time;
}
inline bool is_ancestor(int u, int v){
	return intime[u] <= intime[v] and outtime[u] >= outtime[v];
}
inline int lca(int u, int v){
	if(is_ancestor(u, v)){
		return u;
	}
	if(is_ancestor(v, u)){
		return v;
	}
	for(int i = l; i >= 0; i--){
		if(!is_ancestor(up[u][i], v)){
			u = up[u][i];
		}
	}
	return up[u][0];
}

vector<int> parent, depth, heavy, head, pos;
int cur_pos;

int dfs(int v, vector<vector<int>> const& adj) {
	int size = 1;
	int max_c_size = 0;
	for (int c : adj[v]) {
		if (c != parent[v]) {
			parent[c] = v, depth[c] = depth[v] + 1;
			int c_size = dfs(c, adj);
			size += c_size;
			if (c_size > max_c_size)
				max_c_size = c_size, heavy[v] = c;
		}
	}
	return size;
}

void decompose(int v, int h, vector<vector<int>> const& adj) {
	head[v] = h, pos[v] = cur_pos++;
	if (heavy[v] != -1)
		decompose(heavy[v], h, adj);
	for (int c : adj[v]) {
		if (c != parent[v] && c != heavy[v])
			decompose(c, c, adj);
	}
}

void init(vector<vector<int>> const& adj) {
	int n = adj.size();
	parent = vector<int>(n);
	depth = vector<int>(n);
	heavy = vector<int>(n, -1);
	head = vector<int>(n);
	pos = vector<int>(n);
	cur_pos = 0;

	dfs(0, adj);
	decompose(0, 0, adj);

	intime = vector<int>(n);
	outtime = vector<int>(n);
	up = vector<vector<int>>(n, vector<int>(l + 1));

	dfs_lca(0, 0, adj);
}
// int query(int a, int b, Segment_Tree<int> &stree) {
// 	int res = 0;
// 	if(depth[b] < depth[a]) {
// 		swap(a, b);
// 	}
// 	for(; head[a] != head[b]; b = parent[head[b]]) {
// 		res = max(res, stree.sum(pos[head[b]], pos[b]));
// 	}

// 	if(pos[a] != pos[b]) {
// 		res = max(res, stree.sum(pos[a] + 1, pos[b]));
// 	}

// 	return res;
// }
int main() {
	return 0;
}