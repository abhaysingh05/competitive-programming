template <typename T>
struct minmax_heap {
    priority_queue<T, vector<T>, greater<T>> minh, minp;
    priority_queue<T, vector<T>, less<T>> maxh, maxp;
    void normalize() {
        while (!minp.empty() && minp.top() == minh.top()) minp.pop(), minh.pop();
        while (!maxp.empty() && maxp.top() == maxh.top()) maxp.pop(), maxh.pop();
    }
    void push(T x) {
        minh.push(x), maxh.push(x);
    }
    T min() {
        return normalize(), minh.top();
    }
    T max() {
        return normalize(), maxh.top();
    }
    void pop_min() {
        normalize(), maxp.push(minh.top()), minh.pop();
    }
    void pop_max() {
        normalize(), minp.push(maxh.top()), maxh.pop();
    }
};