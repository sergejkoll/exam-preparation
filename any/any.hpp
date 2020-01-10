//
// Created by sergej on 09.01.2020.
//

#ifndef INC_9_ANY_ANY_HPP
#define INC_9_ANY_ANY_HPP

#include <exception>
#include <memory>

class any {
public:
    template<class Type> friend
    Type any_cast(any&);

    template <class ValueType> friend
    ValueType any_cast(const any& val);

    template<class ValueType>
    ValueType* any_cast(any* operand) noexcept;

    any() : _ptr(nullptr)
    {}

    any(const any& value) {
        if (value._ptr) {
            _ptr = value._ptr->clone();
        }
    }

    any(any&& value) noexcept
            : _ptr(std::move(value._ptr)) {}

    template <class ValueType>
    any(ValueType&& other) : _ptr(std::forward<ValueType>(other)) {}

    template <class ValueType>
    any& operator=(const ValueType& value) {
        _ptr.reset(new concrete<ValueType>(value));
        return *this;
    }

    const std::type_info& type() const noexcept {
        return _ptr->type();
    }
private:
    struct placeholder {
        virtual std::unique_ptr<placeholder> clone() const = 0;
        virtual const std::type_info& type() const = 0;
        virtual ~placeholder() = default;
    };

    template<class T>
    struct concrete : public placeholder {

        explicit concrete(T&& x)
                : _value(std::move(x))
        {}

        explicit concrete(const T& x)
                : _value(x)
        {}

        virtual std::unique_ptr<placeholder> clone() const override {
            return std::unique_ptr<placeholder>(new concrete<T>(_value));
        }

        virtual const std::type_info& type() const override {
            return typeid(T);
        }

        T _value;
    };

    std::unique_ptr<placeholder> _ptr;
};

template<class ValueType>
ValueType any_cast(const any& val) {
    if (val._ptr->type() != typeid(ValueType)) {
        throw std::bad_cast();
    }
    return static_cast<any::concrete<ValueType>*>(val._ptr.get())->_value;
}

template<class ValueType>
ValueType* any::any_cast(any* operand) noexcept {
    if (operand->_ptr->type() != typeid(ValueType)) {
        throw std::bad_cast();
    }
    return static_cast<ValueType*>(&(operand->_ptr->_value));
}

template<class ValueType>
const ValueType* any::any_cast(const any* operand) noexcept {
    return const cast<const ValueType*>(any_cast(operand)));

#endif //INC_9_ANY_ANY_HPP
