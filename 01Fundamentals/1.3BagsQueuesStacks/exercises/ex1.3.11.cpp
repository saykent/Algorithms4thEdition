#include <iostream>
#include <sstream>
#include <cmath>
#include "StdIn.h"
#include "../Stack.h"

/**
 * ( 1 ( ( 2 3 + ) ( 4 5 * ) * ) + )  ==> 101.0
 * @return
 */
int main()
{
    Stack<std::string> operators;
    Stack<double> values;

    while (!StdIn::isEmpty())
    {
        std::string s = StdIn::readString();

        if      (s == "(") ;
        else if (s == "+")      operators.push(s);
        else if (s == "-")      operators.push(s);
        else if (s == "*")      operators.push(s);
        else if (s == "/")      operators.push(s);
        else if (s == ")")
        {
            std::string op = operators.pop();
            double v = values.pop();
            if      (op == "+")     v = values.pop() + v;
            else if (op == "-")     v = values.pop() - v;
            else if (op == "*")     v = values.pop() * v;
            else if (op == "/")     v = values.pop() / v;

            values.push(v);
        }
        else
        {
            values.push(std::stod(s));
        }
    }

    std::cout << "value is " << values.pop() << std::endl;
}