#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <stdexcept>

using namespace std;

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    ~BinarySearchTree()
    {
        Clear();
    }

    void Add(T value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            return;
        }

        Node* nodoActual = root;
        while (true)
        {
            if (value > nodoActual->value)
            {
                if (nodoActual->rightChild != nullptr)
                {
                    nodoActual = nodoActual->rightChild;
                }
                else
                {
                    Node* nuevoNodo = new Node(value);
                    nodoActual->rightChild = nuevoNodo;
                    nuevoNodo->parent = nodoActual;
                    return;
                }
            }
            else // value <= nodoActual->value
            {
                if (nodoActual->leftChild != nullptr)
                {
                    nodoActual = nodoActual->leftChild;
                }
                else
                {
                    Node* nuevoNodo = new Node(value);
                    nodoActual->leftChild = nuevoNodo;
                    nuevoNodo->parent = nodoActual;
                    return;
                }
            }
        }
    }

    // --- PUNTO 2: Búsqueda Iterativa ---
    bool Search(T value)
    {
        Node* nodoActual = root;
        while (nodoActual != nullptr)
        {
            if (nodoActual->value == value)
                return true;

            if (value < nodoActual->value)
                nodoActual = nodoActual->leftChild;
            else
                nodoActual = nodoActual->rightChild;
        }
        return false;
    }

    // --- PUNTO 3: Borrado Total (Recursivo) ---
    void Clear()
    {
        ClearRecursive(root);
        root = nullptr;
    }

    // --- PUNTO 4: Post-Order Iterativo ---
    void PostOrderIterative()
    {
        if (root == nullptr) return;

        stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty())
        {
            Node* nodo = s1.top();
            s1.pop();
            s2.push(nodo);

            if (nodo->leftChild)
                s1.push(nodo->leftChild);
            if (nodo->rightChild)
                s1.push(nodo->rightChild);
        }

        while (!s2.empty())
        {
            Node* nodo = s2.top();
            s2.pop();
            cout << nodo->value << ", ";
        }
        cout << endl;
    }

    bool Find(T value)
    {
        Node* resultado = FindNode(value);
        return resultado != nullptr;
    }

    T MaxValue()
    {
        if (root == nullptr) return T{};
        Node* nodoActual = root;
        while (nodoActual->rightChild != nullptr)
        {
            nodoActual = nodoActual->rightChild;
        }
        return nodoActual->value;
    }

    T MinValue()
    {
        if (root == nullptr) return T{};
        Node* nodoActual = root;
        while (nodoActual->leftChild != nullptr)
        {
            nodoActual = nodoActual->leftChild;
        }
        return nodoActual->value;
    }

    T Siguiente(T value)
    {
        Node* nodoConValue = FindNode(value);
        if (nodoConValue == nullptr) return T{};

        Node* sucesor = Sucesor(nodoConValue);
        if (sucesor == nullptr) return T{};
        
        return sucesor->value;
    }

    T Anterior(T value)
    {
        Node* nodoConValue = FindNode(value);
        if (nodoConValue == nullptr) return T{};

        Node* predecesor = Predecesor(nodoConValue);
        if (predecesor == nullptr) return T{};

        return predecesor->value;
    }

    bool BorrarPorValor(T valor)
    {
        if (root == nullptr) return false;

        Node* nodoABorrar = FindNode(valor);
        if (nodoABorrar == nullptr) return false;

        // Caso 1: Hoja
        if (nodoABorrar->leftChild == nullptr && nodoABorrar->rightChild == nullptr)
        {
            DeleteCaso1(nodoABorrar);
            return true;
        }
        // Caso 2: Un solo hijo
        if ((nodoABorrar->leftChild == nullptr) != (nodoABorrar->rightChild == nullptr))
        {
            DeleteCaso2(nodoABorrar);
            return true;
        }

        // Caso 3: Dos hijos
        Node* nodoSucesor = Sucesor(nodoABorrar);
        Node* hijoDerechoDelSucesor = nodoSucesor->rightChild;
        Node* padreDelSucesor = nodoSucesor->parent;

        nodoSucesor->leftChild = nodoABorrar->leftChild;
        if(nodoSucesor != nodoABorrar->rightChild)
            nodoSucesor->rightChild = nodoABorrar->rightChild;

        nodoSucesor->leftChild->parent = nodoSucesor;
        
        if (nodoSucesor->rightChild != nullptr)
            nodoSucesor->rightChild->parent = nodoSucesor;

        nodoSucesor->parent = nodoABorrar->parent;
        
        if (nodoABorrar->parent != nullptr)
        {
            if (nodoABorrar->parent->leftChild == nodoABorrar)
                nodoSucesor->parent->leftChild = nodoSucesor;
            else
                nodoSucesor->parent->rightChild = nodoSucesor;
        }
        else
        {
            root = nodoSucesor;
        }

        if (padreDelSucesor != nullptr)
            padreDelSucesor->leftChild = hijoDerechoDelSucesor;

        if (hijoDerechoDelSucesor != nullptr)
            hijoDerechoDelSucesor->parent = padreDelSucesor;

        delete nodoABorrar;
        return true;
    }

    // Recorridos Públicos
    void InOrderRecursivo()
    {
        InOrderRecursivo(root);
        cout << endl;
    }

    void PreOrderRecursivo()
    {
        PreOrderRecursivo(root);
        cout << endl;
    }

    void PostOrderRecursivo()
    {
        PostOrderRecursivo(root);
        cout << endl;
    }

    pair<T, T> ObtenerMinimoYMaximo()
    {
        return { MinValue(), MaxValue() };
    }

    vector<T> ObtenerRaizMinimoYMaximoConVector()
    {
        vector<T> resultado;
        if(root) resultado.push_back(root->value);
        resultado.push_back(MinValue());
        resultado.push_back(MaxValue());
        return resultado;
    }

private:
    class Node
    {
    public:
        Node(T _value) : value(_value), parent(nullptr), rightChild(nullptr), leftChild(nullptr) {}
        T value;
        Node* parent;
        Node* rightChild;
        Node* leftChild;
    };

    Node* root;

    // Helper recursivo para el Punto 3
    void ClearRecursive(Node* nodo)
    {
        if (nodo == nullptr) return;
        ClearRecursive(nodo->leftChild);
        ClearRecursive(nodo->rightChild);
        delete nodo;
    }

    void DeleteCaso1(Node* nodoABorrar)
    {
        if (nodoABorrar->parent == nullptr)
        {
            delete nodoABorrar;
            root = nullptr;
            return;
        }
        if (nodoABorrar->parent->leftChild == nodoABorrar)
            nodoABorrar->parent->leftChild = nullptr;
        else
            nodoABorrar->parent->rightChild = nullptr;

        delete nodoABorrar;
    }

    void DeleteCaso2(Node* nodoABorrar)
    {
        Node* hijo = (nodoABorrar->leftChild) ? nodoABorrar->leftChild : nodoABorrar->rightChild;
        hijo->parent = nodoABorrar->parent;

        if (nodoABorrar == root)
        {
            root = hijo;
        }
        else if (nodoABorrar->parent->leftChild == nodoABorrar)
        {
            nodoABorrar->parent->leftChild = hijo;
        }
        else
        {
            nodoABorrar->parent->rightChild = hijo;
        }
        delete nodoABorrar;
    }

    Node* FindNode(T value)
    {
        Node* nodoActual = root;
        while (nodoActual != nullptr)
        {
            if (nodoActual->value == value)
                return nodoActual;

            if (value > nodoActual->value)
                nodoActual = nodoActual->rightChild;
            else
                nodoActual = nodoActual->leftChild;
        }
        return nullptr;
    }

    Node* Sucesor(Node* node)
    {
        if (node->rightChild != nullptr)
        {
            Node* actual = node->rightChild;
            while (actual->leftChild != nullptr)
                actual = actual->leftChild;
            return actual;
        }
        
        Node* actual = node;
        Node* padre = actual->parent;
        while(padre != nullptr && actual == padre->rightChild)
        {
            actual = padre;
            padre = padre->parent;
        }
        return padre;
    }

    Node* Predecesor(Node* node)
    {
        if (node->leftChild != nullptr)
        {
            Node* actual = node->leftChild;
            while (actual->rightChild != nullptr)
                actual = actual->rightChild;
            return actual;
        }

        Node* actual = node;
        Node* padre = actual->parent;
        while (padre != nullptr && actual == padre->leftChild)
        {
            actual = padre;
            padre = padre->parent;
        }
        return padre;
    }

    void InOrderRecursivo(Node* nodo)
    {
        if (nodo)
        {
            InOrderRecursivo(nodo->leftChild);
            cout << nodo->value << ", ";
            InOrderRecursivo(nodo->rightChild);
        }
    }

    void PreOrderRecursivo(Node* nodo)
    {
        if (nodo)
        {
            cout << nodo->value << ", ";
            PreOrderRecursivo(nodo->leftChild);
            PreOrderRecursivo(nodo->rightChild);
        }
    }

    void PostOrderRecursivo(Node* nodo)
    {
        if (nodo)
        {
            PostOrderRecursivo(nodo->leftChild);
            PostOrderRecursivo(nodo->rightChild);
            cout << nodo->value << ", ";
        }
    }
};