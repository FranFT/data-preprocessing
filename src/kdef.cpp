/*
* Includes
*/
#include <iostream>
#include <opencv2/opencv.hpp>
#include "utilidades.h"
#include "infoBaseDatos.h"

/*
* Namespaces
*/
using namespace std;
using namespace cv;

/***************
 * Functions
 **************/

int main(int argc, char **argv){

  infoBaseDatos* db;
  db = new KDEF();
  Mat aux;
  int cont = 0;
  int total = db->get_num_sessions() * db->get_num_genders() * db->get_num_sujetos() * db->get_num_expresiones() * db->get_num_angles();
  for( unsigned int s = 0; s < db->get_num_sessions(); s++ ){
    for( unsigned int g = 0; g < db->get_num_genders(); g++ ){
      for( unsigned int i = 0; i < db->get_num_sujetos(); i++ ){
        for( unsigned int j = 0; j < db->get_num_expresiones(); j++ ){
          for( unsigned int a = 0; a < db->get_num_angles(); a++ ){
            if( !leeimagen( db->construir_path(i,j,g,s,a), aux, 0 ) )
              cerr << "Error leyendo: " << db->construir_path(i,j,g,s,a) << endl;
            cout << "Leyendo... ";printProgress(cont, total);
            cont++;
          }
        }
      }
    }
  }

  return 0;
}
