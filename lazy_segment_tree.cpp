#include<bits/stdc++.h>

using namespace std;


template<class T> class Lazy_Segment_Tree {
public:
	int n;
	vector<T> t;
	vector<T> a;
	vector<T> lazy;
	T invalid;
	void push(int v, int tl, int tr, int tmid) {
		/*
			This function propagates the lazy value to
			the children nodes of node v. Change it according
			to operation. Currently, this push function
			adds a value to a given range. Don't forget to change
			the combine operations in query and update functions.
		*/
		if(lazy[v] != 0) {
			t[v] += (tr - tl + 1)*lazy[v];
			if(tl != tr) {
				lazy[2*v + 1] += lazy[v];
				lazy[2*v + 2] += lazy[v];
			}
			lazy[v] = 0;
		}
	}
	void build(int v, int l, int r){
		if(l == r){
			t[v] = a[l];
			return;
		}
		int mid = l + (r - l)/2;
		build(2*v + 1, l, mid);
		build(2*v + 2, mid + 1, r);
		t[v] = t[2*v + 1] + t[2*v + 2];
	}
	T sum(int l, int r, int v, int tl, int tr){
		if(l > r) return invalid;
		int tmid = tl + (tr - tl)/2;
		push(v, tl, tr, tmid);
		if(l == tl and r == tr) return t[v];
		return sum(l, min(r, tmid), 2*v + 1, tl, tmid) + sum(max(l, tmid + 1), r, 2*v + 2, tmid + 1, tr);
	}
	void update(int l, int r, T val, int v, int tl, int tr){
		int tmid = tl + (tr - tl)/2;
		push(v, tl, tr, tmid);
		if(l > r) {
			return;
		}
		if(l == tl and r == tr) {
			lazy[v] += val;
			push(v, tl, tr, tmid);
		}
		else{
			update(l, min(r, tmid), val, 2*v + 1, tl, tmid);
			update(max(l, tmid + 1), r, val, 2*v + 2, tmid + 1, tr);
			t[v] = t[2*v + 1] + t[2*v + 2];
		}
	}
	Lazy_Segment_Tree(int si, T inv){
		n = si;
		t.resize(4*si);
		lazy.resize(4*si);
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
	int n, q; cin >> n >> q;
	vector<long long> a(n);
	Lazy_Segment_Tree<long long> stree(n, 0);
	for(int i = 0; i < n; i++) {
		a[i] = rand() % 10;
		stree.a[i] = a[i];
	}
	// st.build() -> build the semgment t after filling up the array st.a
	// st.sum(l, r) -> return sum of segment from l to r (both inclusive; 0 indexed)
	// st.update(l, r, val) -> update value from positions l to r (0 indexed) to val

	
}