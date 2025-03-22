#include <iostream>
using namespace std;

bool IsPrime(int num){
    if(num <= 1) return false;
    for(int i = 2; i*i <= num; i++){
        if(num % i == 0){
            return false;
        }
    }
    return true;
}

int RevNum(int num){
    int rev_num = 0;
    while(num){
        rev_num = rev_num*10 + num%10;
        num /= 10;
    }
    return rev_num;
}

int main() {
    int k;
    cin >> k;
    int ret = 1;
    while(k){
        ret++;
        int rev_num = RevNum(ret);
        if(rev_num != ret && IsPrime(ret) && IsPrime(RevNum(ret))){
            k--;
        } 
    }
    cout << ret;
    return 0;
}
// 64 位输出请用 printf("%lld")