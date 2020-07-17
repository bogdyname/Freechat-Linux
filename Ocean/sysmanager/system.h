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

/*----------------------------------------INFO OF OBJECT----------------------------------------*/
public:
    template <typename Type>
    void Free(Type &object);
/*----------------------------------------INFO OF OBJECT----------------------------------------*/



/*----------------------------------------INFO OF OBJECT----------------------------------------*/
public:
    template <typename Type>
    bool PointerIsEmpty(const Type &object);
/*----------------------------------------INFO OF OBJECT----------------------------------------*/
};

#endif
