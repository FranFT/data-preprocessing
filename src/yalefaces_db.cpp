#include "infoBaseDatos.h"

yalefaces::yalefaces():infoBaseDatos(15, 11, "yalefaces"){
	this->db_dir = "../res/yalefaces";
	this->expresiones = { "centerlight", "glasses", "happy", "leftlight",
		"noglasses", "normal", "rightlight", "sad", "sleepy", "surprised", "wink" };
}

String yalefaces::construir_path(
	unsigned int _sujeto,
	unsigned int _expresion,
	unsigned int _gender,
	unsigned int _session,
	unsigned int _angle) const{

	assert( _sujeto+1 <= this->num_sujetos );
	assert( _expresion < this->expresiones.size());

  ostringstream conversor;

  if(_sujeto+1 < 10)
      conversor << this->db_dir << "/subject0" << _sujeto+1 << "." << this->expresiones.at(_expresion) << ".png";
  else
      conversor << this->db_dir << "/subject" << _sujeto+1 << "." << this->expresiones.at(_expresion) << ".png";

  return conversor.str();
}
