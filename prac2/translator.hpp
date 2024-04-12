#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

void translator()
{
    for (int n = 5; n <= 30; n += 5)
    {
        // Open the file generatorN.txt
        string g_name = "generator" + to_string(n) + ".txt";
        ifstream g(g_name);

        // Create the file translatorN.txt
        string t_name = "translator" + to_string(n) + ".txt";
        ofstream t(t_name);

        // Process the file generatorN.txt
        vector<vector<int>> lines(n);
        string reading_line;
        int currentLine = 0;
        while (getline(g, reading_line))
        {
            int number;
            istringstream format_line(reading_line);

            while (format_line >> number)
                lines[currentLine].push_back(number);
            currentLine++;
        }

        // Find the subjects that share at least one student
        int m = 0;
        vector<vector<bool>> problem(n, vector<bool>(n));

        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (find_first_of(lines[i].begin(), lines[i].end(), lines[j].begin(), lines[j].end()) != lines[i].end())
                {
                    problem[i][j] = true;
                    m++;
                }

        // Write the data in the translatorN.txt
        t << "p edge " << n << " " << m;
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (problem[i][j])
                    t << endl << "e " << i + 1 << " " << j + 1;

        // Close the files
        g.close();
        t.close();
    }
}