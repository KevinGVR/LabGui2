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
    idVrtInicial = -1;  //Inicializa la variable idVrtInicial
    idVrtFinal = -1;    //Inicializa la variable idVrtFinal
//    for(int i = 0; i<laberinto.obtTotVrt(); i++){
//        vector<int> rsp;
//        laberinto.obtIdVrtAdys(i, rsp);
//        for(int j= 0; j< rsp.size(); j++){
//            Adyacencia a(1,0);
//            laberinto.asgDatoAdy(i,rsp[j],a);
//        }
//    }
    
}

Laberinto::Laberinto(ifstream& archivo): laberintoPtr(shared_ptr< Grafo < int,Adyacencia > >(new Grafo< int,Adyacencia >(archivo))), laberinto(*laberintoPtr) {
    idVrtInicial= -1;   //Inicializa la variable idVrtInicial
    idVrtFinal = -1;    //Inicializa la variable idVrtFinal
//    for(int i = 0; i<laberinto.obtTotVrt(); i++){
//        vector<int> rsp;
//        laberinto.obtIdVrtAdys(i, rsp);
//        for(int j= 0; j< rsp.size(); j++){
//            Adyacencia a(1,0);
//            laberinto.asgDatoAdy(i,rsp[j],a);
//        }
//    }
}

Laberinto::Laberinto(const Laberinto& orig): laberintoPtr(shared_ptr< Grafo < int,Adyacencia > >(new Grafo< int,Adyacencia >(orig.laberinto))), laberinto(*laberintoPtr) {
    idVrtInicial = orig.obtIdVrtInicial();  //Inicializa la variable idVrtInicial con la variable idVrtInicial de orig
    idVrtFinal = orig.obtIdVrtFinal();      //Inicializa la variable idVrtInicial con la variable idVrtInicial de orig
}
//Destructor
Laberinto::~Laberinto() {
}

/* MÉTODOS OBSERVADORES BÁSICOS */
bool Laberinto::xstVrt(int idVrt) const {
    return laberinto.xstVrt(idVrt); //Retorna si exite el vertice en el laberinto
}

bool Laberinto::xstAdy(int idVrtO, int idVrtD) const {
    return laberinto.xstAdy(idVrtO,idVrtD); //Retorna si existe la adyacencia entre el vertice idVrtO y el rl vertiCE idVrtD
}

int Laberinto::obtIdVrtInicial() const {
    return idVrtInicial;    //Retorna el vertice Inicial del laberinto
}

int Laberinto::obtIdVrtFinal() const {
    return idVrtFinal;  //Retorna el vertice Final del laberinto
}

void Laberinto::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
    laberinto.obtIdVrtAdys(idVrt,rsp); //Obtiene en el vector rsp todas las adyacencias del vetice merdiante la plantilla grafo
}

Adyacencia Laberinto::obtDatoAdy(int idVrtO, int idVrtD) const {
    laberinto.obtDatoAdy(idVrtO,idVrtD); //Obtiene la adyecencia entre el vertice idVrtO y el vertice idVrtD  merdiante la plantilla grafo
}

int Laberinto::obtTotAdy() const {
    laberinto.obtTotAdy(); // Obtiene el total de adyacencias del laberinto del laberinto mediante la plsntilla grafo
}

int Laberinto::obtTotVrt() const {
    laberinto.obtTotVrt();  // Obtiene el total de vertices del laberinto del laberinto mediante la plsntilla grafo
}

int Laberinto::caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const {
    laberinto.caminoMasCorto(idVrtO,idVrtD,camino); //Obtiene el camino mas corto del laberinto mediante la pantilla grafo
}

int Laberinto::caminoEncontrado(int idVrtO, int idVrtD, vector<int>& camino) const {
    return 0;
}

double Laberinto::sumaTotalFerormona() const {
    vector<int> vect;
    double suma;
    for(int i=0;i<laberinto.obtTotVrt();i++){ 
        laberinto.obtIdVrtAdys(i,vect);
        for(int j=0;j<vect.size();j++){
            if(laberinto.xstAdy(0,vect[j])){
                suma += laberinto.obtDatoAdy(i,vect[j]).obtCntFerormona();
            }
        }
    }  
    return suma;
}

void Laberinto::asgVrtInicial(int idVrtInicialN) {
    idVrtInicial = idVrtInicialN; //asigna al vertice inicial un valor
}

void Laberinto::asgVrtFinal(int idVrtFinalN) {
    idVrtFinal = idVrtFinalN; // asigna al vertice final un valor
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