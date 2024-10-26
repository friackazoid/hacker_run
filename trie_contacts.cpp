// https://www.hackerrank.com/challenges/contacts/problem?isFullScreen=true

#include <bits/stdc++.h>
#include <utility>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'contacts' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_STRING_ARRAY queries as parameter.
 */

vector<int> contacts(vector<std::pair<std::string, std::string>> queries) {

    vector<int> result;
    std::set<string> contacts;
    for (auto query : queries) {
        if (query.first == "add") {
            contacts.insert(query.second);
        } else if (query.first == "find") {
            int count = 0;
            auto it = contacts.lower_bound(query.second);
            while (it != contacts.end() && it->find(query.second) == 0) {
                //if (contact.starts_with(query.second)) {
                // check that substring is at the beginning of the string
                count++;
                it++;
            }
            result.push_back(count);
        }
    }
    return result;


}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string queries_rows_temp;
    getline(cin, queries_rows_temp);

    int queries_rows = stoi(ltrim(rtrim(queries_rows_temp)));

    vector<pair<string, string>> queries(queries_rows);

    for (int i = 0; i < queries_rows; i++) {

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));
        queries[i] = std::make_pair (queries_row_temp[0], queries_row_temp[1]);
    }

    std::cout << "queries: " << queries.size() << std::endl;

    vector<int> result = contacts(queries);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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

