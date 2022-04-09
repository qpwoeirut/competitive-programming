#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<int>> shiftingSands(vector<vector<int>> board, vector<string> moves)
{
}

// Do not modify below this line
vector<string> tokenize(string s)
{
    vector<string> tokens;
    stringstream ss(s);
    string word;

    while (ss >> word)
        tokens.push_back(word);

    return tokens;
}

int main()
{
    string s;
    int t;

    getline(cin, s);
    t = stoi(s);

    for (int i = 0; i < t; i++)
    {
        vector<vector<int>> board;

        for (int j = 0; j < 4; j++)
        {
            vector<int> vector_row;
            getline(cin, s);
            vector<string> vector_row_str = tokenize(s);
            for (int k = 0; k < 4; k++)
                vector_row.push_back(stoi(vector_row_str[k]));

            board.push_back(vector_row);
        }

        vector<string> moves;
        getline(cin, s);
        moves = tokenize(s);
        vector<vector<int>> output = shiftingSands(board, moves);

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                cout << output[j][k] << " ";
            }
            cout << endl;
        }
    }
}
