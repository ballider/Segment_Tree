// segment tree for sum
// find k-тую единицу(возвращает индекс к-той единицы)(единицы пронумерованы с 0)
#include <iostream>
#include <vector>

struct segment_tree{
    std::vector<int64_t> tree;
    int64_t size;

    void init(const int64_t n){
        size = 1;
        while( size < n ) size *= 2;
        tree.assign(2*size-1, 0);
    }

    void build(const int64_t i, const int64_t v){
        build(i, v, 0, 0, size);
    }

    void build(const int64_t i, const int64_t v, int64_t x, int64_t left, int64_t rigth){
        if(rigth-left == 1){
            tree[x] = v;
            return;
        }
        int64_t m = (left+rigth)/2;
        if( i <  m ) build(i, v, 2*x+1, left, m);
        else build(i, v, 2*x+2, m, rigth);
        tree[x] = tree[2*x+1] + tree[2*x+2];
    }

    void set(const int64_t i){
        set(i, 0, 0, size);
    }

    void set(const int64_t i, int64_t x, int64_t left, int64_t rigth){
        if(rigth-left == 1){
            if(tree[x] == 1) tree[x] = 0;
            else tree[x] = 1;
            return;
        }
        int64_t m = (left+rigth)/2;
        if( i <  m ) set(i, 2*x+1, left, m);
        else set(i, 2*x+2, m, rigth);
        tree[x] = tree[2*x+1] + tree[2*x+2];
    }

    int64_t find(const int64_t k){
        return find(k, 0, 0, size)-size+1;
    }

    int64_t find(int64_t k, int64_t x, int64_t left, int64_t right){
        if(right-left == 1) return x;

        int64_t m = (left+right)/2;

        if( k < tree[2*x+1] ) find(k, 2*x+1, left, m);
        else find(k-tree[2*x+1], 2*x+2, m, right);
    }

    void print(){
        for(auto i : tree){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main(){
    int64_t n, m; std::cin >> n >> m;
    segment_tree T; T.init(n);
    for(int64_t i = 0; i < n; i++){
        int64_t v; std::cin >> v;
        T.build(i, v);
    }

    for(int64_t _ = 0; _ < m; _++){
        int64_t a, b; std::cin >> a >> b;
        if(a == 1) T.set(b);
        if(a == 2) std::cout << T.find(b) << std::endl;
    }
    
    return 0;
}
