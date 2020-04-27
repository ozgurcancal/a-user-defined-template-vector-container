// vector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector.h"
#include <vector>
#include <time.h>
#include <conio.h>

Vector::Vector() noexcept :arr{ new int[0] }, mysize{ 0 }, mycap{ 0 }{}

Vector::~Vector()noexcept {

    delete[] arr;   
    arr = nullptr;     
}

Vector::Vector(size_t size, int val) {  

    mysize, mycap = size;
    arr = new int[mycap] {val};
}

void Vector::copy_Vector(const Vector& Obj) {

    if (Obj.mycap > mycap) {
        reserve(Obj.mycap);  //kopyalanacak arraya gore yer(kapasite) acar
        mysize = Obj.mysize;
        std::copy(Obj.arr, Obj.arr + Obj.mysize, arr);
    }

    else if (mycap == Obj.mycap) {   // shrink_to_fit 

        arr = new int[Obj.mysize];
        mycap = Obj.mysize;

        std::copy(Obj.arr, Obj.arr + Obj.mysize, arr);
    }

}

Vector::Vector(const Vector& Obj) {

    copy_Vector(Obj);
}

Vector::Vector(Vector&& Obj)noexcept { 

    copy_Vector(Obj);
    delete[] Obj.arr;
    Obj.arr = nullptr;
}

Vector& Vector::operator=(const Vector& Obj) {

    copy_Vector(Obj);
    return *this;
}

Vector& Vector::operator=(Vector&& Obj)noexcept {

    copy_Vector(Obj);
    delete[] Obj.arr;
    Obj.arr = nullptr;
    return *this;
}

Vector::Vector(std::initializer_list<int> ilist) {  

    mysize = ilist.size();
    mycap = mysize * 2;
    arr = new int[mycap];
    std::initializer_list<int>::iterator it;  
    int i = 0;
    for (it = ilist.begin(); it != ilist.end(); ++it) {
        arr[i] = *it;
        i++;
    }

}

template <typename T>
void Vector::initialize_in_range(T x, T y) {

    if (!mysize) {
        mysize = 5;
        mycap = 10;
        arr = new int[mycap];
    }

    auto vbegin = const_cast<int*>(x);
    auto vend = const_cast<int*>(y);
    int range = *vbegin - *vend;

    for (unsigned i = 0; i < mysize; i++) {
        arr[i] = (rand() % range) + *vbegin;
    }
}

Vector::Vector(const int* pbegin, const int* pend) {

    initialize_in_range<const int*>(pbegin, pend);
}

Vector::Vector(const_iterator beg, const_iterator end) {

    initialize_in_range<const int*>(beg.p, end.p);
}

void Vector::reserve(size_t new_cap) {

    if (new_cap > mycap) {
        int* p = new int[new_cap];
        for (unsigned i = 0; i < mysize; i++)
            p[i] = arr[i];

        delete[] arr;
        arr = p;
        mycap = new_cap;

    }
}

void Vector::shrink_to_fit() {

    Vector Obj{ *this };
    copy_Vector(Obj);
}

Vector::iterator Vector::begin() {

    Vector::iterator it;
    it.p = arr;
    if (!mysize)
        throw ("array bos"); 
    return it;
}

Vector::iterator Vector::end() { 

    Vector::iterator it;
    it.p = arr + mysize;
    if (!mysize)
        throw ("array bos"); 
    return it;
}

Vector::const_iterator Vector::begin()const {

    Vector::const_iterator it;
    it.p = arr;

    return it;
}

Vector::const_iterator Vector::end()const {

    Vector::const_iterator it;
    it.p = arr + mysize;

    return it;
}

void Vector::copy_ilist(std::initializer_list<int> ilist) {

    if (mycap < ilist.size()) {
        if (!mysize)
            delete[] arr;
        arr = new int[ilist.size() * 2];
        mysize = ilist.size();
        mycap = 2 * mysize;
    }
    std::copy(ilist.begin(), ilist.end(), arr);
}

Vector& Vector::operator=(std::initializer_list<int> ilist) {

    copy_ilist(ilist);

    return *this;
}

void Vector::resize(size_t new_size, int val) { 

    if (new_size > mycap)
        reserve(2 * new_size);

    else
    {
        if (mysize > new_size)
            mysize -= mysize - new_size;

        else if (mysize < new_size) {
            auto size_difference = new_size - mysize;
            unsigned i = 0;
            while (i < size_difference) {
                arr[mysize + i] = val;
                i++;
            }
            mysize = new_size;
        }
    }

}

void Vector::assign(size_t n, int m) {

    mycap = n * 2;
    mysize = n;
    arr = new int[n * 2];

    unsigned i = 0;
    while (i < n) {

        arr[i] = m;
        i++;
    }
}

void Vector::assign(std::initializer_list<int> ilist) {

    copy_ilist(ilist);
}

void Vector::assign(const int* pbeg, const int* pend) {

    initialize_in_range(pbeg, pend);
}

Vector::iterator Vector::insert(iterator where, int val) {	

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

Vector::iterator Vector::insert(iterator where, iterator source_beg, iterator source_end) {
    int* it = source_beg.p;

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

Vector::iterator Vector::erase(iterator where) {

    unsigned pos = where.p - arr;
    unsigned i = pos;
    while (i < mysize) {
        arr[i] = arr[i + 1];
        i++;
    }
    mysize--;
    return where;
}

Vector::iterator Vector::erase(iterator where, iterator source_beg, iterator source_end) {

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

void Vector::push_back(int val) {

    arr[mysize] = val;
    mysize++;
}

void Vector::pop_back() {

    mysize--;
}

void Vector::swap(Vector& Obj) { 
    
    int* temp=nullptr; int i = 0;    
    auto size=mysize > Obj.mysize ? mysize : Obj.mysize;   //choose bigger size

    while (i<size)  //swap the elements
    {
        std::swap(arr, Obj.arr);
        i++;
    }

    std::swap(mysize, Obj.mysize);   //swap the sizes  
}

void Vector::clear() {

    delete[] arr;
    arr = new int[0];
    mycap, mysize = 0;

}

int& Vector::front() {

    if (int* p = arr; mysize)
        return *p;
    else
        throw("vector bos ");
}

const int& Vector::front()const {

    if (int* p = arr; mysize)
        return *p;
    else
        throw("vector bos ");
}

int& Vector::back() {

    if (int* p = arr + mysize - 1; mysize)
        return *p;
    else
        throw("vector bos ");
}

const int& Vector::back()const {

    if (int* p = arr + mysize - 1; mysize)
        return *p;
    else
        throw("vector bos ");
}

int& Vector::operator[](size_t idx) {

    if (idx < mysize)
        return arr[idx];
    else
        throw("indeks gecerli degil ");
}

const int& Vector::operator[](size_t idx)const {

    if (idx < mysize)
        return arr[idx];
    else
        throw("indeks gecerli degil ");
}

int* Vector::data() {

    return arr;
}

const int* Vector::data()const {

    return arr;
}

size_t Vector::capacity()const {

    return mycap;
}

size_t Vector::size()const {

    return mysize;
}

bool Vector::empty()const {

    if (mysize)
        return 1;
    else
        return 0;
}

Vector::iterator& Vector::iterator::operator++() {  

    p++;

    return *this;
}

Vector::iterator Vector::iterator::operator++(int) {

    iterator it{ *this };
    p++;

    return it;
}

Vector::iterator& Vector::iterator::operator--() {

    p--;

    return *this;
}

Vector::iterator Vector::iterator::operator--(int) {

    iterator it{ *this };
    p--;

    return it;
}

int& Vector::iterator::operator*() {

    return *p;
}

int& Vector::iterator::operator[](int n) {

    return *(p + n);
}

std::ptrdiff_t Vector::iterator::diffiter(const iterator& it) {

    return p - it.p;
}

Vector::iterator Vector::iterator::operator+(size_t n) { 

    iterator it;
    it.p += n;
    return it;
}

Vector::iterator Vector::iterator::operator-(size_t n) {

    iterator it;
    it.p -= n;
    return it;
}

Vector::iterator& Vector::iterator::operator+=(size_t n) {

    p += n;

    return *this;
}

Vector::iterator& Vector::iterator::operator-=(size_t n) {

    p -= n;
    return *this;
}

bool Vector::iterator::operator<(const iterator& it)const {

    if (*p < *it.p)
        return 1;
    else
        return 0;
}

bool Vector::iterator::operator<=(const iterator& it)const {

    return !(it < *this);
}
//
bool Vector::iterator::operator>(const iterator& it)const {

    return (it < *this);
}
//
bool Vector::iterator::operator>=(const iterator& it)const {

    return !(*this < it);
}

bool Vector::iterator::operator==(const iterator& it)const {

    return (*p == *it.p);
}

bool Vector::iterator::operator!=(const iterator& it)const {

    return !(*this == it);
}

Vector::iterator& Vector::const_iterator::operator++() {

    iterator it;
    it.p = const_cast<int*>(p);
    p++;

    return it;

}

Vector::iterator Vector::const_iterator::operator++(int) {

    iterator it;

    it.p = const_cast<int*>(p);

    p++;

    return it;

}//80

Vector::iterator& Vector::const_iterator::operator--() {

    iterator it;

    it.p = const_cast<int*>(p);

    p--;

    return it;

}

Vector::iterator Vector::const_iterator::operator--(int) {

    iterator it;

    it.p = const_cast<int*>(p);

    p--;

    return it;

}//80

const int& Vector::const_iterator::operator*() {


    return *p;

}//80

const int& Vector::const_iterator::operator[](int n) {


    return *(p + n);

}//80

std::ptrdiff_t Vector::const_iterator::operator-(iterator it) {


    return (p - it.p);

}//80

Vector::const_iterator Vector::const_iterator::operator+(int n)const {

    const_iterator it;
    it.p = p + n;
    return (it);

}//80

Vector::const_iterator Vector::const_iterator::operator-(int n)const {

    const_iterator it;
    it.p = p - n;
    return (it);

}//80

Vector::const_iterator& Vector::const_iterator::operator+=(int n) {


    p += n;
    return (*this);

}//80

Vector::const_iterator& Vector::const_iterator::operator-=(int n) {


    p -= n;
    return (*this);

}//80

bool Vector::const_iterator::operator<(const const_iterator& it)const {



    return (*p < *it.p);

}//80

bool Vector::const_iterator::operator<=(const const_iterator& it)const {



    return !(*it.p < *p);

}//80

bool Vector::const_iterator::operator>(const const_iterator& it)const {



    return (*it.p < *p);

}//80

bool Vector::const_iterator::operator>=(const const_iterator& it)const {



    return !(*p < *it.p);

}//80

bool Vector::const_iterator::operator==(const const_iterator& it)const {



    return (*p == *it.p);

}//80

bool Vector::const_iterator::operator!=(const const_iterator& it)const {



    return !(*p == *it.p);

}//80


int main()try
{

    //for (unsigned i = 0; i < v.mysize; i++)
//    std::cout << v.arr[i]<<" ";

/*---------------------Test Codes------------------- */


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


    //Vector::iterator it;
    //Vector::iterator it2;
    //const Vector v{ 1,2,3,4,5 };
    //it.p = v.arr + 2;
    //it2.p = v.arr + 3;
    //std::cout << (it2 < it);

    //Vector::iterator it;
    //const Vector v{ 1,2,3,4,5 };
    //it.p = v.arr + 2;
    //it -= 1;
    //std::cout << *(it).p;


    //Vector::iterator it;
    //Vector::iterator it2;
    //const Vector v{ 1,2,3,4,5 };
    //it.p = v.arr;
    //it2.p = v.arr + 1;
    //std::cout << it.diffiter(it2);


    //Vector::iterator it;
    //const Vector v{ 1,2,3,4,5 };
    //it.p = v.arr;
    //std::cout << *it;


    //Vector::iterator it;
    //const Vector v{ 1,2,3,4,5 };
    //it.p = v.arr;
    //std::cout << it[3];

//Vector::iterator it;
//const Vector v{ 1,2,3,4,5 };
//it.p = v.arr + 3;
//
//++it;
//
//if (it.p > v.arr + 4)
//throw("size ı astin");


    //const Vector v{ 1,2,3,4,5 };
//std::cout << v[0];

//const Vector v{ 1,2,3,4,5 };
//std::cout << v[0];
//std::cout << v[0];


    //Vector v{ 1,2,3,4,5 };
    //std::cout << v.front();


    //Vector v{ 1,2,3,4,5 };
    //Vector v1{ 10,11,12,13,14,15,16 };
    //v.swap(v1);

    //Vector v{ 1,2,3,4,5 };
    //v.pop_back();


    //Vector v{ 1,2,3,4,5 };
    //v.push_back(6);


    //Vector v{ 1,2,3,4,5 };
    //Vector::iterator where;
    //Vector::iterator it1;
    //Vector::iterator it2;
    //where.p = v.arr;
    //it1.p = v.arr + 2;
    //it2.p = v.arr + 4;
    //v.erase(where, it1, it2);


    //Vector::iterator it1;
    //Vector v{ 1,2,3,4,5 };
    //it1.p = v.arr;
    //v.erase(it1);


    //Vector v{ 1,2,3,4,5 };
    //Vector::iterator where;
    //Vector::iterator it1;
    //Vector::iterator it2;
    //where.p = v.arr;
    //it1.p = v.arr + 2;
    //it2.p = v.arr + 4;
    //v.insert(where, it1, it2);

 //Vector v{ 1,2,3,4,5 }; 
//Vector::iterator it;
//it.p1 = v.arr+2;
//it.p2 = v.arr+2;
//v.insert(it, 9);

    //Vector v{ 1,2,3,4,5 };  sonuc var takılıyor ama.??
//Vector::iterator it;
//it.p = v.arr+2;
//v.insert(it, 9);

    //int x = 1, y = 10;
    //Vector v;
    //v.assign(&x, &y);


    //Vector v;
    //v.assign({ 1,2,3,4,5 });


    //Vector v;
    //v.assign(5, 1);


    //Vector v;
    //v = { 1,2,3 };
    //v.resize(5, 2);


    //Vector v;
    //v = { 1,2,3 };

    //Vector v{ 3,4,5 };
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

 /*   Vector v1{ 3,4,5 };
    Vector v{ std::move(v1) };*/

    //int x = 1, y = 10;  
//Vector::const_iterator beg,end ;
//beg.p = &x;
//end.p = &y;
//Vector v(beg, end);


    //int x = 1, y = 10;
    //Vector v(&x, &y);



 //   Vector v{ 1,2,3 };


    //std::vector<int> vec{ 10,20,30 };
    //Vector::iterator it;
    //it.p = &vec[0];
    //
    //std::cout << *(it++.p);
    //std::cout << *(it.p);


}
catch (const char* error) {
    std::cout << " hata yakalandi: " << error;
    exit(EXIT_FAILURE);
}


