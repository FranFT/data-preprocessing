#include <iostream>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "infoBaseDatos.h"
#include "utilidades.h"

using namespace std;
using namespace cv;

String transformName( const int _expr ){
  String output;
  switch ( _expr ) {
    case 0:
      output = "neutral";
      break;
    case 1:
      output = "happy";
      break;
    case 2:
      output = "angry";
      break;
    case 3:
      output = "afraid";
      break;
    case 4:
      output = "disgusted";
      break;
    case 5:
      output = "sad";
      break;
    case 6:
      output = "surprised";
      break;
  }
  return output;
}

int main(){
  /*
   Variables
   */
   Mat temp_image;
   ostringstream output_path;
   infoBaseDatos* db;
   db = new KDEF();
   int angle = 2; // Only front angle faces.
   Rect roi = Rect( Point2f(100,200), Point2f(462,660) );

   for( unsigned int s = 0; s < db->get_num_sessions(); s++ ){
     for( unsigned int g = 0; g < db->get_num_genders(); g++ ){
       for( unsigned int i = 0; i < db->get_num_sujetos(); i++ ){
         for( unsigned int j = 0; j < db->get_num_expresiones(); j++ ){
           if( leeimagen( db->construir_path( i, j, g, s, angle ), temp_image, 0 ) ){
             output_path << "temp/" << transformName( j ) << "/" << i << ".JPG";
             resize( temp_image(roi), temp_image, Size( 100, 100 ) );
             imwrite( output_path.str(), temp_image );
             output_path.str("");
           }
           else{
             cerr << "Error intentado leer la imagen: '"
             << db->construir_path( i, j, g, s, angle ) << endl;
             return 1;
           }
         }
       }
     }
   }
    return 0;
}
