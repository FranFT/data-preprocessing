#ifndef __INFOBASEDATOS_H__
#define __INFOBASEDATOS_H__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <cassert>
using namespace std;
using namespace cv;

/***************************************************************************************************
*	Clase base abstracta.																		   *
***************************************************************************************************/
class infoBaseDatos{
protected:
	/**
	*	Datos miembro.
	**/
	const char* nombre;
	int num_sujetos;
	int num_expresiones;
	float training_sample_size;
	vector<String> expresiones;

	/**
	* Métodos privados.
	**/
	void insertar_expresion(String _expresion);

public:
	/**
	*	Métodos definidos.
	**/
	// Constructor.
	infoBaseDatos( int _ns, int _ne, const char* _nombre, float _training_sample_size = 0.7 );

	// Muestra información de la base de datos concreta.
	void imprime_info() const;

	/**
	*	Getters
	**/
	int get_num_sujetos() const;
	int get_num_expresiones() const;
	float get_training_sample_size() const;
	String get_expresion(int _indice) const;

	/**
	*	Métodos abstractos.
	**/
	virtual String construir_path(
		unsigned int _sujeto,
		unsigned int _expresion,
		unsigned int _gender = 0,
		unsigned int _session = 0,
		unsigned int _angle = 0 ) const = 0;
};

/***************************************************************************************************
*	Clases derivadas.																			   *
***************************************************************************************************/
// Base de datos "yalefaces"
class yalefaces: public infoBaseDatos{
private:
	const String db_dir = "../res/yalefaces";
public:
	yalefaces();

	String construir_path(
		unsigned int _sujeto,
		unsigned int _expresion,
		unsigned int _gender = 0,
		unsigned int _session = 0,
		unsigned int _angle = 0 ) const;
};


// Base de datos "KDEF"
class KDEF: public infoBaseDatos{
private:
	const String db_dir = "../res/KDEF";
	const String gender [2] = { "F", "M" };
	const String session [2] = { "A", "B" };
	const String angle [5] = { "FL", "HL", "S", "HR", "FR" };

public:
	KDEF();

	String construir_path(
		unsigned int _sujeto,
		unsigned int _expresion,
		unsigned int _gender,
		unsigned int _session,
		unsigned int _angle) const;
};

#endif //__INFOBASEDATOS_H__
