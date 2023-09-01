
#ifndef NTL_vec_c_RR__H
#define NTL_vec_c_RR__H

#include <NTL/vector.h>
#include<NTL/c_RR.h>
#include<NTL/vec_RR.h>

NTL_OPEN_NNS


typedef Vec<c_RR> vec_c_RR;

void do_print(const vec_c_RR& a, int prec = -1);

// add operator
void add(vec_c_RR& x, const vec_c_RR& a, const vec_c_RR& b);
inline vec_c_RR add(const vec_c_RR &a,const vec_c_RR &b){
   vec_c_RR x; add(x,a,b); return x;
}

// sub operator
void sub(vec_c_RR& x, const vec_c_RR& a, const vec_c_RR& b);
inline vec_c_RR sub(const vec_c_RR &a,const vec_c_RR &b){
   vec_c_RR x; sub(x,a,b); NTL_OPT_RETURN(vec_c_RR, x);
}

// mul operator
void mul(vec_c_RR& x, const vec_c_RR& a, double b);
inline vec_c_RR mul(const vec_c_RR &a,double b){
   vec_c_RR x; mul(x,a,b); NTL_OPT_RETURN(vec_c_RR, x);
}

void mul(vec_c_RR& x, const vec_c_RR& a, const RR& b);
inline vec_c_RR mul(const vec_c_RR &a,const RR &b){
   vec_c_RR x; mul(x,a,b); NTL_OPT_RETURN(vec_c_RR, x);
}

void mul(vec_c_RR& x, const vec_c_RR& a, const c_RR& b);
inline vec_c_RR mul(const vec_c_RR &a,const c_RR &b){
   vec_c_RR x; mul(x,a,b);  NTL_OPT_RETURN(vec_c_RR, x);
}

void SetReal(vec_c_RR& x, const vec_RR& a);
inline vec_c_RR SetReal(const vec_RR &a){
   vec_c_RR x; SetReal(x,a); NTL_OPT_RETURN(vec_c_RR, x);
}

void SetImag(vec_c_RR& x, const vec_RR& a);
inline vec_c_RR SetImag(const vec_RR &a){
   vec_c_RR x; SetImag(x,a);NTL_OPT_RETURN(vec_c_RR, x);
}

void GetReal(vec_RR& x, const vec_c_RR& a);
inline vec_RR GetReal(const vec_c_RR &a){
   vec_RR x; GetReal(x,a); NTL_OPT_RETURN(vec_RR, x);
}

void GetImag(vec_RR& x, const vec_c_RR& a);
inline vec_RR GetImag(const vec_c_RR &a){
   vec_RR x; GetImag(x,a);NTL_OPT_RETURN(vec_RR, x);
}


void clear(vec_c_RR& x);

void negate(vec_c_RR& x, const vec_c_RR& a);


void InnerProduct(c_RR& x, const vec_c_RR& a, const vec_c_RR& b);

inline c_RR InnerProduct(const vec_c_RR& a, const vec_c_RR& b){
   c_RR x; InnerProduct(x,a,b); NTL_OPT_RETURN(c_RR, x);
}

long IsZero(const vec_c_RR& a);

void VectorCopy(vec_c_RR& x, const vec_c_RR& a, long n);
inline vec_c_RR VectorCopy(const vec_c_RR& a, long n)
   { vec_c_RR x; VectorCopy(x, a, n); NTL_OPT_RETURN(vec_c_RR, x); }
 


vec_c_RR operator+(const vec_c_RR& a, const vec_c_RR& b);
vec_c_RR operator-(const vec_c_RR& a, const vec_c_RR& b);
vec_c_RR operator-(const vec_c_RR& a);

inline vec_c_RR operator*(const vec_c_RR& a, const c_RR& b){ 
   vec_c_RR x; mul(x, a, b); NTL_OPT_RETURN(vec_c_RR, x); 
}

inline vec_c_RR operator*(const vec_c_RR& a, double b){ 
   vec_c_RR x; mul(x, a, b); NTL_OPT_RETURN(vec_c_RR, x); 
}

inline vec_c_RR operator*(const vec_c_RR& a, RR b){ 
   vec_c_RR x; mul(x, a, b); NTL_OPT_RETURN(vec_c_RR, x); 
}

// assignment operator notation:

inline vec_c_RR& operator+=(vec_c_RR& x, const vec_c_RR& a)
{ 
   add(x, x, a);
   return x;
}

inline vec_c_RR& operator-=(vec_c_RR& x, const vec_c_RR& a)
{ 
   sub(x, x, a);
   return x;
}

inline vec_c_RR& operator*=(vec_c_RR& x, const c_RR& a)
{ 
   mul(x, x, a);
   return x;
}

inline vec_c_RR& operator*=(vec_c_RR& x, double a)
{ 
   mul(x, x, a);
   return x;
}

inline vec_c_RR& operator*=(vec_c_RR& x, const RR & a)
{ 
   mul(x, x, a);
   return x;
}

void random(vec_c_RR& x, long n,double start = -1,double end = 1);
inline vec_c_RR random_vec_c_RR(long n,double start = -1,double end = 1){
   vec_c_RR x;random(x, n,start,end);return x;
}

void RoundPrec(vec_c_RR& x, const vec_c_RR& a, long p=100);
inline vec_c_RR RoundPrec(const vec_c_RR& a, long p=100) {
   vec_c_RR x;
   RoundPrec(x, a, p);
   return x;
}

void ConvPrec(vec_c_RR& x, const vec_c_RR& a, long p=100);
inline vec_c_RR ConvPrec(const vec_c_RR& a, long p=100) {
   vec_c_RR x;
   ConvPrec(x, a, p);
   return x;
}

// N = M >> 1 ; M is the degree of poly
void RootOfUnit_vec(vec_c_RR &,int N);
inline vec_c_RR RootOfUnit_vec(int N) {vec_c_RR x;RootOfUnit_vec(x,N);return x;}

NTL_CLOSE_NNS

#endif
