#include <iostream>
using namespace std;

int N, M, q;
int c, a, b, k;
int arr[3000][3000];
int idx[3000];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> q;
	for (int i = 0; i < N; i++) {
		idx[i] = i;
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < q; i++) {
		cin >> c;
		if (c == 0) {
			cin >> a >> b >> k;
			arr[idx[a]][b] = k;
		}
		else {
			cin >> a >> b;
			swap(idx[a], idx[b]);
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << arr[idx[i]][j] << " ";
		}
		cout << "\n";
	}
}