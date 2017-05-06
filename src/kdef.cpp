/*
* Includes
*/
#include <iostream>
#include <fstream>
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
  string imgname;
  ofstream trainingListFile, testListFile;
  infoBaseDatos* db;
  Scalar color = Scalar( 255, 255, 0 );
  Rect roi = Rect( Point2f(100,200), Point2f(462,660) );
  db = new KDEF();

  int angle = 2;
  int cont = 0;
  int total = db->get_num_sessions() * db->get_num_genders() * db->get_num_sujetos() * db->get_num_expresiones();
  int testCount = 0;
  int trainingCount = 0;

  // Opening output files.
  trainingListFile.open( "trainingListFile.txt", ios::trunc );
  testListFile.open( "testListFile.txt", ios::trunc );

  if( trainingListFile.is_open() && testListFile.is_open() ){

    vector<bool> ts = generateTrainingSample( total, 0.7 );

    for( unsigned int s = 0; s < db->get_num_sessions(); s++ ){
      for( unsigned int g = 0; g < db->get_num_genders(); g++ ){
        for( unsigned int i = 0; i < db->get_num_sujetos(); i++ ){
          for( unsigned int j = 0; j < db->get_num_expresiones(); j++ ){
            if( leeimagen( db->construir_path( i, j, g, s, angle ), image, 0 ) ){
              // Preprocesamiento.
              resize( image(roi), image, Size( 100, 100 ) );
              if( ts[cont] ){
                imgname = to_string( trainingCount++ ) + ".JPG";
                trainingListFile << imgname << " " << j << endl;
                imwrite( "training/" + imgname, image );
              }
              else{
                imgname = to_string( testCount++ ) + ".JPG";
                testListFile << imgname << " " << j << endl;
                imwrite( "test/" + imgname, image );
              }

              cout << "Procesando... ";
              printProgress(cont++, total);
            }
          }
        }
      }
    }
    trainingListFile.close();
    testListFile.close();
    db->generateSolverFile();
  }

  return 0;
}
