#ifndef _1_SAFEQUEUE_SAFEQUEUE_HPP
#define _1_SAFEQUEUE_SAFEQUEUE_HPP

#include <mutex>
#include <queue>

template <class T>
class SafeQueue {
public:
    SafeQueue() = default;

    T Pop() {
        std::lock_guard<std::mutex> lock(_mutex);
        if (!_queue.empty()) {
            T deleteItem;
            deleteItem = _queue.front();
            _queue.pop();
            return deleteItem;
        } else {
            throw std::out_of_range("queue is empty");
        }
    }

    void Push(const T& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(value);
    }

    /*
    bool TryPop(T& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return false;
        value=std::move(data_queue.front());
        data_queue.pop();
        return true;
    }    
    */
    bool TryPop(T& value) {
        std::unique_lock<std::mutex> lock(_mutex, std::try_to_lock);
        if(!lock.owns_lock() && !_queue.empty()){
            value = std::move(_queue.front());
            _queue.pop();
            return true;
        } else {
            return false;
        }
    }

private:
    std::mutex _mutex;
    std::queue<T> _queue;
};
