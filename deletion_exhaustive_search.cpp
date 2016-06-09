#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

int treated[100][100];
void rooting(vector<vi>& adjlist) {
    int n = adjlist.size() - 1;
    for (int i = 0; i < n; i++) {
        adjlist[i].push_back(n);
        adjlist[n].push_back(i);
    }
}

int threshold_recognition(vi& tree) {
    vi degree(tree.size(), 0);
    vi distance(tree.size(), 0);
    queue<int> q;
    for (int i = 0; i < tree.size(); i++) {
        if (tree[i] != -1)
            degree[tree[i]]++;
    }
    for (int i = 0; i < tree.size(); i++) {
        if (degree[i] == 0)
            q.push(i);
    }
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        int f = tree[cur];
        //cout << "cur: " << cur << "  f: " << f << endl;
        if (f == -1)
            break;
        if (distance[cur] > 0 && distance[f] > 1)
            return 0;
        distance[f] = max(distance[cur] + 1, distance[f]);
        if (--degree[f] == 0)
            q.push(f);
    }
    return 1;
}

int recognition(vector<vi> adjlist) {
    rooting(adjlist);
    vi result(adjlist.size(), -1);
    int n = adjlist.size();
    vector<vi> sorted;
    vi visited;
    sorted.assign(n,vi());
    visited.assign(n, 0);
    for (int i = 0; i < adjlist.size(); i++) {
        int deg = adjlist[i].size();
        sorted[deg].push_back(i);
    }
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
    /*for (int i = 0; i < result.size(); i++) {
            cout <<i << "  " << result[i] << endl;
    } */
    if (threshold_recognition(result))
        return 2;
    return 1;
}

int recursive_search(vector<vi> adjlist, int k) {
    if (recognition(adjlist) == 2)
        return k;
    int min = 1E9;
    for (int i = 0; i < adjlist.size(); i++) {
        for (int j = 0; j < adjlist[i].size(); j++) {
            int source = i;
            int dest = adjlist[i][j];
          //  cout << "source:  " << source << "   dest: " << dest << endl;
            if (treated[source][dest])
                continue;
            
            treated[source][dest] = 1;
            treated[dest][source] = 1;
            adjlist[source].erase(adjlist[source].begin() + j);
            int l;
            for (l = 0; l < adjlist[dest].size(); l++) {
                if (adjlist[dest][l] == source) {
                    adjlist[dest].erase(adjlist[dest].begin() + l);
                  //  cout << "l: " << l << endl;
                    break;
                }
                    
            }
          /*  for (int y = 0; y < adjlist.size(); y++) {
                cout << y << ": ";
                for (int z = 0; z < adjlist[y].size(); z++) {
                    cout << adjlist[y][z] << "  ";
                }
                cout << endl;
            }
            cout << endl;*/
            int res = recursive_search(adjlist, k+1);
            if (res < min)
                min = res;
            
            adjlist[source].insert(adjlist[source].begin() + j, dest);
            adjlist[dest].insert(adjlist[dest].begin() + l, source);
           // cout << "source:  " << source << "   dest: " << dest << endl;
        }
    }
    for (int i = 0; i < adjlist.size(); i++) {
        for (int j = 0; j < adjlist[i].size(); j++) {
            treated[i][adjlist[i][j]] = 0;
            treated[adjlist[i][j]][i] = 0;
        }
    }
    return min;
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
    for (int i = 0; i < adjlist.size(); i++) {
        cout << i << ":  " ;
        for (int j = 0; j <adjlist[i].size(); j++) {
            cout << adjlist[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    /*int res = recognition(adjlist);
    if (res == 0)
        cout << "no quasi-threshold" << endl;
    if (res == 1)
        cout << "quasi-threshold" << endl;
    if (res == 2)
        cout << "threshold" << endl; */
    cout << recursive_search(adjlist,0) << endl;
}
























