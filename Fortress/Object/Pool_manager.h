#pragma once
//#include "Object_Poolable.h"

class Pool_manager
{
public:
    std::vector<Object_Poolable*> PoolObjects;

public:
    template<typename T>
    T* GetRecycledObject()
    {
        T* poolObj = nullptr;

        if (PoolObjects.size() == 0)
        {
            PoolObjects.push_back(dynamic_cast<Object_Poolable*>(poolObj = new T));
            return poolObj;
        }

        for (auto elem : PoolObjects)
        {
            if (elem->CanRecylcable)
            {
                poolObj = static_cast<T*>(elem);
                break;
            }
        }

        if (poolObj == nullptr)
        {
            PoolObjects.push_back(dynamic_cast<Object_Poolable*>(poolObj = new T));
            return poolObj;
        }

        poolObj->OnRecycle();

        return poolObj;
    }
};

