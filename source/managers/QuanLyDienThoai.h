#ifndef _QUAN_LY_DIEN_THOAI_H_
#define _QUAN_LY_DIEN_THOAI_H_

#include "../lib/lib.cpp"
#include "../models/DienThoai.h"

class QuanLyDienThoai {
private:
    struct Node
    {
        DienThoai info;
        Node* _pNext;
    };

    Node* _pHead, *_pTail;
    int _soLuong;
    static Node* CreateNode(const DienThoai& value)
    {
        Node* node = new Node{ value, nullptr };
        return node;
    }

public:
class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* p) : current(p) {}
        Iterator& operator++() {
            current = current->_pNext;
            return *this;
        }
        bool operator!=(const Iterator& it) const {
            return current != it.current;
        }
        const DienThoai& operator*() const {
            return current->info;
        }
    };

    QuanLyDienThoai();
    ~QuanLyDienThoai();

    void AddHead(const DienThoai&);
    void AddTail(const DienThoai&);
    void RemoveHead();
    void RemoveTail();
    void Clear();


    /// --- Iterator ---
    Iterator begin()
    {
        return Iterator(_pHead);
    }

    Iterator end()
    {
        return Iterator(nullptr); // Iterator end() trỏ tới nullptr
    }

    friend ostream& operator<<(ostream& os, const QuanLyDienThoai& ll)
    {
        Node* node = ll._pHead;
        if (node == nullptr)
        {
            os << "📭 Không có điện thoại nào trong danh sách.\n";
            return os;
        }
        os << "\n📱 Danh sách điện thoại:\n";
        while (node != nullptr)
        {
            os << node->info << ", ";
            node = node->_pNext;
        }
        return os;
    }
};

#endif