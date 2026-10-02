# Basic Primality Testing:
Primality testing is checking whether a given number is prime or not

## Brute Force:
go from 2 to n-1, if any of the number divides n, n is not prime, else it is prime 
- Time Complexity: O(n) - linear

## Square Root Method:
go from 2 to sqrt(n), if any of the number divides n, n is not prime, else it is prime 
why this works, n can be represented as a*b, now at least one of a, b <= sqrt(n), why? 
let say a>sqrt(n) and b>sqrt(n) => a*b>n which contradicts it
- Time Complexity - sqrt(n)

## Sieve of Eratosthenes:
- Used to find all the prime numbers upto a given limit
- Main idea behind this algo is instead of finding all the primes in a range, we are finding all the composites, and the remaining numbers are automatically left as prime
- Basic concept is that every composite number C must have a prime factor P < C
- we will keep marking all the multiples of the prime number (or the unmarked numbers going in order from 2) as non prime, at the end all the numbers that are not marked are prime
- idea is that if a number is not marked by any of the prime factors before it, it must be prime
```cpp
vector<ll> seive(ll n){

    vector<ll> prime(n+1, 1);

    prime[0] = prime[1] = 0;
    for(ll i=2; i*i<=n; i++){ // note that you do not have to go all the way till n, now the reasoning comes from the inner loop, that we start it from i*i till n, if i*i>n, there is no point in iterating over those values

        if(prime[i] == 1){

            for(ll j=i*i; j<=n; j+=i) prime[i] = 0; // we are not marking the numbers from 2*i, 3*i, 4*i to (i-1)*i because those numbers contain one of the factor < i and hence, they would already be marked by the prime factors < i, so this reduces the time complexity
        }
    }
}
```
- Time complexity - O(n * log(log(n)))
> Proof: for j = i, the inner loop iterated n/i times and this happen for all the i that are prime, which means the total time complexity of the algo is n/2 + n/3 + n/5 + ... + n/n = n * (1/2 + 1/3 + 1/5 + ... + 1/n), which based on the calculation is approximately equal to ln(ln(n)) [base e].

> note that we can consider that this time complexity is approximately equal to O(n) only since ln(ln(1e18)) = 4

Interesting:
- We can approximately calculate the time complexity of seive as O(nlogn)
``` cpp
// as already mentioned, the time complexity of seive will be:
n*(1/2 + 1/3 + 1/5 + 1/7 + ... + 1/(last prime))

// now let's boil it down to
n*(1/2 + 1/3 + 1/4 + 1/5 + ..... + 1/n)

// let's change a few numbers to their neighboring number - we will only be increasing the overall term so that won't reduce the time complexity, it would just increase it, which is fine, as we are only finding the approximate
n*(1/2 + 1/2 + 1/4 + 1/4 + 1/4 + 1/4 + 1/8 + .... )

// now, we can directly see that combining these terms would result in a few 1's and that would be logn 1's
// so time complexity becomes n*logn

```


# Prime Factorization:

## Trial Division
- It uses the basic rule that smallest divisor of any number is less than or equal to the `sqrt(n)` and will always be prime.
- n can be represented as `a^x * b^y * c^z * ...` and so on, where `a, b, c` are prime and `x, y, z` are `>= 0`
- We will find the smallest divisor of `n` iterating from `2` to `sqrt(n)` and divide `n` with `a` until it no more remains a multiple
- let `a` be the smallest divisor, now the next smallest divisor will definitely be greater than `a` 
- so we will keep iterating from `a+1`, note that while doing so, the breaking condition will also change, i.e., now we will iterate till `sqrt(n/(a^x))` becasue the smallest divisor of `n/(a^x)` will lie between 2 and its square root.
- example: n = 108
    - 2 is a multiple of n => n/2 = 108/2 = 54
    - 2 still divises n => 54/2 = 27
    - now we will iterate from 3 to sqrt(27) = 5
    - 3 divides n => 27/3 = 9
    - 3 divides n => 9/3 = 3
    - 3 divides n => 3/3 = 1

- now you may question that since we are reducing the breaking condition, it might happen that we do not process some of the valid divisors.
- note that this is true in the case when only one divisor is remaining
    - `n = a * b` (`a = b` or `a != b`) and both of them remains to be processed. This case cannot happen, because if `n = a * b`, one of `a, b <=sqrt(n)`, so one of them will definitely be processed during the loop
- code in [this file](1.NT.TrialDivision.cpp)

## Using Seive
- The basic idea is how we used to prime factorize a number in our childhood, that is finding the smallest prime factor of the current number, divide that number and again finding the smallest prime factor:
```
2 | 20
  |___
2 | 10
  |___
5 | 5
  |___
  | 1
  |___
```
- now to find the smallest prime factor of all of those numbers in O(1) time, we just store the spf of all the numbers beforehand
- This is done through seive
``` cpp
vector<ll> seive(ll n){
    vector<ll> spf(n+1, -1);
    for(ll i=2; i<=n; i++){
        if(spf[i] == -1){
            spf[i]=i;
            for(ll j=i*i; j<=n; j++){
                if(spf[j]==-1) spf[j]=i;
            }
        }
    }
    return spf;
}

// Time Complexity: O(log(n)) - because in the worst case it way go like 2^x
void primeFactorize(ll n){
    vector<ll> spf = seive(n);
    while(n>1){
        cout<<spf[n]<<" ";
        n /= spf[n];
    }
}
```

# Modulo Arithmetic:
Arithmetic operations involving modulo. It is used whne we need to print very very large numbers

## Why do problems ask to reduce the answer with modulo 1e9+7?
When the answer is too long and cannot be accommodated within the memory limit available, and the exact result is not valuable that much, just the modulo result or some part of that info is valuable enough to solve a problem, we use modulo of a prime number instead of computing the whole answer.
We take modulo of a prime numebr especially 1e9+7 because of 3 reasons:
1. It is large enough to avoid excessive collisions in many problems., coz the result produced would be one in the range of 0 to 1e9+6
2. Every non zero number modulo m has a multiplicative inverse if the m is prime which is useful when one needs to perform a modulo division. And this is crucial in CP, because suppose we need to find the value of (100!)/(57!*43!), we need to perform modulo division, which is only possible when m is prime
> If interested: x modulo m has a multiplicative inverse only if gcd(x, m) = 1, for m being prime, its valid for all the numbers
3. It fits comfortably inside standard integer types.

## Modulo Rules:

Why do we have these rules, why can't we do (a+b)%m directly?
Because if a = 1e18 and b = 1e18 then a+b = 2*1e18 which overflows
So to avoid that overflow, we first tke modulo individually and then perform the operation

### Addition Rule:
``` cpp
(a + b)%m = (a%m + b%m)%m
```

### Multiplication Rule:
``` cpp
(a * b)%m = ((a%m) * (b%m))%m
```
Never remove inner parantheses in case of multiplication rule because % and * have same precedence in C++, so they will be evaluated left to right if not separated by parantheses

### Subtraction Rule:
``` cpp
(a - b)%m = ((((a%m) - (b%m))%m) + m)%m

// a = 2, b = 3, m = 5

// LHS: (2 - 3)%5 = (-1)%5 = -1 (in cpp)
// RHS: ((((2%5) - (3%5))%5) + 5)%5 
//      = ((-1%5) + 5)%5 
//      = (-1+5)%5 
//      = 4%5
//      = 4
```
(-a % m) should alwyas be a positive number because modulo expects the answer to be inside the range of 0 and m-1 and that's exactly what we gte in python
So when we divide -13 by 5, it should ideally give the quotient as -3, because we always subtract a number less than or equal to the divisor (here we subtract (5*(-3) = -15) from -13 and that gives the remainder as 2)

But in C++, when we take (-a % m), the remainder we get is actually negative.
So when we divide -13 by 5, it treats it as a positive number and subtracts 5*(-2) = -10 from it, leaving the remainder as -3.
So to fix this, we add an extra modulo addition operation in subtraction
> Note that in C++  5 / (-3) = -1 and consequently, 5 % (-3) = 2

### Division

> Note: Read this section after reading the binary exponentiation

> Note that we perform modular division only when `a` isatually divisible by `b` 

We cannot simply apply the division as we did for addition and other rules because 
``` cpp
(a/b)%m != ((a%m) / (b%m))%m
```
even if a is divisible by b, this statement can change the whole definition
Example, `a = 12, b = 4, m = 5`
- LHS: `(12/4)%5 = 3%5 = 3`
- RHS: `((12%5) / (4%5))%5 = (2 / 4)%5 = 0`

So we do something called as **Modular Inverse** \
In modulo, we can we can write 
``` cpp
(a/b)%m = (a * inv(b))%m
``` 
where `inv(b)` can be think of a number `i` such that 
``` cpp
(b * i)%m = 1 or `(b * i) ≡ 1 (mod m)` 
```
(mathematical representation - just a way of writing)

But finding the inverse is very difficult, because we need to iterate over all the numbers within the range and check whether its product with `b` modulo `m` is equal to 1.

So here comes the Fermat's Little Theorem: \
for prime `m`

`x`<sup>`m-1`</sup> `% m = 1` \
`x`<sup>`m-1`</sup> `≡ 1 (mod m)`

Dividing both sides by x \
`x`<sup>`m-2`</sup> ≡ $\frac{1}{x}$ `(mod m) ≡ x`<sup>`-1`</sup> `(mod m)` 

which means that `x`<sup>`m-2`</sup> is a valid inverse of `x`
which can be easily calculates using binary exponentiation

> Note that Fermat's little Theorem works only when x and m are coprime

Let inverse of a = x\
`ax % m = 1`\
`ax = my + 1`\
`ax - my = 1 ----> LDE`\
LDE states that for this equation to have integer solution for `x` and `y =>
c % gcd(a, m) `should be equal to `0`\
`=> 1 % gcd(a, m) == 0`\
This is possible only when `gcd(a, m) = 1`\
Hence, `a` and `m` must be coprime

``` cpp
ll const m = 1e9+7;

ll mul(ll a, ll b){
    return ((a%m) * (b%m))%m;
}

ll exp(ll a, ll b){
    if(b == 0) return 1;
    ll half = exp(a, b/2);
    if(b%2 == 1) return mul(mul(half, half), b);
    else return mul(half, half);
}

ll inv(ll a){
    return exp(a, m-2);
}

ll div(ll a, ll b){
    return mul(a, inv(b));
}
```

**Use case:** \
It is used when the division is guaranteed to be integral without any decimal left over, for example, factorial division:

``` cpp
vector<ll> fact(101);

ll ncr(ll n, ll r){
    return div(fact[n], mul(fact[r], fact[n-r]));
}

void factorial(){
    fact[0] = fact[1] = 1;
    for(ll i=2; i<=100; i++){
        fact[i] = mul(fact[i-1], i);
    }
}
```


# Exponentiation
1. They are different, LHS is actually 2^12
`(2^3)^4 != 2^(3^4)`

2. Never ever use `pow()` to calculate `a^b`. Reason? 
    - it has the same time complexity as calculating the value using a for loop which is `O(b)`.
    - `pow()` uses floating-point (double) arithmetic, and double cannot represent every number exactly, especially large integers. So even if the mathematical answer is an exact integer, `pow()` may internally store a very close approximation instead. When you convert that result back to an integer, that tiny error can produce a wrong answer.
    - In the problems involving modulo, the answer may overflow when we use pow function.
``` cpp
ll calcPower(ll a, ll b){
    ll ans = 1;
    for(ll i=1; i<=b; i++) ans *= a;
    return ans;
}
```

3. We need to calculate `a^b` sometimes when `b>1e9`. We cannot directly use the for loop because of time complexity.

So reduce the TC, we optimize it by using a simple formula:
- `if(b is even) a^b = a^(b/2) * a^(b/2)` 
- `if(b is odd) a^b = a^(b/2) * a^(b/2) * a` 
- we know that `a^0 = 1` => so that's the base condition

[Code Link](2.NT.BinaryExponentiation.cpp)
``` cpp
ll exp(ll a, ll b){
    if(b == 0) return 1; // base condition
    ll x = exp(a, b/2); // x = a^(b/2)
    if(b%2 == 0) return x*x;
    else return x*x*a;
}
```

Time complexity: `O(log b base 2)`
- How? because each time we are calculating the half of the answer and using it to calculate the complete value, we keep halving until becomes 0

# GCD
GCD is the greatest common divisor between two numbers. The brute force way to calculate GCD is to find all the factors of both the numbers and whichever is the largest common factor would be the GCD. TC for this approach: `O(sqrt(n))`

Brute Force:
``` cpp
for(int i=min(a, b); i>=1; i--){
    if(a%i == 0 && b%i == 0) return i; 
}

// Time complexity: O(min(a, b))
```

## Euclidean Algorithm:

### Basics:
gcd(a, b) cannot be greater than |a-b|.
Proof: let a < b and gcd(a,b) = g > b - a
``` cpp
=> a = g*x
=> b >= g*(x+1)
=> b-a >= g*(x+1 - x)
=> b-a >= g
```
also
``` cpp
Let g = gcd(a, b)
a = x*g and b = y*g
=> (a-b) = (x-y)*g
=> g divides (a-b) as well
```
=> `gcd(a, b) = gcd(b, a-b) where a>b` \
=> `gcd(a, b) = gcd(b, a-2b)` \
=> `gcd(a, b) = gcd(b, a-nb)` \
=> `a-nb >= 0` \
=> `n <= a/b` \
=> `a-nb = a%b` 

### Algo:
```cpp
gcd(a, b) = gcd(b%a, a) = gcd(b, a%b)
```
and when a = 0, b is the solution -> base case

gcd(10, 25) = gcd(5, 10) = gcd(0, 5) => gcd = 5

``` cpp
ll gcd(ll a, ll b){
    if(a == 0) return b;
    return gcd(b%a, a);
}
```

Worst case of this approch is Fibonacci sequence, so taking any two consecutive numbers of the sequence would iteratively go backward in the fibonacci series as it will keep subtracting, and since fibonacci numbers are almost double of the previous number, we can safely say that the worst case time complexity of this approach is `O(log(min(a, b)) base phi(1.14))`

In built `__gcd()` function also uses the same algo
> Always use abs numbers inside the built in function: `__gcd(abs(a), abs(b))`. Because some people claim that otherwise it gives wrong answer sometimes.

## Properties:
- `gcd(0, n) = n`
- GCD can be represented as product of `min(pi^ai, pi^bi)` for each prime factor `pi`
- `gcd(a, b, c, ...) = gcd(gcd(gcd(a, b), c), ...)`
- `gcd(a, a+1) = 1`
    - Proof (using euclidean algo)
    ``` cpp 
    gcd(a, a+1) = gcd((a+1)%a, a)
                = gcd((a+1)%a, a)
                = gcd((a%a + 1%a)%a, a)
                = gcd(1, a)
                = gcd(a%1, 1)
                = gcd(0, 1)
                = 1
    ```
- if we have an array `a = [a0, a1, a2, ... , an]`, then 
``` cpp
gcd(a) = gcd(a0, a1, a2, ... , an) = gcd(a0, a1-a0, a2-a0, ... , an-a0) 
```
and its one of the very important property, coz we are correlating the gcd with addition / subtraction operation, this property is getting used in [this question](/Number%20Theory/P7.A_Row_GCD.cpp)

- `gcd(a, b) = gcd(abs(a), abs(b))`
- in any case, max value of `gcd(a, b) = min(a, b)`

# LCM

```cpp
lcm(a, b) = (a * b) / gcd(a, b)
```

This is completely wrong:
```cpp
lcm(a, b, c) != ((a * b * c) / gcd(a, b, c))
```
This is the right way:
```cpp
lcm(a, b, c) = lcm(lcm(a, b), c)
```

## Properties:
- LCM can be represented as product of `max(pi^ai, pi^bi)` for each prime factor `pi`
- `lcm(a, b, c, ...) = lcm(lcm(lcm(a, b), c), ...)`
- `lcm(a, b) * gcd(a, b) = a*b`
    - Proof
    ``` cpp
    if max(a, b) = a, then min(a, b) = b
    if max(a, b) = b, then min(a, b) = a
    which means that max(a, b) + min(a, b) = a + b
    now lcm is the product of the max of each prime factor
    and gcd is the product of the min of each prime factor
    So multiplying both of them eventually adds of the min and max power
    ```
    - Easy Proof
    ``` cpp
    gcd(a, b) = g
    a = x * g (x is the distinct multiple of a)
    b = y * g (y is the distinct multiple of b)
    a*b = x*y*g*g (we have an extra g here)
    so lcm(a, b) = (a*b) / g
    => lcm (a, b) * gcd(a, b) = (a * b)
    ```

# Extended Euclid's Algo:
> Rare to see qs on this topic: 

We have an equation of the form below and we want to find the integral solution of x and y
`ax + by = gcd(a, b)`
``` cpp
gcd(b%a, a) = (b%a)x1 + ay1  

now we know that:
    b%a = b - floor(b/a).a

Replacing it in the above equation
gcd(b%a, a) = (b - floor(b/a)a)x1 + ay1
            = a(y1 - floor(b/a)x1) + bx1

gcd(a, b)   = aX + bY

Hence,
x = y1 - floor(b/a)x1
y = x1

Now as we propagate below in gcd, at some point we get:
gcd(0, b) = b
gcd(0, b) = ax + by
b = ax + by
x = 0 and y = 1 
```  

[Code here](\3.NT.ExtendedEuclidAlgo.cpp)

## LDE (Linear Diophantine Equation)
Use case of Extended Euclid's algorithm

We have equation `ax + by = c -- a, b, c => integers`
We are asked to find the integral solution of x and y

`ax + by = c`\
`ax + by = c.`$\frac{g}{g}$\
`a.`$\frac{g}{c}$`x + b.`$\frac{g}{c}$`y = g`\
`a.X + b.Y = g` => this is extended euclid's algo and it always has a solution

So to find x and y, we can just solve the extended euclid equation and find X and Y, and use them to find x and y in the original equation.

`X = `$\frac{g}{c}$`.x`\
`x = `$\frac{c}{g}$`.X`\
and similarly:\
`x = `$\frac{c}{g}$`.Y`

> This equation will have a solution only if `c%g == 0`\
If c%g == 0 -> infinite integer solution\
If c%g != 0 -> 0 integer solution

Now let's try to find the infinite solution:\
`ax' + by' = c`\
`ax' + by' +` $\frac{a.b}{g}$ - $\frac{a.b}{g}$` = c`\
`a(x' + `$\frac{b}{g}$`) + b(y' - `$\frac{b}{g}$`) = c`\
Hence, the infinite solutions would be: \
`x = (x' + `$\frac{b}{g}$`)*k` and \
`y = (y' - `$\frac{b}{g}$`)*k` where k is integer


