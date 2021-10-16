#include <iostream>
#include "includes/values/String.cpp"
#include <string>

using namespace std;

int main() {
    //todo: make token base class and make different value types
    auto* hi1 = new String("hi");
    auto* hi2 = new String("hi");

    cout << hi1->compare(hi2);
    return 0;
}
