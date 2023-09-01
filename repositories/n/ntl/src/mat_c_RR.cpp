#include <NTL/mat_c_RR.h>
#include<NTL/mat_RR.h>


NTL_START_IMPL

  
void add(mat_c_RR& X, const mat_c_RR& A, const mat_c_RR& B)  
{  
   long n = A.NumRows();  
   long m = A.NumCols();  
  
   if (B.NumRows() != n || B.NumCols() != m)   
      LogicError("matrix add: dimension mismatch");  
  
   X.SetDims(n, m);  
  
   long i, j;  
   for (i = 1; i <= n; i++)   
      for (j = 1; j <= m; j++)  
         add(X(i,j), A(i,j), B(i,j));  
}  
  
void sub(mat_c_RR& X, const mat_c_RR& A, const mat_c_RR& B)  
{  
   long n = A.NumRows();  
   long m = A.NumCols();  
  
   if (B.NumRows() != n || B.NumCols() != m)  
      LogicError("matrix sub: dimension mismatch");  
  
   X.SetDims(n, m);  
  
   long i, j;  
   for (i = 1; i <= n; i++)  
      for (j = 1; j <= m; j++)  
         sub(X(i,j), A(i,j), B(i,j));  
}  
  
void mul_aux(mat_c_RR& X, const mat_c_RR& A, const mat_c_RR& B)  
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  
  
   if (l != B.NumRows())  
      LogicError("matrix mul: dimension mismatch");  
  
   X.SetDims(n, m);  
  
   long i, j, k;  
   c_RR acc, tmp;  
  
   for (i = 1; i <= n; i++) {  
      for (j = 1; j <= m; j++) {  
         clear(acc);  
         for(k = 1; k <= l; k++) {  
            mul(tmp, A(i,k), B(k,j));  
            add(acc, acc, tmp);  
         }  
         X(i,j) = acc;  
      }  
   }  
}  
  
  
void mul(mat_c_RR& X, const mat_c_RR& A, const mat_c_RR& B)  
{  
   if (&X == &A || &X == &B) {  
      mat_c_RR tmp;  
      mul_aux(tmp, A, B);  
      X = tmp;  
   }  
   else  
      mul_aux(X, A, B);  
}  
  
  
static
void mul_aux(vec_c_RR& x, const mat_c_RR& A, const vec_c_RR& b)  
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
  
   if (l != b.length())  
      LogicError("matrix mul: dimension mismatch");  
  
   x.SetLength(n);  
  
   long i, k;  
   c_RR acc, tmp;  
  
   for (i = 1; i <= n; i++) {  
      clear(acc);  
      for (k = 1; k <= l; k++) {  
         mul(tmp, A(i,k), b(k));  
         add(acc, acc, tmp);  
      }  
      x(i) = acc;  
   }  
}  
  
  
void mul(vec_c_RR& x, const mat_c_RR& A, const vec_c_RR& b)  
{  
   if (&b == &x || A.alias(x)) {
      vec_c_RR tmp;
      mul_aux(tmp, A, b);
      x = tmp;
   }
   else
      mul_aux(x, A, b);
}  

static
void mul_aux(vec_c_RR& x, const vec_c_RR& a, const mat_c_RR& B)  
{  
   long n = B.NumRows();  
   long l = B.NumCols();  
  
   if (n != a.length())  
      LogicError("matrix mul: dimension mismatch");  
  
   x.SetLength(l);  
  
   long i, k;  
   c_RR acc, tmp;  
  
   for (i = 1; i <= l; i++) {  
      clear(acc);  
      for (k = 1; k <= n; k++) {  
         mul(tmp, a(k), B(k,i));
         add(acc, acc, tmp);  
      }  
      x(i) = acc;  
   }  
}  

void mul(vec_c_RR& x, const vec_c_RR& a, const mat_c_RR& B)
{
   if (&a == &x) {
      vec_c_RR tmp;
      mul_aux(tmp, a, B);
      x = tmp;
   }
   else
      mul_aux(x, a, B);
}

void ident(mat_c_RR &X, int n)
{
    
    X.SetDims(n, n);  
    int i, j;  
    for (i = 0; i < n; i++)  
        for (j = 0; j < n; j++)  
            if (i == j){       
                X.put(i, j, c_RR(1,0));
            }else{
                clear(X[i][j]);  
            }
}

void ident(mat_c_RR &X, long n)
{  
   X.SetDims(n, n);  
   long i, j;  
  
   for (i = 0; i < n; i++)  
        for (j = 0; j < n; j++)  
            if (i == j){       
                X.put(i, j, c_RR(1,0));
            }else{
                clear(X[i][j]);  
            }
}

void inv(mat_c_RR& X, const mat_c_RR& A){
   long rows = A.NumRows();
   long cols = A.NumCols();
   if (rows!=cols)
      LogicError("inv: nonsquare matrix");

   if (rows == 0) {
      X.SetDims(0, 0);
      return;
   }
   mat_c_RR identity;
   ident(identity, rows);
   X.SetDims(rows, cols);
   mat_c_RR inputCopy(A);
   for (size_t i = 0; i < rows; ++i) {
        if (inputCopy[i][i] == c_RR(0.0, 0.0)) {
            for (size_t j = i + 1; j < rows; ++j) {
                if (inputCopy[j][i] != c_RR(0.0, 0.0)) {
                    for (size_t k = 0; k < cols; ++k) {
                        std::swap(inputCopy[i][k], inputCopy[j][k]);
                        std::swap(identity[i][k], identity[j][k]);
                    }
                    break;
                }
            }
        }
        
        if (inputCopy[i][i] != c_RR(0.0, 0.0)) {
            c_RR inv_pivot = 1.0 / inputCopy[i][i];
            for (size_t j = 0; j < cols; ++j) {
                inputCopy[i][j] *= inv_pivot;
                identity[i][j] *= inv_pivot;
            }
            
            for (size_t j = i + 1; j < rows; ++j) {
                c_RR factor = inputCopy[j][i];
                for (size_t k = 0; k < cols; ++k) {
                    inputCopy[j][k] -= factor * inputCopy[i][k];
                    identity[j][k] -= factor * identity[i][k];
                }
            }
        }
    }
    // 变换为对角矩阵
    for (int i = static_cast<int>(rows) - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            c_RR factor = inputCopy[j][i];
            for (size_t k = 0; k < cols; ++k) {
                inputCopy[j][k] -= factor * inputCopy[i][k];
                identity[j][k] -= factor * identity[i][k];
            }
        }
    }
   X = identity;
}

void determinant_LU(c_RR & d, const mat_c_RR& M){
    mat_c_RR matrix = M;
   size_t n = matrix.NumCols();

    // 初始化L和U矩阵
    mat_c_RR L = matrix;
    mat_c_RR U;
    U.SetDims(n, n);

    // 对角线元素为1
    for (size_t i = 0; i < n; ++i) {
        L[i][i] = c_RR(1.0, 0.0);
    }

    // 执行LU分解
    for (size_t k = 0; k < n; ++k) {
        U[k][k] = matrix[k][k];
        if(U[k][k]==c_RR())
            LogicError("this matrix' mat[k][k] is zero! ");
        for (size_t i = k + 1; i < n; ++i) {
            L[i][k] = matrix[i][k] / U[k][k];
            U[k][i] = matrix[k][i];
        }
        for (size_t i = k + 1; i < n; ++i) {
            for (size_t j = k + 1; j < n; ++j) {
                matrix[i][j] = matrix[i][j] - L[i][k] * U[k][j];
            }
        }
    }
     d = c_RR(1,0);
     for (size_t i = 0; i < U.NumCols(); ++i) {
        d *= U[i][i];
        
    }
    
}

void determinant(c_RR& d, const mat_c_RR& M){
   if (M.NumRows() != M.NumCols())
      LogicError("determinant: nonsquare matrix");
   if (M.NumRows() == 0) {
      d = 0.0;
      return;
   }
   if (M.NumRows() == 1) {
      d = M[0][0];
      return;
   }
   if (M.NumRows() == 2) {
      d = M[0][0] * M[1][1] - M[0][1] * M[1][0];
      return;
   }
   mat_c_RR M_in = M;
   determinant_LU(d, M_in);
}


c_RR determinant(const mat_c_RR& a)
   { c_RR x; determinant(x, a); NTL_OPT_RETURN(c_RR, x); }


long IsIdent(const mat_c_RR &A, long n){
   if (A.NumRows() != n || A.NumCols() != n)
      return 0;

   long i, j;

   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
         if (i != j) {
            if (!IsZero(A(i, j))) return 0;
         }
         else {
            if (!IsOne(A(i, j))) return 0;
         }

   return 1;
}
            

void transpose(mat_c_RR& X, const mat_c_RR& A)
{
   long n = A.NumRows();
   long m = A.NumCols();

   long i, j;

   if (&X == & A) {
      if (n == m)
         for (i = 1; i <= n; i++)
            for (j = i+1; j <= n; j++)
               swap(X(i, j), X(j, i));
      else {
         mat_c_RR tmp;
         tmp.SetDims(m, n);
         for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
               tmp(j, i) = A(i, j);
         X.kill();
         X = tmp;
      }
   }
   else {
      X.SetDims(m, n);
      for (i = 1; i <= n; i++)
         for (j = 1; j <= m; j++)
            X(j, i) = A(i, j);
   }
}

void solve(c_RR &d, vec_c_RR &X, const mat_c_RR &A, const vec_c_RR &b)
{
   long n = A.NumRows();

   if (n != A.NumCols() || n != b.length())
      LogicError("solve: invalid dimensions");

   if (n == 0) return;
   long i, j;
   mat_c_RR A_inv;
   inv(A_inv, A);
   determinant_LU(d, A);
   mul(X, A_inv, b);
}

void mul(mat_c_RR& X, const mat_c_RR& A, const c_RR& b)
{
   long n = A.NumRows();
   long m = A.NumCols();

   X.SetDims(n, m);

   long i, j;
   for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
         mul(X[i][j], A[i][j], b);
}

void mul(mat_c_RR &X, const mat_c_RR &A, const RR &b)
{
   long n = A.NumRows();
   long m = A.NumCols();

   X.SetDims(n, m);

   long i, j;
   for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
         mul(X[i][j], A[i][j], b);
}

void mul(mat_c_RR& X, const mat_c_RR& A, double b)
{
   long n = A.NumRows();
   long m = A.NumCols();

   X.SetDims(n, m);

   long i, j;
   for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
         mul(X[i][j], A[i][j], b);
}

void diag(mat_c_RR& X, long n, const c_RR& d)  
{  
   X.SetDims(n, n);  
   long i, j;  
  
   for (i = 1; i <= n; i++)  
      for (j = 1; j <= n; j++)  
         if (i == j)  
            X(i, j) = d;  
         else  
            clear(X(i, j));  
} 

long IsDiag(const mat_c_RR& A, long n, const c_RR& d)
{
   if (A.NumRows() != n || A.NumCols() != n)
      return 0;

   long i, j;

   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
         if (i != j) {
            if (!IsZero(A(i, j))) return 0;
         }
         else {
            if (A(i, j) != d) return 0;
         }

   return 1;
}

void negate(mat_c_RR& X, const mat_c_RR& A)
{
   long n = A.NumRows();
   long m = A.NumCols();


   X.SetDims(n, m);

   long i, j;
   for (i = 1; i <= n; i++)
      for (j = 1; j <= m; j++)
         negate(X(i,j), A(i,j));
}

long IsZero(const mat_c_RR& a)
{
   long n = a.NumRows();
   long i;

   for (i = 0; i < n; i++)
      if (!IsZero(a[i]))
         return 0;

   return 1;
}

void clear(mat_c_RR& x)
{
   long n = x.NumRows();
   long i;
   for (i = 0; i < n; i++)
      clear(x[i]);
}


mat_c_RR operator+(const mat_c_RR& a, const mat_c_RR& b)
{
   mat_c_RR res;
   add(res, a, b);
   NTL_OPT_RETURN(mat_c_RR, res);
}

mat_c_RR operator*(const mat_c_RR& a, const mat_c_RR& b)
{
   mat_c_RR res;
   mul_aux(res, a, b);
   NTL_OPT_RETURN(mat_c_RR, res);
}

mat_c_RR operator-(const mat_c_RR& a, const mat_c_RR& b)
{
   mat_c_RR res;
   sub(res, a, b);
   NTL_OPT_RETURN(mat_c_RR, res);
}


mat_c_RR operator-(const mat_c_RR& a)
{
   mat_c_RR res;
   negate(res, a);
   NTL_OPT_RETURN(mat_c_RR, res);
}


vec_c_RR operator*(const mat_c_RR& a, const vec_c_RR& b)
{
   vec_c_RR res;
   mul_aux(res, a, b);
   NTL_OPT_RETURN(vec_c_RR, res);
}

vec_c_RR operator*(const vec_c_RR& a, const mat_c_RR& b)
{
   vec_c_RR res;
   mul_aux(res, a, b);
   NTL_OPT_RETURN(vec_c_RR, res);
}

inline void SetReal(mat_c_RR &a, const mat_RR &real)
{
   a.SetDims(real.NumRows(), real.NumCols());
   for (long i = 0; i < a.NumRows(); i++)
      for (long j = 0; j < a.NumCols(); j++)
         a[i][j].real = real[i][j];
}

inline void SetImag(mat_c_RR &a, const mat_RR &imag)
{
   a.SetDims(imag.NumRows(), imag.NumCols());
   for (long i = 0; i < a.NumRows(); i++)
      for (long j = 0; j < a.NumCols(); j++)
         a[i][j].imag = imag[i][j];  
}

inline mat_RR GetReal(const mat_c_RR &a)
{
   mat_RR real;
   clear(real);
   real.SetDims(a.NumRows(), a.NumCols());
   for (long i = 0; i < a.NumRows(); i++)
      for (long j = 0; j < a.NumCols(); j++)
         real[i][j] = a[i][j].real;  
   return real;
}

inline mat_RR GetImag(const mat_c_RR &a)
{
   mat_RR imag;
   clear(imag);
   imag.SetDims(a.NumRows(), a.NumCols());
   for (long i = 0; i < a.NumRows(); i++)
      for (long j = 0; j < a.NumCols(); j++)
         imag[i][j] = a[i][j].imag;  
   return imag;
}

void random(mat_c_RR &x, long n, long m, double start, double end)
{
    clear(x);
    x.SetDims(n, m);
    for(long i=0; i<n; i++){
        for(long j=0; j<m; j++){
            random(x[i][j],start,end);
        }
    }
}

void power(mat_c_RR& X, const mat_c_RR& A, const ZZ& e)
{
   if (A.NumRows() != A.NumCols()) LogicError("power: non-square matrix");

   if (e == 0) {
      ident(X, A.NumRows());
      return;
   }

   mat_c_RR T1, T2;
   long i, k;

   k = NumBits(e);
   T1 = A;

   for (i = k-2; i >= 0; i--) {
      sqr(T2, T1);
      if (bit(e, i))
         mul(T1, T2, A);
      else
         T1 = T2;
   }

   if (e < 0)
      inv(X, T1);
   else
      X = T1;
}

void RoundPrec(mat_c_RR& x,const mat_c_RR& a, long p){
  if(&x == &a){
   
   for (long i = 0; i < a.NumRows(); i++)
   {
      for(long j =0;j<a.NumCols();j++){
         RoundPrec(x[i][j].real,a[i][j].real,p);
         RoundPrec(x[i][j].imag,a[i][j].imag,p);
      }
   }
  }else{
   x.SetDims(a.NumRows(),a.NumCols());
   for (long i = 0; i < a.NumRows(); i++)
   {
      for(long j =0;j<a.NumCols();j++){
         RoundPrec(x[i][j].real,a[i][j].real,p);
         RoundPrec(x[i][j].imag,a[i][j].imag,p);
      }
   }
  }
   
}

void ConvPrec(mat_c_RR& x,const mat_c_RR& a, long p){
  if(&x == &a){
   for (long i = 0; i < a.NumRows(); i++)
   {
      for(long j =0;j<a.NumCols();j++){
         ConvPrec(x[i][j].real,a[i][j].real,p);
         ConvPrec(x[i][j].imag,a[i][j].imag,p);
      }
   }
  }else{
   x.SetDims(a.NumRows(),a.NumCols());
   for (long i = 0; i < a.NumRows(); i++)
   {
      for(long j =0;j<a.NumCols();j++){
         ConvPrec(x[i][j].real,a[i][j].real,p);
         ConvPrec(x[i][j].imag,a[i][j].imag,p);
      }
   }
  }
   
}

void vandermonde(mat_c_RR &V, long N)
{
   V.SetDims(N, N);
   vec_c_RR r_v;
   RootOfUnit_vec(r_v, N);
   for (long i = 0; i < N; i++)
   {
      for (long j = 0; j < N; j++)
      {
         power(V[i][j], r_v[i], j);
      }
   }
}

NTL_END_IMPL
