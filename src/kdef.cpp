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

  for( unsigned int s = 0; s < 2; s++)
    for( unsigned int g = 0; g < 2; g++)
      for( unsigned int i = 0; i < db->get_num_sujetos(); i++)
        cout << db->construir_path(i,0,g,s) << endl;

  return 0;
}
