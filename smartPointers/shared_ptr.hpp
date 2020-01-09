#ifndef EXAM_PREPARATION_SHARED_PTR_HPP
#define EXAM_PREPARATION_SHARED_PTR_HPP

template <class T>
class shared_ptr {
    std::atomic<unsigned int>* quantity_;
    T* ptr_;
    void Deleter() {
        --(*quantity_);
        if (*quantity_ == 0) {
            if (ptr_ != nullptr) {
                delete ptr_;
                ptr_ = nullptr;
            }
            if (quantity_ != nullptr) {
                delete quantity_;
                quantity_ = nullptr;
            }
        }
    }

public:
    shared_ptr() {
        quantity_ = nullptr;
        ptr_ = nullptr;
    }

    ~shared_ptr() {
        Deleter();
    }

    /*shared_ptr(shared_ptr<T>&& rhs) {
        ptr_(std::move(rhs.ptr_));
        quantity_(std::move(rhs.quantity_));
    }*/

    shared_ptr<T>& operator=(shared_ptr<T>&& rhs) noexcept {
        std::swap(*this, rhs);
        rhs.Deleter();
        return *this;
    }

    shared_ptr<T>& operator=(const shared_ptr<T>& rhs) {
        if (ptr_ != nullptr) {
            delete ptr_;
            ptr_ = nullptr;
        }

        if (quantity_ != nullptr) {
            delete quantity_;
            quantity_ = nullptr;
        }

        ptr_ = rhs.ptr_;
        quantity_ = rhs.quantity_;
        ++(*quantity_);
        return *this;
    }

    shared_ptr(const shared_ptr<T>& rhs) {
        ptr_ = rhs.ptr_;
        quantity_ = rhs.quantity_;
        ++(*quantity_);
    }

    void reset(T* ptr = nullptr) {
        if (ptr_ != ptr) {
            Deleter();
            ptr_ = ptr;
            *quantity_ = 1;
        }
    }

    T* release() {
        return ptr_;
    }

    void swap(shared_ptr<T>& rhs) {
        if (this != &rhs) {
            std::swap(quantity_, rhs.quantity_);
            std::swap(ptr_, rhs.ptr_);
        }
    }

    T* operator->() {
        return ptr_;
    }

    T& operator*() {
        return *ptr_;
    }

    operator bool() const {
        return ptr_;
    }

    T* get() {
        return ptr_;
    }
};
#endif //EXAM_PREPARATION_SHARED_PTR_HPP
