// src.hpp – full MyList implementation for ACMOJ submission.

#ifndef SRC_HPP
#define SRC_HPP

template <typename ValueType>
class MyList {
public:
    MyList() : head_(nullptr), tail_(nullptr), sz_(0) {}

    MyList(MyList &&obj) noexcept : head_(obj.head_), tail_(obj.tail_), sz_(obj.sz_) {
        obj.head_ = obj.tail_ = nullptr; obj.sz_ = 0; }

    MyList(const MyList &obj) : head_(nullptr), tail_(nullptr), sz_(0) {
        Node* cur = obj.head_; while (cur) { push_back(cur->value); cur = cur->next; } }

    ~MyList() { clear(); }

    void push_back(const ValueType &value) {
        Node* n = new Node(value);
        if (!tail_) head_ = tail_ = n; else { tail_->next = n; n->prev = tail_; tail_ = n; }
        ++sz_; }

    void pop_back() {
        if (!tail_) return; Node* del = tail_; tail_ = tail_->prev;
        if (tail_) tail_->next = nullptr; else head_ = nullptr; delete del; --sz_; }

    void push_front(const ValueType &value) {
        Node* n = new Node(value);
        if (!head_) head_ = tail_ = n; else { n->next = head_; head_->prev = n; head_ = n; }
        ++sz_; }

    void pop_front() {
        if (!head_) return; Node* del = head_; head_ = head_->next;
        if (head_) head_->prev = nullptr; else tail_ = nullptr; delete del; --sz_; }

    ValueType &front() const { return head_->value; }
    ValueType &back() const { return tail_->value; }

    void insert(int index, const ValueType &value) {
        if (index <= 0) { push_front(value); return; }
        if (index >= sz_) { push_back(value); return; }
        Node* cur = node_at(index);
        Node* n = new Node(value);
        n->prev = cur->prev; n->next = cur; cur->prev->next = n; cur->prev = n; ++sz_; }

    void erase(int index) {
        if (index < 0 || index >= sz_) return;
        if (index == 0) { pop_front(); return; }
        if (index == sz_-1) { pop_back(); return; }
        Node* cur = node_at(index);
        cur->prev->next = cur->next; cur->next->prev = cur->prev; delete cur; --sz_; }

    int size() const { return sz_; }
    bool empty() const { return sz_ == 0; }

    void clear() { while (head_) { Node* nxt = head_->next; delete head_; head_ = nxt; } tail_ = nullptr; sz_ = 0; }

    void link(const MyList &obj) { Node* cur = obj.head_; while (cur) { push_back(cur->value); cur = cur->next; } }

    MyList cut(int index) {
        MyList tailPart;
        if (index <= 0) { tailPart.head_ = head_; tailPart.tail_ = tail_; tailPart.sz_ = sz_; head_ = tail_ = nullptr; sz_ = 0; return tailPart; }
        if (index >= sz_) return tailPart;
        Node* splitNode = node_at(index);
        tailPart.head_ = splitNode; tailPart.tail_ = tail_; int cnt = 0; for (Node* p = splitNode; p; p = p->next) ++cnt; tailPart.sz_ = cnt;
        tail_ = splitNode->prev; if (tail_) tail_->next = nullptr; splitNode->prev = nullptr; sz_ -= cnt; return tailPart; }

private:
    struct Node { ValueType value; Node *prev = nullptr, *next = nullptr; explicit Node(const ValueType &v) : value(v) {} };
    Node* head_; Node* tail_; int sz_;
    Node* node_at(int index) const { Node* cur = head_; while (index-- > 0 && cur) cur = cur->next; return cur; }
};

#endif // SRC_HPP

