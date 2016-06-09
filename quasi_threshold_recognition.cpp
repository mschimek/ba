#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

void rooting(vector<vi>& adjlist) {
    int n = adjlist.size() - 1;
    for (int i = 0; i < n; i++) {
        adjlist[i].push_back(n);
        adjlist[n].push_back(i);
    }
}

int recognition(vector<vi>& adjlist, vi& result) {
    rooting(adjlist);
    /*for (int i = 0; i < adjlist.size(); i++) {
        cout << i << ":  " ;
        for (int j = 0; j <adjlist[i].size(); j++) {
            cout << adjlist[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    */
    int n = adjlist.size();
    vector<vi> sorted;
    vi visited;
    sorted.assign(n,vi());
    visited.assign(n, 0);
    for (int i = 0; i < adjlist.size(); i++) {
        int deg = adjlist[i].size();
        sorted[deg].push_back(i);
    }

    /*
    for (int i = 0; i < sorted.size(); i++) {
        cout << i << ":  " ;
        for (int j = 0; j < sorted[i].size(); j++) {
            cout << sorted[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;*/
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j < sorted[i].size(); j++) {
            int curNode = sorted[i][j];
            visited[curNode] = 1;
            for (int k = 0; k < adjlist[curNode].size(); k++) {
                int neighbour = adjlist[curNode][k];
                if (visited[adjlist[curNode][k]])
                    continue;
                if (result[neighbour] == result[curNode])
                    result[neighbour] = curNode;
                else
                    return 0;
            }
        }
    }
    return 1;
}

int main() {
    int n;
    cin >> n;
    vector<vi> adjlist(n+1,vi());
    vi result(n+1,-1);
    
    int p,q;
    while (cin >> p >> q) {
        adjlist[p].push_back(q);
        adjlist[q].push_back(p);
    }
    int res = recognition(adjlist, result);
    if (res) {
        for (int i = 0; i < n + 1; i++) {
            cout <<i << "  " << result[i] << endl;
        }
        return 0;
    }

    cout << "no quasi-threshold graph" << endl;
    return 0;



}
