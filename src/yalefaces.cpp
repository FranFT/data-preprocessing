/*
* Includes
*/
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "utilidades.h"
#include "infoBaseDatos.h"
#include "subject.h"

/*
* Namespaces
*/
using namespace std;
using namespace cv;

/***************
 * Functions
 **************/

int main(int argc, char **argv){
  /*
   Variables
   */
  int choosen_expr = 0;
  infoBaseDatos* data_base;
  data_base = new yalefaces();

  Mat temp_image;
  vector< bool > is_training;
  vector<vector< Subject > > subjects;
  ofstream training_output_file, test_output_file;
  String training_path, test_path, training_output_file_name, test_output_file_name;
  ostringstream image_name, file_name;
  int combinedImagesToBeGenerated;

  /*
  Checking input parameters.
   */
  if( argc == 1 ){ // No parameters.
    choosen_expr = -1;
    file_name << "testListFile_all.txt";
  }
  else if( argc == 2 ){ // Expression was given.
    bool found = false;
    // Checking if the expression is correct.
    for( int i = 0; i < data_base->get_num_expresiones(); i++ )
      if( argv[1] == data_base->get_expresion( i ) ){
        found = true;
        choosen_expr = i;
      }

    if( !found ){
      cerr << "Error: Debes introducir una expresión válida." << endl;
      return 1;
    }
    else{
      file_name << "testListFile_" << argv[1] << ".txt";
    }
  }
  else{ // More than one parameter
    cerr << "Error: El número de parámetros debe ser 1 o ninguno." << endl;
    return 1;
  }


  /*
  Main code
   */
  // Data inicialitation
  srand(time(NULL));
  training_path = "data/training/";
  test_path = "data/test/";
  is_training = getTrainingSample( data_base );
  training_output_file_name = "trainingListFile.txt";
  test_output_file_name = file_name.str();
  combinedImagesToBeGenerated = 5;

  // Allocating memmory
  subjects = vector<vector< Subject > >( data_base->get_num_sujetos() );


  // Reading images
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++)
    for( unsigned int j = 0; j < data_base->get_num_expresiones(); j++)
      if( leeimagen( data_base->construir_path( i, j ), temp_image ) )
        subjects.at( i ).push_back( Subject( temp_image, j ));
      else{
        cerr << "Error intentado leer la imagen: '"
        << data_base->construir_path( i, j ) << endl;
        return 1;
      }

  // Applying random transformations to each training image.
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++){
    if( is_training.at( i ) ){
      for( unsigned int j = 0; j < data_base->get_num_expresiones(); j++){
        //
        // Do some transformations ( Data augmetation process )
        //
        subjects.at( i ).push_back( Subject( horizontalFlip( subjects[i][j].getImage()), j ) );
        subjects.at( i ).push_back( Subject( randomZoom( subjects[i][j].getImage()), j ) );
        subjects.at( i ).push_back( Subject( randomRotate( subjects[i][j].getImage()), j ) );
        subjects.at( i ).push_back( Subject( randomNoise( subjects[i][j].getImage()), j ) );

        //
        // Combined transformations.
        //
        Mat combinedTransImage;
        for( unsigned int k = 0; k < rand() % combinedImagesToBeGenerated; k++ )
            if( combinedTrans( subjects[i][j].getImage(), combinedTransImage ) )
              subjects.at( i ).push_back( Subject( combinedTransImage, j ) );
      }// for
    }// if
  }// for

  // Compensating test sample in the binary classification case.
  if( choosen_expr != -1 ){
    cout << "Compensando..." << endl;
    int positiveTestImgs = 0;
    int negativeTestImgs = 0;
    vector<int> testSubjects;

    for( unsigned int i = 0; i < subjects.size(); i++ )
      if( !is_training.at( i ) ){
        testSubjects.push_back( i );
        for( unsigned int j = 0; j < subjects.at( i ).size(); j++)
          if( subjects[i][j].getLabel() == choosen_expr )
            positiveTestImgs++;
          else
            negativeTestImgs++;
      }// if

    int newImgsPerSubject = ( negativeTestImgs - positiveTestImgs ) /  testSubjects.size();

    for( unsigned int i = 0; i < testSubjects.size(); i++ ){
      int imagesGenerated = 0;
      while( imagesGenerated < newImgsPerSubject ){
        Mat combinedTransImage;
        if( combinedTrans( subjects[testSubjects.at(i)][choosen_expr].getImage(), combinedTransImage ) ){
          subjects.at( testSubjects.at( i ) ).push_back( Subject( combinedTransImage, choosen_expr ) );
          imagesGenerated++;
        }// if
      }// while
    }// for
  }// if

  // Getting 0 mean 1 variance.
  /*for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++ )
    if( is_training.at( i ) )
      for( unsigned int j = 0; j < subjects[i].size(); j++ )
        subjects[i][j].insertImage( normalizeImage( subjects[i][j].getImage() ) );*/

  // Writing images and listfile.
  training_output_file.open( training_output_file_name.c_str(), ios::trunc );
  test_output_file.open( test_output_file_name.c_str(), ios::trunc );
  if( training_output_file.is_open() && test_output_file.is_open() ){
    for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++ ){
      for( unsigned int j = 0; j < subjects[i].size(); j++ ){
        image_name << "subject" << i << "-" << j << "-" << data_base->get_expresion(subjects[i][j].getLabel()) << ".png";
        if( is_training[i] ){
          imwrite( training_path + image_name.str(), subjects[i][j].getImage());
          training_output_file << "training/" << image_name.str() << " ";
          if( choosen_expr == -1 )
            training_output_file << subjects[i][j].getLabel() << endl;
          else
            ( subjects[i][j].getLabel() == choosen_expr ) ? training_output_file << 1 << endl : training_output_file << 0 << endl;
        }
        else{
          imwrite( test_path + image_name.str(), subjects[i][j].getImage());
          test_output_file << "test/" << image_name.str() << " ";
          if( choosen_expr == -1 )
            test_output_file << subjects[i][j].getLabel() << endl;
          else
            ( subjects[i][j].getLabel() == choosen_expr ) ? test_output_file << 1 << endl : test_output_file << 0 << endl;
        }
        image_name.str("");
      }
    }
    training_output_file.close();
    test_output_file.close();

    // Generates label file.
    if( !generateLabelsFile(data_base, choosen_expr)){
      cerr << "ERROR: No se pudo generar el archivo LabelsFile" << endl;
      return 1;
    }
  }
  else{
    cerr << "ERROR: No se pudo escribir el archivo ListFile" << endl;
    return 1;
  }
   return 0;
}
