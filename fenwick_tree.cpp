#include<bits/stdc++.h>

using namespace std;

template <class T> class FenwickTree {
public:
	vector<T> BIT;
	int n;

	FenwickTree(int n) {
		this->n = n + 1;
		BIT.resize(n + 1);
	}

	void update(int idx, T delta) {
		for(idx++; idx < n; idx += idx & -idx){
			BIT[idx] += delta;
		}
	}

	FenwickTree(vector<T> a) {
		this->n = (int)a.size() + 1;
		BIT.resize(n + 1);
		for(int i = 0; i < n; i++){
			update(i, a[i]);
		}
	}

	T sum(int idx) {
		// Prefix sum function
		T ret = 0;
		for(idx++; idx > 0; idx -= idx & -idx){
			ret += BIT[idx];
		}
		return ret;
	}

	T sum(int l, int r){
		// Range sum function
		return sum(r) - sum(l - 1);
	}
};

int main() {
	/*
		The tree is initially build with all 0s and needs to be updated.
		Also, note that update operations adds delta to an element.
	*/
}