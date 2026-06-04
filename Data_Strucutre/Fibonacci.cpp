#include <iostream>
using namespace std;
int main(){
    int sum=0;
    int prev1=0;
    int prev2=1;
    for(int i = 1 ; i<=5; i++){
        sum =prev1+prev2;
        cout<<sum<<"\t";
        prev1=prev2;
        prev2=sum;
    }

}