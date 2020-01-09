// Copyright 2020 AndreevSemen semen.andreev00@mail.ru (librarians-squad)

#ifndef EXAM_PREPARATION_LOCK_FREE_STACK_
#define EXAM_PREPARATION_LOCK_FREE_STACK_

#include <atomic>
#include <memory>

template < typename T >
class LockFreeStack {
private:
    struct StackNode {
        T value;
        StackNode* next;

        explicit StackNode(T value)
          : value(std::move(value))
        {}
    };

    std::atomic<StackNode*> _head;
    LockFreeStack<T>* _pDump;

private:
    void _ClearLinkedList(StackNode* node) {
        while (node) {
            auto next = node->next;
            delete node;
            node = next;
        }
    }

    void Push(StackNode* node) {
        node->next = _head.load();
        while (!_head.compare_exchange_weak(node->next, node)) {}
    }

public:
    LockFreeStack()
      : _head{nullptr}
      , _pDump{nullptr}
    {}

    LockFreeStack(const LockFreeStack&) = delete;
    LockFreeStack& operator=(const LockFreeStack&) = delete;

    ~LockFreeStack() {
        _ClearLinkedList(_head.load());
        delete _pDump;
    }

    void Push(const T& value) {
        auto newNode = new StackNode{value};
        Push(newNode);
    }

    bool TryPop(T& bucket) {
        if (!_pDump) {
            _pDump = new LockFreeStack{};
        }

        auto oldNode = _head.load();
        while (oldNode && !_head.compare_exchange_weak(oldNode, oldNode->next)) {}

        if (!oldNode) {
            return false;
        }

        bucket = oldNode->value;
        _pDump->Push(oldNode);
        return true;
    }
};

#endif // EXAM_PREPARATION_LOCK_FREE_STACK_
