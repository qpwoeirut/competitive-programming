#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>

class Bridgeman {
public:
    int ID;
    int Position;
    int Target;
    int Bricks;
    int BridgeFrom = -1;
    int BridgeTo = -1;
};

class Order {
public:
    int From;
    int To;
};

static int g_seed = 777778;
static int Rand(int mod) {
    g_seed = (214013 * g_seed + 2531011);
    return ((g_seed >> 16) & 0x7FFF) % mod;
}

int main() {
    int N, B, O;
    std::cin >> N >> B >> O;

    int dists[N][N];
    bool connected[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            connected[i][j]=false;
            std::cin >> dists[i][j];
        }
    }

    Bridgeman bridgemen[B];
    for (int i = 0; i < B; ++i) {
        bridgemen[i].ID = i;
    }

    for (int turn = 1; turn <= 1000; turn++) {
        int elapsedTime;
        std::cin >> elapsedTime;
        for (int i = 0; i < B; ++i) {
            std::cin >> bridgemen[i].Position >> bridgemen[i].Bricks >> bridgemen[i].Target;
        }
        std::vector<Order> orders(O);
        for (int i = 0; i < O; ++i) {
            std::cin >> orders[i].From >> orders[i].To;
        }

        std::vector<std::string> output;
        for (auto& b : bridgemen) {
            if (b.BridgeFrom == -1) { // unpack
                std::vector<int> targets;
                for (int t = 0; t < N; ++t) {
                    if (t != b.Position && !connected[b.Position][t] && dists[b.Position][t] <= b.Bricks) {
                        targets.push_back(t);
                    }
                }
                if (!targets.empty()) {
                    int t = targets[Rand(targets.size())];
                    output.push_back("UNPACK " + std::to_string(b.ID) + " " + std::to_string(t));
                    b.BridgeFrom = b.Position;
                    b.BridgeTo = t;
                    connected[b.BridgeFrom][b.BridgeTo] = true;
                    connected[b.BridgeTo][b.BridgeFrom] = true;
                }
            } else if (b.BridgeFrom == b.Position) { // MOVE
                output.push_back("MOVE " + std::to_string(b.ID) + " " + std::to_string(b.BridgeTo));
            } else { // PACK
                output.push_back("PACK " + std::to_string(b.ID) + " " + std::to_string(b.BridgeFrom));
                connected[b.BridgeFrom][b.BridgeTo] = false;
                connected[b.BridgeTo][b.BridgeFrom] = false;
                b.BridgeFrom = -1;
                b.BridgeTo = -1;
            }
        }

        for (size_t i = 0; i < output.size(); ++i) {
            std::cout << output[i];
            if (i < output.size() - 1) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}