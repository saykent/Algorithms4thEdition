#include "StdIn.h"
#include <regex>
#include <stack>
#include <cmath>

/**
 * ( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )  ==> 101.0
 * ( ( 1 + sqrt ( 5.0 ) ) / 2.0 )  ==> 1.618033988749895
 * @return
 */
int main()
{
    std::stack<std::string> operators;
    std::stack<double> values;

    while (!StdIn::isEmpty())
    {
        std::string s = StdIn::readString();

        if      (s == "(") ;
        else if (s == "+")      operators.push(s);
        else if (s == "-")      operators.push(s);
        else if (s == "*")      operators.push(s);
        else if (s == "/")      operators.push(s);
        else if (s == "sqrt")   operators.push(s);
        else if (s == ")")
        {
            std::string op = operators.top(); operators.pop();
            double v = values.top(); values.pop();
            if      (op == "+")     v = values.top() + v;
            else if (op == "-")     v = values.top() - v;
            else if (op == "*")     v = values.top() * v;
            else if (op == "/")     v = values.top() / v;
            else if (op == "sqrt")  v = std::sqrt(v);
            if (op != "sqrt")
                values.pop();
            values.push(v);
        }
        else
        {
            values.push(std::stod(s));
        }
    }

    std::cout << "Result is " << std::endl;
    std::cout << values.top() << std::endl;

    return EXIT_SUCCESS;
}

int main2()
{
    std::string text("abc def");
    std::regex pat{"\\s+"};

    std::smatch matches;
    if (std::regex_search(text.cbegin(), text.cend(), matches, pat))
    {
        std::cout << "True" << std::endl;
        std::cout << "Start pos: " << matches.position(0) << std::endl;
        std::cout << "matched: " << matches[0].str() << std::endl;
    }

    std::smatch matches2;
    if (std::regex_match(text, matches2, pat))
        std::cout << "Start pos2: " << matches2.position(0) << std::endl;

    if (std::regex_match ("subject", std::regex("(sub)(.*)") ))
        std::cout << "string literal matched\n";

    std::string s ("subject");
    std::regex e ("(sub)");
    if ( std::regex_match ( s.cbegin(), s.cend(), matches2, e ) )
        std::cout << "range matched: " << matches2[0].str() << std::endl;
    return EXIT_SUCCESS;
}