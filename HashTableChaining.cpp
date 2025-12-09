#include "HashTableChaining.h"
#include <iostream>

using namespace std;

void DemostracionHashTableChaining()
{
    cout << "========================================" << endl;
    cout << "       PRUEBA 1: HASHTABLE NORMAL       " << endl;
    cout << "     (Permite elementos repetidos)      " << endl;
    cout << "========================================" << endl;

    // Creamos una Hash Table de 5 cubetas
    HashTableChaining<int> myTable(5);

    // Agregamos elementos, incluyendo repetidos (el 10 y el 5)
    myTable.Add(10); 
    myTable.Add(5);  
    myTable.Add(15); 
    myTable.Add(10); // Repetido
    myTable.Add(5);  // Repetido

    cout << "Contenido de la Tabla Hash:" << endl;
    myTable.Imprimir();


    cout << endl << endl;
    cout << "========================================" << endl;
    cout << "    PRUEBA 2: HASHSET (HERENCIA)        " << endl;
    cout << "     (NO permite elementos repetidos)   " << endl;
    cout << "========================================" << endl;

    // Creamos un HashSet de 5 cubetas
    HashSet<int> mySet(5);

    // Intentamos agregar exactamente los mismos numeros
    mySet.Add(10);
    cout << "- Agregado 10" << endl;
    
    mySet.Add(5);
    cout << "- Agregado 5" << endl;
    
    mySet.Add(15);
    cout << "- Agregado 15" << endl;

    mySet.Add(10); // Este NO deberia agregarse
    cout << "- Intento agregar 10 (repetido)..." << endl;

    mySet.Add(5);  // Este NO deberia agregarse
    cout << "- Intento agregar 5 (repetido)..." << endl;

    cout << endl << "Contenido del HashSet (Sin duplicados):" << endl;
    mySet.Imprimir();

    // Verificación final
    if(mySet.Encontrar(10)) 
        cout << "\nEl valor 10 existe en el Set (Correcto)." << endl;
    
    // Prueba de borrado en HashSet
    cout << "Borrando el 10..." << endl;
    mySet.BorrarValor(10);
    mySet.Imprimir();
}

int main()
{
    DemostracionHashTableChaining();
    return 0;
}