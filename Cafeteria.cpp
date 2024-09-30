#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std;

// Estructura para almacenar la información de cada producto
struct Producto {
    string nombre;
    double precio;
    double costo_fijo;
    int unidades_vendidas;
    double ventas;
    double utilidad;
};

// Mutex para proteger el acceso a las variables compartidas
mutex mtx;

// Función para el calculo de  las ventas y la utilidad de un producto
void calcularVentasYUtilidad(Producto &producto, int hilo_num, double &total_ventas, double &total_utilidad) {
    cout << "Calculo hilo " << hilo_num << " iniciado" << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simular procesamiento en paralelo

    // Cálculo de ventas y utilidad
    producto.ventas = producto.unidades_vendidas * producto.precio;
    producto.utilidad = producto.ventas - (producto.unidades_vendidas * producto.costo_fijo);

    // Sección crítica: actualizar las ventas y utilidad totales con protección del mutex
    mtx.lock();
    total_ventas += producto.ventas;
    total_utilidad += producto.utilidad;
    mtx.unlock();

    cout << "Calculo hilo " << hilo_num << " terminado" << endl;
}

int main() {
    // Los datos del mes de julio
    vector<Producto> productos_julio = {
        {"Porcion pastel de chocolate", 60.0, 20.0, 300},
        {"White mocha", 32.0, 19.2, 400},
        {"Café americano 8onz", 22.0, 13.2, 1590},
        {"Latte 8onz", 24.0, 17.2, 200},
        {"Toffee coffee", 28.0, 20.1, 390},
        {"Cappuccino 8onz", 24.0, 17.2, 1455},
        {"S'mores Latte", 32.0, 23.0, 800},
        {"Café tostado molido", 60.0, 20.0, 60}
    };

    // Los datos del mes de agosto
    vector<Producto> productos_agosto = {
        {"Porcion pastel de chocolate", 60.0, 20.0, 250},
        {"White mocha", 32.0, 19.2, 380},
        {"Café americano 8onz", 22.0, 13.2, 800},
        {"Latte 8onz", 24.0, 17.2, 250},
        {"Toffee coffee", 28.0, 20.1, 600},
        {"Cappuccino 8onz", 24.0, 17.2, 1200},
        {"S'mores Latte", 32.0, 23.0, 1540},
        {"Café tostado molido", 60.0, 20.0, 15}
    };

    // Variables para almacenar las ventas y utilidad totales de cada mes
    double total_ventas_julio = 0, total_utilidad_julio = 0;
    double total_ventas_agosto = 0, total_utilidad_agosto = 0;

    // Se usan los vectores para almacenar los hilos
    vector<thread> hilos_julio;
    vector<thread> hilos_agosto;

    // Usar  los hilos para calcular las ventas y utilidades de cada producto en julio
    for (int i = 0; i < productos_julio.size(); ++i) {
        hilos_julio.push_back(thread(calcularVentasYUtilidad, ref(productos_julio[i]), i, ref(total_ventas_julio), ref(total_utilidad_julio)));
    }

    // Esperar a que terminen todos los hilos de julio
    for (auto &hilo : hilos_julio) {
        hilo.join();
    }

    // Se imprime el reporte de julio
    cout << "------------------------------------------" << endl;
    cout << "REPORTE DEL MES DE JULIO" << endl;
    cout << "--- Monto Ventas por Producto ---" << endl;
    for (const auto &producto : productos_julio) {
        cout << producto.nombre << ": Q" << producto.ventas << endl;
    }
    cout << "--- Utilidad por Producto ---" << endl;
    for (const auto &producto : productos_julio) {
        cout << producto.nombre << ": Q" << producto.utilidad << endl;
    }
    cout << "--- Monto Total Ventas del Mes: Q" << total_ventas_julio << endl;
    cout << "--- Utilidad del mes: Q" << total_utilidad_julio << endl;

    // Lanzar los hilos para calcular las ventas y utilidades de cada producto en agosto
    for (int i = 0; i < productos_agosto.size(); ++i) {
        hilos_agosto.push_back(thread(calcularVentasYUtilidad, ref(productos_agosto[i]), i, ref(total_ventas_agosto), ref(total_utilidad_agosto)));
    }

    // Se espera a que terminen todos los hilos de agosto
    for (auto &hilo : hilos_agosto) {
        hilo.join();
    }

    // Se imprime el reporte de agosto
    cout << "------------------------------------------" << endl;
    cout << "REPORTE DEL MES DE AGOSTO" << endl;
    cout << "--- Monto Ventas por Producto ---" << endl;
    for (const auto &producto : productos_agosto) {
        cout << producto.nombre << ": Q" << producto.ventas << endl;
    }
    cout << "--- Utilidad por Producto ---" << endl;
    for (const auto &producto : productos_agosto) {
        cout << producto.nombre << ": Q" << producto.utilidad << endl;
    }
    cout << "--- Monto Total Ventas del Mes: Q" << total_ventas_agosto << endl;
    cout << "--- Utilidad del mes: Q" << total_utilidad_agosto << endl;

    return 0;
}