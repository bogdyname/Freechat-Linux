/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>

class System
{
public:
    constexpr System();

/*------------------------------------ACTION WITH AN OBJECT--------------------------------------*/
public:
    template <typename Type>
    static void Free(Type &object);
/*------------------------------------ACTION WITH AN OBJECT--------------------------------------*/



/*----------------------------------------INFO OF OBJECT----------------------------------------*/
public:
    template <typename Type>
    static bool PointerIsEmpty(const Type &object);
/*----------------------------------------INFO OF OBJECT----------------------------------------*/
};

#endif
