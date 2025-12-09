#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t count;

public:
    LinkedList() : head(nullptr), count(0) {}

    ~LinkedList()
    {
        Limpiar();
    }

    void PushBack(T value)
    {
        Node* nuevoNodo = new Node(value);
        if (head == nullptr)
        {
            head = nuevoNodo;
        }
        else
        {
            Node* actual = head;
            while (actual->next != nullptr)
            {
                actual = actual->next;
            }
            actual->next = nuevoNodo;
        }
        count++;
    }

    bool Encontrar(T value)
    {
        Node* actual = head;
        while (actual != nullptr)
        {
            if (actual->data == value)
                return true;
            actual = actual->next;
        }
        return false;
    }

    bool BorrarNodoPorValor(T value)
    {
        if (head == nullptr)
            return false;

        // Si el primer nodo contiene el valor
        if (head->data == value)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            count--;
            return true;
        }

        // Buscar en el resto de la lista
        Node* actual = head;
        while (actual->next != nullptr)
        {
            if (actual->next->data == value)
            {
                Node* temp = actual->next;
                actual->next = temp->next;
                delete temp;
                count--;
                return true;
            }
            actual = actual->next;
        }
        return false;
    }

    void Print()
    {
        Node* actual = head;
        while (actual != nullptr)
        {
            cout << actual->data << " ";
            actual = actual->next;
        }
        cout << endl;
    }

    size_t GetCount() const
    {
        return count;
    }

    void Limpiar()
    {
        Node* actual = head;
        while (actual != nullptr)
        {
            Node* temp = actual;
            actual = actual->next;
            delete temp;
        }
        head = nullptr;
        count = 0;
    }
};
