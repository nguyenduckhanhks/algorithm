#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

template < typename Type > std::string to_str (const Type & t)
{
  std::ostringstream os;
  os << t;
  return os.str ();
}

int GetPriority(string ope)
{
    if(ope == "/" || ope == "*") return 2;
    else if(ope == "+" || ope == "-") return 1;
    return 0;
}

int IsOpe(string ope)
{
    if(GetPriority(ope) == 0)
    {
        if(ope == "(" || ope == ")") return 0;
        else return 1;
    }
    return 2;
}

vector<string> CaculationToPostfix(string caculation)
{
    vector<string> Output;
    vector<string> Stack;
    string extra = "";
    for(int i = 0; i < caculation.length(); i++)
    {
        string s(1, caculation[i]);
        if(GetPriority(s) == 0 && IsOpe(s) == 1)
        {
            extra = extra + caculation[i];
        }

        if(GetPriority(s) != 0)
        {
            if(extra != "")
            {
                Output.push_back(extra);
                extra = "";
            }

            if(Stack.size() == 0) Stack.push_back(s);
            else if(GetPriority(Stack.back()) > GetPriority(s))
            {
                Output.push_back(Stack.back());
                Stack.pop_back();
                Stack.push_back(s);
            }
            else Stack.push_back(s);
        }

        if(GetPriority(s) == 0 && IsOpe(s) == 0)
        {
            if(extra != "")
            {
                Output.push_back(extra);
                extra = "";
            }


            if(s == "(") Stack.push_back(s);
            else if(s == ")")
            {
                while(Stack.back() != "(")
                {
                    Output.push_back(Stack.back());
                    Stack.pop_back();
                }
                Stack.pop_back();
            }
        }
    }

    while(Stack.empty() == false)
    {
        Output.push_back(Stack.back());
        Stack.pop_back();
    }

    return Output;
}

float ConvertStringToDouble(string str)
{
    char* s = new char(str.length()+1);
    for(int i = 0; i <= str.length(); i++) s[i] = str[i];
    return atof(s);
}

float Caculate(vector<string> postfix)
{
    vector<string>  total;
    for(int i = 0; i < postfix.size(); i++)
    {
        if(GetPriority(postfix[i]) == 0)
        {
            total.push_back(postfix[i]);
        }
        else
        {
            float a = ConvertStringToDouble(total.back());
            total.pop_back();
            float b = ConvertStringToDouble(total.back());
            total.pop_back();
            float c;
            if(postfix[i] == "/") c = b/a;else
            if(postfix[i] == "*") c = b*a;else
            if(postfix[i] == "+") c = b+a;else
            if(postfix[i] == "-") c = b-a;
            total.push_back(to_str(c));
        }
    }
    return ConvertStringToDouble(total.back());
}

int main()
{
    string caculation;
    cin >> caculation;
    vector<string> s = CaculationToPostfix(caculation);
    cout << endl << Caculate(s);
}
