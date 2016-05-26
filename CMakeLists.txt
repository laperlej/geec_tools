CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

SET( PROJ_NAME "GeFF" )
SET( EXECUTABLE_OUTPUT_PATH "../../bin" )
SET( LIBRARY_OUTPUT_PATH "../../libs" )
SET( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ../libs )

PROJECT( ${PROJ_NAME} )

ADD_SUBDIRECTORY( "bwreader" "bwreader" )
ADD_SUBDIRECTORY( "utils" "utils" )
ADD_SUBDIRECTORY( "to_hdf5" "to_hdf5" )
ADD_SUBDIRECTORY( "to_zscore" "to_zscore" )
ADD_SUBDIRECTORY( "correlation" "correlation" )
ADD_SUBDIRECTORY( "correlation_nm" "correlation_nm" )
