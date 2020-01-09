#ifndef EXAM_PREPARATION_STRING_HPP
#define EXAM_PREPARATION_STRING_HPP


class String {
public:
    ~String() {
        delete[] Data;
    }

    String() {
        size = 0;
        Data = new char[1];
    }

    String(const String& rhs) {
        size = std::strlen(rhs.Data);
        Data = new char[size + 1];
        std::memcpy(Data, rhs.Data, sizeof(char) * (size + 1));
    }

    String(String&& rhs) {
        Data = rhs.Data;
        size = rhs.size;

        rhs.Data = nullptr;
        rhs.size = 0;
    }

    String& operator=(String&& rhs) {
        if (this != &rhs) {
            delete[] Data;
            size = rhs.size;
            Data = rhs.Data;

            rhs.Data = nullptr;
            rhs.size = 0;
        }
        return *this;
    }
    explicit String(const char* data) {
        size = std::strlen(data);
        Data = new char[size + 1];
        std::memcpy(Data, data, sizeof(char) * (size + 1));
    }

    String& operator=(const String& rhs) {
        if (this != &rhs) {
            delete[] Data;
            size = rhs.size;
            Data = new char[size + 1];
            std::memcpy(Data, rhs.Data, sizeof(char) * (size + 1));
        }
        return *this;
    }

    char operator[](size_t index) const {
        return Data[index];
    }

    char& operator[](size_t index) {
        return Data[index];
    }

    String& append(const String& rhs) {
        char* ans = new char[size + rhs.size + 1];
        std::memcpy(ans, Data, sizeof(char) * size);
        std::memcpy(ans + size, rhs.Data, sizeof(char) * (rhs.size + 1));
        delete[] Data;
        Data = ans;
        size += rhs.size;
        return *this;
    }

private:
    char* Data;
    size_t size;
};

#endif //EXAM_PREPARATION_STRING_HPP
