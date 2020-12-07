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
    template <typename Type>
    static void Free(Type &object);

    template <typename Type>
    static bool PointerIsEmpty(const Type &object);
};

#endif
