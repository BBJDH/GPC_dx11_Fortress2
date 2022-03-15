#pragma once
//#include "Object_Poolable.h"

class Pool_manager
{
public:
    std::vector<Object_Poolable*> objects;

public:
    template<typename T>
    T* get_recycled_object()
    {
        T* poolObj = nullptr;

        if (objects.size() == 0)//최초 객체 생성
        {
            objects.push_back(dynamic_cast<Object_Poolable*>(poolObj = new T));
            return poolObj;
        }

        for (auto elem : objects) //재사용 가능한 객체를 찾는다
        {
            if (elem->CanRecylcable)
            {
                poolObj = static_cast<T*>(elem);
                break;
            }
        }

        if (poolObj == nullptr) //객체가 모두 사용중일때
        {
            objects.push_back(dynamic_cast<Object_Poolable*>(poolObj = new T));
            return poolObj;
        }

        poolObj->recycle();     //객체 재사용

        return poolObj;
    }
};

