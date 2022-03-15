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

        if (objects.size() == 0)//���� ��ü ����
        {
            objects.push_back(dynamic_cast<Object_Poolable*>(poolObj = new T));
            return poolObj;
        }

        for (auto elem : objects) //���� ������ ��ü�� ã�´�
        {
            if (elem->CanRecylcable)
            {
                poolObj = static_cast<T*>(elem);
                break;
            }
        }

        if (poolObj == nullptr) //��ü�� ��� ������϶�
        {
            objects.push_back(dynamic_cast<Object_Poolable*>(poolObj = new T));
            return poolObj;
        }

        poolObj->recycle();     //��ü ����

        return poolObj;
    }
};

