#pragma once

#include <iostream>


class Vector {
private:
	void copy_ilist(std::initializer_list<int> ilist);   //std::initializer listi kopyalar
	template <class T>
	void inline template_swap(T& x, T& y);
public:

	int* arr = nullptr;
	size_t mysize = 0;
	size_t mycap = 0;


	class iterator;//1. İçsel(nested) iterator türü.Kaptaki öğelerin konumlarını tutan iterator nesnelerinin türü.Okuma ve yazma erişimi sağlar.

	class const_iterator;//2. İçsel(nested) const_iterator türü.Kaptaki öğelerin konumlarını tutan const_iterator nesnelerinin türü.Yalnızca okuma amaçlı erişim sağlar.

	Vector()noexcept;//3. Varsayılan kurucu işlev(default constructor).Boş bir Vector nesnesi oluşturur.
//
	~Vector()noexcept;//4. Sonlandırıcı işlev(destructor).
//
	void copy_Vector(const Vector& Obj);

	Vector(const Vector& Obj);///5. Kopyalayan kurucu işlev. (copy constructor)
//
	Vector(Vector&& Obj)noexcept;//6. Taşıyan kurucu işlev. (move constructor)
//
	Vector& operator=(const Vector& Obj);//7. Kopyalayan atama işlevi. (copy assignment)
//
	Vector& operator=(Vector&& Obj)noexcept;//8. Taşıyan atama işlevi. (move assignment)
//
	Vector(size_t size, int val = 0);//9. Kurucu işlev.Vector'ü değeri val olan size tane öğe ile başlatır (fill constructor).
//
	Vector(std::initializer_list<int> ilist);//10. std::initializer_list parametreli kurucu işlev.Vector nesnesini listedeki değerleri tutacak şekilde başlatır.
//
	template <typename T>  // Vektor nesnesine  belirtilen aralıkta ilk deger vererir .
	void initialize_in_range(T x, T y);

	Vector(const int* pbegin, const int* pend);//11. Aralık(range) parametreli kurucu işlev.Vector nesnesini[pbegin, pend) aralığındaki değerlerle başlatır.Aralık olarak doğrudan adresler(pointer) kullanılmaktadır.
//
	Vector(const_iterator beg, const_iterator end);//12. Aralık(range) parametreli kurucu işlev.Vector nesnesini[beg, end) aralığındaki değerlerle başlatır.Aralık olarak const_iterator değerleri kullanılmaktadır.
//
	void reserve(size_t new_cap);//13. reserve işlevi.Eğer new_cap değeri var olan kapasiteden büyükse kapasiteyi arttırır.Eğer new_cap değeri var olan kapasiteden küçükse kapasiteyi küçültür.
//
	void shrink_to_fit();	//14. Kapasite değerini Vector'de tutulan öğe sayısına (size) büzer (kapasiteyi küçültür).

	iterator begin();	//15. Vector'de tutulan ilk öğenin konumunu döndürür. İşlevin geri dönüş değeri içsel bir tür olan iterator türüdür. Boş bir Vector'de bu konumun içerik(dereferencing) operatörünün terimi yapılması tanımsız davranıştır.

	iterator end();	//16. Vector'de tutulan son öğeden sonraki (olmayan öğenin) konumunu döndürür. İşlevin geri dönüş değeri içsel bir tür olan iterator türüdür. Bu işlevden alınan konum karşılaştırma operatörleri ile diğer konumlarla karşılaştırılabilir. Bu konumun içerik (dereferencing) operatörünün terimi yapılması tanımsız davranıştır.*/

	const_iterator begin()const;	//17. Vector'de tutulan ilk öğenin konumunu (salt okuma erişimli) döndürür. İşlevin geri dönüş değeri içsel bir tür olan const_iterator türüdür. Boş bir Vector'de bu konumun içerik(dereferencing) operatörünün terimi yapılması tanımsız davranıştır.

	const_iterator end()const;	//18. Vector'de tutulan son öğenin konumunu (salt okuma erişimli) döndürür. İşlevin geri dönüş değeri içsel bir tür olan const_iterator türüdür. Boş bir Vector'de bu konumun içerik(dereferencing) operatörünün terimi yapılması tanımsız davranıştır.

	Vector& operator=(std::initializer_list<int> ilist);//22. initializer_list parametreli atama işlevi.Bu işlevin çağrılması ile Vector artık parametre olan listedeki değerleri tutar.

	void resize(size_t new_size, int val = 0);//	23. resize işlevi.Vector'de tutulan öğe sayısını değiştirir. Bu işlev Vector'deki öğe sayısını hem arttırmak hem de azaltmak için kullanılabilir.İşlevin varsayılan argüman alan ikinci parametresi Vector'deki öğe sayısının arttırılması durumunda yeni eklenecek öğelerin alacakları değerdir. Vector'deki öğe sayısından daha küçük bir değerle çağrılırsa sondan silme işlemi yapar.

	void assign(size_t n, int m);//	26. assign işlevi.Bu işlevin çağrılmasıyla Vector nesnesi n tane val değeri tutar hale gelir. (fill assign)

	void assign(std::initializer_list<int> ilist);//	27. initializer_list parametreli assign işlevi.artık Vector parametresine gelen listedeki değerleri tutar.

	void assign(const int* pbeg, const int* pend);	//28. aralık(range)_ parametreli assign işlevi. artık Vector parametresine gelen aralıktaki değerleri tutar.

	iterator insert(iterator where, int val);	//30. where konumuna val değerini ekler.İşlevin geri dönüş değeri eklenmiş öğenin konumu .

	iterator insert(iterator where, iterator source_beg, iterator source_end);//31. where konumuna[beg end) aralığındaki değerleri ekler.İşlevin geri dönüş değeri ilk eklenmiş öğenin konumu .

	iterator erase(iterator where);	//34. where konumundaki öğeyi silmeli.İşlevin geri dönüş değeri silinmiş öğeden sonraki öğenin konumu olmalı

	iterator erase(iterator where, iterator source_beg, iterator source_end);	//35.[beg end) aralığındaki değerleri siler.İşlevin geri dönüş değeri silinen öğelerden sonraki öğenin konumu .

	void push_back(int val); 	//36. push_back işlevi.Parametresine gelen değeri Vector'e son öğe olarak ekler.

	void pop_back();	//37. pop_back işlevi.Vector'deki son öğeyi siler.

	void swap(Vector& Obj);	//38. swap işlevi iki Vector'ü takas eder. 

	void clear();	//39. clear işlevi iki Vector'deki tüm öğeleri silmeli yani Vector'ü boşaltmalır.

	int& front();	//42. front işlevi Vector'de tutulan ilk öğeyi döndürür. Vector'ün boş olması durumunda bu işlevin çağrılması tanımsız davranıştır.

	const int& front()const;	//43. front işlevi Vector'de tutulan ilk öğeye const referans döndürür (const overloading). Vector'ün boş olması durumunda bu işlevin çağrılması tanımsız davranıştır.

	int& back();	//44. back işlevi Vector'de tutulan son öğeyi döndürür. Vector'ün boş olması durumunda bu işlevin çağrılması tanımsız davranıştır.

	const int& back()const;	//45. back işlevi Vector'de tutulan ilk öğeye const referans döndürür (const overloading). Vector'ün boş olması durumunda bu işlevin çağrılması tanımsız davranıştır.

	int& operator[](size_t x);	//46. operator[] işlevi.Vector'de tutulan idx indisli öğeyi döndürür. idx değerinin geçerli olmaması tanımsız davranıştır.

	const int& operator[](size_t x)const;	//47. operator[] işlevi.Vector'de tutulan idx indisli öğeyi (salt okuma erişimli) döndürmeli. (const overloading) idx değerinin geçerli olmaması tanımsız davranıştır.

	int* data();	//50. data işlevi Vector'de tutulan ilk öğenin adresini döndürür. Bu adres C işlevlerine bir dizi adresi olarak gönderilebilir.

	const int* data()const;	//51. data işlevi Vector'de tutulan ilk öğenin adresini (salt okuma erişimli) döndürmeli. Bu adres C api'lerine bir dizi adresi olarak gönderilebilir.

	size_t capacity()const;	//52. capacity işlevi Vector'ün kapasite değerini döndürür. Kapasite değeri Vector nesnesinin edindiği ve tutmakta olduğu dinamik bellek bloğunun öğe sayısı cinsinden büyüklüğüdür.

	size_t size()const;	//53. size işlevi Vector'ün size değerini döndürür. size değeri Vector nesnesinin tutmakta olduğu öğe sayısıdır.

	bool empty()const;	//54. empty işlevi Vector'ün boş olup olmadığını sınar.

};

class Vector::iterator {
public:
	int* p = nullptr;

	iterator& operator++();	//60. Ön ek ++ operatörü.iterator nesnesini 1 arttırarak bir sonraki öğenin konumunu tutmasını sağlar.

	iterator operator++(int);	//61. Son ek ++ operatörü.iterator nesnesini 1 arttırarak bir sonraki öğenin konumunu tutmasını sağlar.

	iterator& operator--();		//62. Ön ek -- operatörü.iterator nesnesini 1 eksilterek bir önceki öğenin konumunu tutmasını sağlar.

	iterator operator--(int);	//63. Son ek -- operatörü.iterator nesnesini 1 eksilterek bir önceki öğenin konumunu tutmasını sağlar.

	int& operator*();	//64. İçerik operatörü.iterator nesnesinin tuttuğu konumdaki öğeye eriştirir.

	int& operator[](int n);	//65. İndeks operatörü.iterator nesnesinin tuttuğu konumdaki öğeden n sonraki ya da önceki öğeye eriştirir. 

	std::ptrdiff_t diffiter(const iterator& it); 	//66. İki iterator arasındaki farkı döndürür.

	iterator operator+(size_t n);	//67. iterator konumundan n sonraki konumu döndürür

	iterator operator-(size_t n);	//68. iterator konumundan n önceki konumu döndürür.

	iterator& operator+=(size_t n);	//69. iterator nesnesini n sonraki nesnenin konumunu tutacak şekilde arttırır.

	iterator& operator-=(size_t n);	//70. iterator nesnesini n önceki nesnenin konumunu tutacak şekilde eksiltir.

	bool operator<(const iterator&)const;	//71. iterator nesnelerinin karşılaştırılmalarını sağlayan karşılaştıma operatör işlevleri.

	bool operator<=(const iterator&)const; //71

	bool operator>(const iterator&)const; //71

	bool operator>=(const iterator&)const; //71

	bool operator==(const iterator&)const; //71

	bool operator!=(const iterator&)const; //71


};

class Vector::const_iterator {
public:
	const int* p;


	iterator& operator++();  //80     
	iterator operator++(int); //81
	iterator& operator--();  //82
	iterator operator--(int); //83
	const int& operator*(); //84
	const int& operator[](int n);  //85
	ptrdiff_t operator-(iterator); //86
	const_iterator operator+(int n)const; //87
	const_iterator operator-(int n)const; //88
	const_iterator& operator+=(int n);  //89
	const_iterator& operator-=(int n);//90
	bool operator<(const const_iterator&)const; //91
	bool operator<=(const const_iterator&)const; //91
	bool operator>(const const_iterator&)const; //91
	bool operator>=(const const_iterator&)const; //91
	bool operator==(const const_iterator&)const; //91
	bool operator!=(const const_iterator&)const; //91
};
