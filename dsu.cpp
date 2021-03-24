#include<bits/stdc++.h>

using namespace std;

struct DSU {

	// With both path compression and union by size

	vector<int> parent;
	vector<int> size;

	DSU(int n){
		parent.assign(n + 1, -1);
		size.assign(n + 1, -1);
	}

	void make_set(int u){
		parent[u] = u;
		size[u] = 1;
	}

	int find_set(int u){
		if(parent[u] == u){
			return u;
		}
		return parent[u] = find_set(parent[u]);
	}

	void union_sets(int u, int v){
		int leader_u = find_set(u);
		int leader_v = find_set(v);

		if(leader_u != leader_v){
			if(size[leader_u] < size[leader_v]){
				swap(leader_u, leader_v);
			}
			parent[leader_v] = leader_u;
			size[leader_u] += size[leader_v];
		}
	}
};



struct DSU_LIST{

	// No path compression but union by size

	vector<vector<int>> sets;
	vector<int> leader;

	DSU_LIST(int n){
		leader.assign(n + 1, -1);
	}

	int size(int u){
		return (int)sets[u].size();
	}

	void make_set(int u){
		if(leader[u] == -1){
			leader[u] = (int)sets.size();
			sets.push_back(vector<int>{u});
		}
	}

	int find_set(int u){
		if(leader[u] == -1){
			make_set(u);
		}
		return leader[u];
	}

	void union_sets(int u, int v){
		int leader_u = find_set(u);
		int leader_v = find_set(v);

		if(leader_u != leader_v){
			if(size(leader_u) < size(leader_v)){
				swap(leader_u, leader_v);
			}
			for(int element: sets[leader_v]){
				leader[element] = leader_u;
				sets[leader_u].push_back(element);
			}
			sets[leader_v].resize(0);
		}
	}

};

int main() {
	// Note that both dsu classes are 1 indexed
}