// Copyright LIBRARIANS SQUAD 2020
#ifndef EXAM_PREPARATION_SAFETHREADQUEUE_HPP
#define EXAM_PREPARATION_SAFETHREADQUEUE_HPP

template <class T>
class SafeQueue {
private:
    std::queue<T> queue_;
    std::mutex mut_;
public:
    T pop();
    void Push(const T& value);
    bool TryPop(T& value);
};

template <class T>
T SafeQueue<T>::pop() {
    T value;
    std::lock_guard<std::mutex> lk{ mut_ };
    value = queue_.front();
    queue_.pop();
    return value;
}

template <class T>
void SafeQueue<T>::Push(const T& value) {
    std::lock_guard<std::mutex> lk{ mut_ };
    queue_.push(value);
}

template <class T>
bool SafeQueue<T>::TryPop(T& value) {
    std::lock_guard<std::mutex> lk{ mut_ };
    if (!queue_.empty() && queue_.front() == value) {
        queue_.pop();
        return true;
    }
    return false;
}
#endif //EXAM_PREPARATION_SAFETHREADQUEUE_HPP
