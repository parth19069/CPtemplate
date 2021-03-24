#include<bits/stdc++.h>

using namespace std;

template <class T> class Segment_Tree{
public:
	int n;
	vector <T> t;
	vector <T> a;
	T invalid;
	T combine(T a, T b);
	void build(int v, int l, int r){
		if(l == r){
			t[v] = a[l];
			return;
		}
		int mid = l + (r - l)/2;
		build(2*v + 1, l, mid);
		build(2*v + 2, mid + 1, r);
		t[v] = combine(t[2*v + 1], t[2*v + 2]);
	}
	T sum(int l, int r, int v, int tl, int tr){
		if(l > r) return invalid;
		if(l == tl and r == tr) return t[v];
		int tmid = tl + (tr - tl)/2;
		return combine(sum(l, min(r, tmid), 2*v + 1, tl, tmid), sum(max(l, tmid + 1), r, 2*v + 2, tmid + 1, tr));
	}
	void update(int pos, T val, int v, int tl, int tr){
		if(tl == tr) {
			t[v] = val;
		}
		else{
			int tmid = tl + (tr - tl)/2;
			if(pos <= tmid) update(pos, val, 2*v + 1, tl, tmid);
			else update(pos, val, 2*v + 2, tmid + 1, tr);
			t[v] = combine(t[2*v + 1], t[2*v + 2]);
		}
	}
	Segment_Tree(int si, T inv){
		t.resize(4*si);
		a.resize(si);
		n = si;
		invalid = inv;
	}
	void build() {
		build(0, 0, n - 1);
	}
	T sum(int l, int r) {
		return sum(l, r, 0, 0, n - 1);
	}
	void update(int pos, T val) {
		update(pos, val, 0, 0, n - 1);
	}
};
template <class T> inline T Segment_Tree<T>::combine(T a, T b){
	return a + b;
}

int main() {
	int n; cin >> n;
	vector<int> a(n);
	Segment_Tree<int> stree(n, 0);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		stree.a[i] = a[i];
	}
	// stree.build() -> build the semgment tree after filling up the array stree.a
	// stree.sum(l, r) -> return sum of segment from l to r (both inclusive; 0 indexed)
	// stree.update(pos, val) -> update value at position pos (0 indexed) to val
}