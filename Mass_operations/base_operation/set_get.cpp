// присвоить всем элементам на отрезке значение
#include <iostream>
#include <vector>

struct segment_tree{
    std::vector<int64_t> tree;
    int64_t size;

    void init(const int64_t n){
        size = 1;
        while( size < n ) size *= 2;
        tree.assign(2*size-1, -1);
    }

    void modify(const int64_t l, const int64_t r, const int64_t v){
        modify(l, r, v, 0, 0, size);
    }

    void modify(const int64_t L, const int64_t R, const int64_t v, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left) return;

        // делаем проталкивание
        if(tree[x] != -1){
            if(right-left == 1){
                tree[x] = v;
                return;
            }
            else{
                tree[2*x+1] = tree[x];
                tree[2*x+2] = tree[x];
            }
            tree[x] = -1;
        }


        if(L <= left && R >= right){ 
            tree[x] = v;
            return;
        }

        int64_t m = (left+right)/2;
        modify(L, R, v, 2*x+1, left, m);
        modify(L, R, v, 2*x+2, m, right);
    }

    int64_t get(const int64_t i){
        int64_t ans = get(i, 0, 0, size);
        if(ans == -1) return 0;
        return ans;
    }

    int64_t get(const int64_t i, int64_t x, int64_t left, int64_t right){
        if(right-left == 1 ) return tree[x];

        if(tree[x] != -1) return tree[x];

        int64_t m = (left+right)/2;
        if(i < m) get(i, 2*x+1, left, m);
        else get(i, 2*x+2, m, right);
    }

    void print(){
        for(auto i : tree){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int64_t n, m; std::cin >> n >> m;
    segment_tree T; T.init(n);

    for(int64_t _ = 0; _ < m; _++){
        int64_t type; std::cin >> type;
        if(type == 1){
            int64_t l, r, v; std::cin >> l >> r >> v;
            T.modify(l, r, v);
            //T.print();
        }
        if(type == 2){
            int64_t i; std::cin >> i;
            std::cout << T.get(i) << "\n";
        }
    }

    return 0;
}
