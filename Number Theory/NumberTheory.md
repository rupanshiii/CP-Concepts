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
- Basic concept is that every composite number C must have a prime factor P < C
- we will keep marking all the multiples of the prime number (or the unmarked numbers going in order from 2) as non prime, at the end all the numbers that are not marked are prime
- idea is that if a number is not marked by any of the prime factors before it, it must be prime
```cpp
vector<ll> seive(ll n){

    vector<ll> prime(n+1, 1);

    prime[0] = prime[1] = 0;
    for(ll i=2; i*i<=n; i++){ // note that you do not have to go all the way till n, now the reasoning comes from the inner loop, that we start it from i*i till n, if i*i>n, there is no point in iterating over those values

        if(prime[i] == 0){

            for(ll j=i*i; j<=n; j+=i) prime[i] = 0; // we are not marking the numbers from 2*i, 3*i, 4*i to (i-1)*i because those numbers contain one of the factor < i and hence, they would already be marked by the prime factors < i, so this reduces the time complexity
        }
    }
}
```
- Time complexity - O(n * log(log(n)))
> Proof: for j = i, the inner loop iterated n/i times and this happen for all the i that are prime, which means the total time complexity of the algo is n/2 + n/3 + n/5 + ... + n/n = n * (1/2 + 1/3 + 1/5 + ... + 1/n), which based on the calculation is approximately equal to ln(ln(n)) [base e].

> note that we can consider that this time complexity is approximately equal to O(n) only since ln(ln(1e18)) = 4


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
`if(b is even) a^b = a^(b/2) * a^(b/2)` 
`if(b is odd) a^b = a^(b/2) * a^(b/2) * a` 
we know that `a^0 = 1` => so that's the base condition

[Code Link](\2.NT.BinaryExponentiation.cpp)
``` cpp
ll exp(ll a, ll b){
    if(b == 0) return 1; // base condition
    ll x = exp(a, b/2); // x = a^(b/2)
    if(b%2 == 0) return x*x;
    else return x*x*a;
}
```
