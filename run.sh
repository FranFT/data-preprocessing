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

cmake .. && make