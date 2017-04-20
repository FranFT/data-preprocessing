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
