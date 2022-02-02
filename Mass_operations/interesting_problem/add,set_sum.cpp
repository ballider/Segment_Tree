// присвание или прибавление и сумма на отрезке
// когда делаем проталкивание всегда считаем, что в данном узле сумма уже посчитана правильно, и пересчитываем только в узлах
#include <iostream>
#include <vector>

struct segment_tree{
    struct Node{
        int64_t set;
        int64_t add;
        int64_t sum;
        int64_t len;
    };
    int64_t size;
    std::vector<Node> tree;

    void build(int64_t x, int64_t left, int64_t right){
        if(right-left == 1){
            tree[x].set = -1;
            tree[x].add = -1;
            tree[x].sum = 0;
            tree[x].len = 1;
        }
        else{
            int64_t m = (left+right)/2;
            build(2*x+1, left, m);
            build(2*x+2, m, right);
            tree[x].len = tree[2*x+1].len + tree[2*x+2].len;
            tree[x].set = -1;
            tree[x].add = -1;
            tree[x].sum = 0;
        }
    }

    void init(const int64_t n){
        size = 1;
        while( size < n ) size *= 2;
        tree.resize(2*size-1);
        build(0, 0, size);
    }

    void propagate(int64_t x, int64_t left, int64_t right){
        if(right-left == 1){
            tree[x].set = -1;
            tree[x].add = -1;
            return;
        }
        if(tree[x].set != -1 && right-left != 1){
            tree[2*x+1].add = -1;
            tree[2*x+1].set = tree[x].set;
            tree[2*x+1].sum = tree[2*x+1].len*tree[2*x+1].set;

            tree[2*x+2].add = -1;
            tree[2*x+2].set = tree[x].set;
            tree[2*x+2].sum = tree[2*x+2].len*tree[2*x+2].set;

            tree[x].set = -1;
        }
        if(tree[x].add != -1 && right-left != 1){
            if(tree[2*x+1].add == -1) tree[2*x+1].add = 0;
            if(tree[2*x+2].add == -1) tree[2*x+2].add = 0;

            tree[2*x+1].add += tree[x].add;
            tree[2*x+1].sum += tree[2*x+1].len*tree[x].add;

            tree[2*x+2].add += tree[x].add;
            tree[2*x+2].sum += tree[2*x+2].len*tree[x].add;

            tree[x].add = -1;
        }
        /*
        std::cout << "--\n";
        print();
        std::cout << "--\n";
        */
    }

    void set(const int64_t l, const int64_t r, const int64_t v){
        set(l, r, v, 0, 0, size);
    }

    void set(const int64_t L, const int64_t R, const int64_t v, int64_t x, int64_t left, int64_t right){
        propagate(x, left, right);

        if(L >= right || R <= left) return;
        if(L <= left && R >= right){ 
            tree[x].set = v;
            tree[x].add = -1;
            tree[x].sum = tree[x].len*tree[x].set;
            return;
        }

        int64_t m = (left+right)/2;
        set(L, R, v, 2*x+1, left, m);
        set(L, R, v, 2*x+2, m, right);

        tree[x].sum = tree[2*x+1].sum + tree[2*x+2].sum;
    }

    void add(const int64_t l, const int64_t r, const int64_t v){
        add(l, r, v, 0, 0, size);
    }

    void add(const int64_t L, const int64_t R, const int64_t v, int64_t x, int64_t left, int64_t right){
        propagate(x, left, right);
        
        if(L >= right || R <= left) return;
        if(L <= left && R >= right){
            if(tree[x].add == -1) tree[x].add = 0;
            tree[x].add += v;
            tree[x].sum += tree[x].len*tree[x].add;
            return;
        }

        int64_t m = (left+right)/2;
        add(L, R, v, 2*x+1, left, m);
        add(L, R, v, 2*x+2, m, right);

        tree[x].sum = tree[2*x+1].sum + tree[2*x+2].sum;
    }

    int64_t sum(const int64_t l, const int64_t r){
        return sum(l, r, 0, 0, size);
    }

    int64_t sum(const int64_t L, const int64_t R, int64_t x, int64_t left, int64_t right){
        propagate(x, left, right);
        
        if(L >= right || R <= left) return 0;
        if(L <= left && R >= right) return tree[x].sum;

        int64_t m = (left+right)/2;
        int64_t sum1 = sum(L, R, 2*x+1, left, m);
        int64_t sum2 = sum(L, R, 2*x+2, m, right);

        return sum1 + sum2;
    }

    void print(){
        for(auto it : tree){
            std::cout << it.sum << " " << it.set << " " << it.add << "| "; 
        }
        std::cout << "\n";
    }

};

int main(){
    int64_t n, m; std::cin >> n >> m;

    segment_tree T; T.init(n);

    for(int64_t _ = 0; _ < m; _++){
        int64_t type; std::cin >> type;
        if(type == 1){
            int64_t l, r, v; std::cin >> l >> r >> v;
            T.set(l, r, v);
            //T.print();
        }
        if(type == 2){
            int64_t l, r, v; std::cin >> l >> r >> v;
            T.add(l, r, v);
            //T.print();
        }
        if(type == 3){
            int64_t l, r; std::cin >> l >> r;
            std::cout << T.sum(l, r) << "\n";
        }
    }

    return 0;
}
