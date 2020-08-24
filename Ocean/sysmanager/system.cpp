/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
***Contact: donvalentiy@yandex.ru
*/

#include "system.h"

constexpr System::System()
{

}

template <typename Type>
void System::Free(Type &object)
{
    delete object;
    object = nullptr;

    return;
}

template <typename Type>
bool System::PointerIsEmpty(const Type &object)
{
    if(object)
        return false;
    else
        return true;
}
