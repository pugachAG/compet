template<class IMPL, class RET>
class DP2 {
public:
    static IMPL* create(int sz1, int sz2, RET emptyValue = -1) {
        auto res = new IMPL();
        res->init(sz1, sz2, emptyValue);
        return res;
    }

    RET calc(int i1, int i2) {
        auto impl = static_cast<IMPL*>(this);
        if (i1 < 0 || i1 >= sz1 || i2 < 0 || i2 >= sz2) {
		    return impl->impl(i1, i2);
        }
        auto &res = mem[i1*sz2 + i2];
        if (res == emptyValue) {
            res = impl->impl(i1, i2);
        }
        return res;
    }

private:
    int sz1 = -1;
    int sz2 = -1;
    RET emptyValue;
    vector<RET> mem;

    void init(int sz1, int sz2, RET emptyValue) {
        this->sz1 = sz1;
        this->sz2 = sz2;
        this->emptyValue = emptyValue;
        mem.assign(sz1*sz2, emptyValue);
    }
};
