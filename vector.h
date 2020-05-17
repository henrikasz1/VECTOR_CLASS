#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include<sstream>
#include <memory>
#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <cmath>
#include <memory>
#include <algorithm>
#include<iostream>
#include<ctime>
#include<string>
#include<numeric>
#include<limits>
#include<fstream>
#include<random>
#include<chrono>

#define MAX_SIZE 1000000000

using namespace std;

template <class T> class Vec
{
public:
    //member types
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef ptrdiff_t difference_type;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // rule of three
    Vec()
    {
        create();
    }
    explicit Vec(size_type n, const T& t = T{})
    {
        create(n, t);
    }
    Vec(const Vec& v)
    {
        create(v.begin(), v.end());
    }
    Vec& operator=(const Vec&);
    ~Vec()
    {
        uncreate();
    }

    reference operator[](size_type i)
    {
        return data_[i];    //    []
    }
    const reference operator[](size_type i) const
    {
        return data_[i];    //    []
    }
    //iterators
    iterator begin()
    {
        return data_;    //begin()
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(avail);
    }
    const_reverse_iterator crbegin() const
    {
        return reverse_iterator(avail);
    }
    reverse_iterator rend()
    {
        return reverse_iterator(data_);
    }
    const_reverse_iterator crend() const
    {
        return reverse_iterator(data_);
    }
    const_iterator cbegin() const
    {
        return data_;    //begin()
    }
    iterator end()
    {
        return avail;    //end()
    }
    const_iterator cend() const
    {
        return avail;    //end()
    }
    reference at(int i)
    {
        return data_[i];
    }
    reference front()
    {
        return data_[0];
    }
    reference back()
    {
        return data_[size()-1];
    }
    iterator data() noexcept
    {
        return data_;
    };

    //modifiers
    void push_back(const T& t);     //push_back()
    void pop_back();
    void swap(Vec<T>& l) noexcept;
    void clear();
    void insert(const_iterator it, const_reference value);
    void insert(const_iterator it, int n, const_reference value);
    void emplace_back(T temp);
    void resize(int it, T value);
    void resize(int it);
    void erase(const_iterator it);
    void erase(const_iterator it_1, const_iterator it_2);
    void emplace(const_iterator it, const_reference args);
    void assign(size_t n, const_reference value);
    void assign(const_iterator start, const_iterator finish);
    //capacity
    size_type size() const
    {
        return avail - data_;    //size()
    }
    size_type capacity() const
    {
        return limit - data_;
    }
    size_type max_size() const
    {
        return MAX_SIZE;    //-
    }
    void shrink_to_fit() const;
    bool empty();
    void reserve(const int x);

    bool operator==(const Vec<T>& l) const;
    bool operator!=(const Vec<T>& l) const;
    bool operator<(const Vec<T>& l) const;
    bool operator>(const Vec<T>& l) const;
    bool operator<=(const Vec<T>& l) const;
    bool operator>=(const Vec<T>& l) const;
private:
    iterator data_;
    iterator avail;
    iterator limit;


    allocator<T> alloc; // objektas atminties valdymui
    // iðskirti atmintá (array) ir jà inicializuoti
    void create() ;
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);
    // sunaikinti elementus array ir atlaisvinti atmintá
    void uncreate();
    // pagalbinës funkcijos push_back realizacijai
    void grow();
    void unchecked_append(const T&);
};
//asign()
template <class T>
void Vec<T>::assign(size_t n, const_reference value)
{
    this->uncreate();
    for (size_t i=0; i!=n; i++)
    {
        this->push_back(value);
    }
}
//assign()
template <class T>
void Vec<T>::assign(const_iterator start, const_iterator finish)
{
    this->uncreate();
    for (Vec<T>::const_iterator i = start; i!= finish; i++)
    {
        this->push_back(*i);
    }
}
//erase()
template <class T>
void Vec<T>::erase(const_iterator it_1, const_iterator it_2)
{
    if (it_1<data_ || it_2>avail)
    {
        throw out_of_range{"erase()"};
    }
    int first = 0, second = 0;
    for (auto i = begin(); i < it_1; i++)
    {
        first++;
    }
    for (auto i = begin(); i < it_2; i++)
    {
        second++;
    }
    for (first; first < size() - second; first++)
    {
        data_[first] = data_ [first+second];
    }
    avail -=second;
}
//erase()
template<class T>
void Vec<T>::erase(const_iterator it)
{
    if (it < data_ || it > avail)
        throw out_of_range{ "erase()" };
    int temp = 0;
    for (auto i = begin(); i < it; i++)
    {
        temp++;
    }
    for (temp; temp < size(); temp++)
    {
        data_[temp] = data_[temp + 1];
    }
    avail--;
}
//resize()
template <class T>
void Vec<T>::resize(int it)
{
    int count = 0;
    if (it < this->size())
    {
        for (size_t i=it; i!=this->size(); i++)
        {
            this->data_[i] = 0;
            count ++;
        }
        avail -= count;
    }
    else
    {
        int sz = this->size();
        this->avail += it - this->size();
        for (size_t i=sz; i!=it; i++)
        {
            this->data_[i] = 0;
        }
    }
}
//resize()
template <class T>
void Vec<T>::resize(int it, T value)
{
    if (it > this->size())
    {
        int sz = this->size();
        this->avail += it - this->size();
        for (size_t i=sz; i!=it; i++)
        {
            this->data_[i] = value;
        }
    }
    else
        resize(it);
}
//create()
template <class T>
void Vec<T>::create()
{
    data_ = avail = limit = nullptr;
}
template <class T>
void Vec<T>::create(size_type n, const T& val)
{
    data_ = alloc.allocate(n); // gràþina ptr á array pirmà elementà
    limit = avail = data_ + n; // sustato rodykles á vietas
    uninitialized_fill(data_, limit, val); // inicializuoja elementus val reikðme
}
template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data_ = alloc.allocate(j - i); // iðskirti vietos j-i elementams
    limit = avail = uninitialized_copy(i, j, data_); // nukopijuoja elementus ið intervalo
}
//uncreate()
template <class T>
void Vec<T>::uncreate()
{
    if (data_)
    {
// sunaikinti (atbuline tvarka) sukonstruotus elementus
        iterator it = avail;
        while (it != data_)
            alloc.destroy(--it);
// atlaisvinti iðskirtà atmintá. Turi bûti data_ != nullptr
        alloc.deallocate(data_, limit - data_);
    }
// reset'inam pointer'iuss - Vector'ius tuðèias
    data_ = limit = avail = nullptr;
}
template <class T>
void Vec<T>::grow()
{
// dvigubai daugiau vietos, nei buvo
    size_type new_size = max(2 * (limit - data_), ptrdiff_t(1));
// iðskirti naujà vietà ir perkopijuoti egzistuojanèius elementus
    iterator new_data_ = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data_, avail, new_data_);
// atlaisvinti senà vietà
    uncreate();
// reset'int rodykles á naujai iðskirtà vietà
    data_ = new_data_;
    avail = new_avail;
    limit = data_ + new_size;
}
// tariame, kad `avail` point'ina á iðskirtà, bet neinicializuotà vietà
template <class T>
void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}
//emplace()
template <class T>
void Vec<T>::emplace(const_iterator it, const_reference args) //does not avoid copying, so it is the same as insert()
{
    int temp = 0;
    for (auto i = this->begin(); i != it; i++)
    {
        temp++;
    }
    //from grow() function
    size_type new_size = this->size()+1;
    iterator new_data_ = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data_, avail+1, new_data_);
    for (size_t i=0; i<temp; i++)
    {
        new_data_[i] = data_[i];
    }
    new_data_[temp] = args;
    for (size_t i=temp+1; i!=new_size; i++)
    {
        new_data_[i] = data_[i-1];
    }
    uncreate();
    //from grow() function
    data_ = new_data_;
    avail = new_avail;
    limit = data_ + new_size;
}
//push_back()
template <class T>
void Vec<T>::push_back(const T& t)
{
    if (avail == limit)
        grow();
    unchecked_append(t);
}
//pop_back()
template <class T>
void Vec<T>::pop_back()
{
    if(avail)
        avail--;
}
template <class T>
void Vec<T>::emplace_back(T temp)
{
    this->push_back(temp);
}
//insert()
template <class T>
void Vec<T>::insert(const_iterator it, const_reference value)
{
    int temp = 0;
    for (auto i = this->begin(); i != it; i++)
    {
        temp++;
    }
    //from grow() function
    size_type new_size = this->size()+1;
    iterator new_data_ = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data_, avail+1, new_data_);
    for (size_t i=0; i<temp; i++)
    {
        new_data_[i] = data_[i];
    }
    new_data_[temp] = value;
    for (size_t i=temp+1; i!=new_size; i++)
    {
        new_data_[i] = data_[i-1];
    }
    uncreate();
    //from grow() function
    data_ = new_data_;
    avail = new_avail;
    limit = data_ + new_size;

}
template <class T>
void Vec<T>::insert(const_iterator it, int n, const_reference value)
{
    int temp = 0;
    for (auto i = this->begin(); i != it; i++)
    {
        temp++;
    }
    //from grow() function
    size_type new_size = this->size()+n;
    iterator new_data_ = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data_, avail+n, new_data_);
    for (size_t i=0; i<temp; i++)
    {
        new_data_[i] = data_[i];
    }
    for (size_t i=temp; i!=n+temp; i++)
    {
        new_data_[i] = value;
    }
    for (size_t i=n+temp; i!=new_size; i++)
    {
        new_data_[i] = data_[i-n];
    }
    uncreate();
    //from grow() function
    data_ = new_data_;
    avail = new_avail;
    limit = data_ + new_size;
}
//shrink_to_fit()
template <class T>
void Vec<T>::shrink_to_fit() const
{
    limit = avail;
}
//empty()
template <class T>
bool Vec<T>::empty()
{
    if(begin() == end())
        return true;
    else
        return false;
}
//reserve()
template <class T>
void Vec<T>::reserve(const int x)
{
    if (x > capacity())
    {
        size_type sz = x;
        limit = data_ + sz;
    }
}
//swap()
template <class T>
void Vec<T>::swap(Vec<T>& l) noexcept
{
    iterator temp_data_ = this->data_;
    iterator temp_avail = this->avail;
    iterator temp_limit = this->limit;
    this->data_ = l.data_;
    this->avail = l.avail;
    this->limit = l.limit;
    l.data_ = temp_data_;
    l.avail = temp_avail;
    l.limit = temp_limit;
}
//clear()
template <class T>
void Vec<T>::clear()
{
    this->uncreate();
}
// priskyrimo operatorius
template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    if (&rhs != this)
    {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}
//operatorius ==
template <class T>
bool Vec<T>::operator==(const Vec<T>& l) const
{
    if (this->size()!=l.size())
    {
        throw std::runtime_error("Vektoriu dydzio neatitikimas!");
        return false;
    }
    else
    {
        for (size_t i=0; i!=l.size(); i++)
        {
            if (this->data_[i]!=l.data_[i])
                return false;
        }
    }
    return true;
}
//operatorius !=
template <class T>
bool Vec<T>::operator!=(const Vec<T>& l) const
{
    if (this->size()!=l.size())
    {
        return true;
    }
    else
    {
        for (size_t i=0; i!=l.size(); i++)
        {
            if (this->data_[i]!=l.data_[i])
                return true;
        }
    }
    return false;
}
//operatorius >
template <class T>
bool Vec<T>::operator>(const Vec<T>& l) const
{
    if (this->size()!=l.size())
    {
        throw std::runtime_error("Vektoriu dydzio neatitikimas!");
        return false;
    }
    else
    {
        for (size_t i=0; i<l.size(); i++)
        {
            if (this->data_[i]<=l.data_[i])
            {
                return false;
            }
        }
    }
    return true;
}
//operatorius <
template <class T>
bool Vec<T>::operator<(const Vec<T>& l) const
{
    if (this->size()!=l.size())
    {
        throw std::runtime_error("Vektoriu dydzio neatitikimas!");
        return false;
    }
    else
    {
        for (size_t i=0; i<l.size(); i++)
        {
            if (this->data_[i]>=l.data_[i])
            {
                return false;
            }
        }
    }
    return true;
}
//operatorius >=
template <class T>
bool Vec<T>::operator>=(const Vec<T>& l) const
{
    if (this->size()!=l.size())
    {
        throw std::runtime_error("Vektoriu dydzio neatitikimas!");
        return false;
    }
    else
    {
        for (size_t i=0; i<l.size(); i++)
        {
            if (this->data_[i]<l.data_[i])
            {
                return false;
            }
        }
    }
    return true;
}
//operatorius <=
template <class T>
bool Vec<T>::operator<=(const Vec<T>& l) const
{
    if (this->size()!=l.size())
    {
        throw std::runtime_error("Vektoriu dydzio neatitikimas!");
        return false;
    }
    else
    {
        for (size_t i=0; i<l.size(); i++)
        {
            if (this->data_[i]>l.data_[i])
            {
                return false;
            }
        }
    }
    return true;
}

#endif // VECTOR_H_INCLUDED
