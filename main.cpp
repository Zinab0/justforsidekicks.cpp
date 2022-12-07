#include <bits/stdc++.h>

#define ll long long
using namespace std;
const int N = 5001;

int n, q;

vector<ll> tree[6];
vector<int> gems, types(6);

ll seg(int node, int node_low, int node_high, int query_low, int query_high, int i) {
    if (node_high <= query_high && node_low >= query_low) {
        return tree[i][node];
    }
    if (node_high < query_low || node_low > query_high) {
        return 0;
    }
    int mid = (node_low + node_high) / 2;
    return seg(2 * node, node_low, mid, query_low, query_high, i)
           + seg(2 * node + 1, mid + 1, node_high, query_low, query_high, i);

}

void update(int i, int val) {
    tree[gems[i]][i + n]--;
    for (int j = (i + n) / 2; j >= 1; j /= 2) {
        tree[gems[i]][j] = tree[gems[i]][j * 2] + tree[gems[i]][j * 2 + 1];
    }
    tree[val][i + n]++;
    for (int j = (i + n) / 2; j >= 1; j /= 2) {
        tree[val][j] = tree[val ][j * 2] + tree[val][j * 2 + 1];
    }
    gems[i]=val;
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    cin >> n >> q;

    for (int i = 0; i < 6; ++i) {
        cin >> types[i];
    }
    for (int i = 0; i < n; ++i) {
        char y;
        cin >> y;
        gems.push_back(y - '1' );
    }
    while (__builtin_popcount(n) != 1) {
        n++;
        //gems.push_back(0);
    }
    for (auto & i : tree) {
        i.resize(2 * n);

    }



    //Build Tree O(n)
    //leaf nodes
    for (int i = 0; i < gems.size(); ++i) {
        tree[gems[i]][i + n]++;
    }
    // internal nodes
    for (int j = 0; j < 6; ++j) {
        for (int i = n - 1; i >= 1; --i) {
            tree[j][i] = tree[j][2 * i] + tree[j][2 * i + 1];
        }
    }

    // queries
    for (int i = 0; i < q; ++i) {
        int qr, x, y;
        cin >> qr >> x >> y;
        x--;
        if (qr == 1) {
            y--;
            update(x, y);
        } else if (qr == 2) {
            types[x] = y;
        } else {
            y--;
            ll sum = 0;
            for (int j = 0; j < 6; ++j) {
                sum += seg(1, 0, n - 1, x, y, j)*types[j];
            }
            cout << sum << '\n';
        }
    }


    return 0;

}

//3 6
//10 10 10 10 10 10
//111
//3 1 3
//2 3 100
//1 1 3
//3 1 3
//1 2 3
//3 1 3
//30-120-210

//3 6
//10 10 10 10 100 20
//111
//1 1 5
//3 1 3
//1 1 1
//3 1 3
//2 1 55
//3 1 3
//120-30-165

//4 6
//1 2 3 4 5 6
//1234
//3 1 3
//1 1 2
//2 2 1
//3 1 4
//2 4 0
//3 1 4


//2 1
//1 2 3 4 5 6
//1 3
//3 1 2