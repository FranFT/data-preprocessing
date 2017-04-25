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

  // Variables
  Mat image;
  infoBaseDatos* db;
  Scalar color = Scalar( 255, 255, 0 );
  Rect roi = Rect( Point2f(100,200), Point2f(462,660) );
  db = new KDEF();
  int cont = 0;
  int total = db->get_num_sessions() * db->get_num_genders() * db->get_num_sujetos() * db->get_num_expresiones();
  vector<bool> ts = generateTrainingSample( total, 0.7 );

  for( unsigned int s = 0; s < db->get_num_sessions(); s++ ){
    for( unsigned int g = 0; g < db->get_num_genders(); g++ ){
      for( unsigned int i = 0; i < db->get_num_sujetos(); i++ ){
        for( unsigned int j = 0; j < db->get_num_expresiones(); j++ ){
          if( leeimagen( db->construir_path(i,j,g,s,2), image, 0 ) ){
            cout << "Procesando... ";
            printProgress(cont, total);
            cont++;

            // Preprocesamiento.
            resize( image(roi), image, Size( 100, 100 ) );
            pintaI( image, "imagen" );
          }
        }
      }
    }
  }

  return 0;
}
