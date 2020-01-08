#ifndef EXAM_PREPARATION_UNIQUEPTR_HPP
#define EXAM_PREPARATION_UNIQUEPTR_HPP
template<class T>
class unique_ptr {
    T* ptr = nullptr;
public:
    unique_ptr() {
        ptr = new T(nullptr);
    }

    ~unique_ptr() {
        delete ptr;
    }

    unique_ptr(unique_ptr<T>&& other) noexcept {
        ptr = new T(other->ptr);
        other->~unique_ptr();
    }

    unique_ptr<T>& operator=(unique_ptr<T>&& other) noexcept {
        ptr = new T(other->ptr);
        other->unique_ptr();
    }

    void reset(T* _ptr = nullptr) {
        delete ptr;
        ptr = _ptr;
    }

    T* release() {
        return ptr;
    }

    void swap(unique_ptr<T>&& other) {
        std::swap(this, other);
    }
    T* operator->() {
        return ptr;
    }

    T& operator*() {
        return *ptr;
    }

    explicit operator bool() const {
        return ptr;
    }

    T* get() {
        return ptr;
    }
};

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //EXAM_PREPARATION_UNIQUEPTR_HPP
