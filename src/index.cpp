//Hecho por: Gabriel Vargas Monroy
#include <stdio.h>
#include <iostream>
#include<queue>

using namespace std;

struct Nodo
{
    int elemento;
    int izq;
    int der;
};

class ArbolBinario
{
    int numNodos;
    Nodo *arbol;

    public:
        ArbolBinario(int);
        int agregar(int,int);
        int eliminar(int,int);
        bool buscar(int,int);
        void mostrarInorden(int);
        void preOrden(int);
        void posOrden(int);
        void Niveles();
        int canthojas(int);
        int profundidad(int);
        bool esHoja(int);
        bool esCompleto(int);
        void reemplazar(int,int);

        int getraiz();
        void setarbolizq(int);
};

ArbolBinario::ArbolBinario(int cant)
{
    this->numNodos=cant;
    this->arbol=new Nodo[cant];
    arbol[0].der=arbol[0].izq=-1;
    for (int i=1;i<cant-1;i++)arbol[i-1].der=i;
    arbol[cant-1].der=-1;
}

int ArbolBinario::agregar (int raiz, int elemento)
{
    if (raiz != -1)
    {
        if(arbol[raiz].elemento<elemento)
        {
            arbol[raiz].der=agregar(arbol[raiz].der,elemento);
        }
        else
        {
            arbol[raiz].izq=agregar (arbol[raiz].izq,elemento);
        }
    }
    else
    {
        raiz=arbol[0].der;
        arbol[0].der=arbol[raiz].der;
        arbol[raiz].elemento=elemento;
        arbol[raiz].izq=arbol[raiz].der=-1;
    }
    return raiz;
}

bool ArbolBinario::esHoja (int raiz)
{
    return arbol[raiz].der != -1 && arbol[raiz].izq != -1;
}

bool ArbolBinario::buscar (int raiz, int elemento)
{
    if (raiz == -1){return false;}
    if (arbol[raiz].elemento == elemento){return true;}
    if (arbol[raiz].elemento>elemento){return buscar(arbol[raiz].izq,elemento);}
    if (arbol[raiz].elemento<elemento){return buscar(arbol[raiz].der,elemento);}
    return false;
}

int ArbolBinario::eliminar (int posicion,int valor)
{
    if (arbol[0].izq==-1){return -1;}
    if (arbol[0].izq==posicion && arbol[posicion].izq==-1 && arbol[posicion].der==-1)
    {
        arbol[0].izq=-1;
        arbol[posicion].der=arbol[0].der;
        arbol[0].der=posicion;
        return -1;
    }
    if (arbol[0].izq==posicion)
    {
        if (arbol[posicion].elemento==valor)
        {
            if (arbol[posicion].der != -1)
            {
                if (arbol[arbol[posicion].der].izq ==-1)
                {
                    int temp=arbol[posicion].der;
                    arbol[temp].izq=arbol[posicion].izq;
                    arbol[posicion].der=arbol[0].der;
                    arbol[0].der=posicion;
                    arbol[0].izq=temp;
                    return -1;
                }
                else
                {
                    int padre,hijo;
                    padre=arbol[posicion].der;
                    hijo=arbol[padre].izq;
                    while (arbol[hijo].izq!=-1)
                    {
                        padre=hijo;
                        hijo=arbol[hijo].izq;
                    }
                    arbol[padre].izq=arbol[hijo].der;
                    arbol[hijo].izq=arbol[posicion].izq;
                    arbol[hijo].der=arbol[posicion].der;
                    arbol[posicion].der=arbol[0].der;
                    arbol[0].der=posicion;
                    arbol[0].izq=hijo;
                    return -1;
                }
            }
            else
            {
                if (arbol[arbol[posicion].izq].der==-1)
                {
                    int temp=arbol[posicion].izq;
                    arbol[temp].der=arbol[posicion].der;
                    arbol[posicion].der=arbol[0].der;
                    arbol[0].der=posicion;
                    arbol[0].izq=temp;
                    return -1;
                }
                else
                {
                    int padre,hijo;
                    padre=arbol[posicion].izq;
                    hijo=arbol[padre].der;
                    while (arbol[hijo].der!=-1)
                    {
                        padre=hijo;
                        hijo=arbol[hijo].der;
                    }
                    arbol[padre].der=arbol[hijo].izq;
                    arbol[hijo].der=arbol[posicion].der;
                    arbol[hijo].izq=arbol[posicion].izq;
                    arbol[posicion].der=arbol[0].der;
                    arbol[0].der=posicion;
                    arbol[0].izq=hijo;
                    return -1;
                }
            }
        }
        else
        {
            if (valor>arbol[posicion].elemento)
            {
                arbol[posicion].der=eliminar(arbol[posicion].der,valor);
            }
            else
            {
                arbol[posicion].izq=eliminar(arbol[posicion].izq,valor);
            }
            return -1;
        }
    }
    if (arbol[posicion].elemento==-1)
    {
        return -1;
    }
    if (valor<arbol[posicion].elemento)
    {
        arbol[posicion].izq=eliminar (arbol[posicion].izq, valor);
        return posicion;
    }
    if (valor>arbol[posicion].elemento)
    {
        arbol[posicion].der=eliminar (arbol[posicion].der, valor);
        return posicion;
    }
    if (arbol[posicion].elemento==valor)
    {
        if (arbol[posicion].der!=-1)
        {
            if (arbol[arbol[posicion].der].izq==-1)
            {
                int temp=arbol[posicion].der;
                arbol[temp].izq=arbol[posicion].izq;
                arbol[posicion].der=arbol[0].der;
                arbol[0].der=posicion;
                return temp;
            }
            else
            {
                int padre,hijo;
                padre=arbol[posicion].der;
                hijo=arbol[padre].izq;
                while (arbol[hijo].izq!=-1)
                {
                    padre=hijo;
                    hijo=arbol[hijo].izq;
                }
                arbol[padre].izq=arbol[hijo].der;
                arbol[hijo].izq=arbol[posicion].izq;
                arbol[hijo].der=arbol[posicion].der;
                arbol[posicion].der=arbol[0].der;
                arbol[0].der=posicion;
                return hijo;
            }
        }
        else
        {
            if (arbol[posicion].izq==-1)
            {
                return -1;//YA QUE ES UNA HOJA
            }
            if (arbol[arbol[posicion].izq].der==-1)
            {
                int temp=arbol[posicion].der;
                arbol[temp].der=arbol[posicion].der;
                arbol[posicion].der=arbol[0].der;
                arbol[0].der=posicion;
                return temp;
            }
            else
            {
                int padre,hijo;
                padre=arbol[posicion].izq;
                hijo=arbol[padre].der;
                while (arbol[hijo].der!=-1)
                {
                    padre=hijo;
                    hijo=arbol[hijo].der;
                }
                arbol[padre].der=arbol[hijo].izq;
                arbol[hijo].der=arbol[posicion].der;
                arbol[hijo].izq=arbol[posicion].izq;
                arbol[posicion].der=arbol[0].der;
                arbol[0].der=posicion;
                return hijo;
            }
        }
    }
    return -1;
}

bool ArbolBinario::esCompleto (int pos)
{
    if (pos == -1){return true;}
    if (arbol[pos].izq == -1 && arbol[pos].der == -1){return true;}
    if (arbol[pos].izq != -1 && arbol[pos].der != -1)
        {return esCompleto (arbol[pos].izq) && esCompleto (arbol[pos].der);}
    return false;
}

int ArbolBinario::canthojas (int clave)
{
    if (clave == -1) return 0;
    if (arbol[clave].izq==-1 && arbol[clave].der==-1) return 1;
    return canthojas (arbol[clave].izq)+canthojas (arbol[clave].der);
}

void ArbolBinario::mostrarInorden (int clave)
{
    if (clave != -1)
    {
        mostrarInorden (arbol[clave].izq);
        cout<<arbol[clave].elemento<<" "<<endl;
        mostrarInorden (arbol[clave].der);
    }
}

void ArbolBinario::preOrden (int clave)
{
    if (clave != -1)
    {
        cout<<arbol[clave].elemento<<" "<<endl;
        preOrden (arbol[clave].izq);
        preOrden (arbol[clave].der);
    }
}

void ArbolBinario::posOrden (int clave)
{
    if (clave != -1)
    {
        posOrden (arbol[clave].izq);
        posOrden (arbol[clave].der);
        cout<<arbol[clave].elemento<<" "<<endl;
    }
}

void ArbolBinario::Niveles ()
{
    if (getraiz () != -1)
    {
        queue<Nodo> q;
        q.push(arbol[getraiz ()]);
        while(!q.empty ())
        {
            Nodo nodo=q.front ();
            cout<<nodo.elemento<<endl;
            q.pop ();
            if (nodo.izq!=-1) q.push(arbol[nodo.izq]);
            if (nodo.der!=-1) q.push(arbol[nodo.der]);
        }
    }
}

int ArbolBinario::profundidad (int pos)
{
    if (pos ==-1){return 0;}
    if (arbol[pos].izq == -1 && arbol[pos].der == -1){return 1;}
    if (profundidad (arbol[pos].izq)>=profundidad (arbol[pos].der))
    {
        return 1+profundidad (arbol[pos].izq);
    }
    if (profundidad (arbol[pos].izq)<profundidad (arbol[pos].der))
    {
        return 1+profundidad (arbol[pos].izq);
    }
    return 0;
}

int ArbolBinario::getraiz (){return arbol[0].izq;}

void ArbolBinario::setarbolizq (int val)
{
    arbol[0].izq=val;
}

char menuMostrar()
{
    cout<<"-----------------"<<endl;
    cout<<"(P)reorden"<<endl;
    cout<<"(I)norden"<<endl;
    cout<<"P(O)srden"<<endl;
    cout<<"(N)iveles"<<endl;
    cout<<"Ingrese opcion: ";
    char val;
    cin>>val;
    cout<<"---------------"<<endl;
    return val;
}

char menu()
{
    cout<<"---------------"<<endl;
    cout<<"Arbol Binario con arreglo estatico"<<endl;
    cout<<"(A)gregar Elemento"<<endl;
    cout<<"(E)liminar Elemento"<<endl;
    cout<<"(M)ostrar Elementos"<<endl;
    cout<<"(B)uscar Elemento"<<endl;
    cout<<"(C)ontar hojas"<<endl;
    cout<<"Calcular (P)rofundidad"<<endl;
    cout<<"Revizar si es C(O)mpleto"<<endl;
    cout<<"(S)alir"<<endl;
    cout<<"Ingrese opcion: ";
    char val;
    cin>>val;
    cout<<"---------------"<<endl;
    return val;
}

int main()
{
    ArbolBinario ab =*new ArbolBinario(50);
    char dato=menu();
    while (dato != 's' && dato != 'S')
    {
        switch (dato)
        {
            case('A'):
            case('a'):
            {
                int x;
                cout<<"Ingrese el valor a agregar: ";
                cin>>x;
                if (ab.getraiz ()==-1)
                {
                    ab.setarbolizq (ab.agregar (ab.getraiz (), x));
                }
                else
                {
                    ab.agregar (ab.getraiz (), x);
                }
            }
            break;
            case('E'):
            case('e'):
            {
                int x;
                cout<<"Ingrese el valor a Eliminar: ";
                cin>>x;
                if (ab.eliminar (ab.getraiz (),x))
                {
                    cout<<"Hecho Correctamente"<<endl;
                }
                else
                {
                    cout<<"Hubo un Error"<<endl;
                }
            }
            break;
            case('M'):
            case('m'):
            {
                char opcionmenu=menuMostrar ();
                switch(opcionmenu)
                {
                    case ('p'):
                    case ('P'):
                    {
                        ab.preOrden (ab.getraiz ());
                        cout<<"--"<<endl;
                    }
                    break;
                    case ('i'):
                    case ('I'):
                    {
                        ab.mostrarInorden (ab.getraiz ());
                    }
                    break;
                    case ('O'):
                    case ('o'):
                    {
                        ab.posOrden (ab.getraiz ());
                    }
                    break;
                    case ('N'):
                    case ('n'):
                    {
                        ab.Niveles ();
                    }
                    break;
                }
            }
            break;
            case('B'):
            case('b'):
            {
                int x;
                cout<<"Ingrese el valor a Buscar: ";
                cin>>x;
                if (ab.buscar (ab.getraiz (),x))
                {
                    cout<<"Elemento Encontrado!!"<<endl;
                }
                else
                {
                    cout<<"Elemento No Encontrado"<<endl;
                }
            }
            break;
            case('C'):
            case('c'):
            {
                cout<<"Las hojas en el programa son: "<<ab.canthojas (ab.getraiz ())<<endl;
            }
            break;
            case('P'):
            case('p'):
            {
                cout<<"La profundidad del arbol es: "<<ab.profundidad (ab.getraiz ())<<endl;
            }
            break;
            case('O'):
            case('o'):
            {
                if (ab.esCompleto (ab.getraiz ()))
                {
                    cout<<"El arbol es Completo"<<endl;
                }
                else
                {
                    cout<<"El arbol no es completo"<<endl;
                }
            }
            break;
        }
        dato=menu();
    }
    return 0;
}
