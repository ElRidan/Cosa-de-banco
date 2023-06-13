#pragma once
#include <string>
#include <vector>
using namespace std;
class Transaccion {
private:
	double cantidad;
	string tipo;
public:
	Transaccion(double c, string t) {
		cantidad = c;
		tipo = t;
	}
	double getCantidad() {
		return cantidad;
	}
	string getTipo() {
		return tipo;
	}
	void setCantidad(double cant) {
		cantidad = cant;
	}
	void setTipo(string t) {
		tipo = t;
	}
};