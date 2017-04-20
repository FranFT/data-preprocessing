#ifndef __UTILIDADES__
#define __UTILIDADES__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "infoBaseDatos.h"

using namespace std;
using namespace cv;

/**
*	@fn bool leeimagen(char* _filename, Mat& _imagen, unsigned int _flagColor = 0)
*	@brief Lee una imagen.
*	@param[in] _filename Path necesario para leer la imagen.
*	@param[in] _flagColor Si es 0 la almacena en escala de grises (1 canal).
*						 Si es 1 la almacena en color (3 canales).
*	@param[out] _imagen Objeto que contiene la imagen leida.
*	@returns Si se ha podido leer o no la imagen.
*/
bool leeimagen(char* _filename, Mat& _imagen, unsigned int _flagColor = 0);

/**
*	@fn bool leeimagen(String _filename, Mat& _imagen, unsigned int _flagColor = 0)
*	@brief Lee una imagen.
*	@param[in] _filename Path necesario para leer la imagen.
*	@param[in] _flagColor Si es 0 la almacena en escala de grises (1 canal).
*						 Si es 1 la almacena en color (3 canales).
*	@param[out] _imagen Objeto que contiene la imagen leida.
*	@returns Si se ha podido leer o no la imagen.
*/
bool leeimagen(String _filename, Mat& _imagen, unsigned int _flagColor = 0);

/**
*	@fn pintaI(const Mat& im, char* nombre_ventana = "imagen")
*	@brief Muestra una imagen por pantalla.
*	@param[in] im Objeto Mat que se desea mostrar.
*	@param[in] nombre_ventana Nombre que tendrá la ventana donde se muestra la imagen.
*	@details Internamente la imagen se convertirá a un formato que pueda ser representado por un monitor.
*/
void pintaI(const Mat& _imagen, const char* _nombre_ventana);

/**
*   @fn marcar_punto(Mat &img, Point2f pt, Scalar& color, int tam_pixel)
*/
void marcar_punto(Mat &img, Point2f pt, Scalar& color, int tam_pixel);

/**
*	@fn version_OpenCV()
*	@brief Muestra por pantalla la versión de OpenCV que se tiene instalada.
*/
void version_OpenCV();

/**
*	@fn getTrainingSample( const infoBaseDatos* _data_base )
*	@brief This method calculates which sample element is in the training sample.
*  @returns Vector indicating which element belongs to training (1) or not (0)
*/
vector<bool> getTrainingSample( const infoBaseDatos* _data_base );

/**
 * Returns the mirror image.
 * @param _image Image to be flipped.
 */
Mat horizontalFlip(const Mat& _image);

/**
 * Makes a random zoom-in within a range.
 * @param  _image    Image to be zoomed.
 * @param  min_range Minimun percentage of the picture to be zoomed in.
 * @param  max_range Maximun percentage of the picture to be zoomed in.
 * @return           Zoomed in image.
 */
Mat randomZoom( const Mat& _image, int min_range = 10, int max_range = 30 );

/**
 * Makes a random rotation within a range.
 * @param  _image    Image to be rotated.
 * @param  min_range Minimun angle of the picture to be rotated.
 * @param  max_range Maximun angle of the picture to be rotated.
 * @return           rotated in image.
 */
Mat randomRotate( const Mat& _image, int min_range = 5, int max_range = 40 );

/**
 * It normalizes a image to reach 0 mean 1 variance. It is achieved by subtracting
 * the image pixels mean and then dividing by image standard deviation.
 * @param  _image image to be normalized.
 * @return        Normalized image.
 */
Mat normalizeImage( const Mat& _image );

/**
 * Adds Gaussian Noise to a given image.
 * @param  _image Image which will receive noise.
 * @return        50% prob to return the given image with brigher or darker noise.
 */
Mat randomNoise( const Mat& _image );

/**
 * Apply a random combination of the transformations already implemented to the
 * same image.
 * @param  _image     Image to be transformed.
 * @param  output_mat Transformed output image.
 * @param  nt         Number of different transformations that can be applied.
 * @return            True if some transformation was applied. False otherwise.
 */
bool combinedTrans( const Mat& _image, Mat& output_mat, int nt = 4 );

#endif
