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
#include <time.h>
#include <bits/stl_vector.h>


std::list<int>::iterator it;
Laberinto::Laberinto(int cantidadVrts, double probabilidadAdy){
    
    vertices.resize(cantidadVrts);
    double random;
    for(int i=0;i<cantidadVrts;i++){
        it = vertices[i].lstAdy.begin(); 
        for(int y=0;y<cantidadVrts;y++){
            srand (time(NULL));
            random = (rand()% 10+1)/10;
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
    for (int i = 0; i<vertices.size(); i++) {
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
    for (int i=0;i<sizeof(orig.vertices);i++){
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
    if (idVrt < vertices.size()){
        if (0 <= idVrt){
            booleano = true;
        }
    }
    return booleano;
}

bool Laberinto::xstAdy(int idVrtO, int idVrtD) const {
bool booleano;
    if (idVrtO < vertices.size()){
        if (0 <= idVrtO){
           if (idVrtD < vertices.size()){
                if (0 <= idVrtD){
//                    vertices::iterator it;
//                    for(it.begin();it != it.end()){
//                        vertices[idVrtO].lstAdy.;
//                        //booleano = arregloVrts[idVrtO].lstAdy.buscar(idVrtD);   
//                    }
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
    Adyacencia adya;
//    adya.asgCntFerormona(datosAdys[obtIndiceAdy(idVrtO,idVrtD)]->);
//    return adya;
//    datosAdys[obtIndiceAdy(idVrtO,idVrtD)];
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

//int Laberinto::caminoMasCorto(int idVrtO, int idVrtD, vector<int>& camino) const {
//}
//
//int Laberinto::caminoEncontrado(int idVrtO, int idVrtD, vector<int>& camino) const {
//}

double Laberinto::sumaTotalFerormona() const {
}

void Laberinto::asgIdVrtInicial(int idVrtInicialN) {
}

void Laberinto::asgIdVrtFinal(int idVrtFinalN) {
}

void Laberinto::asgDatoAdy(int idVrtO, int idVrtD, const Adyacencia& ady) {
}

void Laberinto::decrementarFerormonaAdys(double decrFerormona) {
}

void Laberinto::actualizarValoracionAdys() {
}

int Laberinto::obtIndiceAdy(int f, int c) const {
    if ( f > c){
        int t = f;
        f = t;
        c = f;
    }
    return f * vertices.size() + c - f * (f + 1) / 2;
}