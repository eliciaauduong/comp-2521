/*
Let p(x)=anxn+an−1xn−1+⋯+a1x+a0 p(x)=anxn+an−1xn−1+⋯+a1x+a0 be a polynomial of degree 
nn. Design an O(n) O(n)-time algorithm for computing p(x). 
Hint: Assume that the coefficients ai are stored in an array A[0..n]. 
*/

// TIME COMPLEXITY: O(n^2)

int power(int n, int x) {
    int pow = 1;
    for (int i = 0; i < n; i++) {
        pow *= x;
    }
    return pow;
}

int evaluatePoly (int n, int *a, int x) {
    int val = 0;
    for (int i = 0; i <= n; i++) {
        val += power(i,x) * a[i];
    }
    return val;
}

// ORRR

int evaluatePoly (int n, int *a, int x) {
    int val = 0;
    for (int i = 0; i <= n; i++) {
        val += pow * a[i];
        pow *= x
    }
    return val;
}
