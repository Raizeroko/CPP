//参数解析
#include<iostream>
#include<string>
#include<stack>
#include<vector>

using namespace::std;

int main()
{
    string s1;
    getline(cin, s1);
    stack<char> v1;
    vector<string> output;
    int fast = 0, slow = 0;
    int flag = 0;

    while (fast < s1.size())
    {
        if (v1.empty() && s1[fast] == '"')
        {
            v1.push('"');
            //cout<<v1.top()<<'\n';
            fast++;
            continue;
        }
        if (!v1.empty() && s1[fast] == '"')
        {
            //cout<<v1.top();
            v1.pop();
            flag = 1;
            fast++;
            continue;
        }
        if (v1.empty() && s1[fast] == ' ')
        {
            if (flag == 0)
            {
                string tmp = "";
                tmp.append(s1, slow + flag, fast - slow - flag);
                output.push_back(tmp);
            }
            else
            {
                string tmp = "";
                tmp.append(s1, slow + flag, fast - slow - 2);
                output.push_back(tmp);
            }
            fast++;
            slow = fast;
            flag = 0;
        }
        else
        {
            fast++;
        }
    }
    if (fast != slow && flag == 0)
    {
        string tmp = "";
        tmp.append(s1, slow, fast - slow);
        output.push_back(tmp);
    }
    else if(fast != slow && flag == 1)
    {
        string tmp = "";
        tmp.append(s1, slow + flag, fast - slow - 2);
        output.push_back(tmp);
    }
    cout << output.size() << '\n';
    for (size_t i = 0; i < output.size(); i++)
    {
        cout << output[i] << '\n';
    }
    return 0;
}

//跳石板
#include<iostream>
#include<vector>
#include<cmath> 

using namespace::std;

void divisorNum(int n, vector<int>& divNum)
{
    for (int i = 2; i <= sqrt((double)n); i++)
    {
        if (n % i == 0)
        {
            divNum.push_back(i);
            if (n / i != i)
                divNum.push_back(n / i);
        }
    }
}

int Jump(int n, int m)
{
    vector<int> stepNum(m + 1, 0);
    stepNum[n] = 1;
    for (size_t i = n; i <= m; i++)
    {
        vector<int> divNum;
        if (stepNum[i] == 0)
        {
            continue;
        }
        divisorNum(i, divNum);
        for (size_t j = 0; j < divNum.size(); j++)
        {
            if (divNum[j] + i <= m && stepNum[divNum[j] + i] == 0)
            {
                stepNum[divNum[j] + i] = stepNum[i] + 1;
            }
            else if (divNum[j] + i <= m)
            {
                stepNum[divNum[j] + i] = min(stepNum[divNum[j] + i], stepNum[i] + 1);
            }
        }
    }
    if (stepNum[m] == 0)
    {
        return -1;
    }
    return stepNum[m] - 1;
}

int main()
{
    int N, M;
    cin >> N >> M;
    cout << Jump(N, M) << endl;

}
