#ifndef _QUAN_LY_DIEN_THOAI_H_
#define _QUAN_LY_DIEN_THOAI_H_

#include "DienThoai.h"

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
    //////////////////// --- class Iterator ---/////////////////////
    class Iterator 
    {
    public:
        // Các type alias cần thiết cho iterator traits (để tương thích STL)
        using iterator_category = forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = DienThoai;
        using pointer = DienThoai*;
        using reference = DienThoai&;

    private:
        Node* current;
        Iterator(Node* p) : current(p) {}
        friend class QuanLyDienThoai;
    public:
        Iterator() : current(nullptr) {}

        reference operator*() const
        {
            if (!current)
            {
                throw out_of_range("Dereference end() or null iterator");
            }
            return current->info;
        }

        pointer operator->() const
        {
            if (!current)
            {
                throw out_of_range("Accessing member via end() or null iterator");
            }
            return &(current->info);
        }

        Iterator& operator++()
        {
            if (current)
            {
                current = current->_pNext;
            }
            else
            {
                throw out_of_range("Incrementing end() or null iterator");
            }
            return *this;
        }

        Iterator operator++(int)
        {
            if (!current)
            {
                throw out_of_range("Incrementing end() or null iterator");
            }
            Iterator temp = *this;
            current = current->_pNext;
            return temp;
        }

        bool operator==(const Iterator& other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }
    };

public:
    /// Constructor
    QuanLyDienThoai();

    /// Destructor
    ~QuanLyDienThoai();

   /// Function
    void Push_back(const DienThoai&);
    void RemoveHead();
    void RemoveTail();
    void Remove(const DienThoai&);
    std::string wstringToString(const std::wstring& wstr);
    DienThoai* TimKiemTheoID(SQLHDBC db,const int&id);
    DienThoai* TimKiemTheoTen(SQLHDBC db, const string& ten);
    DienThoai TimKiem(const string&);
    void XoaDienThoaiTheoID(SQLHDBC db,const int& id);
    void XuatDanhSachDienThoai(SQLHDBC db);
    DienThoai TimKiem(const string&);
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

    /// Operator
    DienThoai& operator[](const int i)
    {
        Node* newNode = _pHead;
        for (int j = 0; j < i; j++)
        {
            newNode = newNode->_pNext;
        }
        return newNode->info;
    }

    friend ostream& operator<<(ostream& os, const QuanLyDienThoai& ll)
    {
        Node* node = ll._pHead;
        if (node == nullptr)
        {
            os << "📭 Khong co dien thoai nao trong danh sach\n";
            return os;
        }
        os << "\n📱 Danh sach dien thoai\n";
        int stt = 1;
        while (node != nullptr)
        {
            os << "Dien thoai " << stt++ << endl;
            os << node->info << "\n";
            node = node->_pNext;
        }
        return os;
    }

    
    
};

#endif