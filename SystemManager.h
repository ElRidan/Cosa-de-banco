#pragma once

#include"Cliente.h"
#include<iostream>
#include <fstream>
#include <cstdio>
#include <regex>
#include <stdlib.h>
#include <conio.h>
using namespace std;
class SystemManager {
private:
	vector<Cliente*> listaClientes;
	bool inicioSesion;
public:
	SystemManager() {
		inicioSesion = false;
		cargarListaClientes();
	}

	~SystemManager() {
		guardarListaClientes();
	}

	bool comprobarUsuario(string nombre, string contrasena) {
		for (Cliente* ctrCliente : listaClientes) {
			if (nombre == ctrCliente->getNombre()  ) {
				if (contrasena == ctrCliente->getContrasena()  ) {
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	void Registrar() {
		string nombre, contrasena;               

		cout << "Ingrese su nombre: "; cin >> nombre;
		cout << "Ingresa tu Contraseña: "; cin >> contrasena;

		const regex patron("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[-+_!@#$%^&*.,?]).+$");
		if (!regex_match(contrasena, patron))
		{
			cerr << "Error, su contraseña deberia tener por lo menos un caracter especial,\n un numero, una mayuscula, y una minuscula." << endl;
			return;
		}
		if (listaClientes.empty())
		{
			listaClientes.push_back(new Cliente(nombre, contrasena));
			cout << "Registro de usuario exitoso" << endl;
			crearArchivoCliente(Cliente(nombre,contrasena));
		}

		else
		{
			
			for (int i = 0; i > listaClientes.size(); i++) {
				if (listaClientes[i]->getNombre() == nombre) {
					cerr << "Error, nombre de usuario ya existente. Intente de nuevo" << endl;
					return;	
				}
				else
				{
					continue;
				}	
				
			}		
			listaClientes.push_back(new Cliente(nombre, contrasena));
			cout << "Registro de usuario exitoso" << endl;
			crearArchivoCliente(Cliente(nombre, contrasena));

			
		}
	}

	void Login() {
		
		string nombre, contrasena;

		cout << "Ingrese su nombre: "; cin >> nombre;
		cout << "Ingresa tu Contraseña: "; cin >> contrasena;
		inicioSesion = comprobarUsuario(nombre, contrasena);
			if (inicioSesion == true) {
				cout << "Usted a Iniciado sesion exitosamente"<<endl;
				system("cls");
				Cliente *c = cargarArchivoCliente(Cliente(nombre, contrasena));
				menuCliente(c);
			}
			else {
				cout << "Contraseña o usuario incorrectos o no registrados." << endl;
				cout << "Presione Y para Intentar de nuevo" << endl;
				cout << "Presione N para salir al menu" << endl;
				char ch = _getch();
			
				while (ch != 'y' && ch != 'n')
				{
					
					if (ch == 'y')
					{
						system("cls");
						Login();
					}
					else if (ch == 'n')
					{
						return;
					}
					{
					
					}
				}
			

		}
	}

	void menu() {
		int opcion;
		string nombre, contrasena;
		cout << "1. Registrarse" << endl;
		cout << "2. Iniciar sesion" << endl;
		cout << "3. Salir" << endl;
		cout << "4. Mostrar lista de clientes" << endl;
		cout << "Ingrese una opcion: ";  
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			

			Registrar();
			system("pause");
			system("cls");
			menu();
			break;

		case 2:
			Login();

			system("pause");
			system("cls");
			menu();
			break;

		case 3:
			guardarListaClientes();
			exit(1);

		case 4:
			mostrarListaDeClientes();
			system("pause");
			system("cls");
			menu();
		default:
			cout << "Ingrese una opcion diferente" << endl;
			system("pause");
			system("cls");
			menu();
		}

	}

	void menuCliente(Cliente* c) {
		leerArchivoTransaccion(c);
		int opcion;
		cout << "1. Revisar cuenta bancaria" << endl;
		cout << "2. Realizar transaccion" << endl;
		cout << "3. Revisar movimientos" << endl;
		cout << "4. Salir" << endl;
		cout << "Ingrese una opcion" << endl;
		cin >> opcion;
		switch (opcion){
			case 1:
				system("cls");
				revisarCuenta(c);
				system("pause");
				system("cls");
				
				menuCliente(c);	
				break;
			case 2:
				system("cls");
				realizarTransaccion(c);
				system("pause");
				system("cls");
				menuCliente(c);
				break;
			case 3:
				system("cls");
				revisarMovimientos(c);
				system("pause");
				system("cls");
				menuCliente(c);
			case 4:
				system("cls");
				menu();

		default:
			break;
		}
	}

	void revisarCuenta(Cliente* c) {
		cout << "================ Cuenta del cliente ================" << endl;
		cout << "Cuenta Bancaria en Soles: " << c->getCuentaSoles() << endl;
	}

	void realizarTransaccion(Cliente* c) {
		int opcion;
		cout << "Ingrese una opcion para realizar una accion en su cuenta: "<<endl; 
		cout << "1.Depositar" << endl;
		cout << "2.Retirar" << endl;
		
		
		
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			system("cls");
			realizarDespositoCuenta(c);

			system("pause");
			system("cls");
			menuCliente(c);
			break;
		case 2:
			system("cls");
			realizarRetiroCuenta(c);

			system("pause");
			system("cls");
			menuCliente(c);
			break;
		case 3:
			menuCliente(c);
		default:
			cout << "Opcion invalida, intente de nuevo" << endl;
			realizarTransaccion(c);
		}
	}

	void revisarMovimientos(Cliente* c) {
		int count = 1;
		cout << "Lista de Transacciones \n\n";
		for  (auto t : c->getTransacciones())
		{

			cout << "#########################" << endl;
			cout << "Transaccion" << count << "==========" << endl;
			cout << "Tipo: " << t->getTipo() << endl;
			cout << "Cantidad: " << t->getCantidad() << endl;
			count++;
		}
		
	}
	void realizarRetiroCuenta(Cliente* c) {
		double monto;
		string tipo = "Retiro";
		do
		{
			cout << "Saldo actual: " << c->getCuentaSoles() << endl;
			cout << "Ingrese la cantidad a retirar: ";
			cin >> monto;
			if (monto < 0) {
				cout<<"No se puede retirar una cantidad negativa de su cuenta";
				system("pause");
				system("cls");
				continue;
			}
			else {
				"Monto valido\n";
				continue;
				}
			if (monto > c->getCuentaSoles()) {
				cout << "Fondos Insuficientes en su cuenta" << endl; 
				system("cls");
			}
			else {
				"Monto valido\n";
				continue;
			}
		} while (monto < 0 && monto > c->getCuentaSoles());

		c->setCuentaSoles(c->getCuentaSoles() - monto);
		cout << "La cantidad de " << monto << " ha sido retirada exitosamente de su cuenta." << endl;
		guardarTransaccion(c, tipo, monto);
	}

	void realizarDespositoCuenta(Cliente* c) {

		string tipo = "Deposito";
		double monto;
		do
		{
			cout << "Ingrese la cantidad a depositar: ";
			cin >> monto;
			if (monto < 0) {
				cout << "No se puede depositar un monto negativo a la cuenta" << endl;
				system("cls");
			}
			else {
				continue;
			}
		} while (monto < 0);
		c->setCuentaSoles(c->getCuentaSoles() + monto);
		cout << "La cantidad de " << monto << " ha sido depositada exitosamente de su cuenta." << endl;
		guardarTransaccion(c, tipo, monto);
	}

	void crearArchivoCliente(Cliente c) {
		string nombre = c.getNombre() + to_string(c.getId()) + ".txt";
		string direccion = "C:/Users/billg/source/repos/EJercicio banco/Clientes";
		ofstream archivo; 
		string nombreArchivo = (direccion + nombre);
		archivo.open(nombreArchivo);
		if (archivo.is_open())
		{
			archivo << c.getNombre() << endl;
			archivo << c.getContrasena() << endl;
			archivo << "0" << endl;
			cout << "Archivo creado exitosamente!" << endl;
			
			/*for (Transaccion* T : c.getTransacciones()) {
				archivo << T->getTipo() << endl;
				archivo << T->getCantidad() << endl;
			}*/
		}
	}

	void guardarArchivoCliente(Cliente c) {
		ofstream archivo;
		string nombre = c.getNombre() + to_string(c.getId());
		string direccion = "C:/Users/billg/source/repos/EJercicio banco/Clientes";
		string nombreArchivo = (+ ".txt");
		archivo.open(nombreArchivo);
		if (archivo.is_open())
		{
			archivo << c.getNombre() << endl;
			archivo << c.getContrasena() << endl;
			archivo << c.getCuentaSoles() << endl;
			cout << "Archivo guardado exitosamente!" << endl;
			archivo.close();
			
		}
	}

	Cliente* cargarArchivoCliente(Cliente c){
		ifstream archivo;
		string s1, s2;
		double s3 = 0.0;
		string nombreArchivo = (c.getNombre() + to_string(c.getId())+".txt");
		archivo.open(nombreArchivo);
		if (archivo.is_open())
		{
			archivo >> s1;
			archivo >> s2;
			archivo >> s3;
			cout << "Archivo leido exitosamente!" << endl;
			archivo.close();
		}
		return new Cliente(s1, s2, s3);
	}
	
	void borrarArchivoCliente(Cliente c) {
		string nombreArchivo = (c.getNombre() + to_string(c.getId()));
		remove(nombreArchivo.c_str());
	}

	void guardarListaClientes() {
		string nombreArchivo = "ListaCliente.txt";
		remove(nombreArchivo.c_str());
		ofstream archivo;

		archivo.open("ListaCliente.txt");
		if (archivo.is_open())
		{
			for (auto& lista : listaClientes)
			{
				archivo << lista->getNombre() << endl;
				archivo << lista->getContrasena() << endl;
				archivo << lista->getCuentaSoles() << endl;
			}
		}
	}
	
	void cargarListaClientes() {
		listaClientes.clear();
		ifstream archivo;
		string s1;
		string s2;
		double s3;

		archivo.open("ListaCliente.txt");
		if (archivo.is_open())
		{
			while (archivo >> s1 >> s2 >> s3) {
				
				listaClientes.push_back(new Cliente(s1, s2, s3));
			}
		}
	}
	
	void guardarTransaccion(Cliente* c, string tipo, double cantidad) {
		string nombre = c->getNombre() + to_string(c->getId()) + "Transacciones.txt";
		string direccion = "C:/Users/billg/source/repos/EJercicio banco/Clientes/Transacciones";
		ofstream archivo;
		string nombreArchivo = (direccion + nombre);
		archivo.open(nombreArchivo, ios::out || ios::app);
		if (archivo.is_open())
		{ 
			for (auto t : c->getTransacciones())
			{
				archivo << t->getCantidad();
				archivo << t->getTipo();
			}
			archivo << tipo << endl;
			archivo << cantidad << endl;
			cout << "Archivo creado exitosamente!" << endl;
		}
	}
	void leerArchivoTransaccion(Cliente* c) {
		ifstream archivo;
		double s1;
		string s2;
		int cont = 1;
		string nombre = c->getNombre() + to_string(c->getId()) + "Transacciones.txt";
		string direccion = "C:/Users/billg/source/repos/EJercicio banco/Clientes/Transacciones";
		ofstream archivo;
		string nombreArchivo = (direccion + nombre);
		archivo.open(nombreArchivo, ios::in);
		if (archivo.is_open())
		{
			while (!archivo.eof())
			{
				archivo >> s1;
				archivo >> s2;
				c->getTransacciones().push_back(new Transaccion(s1, s2));
			}
		}
	}
	void mostrarListaDeClientes() {
		for (auto lista : listaClientes)
		{
			cout << "==============" << "Usuario #" << lista->getId() << "==============" << endl;
			cout << "Nombre: " << lista->getNombre() << endl;
			cout << "Contrasena: " << lista->getContrasena() << endl;
			cout << "Cuenta:" << lista->getCuentaSoles() << endl;
		}
	}
};
