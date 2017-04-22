#include "infoBaseDatos.h"

KDEF::KDEF():infoBaseDatos( 35, 7, "KDEF" ){
  insertar_expresion("NE"); // neutral
  insertar_expresion("HA"); // happy
  insertar_expresion("AN"); // angry
  insertar_expresion("AF"); // afraid
  insertar_expresion("DI"); // disgusted
  insertar_expresion("SA"); // sad
  insertar_expresion("SU"); // surprised
}

String KDEF::construir_path(
  unsigned int _sujeto,
  unsigned int _expresion,
  unsigned int _gender,
  unsigned int _session,
  unsigned int _angle) const{
  // Checking parameters.
  assert( _sujeto+1 <= this->num_sujetos );
  assert( _expresion < this->expresiones.size() );
  assert( _gender < 2 );
  assert( _session < 2 );
  assert( _angle < 5 );

  // Variables.
  ostringstream conversor;
  String folder, imagen;

  // Getting the folder.
  conversor << this->session[_session] << this->gender[_gender];
  if( _sujeto + 1 < 10 ) conversor << "0";
  conversor << _sujeto + 1;
  folder = conversor.str();
  conversor.str("");
  conversor.clear();

  // Getting the image.
  conversor << folder << this->expresiones[_expresion] << this->angle[_angle] << ".JPG";
  imagen = conversor.str();
  
  return this->db_dir + "/" + folder + "/" + imagen;
}
