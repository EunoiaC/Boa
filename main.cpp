#include <iostream>
#include "includes/values/String.cpp"
#include "includes/values/Number.cpp"
#include <string>

using namespace std;

int main() {
    //todo: make token base class and make different value types
    auto* hi1 = new Number(12);
    auto* hi2 = new Number(12);

    cout << hi1->compare(hi2);
    return 0;
}
