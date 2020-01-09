#ifndef EXAM_PREPARATION_VECTOR_HPP
#define EXAM_PREPARATION_VECTOR_HPP

template <class T>
class Vector
{
private:
    T* data;
    size_t size;
    size_t capacity;
public:
    Vector() : size(0), capacity(16) {
        data = new T[capacity];
    }
    Vector(const Vector& vec) : size(vec.size), capacity(vec.capacity) {
        if (size == 0) {
            data = nullptr;
        } else {
            data = new T[capacity];
            std::memcpy(data, vec.data, sizeof(T)*size);
        }
    }

    Vector(Vector&& vec) noexcept : size(vec.size), capacity(vec.capacity), data(vec.data)  {
        vec.data = nullptr;
        vec.size = 0;
        vec.capacity= 0;
    }

    Vector& operator=(Vector&& rhs) noexcept {
        if (this != &rhs) {
            capacity = rhs.capacity;
            size = rhs.size;
            delete[] data;
            data = rhs.data;

            rhs.data = nullptr;
            rhs.size = 0;
            rhs.capacity = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    Vector& operator=(const Vector& rhs) {
        if (this != &rhs) {
            capacity = rhs.capacity;
            size = rhs.size;
            delete[] data;
            data = new T[capacity];
            std::memcpy(data, rhs.data, sizeof(T) * size);
        }
        return *this;
    }

    T& operator[](const size_t index) {
        if (size > index)
        {
            return data[index];
        } else {
            throw std::range_error("Out of range");
        }
    }
    const T& operator[](const size_t index) const
    {
        if (index >= size) {
            throw std::range_error("Out of range");
        } else {
            return data[index];
        }
    }

    void push_back(const T& value) {
        if (capacity == size) {
            if (size == 0) {
                T* newData = new T[16];
                data = newData;
                capacity = 16;
            } else {
                T* newData = new T[size * 2];
                capacity = size * 2;
                std::memcpy(newData, data, (size) * sizeof(T));
                delete[] data;
                data = newData;
            }
        }
        data[size] = value;
        ++size;
    }

};

#endif //EXAM_PREPARATION_VECTOR_HPP
