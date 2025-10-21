#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, vector<int>> minimumTotalWithPath(vector<vector<int>>& triangle) {
    if (triangle.empty()) return { 0, {} };

    int n = triangle.size();
    vector<int> dp = triangle.back();           
    vector<vector<int>> path(n);               
    for (int i = 0; i < n; ++i) path[i].resize(i + 1);

    for (int row = n - 2; row >= 0; --row) {
        for (int col = 0; col <= row; ++col) {
            if (dp[col] < dp[col + 1]) {
                dp[col] += triangle[row][col];
                path[row][col] = col;
            }
            else {
                dp[col] = dp[col + 1] + triangle[row][col];
                path[row][col] = col + 1;
            }
        }
    }

    vector<int> minPath;
    int col = 0;
    for (int row = 0; row < n; ++row) {
        minPath.push_back(triangle[row][col]);
        col = path[row][col];
    }

    return { dp[0], minPath };
}

int main() {
    int t;
    cout << "Enter number of tests: ";
    cin >> t;

    for (int test = 1; test <= t; ++test) {
        int n;
        cout << "\nTest #" << test << "\nEnter the number of rows in the triangle: ";
        cin >> n;

        vector<vector<int>> triangle(n);
        cout << "Enter elements in the triangle:\n";
        for (int i = 0; i < n; ++i) {
            triangle[i].resize(i + 1);
            for (int j = 0; j <= i; ++j) {
                cin >> triangle[i][j];
            }
        }

        pair<int, vector<int>> res = minimumTotalWithPath(triangle);
        int result = res.first;
        vector<int> minPath = res.second;

        cout << "Minimal path: ";
        for (size_t i = 0; i < minPath.size(); ++i) {
            cout << minPath[i];
            if (i != minPath.size() - 1) cout << " -> ";
        }
        cout << "\nResult: " << result << "\n";
    }

    return 0;
}

