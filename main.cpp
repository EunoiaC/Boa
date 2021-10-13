#include <iostream>
#include "Includes/Value.cpp"

using namespace std;

int main() {
    auto* hi1 = new Value<int>(7, "int");
    auto* hi2 = new Value<string>("hi", "STRING");
    return 0;
}
