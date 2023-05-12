// https://www.hackerrank.com/challenges/dijkstrashortreach/problem?utm_campaign=challenge-recommendation&utm_medium=email&utm_source=24-hour-campaign

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'shortestReach' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER s
 */

void prepare_adj_graph(vector<vector<int>>& graph, vector<vector<int>> const& edges) {
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0] ;
        int v = edges[i][1] ;
        int w = edges[i][2];
        
        if (graph[u][v] == -1 || graph[u][v] > w) {
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }
}

void print_vector (std::vector<int> const& v) {
    for (const auto i : v) 
        std::cout << i << " " ;
        
    std::cout << std::endl;
}

vector<int> shortestReach(int n, vector<vector<int>> edges, int s) {
    vector<int> result;
    vector<int> dist(n+1, std::numeric_limits<int>::max());
    std::vector<std::vector<int>> graph(n+1, std::vector<int>(n+1, -1));
   
    prepare_adj_graph(graph, edges);

    vector<bool> visited(n+1, false);
    auto cmp = [](std::pair<int, int> const& a, std::pair<int, int> const& b) { return a.second > b.second; };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, decltype(cmp) > q(cmp);
   
    dist[s] = 0;
    q.push({s, dist[s]});
    
    while (!q.empty()) {
        int u = q.top().first;
        q.pop();
        visited[u] = true;
        
        std::cout << u << ": " ;
        print_vector(graph[u]);
        
        for (int v = 1; v <= n; ++v) {

            if (!visited[v] && graph[u][v] != -1) {
                std::cout << "u: " << u << " v: " << v << " w: " << graph[u][v] << std::endl;
                std::cout << "dist " << v << " was " << dist[v] << " new " << dist[u] + graph[u][v] << std::endl;
                if (dist[v] > dist[u] + graph[u][v]) {
                    std::cout << " Update "<< std::endl;
                    dist[v] = dist[u] + graph[u][v];
                    q.push({v, dist[v]});
                }
            }
        }
        print_vector(dist);
    }
    
    for (int i = 1; i <= n; i++) {
        if (i != s)  {
            if (dist[i] == std::numeric_limits<int>::max()) {
                result.push_back(-1);
            } else {
                result.push_back(dist[i]);
            }
        }
    }
    
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<vector<int>> edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(3);

            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 3; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        vector<int> result = shortestReach(n, edges, s);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

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

