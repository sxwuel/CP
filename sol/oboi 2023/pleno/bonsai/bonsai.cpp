#include<bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;

const int mxn=2e5+10, mxk=210;
const ll inf=1e18+10;
int n,k, b[mxn];
ll ans=0;
vector<int> Adj[mxn];

ll sp[mxn];
ll dp[mxn][mxk];

int tin[mxn], tout[mxn], et[mxn], timer=0;
bool fol[mxn]; 

void dfs(int v, int u){
    tin[v]=++timer;
    et[timer]=v;
    sp[tin[v]]+=b[v]; //atencao
    for(int vz:Adj[v]){
        if(vz==u) continue;
        dfs(vz, v);
    }
    tout[v]=timer;
    if(tin[v]==tout[v])
        fol[timer]=true;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    for(int i=1; i<=n; i++)
        cin>>b[i];
    for(int i=1; i<=n-1; i++){
        int u, v;
        cin>>u>>v;
        Adj[u].pb(v);
        Adj[v].pb(u);
    }
    //passeio de euler
    dfs(1, -1);
    for(int i=1; i<=n+1; i++)
        sp[i]=sp[i-1]+sp[i];
    
    for(int u=1; u<=n+10; u++)
        for(int j=0; j<=k; j++)
            dp[u][j]-inf;

    ll spn=sp[n];
    for(int u=1; u<=n; u++){
        int e=tin[u];
        dp[e][0]=spn-sp[e-1];
    }
    
    for(int e=n; e>=1; e--){
        int u=et[e];
        for(int j=1; j<=k; j++){
            dp[e][j] = max( b[u]+dp[e+1][j] , dp[tout[u]+1][j-1] );
        }
    }

    for(int i=0; i<=k; i++)
        ans=max(ans, dp[1][i]);
    
    cout<<ans;

}
