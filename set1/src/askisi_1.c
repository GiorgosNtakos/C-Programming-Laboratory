#include <stdio.h>

int main() {
    int x, y, z, w, a, b, res;

    // i
    x=3; y=3; z=1; w=15; a=14; b=3;
    res = y + z/x;
    printf("i)  res = y + z/x;        -> res = %d (x=%d y=%d z=%d w=%d a=%d b=%d)\n",
           res, x, y, z, w, a, b);

    // ii
    x=3; y=3; z=1; w=15; a=14; b=3;
    res = w*x/y/z;
    printf("ii) res = w*x/y/z;        -> res = %d (x=%d y=%d z=%d w=%d a=%d b=%d)\n",
           res, x, y, z, w, a, b);

    // iii
    x=3; y=3; z=1; w=15; a=14; b=3;
    res = w/x*++z + x/y;
    printf("iii) res = w/x*++z+x/y;   -> res = %d (x=%d y=%d z=%d w=%d a=%d b=%d)\n",
           res, x, y, z, w, a, b);

    // iv
    x=3; y=3; z=1; w=15; a=14; b=3;
    res = ++b, --a;
    printf("iv) res = ++b, --a;       -> res = %d (x=%d y=%d z=%d w=%d a=%d b=%d)\n",
           res, x, y, z, w, a, b);

    // v
    x=3; y=3; z=1; w=15; a=14; b=3;
    res = (--b, ++a);
    printf("v)  res = (--b, ++a);     -> res = %d (x=%d y=%d z=%d w=%d a=%d b=%d)\n",
           res, x, y, z, w, a, b);

    // vi
    x=3; y=3; z=1; w=15; a=14; b=3;
    res = (a>b) ? b : a;
    printf("vi) res = (a>b)?b:a;      -> res = %d (x=%d y=%d z=%d w=%d a=%d b=%d)\n",
           res, x, y, z, w, a, b);

    return 0;
}
