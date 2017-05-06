#ifndef __INFOBASEDATOS_H__
#define __INFOBASEDATOS_H__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
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
	String db_dir;
	vector<String> expresiones;
	vector<String> gender;
	vector<String> session;
	vector<String> angle;

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
	int get_num_genders() const;
	int get_num_angles() const;
	int get_num_sessions() const;
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

	virtual void generateSolverFile( int _expr = -1 ) const = 0;
};

/***************************************************************************************************
*	Clases derivadas.																			   *
***************************************************************************************************/
// Base de datos "yalefaces"
class yalefaces: public infoBaseDatos{
public:
	yalefaces();

	String construir_path(
		unsigned int _sujeto,
		unsigned int _expresion,
		unsigned int _gender = 0,
		unsigned int _session = 0,
		unsigned int _angle = 0 ) const;

	void generateSolverFile( int _expr = -1 ) const;
};


// Base de datos "KDEF"
class KDEF: public infoBaseDatos{
public:
	KDEF();

	String construir_path(
		unsigned int _sujeto,
		unsigned int _expresion,
		unsigned int _gender,
		unsigned int _session,
		unsigned int _angle) const;

		void generateSolverFile( int _expr = -1 ) const;
};

#endif //__INFOBASEDATOS_H__
