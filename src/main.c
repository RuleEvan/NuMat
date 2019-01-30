#include "data_gen.h"

int main(int argc, char *argv[]) {
  printf("%g\n", compute_matrix_element_M_F());
  printf("MGT: %g\n", compute_matrix_element_M_GT());
  printf("M1: %g\n", compute_matrix_element_tau_plus(1));
  printf("M2: %g\n", compute_matrix_element_sigma_tau_plus(1));
  printf("M1': %g\n", compute_matrix_element_tau_plus(4));
  printf("M2': %g\n", compute_matrix_element_sigma_tau_plus(4));
  printf("M3': %g\n", (compute_matrix_element_sigma_tau_plus(4) + compute_matrix_element_TT(4))/3.0);
//  printf("M_AA_GT: %g\n", compute_matrix_element_sigma_tau_plus(1));
//  printf("M_AP_GT: %g\n", compute_matrix_element_sigma_tau_plus(8));
//  printf("M_PP_GT: %g\n", compute_matrix_element_sigma_tau_plus(10));
//  printf("M_MM_GT: %g\n", compute_matrix_element_sigma_tau_plus(12));
//  printf("M_F_sd: %g\n", compute_matrix_element_tau_plus(14));
//  printf("M_AA_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(15));
//  printf("M_AP_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(17));
//  printf("M_PP_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(19));
//  printf("M_MM_GT_sd: %g\n", compute_matrix_element_sigma_tau_plus(21));


  return 0;
}
