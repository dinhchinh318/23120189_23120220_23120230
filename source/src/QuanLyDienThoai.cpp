#include "../include/QuanLyDienThoai.h"

QuanLyDienThoai::QuanLyDienThoai()
{
    _pHead = _pTail = nullptr;
    _soLuong = 0;
}

QuanLyDienThoai::~QuanLyDienThoai()
{
    Clear();
}

void QuanLyDienThoai::Clear()
{
    while (_pHead != nullptr)
    {
        RemoveHead();
    }
}

void QuanLyDienThoai::AddTail(const DienThoai& value)
{
    Node* node = CreateNode(value);
    if (node == nullptr)
    {
        return;
    }
    if (_pHead == nullptr)
    {
        _pHead = _pTail = node;
        _soLuong++;
        return;
    }
    _pTail->_pNext = node;
    _pTail = node;
    _soLuong++;
}

void QuanLyDienThoai::AddHead(const DienThoai& value)
{
    Node* node = CreateNode(value);
    if (!node) return;

    if (_pHead == nullptr)
    {
        _pHead = _pTail = node;
    }
    else
    {
        node->_pNext = _pHead;
        _pHead = node;
    }
    _soLuong++;
}

void QuanLyDienThoai::RemoveHead()
{
    if (_pHead == nullptr) return;

    Node* temp = _pHead;
    _pHead = _pHead->_pNext;
    delete temp;
    _soLuong--;

    if (_pHead == nullptr)
    {
        _pTail = nullptr;
    }
}

void QuanLyDienThoai::RemoveTail()
{
    if (_pTail == nullptr) return;

    if (_pHead == _pTail)
    {
        delete _pTail;
        _pHead = _pTail = nullptr;
    }
    else
    {
        Node* prev = _pHead;
        while (prev->_pNext != _pTail)
        {
            prev = prev->_pNext;
        }
        delete _pTail;
        _pTail = prev;
        _pTail->_pNext = nullptr;
    }
    _soLuong--;
}