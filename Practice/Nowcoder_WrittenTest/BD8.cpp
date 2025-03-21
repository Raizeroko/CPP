#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
    string input;
    while(cin >> input);
    stack<char> st;
    for(auto ch: input){
        if(ch == ']' && !st.empty() && st.top() == '[')
        {
            st.pop();
        }
        else
        {
            st.push(ch);
        }
    }
    int left = 0;
    int right = 0;
    while(!st.empty()){
        char tmp = st.top();
        st.pop();
        if(tmp == '[') left++;
        else right++;
    }
    input.insert(0, right, '[');
    input.insert(input.size(), left, ']');
    cout<<input;

}
// 64 位输出请用 printf("%lld")