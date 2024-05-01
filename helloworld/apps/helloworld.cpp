#include <iostream>
#include <vector>
#include <string>
#include <header/header.h>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "using CMD cmake"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
    print();
}
