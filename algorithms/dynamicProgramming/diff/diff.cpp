/*
git diff: Application of Longest common subsequence 
*/
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

/*
struct represent the diff entry
@type: '+' lines added
       '-' lines removed
       ' ' unchanged
@line actual content of lines.
*/
struct DiffEntry{
    char type;
    string line;
};

vector<string> readLinesFromFiles(string& fileName) {
    vector<string> lines;
    ifstream file(fileName);

    if(!file.is_open()){
        cerr << "Error: could not open file " << fileName << endl;
        return lines;
    }

    string line;
    while(getline(file, line)){
        lines.push_back(line);
    }

    return lines;
}

/**
 * @brief Computes the difference between two sets of lines using the Longest Common Subsequence (LCS) algorithm.
 * It generates a sequence of DiffEntry objects indicating common, added, or deleted lines.
 * @param file1Lines A vector of strings representing the lines of the first file.
 * @param file2Lines A vector of strings representing the lines of the second file.
 * @return A vector of DiffEntry objects, representing the computed diff.
 */
vector<DiffEntry> computeDiff(vector<string>& file1Lines, vector<string>& file2Lines) {
    int m = file1Lines.size();
    int n = file2Lines.size();

    // Create a 2D dynamic programming table (dp).
    // dp[i][j] will store the length of the LCS of file1Lines[0...i-1]
    // and file2Lines[0...j-1].
    // The table is (m+1) x (n+1) to handle empty prefixes (base cases).
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the dp table using the LCS recurrence relation
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            // If the current lines from both files match
            if (file1Lines[i - 1] == file2Lines[j - 1]) {
                // The LCS length is 1 plus the LCS of the preceding lines
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                // If lines don't match, the LCS is the maximum of:
                // 1. LCS of file1Lines[0...i-2] and file2Lines[0...j-1] (skipping file1's current line)
                // 2. LCS of file1Lines[0...i-1] and file2Lines[0...j-2] (skipping file2's current line)
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstruct the diff by backtracking through the dp table.
    // We start from the bottom-right corner (dp[m][n]) and move towards dp[0][0].
    vector<DiffEntry> diff;
    int i = m, j = n;
    while (i > 0 || j > 0) {
        // Case 1: Current lines match (common line)
        // This condition also implies that dp[i][j] must have come from dp[i-1][j-1] + 1
        if (i > 0 && j > 0 && file1Lines[i - 1] == file2Lines[j - 1]) {
            diff.push_back({' ', file1Lines[i - 1]}); // Add as common
            i--; // Move diagonally up-left in the dp table
            j--;
        }
        // Case 2: Line in file2 was added (move left in dp table)
        // This means dp[i][j] came from dp[i][j-1] and file2[j-1] is an addition.
        // We prioritize additions if lengths are equal for simplicity, or if file1 is exhausted.
        else if (j > 0 && (i == 0 || dp[i][j - 1] > dp[i - 1][j])) {
            diff.push_back({'+', file2Lines[j - 1]}); // Add as new line
            j--; // Move left in the dp table
        }
        // Case 3: Line in file1 was deleted (move up in dp table)
        // This means dp[i][j] came from dp[i-1][j] and file1[i-1] is a deletion.
        // This also handles the case where dp[i-1][j] == dp[i][j-1] (prioritizing deletion if tie).
        else { // (i > 0 && (j == 0 || dp[i - 1][j] >= dp[i][j - 1]))
            diff.push_back({'-', file1Lines[i - 1]}); // Add as deleted line
            i--; // Move up in the dp table
        }
    }

    // The diff entries are collected in reverse order during backtracking,
    // so reverse the vector to get the correct chronological order.
    reverse(diff.begin(), diff.end());
    return diff;
}

/**
 * @brief Prints the computed diff to the console.
 * @param diff A vector of DiffEntry objects to print.
 */
void printDiff(const vector<DiffEntry>& diff) {
    cout << "--- Diff Output ---" << endl;
    for (const auto& entry : diff) {
        cout << entry.type << " " << entry.line << endl;
    }
    cout << "-------------------" << endl;
}

/*
Enter two filepath and run the program to get diff.
*/
int main(int argc, char* argv[]){
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << "<file1_path> <file2_path>" << endl;
        return 1;
    }

    string file1Name = argv[1];
    string file2Name = argv[2];

    vector<string> file1Lines = readLinesFromFiles(file1Name);
    vector<string> file2Lines = readLinesFromFiles(file2Name);

    if(file1Lines.empty() && !ifstream(file1Name).is_open())
    {
        cerr << "Wrong file path" << file1Name << " " << endl;
        return 1;
    }

    if(file2Lines.empty() && !ifstream(file2Name).is_open())
    {
        cerr << "Wrong file path" << file2Name << " " << endl;
        return 1;
    }


    vector<DiffEntry> diff = computeDiff(file1Lines, file2Lines);
    printDiff(diff);

    return 0;
}