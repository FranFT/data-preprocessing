#include "infoBaseDatos.h"

KDEF::KDEF():infoBaseDatos( 35, 7, "KDEF" ){
  // neutral, happy, angry, afraid, disgusted, sad, surprised.
  this->db_dir = "../res/KDEF";
  this->expresiones = { "NE","HA","AN","AF","DI","SA","SU" };
  this->gender = { "F", "M" };
  this->session = { "A", "B" };
  this->angle = { "FL", "HL", "S", "HR", "FR" };
}

String KDEF::construir_path(
  unsigned int _sujeto,
  unsigned int _expresion,
  unsigned int _gender,
  unsigned int _session,
  unsigned int _angle) const{
  // Checking parameters.
  assert( _sujeto+1 <= this->num_sujetos );
  assert( _expresion < this->expresiones.size() );
  assert( _gender < this->gender.size() );
  assert( _session < this->session.size() );
  assert( _angle < this->angle.size() );

  // Variables.
  ostringstream conversor;
  String folder, imagen;

  // Getting the folder.
  conversor << this->session[_session] << this->gender[_gender];
  if( _sujeto + 1 < 10 ) conversor << "0";
  conversor << _sujeto + 1;
  folder = conversor.str();
  conversor.str("");
  conversor.clear();

  // Getting the image.
  conversor << folder << this->expresiones[_expresion] << this->angle[_angle] << ".JPG";
  imagen = conversor.str();

  return this->db_dir + "/" + folder + "/" + imagen;
}

void KDEF::generateSolverFile( int _expr ) const{
  // Variables.
  ofstream solver_file;

  // Open file.
  solver_file.open( "solver.prototxt", ios::trunc );

  if( solver_file.is_open() ){
    solver_file
    << "net: \"data/nets/kdef_all.prototxt\"" << endl
    << "test_iter: 5" << endl
    << "test_interval: 500" << endl
    << "base_lr: 0.1" << endl
    << "lr_policy: \"step\"" << endl
    << "gamma: 0.1" << endl
    << "stepsize: 1000" << endl
    << "display: 500" << endl
    << "max_iter: 3000" << endl
    << "momentum: 0.9" << endl
    << "snapshot: 1000" << endl
    << "snapshot_prefix: \"/home/fran/Escritorio/results/kdef/kdef_train\"" << endl
    //<< "snapshot_prefix: \"/home/fran/Escritorio/results/kdef_train_"<< _expr << "\"" << endl
    //<< "snapshot_prefix: \"data/nets/yalefaces_train_"<< _expr << "\"" << endl
    << "solver_mode: CPU";

    solver_file.close();
  }
}
