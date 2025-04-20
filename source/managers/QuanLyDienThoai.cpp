#include "QuanLyDienThoai.h"

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

class QuanLyDienThoai::Iterator
{
public:
    // Các type alias cần thiết cho iterator traits (để tương thích STL)
    using iterator_category = forward_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = DienThoai;
    using pointer = DienThoai*;
    using reference = DienThoai&;

private:
    Node* current_node;
    Iterator(Node* node) : current_node(node) {}
    friend class QuanLyDienThoai;

public:
    Iterator() : current_node(nullptr) {}
    reference operator*() const
    {
        if (!current_node)
        {
            throw out_of_range("Dereference end() or null iterator");
        }
        return current_node->info;
    }

    pointer operator->() const
    {
        if (!current_node)
        {
            throw out_of_range("Accessing member via end() or null iterator");
        }
        return &(current_node->info);
    }

    Iterator& operator++()
    {
        if (current_node)
        {
            current_node = current_node->_pNext;
        }
        else
        {
            throw out_of_range("Incrementing end() or null iterator");
        }
        return *this;
    }

    Iterator operator++(int)
    {
        if (!current_node)
        {
            throw out_of_range("Incrementing end() or null iterator");
        }
        Iterator temp = *this;
        current_node = current_node->_pNext;
        return temp;
    }

    bool operator==(const Iterator& other) const
    {
        return current_node == other.current_node;
    }
    bool operator!=(const Iterator& other) const
    {
        return !(*this == other);
    }
};