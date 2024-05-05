#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include <algorithm>

// Yuuji Kobayashi
// CWID: 886294727

class Stack
{
    private:
        std::vector<std::pair<char, int>> paren_stack;

    void push(char ch, int index) {
        paren_stack.push_back(std::make_pair(ch, index));
    }

    void pop() {
        if (!paren_stack.empty()) {
            paren_stack.pop_back();
        }
    }

    std::pair<char, int> top() {
        if (!paren_stack.empty()) {
            return paren_stack.back();
        }
        return std::make_pair('\0', -1);
    }

    bool isEmpty() {
        return paren_stack.empty();
    }

    bool isOpen(char ch) {
        return ch == '(' || ch == '[' || ch == '{';
    }

    bool isClose(char ch) {
        return ch == ')' || ch == ']' || ch == '}';
    }

    bool isMatch(char open, char close) {
        return (open == '(' && close == ')') ||
               (open == '[' && close == ']') ||
               (open == '{' && close == '}');
    }
    public:
    void validPara(const std::string& expression) {
        for (int i = 0; i < expression.length(); ++i) {
            char ch = expression[i];
            if (isOpen(ch)) {
                push(ch, i);
            } else if (isClose(ch)) {
                if (!isEmpty() && isMatch(top().first, ch)) {
                    pop();
                } else {
                    std::cout << "invalid" << std::endl;
                    return;
                }
            }
        }
        std::cout << (isEmpty() ? "valid" : "invalid") << std::endl;
    }

    int indexError(const std::string& expression) {
        for (int i = 0; i < expression.length(); ++i) {
            char ch = expression[i];
            if (isOpen(ch)) {
                push(ch, i);
            } else if (isClose(ch)) {
                if (!isEmpty() && isMatch(top().first, ch)) {
                    pop();
                } else {
                    return i;
                }
            }
        }
        return isEmpty() ? -1 : top().second;
    }

    void minPara(const std::string& expression) {
    int count = 0;
    for (int i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isOpen(ch)) {
            push(ch, i);
        } else if (isClose(ch)) {
            if (!isEmpty() && isMatch(top().first, ch)) {
                pop();
            } else {
                count++; // Count unmatched closing parenthesis
                continue;
            }
        }
    }
    count += paren_stack.size();
    std::cout << count << std::endl;
}

    void scorePara(const std::string& expression) {
    int score = 0;
    for (int i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isOpen(ch)) {
            push(ch, i);
        } else if (isClose(ch)) {
            if (!isEmpty() && isMatch(top().first, ch)) {
                pop();
                score++; // Increment score for a valid match
            } else {
                continue;
            }
        }
    }
        std::cout << score << std::endl;
    }
};

class Queue
{
    private:
        std::vector<std::string> buffer;

    std::string reverse(const std::string& s) {
        std::string reversed = s;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }
    public:
    void enqueue(const std::string& message) {
        int length = message.length();
        for (int i = 0; i < length; i += 8) {
            std::string chunk = message.substr(i, std::min(8, length - i));
            buffer.push_back(reverse(chunk));
        }
    }

    void processMsg() {
        std::string fullMessage;
        while (!buffer.empty()) {
            std::string chunk = buffer.front();
            buffer.erase(buffer.begin());
            fullMessage += reverse(chunk);
        }
        std::cout << fullMessage << std::endl;
    }
};

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