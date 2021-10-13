#include <iostream>
#include "Includes/Value.cpp"

using namespace std;

int main() {
    auto* hi1 = new Value<string>("hi", "STRING");
    auto* hi2 = new Value<string>("hi", "STRING");
    cout << hi1->compare(hi2);
    return 0;
}
