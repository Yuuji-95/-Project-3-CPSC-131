#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include <algorithm>

// Logan Arroyo
//CWID: 884643172

// Add class Stack here
class Stack
{
    private:
        void push(std::vector<std::pair<char, int>>& a, std::pair<char, int> b)
        {
            a.push_back(b);
        }
        std::pair<char, int> top(std::vector<std::pair<char, int>>& a)
        {
            if (a.size() == 0)
            {
                return std::make_pair(NULL, NULL);
            }
            return a[a.size()-1];
        }
        void pop(std::vector<std::pair<char, int>>& a)
        {
            a.pop_back();
        }
        bool match(char a, char b)
        {
            if (a == '(' && b == ')')
            {
                return true;
            }
            else if (a == '[' && b == ']')
            {
                return true;
            }
            else if (a == '{' && b == '}')
            {
                return true;
            }
            return false;
        }
        bool isOpen(char a)
        {
            return a == '(' || a == '[' || a == '{';
        }
        bool isClose(char a)
        {
            return a == ')' || a == ']' || a == '}';
        }
    public:
        void validPara(std::string pairs)
        {
            std::vector<std::pair<char, int>> parent_stack;

            for (int i = 0; i < pairs.length(); i++)
            {
                if (pairs[i] == '(' || pairs[i] == '[' || pairs[i] == '{' || pairs[i] == ')' || pairs[i] == ']' || pairs[i] == '}')
                {
                    if (parent_stack.size() == 0)
                    {
                        push(parent_stack, std::make_pair(pairs[i], i));
                    }
                    else
                    {
                        if (match(top(parent_stack).first, pairs[i]))
                        {
                            pop(parent_stack);
                        }
                        else
                        {
                            push(parent_stack, std::make_pair(pairs[i], i));
                        }
                    }
                }
            }
            if (parent_stack.size() != 0)
            {
                std::cout<<"invalid"<<std::endl;
                return;
            }
            std::cout<<"valid"<<std::endl;
        }

        int indexError(std::string pairs)
        {
            std::vector<std::pair<char, int>> squig_stack;
            std::vector<std::pair<char, int>> hard_stack;
            std::vector<std::pair<char, int>> smooth_stack;
            std::vector<int> errors;
            for (int i = 0; i < pairs.length(); i++)
            {
                if (isOpen(pairs[i]) || isClose(pairs[i]))
                {
                    if (pairs[i] == '{' || pairs[i] == '}')
                    {
                        if (match(top(squig_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(squig_stack).second), errors.end());
                            pop(squig_stack);
                        }
                        else
                        {
                            push(squig_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                    else if (pairs[i] == '[' || pairs[i] == ']')
                    {
                        if (match(top(hard_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(hard_stack).second), errors.end());
                            pop(hard_stack);
                        }
                        else
                        {
                            push(hard_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                    else if (pairs[i] == '(' || pairs[i] == ')')
                    {
                        if (match(top(smooth_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(smooth_stack).second), errors.end());
                            pop(smooth_stack);
                        }
                        else
                        {
                            push(smooth_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                }
            }
            if (errors.size() != 0)
            {
                if (isOpen(pairs[errors[0]]))
                {
                    int pair_count = 0;
                    int first_close = -1;
                    for (int i = errors[0]+1; i < pairs.length(); i++)
                    {
                        if (isClose(pairs[i]))
                        {
                            if (first_close == -1)
                            {
                                first_close = i;
                            }
                            pair_count -= 1;
                        }
                        else if (isOpen(pairs[i]))
                        {
                            pair_count += 1;
                        }
                        //std::cout<<"DSDSDSD "<<pairs[i]<<std::endl;
                    }
                    if (pair_count < 0)
                    {
                        return first_close;
                    }
                    return pairs.length();
                }
                else if (isClose(pairs[errors[0]]))
                {
                    return errors[0];
                }
            }

            return -1;

        }

        void minPara(std::string pairs)
        {
            std::vector<std::pair<char, int>> squig_stack;
            std::vector<std::pair<char, int>> hard_stack;
            std::vector<std::pair<char, int>> smooth_stack;
            std::vector<int> errors;
            for (int i = 0; i < pairs.length(); i++)
            {
                if (isOpen(pairs[i]) || isClose(pairs[i]))
                {
                    if (pairs[i] == '{' || pairs[i] == '}')
                    {
                        if (match(top(squig_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(squig_stack).second), errors.end());
                            pop(squig_stack);
                        }
                        else
                        {
                            push(squig_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                    else if (pairs[i] == '[' || pairs[i] == ']')
                    {
                        if (match(top(hard_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(hard_stack).second), errors.end());
                            pop(hard_stack);
                        }
                        else
                        {
                            push(hard_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                    else if (pairs[i] == '(' || pairs[i] == ')')
                    {
                        if (match(top(smooth_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(smooth_stack).second), errors.end());
                            pop(smooth_stack);
                        }
                        else
                        {
                            push(smooth_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                }
            }

            std::cout<<"Min: "<<(squig_stack.size() + hard_stack.size() + smooth_stack.size())<<std::endl;
        }

        void scorePara(std::string pairs)
        {
            //std::vector<std::pair<char, int>> parent_stack;
            int score = 0;

            std::vector<std::pair<char, int>> squig_stack;
            std::vector<std::pair<char, int>> hard_stack;
            std::vector<std::pair<char, int>> smooth_stack;
            std::vector<int> errors;
            for (int i = 0; i < pairs.length(); i++)
            {
                if (isOpen(pairs[i]) || isClose(pairs[i]))
                {
                    if (pairs[i] == '{' || pairs[i] == '}')
                    {
                        if (match(top(squig_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(squig_stack).second), errors.end());
                            pop(squig_stack);
                            score++;
                        }
                        else
                        {
                            push(squig_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                    else if (pairs[i] == '[' || pairs[i] == ']')
                    {
                        if (match(top(hard_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(hard_stack).second), errors.end());
                            pop(hard_stack);
                            score++;
                        }
                        else
                        {
                            push(hard_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                    else if (pairs[i] == '(' || pairs[i] == ')')
                    {
                        if (match(top(smooth_stack).first, pairs[i]))
                        {
                            errors.erase(std::remove(errors.begin(), errors.end(), top(smooth_stack).second), errors.end());
                            pop(smooth_stack);
                            score++;
                        }
                        else
                        {
                            push(smooth_stack, std::make_pair(pairs[i], i));
                            errors.push_back(i);
                        }
                    }
                }
            }

            //int sub = (smooth_open - smooth_closed) + (brack_open - brack_closed) + (squig_open - squig_closed);
            std::cout<<"Balance: "<<score<<std::endl;
        }

};


// Add class Queue here
class Queue
{
    private:
        std::vector<std::string> queue;
        std::string pop()
        {
            auto a = queue[0];
            queue.erase(queue.begin());
            return a;
        }
        std::string reverse(std::string s)
        {
            std::string a = "";
            for (int i = s.size()-1; i >= 0; i--)
            {
                a += s[i];
            }//std::cout<<"DDDD"<<std::endl;
            return a;
        }
    public:
        void enqueue(std::string s)
        {
            int i = 0;
            int last_working_i = 0;
            for (i = 0; i < s.size(); i++)
            {
                //std::cout<<((i+1) % 8)<<std::endl;
                if ((i+1) % 8 == 0)
                {
                    queue.push_back(reverse(s.substr(i-7, (i+1) - (i-7))));
                    last_working_i = i;
                }
            }
            if (last_working_i != i)
            {
                //std::cout<<"[]"<<s.substr(i)<<"[]"<<std::endl;
                queue.push_back(reverse(s.substr(last_working_i+1)));
            }
        }
        void processMsg()
        {
            std::string fin;
            while (queue.size() != 0)
            {
                fin += reverse(pop());
            }
            std::cout<<fin<<std::endl;
        }
};

// Remove comments before testing and do not change anything in main function
int main(){
    Stack s1;
    s1.validPara("(([]))");
    s1.minPara("(([]))");
    s1.scorePara("(([]))");
    s1.validPara("(([])");
    std::cout<<s1.indexError("(([))")<<std::endl;
    s1.minPara("(([])");
    s1.validPara("(([{}))");
    std::cout<<s1.indexError("(([[}])")<<std::endl; // This should be index 7, there is a missing ) at the very beginning
    s1.minPara("(([{}))");
    s1.scorePara("(([{}))");
    std::cout<<s1.indexError("({}[]()[)")<<std::endl;
    s1.validPara("(([))");
    s1.minPara("(([))");
    std::cout<<s1.indexError("[({)]")<<std::endl;
    s1.validPara("(([{[{({})}]}]))");
    s1.minPara("(([{[{({})}]}]))");
    s1.scorePara("(([{[{({})}]}]))");
    s1.validPara("(([[{[{({})}]))");
    s1.validPara("(([[{[{({})}]}])]))");
    s1.scorePara("(([[{[{({})}]}])]))");
    std::cout<<s1.indexError("(([[{{({})]}])]))")<<std::endl;
    s1.validPara("(())");
    s1.validPara("(())");
    s1.validPara("void function(){}");
    s1.scorePara("void function(){}");
    s1.validPara("void function(");
    s1.minPara("void function(");
    s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
    s1.scorePara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
    s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}");
    s1.validPara("void function(std::string expre){if(expre){return 1;else{return 0;");
    s1.minPara("void function(std::string expre){if(expre){return 1;else{return 0;");
    std::cout<<s1.indexError("void function(std::string expre){if(expre){return 1;else{return 0;")<<std::endl;
    Queue q1;
    q1.enqueue("This is a secure message.");
    q1.processMsg();
    q1.enqueue("The product I received is damaged. What should I do?");
    q1.processMsg();
    q1.enqueue("I need assistance with setting up my new device");
    q1.processMsg();
    q1.enqueue("The website is not loading properly on my browser.");
    q1.processMsg();
    q1.enqueue("I accidentally placed the wrong order. Can it be canceled?");
    q1.processMsg();
    q1.enqueue("This is your project3. Have a happy thanksgiving!!! Hahaha");
    q1.processMsg();
    q1.enqueue("I forgot my password and can't reset it. Help, please! Do you provide technical support for mobile devices?");
    q1.processMsg();
    q1.enqueue("The software update is causing issues on my computer. The response time on your website is very slow.");
    q1.processMsg();
    return 0;
}