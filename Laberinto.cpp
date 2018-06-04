/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Laberinto.cpp
 * Author: Alan
 * 
 * Created on 7 de febrero de 2018, 04:46 PM
 */


#include <vector>
#include <stdio.h>
#include "Laberinto.h"
#include "Adyacencia.h"
#include <stdlib.h>
#include <time.h>
#include <bits/stl_vector.h>
#include <limits.h>


std::list<int>::iterator it;
Laberinto::Laberinto(int cantidadVrts, double probabilidadAdy){
    
    vertices.resize(cantidadVrts);
    for(int i=0;i<cantidadVrts;i++){
        double random;
        it = vertices[i].lstAdy.begin(); 
        for(int y=0;y<cantidadVrts;y++){
            double srand (time(NULL));
            random = rand()% 10+1;
            random/10;
            if(random <= probabilidadAdy){
                vertices[i].lstAdy.insert(it,y);
                ++it;
            }
        }
    }
}

Laberinto::Laberinto(ifstream& archivo){
    int pe;
    char finLinea = ' ';

    archivo >> pe;
    vertices.resize(pe);
    archivo >> pe;
    for (int i = 0; i<vertices.size()-1; i++) {
        it = vertices[i].lstAdy.begin();
        while (!archivo.eof()&&(finLinea != 10)) { // 10 ascii de fin de línea
            vertices[i].lstAdy.insert(it,pe);
            archivo >> pe;
            archivo.get(); // consume un blanco
            finLinea = archivo.peek(); // intenta leer fin de línea
        }
        if (!archivo.eof()){
        vertices[i].lstAdy.insert(it,pe);
        archivo >> pe;
        archivo.get();
        finLinea = archivo.peek();
        }
    }    
}

Laberinto::Laberinto(const Laberinto& orig){
    idVrtInicial = orig.idVrtInicial;
    idVrtFinal = orig.idVrtFinal;
    for (int i=0;i<sizeof(orig.vertices)-1;i++){
        vertices[i]=orig.vertices[i];
    }
//    memcopy (&vertices,&orig.vertices,sizeof(orig.vertices));
    datosAdys.insert(orig.datosAdys.begin(), orig.datosAdys.end());
}

Laberinto::~Laberinto() {
}

/* MÉTODOS OBSERVADORES BÁSICOS */
bool Laberinto::xstVrt(int idVrt) const {
    bool booleano = false;
    if (idVrt < vertices.size()-1){
        if (0 <= idVrt){
            booleano = true;
        }
    }
    return booleano;
}

bool Laberinto::xstAdy(int idVrtO, int idVrtD) const {
bool booleano = false;;
    if (idVrtO < vertices.size()){
        if (0 <= idVrtO){
           if (idVrtD < vertices.size()-1){
                if (0 <= idVrtD){                    
                    vector<int>ady;
                    obtIdVrtAdys(idVrtO,ady);
                    int i=0;
                    while(ady[i] != idVrtD || i<ady.size()){
                        if(ady[i] == idVrtD){
                            booleano = true;
                        }
                    }
                }
            }
        }
    }
    return booleano;
}

int Laberinto::obtIdVrtInicial() const {
    return idVrtInicial;
}

int Laberinto::obtIdVrtFinal() const {
    return idVrtFinal;
}

void Laberinto::obtIdVrtAdys(int idVrt, vector<int>& rsp) const {
    rsp.assign(vertices[idVrt].lstAdy.begin(),vertices[idVrt].lstAdy.end());
}

Adyacencia Laberinto::obtDatoAdy(int idVrtO, int idVrtD) const {
    
    int indice =obtIndiceAdy(idVrtO, idVrtD);
    Adyacencia adya(datosAdys.find(indice)->second);
    return adya;
}

int Laberinto::obtCntAdy(int idVrt) const {
    return sizeof(vertices[idVrt].lstAdy);
}

int Laberinto::obtTotAdy() const {
    return sizeof(datosAdys);
}

int Laberinto::obtTotVrt() const {
    return sizeof(vertices);
}

int Laberinto::caminoMasCorto(int idVrtO, int idVrtD, vector<int>& camino) const {
    vector<int>dist;
    vector<int>previo;
    vector<bool>visitados;
    dist.resize(sizeof(vertices,INT_MAX));
    previo.resize(sizeof(vertices,-1));
    visitados.resize(sizeof(vertices,false));
    if ((idVrtO < sizeof(vertices))&&(0 <= idVrtO)&&(idVrtD < sizeof(vertices))&&(0 <= idVrtD)){
        for (int p=0; p<sizeof(vertices); p++){
            if(xstAdy(idVrtO,p)){
                dist[p]= 1;
                previo[p]=idVrtO;
            }
        }
        dist[idVrtO] = 0;  
        while(visitados[idVrtD]== false){              //busca la distancia menor y el vertice que la tiene
            int idVrtMenor=-1;
            int distMenor= INT_MAX;
            for(int y = 0; y<sizeof(vertices); y++){
                if(dist[y]<distMenor && !visitados[y]){
                    idVrtMenor=y;
                    distMenor=dist[y];
                    previo[y]=idVrtO;
                }
            }
            vector<int>ady;
            obtIdVrtAdys(idVrtMenor,ady);
            visitados[idVrtMenor]=true;
            int prev=idVrtMenor;
            for(int i=0;i<sizeof(idVrtMenor);i++){               
                if(!visitados[ady[i]] && dist[idVrtMenor]+1<dist[ady[i]]){
                    dist[ady[i]]=dist[idVrtMenor]+1;
                }
            }
        }
    }
}
int Laberinto::caminoEncontrado(int idVrtO, int idVrtD, vector<int>& camino) const {
}

double Laberinto::sumaTotalFerormona() const {
    double fero;
    std::map<int,Adyacencia>::const_iterator it = datosAdys.begin();
    while ( it!=datosAdys.end()){
        Adyacencia adya(it->second);
        fero += adya.obtCntFerormona();
        it++;
    }
    return fero;
}

void Laberinto::asgIdVrtInicial(int idVrtInicialN) {
    idVrtInicial=idVrtInicialN;
}

void Laberinto::asgIdVrtFinal(int idVrtFinalN) {
    idVrtFinal=idVrtFinalN;
}

void Laberinto::asgDatoAdy(int idVrtO, int idVrtD, const Adyacencia& ady) {
    Adyacencia adya(ady);
    int indice = obtIndiceAdy(idVrtO, idVrtD);
    datosAdys.find(indice)->second = adya;
}    

void Laberinto::decrementarFerormonaAdys(double decrFerormona) {
    std::map<int,Adyacencia>::const_iterator it = datosAdys.begin();
    while ( it!=datosAdys.end()){
    it->second.asgCntFerormona(it->second.obtCntFerormona()*decrFerormona-it->second.obtCntFerormona());
    it++;
    }
}

void Laberinto::actualizarValoracionAdys() {
    for (int i=0;i<sizeof(vertices);i++){
        std::map<int,Adyacencia>::const_iterator it = vertices[i].lstAdy.begin();
        while ( it!=vertices[i].lstAdy.end()){
            
            it++;    
        }
    }
}

int Laberinto::obtIndiceAdy(int f, int c) const {
    if ( f > c){
        int t = f;
        f = t;
        c = f;
    }
    return f * vertices.size() + c - f * (f + 1) / 2;
}
    
    