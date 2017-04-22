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
  infoBaseDatos* db1;
  db = new KDEF();

  for( unsigned int s = 0; s < db->get_num_sessions(); s++ )
    for( unsigned int g = 0; g < db->get_num_genders(); g++ )
      for( unsigned int i = 0; i < db->get_num_sujetos(); i++ )
        for( unsigned int j = 0; j < db->get_num_expresiones(); j++ )
          for( unsigned int a = 0; a < db->get_num_angles(); a++ )
            cout << db->construir_path(i,j,g,s,a) << endl;

  return 0;
}
