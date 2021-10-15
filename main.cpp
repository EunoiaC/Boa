#include <iostream>
#include "includes/Token.cpp"

#include <string>

using namespace std;

int main() {
    auto* hi1 = new Token<int>("", new Value<int>(12, "STRING"));
    int s = hi1->getValueObject()->getValue();
    cout << s;
    return 0;
}
