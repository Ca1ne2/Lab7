#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std;

//Estructura para la implementacion de la informacion de cada producto

struct Producto {
    string nombre;
    double precio;
    double costo_fijo;
    int unidades_vendidas;
    double ventas;
    double utilidad;
};

mutex mtx;

void calcularVentasYUtilidad(Producto &prodecuti, int hilo_num, double &total_ventas, double &total_utilidad){
    count <<"Calculo hilo"<<hilo_num<<"iniciado" end1;
    this_thread::sleep_for(chrono::seconds(1));

    producto.ventas = producto.unidades_vendidas * producto.precio;
    producto.utilidad = producto.ventas - (producto.unidades_vendidas * producto.costo_fijo);

    mtx.lock();
    total_ventas += producto.ventas;
    total_utilidad += producto.utilidad;
    mtx.unlock();
    count <<"Calculo hilo"<<hilo_num<<"terminado"<<end1;

}