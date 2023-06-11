
APP_DIR = ..
APP_BIN = ${APP_DIR}/bin
APP_LIB = ${APP_DIR}/lib
APP_INCL_DIR = ${APP_DIR}/include

CFLAGS = -g -I. -I${APP_INCL_DIR} -Wall 
		
LDLIBS = -L${APP_LIB} -lpse -lm -pthread

CC = gcc
