// vector.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include "Vector.h"
#include <vector>
#include <time.h>
#include <conio.h>

template<typename T>
Vector<T>::Vector() noexcept :arr{ new T[0] }, mysize{ 0 }, mycap{ 0 }{}

template<typename T>
Vector<T>::~Vector()noexcept {

    delete[] arr;  
    arr = nullptr;    

}

template<typename T>
Vector<T>::Vector(size_t size, T val) {  

    mysize, mycap = size;
    arr = new T[mycap]{ val };
}

template <typename T>
void Vector<T>::copy_container(const T& Obj) {

    if (Obj.mycap > mycap) {
        reserve(Obj.mycap);  //kopyalanacak arraya gore yer(kapasite) acar
        mysize = Obj.mysize;
        std::copy(Obj.arr, Obj.arr + Obj.mysize, arr);
    }

    else if (mycap == Obj.mycap) {   // shrink_to_fit 

        arr = new T[Obj.mysize];
        mycap = Obj.mysize;

        std::copy(Obj.arr, Obj.arr + Obj.mysize, arr);
    }

}

template <typename T>
Vector<T>::Vector(const Vector& Obj) {

    copy_container(Obj);
}

template <typename T>
Vector<T>::Vector(Vector&& Obj)noexcept {  //yer ayırma işlemi yapıyor yine de noexcept yazdım ???

    copy_container(Obj);
    delete[] Obj.arr;
    Obj.arr = nullptr;


}
//delegating constructor?
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& Obj) { 

    copy_container(Obj);
    std::cout << "copy assignment cagrildi\n";
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& Obj)noexcept {  

    copy_container(Obj);
    delete[] Obj.arr;
    Obj.arr = nullptr;
    std::cout << "move assignment cagrildi\n";
    return *this;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> ilist) {  

    mysize = ilist.size();
    mycap = mysize * 2;
    arr = new T[mycap];
    typename std::initializer_list<T>::iterator it;   
    int i = 0;
    for (it = ilist.begin(); it != ilist.end(); ++it) {
        arr[i] = *it;
        i++;
    }
}

template <typename T>
template <typename U>
void Vector<T>::initialize_in_range(const U x, const U y) {

    if (!mysize) {
        mysize = 5;
        mycap = 10;
        arr = new T[mycap];
    }

    auto vbegin = const_cast<U>(x);  //int*
    auto vend = const_cast<U>(y);
    int range = *vbegin - *vend;

    for (unsigned i = 0; i < mysize; i++) {
        arr[i] = (rand() % range) + *vbegin;
    }
}

template <typename T>
Vector<T>::Vector(const T* pbegin, const T* pend) {   

    initialize_in_range<const T*>(pbegin, pend);
}

template <typename T>
Vector<T>::Vector(const_iterator beg, const_iterator end) {

    initialize_in_range<const_iterator>(beg.p, end.p);
}

template <typename T>
void Vector<T>::reserve(size_t new_cap) {

    if (new_cap > mycap) {
        T* p = new T[new_cap];
        for (unsigned i = 0; i < mysize; i++)
            p[i] = arr[i];

        delete[] arr;
        arr = p;
        mycap = new_cap;

    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {

    Vector Obj{ *this };
    copy_container(Obj);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {  

    iterator it;
    it.p = arr;
    *(it.p) =
        if (!mysize)
            throw ("array bos"); 
    return it;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {   //dereferance etmek tanımsız davranış 

    iterator it;
    it.p = arr + mysize;
    if (!mysize)
        throw ("array bos"); 
    return it;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin()const {

    Vector<T>::const_iterator it;
    it.p = arr;

    return it;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end()const {

    Vector<T>::const_iterator it;
    it.p = arr + mysize;

    return it;
}

template <typename T>
void Vector<T>::copy_ilist(std::initializer_list<T> ilist) {

    if (mycap < ilist.size()) {
        if (!mysize)
            delete[] arr;
        arr = new T[ilist.size() * 2];
        mysize = ilist.size();
        mycap = 2 * mysize;
    }
    std::copy(ilist.begin(), ilist.end(), arr);
}

template <typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> ilist) {

    copy_ilist(ilist);

    return *this;
}

template <typename T>
void Vector<T>::resize(size_t new_size, T val) { 

    if (new_size > mycap)
        reserve(2 * new_size);

    else
    {
        if (new_size < mysize)  //cut the size
            mysize -= mysize - new_size;

        else if (new_size > mysize) {
            auto size_difference = new_size - mysize;
            unsigned i = 0;
            while (i < size_difference) {  //fill extra size with val
                arr[mysize + i] = val;
                i++;
            }
            mysize = new_size;
        }
    }

}

template <typename T>
void Vector<T>::assign(size_t n, T val) {

    mycap = n * 2;
    mysize = n;
    arr = new T[n * 2];

    unsigned i = 0;
    while (i < n) {

        arr[i] = val;
        i++;
    }
}

template <typename T>
void Vector<T>::assign(std::initializer_list<T> ilist) {

    copy_ilist(ilist);
}

template <typename T>
void Vector<T>::assign(const T* pbeg, const T* pend) {

    initialize_in_range(pbeg, pend);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator where, T val) {	

    unsigned size = mysize;
    unsigned pos = where.p - arr;
    while (pos < size) {     //kaydır
        arr[size] = arr[size - 1];
        size--;
    }
    arr[pos] = val;   //ekle
    mysize++;
    return where;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator where, iterator source_beg, iterator source_end) {  
    T* it = source_beg.p;

    unsigned size = mysize;
    unsigned pos = where.p - arr;
    unsigned x = source_end.p - source_beg.p;

    mysize += x;
    while (pos < size) {  //pozisyondan itibaren arrayi eklenen eleman sayısı kadar sağa çek
        arr[size + x - 1] = arr[size - 1];
        size--;
    }
    unsigned i = pos;
    while (it < source_end.p) {  //elemanları ekle
        arr[i] = *it;
        i++; it++;
    }
    return source_beg;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator where) {

    unsigned pos = where.p - arr;
    unsigned i = pos;
    while (i < mysize) {
        arr[i] = arr[i + 1];
        i++;
    }
    mysize--;
    return where;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator where, iterator source_beg, iterator source_end) {

    unsigned pos = where.p - arr;
    unsigned x = source_end.p - source_beg.p;

    unsigned i = pos;
    while (i < mysize) {
        arr[pos + i] = arr[pos + i + x];
        i++;
    }
    mysize -= x;

    return where;
}

template <typename T>
void Vector<T>::push_back(T val) {
    if (mysize == mycap)
        reserve(10);

    arr[mysize] = val;
    mysize++;
}
template <typename T>
void Vector<T>::pop_back() {

    mysize--;
}

template<typename T>
void Vector<T>::swap_containers(T& Obj) {
    int i = 0;

    auto size = mysize > Obj.mysize ? mysize : Obj.mysize;   //choose bigger size

    while (i < size)  //swap the elements
    {
        std::swap(arr, Obj.arr);
        i++;
    }

    std::swap(mysize, Obj.mysize);   //swap the sizes

}

template <typename T>
void Vector<T>::clear() {

    delete[] arr;
    arr = new T[0];
    mycap, mysize = 0;

}

template <typename T>
T& Vector<T>::front() {

    if (T* p = arr; mysize)
        return *p;
    else
        throw("vector bos ");
}

template <typename T>
const T& Vector<T>::front()const {

    if (T* p = arr; mysize)
        return *p;
    else
        throw("container bos ");
}

template <typename T>
T& Vector<T>::back() {

    if (T* p = arr + mysize - 1; mysize)
        return *p;
    else
        throw("container bos ");
}

template <typename T>
const T& Vector<T>::back()const {

    if (T* p = arr + mysize - 1; mysize)
        return *p;
    else
        throw("container bos ");
}

template <typename T>
T& Vector<T>::operator[](size_t idx) {

    if (idx < mysize)
        return arr[idx];
    else
        throw std::out_of_range("indeks gecerli degil ");
}

template <typename T>
const T& Vector<T>::operator[](size_t idx)const {

    if (idx < mysize)
        return arr[idx];
    else
        throw std::out_of_range("indeks gecerli degil ");
}

template <typename T>
T* Vector<T>::data() {

    return arr;
}

template <typename T>
const T* Vector<T>::data()const {

    return arr;
}

template <typename T>
size_t Vector<T>::capacity()const {

    return mycap;
}

template <typename T>
size_t Vector<T>::size()const {

    return mysize;
}

template <typename T>
bool Vector<T>::empty()const {

    if (mysize)
        return 1;
    else
        return 0;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator++() {  //iterator size ı aşarsa ve dereferans edilirse tanımsız davranış

    p++;

    return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator++(int) {

    iterator it{ *this };  //
    p++;

    return it;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator--() {

    p--;

    return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator--(int) {

    iterator it{ *this };
    p--;

    return it;
}

template <typename T>
T& Vector<T>::iterator::operator*() {

    return *p;
}

template <typename T>
T& Vector<T>::iterator::operator[](int n) {

    return *(p + n);
}

template <typename T>
std::ptrdiff_t Vector<T>::iterator::diffiter(const iterator& it) {

    return p - it.p;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator+(size_t n) {  

    iterator it;
    it.p += n;
    return it;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator-(size_t n) {

    iterator it;
    it.p -= n;
    return it;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator+=(size_t n) {

    p += n;

    return *this;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator-=(size_t n) {

    p -= n;
    return *this;
}

template <typename T>
bool Vector<T>::iterator::operator<(const iterator& it)const {

    if (*p < *it.p)
        return 1;
    else
        return 0;
}

template <typename T>
bool Vector<T>::iterator::operator<=(const iterator& it)const {

    return !(it < *this);
}
//
template <typename T>
bool Vector<T>::iterator::operator>(const iterator& it)const {

    return (it < *this);
}
//
template <typename T>
bool Vector<T>::iterator::operator>=(const iterator& it)const {

    return !(*this < it);
}

template <typename T>
bool Vector<T>::iterator::operator==(const iterator& it)const {

    return (*p == *it.p);
}

template <typename T>
bool Vector<T>::iterator::operator!=(const iterator& it)const {

    return !(*this == it);
}

template <typename T>
typename Vector<T>::const_iterator& Vector<T>::const_iterator::operator++() {

    p++;

    return *this;

}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::const_iterator::operator++(int) {

    const_iterator it{ *this };

    p++;

    return it;

}

template <typename T>
typename Vector<T>::const_iterator& Vector<T>::const_iterator::operator--() {

    p--;

    return *this;

}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::const_iterator::operator--(int) {

    const_iterator it{ *this };

    p--;

    return it;

}

template <typename T>
const T& Vector<T>::const_iterator::operator*() {


    return *p;

}

template <typename T>
const T& Vector<T>::const_iterator::operator[](int n) {


    return *(p + n);

}

template <typename T>
std::ptrdiff_t Vector<T>::const_iterator::operator-(iterator it) {


    return (p - it.p);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::const_iterator::operator+(int n)const {

    const_iterator it;
    it.p = p + n;
    return (it);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::const_iterator::operator-(int n)const {

    const_iterator it;
    it.p = p - n;
    return (it);
}

template <typename T>
typename Vector<T>::const_iterator& Vector<T>::const_iterator::operator+=(int n) {

    p += n;
    return (*this);
}

template <typename T>
typename Vector<T>::const_iterator& Vector<T>::const_iterator::operator-=(int n) {

    p -= n;
    return (*this);
}

template <typename T>
bool Vector<T>::const_iterator::operator<(const const_iterator& it)const {

    return (*p < *it.p);
}

template <typename T>
bool Vector<T>::const_iterator::operator<=(const const_iterator& it)const {

    return !(*it.p < *p);
}

template <typename T>
bool Vector<T>::const_iterator::operator>(const const_iterator& it)const {

    return (*it.p < *p);
}

template <typename T>
bool Vector<T>::const_iterator::operator>=(const const_iterator& it)const {

    return !(*p < *it.p);
}

template <typename T>
bool Vector<T>::const_iterator::operator==(const const_iterator& it)const {

    return (*p == *it.p);
}

template <typename T>
bool Vector<T>::const_iterator::operator!=(const const_iterator& it)const {

    return !(*p == *it.p);
}


int main()try
{

/*-------------------------test codes---------------------*/
    //Vector<char> v{ '1','2','3','4','5' };  
    //Vector<char>::iterator it;
    //it.p = v.arr + 2;
    //v.insert(it, '9');

    //   for (unsigned i = 0; i < v.mysize; i++)
    //       std::cout << v.arr[i]<<" ";



    //Vector<double> vec;
    //vec.push_back(1);
    //vec.push_back(2);
    //vec.pop_back(2);
    //Vector<double>::iterator it;
    //bool first = true;
    //for (it = vec.begin(); it != vec.end(); ++it)
    //{
    //    if (first) //modify container once while iterating
    //    {
    //        vec.push_back(4);
    //        first = false;
    //    }
    //    (*it)++;
    //    std::cout << *it << '\n'; 
    //                      
    //}


    //Vector<double>::iterator it;
    //Vector<double> v{ 1,2,3,4,5 };
    //it = v.begin();
    //std::cout << *it++;  //1
    //std::cout << *(it++);  //2
    //std::cout << *(it);  //3
    //std::cout << *(++it); //4



           //Vector::const_iterator it;
           //Vector::const_iterator it2;
           //const Vector v{ 1,1,3,4,5 };
           //it.p = v.arr;
           //it2.p = v.arr + 1;
           //std::cout << (it >= it2) << '\n';
           //std::cout << (it > it2) << '\n';
           //std::cout << (it < it2) << '\n';


           //Vector::iterator it;
           //Vector::iterator it2;
           //const Vector v{ 1,2,3,3,5 };
           //it.p = v.arr + 2;
           //it2.p = v.arr + 3;
           //std::cout << (it2 <= it);
           //std::cout << (it2 < it);
            //std::cout << it.diffiter(it2);
             //std::cout << v.front();
    
           //Vector::iterator it;
           //const Vector v{ 1,2,3,4,5 };
           //it.p = v.arr + 2;
           //it -= 1;
           //std::cout << *(it).p;


       //Vector::iterator it;
       //const Vector v{ 1,2,3,4,5 };
       //it.p = v.arr + 3;
       //
       //++it;
       //
       //if (it.p > v.arr + 4)
       //throw("size ı astin");


           //Vector v{ 1,2,3,4,5 };
           //Vector v1{ 10,11,12,13,14,15,16 };
           //v.swap(v1);



           //Vector v{ 1,2,3,4,5 };
           //Vector::iterator where;
           //Vector::iterator it1;
           //Vector::iterator it2;
           //where.p = v.arr;
           //it1.p = v.arr + 2;
           //it2.p = v.arr + 4;
           //v.erase(where, it1, it2);
           // v.insert(where, it1, it2);
           //v.erase(it1);


       //    Vector<int> v{ 1,2,3,4,5 };  
       //Vector<int>::iterator it;
       //it.p = v.arr+2;
       //v.insert(it, 9);


           //Vector v;
           //v.assign({ 1,2,3,4,5 });      
           //v.assign(5, 1);
           //std::cout << v.mycap << " ";
           //v.shrink_to_fit();
           //std::cout << v.mycap << "\n";


           //Vector v1{ 3,4,5 };
           //Vector v;
           //v = std::move(v1);

           //Vector v1{ 3,4,5 };
           //Vector v;
           //v = v1;

           //Vector v1{ 3,4,5 };
           //Vector v{ (v1) };


}
catch (const char* error) {
    std::cout << " hata yakalandi: " << error;
    exit(EXIT_FAILURE);
}
catch (std::out_of_range& ex) {

    std::cout << ex.what();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

