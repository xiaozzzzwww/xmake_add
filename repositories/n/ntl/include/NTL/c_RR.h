#ifndef NTL_complex_RR__H
#define NTL_complex_RR__H

#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <NTL/xdouble.h>
#include <NTL/quad_float.h>

NTL_OPEN_NNS

class c_RR {
public:
    RR real;
    RR imag;

public:
    c_RR() : real(0.0), imag(0.0) {}
    c_RR(const double a): real(conv<RR>(a)), imag(0.0) {}
    c_RR(const double a, const double b) : real(conv<RR>(a)), imag(conv<RR>(b)) {}
    c_RR(const int a):real(conv<RR>(a)),imag(0.0){}
    c_RR(const RR& a) : real(a), imag(0.0) {}
    c_RR(const RR& a, const RR& b) : real(a), imag(b) {}
    c_RR(const ZZ& a) : real(conv<RR>(a)), imag(0.0) {}
    c_RR(const ZZ& a, const ZZ& b) : real(conv<RR>(a)), imag(conv<RR>(b)) {}
    c_RR(const long a, const long b) : real(conv<RR>(a)), imag(conv<RR>(b)) {}
    c_RR(const int a, const int b) : real(conv<RR>(a)), imag(conv<RR>(b)) {}
    c_RR(const RR& a, const long b) : real(a), imag(conv<RR>(b)) {}
    c_RR(const long a, const RR& b) : real(conv<RR>(a)), imag(b) {}
    c_RR(const c_RR& a) : real(a.real), imag(a.imag) {}

    void kill() { real = 0.0; imag = 0.0; }

};

std::ostream& operator<<(NTL_SNS ostream& s, const c_RR& a);

void do_print(const c_RR& a, int prec = -1);

long IsZero(const c_RR& a);

long IsOne(const c_RR& a);

void conj(c_RR& z, const c_RR& a);
inline c_RR conj(const c_RR& a) { c_RR z; conj(z,a);  NTL_OPT_RETURN(c_RR,z); }



void SetReal(c_RR &z, const RR &a);
inline c_RR SetReal(const RR& a) { c_RR z; SetReal(z,a);  NTL_OPT_RETURN(c_RR,z); }
void SetImag(c_RR &z, const RR &a);
inline c_RR SetImag(const RR& a) { c_RR z; SetImag(z,a);  NTL_OPT_RETURN(c_RR,z); }

void GetReal(RR& z, const c_RR& a);
inline RR GetReal(const c_RR& a) { RR z; GetReal(z,a);  NTL_OPT_RETURN(c_RR,z); }
void GetImag(RR& z, const c_RR& a);
inline RR GetImag(const c_RR& a) { RR z; GetImag(z,a);  NTL_OPT_RETURN(c_RR,z); }

void negate(c_RR& z, const c_RR& a);
inline c_RR negate(const c_RR& a) { c_RR z; negate(z,a);  NTL_OPT_RETURN(c_RR,z); }

// add operator notation:
void add(c_RR& z, const c_RR& a, const c_RR& b);
inline c_RR add(const c_RR& a, const RR& b) { c_RR z; add(z,a,b);  NTL_OPT_RETURN(c_RR,z); }

void add(c_RR& z, const c_RR& a, RR b);
inline c_RR add(const c_RR& a, RR b) { c_RR z; add(z,a,b);  NTL_OPT_RETURN(c_RR,z); }


void add(c_RR& z, const c_RR& a, double b);
inline c_RR add(const c_RR& a, double b) { c_RR z; add(z,a,b);  NTL_OPT_RETURN(c_RR,z);}


inline c_RR operator+(const c_RR& a, const c_RR& b){
  c_RR z; add(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}
inline c_RR operator+(const c_RR& a, const RR& b){
  c_RR z; add(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}
inline c_RR operator+(const c_RR& a, double b){
  c_RR z; add(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}

inline c_RR operator+=(c_RR& a, const c_RR& b){
   add(a,a,b); return a;
}
inline c_RR operator+=(c_RR& a, const RR& b){
   add(a,a,b); return a;
}
inline c_RR operator+=(c_RR& a, double b){
   add(a,a,b); NTL_OPT_RETURN(c_RR,a);
}

// sub operator notation:
void sub(c_RR& z, const c_RR& a, const c_RR& b);
inline c_RR sub(const c_RR& a, const RR& b) { c_RR z; sub(z,a,b);  NTL_OPT_RETURN(c_RR,z); }

void sub(c_RR& z, const c_RR& a, double b);
inline c_RR sub(const c_RR& a, double b) { c_RR z; sub(z,a,b);  NTL_OPT_RETURN(c_RR,z); }


void sub(c_RR& z, const c_RR& a, RR b);
inline c_RR sub(const c_RR& a, RR b) { c_RR z; sub(z,a,b);  NTL_OPT_RETURN(c_RR,z); }


inline c_RR operator-(const c_RR & a){
    c_RR x;negate(x,a); return x;
}

inline c_RR operator-(const c_RR& a, const c_RR& b){
  c_RR z; sub(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}
inline c_RR operator-(const c_RR& a, const RR& b){
  c_RR z; sub(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}
inline c_RR operator-(const c_RR& a, double b){
  c_RR z; sub(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}


inline c_RR operator-=(c_RR& a, const c_RR& b){
   sub(a,a,b); return a;
}
inline c_RR operator-=(c_RR& a, const RR& b){
   sub(a,a,b); return a;
}
inline c_RR operator-=(c_RR& a, double b){
   sub(a,a,b); return a;
}

// div operator notation:

// mul operator notation:
void mul(c_RR& z, const c_RR& a, const c_RR& b);
inline c_RR mul(const c_RR& a, const RR& b) { c_RR z; mul(z,a,b);  NTL_OPT_RETURN(c_RR,z); }

void mul(c_RR& z, const c_RR& a, double b);
inline c_RR mul(const c_RR& a, double b) { c_RR z; mul(z,a,b);  NTL_OPT_RETURN(c_RR,z);}


void mul(c_RR& z, const c_RR& a, RR b);
inline c_RR mul(const c_RR& a, RR b) { c_RR z; mul(z,a,b);  NTL_OPT_RETURN(c_RR,z);}

inline c_RR operator*(const c_RR& a, const c_RR& b){
  c_RR z; mul(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}
inline c_RR operator*(const c_RR& a, const RR& b){
   c_RR z; mul(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}
inline c_RR operator*(const c_RR& a, double b){
   c_RR z; mul(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}


inline c_RR operator*=(c_RR& a, const c_RR& b){
   mul(a,a,b); return a;
}
inline c_RR operator*=(c_RR& a, const RR& b){
   mul(a,a,b); return a;
}
inline c_RR operator*=(c_RR& a, double b){
   mul(a,a,b); return a;
}


// div operator notation:
void div(c_RR& z, const c_RR& a, double b);
inline c_RR div(const c_RR& a, double b) { c_RR z; div(z,a,b);  NTL_OPT_RETURN(c_RR,z);}

void div(c_RR& z, const c_RR& a, RR b);
inline c_RR div(const c_RR& a, RR b) { c_RR z; div(z,a,b);  NTL_OPT_RETURN(c_RR,z);}


void div(c_RR& z, const c_RR& a, const c_RR& b);
inline c_RR div(const c_RR& a, const c_RR& b) { c_RR z; div(z,a,b);  NTL_OPT_RETURN(c_RR,z);}

inline c_RR operator/(const c_RR &a,const c_RR &b){
    c_RR z; div(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}

inline c_RR operator/(const c_RR &a,double b){
    c_RR z; div(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}


inline c_RR operator/(const c_RR &a,const RR & b){
    c_RR z; div(z,a,b);  NTL_OPT_RETURN(c_RR,z);
}


inline c_RR operator/=(c_RR& a, const c_RR& b){
   div(a,a,b); return a;
}
inline c_RR operator/=(c_RR& a, const RR& b){
   div(a,a,b); return a;
}
inline c_RR operator/=(c_RR& a, double b){
   div(a,a,b); return a;
}

void inv(c_RR& z, const c_RR& a);
inline c_RR inv(const c_RR& a) { c_RR z; inv(z,a);  NTL_OPT_RETURN(c_RR,z);}




inline long operator==(const c_RR& a, const c_RR& b) { return IsZero(a-b); }
inline long operator!=(const c_RR& a, const c_RR& b) { return !(a==b); }

void power(c_RR &,const c_RR &,long e);

void clear(c_RR& a);

void random(c_RR & a,double start=0.0,double end=1.0);
inline c_RR random_c_RR(double start=0.0,double end=1.0){
    c_RR x;random(x,start,end);return x;
}

void swap(c_RR& x,c_RR& y);

void abs(RR& a, const c_RR& b);
inline RR abs(const c_RR& a) { RR z; abs(z,a);  NTL_OPT_RETURN(c_RR,z);}

void sqrt(c_RR& z, const c_RR& a);
inline c_RR sqrt(const c_RR& a) { c_RR z; sqrt(z,a);  NTL_OPT_RETURN(c_RR,z);}

void RoundPrec(c_RR& z, const c_RR& a,long prec=100);
inline c_RR RoundPrec(const c_RR& a,long prec=100) { c_RR z; RoundPrec(z,a,prec);  NTL_OPT_RETURN(c_RR,z);}

void ConvPrec(c_RR& z, const c_RR& a,long prec=100);
inline c_RR ConvPrec(const c_RR& a,long prec=100) { c_RR z; ConvPrec(z,a,prec);  NTL_OPT_RETURN(c_RR,z);}


// N = M >> 1 ; M is the degree of poly
void RootOfUnit(c_RR& z, int N);
inline c_RR RootOfUnit(int N) { c_RR z; RootOfUnit(z,N); NTL_OPT_RETURN(c_RR,z);}


NTL_CLOSE_NNS

#endif
