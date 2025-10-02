// Written using GPT-5 (low reasoning) in Windsurf.
// As far as I can tell, Topcoder doesn't have any rules against AI.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MN = 80;
const int MB = 20;
const int MO = 10;

enum MoveType { MT_NONE = 0, MT_MOVE = 1, MT_UNPACK = 2, MT_PACK = 3 };

struct Bridgeman {
    int id;
    int position;
    int bricks;
    int target; // -1 if none
    int bridgeFrom; // -1 if none
    int bridgeTo;

    MoveType planned;
    int planned_to;
};

struct Order { int from, to; };

int N, B, O;
Bridgeman bridgemen[MB];
int G[MN][MN];
bool connected[MN][MN];
Order orders[MO];

inline int edgeCost(int u, int v, int bricks, int source) {
    if (u == v) return 0;
    if (connected[u][v] && u == source) return 1; // only immediate next edge benefits from existing bridge
    if (G[u][v] <= bricks) return 3; // unpack + move + pack
    return 1e8;
}

pair<int,int> shortestNextHop(int s, int t, int bricks) {
    // Dijkstra for next hop with small N
    if (s == t) return {0, -1};
    const int INF = 1e9;
    static int dist[MN];
    static int par[MN];
    static char vis[MN];
    for (int i = 0; i < N; ++i) { dist[i]=INF; par[i]=-1; vis[i]=0; }
    dist[s]=0;
    for (int it=0; it<N; ++it) {
        int u=-1, best=INF;
        for (int i=0;i<N;++i) if(!vis[i] && dist[i]<best){best=dist[i];u=i;}
        if (u==-1) break;
        vis[u]=1;
        if (u==t) break;
        for (int v=0; v<N; ++v) if (v!=u) {
            int w = edgeCost(u,v,bricks,s);
            if (w>=INF) continue;
            if (dist[v] > dist[u] + w) { dist[v] = dist[u]+w; par[v]=u; }
        }
    }
    if (dist[t] >= INF) return {INF, -1};
    // backtrack one step
    int cur = t, prv = par[cur];
    if (prv==-1) return {0,-1};
    while (prv != s) { cur = prv; prv = par[cur]; }
    return {dist[t], cur};
}

void planForCarrying(Bridgeman& b) {
    // If he has a pending placed bridge, enforce packing it eventually, but first move across if at from side
    if (b.bridgeFrom != -1) {
        if (b.position == b.bridgeFrom) {
            b.planned = MT_MOVE; b.planned_to = b.bridgeTo; return;
        } else if (b.position == b.bridgeTo) {
            b.planned = MT_PACK; b.planned_to = b.bridgeFrom; return;
        } else {
            // Shouldn't happen, reset
            b.bridgeFrom = b.bridgeTo = -1;
        }
    }
    auto pr = shortestNextHop(b.position, b.target, b.bricks);
    int nh = pr.second;
    if (nh == -1) { b.planned = MT_NONE; return; }
    if (connected[b.position][nh]) { b.planned = MT_MOVE; b.planned_to = nh; }
    else if (G[b.position][nh] <= b.bricks) { b.planned = MT_UNPACK; b.planned_to = nh; }
    else { b.planned = MT_NONE; }
}

pair<int,int> shortestPathCost(int s, int mid, int t, int bricks) {
    auto a = shortestNextHop(s, mid, bricks);
    int d1 = a.first;
    // approximate cost to destination from mid (ignore potential brick reduction since we repack)
    auto b = shortestNextHop(mid, t, bricks);
    int d2 = b.first;
    if (d1 >= 1e9 || d2 >= 1e9) return { (int)1e9, -1};
    return { d1 + d2, a.second };
}

void planForFree(Bridgeman& b, int myAssignedOrder) {
    // If he has a pending placed bridge, prioritize finishing it to reclaim bricks
    if (b.bridgeFrom != -1) {
        if (b.position == b.bridgeFrom) {
            b.planned = MT_MOVE; b.planned_to = b.bridgeTo; return;
        } else if (b.position == b.bridgeTo) {
            b.planned = MT_PACK; b.planned_to = b.bridgeFrom; return;
        } else {
            // inconsistent, reset tracking to avoid being stuck
            b.bridgeFrom = b.bridgeTo = -1;
        }
    }
    if (myAssignedOrder != -1) {
        // head to pickup for assigned order
        auto pr = shortestNextHop(b.position, orders[myAssignedOrder].from, b.bricks);
        int nh = pr.second;
        if (nh != -1) {
            if (connected[b.position][nh]) { b.planned = MT_MOVE; b.planned_to = nh; }
            else if (G[b.position][nh] <= b.bricks) { b.planned = MT_UNPACK; b.planned_to = nh; }
            else { b.planned = MT_NONE; }
            return;
        }
    }
    // idle behavior: build a short edge if possible
    int bestV = -1, bestD = 1e9;
    for (int v = 0; v < N; ++v) if (v != b.position && !connected[b.position][v] && G[b.position][v] <= b.bricks) {
        if (G[b.position][v] < bestD) { bestD = G[b.position][v]; bestV = v; }
    }
    if (bestV != -1) { b.planned = MT_UNPACK; b.planned_to = bestV; }
    else { b.planned = MT_NONE; }
}

string actStr(const string& cmd, int a, int b) {
    return cmd + " " + to_string(a) + " " + to_string(b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> B >> O;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) { cin >> G[i][j]; connected[i][j]=false; }
    for (int i = 0; i < B; ++i) { bridgemen[i].id = i; bridgemen[i].bridgeFrom = bridgemen[i].bridgeTo = -1; }

    for (int turn = 0; turn < 1000; ++turn) {
        int elapsedTime; cin >> elapsedTime;
        for (int i = 0; i < B; ++i) {
            cin >> bridgemen[i].position >> bridgemen[i].bricks >> bridgemen[i].target;
            bridgemen[i].planned = MT_NONE; bridgemen[i].planned_to = -1;
        }
        for (int i = 0; i < O; ++i) { cin >> orders[i].from >> orders[i].to; }

        // Assign free bridgemen to distinct orders (closest-man heuristic)
        vector<int> orderAssignedTo(O, -1);
        vector<int> freeIds;
        for (int i = 0; i < B; ++i) if (bridgemen[i].target == -1) freeIds.push_back(i);
        // For each order, find closest free bridgeman
        vector<pair<int,pair<int,int>>> cand; // (cost, (order, bridgeman))
        for (int oi = 0; oi < O; ++oi) {
            for (int bi : freeIds) {
                auto pr = shortestPathCost(bridgemen[bi].position, orders[oi].from, orders[oi].to, bridgemen[bi].bricks);
                cand.push_back({pr.first, {oi, bi}});
            }
        }
        sort(cand.begin(), cand.end());
        vector<int> bridgemanAssigned(B, 0);
        for (auto &x : cand) {
            int cost = x.first; int oi = x.second.first; int bi = x.second.second;
            if (cost >= 1e9) continue;
            if (orderAssignedTo[oi] == -1 && !bridgemanAssigned[bi]) {
                orderAssignedTo[oi] = bi; bridgemanAssigned[bi] = 1;
            }
        }

        // Build reverse mapping: which order assigned to each bridgeman
        vector<int> myAssignedOrder(B, -1);
        for (int oi = 0; oi < O; ++oi) if (orderAssignedTo[oi] != -1) myAssignedOrder[orderAssignedTo[oi]] = oi;

        // Plan actions
        for (int i = 0; i < B; ++i) {
            Bridgeman &b = bridgemen[i];
            if (b.target != -1) planForCarrying(b);
            else planForFree(b, myAssignedOrder[i]);
        }

        // Build actions ordered: UNPACKs (dedup same edge) -> MOVEs -> PACKs
        vector<string> out;
        // Track which edge is being unpacked this turn to allow following MOVEs
        bool willUnpack[MN][MN];
        for (int i=0;i<N;++i) for (int j=0;j<N;++j) willUnpack[i][j]=false;

        // First UNPACKs
        for (int i = 0; i < B; ++i) if (bridgemen[i].planned == MT_UNPACK) {
            int u = bridgemen[i].position, v = bridgemen[i].planned_to;
            if (u==v) continue;
            if (!connected[u][v] && !willUnpack[u][v] && G[u][v] <= bridgemen[i].bricks) {
                out.push_back(actStr("UNPACK", bridgemen[i].id, v));
                willUnpack[u][v]=willUnpack[v][u]=true;
                connected[u][v]=connected[v][u]=true; // effective this turn for later MOVEs
                // mark his placed bridge so he will pack it later
                bridgemen[i].bridgeFrom = u; bridgemen[i].bridgeTo = v;
            } else {
                // someone else will unpack or already exists; convert to MOVE if possible
                if (connected[u][v] || willUnpack[u][v]) {
                    bridgemen[i].planned = MT_MOVE;
                } else {
                    bridgemen[i].planned = MT_NONE; // cannot act
                }
            }
        }
        // Then MOVEs
        for (int i = 0; i < B; ++i) if (bridgemen[i].planned == MT_MOVE) {
            int u = bridgemen[i].position, v = bridgemen[i].planned_to;
            if (u!=v && connected[u][v]) {
                out.push_back(actStr("MOVE", bridgemen[i].id, v));
                // update position for possible PACK in same turn? Not allowed: one action per bridgeman per turn.
            }
        }
        // Finally PACKs
        for (int i = 0; i < B; ++i) if (bridgemen[i].planned == MT_PACK) {
            int u = bridgemen[i].position, v = bridgemen[i].planned_to;
            if (u!=v && connected[u][v]) {
                out.push_back(actStr("PACK", bridgemen[i].id, v));
                connected[u][v]=connected[v][u]=false;
                bridgemen[i].bridgeFrom = -1; bridgemen[i].bridgeTo = -1;
            }
        }

        for (size_t i = 0; i < out.size(); ++i) {
            cout << out[i];
            if (i + 1 < out.size()) cout << " | ";
        }
        cout << '\n';
        cout.flush();
    }
    return 0;
}