#ifndef _PHONE_MANAGEMENT_H_
#define _PHONE_MANAGEMENT_H_

#include "Phone.h"

class PhoneManagement {
private:
    struct Node
    {
        Phone info;
        Node* _pNext;
    };

    Node* _pHead, * _pTail;
    int _numberOfPhones;
    static Node* CreateNode(const Phone& value)
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
        using value_type = Phone;
        using pointer = Phone*;
        using reference = Phone&;

    private:
        Node* current;
        Iterator(Node* p) : current(p) {}
        friend class PhoneManagement;
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
    PhoneManagement();

    ~PhoneManagement();

    /// Function
    void Push_back(const Phone&);
    void RemoveHead();
    void RemoveTail();
    void Remove(const Phone&);

    Phone* findByID(SQLHDBC db, const int& id);
    Phone* findByName(SQLHDBC db, const string& name);
    //DienThoai TimKiem(const string&);
    void removePhoneByID(SQLHDBC db, const int& id);
    void printPhoneList(SQLHDBC db);
    //DienThoai TimKiem(const string&);

    void getPhoneList(SQLHDBC db);
    void editPhoneInfor(SQLHDBC db, int id);
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
    Phone& operator[](const int i)
    {
        Node* newNode = _pHead;
        for (int j = 0; j < i; j++)
        {
            newNode = newNode->_pNext;
        }
        return newNode->info;
    }

    friend ostream& operator<<(ostream& os, const PhoneManagement& ll)
    {
        Node* node = ll._pHead;
        if (node == nullptr)
        {
            os << "No phone in list phone\n";
            return os;
        }
        os << "\nList Phone\n";
        int pos = 1;
        while (node != nullptr)
        {
            os << "Phone " << pos++ << endl;
            os << node->info << "\n";
            node = node->_pNext;
        }
        return os;
    }
};
extern SQLCHAR connStr[];
bool connectToSQL(SQLHENV& hEnv, SQLHDBC& hDbc);
string wstringToString(const std::wstring& wstr);
std::wstring stringToWString(const std::string& str);
std::vector<Phone> getPhonesFromDatabase();
std::vector<Phone> getPhonesByMaxPriceDesc(float maxPrice);
std::vector<Phone> getPhonesByManuAndPriceOrder(const std::string& order, const std::string& manufacturer);
#endif
