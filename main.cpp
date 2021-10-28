#include <iostream>
#include "includes/values/String.cpp"
#include "includes/values/Number.cpp"
#include <string>
#include <vector>

using namespace std;

int main() {


    //todo: make token base class and make different value types
    Value<double>* hi1 = new Number(12.993);
    Value<string>* hi2 = new String("12");

    cout << hi1->getValue() << endl;
    cout << hi2->getValue();
    return 0;
}
