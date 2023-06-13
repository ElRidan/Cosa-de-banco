#pragma once
#pragma once

#include "Transacciones.h"

using namespace std;
class Cliente {
private:
	string nombre;
	string contrasena;
	double cuentaSoles;
	vector<Transaccion*> transacciones;
	int Id;
	static int nextId;	
public:
	Cliente(string nombre, string contrasena, double cuentaSoles = 0) {
		this->nombre = nombre;
		this->contrasena = contrasena;
		this->cuentaSoles = cuentaSoles;
		nextId++;
		Id = nextId;
		
	}
	~Cliente() {
	}

	string getNombre() {
		return nombre;
	}

	string getContrasena() {
		return contrasena;
	}

	int getId() {
		return Id;
	}

	double getCuentaSoles() {
		return cuentaSoles;
	}

	void setCuentaSoles(double n) {
		cuentaSoles = n;
	}

	void setNombre(string n) {
		this->nombre = n;
	}

	void setContrasena(string n) {
		this->contrasena = n;
	}

	vector<Transaccion*> getTransacciones() {
		return transacciones;
	}

};

int Cliente::nextId = 0;