#include "../include/QuanLyDienThoai.h"

QuanLyDienThoai::QuanLyDienThoai()
{
    _pHead = _pTail = nullptr;
    _soLuong = 0;
}

QuanLyDienThoai::~QuanLyDienThoai()
{
    while(_pHead)
    {
        Node* tmp = _pHead;
        _pHead = _pHead->_pNext;
        delete tmp;
        _soLuong--;
    }
}

void QuanLyDienThoai::Push_back(const DienThoai& dt)
{
    Node* node = new Node {dt, nullptr};
    if(!_pHead)
    {
        _pHead = _pTail = node;
    }
    else
    {
        _pTail->_pNext = node;
        _pTail = node;
    }
    _soLuong++;
}

void QuanLyDienThoai::RemoveHead()
{
    if(!_pHead) return;
    Node* tmp = _pHead;
    _pHead = _pHead->_pNext;
    delete tmp;
    if(!_pHead)
    {
        _pTail == nullptr;
    }
    _soLuong--;
}

void QuanLyDienThoai::RemoveTail()
{
    if (_pHead == nullptr)
    return;

    if (_pHead == _pTail)
    {
        Node* node = _pHead;
        _pHead = _pTail = nullptr;
        _soLuong--;
        return;
    }

    Node* prev = _pHead;
    while (prev->_pNext != _pTail)
    {
        prev = prev->_pNext;
    }
    Node* node = _pTail;
    _pTail = prev;
    _pTail->_pNext = nullptr;
    _soLuong--;
    return;
}

void QuanLyDienThoai::Remove(const DienThoai& dt)
{
    if(!_pHead) return;
    if(_pHead->info == dt) RemoveHead();
    else if(_pTail->info == dt) RemoveTail();
    else 
    {
        Node* tmp = _pHead;
        while(tmp->info != dt)
        {
            tmp = tmp->_pNext;
        }
        Node* del = tmp;
        tmp = tmp->_pNext;
        delete del;
    }
    _soLuong--;
}

void QuanLyDienThoai::Clear()
{
    while(_pHead)
    {
        Node* tmp = _pHead;
        _pHead = _pHead->_pNext;
        delete tmp;
        _soLuong--;
    }
}

// DienThoai QuanLyDienThoai::TimKiemTheoID(const int& id)
// {
//     Node* tmp = _pHead;
//     while(tmp)
//     {
//         if(tmp->info.getID() == id) return tmp->info;
//         tmp = tmp->_pNext;
//     }
//     return DienThoai();
// }

// DienThoai QuanLyDienThoai::TimKiemTheoTen(const string& ten)
// {
//     Node* tmp = _pHead;
//     while(tmp)
//     {
//         if(tmp->info.getTen() == ten) return tmp->info;
//         tmp = tmp->_pNext;
//     }
//     return DienThoai();
// }

DienThoai QuanLyDienThoai::TimKiem(const string& key)
{
    // Kiểm tra xem key có phải là một dãy số hay không
    bool isNumber = !key.empty() && all_of(key.begin(), key.end(), ::isdigit);

    Node* tmp = _pHead;
    if(isNumber)
    {
        int id = stoi(key);
        while(tmp)
        {
            if(tmp->info.getID() == id) return tmp->info;
            tmp = tmp->_pNext;
        }
    }
    else
    {
        while(tmp)
        {
            if(tmp->info.getTen() == key) return tmp->info;
            tmp = tmp->_pNext;
        }
    }
    return DienThoai(); // Trả về đối tượng rỗng nếu không tìm thấy
}
