template <class T>
class CircularBuffer {
private:
    size_t head = 0;
    size_t tail = 0;
    size_t capacity = 0;
    size_t size = 0;
    T* buffer;

    void increment_head() {
        if (head < capacity - 1)
            head++;
        else
            head = 0;
    }

    void increment_tail() {
        if (tail < capacity - 1)
            tail++;
        else
            tail = 0;
    }

    void decrement_head() {
        if (head > 0)
            head--;
        else
            head = capacity - 1;
    }

    void decrement_tail() {
        if (tail > 0)
            tail--;
        else
            tail = capacity - 1;
    }

public:
    class Iterator {
    private:
        T* ptr;
        T* buf;
        size_t pos{};
        size_t tail{};
        int capacity{};
    public:
        using iterator_category [[maybe_unused]] = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type [[maybe_unused]] = std::ptrdiff_t;
        using pointer [[maybe_unused]] = value_type*;
        using reference [[maybe_unused]] = value_type&;

        Iterator(T* ptr, T* b, size_t p, size_t t, int c)
            : ptr(ptr), buf(b), pos(p), tail(t), capacity(c) {}

        Iterator() : buf(nullptr) {}

        Iterator& operator++ () {
            ++ptr;
            ++pos;
            return *this;
        }

        T& operator*() {
            return buf[(tail - pos) % capacity];
        }

        T* operator-> () const {
            return &(operator*());
        }

        Iterator operator+ (int value) {
            return Iterator(ptr + value, buf, pos + value, tail, capacity);
        }

        Iterator& operator+= (int value) {
            ptr += value;
            pos += value;
            return *this;
        }

        Iterator& operator-= (int value) {
            ptr -= value;
            pos -= value;
            return *this;
        }

        Iterator operator- (int value) {
            return Iterator(ptr - value, buf, pos - value, tail, capacity);
        }

        difference_type operator- (Iterator it) {
            return ptr - it.ptr;
        }

        Iterator& operator--() {
            --ptr;
            --pos;
            return *this;
        }

        bool operator== (const Iterator& t) const {
            return pos == t.pos;
        }

        bool operator!= (const Iterator& t) const {
            return pos != t.pos;
        }

        bool operator>= (const Iterator& t) const {
            return pos >= t.pos;
        }

        bool operator<= (const Iterator& t) const {
            return pos <= t.pos;
        }

        bool operator< (const Iterator& t) const {
            return pos < t.pos;
        }

        bool operator> (const Iterator& t) const {
            return pos > t.pos;
        }
    };

    explicit CircularBuffer(T value) {
        capacity = value;
        buffer = new T[capacity];
    }

    void addLast(T value) {
        if (size == capacity)
            buffer[head] = value;
        else {
            size++;
            decrement_head();
            buffer[head] = value;
        }
    }

    void delLast() {
        if (size == capacity)
            throw std::out_of_range("CircularBuffer is empty");
        size--;
        increment_head();
    }

    void addFirst(T value) {
        buffer[tail] = value;
        if (size == capacity)
            increment_head();
        else
            size++;
        increment_tail();
    }

    void delFirst() {
        if (size == 0)
            throw std::out_of_range("CircularBuffer is empty");
        --size;
        decrement_tail();
    }

    void changeCapacity(int new_capacity) {
        T* tmp = new T[capacity];
        int count = 0;
        int capacityToInt = capacity;
        for (int i = head; i < capacityToInt; i++) {
            tmp[count] = buffer[i];
            count++;
        }
        int tailToInt = tail;
        for (int i = 0; i < tailToInt; i++) {
            tmp[count] = buffer[i];
            count++;
        }
        head = 0;
        tail = size;
        capacity = new_capacity;
        delete[] buffer;
        buffer = tmp;
    }

    T first() const {
        if (size == 0)
            throw std::out_of_range("CircularBuffer is empty");
        if (tail != 0)
            return buffer[tail - 1];
        else return buffer[capacity - 1];
    }

    T last() const {
        if (size == 0)
            throw std::out_of_range("CircularBuffer is empty");
        return buffer[head];
    }

    T &operator[](int i) {
        int sizeToInt = size;
        if (sizeToInt == 0){
            throw std::out_of_range("CircularBuffer is empty");
        }
        if (i >= sizeToInt){
            string answer = "Index out of range: asking for " + std::to_string(i) + ", max index " + std::to_string(sizeToInt - 1);
            throw std::out_of_range(answer);
        }
        return buffer[(tail - 1 - i) % capacity];
    }

    //fixed index and size information in exception
    T operator[](int i) const{
        int sizeToInt = size;
        if (sizeToInt == 0){
            throw std::out_of_range("CircularBuffer is empty");
        }
        if (i >= sizeToInt){
            string answer = "Index out of range: asking for " + std::to_string(i) + ", max index " + std::to_string(sizeToInt - 1);
            throw std::out_of_range(answer);
        }
        return buffer[(tail - 1 - i) % capacity];
    }

    Iterator begin() const {
        if (tail != 0)
            return Iterator(buffer, buffer, 0, tail - 1, capacity);
        return Iterator(buffer, buffer, 0, capacity - 1, capacity);
    }
    Iterator end() const {
        if (tail != 0)
            return Iterator(&buffer[size], buffer, size, tail - 1, capacity);
        return Iterator(&buffer[size], buffer, size, capacity - 1, capacity);
    }

};
