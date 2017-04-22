#include "infoBaseDatos.h"

infoBaseDatos::infoBaseDatos(int _ns, int _ne, const char* _nombre, float _training_sample_size){
	this->nombre = _nombre;
	this->num_sujetos = _ns;
	this->num_expresiones = _ne;
	this->training_sample_size = _training_sample_size;
}

void infoBaseDatos::imprime_info() const {
	cout << "-Nombre de la base de datos: " << this->nombre << endl;
	cout << "--Num. de sujetos: " << this->num_sujetos << endl;
	cout << "--Num. de expresiones: " << this->num_expresiones << endl;
	cout << "--Training: " << this->training_sample_size * 100 << "%" << endl;
	cout << "--Test: " << 100 - ( this->training_sample_size * 100 ) << "%" << endl;
	cout << "--Expresiones registradas: ";
	for(vector<String>::const_iterator it = this->expresiones.begin(); it!=this->expresiones.end(); ++it)
		(it+1==this->expresiones.end()) ? cout << (*it) << endl : cout << (*it) << ", ";
}

int infoBaseDatos::get_num_sujetos() const{
	return this->num_sujetos;
}

int infoBaseDatos::get_num_expresiones() const{
	return this->num_expresiones;
}

int infoBaseDatos::get_num_genders() const{
  return this->gender.size();
}

int infoBaseDatos::get_num_angles() const{
  return this->angle.size();
}
int infoBaseDatos::get_num_sessions() const{
  return this->session.size();
}

float infoBaseDatos::get_training_sample_size() const{
	return this->training_sample_size;
}

String infoBaseDatos::get_expresion(int _indice) const{
	return this->expresiones.at(_indice);
}
