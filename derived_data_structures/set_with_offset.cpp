template <typename T>
struct scam_set {
    T _offset = 0;
    set<T> s;
    void insert(T x) {
        s.insert(x - _offset);
    }
    typename set<T>::iterator find(T x) {
        return s.find(x - _offset);
    }
};