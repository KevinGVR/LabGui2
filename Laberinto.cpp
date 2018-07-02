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

#include "Laberinto.h"
#include "Adyacencia.h"

Laberinto::Laberinto(int cantidadVrts, double probabilidadAdy): laberintoPtr(shared_ptr< Grafo < int,Adyacencia > >(new Grafo< int,Adyacencia >(cantidadVrts,probabilidadAdy))), laberinto(*laberintoPtr){
    idVrtInicial = -1;
    idVrtFinal = -1;
    
}

Laberinto::Laberinto(ifstream& archivo): laberintoPtr(shared_ptr< Grafo < int,Adyacencia > >(new Grafo< int,Adyacencia >(archivo))), laberinto(*laberintoPtr) {
    idVrtInicial= -1;
    idVrtFinal = -1;
}

Laberinto::Laberinto(const Laberinto& orig): laberintoPtr(shared_ptr< Grafo < int,Adyacencia > >(new Grafo< int,Adyacencia >(orig.laberinto))), laberinto(*laberintoPtr) {
    idVrtInicial = orig.obtIdVrtInicial();
    idVrtFinal = orig.obtIdVrtFinal();
}

Laberinto::~Laberinto() {
}

/* MÉTODOS OBSERVADORES BÁSICOS */
bool Laberinto::xstVrt(int idVrt) const {
    return laberinto.xstVrt(idVrt);
}

bool Laberinto::xstAdy(int idVrtO, int idVrtD) const {
    return laberinto.xstAdy(idVrtO,idVrtD);
}

int Laberinto::obtIdVrtInicial() const {
    return idVrtInicial;
}

int Laberinto::obtIdVrtFinal() const {
    return idVrtFinal;
}

void Laberinto::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
    laberinto.obtIdVrtAdys(idVrt,rsp);
}

Adyacencia Laberinto::obtDatoAdy(int idVrtO, int idVrtD) const {
    laberinto.obtDatoAdy(idVrtO,idVrtD);
}

int Laberinto::obtTotAdy() const {
    laberinto.obtTotAdy();
}

int Laberinto::obtTotVrt() const {
    laberinto.obtTotVrt();
}

int Laberinto::caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const {
    laberinto.caminoMasCorto(idVrtO,idVrtD,camino);
}

int Laberinto::caminoEncontrado(int idVrtO, int idVrtD, vector<int>& camino) const {
    int vrtActual=idVrtO;    
    while(vrtActual != idVrtD){
        camino.push_back(vrtActual);
        double masFero=-1;
        int idMasFero =-1;
        vector<int> adys;
        laberinto.obtIdVrtAdys(vrtActual,adys);
        for(int i=0; i<adys.size();i++){
            Adyacencia adya;
            adya = laberinto.obtDatoAdy(vrtActual,adys[0]);
            if(adya.obtCntFerormona()>masFero){                
                masFero=adya.obtCntFerormona();
                idMasFero=adys[i];
            }
        }
        vrtActual=idMasFero;
    }
    return camino.size();
}

double Laberinto::sumaTotalFerormona() const {
    vector<int> vect;
    double suma;
    for(int i=0;i<laberinto.obtTotVrt();i++){ 
        laberinto.obtIdVrtAdys(i,vect);
        for(int j=0;j<vect.size();j++){
            if(laberinto.xstAdy(i,vect[j])){
                laberinto.obtDatoAdy(i,vect[j]);
                suma = suma + laberinto.obtDatoAdy(i,vect[j]).obtCntFerormona();
            }   
        }
    }  
    return suma;
}

void Laberinto::asgVrtInicial(int idVrtInicialN) {
    idVrtInicial = idVrtInicialN;
}

void Laberinto::asgVrtFinal(int idVrtFinalN) {
    idVrtFinal = idVrtFinalN;
}

void Laberinto::asgDatoAdy(int idVrtO, int idVrtD, const Adyacencia& ady) {
    laberinto.asgDatoAdy(idVrtO,idVrtD,ady);
}

void Laberinto::decrementarFerormonaAdys(double decrFerormona) {
    for (int i =0; i<laberinto.obtTotVrt();i++){
        vector <int> ady;
        laberinto.obtIdVrtAdys(i,ady);
        for(int c=0;c<ady.size();c++){
            Adyacencia ady(laberinto.obtDatoAdy(i,c));
            double cantFeror;
            cantFeror= ady.obtCntFerormona()*decrFerormona-ady.obtCntFerormona();
            ady.asgCntFerormona(cantFeror);
        }    
    }
}

void Laberinto::actualizarValoracionAdys() {
    double totalFeror = sumaTotalFerormona();
    for (int i =0; i<laberinto.obtTotVrt();i++){
        vector <int> adya;
        laberinto.obtIdVrtAdys(i,adya);
        for(int c=0;c<adya.size();c++){
            Adyacencia ady(laberinto.obtDatoAdy(i,c));
            double cantFeror= totalFeror/ady.obtCntFerormona();
            laberinto.asgDatoAdy(i,c,ady);
        }    
    }
}