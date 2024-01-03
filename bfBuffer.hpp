#pragma once

#include <deque>


template<typename _Tp, const _Tp def_val = _Tp()>
class bf_buffer
{
    std::deque<_Tp> buffer;
    typename std::deque<_Tp>::iterator iter;

public:
    bf_buffer(const _Tp& data = def_val) : buffer(1, data) {
        iter = buffer.begin();
    }

    _Tp& operator[](int) const = delete;

    inline void setData(const _Tp& data)
    {
        *iter = data;
    }

    inline constexpr const _Tp& getData() const
    {
        return *iter;
    }

    inline constexpr size_t size(bool inbytes = false) const noexcept
    {
        return inbytes ? sizeof(_Tp) * buffer.size() : buffer.size();
    }

    inline constexpr size_t size_left2pointer(bool inbytes = false) const noexcept
    {
        return size(inbytes) - size_right2pointer(inbytes) - 1;
    }

    inline constexpr size_t size_right2pointer(bool inbytes = false) const noexcept
    {
        size_t s = buffer.end() - iter -1;
        return inbytes ? sizeof(_Tp) * s : s;
    }

    inline constexpr _Tp& operator*()
    {
        return *iter;
    }

    inline typename std::deque<_Tp>::iterator operator++()
    {
        if (iter == buffer.end()-1) buffer.push_back(def_val), iter = buffer.end()-1;
        else return ++iter;
        return iter;
    }

    inline typename std::deque<_Tp>::iterator operator++(int)
    {
        if (iter == buffer.end()-1) buffer.push_back(def_val), iter = buffer.end()-1;
        else return iter++;
        return iter-1;
    }

    inline typename std::deque<_Tp>::iterator operator--()
    {
        if (iter == buffer.begin()) buffer.push_front(def_val), iter = buffer.begin();
        else return --iter;
        return iter;
    }

    inline typename std::deque<_Tp>::iterator operator--(int)
    {
        if (iter == buffer.begin()) buffer.push_front(def_val), iter = buffer.begin();
        else return iter--;
        return iter+1;
    }

    template<typename _DT>
    inline typename std::deque<_Tp>::iterator operator+=(const _DT& val)
    {
        if (iter+val >= buffer.end()) buffer.resize(iter-buffer.begin()+val+1, def_val), iter = buffer.end()-1;
        else iter += val;
        return iter;
    }

    template<typename _DT>
    inline typename std::deque<_Tp>::iterator operator-=(const _DT& val)
    {
        if (iter-val < buffer.begin()) buffer.insert(buffer.cbegin(), buffer.begin()-iter+val, def_val), iter = buffer.begin();
        else iter -= val;
        return iter;
    }

};
