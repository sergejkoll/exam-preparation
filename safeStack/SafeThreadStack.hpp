#ifndef EXAM_PREPARATION_SAFETHREADSTACK_HPP
#define EXAM_PREPARATION_SAFETHREADSTACK_HPP

class SafeStack {
private:
    std::stack<T> stack_;
    std::mutex mut_;
public:
    T pop();
    void Push(const T& value);
    bool TryPop(T& value);
};

template <class T>
T SafeStack<T>::pop() {
    T value;
    std::lock_guard<std::mutex> lk{ mut_ };
    if (!stack_.empty()) {
        value = stack_.top();
        stack_.pop();
    }
    return value;
}

template <class T>
void SafeStack<T>::Push(const T& value) {
    std::lock_guard<std::mutex> lk{ mut_ };
    stack_.push(value);
}

template <class T>
bool SafeStack<T>::TryPop(T& value) {
    std::lock_guard<std::mutex> lk{ mut_ };
    if (!stack_.empty() && stack_.top() == value) {
        stack_.pop();
        return true;
    }
    return false;
}

#endif //EXAM_PREPARATION_SAFETHREADSTACK_HPP
