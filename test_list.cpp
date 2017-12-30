#include <iostream>

struct Node
{
    int a = 0;
    struct Node* n = nullptr;
};

void dump(Node* r)
{
    for(Node* it = r; it != nullptr; it = it->n) {
        std::cout << "n = " << it
                  << " a = " << it->a
                  << " n = " << it->n << "\n";
    }
    std::cout << "\n";
}

void destroy(Node* r)
{
    while(r != nullptr)
    {
        Node* n = r->n;
        delete r;
        r = n;
    }
}

int main(int, char**)
{
    Node* r = nullptr;
    std::cout << "r = " << r << "\n";
    Node* tmp = nullptr;
    tmp = r = new Node;
    tmp->a = 1;

    dump(r);

    tmp = tmp->n = new Node;
    tmp->a = 2;

    tmp = tmp->n = new Node;
    tmp->a = 3;

    dump(r);

    destroy(r);

    return 0;
}
