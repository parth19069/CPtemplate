#include<bits/stdc++.h>
using namespace std;


// change __gcd funtion to min or max


template<class T> class SparseTable {
public:
	const int LOGN = 25;
	int n;
	vector<vector<T>> sparse;
	vector<int> logs;
	vector<T> a;
 
	SparseTable(int num) {
		n = num;
		sparse.assign(n, vector<T>(LOGN + 1));
		a.resize(n);
		logs.resize(n + 1);
	}
 
	void build() {
		logs[1] = 0;
		for(int i = 2; i <= n; i++) {
			logs[i] = logs[i/2] + 1;
		}
		for(int i = 0; i < n; i++) {
			sparse[i][0] = a[i];
		}
		for(int j = 1; j <= LOGN; j++) {
			for(int i = 0; i + (1 << j) - 1 < n; i++) {
				sparse[i][j] = __gcd(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
 
	T query(int l, int r) {
		int j = logs[r - l + 1];
		return __gcd(sparse[l][j], sparse[r - (1 << j) + 1][j]);
	}
};

int main() {
	int n; cin >> n;
	vector<int> a(n);
	SparseTable<int> st(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		st.a[i] = a[i];
	}
	st.build();
	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++) {
			cout << i << ", " << j << " = " << st.query(i, j) << endl;
		}
	}
}