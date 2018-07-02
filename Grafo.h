/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Grafo.h
 * Author: Alan
 *
 * Created on 5 de febrero de 2018, 05:49 PM
 */

#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <limits.h>

#include "Adyacencia.h"
using namespace std;

template < typename V, typename A >
class Grafo {
    // Representa un grafo con vértices de tipo V y adyacencias de tipo A.
    /* SUPUESTOS:
     * 1. Los vértices son identificados con números de 0 a N-1, dada N la cantidad
     * total de vértices.
     * 2. El tipo V tiene definido su constructor estándar V().
     * 3. El tipo V tiene definido su constructor de copias V(const V& orig);
     * 4. El tipo A tiene definido su constructor estándar A().
     * 5. El tipo A tiene definido su constructor de copias A(const A& orig);
     */
    

public:
    /* CONSTRUCTORES */

    // REQ: cantidadVrt > 0. En este caso, N es igual a cantidadVrt.
    // REQ: 0 < probabilidadAdy < 1.
    // Construye un grafo con cantidadVrt de vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando probabilidadAdy. Esto
    // implica que la probabilidad de que un arco exista entre cualesquiera dos
    // dos vértices es igual a probabilidadAdy
    Grafo( int cantidadVrt, double probabilidadAdy);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices tienen un índice que va de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con V().
    Grafo(ifstream& archivo);

    // Construye una copia idéntica a orig.
    Grafo(const Grafo< V, A >& orig);

    // Destructor
    ~Grafo();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el grafo.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    V operator[](int idVrt) const;

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: retorna los datos de la adyacencia entre <idVrtO, idVrtD>.
    // NOTA: retorna por valor para que NO pueda ser modificado.    
    A obtDatoAdy(int idVrtO, int idVrtD) const;

    // EFE: retorna el total de arcos o adyacencias en el grafo.
    int obtTotAdy() const;

    // EFE: retorna el total de vértices en el grafo.
    int obtTotVrt() const;

    /* MÉTODOS OBSERVADORES NO BÁSICOS*/

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: retorna en "camino" los índices de los vértices que conforman el
    //      camino más corto entre idVrtO y idVrtD.
    int caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const;

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    V& operator[](int idVrt);

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: asigna el valor "a" a la adyacencia <idVrtO, idVrtD>.
    void asgDatoAdy(int idVrtO, int idVrtD, const A& a);

private:

    template < typename W >
    struct Vrt {
        W w;
        list< int > lstAdy;

        Vrt< W >() : w(W()), lstAdy() {
        }; // constructor estándar de Vrt

        Vrt< W >(const W& ww) : w(ww), lstAdy() {
        }; // constructor con dato de vértice

        Vrt< W >(const Vrt< W >& vrt) : w(vrt.w), lstAdy(vrt.lstAdy) {
        }; // constructor de copias de Vrt
    };

    // REQ: (f >= 0) && (c >= 0) && (N > 0)
    // RET: valor único asociado a f y c con base en N = vectorVrts.size().

    static long fIdUnico(int f, int c, int N) {
        if (f > c) {
            int t = f;
            f = c;
            c = t;
        }
        return f * N + c - f * (f + 1) / 2;
    };

    vector< Vrt< V > > vectorVrts; // vector de vértices
    unordered_map< long, A > mapAdys; // map basado en hashing de adyacencias
};

template < typename V, typename A >
Grafo< V, A >::Grafo(int cantidadVrt, double probabilidadAdy) { 
    vectorVrts.resize(cantidadVrt);    
    for(long i=0;i<cantidadVrt;i++){
            double random;            
            for(long y=0; y<cantidadVrt;y++){
                if(i<y){
                    double srand (time(NULL));
                    random = rand()% 1000+1;
                    random = random/1000.0;
                    if(random <= probabilidadAdy){
                        A a;
                        vectorVrts[i].lstAdy.push_back(y);
                        long x = fIdUnico(i,y,cantidadVrt);
                        mapAdys.insert(typename unordered_map<long,A>::value_type(x,a));                   
                    }
                }    
            }
        }
}

template < typename V, typename A >
Grafo< V, A >::Grafo(ifstream& archivo) {
    int pe;
    A a;
    char finLinea = ' ';
    archivo >> pe;
    vectorVrts.resize(pe);
    archivo >> pe;
    for (int i = 0; i<vectorVrts.size(); i++) {
        while (!archivo.eof()&&(finLinea != 10)) { // 10 ascii de fin de línea
            
            vectorVrts[i].lstAdy.push_back(pe);
            long x = fIdUnico(i,pe,vectorVrts.size());
            mapAdys.insert(typename unordered_map<long,A>::value_type(x,a));   
            archivo >> pe;
            archivo.get(); // consume un blanco
            finLinea = archivo.peek(); // intenta leer fin de línea
        }
        if (!archivo.eof()){
        vectorVrts[i].lstAdy.push_back(pe);
        long x = fIdUnico(i,pe,vectorVrts.size());
        mapAdys.insert(typename unordered_map<long,A>::value_type(x,a)); 
        archivo >> pe;
        archivo.get();
        finLinea = archivo.peek();        
        }
    }  
}

template < typename V, typename A >
Grafo< V, A >::Grafo(const Grafo< V, A >& orig) {
    for (int i=0;i<orig.vectorVrts.size()-1;i++){
        vectorVrts[i]=orig.vectorVrts[i];
    }
//    memcopy (&vectorVrts,&orig.vectorVrts,sizeof(orig.vectorVrts));
    mapAdys.insert(orig.mapAdys.begin(), orig.mapAdys.end());
}

template < typename V, typename A >
Grafo< V, A >::~Grafo() {
}

template < typename V, typename A >
bool Grafo< V, A >::xstVrt(int idVrt) const {
    bool booleano = false;
    if (idVrt < vectorVrts.size()-1){
        if (0 <= idVrt){
            booleano = true;
        }
    }
    return booleano;
}

template < typename V, typename A >
bool Grafo< V, A >::xstAdy(int idVrtO, int idVrtD) const {
    bool booleano = false;;
    if (idVrtO < vectorVrts.size() && 0 <= idVrtO){
           if (idVrtD < vectorVrts.size() && 0 <= idVrtD){                   
                    vector<int>ady;
                    obtIdVrtAdys(idVrtO,ady);
                    int i=0;
                    while(i<ady.size()){
                        if(ady[i] == idVrtD){
                            booleano = true;
                        }
                        i++;
                    }
            }
    }
    if(idVrtO == idVrtD){
        booleano = false;
    }       
    return booleano;
}

template < typename V, typename A >
void Grafo< V, A >::obtIdVrtAdys(int idVrt, vector< int >& rspRetornar) const {
    rspRetornar.assign(vectorVrts[idVrt].lstAdy.begin(),vectorVrts[idVrt].lstAdy.end());
}

template < typename V, typename A >
V Grafo< V, A >::operator[](int idVrt) const {
    return vectorVrts[idVrt].w;
}

template < typename V, typename A >
A Grafo< V, A >::obtDatoAdy(int idVrtO, int idVrtD) const {
    long id = fIdUnico(idVrtO,idVrtD, vectorVrts.size());
    A a (mapAdys.find(id)->second);
    return a;
}

template < typename V, typename A >
int Grafo< V, A >::obtTotAdy() const {
    return mapAdys.size();
}

template < typename V, typename A >
int Grafo< V, A >::obtTotVrt() const {
    return vectorVrts.size();
}

template < typename V, typename A >
V& Grafo< V, A >::operator[](int idVrt) {
    V* v_ptr= new  V(); // sólo para que compile, elimine este código
    return *v_ptr;
}

template < typename V, typename A >
int Grafo< V, A >::caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const {
    vector<int>previo, dist;   //distancia que hay entre idVrtO y un vertice
    vector<bool>visitados;
    previo.resize(vectorVrts.size(), -1); //arreglo donde se guardan los vectorVrts adyacentes previos
    dist.resize(vectorVrts.size(), INT_MAX);   //distancia que hay entre idVrtO y un vertice
    visitados.resize(vectorVrts.size(), false);    
    if ((idVrtO < vectorVrts.size())&&(0 <= idVrtO)&&(idVrtD < vectorVrts.size())&&(0 <= idVrtD)){
        for (int p=0; p<vectorVrts.size(); p++){
            if(xstAdy(idVrtO,p)){
                dist[p]= 1;
                previo[p]=idVrtO;
            }
        }
        dist[idVrtO] = 0;               //indica la distancia de idVrtO en dist[]
        visitados[idVrtO] = true;       //indica como visitado a IdVrtO
        while(visitados[idVrtD]== false){                   //busca la distancia menor y el vertice que la tiene
            int idVrtMenor=-1;
            int distMenor= INT_MAX;
            for(int y = 0; y<vectorVrts.size(); y++){
                if(dist[y]<distMenor && !visitados[y]){
                    idVrtMenor=y;
                    distMenor=dist[y];
                }
            }
            vector<int> adys; 
            obtIdVrtAdys(idVrtMenor,adys);
            visitados[idVrtMenor]=true;
            int prev=idVrtMenor;
            for(int i=0;i<adys.size();i++){               
                if(!visitados[adys[i]] && dist[idVrtMenor]+1<dist[adys[i]]){
                    previo[adys[i]]=prev;
                    dist[adys[i]]=dist[idVrtMenor]+1;                    
                }
            }           
        }
        camino.resize(1);
            int i;
            i=idVrtD;
            while(i != idVrtO){
                camino.push_back(i);
                i=previo[i];
            }
    }   
    return dist[idVrtD];
}

template < typename V, typename A >
void Grafo< V, A >::asgDatoAdy(int idVrtO, int idVrtD, const A& a) {
    A aa(a);
    long id = fIdUnico(idVrtO,idVrtD, vectorVrts.size());
    mapAdys.find(id)->second = aa;
}
#endif /* GRAFO_H */


