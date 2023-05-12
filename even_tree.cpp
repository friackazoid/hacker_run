// https://www.hackerrank.com/challenges/even-tree/problem

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


void print_array(std::vector<int> const& arr){
    for(int i=0; i<arr.size(); ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void print_vector_vector(std::vector< std::vector<int>> const& arr){
    for(int i=0; i<arr.size(); ++i){
        for(int j=0; j<arr[i].size(); ++j){
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int bfs(std::vector< std::vector<int>> const& adj, int start, std::vector<int>& visited){
    std::queue<int> q;
    q.push(start);
    visited[start] = 1;
    int count = 0;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        //std::cout << "visit: " << node << std::endl;
        for(int i=0; i<adj[node].size(); ++i){
            int next = adj[node][i];
            if(visited[next] == 0){
                visited[next] = 1;
                count++;
                q.push(next);
                //std::cout << "add: " << next << std::endl;
            }
        }
    }
    
    return count;
}

// Complete the evenForest function below.
int evenForest(int t_nodes, int t_edges, vector<int> t_from, vector<int> t_to) {
    std::vector< std::vector<int>> adj(t_nodes);
    for(int i=0; i<t_edges; i++){
        //adj[t_from[i] - 1].push_back(t_to[i] - 1);
        adj[t_to[i] - 1].push_back(t_from[i] - 1);
    }

    //print_vector_vector(adj);
    int count = 0;
    std::vector<int> visited(t_nodes, 0);
    for (int i=0; i<t_nodes; ++i){                                                       
          std::vector<int> visited(t_nodes, 0);                                          
          int vis = bfs(adj, i, visited);                                                          
          std::cout << '"' << i << "\": " ;                                              
          print_array(visited);
          
          if (vis%2 == 1) {
            count++;
            cout << "cut: " << i << std::endl;
           }
          
      }

    
    return count-1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_nodes_edges_temp;
    getline(cin, t_nodes_edges_temp);

    vector<string> t_nodes_edges = split(rtrim(t_nodes_edges_temp));

    int t_nodes = stoi(t_nodes_edges[0]);
    int t_edges = stoi(t_nodes_edges[1]);

    vector<int> t_from(t_edges);
    vector<int> t_to(t_edges);

    for (int i = 0; i < t_edges; i++) {
        string t_from_to_temp;
        getline(cin, t_from_to_temp);

        vector<string> t_from_to = split(rtrim(t_from_to_temp));

        int t_from_temp = stoi(t_from_to[0]);
        int t_to_temp = stoi(t_from_to[1]);

        t_from[i] = t_from_temp;
        t_to[i] = t_to_temp;
    }

    int res = evenForest(t_nodes, t_edges, t_from, t_to);

    fout << res << "\n";

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

