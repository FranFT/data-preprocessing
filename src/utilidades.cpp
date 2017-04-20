#include "utilidades.h"

/******************************************************************************/
bool leeimagen(char* _filename, Mat& _imagen, unsigned int _flagColor){
	_imagen = imread(_filename, _flagColor);

	if(!_imagen.data)
		return false;
	else
		return true;
}// leeimagen ends.


/******************************************************************************/
bool leeimagen(String _filename, Mat& _imagen, unsigned int _flagColor){
	_imagen = imread(_filename, _flagColor);

	if(!_imagen.data)
		return false;
	else
		return true;
}// leeimagen ends.


/******************************************************************************/
void pintaI(const Mat& _imagen, const char* _nombre_ventana){
	if(!_imagen.empty()){
		namedWindow(_nombre_ventana, WINDOW_AUTOSIZE);

		if(_imagen.type() != CV_8U){
			Mat imagen_copia = Mat(_imagen);
			imagen_copia.convertTo(imagen_copia, CV_8U);
			imshow(_nombre_ventana, imagen_copia);
		}
		else{
			imshow(_nombre_ventana, _imagen);
		}

		waitKey(0);
		destroyWindow(_nombre_ventana);
	}
	else{
		cerr << "ERROR: No se puede mostrar una imagen vacia." << endl;
	}
}// pintaI ends.


/******************************************************************************/
void marcar_punto(Mat &img, Point2f pt, Scalar& color, int tam_pixel){
	// Se comprueba que el punto tiene valores correctos.
	if (pt.x >= 0 && pt.y >= 0){
		// Dibuja la cruz en el punto pt.
		line(img, pt - Point2f(0, tam_pixel), pt + Point2f(0, tam_pixel), color);
		line(img, pt - Point2f(tam_pixel, 0), pt + Point2f(tam_pixel, 0), color);
		/*line(img, pt - Point2f(0, tam_pixel), pt + Point2f(0, tam_pixel), color);
		line(img, pt - Point2f(tam_pixel, 0), pt + Point2f(tam_pixel, 0), color);*/
	}
}// marcar_punto ends.


/******************************************************************************/
void version_OpenCV(){
	cout << "OpenCV version : " << CV_VERSION << endl;
	cout << "Major version : " << CV_MAJOR_VERSION << endl;
 	cout << "Minor version : " << CV_MINOR_VERSION << endl;
	cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;
}// version_OpenCV ends.


/******************************************************************************/
vector<bool> getTrainingSample( const infoBaseDatos* _data_base ){
	// Variables
	vector<int> indexes;
	vector<bool> output_vector;

	// Method code
	for( unsigned int i = 0; i < _data_base->get_num_sujetos(); i++ )
		indexes.push_back( i );
	random_shuffle( indexes.begin(), indexes.end() );

	output_vector = vector<bool>( indexes.size(), false );
	for( unsigned int i = 0; i < ceil( indexes.size() * _data_base->get_training_sample_size() ); i++ )
		output_vector.at( indexes.at( i ) ) = true;

	return output_vector;
}// getTrainingSample ends.


/******************************************************************************/
Mat horizontalFlip(const Mat& _image){
	Mat flipped_image;
	flip( _image, flipped_image, 1 );
	return flipped_image;
}// horizontalFlip ends.


/******************************************************************************/
Mat randomZoom(const Mat& _image, int min_range, int max_range){
 // Variables //
 int x, y;
 float zoom_range;
 Mat zoomed_image;
 Rect zoomed_area;

 // Code //
 // Defining a random zoom within a [min,max] range.
 zoom_range = ( rand() % (max_range - min_range + 1) ) + min_range;
 zoom_range /= 100;

 // Defining the initial rect point.
 x = _image.cols * zoom_range;
 y = _image.rows * zoom_range;
 zoomed_area = Rect( x, y, _image.cols - x, _image.rows - y );

 // Zooming in while resizing the result image.
 resize( _image( zoomed_area ), zoomed_image, _image.size() );

 return zoomed_image;
}// randomZoom ends.


/******************************************************************************/
Mat randomRotate(const Mat& _image, int min_range, int max_range){
  // Variables //
  int aux;
  Point2f center_point;
  float rotation_angle;
  Mat rot_matrix;
  Mat rotated_image;

  // Code //
  // Calculating image center point.
  center_point = Point2f( _image.cols/2.0F, _image.rows/2.0F);
  // Getting the random rotation angle.
  aux = rand();
  rotation_angle = ( aux % (max_range - min_range + 1) ) + min_range;

  if( aux % 2 == 0 )
    rotation_angle *= -1;
  // Getting the rotation matrix and applying it.
  rot_matrix = getRotationMatrix2D( center_point, rotation_angle, 1.0 );
  warpAffine( _image, rotated_image, rot_matrix, _image.size(),
  CV_INTER_CUBIC,  BORDER_REFLECT);

  return rotated_image;
}// randomRotate ends.


/******************************************************************************/
Mat normalizeImage( const Mat& _image ){
  // Variables
  Mat _mean, _stddev, _temp;

  // Code //
  // Working on a temp variable. Changing its precision for better accuracy
  _temp = _image.clone();
  _temp.convertTo( _temp, CV_64F );

  // Calculating mean and standard deviation.
  meanStdDev( _temp, _mean, _stddev );

  // Returning the normalized image.
  return (_temp - _mean) / _stddev;
}// normalizeImage ends.


/******************************************************************************/
Mat randomNoise( const Mat& _image ){
  // Variables.
  Mat gaussianNoise;

  // Code //
  gaussianNoise = _image.clone();
  // Getting the mask.
  randn(gaussianNoise ,50,20);

  if( rand() % 2 == 0)
    return _image - gaussianNoise; // Darker noise.
  else
    return _image + gaussianNoise; // Brighter noise.
}// randomNoise ends.


/******************************************************************************/
bool combinedTrans( const Mat& _image, Mat& output_mat, int nt ){
  // Variables //
  int trans_to_be_applied;
  bool trasn_was_applied;

  // Code //
  output_mat = _image.clone();
  trasn_was_applied = false;

  // Applying 'num_trans' transformations with a 50% prob.
  for( unsigned int i = 0; i < nt; i++ ){
    trans_to_be_applied = rand() % nt;
    if( rand() % 2 == 0 ){
      trasn_was_applied = true;
      switch ( trans_to_be_applied ) {
        case 0:
          output_mat = horizontalFlip( output_mat );
        break;

        case 1:
          output_mat = randomZoom( output_mat );
        break;

        case 2:
          output_mat = randomRotate( output_mat );
        break;

        case 3:
          output_mat = randomNoise( output_mat );
        break;

        default:
          cerr << "No hay definida una transfomación para el valor: " << trans_to_be_applied << endl;
        break;
      }
    }
  }

  return trasn_was_applied;
}// combinedTrans ends.


/******************************************************************************/
bool generateLabelsFile( const infoBaseDatos* _data_base, int expr ){
  /*
  Variables
   */
  ofstream labels_file;
  String labels_file_name = "labels.txt";

  /*
  Code
   */
  labels_file.open( labels_file_name.c_str(), ios::trunc );
  if( labels_file.is_open() ){
    if( expr == -1 ){
      for( unsigned int i = 0; i < _data_base->get_num_expresiones(); i++ )
        labels_file << i << " " << _data_base->get_expresion( i ) << endl;
    }
    else{
      labels_file << 0 << " Not " << _data_base->get_expresion( expr ) << endl;
      labels_file << 1 << " " << _data_base->get_expresion( expr ) << endl;
    }
    labels_file.close();
    return true;
  }
  else{
    return false;
  }
}// generateLabelsFile ends.
