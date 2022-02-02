// применить ко всем на отрезке битовое OR и найти битовый AND на отрезке
#include <iostream>
#include <vector>

struct segment_tree{
    struct Node{
        int64_t _or;
        int64_t _and;
    };
    int64_t size;
    std::vector<Node> tree;

    void init(const int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size-1, {0, 0});
    }

    void print(){
        for(auto it : tree){
            std::cout << "( " << it._or << " " << it._and << " )" << " ";
        }
        std::cout << "\n";
    }

    void OR(const int64_t l, const int64_t r, const int64_t v){
        OR(l, r, v, 0, 0, size);
    }

    void OR(const int64_t L, const int64_t R, const int64_t v, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left) return;
        if(L <= left && R >= right){ 
            tree[x]._or  = tree[x]._or  | v;
            tree[x]._and = tree[x]._and | v;
            return;
        }

        int64_t m = (left+right)/2;
        OR(L, R, v, 2*x+1, left, m);
        OR(L, R, v, 2*x+2, m, right);

        tree[x]._and = (tree[2*x+1]._and & tree[2*x+2]._and) | tree[x]._or;
    }

    int64_t AND(const int64_t l, const int64_t r){
        return AND(l, r, 0, 0, size);
    }

    int64_t AND(const int64_t L, const int64_t R, int64_t x, int64_t left, int64_t right){
        if( L >= right || R <= left ) return (1LL << 30)-1;
        if(L <= left && R >= right) return tree[x]._and;
        
        int64_t m = (left+right)/2;
        int64_t m1 = AND(L, R, 2*x+1, left, m);
        int64_t m2 = AND(L, R, 2*x+2, m, right);
        return (m1 & m2) | tree[x]._or;
    }
};


int main(){
    int64_t n, m; std::cin >> n >> m;

    segment_tree T; T.init(n);

    for(int64_t _ = 0; _ < m ; _++){
        int64_t type; std::cin >> type;
        if(type == 1){
            int64_t l, r, v; std::cin >> l >> r >> v;
            T.OR(l, r, v);
            //T.print();
        }
        if(type == 2){
            int64_t l, r; std::cin >> l >> r;
            std::cout << T.AND(l, r) << "\n";
        }
    }

    return 0;
}
