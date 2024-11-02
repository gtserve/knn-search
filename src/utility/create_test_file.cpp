//
// Created by Nikos Tsolkas on 24/10/2024.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    ofstream outfile("random.txt");

    if (!outfile)
    {
        cerr << "Error creating file" << endl;
        return 1;
    }

    srand(time(NULL));
    for(int i = 0; i < 1000; i++)
    {
        outfile << rand() % 100 << " " << rand() % 100  << endl;
    }

    outfile.close();
    return 0;
}
