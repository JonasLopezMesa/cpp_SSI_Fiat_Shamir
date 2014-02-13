//
//  main.cpp
//  Fiat-Shamir
//
//  Created by jonas on 09/04/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;
struct Alice {
    int p; //privado
    int q; //privado
    int N; //público
    int s; //Secreto individual de A SECRETO
    int v; //marca de identificación (verifica si una persona conoce o no el secreto) PÚBLICO
    int a;
};
struct ite {
    int x;
    int e;
};
struct Bac {
    int y;
};
int euc(int x,int y){
    return (!y) ? x : euc(y,x%y);
}
int main()
{
    //PETICIÓN DE DATOS/////////////////////////
    Alice A; Bac B;
    bool primo = true;
    int i, divisor, X=1;
    cout << "ENTRADA: " << endl;
    while (X==1) {
        primo = true;
        cout << "p= ";cin >> A.p;
        for (divisor=2; divisor<=sqrt(A.p); divisor++) {
            if (A.p%divisor==0) {
                primo = false;
            }
        }
        if (primo == true) {
            X=0;
        } else {
            cout << "Debe introducirse un número primo" << endl;
        }
    }
    primo = true; X=1;
    while (X==1) {
        primo = true;
        cout << "q= ";cin >> A.q;
        for (divisor=2; divisor<=sqrt(A.q); divisor++) {
            if (A.q%divisor==0) {
                primo = false;
            }
        }
        if (primo == true) {
            X=0;
        } else {
            cout << "Debe introducirse un número primo" << endl;
        }
    }
    A.N = A.p-1*A.q-1;
    int u = 1;
    while (u == 1) {
        cout << "s= ";cin >> A.s;
        if (A.s > 0 && A.s < A.N) {
            if (euc(A.s, A.N) == 1) {
                u = 0;
            } else {
                cout << "Debe ser un número primo con N" << endl;
            }
        } else {
            cout << "Debe ser un número entre s y N" << endl;
        }
    }
    cout << A.N << endl;
    
    
    cout << "i(nº de iteraciones)= ";cin >> i;
    ite IT[i];
    for (int j = 0; j < i; j++) {
        cout << "Iteración:" << j+1 <<  "x=";cin >> IT[j].x;
        IT[j].e = 2;
        while (IT[j].e!=0 && IT[j].e!=1) {
            cout << "e= "; cin >> IT[j].e;
            if (IT[j].e!=0 && IT[j].e!=1) {
                cout << "e debe ser 0 o 1" << endl;
            }
        }
        
    }
    //Generación de clave/////////////////////////
    A.N = A.p*A.q; //Genera N
    A.v = A.s*A.s; //Genera V (abajo tb)
    A.v = A.v%A.N;
    cout << "N: "<<A.N << endl;
    cout << "N: "<<A.v << endl;
    //Protocolo/////////////////////////////////
    for (int j = 0; j < i; j++) {
        //Testigo: A envía a B
        A.a = IT[j].x*IT[j].x;
        A.a = A.a%A.N;
        //enviar un bit e elegido al azar IT[j].e
        //Respuesta A envía a B
        if (IT[j].e == 0) {
            B.y = IT[j].x%A.N;
        } else if (IT[j].e == 1){
            B.y = IT[j].x*A.s;
            B.y = B.y%A.N;
        }
        
        //Verificación B comprueba la información recibida.
        
        if (IT[j].e == 0) {
            
            cout << "Iteración nº " << j+1 << ": " << "a= " << A.a << ", comprobar que " << B.y << "^2 = " << A.a << "(mod " << A.N << ") y dar por válida la iteración" << endl;
            if ((B.y*B.y)%A.N == A.a%A.N) {
                cout << "Iteración válida" << endl;
            }
        } else if (IT[j].e == 1) {
            cout << "Iteración nº " << j+1 << ": " << "a= " << A.a << ", y= " << B.y << ", comprobar que " << B.y << "^2 = " << A.a << "*" << A.v << "(mod " << A.N << ") y dar por válida la iteración" << endl;
            int c = A.a*A.v;
            if ((B.y*B.y)%A.N == c%A.N) {
                cout << (B.y*B.y)%A.N << endl;
                cout << "Iteración válida" << endl;
            }
        }
    }
    return 0;
}