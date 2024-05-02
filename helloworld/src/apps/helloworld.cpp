#include <cstdlib>
#include <iostream>
#include <string>           // system includes with brackets <...> ...
#include <vector>           // ...and in alphabetical order (google c++ code standard)

#include "header/header.h"  // ...local includes with "..."

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "using CMD cmake"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    header::print();  // explicit namespace qualification preferred
    cout << endl;
    
    return EXIT_SUCCESS;  // main returns an int
}
