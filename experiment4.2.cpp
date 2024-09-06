#include <iostream>
#include <fstream>
#include <climits> // For INT_MAX
using namespace std;

const int N = 100;
int rent[N][N];

int MinRent(int n) {
    int dp[N];
    for (int i = 0; i < n; ++i) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    for (int i = 1; i < n; ++i) {
        for (int x = 0; x < i; ++x) {
            if (dp[x] != INT_MAX && dp[x] + rent[x][i] < dp[i])
                dp[i] = dp[x] + rent[x][i];
        }
    }
    return dp[n - 1];
}

int main() {
    int n;

    // 读取input1.txt文件
    ifstream inputFile("input1.txt");
    if (!inputFile) {
        cerr << "Unable to open file input1.txt" << endl;
        return 1;
    }

    inputFile >> n;
    if (n <= 0 || n > N) {
        cerr << "Invalid number of stands in input file. Please enter a value between 1 and " << N << "." << endl;
        return 1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            inputFile >> rent[i][j];
            if (rent[i][j] < 0) {
                cerr << "Invalid cost in input file. Please enter a non-negative value." << endl;
                return 1;
            }
        }
    }

    inputFile.close();

    int minCost = MinRent(n);

    // 输出到output1.txt文件
    ofstream outputFile("output1.txt");
    if (!outputFile) {
        cerr << "Unable to open file output1.txt" << endl;
        return 1;
    }

    outputFile << "The minimum cost from the first stand to " << n << " is: " << minCost << endl;
    cout << "The minimum cost from the first stand to " << n << " is: " << minCost << endl;

    outputFile.close();
    return 0;
}
