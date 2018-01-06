#include <iostream>

#define LINE(n)  std::cout << "---------- " << n << " ----------\n";

struct Node
{
    int data;
    Node(int v) : data(v) {}
    struct Node* next = nullptr;
};

void dump(Node* head)
{
    for(Node* it = head; it != nullptr; it = it->next) {
        std::cout << "ptr = " << it
                  << "; data = " << it->data
                  << "; next = " << it->next << "\n";
    }
    std::cout << "\n";
}

void destroy(Node* head)
{
    while(head != nullptr)
    {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

int main(int, char**)
{
    Node* head = nullptr;

    LINE("Creating tmp list");
    Node* tmp_head = nullptr;
    Node* tmp_next = nullptr;
    for (int i = 0; i < 5; ++i) {
        tmp_next = tmp_head;
        tmp_head = new Node(i+1);
        tmp_head->next = tmp_next;
    }
    dump(tmp_head);

    LINE("Copy tmp into original list");
    for (Node *orig = head, *tmp = tmp_head;
         orig != nullptr && tmp != nullptr;
         orig = orig->next, tmp = tmp->next)
    {
        tmp->data = orig->data;
    }

    LINE("Destroy original list");
    destroy(head);

    LINE("Assign original list");
    head = tmp_head;

    dump(head);

    LINE("Creating expanded list");

    tmp_head = nullptr;
    tmp_next = nullptr;
    for (int i = 0; i < 8; ++i) {
        tmp_next = tmp_head;
        tmp_head = new Node(0);
        tmp_head->next = tmp_next;
    }
    dump(tmp_head);

    LINE("Copy original into expanded list");
    for (Node *orig = head, *tmp = tmp_head;
         orig != nullptr && tmp != nullptr;
         orig = orig->next, tmp = tmp->next)
    {
        tmp->data = orig->data;
    }

    LINE("Destroy original list");
    destroy(head);

    LINE("Assign expanded to original list");
    head = tmp_head;

    dump(head);

    LINE("Creating shrinked list");

    tmp_head = nullptr;
    tmp_next = nullptr;
    for (int i = 0; i < 3; ++i) {
        tmp_next = tmp_head;
        tmp_head = new Node(0);
        tmp_head->next = tmp_next;
    }
    dump(tmp_head);

    LINE("Copy original into shrinked list");
    for (Node *orig = head, *tmp = tmp_head;
         orig != nullptr && tmp != nullptr;
         orig = orig->next, tmp = tmp->next)
    {
        tmp->data = orig->data;
    }

    LINE("Destroy original list");
    destroy(head);

    LINE("Assign shrinked to original list");
    head = tmp_head;

    dump(head);

    destroy(head);

    return 0;
}
