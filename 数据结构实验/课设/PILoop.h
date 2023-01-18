#pragma once
#include "PassInfo.h"
class PILoop :
    public PassInfo
{
public:
    friend class RouteLoopRe;
    friend class PublicTransport;
    friend class Tool;
    PILoop() = default;
    ~PILoop() {
        _head = _head;// ->m_next;
        while (_head) {
            PassInfo* _p = _head;
            _head = _head->m_next;
            delete _p;
        }
    }
private:
    PassInfo* _head = nullptr;
    PassInfo* _tail = nullptr;
    int m_runNum;
    PILoop* m_runNext = nullptr;

};

