#include "infoBaseDatos.h"

KDEF::KDEF():infoBaseDatos( 70, 7, "KDEF" ){
  insertar_expresion("neutral");
  insertar_expresion("happy");
  insertar_expresion("angry");
  insertar_expresion("afraid");
  insertar_expresion("disgusted");
  insertar_expresion("sad");
  insertar_expresion("surprised");
}

String KDEF::construir_path(int _sujeto, int _expresion, int _gender, int _session) const{
  assert(_sujeto+1 > 0 && _sujeto+1 <= this->num_sujetos );
  assert(_expresion >= 0 && _expresion < this->expresiones.size());

  ostringstream conversor;
  // Under construction
  return conversor.str();
}
