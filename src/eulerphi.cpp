#include <iostream>

using namespace std;


int eulerphi(int n){
  int ret=n;
  for(int i=2;i*i<=n;i++) if(n%i==0){
    while(n%i==0) n/=i;
    ret = ret/i*(i-1);
  }
  if(n>1) ret = ret/n*(n-1);
  return ret;
}

int main(){
  int n;cin >>n;
  return eulerphi(n);
}
