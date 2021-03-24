#include<bits/stdc++.h>

using namespace std;


// Initialise all the vectors accordingly
vector<int> intime;
vector<int> outtime;
vector<vector<int>> up;
vector<vector<int>> adj;

int l; // Initialise l with ceil(log(n)) where n is the number of vertices

void dfs(int s, int p){
	Time++;
	intime[s] = Time;
	up[s][0] = p;
	for(int i = 1; i <= l; i++){
		up[s][i] = up[up[s][i - 1]][i - 1];
	}
	for(int u: adj[s]){
		if(u != p){
			dfs(u, s);
		}
	}
	Time++;
	outtime[s] = Time;
}
bool is_ancestor(int u, int v){
	return intime[u] <= intime[v] and outtime[u] >= outtime[v];
}
int lca(int u, int v){
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