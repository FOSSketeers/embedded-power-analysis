unsigned int binaryGCD(unsigned int a, unsigned int b) {
    if (a == b) return a;
    if (a == 0) return b;
    if (b == 0) return a;

    if ((a & 1) == 0 && (b & 1) == 0) {
        return binaryGCD(a >> 1, b >> 1) << 1;
    }
    if ((a & 1) == 0) {
        return binaryGCD(a >> 1, b);
    }
    if ((b & 1) == 0) {
        return binaryGCD(a, b >> 1);
    }

    if (a > b) {
        return binaryGCD((a - b) >> 1, b);
    } else {
        return binaryGCD(a, (b - a) >> 1);
    }
}

int bitLength(unsigned int x) {
    int length = 0;
    while (x > 0) {
        x >>= 1;
        length++;
    }
    return length;
}

unsigned int karatsuba(unsigned int x, unsigned int y) {
    if (x < 2 || y < 2) {
        return x * y;
    }

    int n = bitLength(x) > bitLength(y) ? bitLength(x) : bitLength(y);
    int m = n / 2;

    unsigned int high1 = x >> m;
    unsigned int low1 = x & ((1 << m) - 1);
    unsigned int high2 = y >> m;
    unsigned int low2 = y & ((1 << m) - 1);

    unsigned int z0 = karatsuba(low1, low2);
    unsigned int z1 = karatsuba(low1 + high1, low2 + high2);
    unsigned int z2 = karatsuba(high1, high2);

    return (z2 << (2 * m)) + ((z1 - z2 - z0) << m) + z0;
}

int fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_iterative(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int factorial_recursive(int n) {
    if (n <= 1) return 1;
    return n * factorial_recursive(n - 1);
}

int factorial_iterative(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int sum(int arr[], int n) {
  int res = 0;

  for (int i = 0; i < n; ++i) {
    res += arr[i];
  }

  return res;
}
