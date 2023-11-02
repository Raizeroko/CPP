#define _CRT_SECURE_NO_WARNINGS 1

//BM18
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int i = 0;
        int j = array[0].size() - 1;
        //cout << i << ' ' << j;
        while (i < array.size() && j >= 0)
        {
            if (target < array[i][j])
            {
                j--;
            }
            else if (target > array[i][j])
            {
                i++;
            }
            else
            {
                return true;
            }
            //cout<< array[i][j] << ' ';
        }
        return false;
    }
};


//旋转数组的最小数字
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int left = 0;
        int right = rotateArray.size() - 1;
        int mid = (left + right) / 2;
        //cout << rotateArray[left] << ' ' << rotateArray[mid] << " " << rotateArray[right];
        cout << left << ' ' << mid << " " << right;

        if (rotateArray[left] == rotateArray[right] && rotateArray[left] == rotateArray[mid])
        {

            for (int i = 1; i < rotateArray.size(); i++)
            {
                if (rotateArray[i] < rotateArray[i - 1])
                {
                    return rotateArray[i];
                }
            }
            return rotateArray[0];
        }

        while (left < right)
        {
            //未旋转
            if (rotateArray[left] < rotateArray[right])
            {
                mid = left;
                break;
            }
            //相邻
            if (right - left == 1)
            {
                if (rotateArray[left] > rotateArray[right])
                {
                    mid = right;
                    break;
                }
                else
                {
                    mid = left;
                    break;
                }
            }
            //不相邻
            if (rotateArray[mid] >= rotateArray[left])
            {
                left = mid;
            }
            else
            {
                right = mid;
            }

            mid = (left + right) / 2;
        }
        return rotateArray[mid];
    }
};
//改进
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if (rotateArray.empty())
        {
            return 0;
        }
        int left = 0;
        int right = rotateArray.size() - 1;
        int mid = 0;
        while (rotateArray[left] >= rotateArray[right])
        {
            //左右相邻
            if (right - left == 1)
            {
                return rotateArray[right];
            }

            mid = (left + right) / 2;
            //无法判别
            if (rotateArray[left] == rotateArray[right] &&
                rotateArray[left] == rotateArray[mid])
            {
                for (int i = 1; i < rotateArray.size(); i++)
                {
                    if (rotateArray[i] < rotateArray[i - 1])
                    {
                        return rotateArray[i];
                    }
                }
            }
            //正常情况
            if (rotateArray[mid] >= rotateArray[left])
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }
        return rotateArray[mid];
    }
};


//二进制中1的个数
class Solution {
public:
    int  NumberOf1(int n) {
        int sum = 0;
        for (int i = 0; i < 32; i++)
        {
            cout << (1 << i) << ' ';
            if ((n >> i) & 1 == 1)
            {
                sum += 1;
            }
        }
        return sum;
    }
};
//改进


//调整数组顺序使奇数位于偶数前面
class Solution {
public:
    void reOrderArray(vector<int>& array) {
        //int i = 0;
        int oddnum = 0;
        for (int i = 0; i < array.size(); i++)
        {
            //奇数保存
            int tmp = 0;
            if (array[i] & 1)
            {
                tmp = array[i];
                //将该奇数前面的偶数向后移动一位
                int j = i;
                while (j > oddnum)
                {
                    array[j] = array[j - 1];
                    j--;
                }
                //将保存的奇数放到移动出来的空位上
                array[oddnum++] = tmp;
            }
        }
    }
};

//数组中出现次数超过一半的数
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        sort(numbers.begin(), numbers.end());
        return numbers[numbers.size() / 2];
    }
};