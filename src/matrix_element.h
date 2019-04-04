#ifndef MATRIX_ELEMENT_H
#define MATRIX_ELEMENT_H
#include "file_io.h"
double compute_matrix_element_sigma_tau_plus(char *density_file, int iv);
double compute_matrix_element_tau_plus(char* density_file, int iv);
double compute_matrix_element_M_GT(char *density_file);
double compute_matrix_element_M_F(char *density_file);
double compute_matrix_element_M_F1(char *density_file);
double compute_matrix_element_M_I2(char *density_file);
double compute_matrix_element_M_I1(char *density_file);
double compute_matrix_element_M_JF(char *density_file);
double compute_matrix_element_TT(char * density_file, int iv);
double cme_1_sigma();
#endif
