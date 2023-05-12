// https://www.hackerrank.com/challenges/the-quickest-way-up/problem

#include <bits/stdc++.h>
#include <queue>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'quickestWayUp' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY ladders
 *  2. 2D_INTEGER_ARRAY snakes
 */

void print_vector (vector<int> const& v) {
    for (auto& i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int quickestWayUp(vector<vector<int>> ladders, vector<vector<int>> snakes) {
    vector<int> board(101, -1);
    for (auto& ladder : ladders) {
        board[ladder[0]] = ladder[1];
    }
    for (auto& snake : snakes) {
        board[snake[0]] = snake[1];
    }
    vector<int> dist(101, -1);
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        std::cout << "Go to: " << cur << std::endl;
        for (int i = 1; i <= 6; ++i) {
            int next = cur + i;
            if (next > 100) continue;
            if (board[next] != -1) next = board[next];
            if (dist[next] != -1) continue;
            dist[next] = dist[cur] + 1;
            q.push(next);
        }
    }

    print_vector(dist);
    return dist[100];
}

int quickestWayUp_2 (std::vector<std::vector<int>> ladders, std::vector<std::vector<int>> snakes) {
    std::vector<int> board(101, -1);
    for (auto& ladder : ladders) {
        board[ladder[0]] = ladder[1];
    }
    for (auto& snake : snakes) {
        board[snake[0]] = snake[1];
    }
    std::vector<int> dist(101, -1);

    auto cmp = [](std::pair<int,int> left, std::pair<int,int> right) { return left.second > right.second; };
    std::priority_queue< std::pair<int,int>, std::vector<std::pair<int, int>>, decltype(cmp) > q(cmp);
    q.push( {1, 100} );
    dist[1] = 0;
    while (!q.empty()) {
        int cur = q.top().first;
        q.pop();
        std::cout << "Go to: " << cur << std::endl;
        for (int i = 1; i <= 6; ++i) {
            int next = cur + i;
            if (next == 100) return dist[cur] + 1;
            if (next > 100) continue;
            if (board[next] != -1) next = board[next];
            if (dist[next] != -1) continue;
            dist[next] = dist[cur] + 1;
            std::cout << "Push: " << next << " dist: " << 100 - next << std::endl;
            q.push( {next, 100 - next} );
        }
    }

    print_vector(dist);
    return dist[100];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        vector<vector<int>> ladders(n);

        for (int i = 0; i < n; i++) {
            ladders[i].resize(2);

            string ladders_row_temp_temp;
            getline(cin, ladders_row_temp_temp);

            vector<string> ladders_row_temp = split(rtrim(ladders_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int ladders_row_item = stoi(ladders_row_temp[j]);

                ladders[i][j] = ladders_row_item;
            }
        }

        string m_temp;
        getline(cin, m_temp);

        int m = stoi(ltrim(rtrim(m_temp)));

        vector<vector<int>> snakes(m);

        for (int i = 0; i < m; i++) {
            snakes[i].resize(2);

            string snakes_row_temp_temp;
            getline(cin, snakes_row_temp_temp);

            vector<string> snakes_row_temp = split(rtrim(snakes_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int snakes_row_item = stoi(snakes_row_temp[j]);

                snakes[i][j] = snakes_row_item;
            }
        }

        int result = quickestWayUp(ladders, snakes);

        fout << result << "\n";
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

