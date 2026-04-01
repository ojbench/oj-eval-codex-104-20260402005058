#include <bits/stdc++.h>
using namespace std;

static const int INF = INT_MAX/4;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n: columns, m: rows
    if(!(cin >> n >> m)){
        return 0;
    }
    vector<vector<int>> a(m, vector<int>(n));
    pair<int,int> start={-1,-1}, home={-1,-1};
    vector<pair<int,int>> shops;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int x; cin >> x; a[i][j]=x;
            if(x==2) start={i,j};
            else if(x==3) home={i,j};
            else if(x==4) shops.emplace_back(i,j);
        }
    }

    auto bfs = [&](pair<int,int> s){
        vector<int> dist(m*n, INF);
        deque<pair<int,int>> dq;
        auto idx = [&](int r,int c){return r*n + c;};
        if(s.first>=0){
            dist[idx(s.first,s.second)] = 0;
            dq.push_back(s);
        }
        const int dr[4]={1,-1,0,0};
        const int dc[4]={0,0,1,-1};
        while(!dq.empty()){
            auto [r,c]=dq.front(); dq.pop_front();
            int d = dist[idx(r,c)];
            for(int k=0;k<4;k++){
                int nr=r+dr[k], nc=c+dc[k];
                if(nr<0||nr>=m||nc<0||nc>=n) continue;
                if(a[nr][nc]==1) continue; // cannot pass construction
                int id = idx(nr,nc);
                if(dist[id] > d+1){
                    dist[id] = d+1;
                    dq.emplace_back(nr,nc);
                }
            }
        }
        return dist;
    };

    auto ds = bfs(start);
    auto dh = bfs(home);

    long long best = (long long)INF*2;
    for(auto [r,c]: shops){
        long long d1 = ds[r*n + c];
        long long d2 = dh[r*n + c];
        if(d1>=INF || d2>=INF) continue;
        best = min(best, d1 + d2);
    }

    if(best >= INF) {
        cout << -1 << '\n';
    } else {
        cout << best << '\n';
    }
    return 0;
}
