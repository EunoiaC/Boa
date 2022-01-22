//
// Created by Preeti Thorat on 12/6/21.
//

#ifndef BOA_BASETOKEN_H
#define BOA_BASETOKEN_H

#include <string>

using namespace std;

class BaseToken {
public:
    string fName, fTxt;

    BaseToken(string t, int start_pos, int end_pos, int line_num);
    ~BaseToken();

    /**
     * The starting position of the token at a certain line
     */
    int posStart;
    /**
     * The ending position of the token at a certain line
     */
    int posEnd;
    /**
     * The line the token is on
     */
    int line;
    /**
     * The type of the token, can be a supported object type, identifier, keyword, or a symbol
     */
    string type;

    /**
     * @return The type of token
     */
    string getType();

    /**
     * @return Type of the Token
     */
    virtual string toString();

    /**
     * @return Position data of the Token
     */
    string posData();
};


#endif //BOA_BASETOKEN_H
