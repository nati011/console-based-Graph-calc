
/*
    This header file is an expression parser that uses the SHUNTING YARD ALGORITHM BY EDGAR DIJKSTRA.
*/

#ifndef MATHPARSER_H_INCLUDED
#define MATHPARSER_H_INCLUDED



#endif // MATHPARSER_H_INCLUDED
#include <bits/stdc++.h>

using namespace std;

int precedence(char);
int applyOp(int, int, char);
double Evaluate(string);
string substitute(string, string, string);

// Function to find precedence of operators.
int precedence(char op)
{
    if(op == '+'||op == '-')
        return 1;

    if(op == '*'||op == '/')
        return 2;

    return 0;
}

// Function to perform arithmetic operations.
int applyOp(int a, int b, char op)
{
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}

// Function that returns value of
// expression after evaluation.
double Evaluate(string tokens)
{
    int i,k=1;

    // stack to store integer values.
    stack <double> values;

    // stack to store operators.
    stack <char> ops;

    for(i = 0; i < tokens.length(); i++){

        // Current token is a whitespace,
        // skip it.
        if(tokens[i] == ' ')
            continue;

        // Current token is an opening
        // brace, push it to 'ops'
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }

        // Current token is a number, push
        // it to stack for numbers.
        else if(isdigit(tokens[i]))
        {
            int val = 0;

            // There may be more than one
            // digits in number.
            while(i < tokens.length() && isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }
            if(i<tokens.length() && tokens[i] == '.')
            {
                i++;
                while(i < tokens.length() && isdigit(tokens[i]))
                {
                   val += (tokens[i]-'0')/(10*k);
                   k++;i++;
                }
            }


            values.push(val);

            // right now the i points to
            // the character next to the digit,
            // since the for loop also increases
            // the i, we would skip one
            //  token position; we need to
            // decrease the value of i by 1 to
            // correct the offset.
              i--;
        }

        // Closing brace encountered, solve
        // entire brace.
        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // pop opening brace.
            if(!ops.empty())
               ops.pop();
        }

        // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            while(!ops.empty() && precedence(ops.top())
                                >= precedence(tokens[i])){
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }

}
//This function substitutes the variables in expression to the values of argument x
//input: value x
//output: expression
/*string substitute(string data, string toSearch, string replaceStr)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while( pos != std::string::npos)
    {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos =data.find(toSearch, pos + replaceStr.size());
    }
    return data;
}
*/
string substitute(string in_expression, char variable, double val)
{
	string out_expression;

	for(int i=0; i<in_expression.length(); i++)
	{
		if(in_expression[i] == variable)
			out_expression+=to_string(val);
		else
			out_expression+=in_expression[i];
	}
	return out_expression;
}
