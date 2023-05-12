// https://www.hackerrank.com/challenges/floyd-city-of-blinding-lights
//

#include <bits/stdc++.h>
#include <limits>
#include <vector>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

std::vector<std::vector<int>> floyd_dist;

void prepare_floyd_dist (int n,
                         std::vector<int> const& road_from,
                         std::vector<int> const& road_to,
                         std::vector<int> const& road_weight) {

    floyd_dist.resize(n);
    for(int i = 0; i<n; ++i) {
        floyd_dist[i].resize(n, -1);
    }

    int m = road_weight.size();
    for(int i = 0; i<m; ++i) {
        floyd_dist[road_from[i]-1][road_to[i]-1] = road_weight[i];
    }

    for (int k = 0; k<n; ++k) {
        for (int i = 0; i<n; ++i) {
            for (int j = 0; j<n; ++j) {
                if (floyd_dist[i][k] != -1 && floyd_dist[k][j] != -1) {
                    if (floyd_dist[i][j] == -1) {
                        floyd_dist[i][j] = floyd_dist[i][k] + floyd_dist[k][j];
                    } else {
                        floyd_dist[i][j] = std::min(floyd_dist[i][j], floyd_dist[i][k] + floyd_dist[k][j]);
                    }
                }
            }
        }
    }
}


int solve_query (int x, int y) {
    if (x == y)
        return 0;

    return floyd_dist[x-1][y-1];
}

int main()
{
    string road_nodes_edges_temp;
    getline(cin, road_nodes_edges_temp);

    vector<string> road_nodes_edges = split(rtrim(road_nodes_edges_temp));

    int road_nodes = stoi(road_nodes_edges[0]);
    int road_edges = stoi(road_nodes_edges[1]);

    vector<int> road_from(road_edges);
    vector<int> road_to(road_edges);
    vector<int> road_weight(road_edges);

    for (int i = 0; i < road_edges; i++) {
        string road_from_to_weight_temp;
        getline(cin, road_from_to_weight_temp);

        vector<string> road_from_to_weight = split(rtrim(road_from_to_weight_temp));

        int road_from_temp = stoi(road_from_to_weight[0]);
        int road_to_temp = stoi(road_from_to_weight[1]);
        int road_weight_temp = stoi(road_from_to_weight[2]);

        road_from[i] = road_from_temp;
        road_to[i] = road_to_temp;
        road_weight[i] = road_weight_temp;
    }

    prepare_floyd_dist(road_nodes, road_from, road_to, road_weight);

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int x = stoi(first_multiple_input[0]);

        int y = stoi(first_multiple_input[1]);

        std::cout << solve_query(x, y) << std::endl;
    }

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

