#include <iostream>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "infoBaseDatos.h"
#include "utilidades.h"

using namespace std;
using namespace cv;

int main(){
  /*
   Variables
   */
   Mat temp_image;
   //ofstream output_file;
   ostringstream output_path;
   infoBaseDatos* data_base;
   data_base = new yalefaces();

   //output_file.open("~/DIGITS/datasets/yalefaces/");

  // Reading images
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++)
    for( unsigned int j = 0; j < data_base->get_num_expresiones(); j++)
      if( leeimagen( data_base->construir_path( i, j ), temp_image ) ){
        output_path << "temp/" << data_base->get_expresion( j ) << "/" << i << ".png";
        imwrite( output_path.str(), temp_image );
        output_path.str("");
      }
      else{
        cerr << "Error intentado leer la imagen: '"
        << data_base->construir_path( i, j ) << endl;
        return 1;
      }

    return 0;
}
