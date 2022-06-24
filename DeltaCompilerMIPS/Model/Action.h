#ifndef ACTION_H
#define ACTION_H

#include "../Gals/Token.h"

class Action {
public:
    Action(int action, Token token): action(action), token(token) {}

    int action;
    Token token;
};

#endif // ACTION_H
