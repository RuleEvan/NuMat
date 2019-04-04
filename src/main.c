#include "data_gen.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {printf("Please supply only the parameter file name to the command line\n"); exit(0);}
  nuMatParams* nmp = read_parameter_file(argv[1]);
  printf("I1: %lf\n", compute_matrix_element_M_I1(nmp->density_file));  
  printf("MF1: %lf\n", compute_matrix_element_M_F1(nmp->density_file));  
  printf("I2: %lf\n", compute_matrix_element_M_I2(nmp->density_file));
  printf("M_JF: %g\n", compute_matrix_element_M_JF(nmp->density_file));
  printf("M_F: %g\n", compute_matrix_element_M_F(nmp->density_file));
  printf("M_GT: %g\n", compute_matrix_element_M_GT(nmp->density_file));
  printf("M_F: %g\n", compute_matrix_element_tau_plus(nmp->density_file, 5));
  printf("M_AA_GT: %g\n", compute_matrix_element_sigma_tau_plus(nmp->density_file, 6));
//  printf("M_AA_T: %g\n", compute_matrix_element_TT(7));
  printf("M_AP_GT: %g\n", compute_matrix_element_sigma_tau_plus(nmp->density_file, 8));
  printf("M_PP_GT: %g\n", compute_matrix_element_sigma_tau_plus(nmp->density_file, 10));
  printf("M_MM_GT: %g\n", compute_matrix_element_sigma_tau_plus(nmp->density_file, 12));
  printf("M_AP_T: %g\n", compute_matrix_element_TT(nmp->density_file, 9));
  printf("M_PP_T: %g\n", compute_matrix_element_TT(nmp->density_file, 11));
  printf("M_MM_T: %g\n", compute_matrix_element_TT(nmp->density_file, 13));
  printf("M_F_sd: %g\n", compute_matrix_element_tau_plus(nmp->density_file, 14));
  printf("M_AA_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(nmp->density_file, 15));
//  printf("M_AA_T_sd: %g\n", compute_matrix_element_TT(16));
  printf("M_AP_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(nmp->density_file, 17));
  printf("M_PP_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(nmp->density_file, 19));
  printf("M_AP_T_sd: %g\n", compute_matrix_element_TT(nmp->density_file, 18));
  printf("M_PP_T_sd: %g\n", compute_matrix_element_TT(nmp->density_file, 20));

  return 0;
}
