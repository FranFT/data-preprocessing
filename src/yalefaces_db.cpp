#include "infoBaseDatos.h"

yalefaces::yalefaces():infoBaseDatos(15, 11, "yalefaces"){
	this->db_dir = "../res/yalefaces";
	this->expresiones = { "centerlight", "glasses", "happy", "leftlight",
		"noglasses", "normal", "rightlight", "sad", "sleepy", "surprised", "wink" };
}

String yalefaces::construir_path(
	unsigned int _sujeto,
	unsigned int _expresion,
	unsigned int _gender,
	unsigned int _session,
	unsigned int _angle) const{

	assert( _sujeto+1 <= this->num_sujetos );
	assert( _expresion < this->expresiones.size());

  ostringstream conversor;

  if(_sujeto+1 < 10)
      conversor << this->db_dir << "/subject0" << _sujeto+1 << "." << this->expresiones.at(_expresion) << ".png";
  else
      conversor << this->db_dir << "/subject" << _sujeto+1 << "." << this->expresiones.at(_expresion) << ".png";

  return conversor.str();
}

void yalefaces::generateSolverFile( int _expr ) const{
	// Variables.
	ofstream solver_file;

	// Open file.
	solver_file.open( "solver.prototxt", ios::trunc );

	if( solver_file.is_open() ){
		solver_file
		<< "net: \"buildDataPreprocessing/train_val.prototxt\"" << endl
		<< "test_iter: 10" << endl
		<< "test_interval: 25" << endl
		<< "base_lr: 0.01" << endl
		<< "lr_policy: \"step\"" << endl
		<< "gamma: 0.05" << endl
		<< "stepsize: 50" << endl
		<< "display: 10" << endl
		<< "max_iter: 200" << endl
		<< "momentum: 0.9" << endl
		<< "weight_decay: 0.0005" << endl
		<< "snapshot: 250" << endl
		<< "snapshot_prefix: \"/home/fran/Escritorio/results/yalefaces_train_"<< _expr << "\"" << endl
		//<< "snapshot_prefix: \"data/nets/yalefaces_train_"<< _expr << "\"" << endl
		<< "solver_mode: CPU";

		solver_file.close();
	}
}
