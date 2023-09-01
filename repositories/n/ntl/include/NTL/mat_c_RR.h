
#ifndef NTL_mat_c_RR__H
#define NTL_mat_c_RR__H

#include <NTL/matrix.h>
#include <NTL/vec_vec_c_RR.h>
#include <NTL/mat_RR.h>

NTL_OPEN_NNS

typedef Mat<c_RR> mat_c_RR;


void add(mat_c_RR& X, const mat_c_RR& A, const mat_c_RR& B); 
void sub(mat_c_RR& X, const mat_c_RR& A, const mat_c_RR& B); 
void negate(mat_c_RR& X, const mat_c_RR& A);
void mul(mat_c_RR& X, const mat_c_RR& A, const mat_c_RR& B); 
void mul(vec_c_RR& x, const mat_c_RR& A, const vec_c_RR& b); 
void mul(vec_c_RR& x, const vec_c_RR& a, const mat_c_RR& B); 
void mul(mat_c_RR& X, const mat_c_RR& A, const c_RR& b);
void mul(mat_c_RR& X, const mat_c_RR& A, const RR& b);
void mul(mat_c_RR& X, const mat_c_RR& A, double b);

inline void mul(mat_c_RR& X, const RR& a, const mat_c_RR& B)
   { mul(X, B, a); }

inline void mul(mat_c_RR& X, double a, const mat_c_RR& B)
   { mul(X, B, a); }

void ident(mat_c_RR& X, int n); 
inline mat_c_RR ident_mat_c_RR(int n)
   { mat_c_RR X; ident(X, n); NTL_OPT_RETURN(mat_c_RR, X); }

void ident(mat_c_RR& X, long n); 
inline mat_c_RR ident_mat_c_RR(long n)
   { mat_c_RR X; ident(X, n); NTL_OPT_RETURN(mat_c_RR, X); }

void determinant(c_RR& d, const mat_c_RR& A);
long IsIdent(const mat_c_RR& A, long n);
void transpose(mat_c_RR& X, const mat_c_RR& A);
void solve(c_RR& d, vec_c_RR& X,
           const mat_c_RR& A, const vec_c_RR& b);

inline void sqr(mat_c_RR& X, const mat_c_RR& A)
   { mul(X, A, A); }

inline mat_c_RR sqr(const mat_c_RR& A)
   { mat_c_RR X; sqr(X, A); NTL_OPT_RETURN(mat_c_RR, X); }

void inv(mat_c_RR& X, const mat_c_RR& A);

inline mat_c_RR inv(const mat_c_RR& A)
   { mat_c_RR X; inv(X, A); NTL_OPT_RETURN(mat_c_RR, X); }

void power(mat_c_RR& X, const mat_c_RR& A, const ZZ& e);
inline mat_c_RR power(const mat_c_RR& A, const ZZ& e)
   { mat_c_RR X; power(X, A, e); NTL_OPT_RETURN(mat_c_RR, X); }

inline void power(mat_c_RR& X, const mat_c_RR& A, long e)
   { power(X, A, ZZ_expo(e)); }
inline mat_c_RR power(const mat_c_RR& A, long e)
   { mat_c_RR X; power(X, A, e); NTL_OPT_RETURN(mat_c_RR, X); }


void SetReal(mat_c_RR& X, const mat_RR& A);
inline mat_c_RR SetReal(const mat_RR& A)
   { mat_c_RR X; SetReal(X, A); NTL_OPT_RETURN(mat_c_RR, X); }
void SetImag(mat_c_RR& X, const mat_RR& A);
inline mat_c_RR SetImag(const mat_RR& A)
   { mat_c_RR X; SetImag(X, A); NTL_OPT_RETURN(mat_c_RR, X); }


void diag(mat_c_RR& X, long n, const c_RR& d);
inline mat_c_RR diag(long n, const c_RR& d)
   { mat_c_RR X; diag(X, n, d); NTL_OPT_RETURN(mat_c_RR, X); }

long IsDiag(const mat_c_RR& A, long n, const c_RR& d);


// miscellaneous:

c_RR determinant(const mat_c_RR& a);
// functional variant of determinant

inline mat_c_RR transpose(const mat_c_RR & a)
   { mat_c_RR x; transpose(x, a); NTL_OPT_RETURN(mat_c_RR, x); }


void clear(mat_c_RR& a);
// x = 0 (dimension unchanged)

long IsZero(const mat_c_RR& a);
// test if a is the zero matrix (any dimension)


// operator notation:

mat_c_RR operator+(const mat_c_RR& a, const mat_c_RR& b);
mat_c_RR operator-(const mat_c_RR& a, const mat_c_RR& b);
mat_c_RR operator*(const mat_c_RR& a, const mat_c_RR& b);

mat_c_RR operator-(const mat_c_RR& a);


// matrix/vector multiplication:

vec_c_RR operator*(const mat_c_RR& a, const vec_c_RR& b);

vec_c_RR operator*(const vec_c_RR& a, const mat_c_RR& b);



// matrix/scalar multiplication:

inline mat_c_RR operator*(const mat_c_RR& a, const c_RR& b)
   { mat_c_RR x; mul(x, a, b); NTL_OPT_RETURN(mat_c_RR, x); }

inline mat_c_RR operator*(const mat_c_RR& a, double b)
   { mat_c_RR x; mul(x, a, b); NTL_OPT_RETURN(mat_c_RR, x); }

inline mat_c_RR operator*(const RR& a, const mat_c_RR& b)
   { mat_c_RR x; mul(x, a, b); NTL_OPT_RETURN(mat_c_RR, x); }

inline mat_c_RR operator*(double a, const mat_c_RR& b)
   { mat_c_RR x; mul(x, a, b); NTL_OPT_RETURN(mat_c_RR, x); }




// assignment operator notation:

inline void SetReal(mat_c_RR& a, const mat_RR& real);

inline void SetImag(mat_c_RR& a, const mat_RR& imag);

inline mat_RR GetReal(const mat_c_RR& a);

inline mat_RR GetImag(const mat_c_RR& a);

inline mat_c_RR& operator+=(mat_c_RR& x, const mat_c_RR& a)
{
   add(x, x, a);
   return x;
}   

inline mat_c_RR& operator-=(mat_c_RR& x, const mat_c_RR& a)
{
   sub(x, x, a);
   return x;
}   


inline mat_c_RR& operator*=(mat_c_RR& x, const mat_c_RR& a)
{
   mul(x, x, a);
   return x;
}   

inline mat_c_RR& operator*=(mat_c_RR& x, const RR& a)
{
   mul(x, x, a);
   return x;
}   

inline mat_c_RR& operator*=(mat_c_RR& x, double a)
{
   mul(x, x, a);
   return x;
}   
   

inline vec_c_RR& operator*=(vec_c_RR& x, const mat_c_RR& a)
{
   mul(x, x, a);
   return x;
}

void random(mat_c_RR& x, long n, long m,double start = -1,double end = 1);
inline mat_c_RR random_mat_c_RR(long n, long m,double start = -1,double end = 1){
   mat_c_RR x;random(x, n, m,start,end);return x;
}

void RoundPrec(mat_c_RR &x,const mat_c_RR& a, long p=100);
inline mat_c_RR RoundPrec(const mat_c_RR& a, long p=100){
   mat_c_RR x;RoundPrec(x,a, p);return x;
}

void ConvPrec(mat_c_RR &x,const mat_c_RR& a, long p=100);
inline mat_c_RR ConvPrec(const mat_c_RR& a, long p=100){
   mat_c_RR x;ConvPrec(x,a, p);return x;
}

void vandermonde(mat_c_RR& V, long N);
inline mat_c_RR vandermonde(long N){
   mat_c_RR V;vandermonde(V, N);return V;
}

NTL_CLOSE_NNS


#endif
