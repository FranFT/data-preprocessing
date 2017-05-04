#! /bin/bash

############################## Variables #######################################
BUILD_DIR=build
TRAINING_DIR=training
TEST_DIR=test

############################### Script #########################################
if [ ! -d "$BUILD_DIR/" ];then
  mkdir $BUILD_DIR
  mkdir $BUILD_DIR/$TRAINING_DIR
  mkdir $BUILD_DIR/$TEST_DIR
fi

cd $BUILD_DIR

cmake .. && make -q
if [ $? -ne 0 ]; then
  make
fi

if [ ! -f "trainingListFile.txt" ]; then
  case `echo $1 | tr '[:upper:]' '[:lower:]'` in
    kdef)
      echo "Preprocesando KDEF"
      ./KDEF
      ;;
    yalefaces)
      echo "Preprocesando Yalefaces"
      ./yalefaces
      ;;
    *)
      echo "Preprocesando KDEF"
      ./KDEF
      ;;
  esac
  exit 0
else
  exit 1
fi
