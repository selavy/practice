#include <catch2/catch.hpp>
#include <vector>
#include <utility>
#include <memory>
#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <cassert>

template <class T>
class RingBuffer
{
    static_assert(std::is_pod<T>::value, "Only POD values are supported");
public:
    RingBuffer(size_t maxlen, T value)
        : _length(_find_length(maxlen))
        , _head(0)
        , _buffer(std::make_unique<T[]>(_length))
    {
        assert((_length & (_length - 1)) == 0 && "length must be power of 2");
        for (size_t i = 0; i < _length; ++i) {
            _buffer[i] = value;
        }
    }

    void push_front(T value) noexcept {
        _head = _head == 0 ? _length - 1 : _head - 1;
        _buffer[_head] = value;
    }

    void push_back(T value) noexcept {
        size_t index = (_head + _length) & (_length - 1);
        _buffer[index] = value;
        _head = (_head + 1) & (_length - 1);
    }

    T get(size_t i) const noexcept {
        assert(i < _length);
        size_t index = (_head + i) & (_length - 1);
        return _buffer[index];
    }

    T operator[](size_t i) const noexcept {
        return get(i);
    }

    size_t length() const noexcept {
        return _length;
    }

private:
    static uint32_t _find_length(uint32_t x) noexcept
    {
        if (x <= 8) {
            return 8;
        } else {
            return 1 << (32 - __builtin_clz (x - 1));
        }
    }

    size_t               _length;
    size_t               _head;
    std::unique_ptr<T[]> _buffer;
};

TEST_CASE("Ring Buffer push_back", "[ring_buffer]")
{
    RingBuffer<int> r(8, -1);
    for (int iter = 0; iter < 20; ++iter) {
        for (int i = 0; i < 8; ++i) {
            r.push_back(i);
            REQUIRE(r.get(7) == i);
        }
    }
    for (int i = 0; i < 8; ++i) {
        REQUIRE(r.get(i) == i);
    }
}

TEST_CASE("Ring Buffer push_front", "[ring_buffer]")
{
    RingBuffer<int> r(8, -1);
    for (int iter = 0; iter < 20; ++iter) {
        for (int i = 0; i < 8; ++i) {
            r.push_front(i);
            REQUIRE(r.get(0) == i);
        }
    }
    for (int i = 0; i < 8; ++i) {
        REQUIRE(r.get(i) == (7 - i));
    }
}

TEST_CASE("Buffer size rounding", "[ring_buffer]")
{
    RingBuffer<double> r(15, NAN);
    REQUIRE(r.length() == 16);
}
