#ifndef MODINT_HPP_
#define MODINT_HPP_

#include <iostream>
#include <ostream>
#include <sstream>

template <int mod>
class ModInt{
  typedef long long ll;
private:
  static const int INF = 10000000;
  int val;  
public:
  ModInt<mod> ():val(0){};
  ModInt<mod> (int a):val((a+mod)%mod){};
  ModInt<mod> (const ModInt<mod>& a):val(a.val){};
  inline ModInt<mod> operator+= (const ModInt<mod>& a){
    val = (val + a.val + mod) % mod;
    return *this;
  }
  inline ModInt<mod> operator+= (int a){
    val = (val + a + mod) % mod;
    return *this;
  }
  inline ModInt<mod> operator-= (const ModInt<mod>& a){
    val = (val - a.val + mod) % mod;
    return *this;
  }
  inline ModInt<mod> operator-= (int a){
    val =  (val - a + mod) % mod;
    return *this;
  }
  inline ModInt<mod> operator*= (const ModInt<mod>& a){
    val =  ((ll)val * a.val + mod) % mod;
    return *this;
  }
  inline ModInt<mod> operator*= (int a){
    val =  ((ll)val * a + mod) % mod;
    return *this;
  }
  inline ModInt<mod> operator/= (const ModInt<mod>& a){
    if(a.val == 0) return INF;
    ModInt<mod> tmp = inv(a);
    val =  (val * tmp.val)  % mod;
    return *this;
  }

  inline int get() {
    return val;
  }

  template <int m>
  friend inline ModInt<m> pow(const ModInt<m>& a, int r);
  
  template <int m, typename _CharT, class _Traits>
  friend std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, const ModInt<m>& __x);
};

template <int mod>
inline ModInt<mod> operator+(const ModInt<mod>& a, const ModInt<mod>& b){
  ModInt<mod> tmp(a);
  tmp += b;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator+(const ModInt<mod>& a, int b){
  ModInt<mod> tmp(a);
  tmp += b;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator+(int a, const ModInt<mod>& b){
  ModInt<mod> tmp(b);
  tmp += a;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator-(const ModInt<mod>& a, const ModInt<mod>& b){
  ModInt<mod> tmp(a);
  tmp -= b;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator-(const ModInt<mod>& a, int b){
  ModInt<mod> tmp(a);
  tmp -= b;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator-(int a, const ModInt<mod>& b){
  ModInt<mod> tmp(-b);
  tmp += a;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator*(const ModInt<mod>& a, const ModInt<mod>& b){
  ModInt<mod> tmp(a);
  tmp *= b;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator*(const ModInt<mod>& a, int b){
  ModInt<mod> tmp(a);
  tmp *= b;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator*(int a, const ModInt<mod>& b){
  ModInt<mod> tmp(b);
  tmp *= a;
  return tmp;
}

template <int mod>
inline ModInt<mod> pow(const ModInt<mod>& a, int r){
  if(r == 0) return 1;
  int init = r & 1 ? a.val : 1;
  ModInt<mod> tmp(pow(a, r/2));
  return tmp * tmp * init;
}

template <int mod>
inline ModInt<mod> inv(const ModInt<mod>& a){
  return pow(a, mod-2);
}

template <int mod>
inline ModInt<mod> operator/(const ModInt<mod>& a, const ModInt<mod>& b){
  ModInt<mod> tmp(a);
  tmp/=b;
  return tmp;
}

template <int mod>
inline ModInt<mod> operator/(const ModInt<mod>& a, int b){
  ModInt<mod> tmp(a);
  tmp/=b;
  return tmp;
}

template<int mod, typename _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<<(std::basic_ostream<_CharT, _Traits>& __os, const ModInt<mod>& __x)
{
  std::basic_ostringstream<_CharT, _Traits> __s;
  __s.flags(__os.flags());
  __s.imbue(__os.getloc());
  __s.precision(__os.precision());
  __s << __x.val;
  return __os << __s.str();
}

#endif
