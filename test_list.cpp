#include <iostream>

struct N
{
    int a = 0;
    struct N* n = nullptr;
};

void dump(N* r)
{
    for(N* it = r; it != nullptr; it = it->n) {
        std::cout << "n = " << it
                  << " a = " << it->a
                  << " n = " << it->n << "\n";
    }
    std::cout << "\n";
}

void destroy(N* r)
{
    while(r != nullptr)
    {
        N* n = r->n;
        delete r;
        r = n;
    }
}

int main(int, char**)
{
    N* r = nullptr;
    std::cout << "r = " << r << "\n";
    N* tmp = nullptr;
    tmp = r = new N;
    tmp->a = 1;

    dump(r);

    tmp = tmp->n = new N;
    tmp->a = 2;

    tmp = tmp->n = new N;
    tmp->a = 3;

    dump(r);

    destroy(r);

    return 0;
}
