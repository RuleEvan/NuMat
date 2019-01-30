#include "data_gen.h"

int main(int argc, char *argv[]) {
//  printf("M_F: %g\n", compute_matrix_element_M_F());
//  printf("M_GT: %g\n", compute_matrix_element_M_GT());
  printf("M_F: %g\n", compute_matrix_element_tau_plus(5));
  printf("M_AA_GT: %g\n", compute_matrix_element_sigma_tau_plus(6));
//  printf("M_AA_T: %g\n", compute_matrix_element_TT(7));
  printf("M_AP_GT: %g\n", compute_matrix_element_sigma_tau_plus(8));
  printf("M_PP_GT: %g\n", compute_matrix_element_sigma_tau_plus(10));
  printf("M_MM_GT: %g\n", compute_matrix_element_sigma_tau_plus(12));
  printf("M_AP_T: %g\n", compute_matrix_element_TT(9));
  printf("M_PP_T: %g\n", compute_matrix_element_TT(11));
  printf("M_MM_T: %g\n", compute_matrix_element_TT(13));
  printf("M_F_sd: %g\n", compute_matrix_element_tau_plus(14));
  printf("M_AA_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(15));
//  printf("M_AA_T_sd: %g\n", compute_matrix_element_TT(16));
  printf("M_AP_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(17));
  printf("M_PP_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(19));
  printf("M_AP_T_sd: %g\n", compute_matrix_element_TT(18));
  printf("M_PP_T_sd: %g\n", compute_matrix_element_TT(20));

  return 0;
}
