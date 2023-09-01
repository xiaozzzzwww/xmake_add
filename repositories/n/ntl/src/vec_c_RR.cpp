
#include <NTL/c_RR.h>
#include <NTL/vec_c_RR.h>


NTL_START_IMPL

void do_print(const vec_c_RR& a, int prec ){
   if(prec == -1)
      NTL_SNS cout<<a;
   else{
      NTL_SNS cout<<"[";
      for (long  i = 0; i < a.length(); i++)
      {
         /* code */
         do_print(a[i],prec);
         if(i != a.length()-1){
            NTL_SNS cout<<" ";
         }
      }
      NTL_SNS cout<<"]";
      
   }
}

void add(vec_c_RR& x, const vec_c_RR& a, const vec_c_RR& b)
{
   long n = a.length();
   if (b.length() != n) LogicError("vector add: dimension mismatch");

   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      add(x[i], a[i], b[i]);
}

void sub(vec_c_RR& x, const vec_c_RR& a, const vec_c_RR& b)
{
   long n = a.length();
   if (b.length() != n) LogicError("vector sub: dimension mismatch");
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      sub(x[i], a[i], b[i]);
}



void mul(vec_c_RR& x, const vec_c_RR& a, double b)
{
   
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      mul(x[i], a[i], b);
}

void mul(vec_c_RR & x, const vec_c_RR & a, const RR & b)
{
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      mul(x[i], a[i], b);
}

void mul(vec_c_RR& x, const vec_c_RR& a, const c_RR& b_in)
{
   c_RR b = b_in;
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      mul(x[i], a[i], b);
}

void SetReal(vec_c_RR &x, const vec_RR &a)
{
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      SetReal(x[i], a[i]);
}

void SetImag(vec_c_RR &x, const vec_RR &a)
{
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      SetImag(x[i], a[i]);
}

void GetReal(vec_RR &x, const vec_c_RR &a)
{
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      GetReal(x[i], a[i]);
}

void GetImag(vec_RR &x, const vec_c_RR &a)
{
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      GetImag(x[i], a[i]);
}


void InnerProduct(c_RR& xx, const vec_c_RR& a, const vec_c_RR& b)
{
   c_RR t1, x;

   long n = min(a.length(), b.length());
   long i;

   clear(x);
   for (i = 1; i <= n; i++) {
      mul(t1, conj(a(i)), b(i));
      add(x, x, t1);
   }

   xx = x;
}



void clear(vec_c_RR& x)
{
   long n = x.length();
   long i;
   for (i = 0; i < n; i++)
      clear(x[i]);
}

void negate(vec_c_RR& x, const vec_c_RR& a)
{
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      negate(x[i], a[i]);
}


long IsZero(const vec_c_RR& a)
{
   long n = a.length();
   long i;

   for (i = 0; i < n; i++)
      if (!(IsZero(a[i])))
        return 0;
   return 1;
}

vec_c_RR operator+(const vec_c_RR& a, const vec_c_RR& b)
{
   vec_c_RR res;
   add(res, a, b);
   NTL_OPT_RETURN(vec_c_RR, res);
}

vec_c_RR operator-(const vec_c_RR& a, const vec_c_RR& b)
{
   vec_c_RR res;
   sub(res, a, b);
   NTL_OPT_RETURN(vec_c_RR, res);
}


vec_c_RR operator-(const vec_c_RR& a)
{
   vec_c_RR res;
   negate(res, a);
   NTL_OPT_RETURN(vec_c_RR, res);
}

void random(vec_c_RR &x, long n, double start, double end)
{
   x.SetLength(n);
   for (size_t i = 0; i < n; i++)
   {
      /* code */
      random(x[i], start, end);
   }
   
}

void RoundPrec(vec_c_RR &x, const vec_c_RR &a, long p)
{ 
   long n = a.length();
   if(&x!=&a)
   {
      x.SetLength(n);
   }
   for(long i =0;i<n;i++){
      RoundPrec(x[i],a[i],p);
   }
}

void ConvPrec(vec_c_RR &x, const vec_c_RR &a, long p)
{
   
   long n = a.length();
   if(&x!=&a)
   {
      x.SetLength(n);
   }
   for(long i =0;i<n;i++){
      ConvPrec(x[i],a[i],p);
   }
}

void RootOfUnit_vec(vec_c_RR &x, int N)
{

   if (N < 0) LogicError("RootOfUnit_vec: negative length");
   clear(x);
   x.SetLength(N);
   c_RR r;
   RootOfUnit(r, N);
   for (int i = 0; i < N; i++){
      power(x[i],r, 2*i+1);
   }

}

void VectorCopy(vec_c_RR& x, const vec_c_RR& a, long n)
{
   if (n < 0) LogicError("VectorCopy: negative length");
   if (NTL_OVERFLOW(n, 1, 0)) ResourceError("overflow in VectorCopy");

   long m = min(n, a.length());

   x.SetLength(n);

   long i;

   for (i = 0; i < m; i++)
      x[i] = a[i];

   for (i = m; i < n; i++)
      clear(x[i]);
}

NTL_END_IMPL
