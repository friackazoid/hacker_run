#include <algorithm>
#include <bits/stdc++.h>
#include <queue>
#include <set>
#include <utility>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// we need only unidirected edges;
// if 1->2 edge already added no 2->1 allowed

//bool my_cmp (std::pair<int, int> const& l, std::pair<int, int> const& r) {
//    return (l.first == r.first || l.first == r.second) && (l.second == r.second || l.second == r.first);
//}

class DisjointSet {
    public:
        DisjointSet (int n) {
            
            parent_.resize(n);
            rank_.resize(n);
            
            std::iota(parent_.begin(), parent_.end(), 0);
            std::fill_n(rank_.begin(), n, 0);
        }
        int find (int x) {
            if (parent_[x] != x)
                parent_[x] = find(parent_[x]);
                
            return parent_[x];  
        }
        
        void merge (int x, int y) {
            int root_x = find(x);
            int root_y = find(y);
            
            if (root_x != root_y) {
                if (rank_[root_x] < rank_[root_y]) {
                    parent_[root_x] = root_y;
                } else if (rank_[root_x] > rank_[root_y]) {
                    parent_[root_y] = root_x;
                } else {
                    parent_[root_x] = root_y;
                    rank_[root_y]++;
                }
            }
        }
        
    private:
        std::vector<int> parent_;
        std::vector<int> rank_;  
};

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

/*
 * For the weighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
 *
 */

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {
    
    DisjointSet dsu(g_nodes);
     
    std::vector<int> order(g_weight.size());
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&g_weight](int a, int b) {
        return g_weight[a] < g_weight[b]; });

    int total_sum =0;
    for (const auto e : order) {
        int u = g_from[e];
        int v = g_to[e];
        //std::cout << "w: " << g_weight[e] << " u: " << u << " v: " << v << std::endl;
        
        if (dsu.find(u) != dsu.find(v)) {
            dsu.merge(u,v);
            total_sum = total_sum + g_weight[e];
        }
    }

    return total_sum;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_from, g_to, g_weight);

    // Write your code here.
    fout << res << std::endl;

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

