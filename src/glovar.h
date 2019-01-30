#include <stdio.h>
#include "math.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_sf_expint.h>
#include <gsl/gsl_sf_result.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_errno.h>
<<<<<<< HEAD
=======
#include <gsl/gsl_sf_bessel.h>
>>>>>>> bb97b0b4a648cc011adfaf2a7aeab75b9934a0e8
#include <gsl/gsl_sf.h>

// Isotope setup
#define A_NUC 76 // Atomic Mass
<<<<<<< HEAD
#define NUM_SHELLS 259
#define A_FACTOR 9.155 // [MeV] Average nuclear excitation energy
#define B_OSC 2.927
=======
#define NUM_SHELLS 99
#define A_FACTOR 9.155 // [MeV] Average nuclear excitation energy
#define B_OSC 2.927 // [fm]
>>>>>>> bb97b0b4a648cc011adfaf2a7aeab75b9934a0e8
#define Z_ATOM 32 // Atomic Number

// FILE SETUP
<<<<<<< HEAD
#define DENSITY_FILE "ge-se-full"
#define WFN_FILE_INITIAL "ne20_basis.trwfn"
#define WFN_FILE_FINAL "mg20_basis.trwfn"
#define ORBIT_FILE "sd.sps"
=======
#define DENSITY_FILE "GE76_DENSITY.DAT"
>>>>>>> bb97b0b4a648cc011adfaf2a7aeab75b9934a0e8

// Technical parameters
#define COR_FAC 1

// Physical constants
#define ALPHA_FS 0.007297352
#define R_NUC 1.2 // [fm]
#define M_ELECTRON 0.511 // [MeV]
#define M_NEUTRON 939.57 // [MeV]
#define E_BETA 2.55 // [MeV]
#define G_AXIAL 1.275 // Axial coupling
#define G_MAGNETIC 4.7
#define G_TENSOR 0.99
#define G_VECTOR 1.0
#define E_HADRON 1 // Hadronization scale [GeV] 

#define MIN(a,b) ((a) < (b) ? (a):(b))
#define MAX(a,b) ((a) > (b) ? (a):(b))

#define PION_MASS 1
#define LAMBDA_V 1
#define LAMBDA_A 1
#define KAPPA_1 1
#define MU 1
