// очень не удобно считать знакочередующуюся сумму на отрезке
// но зато очень просто счиать знакочередующуюся сумма префикса
// тогда sgn_sum это будет разность сумм префиксов l и r (взятых с правильным знаком)
#include <iostream>
#include <vector>

// каждый узел содержит знакочередующуюся сумму на отрезке
struct segment_tree{
    int64_t size;
    std::vector<int64_t> tree;

    void init(const int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size-1, 0);
    }

    void set(const int64_t i, const int64_t v){
        set(i, v, 0, 0, size, 1);
    }

    void set(const int64_t i, const int64_t v, int64_t x, int64_t left, int64_t right, int64_t sgn){
        if(right-left == 1){
            tree[x] = v;
            return;
        }

        int64_t m = (left+right)/2;
        if(i < m) set(i, v, 2*x+1, left, m, (sgn+1)%2);
        else set(i, v, 2*x+2, m, right, (sgn+1)%2);

        if(right-left == 2){
            tree[x] = tree[2*x+1] - tree[2*x+2];
        }
        else{
            tree[x] = tree[2*x+1] + tree[2*x+2];
        }
    }

    // знакочередующаяся сумма префикса [0, r)
    int64_t pref_sum(int64_t r){
        return pref_sum(r, 0, 0, size);
    }

    int64_t pref_sum(int64_t r, int64_t x, int64_t left, int64_t right){
        if( r <= left || 0 >= right ) return 0;
        if( left >= 0 && right <= r ) return tree[x];

        int64_t m = (left+right)/2;
        int64_t s1 = pref_sum(r, 2*x+1, left, m);
        int64_t s2 = pref_sum(r, 2*x+2, m, right);
        return s1 + s2;
    }

    int64_t sgn_sum(int64_t l, int64_t r){
        int64_t pref_sum_l = pref_sum(l-1);
        int64_t pref_sum_r = pref_sum(r);
        //std::cout << pref_sum_l << " " << pref_sum_r << "\n";
        if((l-1)%2 != 0) return pref_sum_l-pref_sum_r;
        else return pref_sum_r-pref_sum_l;
    }

    void print(){
        for(auto it : tree){
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
};

int main(){
    int64_t n; std::cin >> n;
    segment_tree T; T.init(n);
    for(int64_t i = 0; i < n; i++){
        int64_t a; std::cin >> a;
        T.set(i, a);
    }

    //T.print();
    
    int64_t m; std::cin >> m;
    for(int64_t _ = 0; _ < m; _++){
        bool op; std::cin >> op;
        if(op){
            int64_t l, r; std::cin >> l >> r;
            std::cout << T.sgn_sum(l, r) << std::endl;
        }
        else{
            int64_t i, j; std::cin >> i >> j;
            T.set(i-1, j);
            //T.print();
        }
    }

    return 0;
}
