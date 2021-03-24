#include<bits/stdc++.h>

using namespace std;

template<class T> class Lazy_Segment_Tree {
public:
	int n;
	vector<T> t;
	vector<T> a;
	vector<bool> marked;
	T invalid;
	void push(int v, int tl, int tr, int tmid) {
		if(marked[v]) {
			T val = t[v]/(tr - tl + 1);
			t[2*v + 1] = val*(tmid - tl + 1);
			t[2*v + 2] = val*(tr - tmid);
			marked[2*v + 1] = marked[2*v + 2] = true;
			marked[v] = false;
		}
	}
	void build(int vertex, int l, int r){
		if(l == r){
			t[vertex] = a[l];
			return;
		}
		int mid = l + (r - l)/2;
		build(2*vertex + 1, l, mid);
		build(2*vertex + 2, mid + 1, r);
		t[vertex] = t[2*vertex + 1] + t[2*vertex + 2];
	}
	T sum(int l, int r, int vertex, int tl, int tr){
		if(l > r) return invalid;
		if(l == tl and r == tr) return t[vertex];
		int tmid = tl + (tr - tl)/2;
		push(vertex, tl, tr, tmid);
		return sum(l, min(r, tmid), 2*vertex + 1, tl, tmid) + sum(max(l, tmid + 1), r, 2*vertex + 2, tmid + 1, tr);
	}
	void update(int l, int r, T val, int vertex, int tl, int tr){
		if(l > r) {
			return;
		}
		if(l == tl and r == tr) {
			t[vertex] = (r - l + 1)*val; 
			marked[vertex] = true;
		}
		else{
			int tmid = tl + (tr - tl)/2;
			push(vertex, tl, tr, tmid);
			update(l, min(r, tmid), val, 2*vertex + 1, tl, tmid);
			update(max(l, tmid + 1), r, val, 2*vertex + 2, tmid + 1, tr);
			t[vertex] = t[2*vertex + 1] + t[2*vertex + 2];
		}
	}
	Lazy_Segment_Tree(int si, T inv){
		n = si;
		t.resize(4*si);
		marked.resize(4*si);
		a.resize(si);
		invalid = inv;
	}
	void build() {
		build(0, 0, n - 1);
	}
	void update(int l, int r, T val) {
		update(l, r, val, 0, 0, n - 1);
	}
	T sum(int l, int r) {
		return sum(l, r, 0, 0, n - 1);
	}
};

int main() {
	int n; cin >> n;
	vector<int> a(n);
	Lazy_Segment_Tree<int> stree(n, 0);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		stree.a[i] = a[i];
	}
	// st.build() -> build the semgment t after filling up the array st.a
	// st.sum(l, r) -> return sum of segment from l to r (both inclusive; 0 indexed)
	// st.update(l, r, val) -> update value from positions l to r (0 indexed) to val
}