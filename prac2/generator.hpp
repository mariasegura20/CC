#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <numeric>
#include <vector>

using namespace std;

void generator()
{
    vector<int> students(5000);
    iota(students.begin(), students.end(), 1);

    for (int n = 5; n <= 30; n += 5)
    {
        // Create the file generatorN.txt
        string f_name = "generator" + std::to_string(n) + ".txt";
        ofstream f(f_name);

        // For each subject, a "sample" random numbers are generated between 1 y 500
        for (int k = 1; k <= n; k++)
        {
            f << k << " ";
            random_shuffle(students.begin(), students.end());
            int sample = ceil(5 * pow(ceil(k / 10.00), -1));
            for (int i = 0; i < sample; i++)
                f << students[i] << " ";
            f << endl;
        }

        // Close the file
        f.close();
    }
}