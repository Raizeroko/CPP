#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<vector>
using namespace std;

//参考
int main()
{
	int n;
	cin >> n;
	//注意这里多给了一个值，是处理越界的情况的比较
	vector<int> a;
	a.resize(n + 1);
	//令边界的下一个为0
	a[n] = 0;
	//读入数组
	int i = 0;
	for (i = 0; i < n; ++i)
		cin >> a[i];
	i = 0;
	int count = 0;
	while (i < n)
	{
		 //非递减子序列
		if (a[i] < a[i + 1])
		{
			while (i < n && a[i] <= a[i + 1])
				i++;
			count++;
			i++;
		}
		else if (a[i] == a[i + 1])
		{
			i++;
		}
		else // 非递增子序列
		{
			while (i < n && a[i] >= a[i + 1])
				i++;
			count++;
			i++;
		}
	}
	cout << count << endl;
	return 0;
}


#include<iostream>
#include<vector>
using namespace::std;

int main()
{
    int n;
    vector<int> num(40);
    cin >> n;
    if (n == 0)
    {
        cout << 0;
        return 0;
    }
    else if (n <= 2)
    {
        cout << 1;
        return 0;

    }
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
        cout << num[i];
    }
    int ret = 1;
    int flag = 0;

    for (int cur = 0; cur < n - 1; cur++)
    {
        找递增或递减
        if (flag == 0)
        {
            if (num[cur] > num[cur + 1]) //递减
            {
                flag = -1;
            }
            else if (num[cur] < num[cur + 1]) //递增
            {
                flag = 1;
            }
            else
            {
                continue;
            }
        }
        if (flag == -1 && num[cur] < num[cur + 1])
        {
            ret += 1;
            flag = 0;
        }
        else if (flag == 1 && num[cur] > num[cur + 1])
        {
            ret += 1;
            flag = 0;
        }
    }
    cout << ret;
    return 0;
}


//
#include<iostream>
#include<string>
using namespace::std;

int main()
{
    string s1;
    getline(cin, s1);
    if (s1.size() == 0)
    {
        cout << "";
        return 0;
    }
    string s2;
    //cout<<s2.size();
    int cur = s1.size() - 1;

    while (cur >= 0)
    {
        //找空格
        int wordlength = 0;
        while (cur >= 0 && s1[cur] != ' ')
        {
            cur--;
            wordlength++;

        }
        s2.append(s1, cur + 1, wordlength);
        s2 += ' ';
        cur--;
    }
    s2.pop_back();
    cout << s2;
    return 0;
}