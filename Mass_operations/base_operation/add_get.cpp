// прибавление к отрезку
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

    void add(const int64_t l, const int64_t r, const int64_t v){
        add(l, r, v, 0, 0, size);
    }

    void add(const int64_t L, const int64_t R, const int64_t v, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left) return;
        if(L <= left && R >= right){ 
            tree[x] += v;
            return;
        }

        int64_t m = (left+right)/2;
        add(L, R, v, 2*x+1, left, m);
        add(L, R, v, 2*x+2, m, right);
    }

    int64_t get(const int64_t i){
        return get(i, 0, 0, size);
    }

    int64_t get(const int64_t i, int64_t x, int64_t left, int64_t right){
        if(right-left ==1 ) return tree[x];

        int64_t ans = tree[x];

        int64_t m = (left+right)/2;
        if(i < m) ans += get(i, 2*x+1, left, m);
        else ans += get(i, 2*x+2, m, right);

        return ans;
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

    for(int64_t _ = 0; _ < m; _++){
        int64_t type; std::cin >> type;
        if(type == 1){
            int64_t l, r, v; std::cin >> l >> r >> v;
            T.add(l, r, v);
            //T.print();
        }
        if(type == 2){
            int64_t i; std::cin >> i;
            std::cout << T.get(i) << "\n";
        }
    }

    return 0;
}
