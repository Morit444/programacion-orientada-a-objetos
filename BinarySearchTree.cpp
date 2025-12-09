#include "BinarySearchTree.h"
#include <iostream>

using namespace std;

void DemostracionBinarySearchTree()
{
    BinarySearchTree<float> myBST;

    // Insercion de datos
    myBST.Add(5); 
    myBST.Add(3); 
    myBST.Add(8); 
    myBST.Add(4); 
    myBST.Add(7);
    myBST.Add(2);
    myBST.Add(9);
    
    // Pruebas de recorridos base
    cout << "--- Recorridos Originales ---" << endl;
    myBST.InOrderRecursivo();
    myBST.PreOrderRecursivo();
    myBST.PostOrderRecursivo();

    // Prueba 1: Busqueda Iterativa
    cout << endl << "--- Busqueda Iterativa ---" << endl;
    float val1 = 7, val2 = 15;
    cout << "Buscando " << val1 << ": " << (myBST.Search(val1) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscando " << val2 << ": " << (myBST.Search(val2) ? "Encontrado" : "No encontrado") << endl;

    // Prueba 2: Post-Order Iterativo
    cout << endl << "--- Post-Order Iterativo ---" << endl;
    myBST.PostOrderIterative();

    // Prueba de Minimos, Maximos y Sucesores
    cout << endl << "--- Pruebas Varias ---" << endl;
    cout << "Max: " << myBST.MaxValue() << endl;
    cout << "Min: " << myBST.MinValue() << endl;
    cout << "Siguiente de 5: " << myBST.Siguiente(5) << endl;
    cout << "Anterior de 5: " << myBST.Anterior(5) << endl;

    // Pruebas de borrado individual
    cout << endl << "--- Borrado Individual (Nodo 2 y 8) ---" << endl;
    myBST.BorrarPorValor(2);
    myBST.BorrarPorValor(8);
    myBST.InOrderRecursivo();

    // Prueba 3: Borrado Total (Clear)
    cout << endl << "--- Vaciar Arbol (Clear) ---" << endl;
    myBST.Clear();
    
    // Verificacion de arbol vacio
    if (myBST.Search(5) == false)
    {
        cout << "El arbol se ha vaciado correctamente." << endl;
    }
    
    // Reiniciar arbol para prueba final
    myBST.Add(10);
    cout << "Nueva raiz agregada tras vaciado: " << myBST.MaxValue() << endl;
}

int main()
{
    DemostracionBinarySearchTree();
    return 0;
}