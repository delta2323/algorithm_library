#include <iostream>

using namespace std;

template <int mod>
class MODINT{
  typedef long long ll;
private:
  static const int INF = 10000000;
  int val;  
public:
  MODINT<mod> ():val(0){};
  MODINT<mod> (int a):val((a+mod)%mod){};
  MODINT<mod> (const MODINT<mod>& a):val(a.val){};
  inline MODINT<mod> operator+= (MODINT<mod> a){
    return (val + a.val+mod)%mod;
  }
  inline MODINT<mod> operator+= (int a){
    return (val + a+mod)%mod;
  }
  inline MODINT<mod> operator-= (MODINT<mod> a){
    return (val - a.val + mod)%mod;
  }
  inline MODINT<mod> operator-= (int a){
    return (val - a + mod)%mod;
  }
  inline MODINT<mod> operator*= (MODINT<mod> a){
    return ((ll)val * a.val + mod)%mod;
  }
  inline MODINT<mod> operator*= (int a){
    return ((ll)val * a + mod)%mod;
  }
  inline MODINT<mod> operator+(MODINT<mod> a){
    return (*this)+=a;
  }
  inline MODINT<mod> operator-(MODINT<mod> a){
    return (*this)-=a;
  }
  inline MODINT<mod> operator*(MODINT<mod> a){
    return (*this)*=a;
  }
  inline MODINT<mod> pow(int r){
    if(r == 0) return 1;
    int init = r & 1 ? val : 1;
    return this->pow(r/2) * this->pow(r/2) * init;
  }
  inline MODINT<mod> inv(){
    return pow(mod-2);
  }
  inline MODINT<mod> operator/= (MODINT<mod> a){
    if(a.val == 0) return INF;
    return (val * a.inv());
  }
  inline MODINT<mod> operator/(MODINT<mod> a){
    return (*this)/=a;
  }
  int print(){
    return val;
  }
};


int main(){
  const int mod = 5;
  MODINT<mod> a(2), b, c(a);
  a.operator+(c);
  cout.operator<<(mod);
  
  //a.operator<<(cout);
  
}
