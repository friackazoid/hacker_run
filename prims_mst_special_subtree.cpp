#include <bits/stdc++.h>
#include <queue>
#include <vector>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

std::vector<std::vector<int>> make_adj_matrix (const int n, vector<vector<int>> const& edges) {
    std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n, -1));
    //std::cout << "here: " << n << std::endl;
    for (const auto& e: edges) {
        //std::cout << "e: [" << e[0] << ", " << e[1] << ", " << e[2] << "]" << std::endl;
        adj_matrix[e[0] - 1][e[1] - 1] = e[2];
        adj_matrix[e[1] - 1][e[0] - 1] = e[2]; 
    }

    return adj_matrix;
}

void print_adj_mat (std::vector<std::vector<int>> const& adj_matrix) {
    for (const auto& n : adj_matrix) {
        for (const auto& e: n)
            std::cout << e << " ";
        std::cout << std::endl;
    }
}

/*
 * Complete the 'prims' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER start
 */
int prims(int n, vector<vector<int>> edges, int start) {
    auto adj_matrix = make_adj_matrix(n, edges);
    auto adj_start = start - 1;
    //print_adj_mat(adj_matrix);
   
    // <width, node_n>
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int,int>>> pq;
       
    pq.push(std::make_pair(0, adj_start));
    //std::cout << "start: " << min_elm << ", " << adj_start << std::endl;
    
    std::vector<int> vis(n, 0);
    int sum = 0;
    while(!pq.empty()) {
        auto it = pq.top(); pq.pop();
        int node = it.second; int wt = it.first;
        
        if (vis[node] == 1) continue;
        
        //std::cout << "pop: " << node << "," << wt << std::endl;
        
        vis[node] = 1;
        sum += wt;
        //std::cout << "sum: " << sum << std::endl;
        for (auto i = 0; i<n; ++i) {
            int edW = adj_matrix[node][i];
            //std::cout << "vis: [" << node << "," << i << "]: " << edW << std::endl;
            if ( vis[i] != 1 && edW != -1) {
                //std::cout << "push: " << i << "," << edW << std::endl;
                pq.push(std::make_pair(edW, i));
            }
        }
    }
    return sum;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

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

    string start_temp;
    getline(cin, start_temp);

    int start = stoi(ltrim(rtrim(start_temp)));

    int result = prims(n, edges, start);

    fout << result << "\n";

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

