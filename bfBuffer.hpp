#pragma once

#include <vector>

template<typename _Tp, _Tp def_val = _Tp()>
class bf_buffer
{
    std::vector<_Tp> forward, backward;
    _Tp* iter = nullptr; 

    void push_back(const _Tp& data)
    {
        forward.push_back(data);
    }

    void push_front(const _Tp& data)
    {
        backward.push_back(data);
    }


public:



    bf_buffer(const _Tp& data = def_val) : forward(1, data) {
        iter = &forward[0];
    }

    _Tp& operator[](int) const = delete;

    inline void setData(const _Tp& data)
    {
        if (iter != nullptr) *iter = data;
    }

    inline constexpr const _Tp& getData() const
    {
        return *iter;
    }

    inline constexpr size_t size(bool inbytes = false) const noexcept
    {
        return inbytes ? sizeof(_Tp)*(forward.size() + backward.size())
                        : forward.size() + backward.size();
    }

    inline constexpr size_t size_left2pointer(bool inbytes = false) const noexcept
    {
        return size(inbytes) - size_right2pointer(inbytes) -1;
    }

    inline constexpr size_t size_right2pointer(bool inbytes = false) const noexcept
    {
        size_t s = 0;
        if (iter >= forward.begin().base() && iter <= forward.begin().base())
            s = forward.end().base() - iter -1;
        else if (iter >= backward.begin().base() && iter <= backward.begin().base())
            s = iter - backward.begin().base() + forward.size();
        return inbytes ? sizeof(_Tp)*s : s;
    }

    inline constexpr _Tp&  operator*()
    {
        return *iter;
    }

    const _Tp* operator++()
    {
        if (iter == backward.begin().base()) 
        {
            iter = forward.begin().base();
            return iter;
        }
        else if (iter+1 == forward.end().base())
        {
            push_back(def_val), iter = forward.end().base()-2;
        }
        return iter >= forward.begin().base() && iter <= forward.end().base() ? ++iter : --iter;
    } 

        
    const _Tp* operator++(int)
    {
        if (iter == backward.begin().base()) 
        {
            iter = forward.begin().base();
            return backward.begin().base();
        }
        else if (iter == forward.end().base()-1)
        {
            push_back(def_val), iter = forward.end().base()-2;
        }
        return iter >= forward.begin().base() && iter <= forward.end().base() ? iter++ : iter--;
    } 

    const _Tp* operator--()
    {
        if (iter == forward.begin().base()) 
        {
            if (backward.empty()) push_front(def_val);
            iter = backward.begin().base();
            return iter;
        }
        else if (iter == backward.end().base()-1)
        {
            push_front(def_val), iter = backward.end().base()-2;
        }
        return iter >= forward.begin().base() && iter <= forward.end().base() ? --iter : ++iter;
    } 

     const _Tp* operator--(int)
    {
        if (iter == forward.begin().base()) 
        {
            if (backward.empty()) push_front(def_val);
            iter = backward.begin().base();
            return forward.begin().base();
        }
        else if (iter == backward.end().base()-1)
        {
            push_front(def_val), iter = backward.end().base()-2;
        }
        return iter >= forward.begin().base() && iter <= forward.end().base() ? iter-- : iter++;
    } 

};
