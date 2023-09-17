### 1. 无向图找割边(桥)

```c++
vector<vector<int>>g(n), ans;
vector<int>low(n), dfn(n), vis(n);
int now = 0;
void tarjan(int x, int fa){
    vis[x] = 1;
    low[x] = dfn[x] = ++now;
    for(int y : g[x]){
        if(y == fa)continue;
        if(!vis[y]){
            tarjan(y, x);
            low[x] = min(low[x], low[y]);
            if(low[y] > dfn[x])
                ans.push_back({x, y});
        }else {
            low[x] = min(low[x], dfn[y]);
        }
    }
}
tarjan(0, -1);
```

### 2. 无向图找割点

```c++
#include <bits/stdc++.h>
using namespace std;
int n, m; 
int dfn[100001], low[100001], inde, res;
bool vis[100001], flag[100001];  
vector<int> edge[100001];      

void tarjan(int x, int fa) {  
    vis[x] = true;
    low[x] = dfn[x] = ++inde; 
    int child = 0;             
    for (auto y : edge[x]) {  
        if (!vis[y]) {
            child++;                       
            tarjan(y, x);                  
            low[x] = min(low[x], low[y]);  
            if (fa != x && low[y] >= dfn[x] && !flag[x]){
                flag[x] = true;
                res++;
            }
        } else if (y != fa)
            low[x] = min(low[x], dfn[y]);  
    }
    if (fa == x && child >= 2 &&!flag[x]) { 
        flag[x] = true;
        res++;  
    }
}

int main() {
    cin >> n >> m;                  
    for (int i = 1; i <= m; i++) {  
        int x, y;
        cin >> x >> y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }                             
    for (int i = 1; i <= n; i++) 
        if (!vis[i]) {
            inde = 0;     
            tarjan(i, i); 
        }
    cout << res << endl;
    for (int i = 1; i <= n; i++)
        if (flag[i]) cout << i << " "; 
    return 0;
}

```

