```c++
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    } else {
        ll tx, ty;
        ll d = exgcd(b, a % b, tx, ty);
        x = ty;
        y = tx - (a / b) * ty;
        return d;
    }
}
```

