// по сути функция weight_sum работает так же как и обычная сумма на отрезке, только возвращается взвешанная сумма, которая пересчитывается
// хитрым образом
#include <iostream>
#include <vector>

struct segment_tree{
    struct Node{
        int64_t add;        // добавляем элеент на отрезок
        int64_t cnt;        // количество эдементов на отрезке
        int64_t sum;        // сумма на отрезке
        int64_t weightSum;  // взвешанная сумма на отрезке
    };
    int64_t size;
    std::vector<Node> tree;

    void build_empty(int64_t x, int64_t left, int64_t right){
        if(right-left == 1){
            tree[x].add = tree[x].sum = tree[x].weightSum = 0;
            tree[x].cnt = 1;
        }else{
            int64_t m = (left+right)/2;
            build_empty(2*x+1, left, m);
            build_empty(2*x+2, m, right);
            tree[x].cnt = tree[2*x+1].cnt + tree[2*x+2].cnt;
            tree[x].add = tree[x].sum = tree[x].weightSum = 0;
        }
    }

    void init(const int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.resize(2*size-1);
        build_empty(0, 0, size);
    }

    void propagate(int64_t x, int64_t left, int64_t right){
        if(right-left == 1){
            tree[x].add = 0;
            return;
        }
        tree[2*x+1].add += tree[x].add;
        tree[2*x+2].add += tree[x].add;
        
        tree[2*x+1].sum += tree[2*x+1].cnt*tree[x].add;
        tree[2*x+2].sum += tree[2*x+2].cnt*tree[x].add;

        int64_t S1 = ((1+tree[2*x+1].cnt)*tree[2*x+1].cnt)/2;   // сумма арифм. прогресси 1 + 2 + 3 + ... + tree[x].cnt;
        tree[2*x+1].weightSum += tree[x].add*S1;

        int64_t S2 = ((1+tree[2*x+2].cnt)*tree[2*x+2].cnt)/2;   // сумма арифм. прогресси 1 + 2 + 3 + ... + tree[x].cnt;
        tree[2*x+2].weightSum += tree[x].add*S2;

        tree[x].add = 0;
    }

    void UpdateNode(int64_t x, int64_t left, int64_t right, int64_t d){
        tree[x].add += d;
        tree[x].sum += tree[x].cnt*d;
        int64_t S = ((1+tree[x].cnt)*tree[x].cnt)/2;
        tree[x].weightSum += d*S;
    }

    void UpdateFromChildren(int64_t x, int64_t left, int64_t right){
        if(right-left == 1) return;
        tree[x].sum = tree[2*x+1].sum + tree[2*x+2].sum;
        tree[x].weightSum = tree[2*x+1].weightSum + (tree[x].cnt/2)*tree[2*x+2].sum + tree[2*x+2].weightSum;
    }

    void add(const int64_t l, const int64_t r, const int64_t d){
        add(l, r, d, 0, 0, size);
    }

    void add(int64_t L, int64_t R, int64_t d, int64_t x, int64_t left, int64_t right){
        propagate(x, left, right);

        if(L >= right || R <= left) return;
        if(L <= left && R >= right){
            UpdateNode(x, left, right, d);
            return;
        }

        int64_t m = (left+right)/2;
        add(L, R, d, 2*x+1, left, m);
        add(L, R, d, 2*x+2, m, right);

        UpdateFromChildren(x, left, right);
    }

    int64_t weight_sum(int64_t l, int64_t r){
        return weight_sum(l, r, 0, 0, size);
    }

    int64_t weight_sum(int64_t L, int64_t R, int64_t x, int64_t left, int64_t right){
        propagate(x, left, right);

        if( L >= right || R <= left ) return 0;
        if(L <= left && R >= right) return (left-L)*tree[x].sum + tree[x].weightSum;
        
        int64_t m = (left+right)/2;
        int64_t s1 = weight_sum(L, R, 2*x+1, left, m);
        int64_t s2 = weight_sum(L, R, 2*x+2, m, right);
        return s1+s2;
    }

    void print(){
        for(auto it : tree){
            std::cout << "( " << it.sum << " " << it.weightSum << " )" << " ";
        }
        std::cout << "\n";
    }

};

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int64_t n, m; std::cin >> n >> m;

    segment_tree T; T.init(n);

    for(int64_t i = 0; i < n; i++){
        int64_t a; std::cin >> a;
        T.add(i, i+1, a);
    }

    //T.print();

    for(int64_t _ = 0; _ < m ; _++){
        int64_t t, l, r; std::cin >> t >> l >> r;
        l--;
        if(t == 1){
            int64_t d; std::cin >> d;
            T.add(l, r, d);
            //T.print();
        }
        if(t == 2){
            std::cout << T.weight_sum(l, r) << "\n";
        }
    }

    return 0;
}
