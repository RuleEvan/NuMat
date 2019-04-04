#include "potential.h"
double a_coeff(double n, double l, double k) {
  double a = pow(-1.0, k)/gsl_sf_gamma(k + 1.0);
  a *= sqrt(2.0*gsl_sf_gamma(n + 1.0)/gsl_sf_gamma(n + l + 1.5))*gsl_sf_gamma(n + l + 1.5)/(gsl_sf_gamma(n - k + 1.0)*gsl_sf_gamma(k + l + 1.5));
  
  return a;
}

double b_coeff(double n, double l, double np, double lp, double p) {
  double b = 0.5*gsl_sf_gamma(p + 1.5);
  int k, kp;
  double b_sum = 0.0;
  for (k = 0; k <= n; k++) {
    for (kp = 0; kp <= np; kp++) {
      if (0.5*(2*k + 2*kp + l + lp) != p) {continue;}
      b_sum += a_coeff(n,l,k)*a_coeff(np, lp, kp);
    }
  }
  b *= b_sum;

  return b;
}

double compute_potential(double n, double np, double l, double lp, int iv) {
  // Sum the required Talmi integrals with the corresponding B coefficients
  double v = 0;
  for (int ip = l + lp; ip <= l + lp + 2*n + 2*np; ip += 2) {
    double p = ip/2.0;
    v += b_coeff(n, l, np, lp, p)*talmi(p, iv);
  }
  return v;
}

double talmi(double p, int iv) {
  // Compute the order p Talmi integral
  // Set the limits of the integral and the error tolerance
  double r_min = 0.0001;
  double r_max = 10.0;
  double tol = pow(10, -6);
  double I_p = Romberg3Vars(&talmi_integrand, r_min, r_max, p, iv, tol);
  I_p *= 2.0/gsl_sf_gamma(p + 1.5);
  
  return I_p;
}
    
double talmi_integrand(double q, double p, int iv) {
  // The integrand of the Talmi integral
  // Plug in the required potential here
  double v = pow(q, 2.0*p + 2.0)*exp(-q*q);
  if (iv == 0) {return v;}
  if (COR_FAC == 1) {
    double beta = exp(-1.1*pow(B_OSC*q, 2))*(1.0 - 0.68*pow(B_OSC*q,2.0));
    v *= pow(1.0 - beta, 2.0);
  }
 
  if (iv == 1) {
    v *= v_light_limit(q);
  } else if (iv == 2) {
    v *= v_pion_f1(q);
  } else if (iv == 3) {
    v *= v_pion_f2(q);
  } else if (iv == 4) {
    v *= v_light_limit_d(q);
  } else if (iv == 5) {
    v *= h_F(q);
  } else if (iv == 6) {
    v *= h_AA_GT(q);
  } else if (iv == 7) {
    v *= h_AA_T(q);
  } else if (iv == 8) {
    v *= h_AP_GT(q);
  } else if (iv == 9) {
    v *= h_AP_T(q);
  } else if (iv == 10) {
    v *= h_PP_GT(q);
  } else if (iv == 11) {
    v *= h_PP_T(q);
  } else if (iv == 12) {
    v *= h_MM_GT(q);
  } else if (iv == 13) {
    v *= h_MM_T(q);
  } else if (iv == 14) {
    v *= h_F_sd(q);
  } else if (iv == 15) {
    v *= h_AA_GT_sd(q);
  } else if (iv == 16) {
    v *= h_AA_T_sd(q);
  } else if (iv == 17) {
    v *= h_AP_GT_sd(q);
  } else if (iv == 18) {
    v *= h_AP_T_sd(q);
  } else if (iv == 19) {
    v *= h_PP_GT_sd(q);
  } else if (iv == 20) {
    v *= h_PP_T_sd(q);
  } else if (iv == 21) {
    v *= h_MM_GT_sd(q);
  } else if (iv == 22) {
    v *= h_MM_T_sd(q);
  }

  return v;
}

double v_light_limit(double r) {
  // Nuclear potential in the case of light neutrinos 
  // Lepton kinematics are ignored (see Haxton review sec. 3.4.2)
  double lb = 0.0050677*B_OSC*A_FACTOR;
  double v = 2.0/M_PI/B_OSC;   
  v *= 1/r;
  v *= gsl_sf_Ci(r*lb)*sin(r*lb) + (M_PI/2.0 - gsl_sf_Si(r*lb))*cos(r*lb);

  return v;
}

double v_light_limit_d(double r) {
  // Nuclear potential in the case of light neutrinos 
  // Lepton kinematics are ignored (see Haxton review sec. 3.4.2)
  double lb = 0.0050677*B_OSC*A_FACTOR;
  double v = (sin(lb*r)*gsl_sf_Ci(lb*r) + cos(lb*r)*(M_PI/2.0 - gsl_sf_Si(lb*r)))/(M_PI*r*B_OSC) - lb/B_OSC*(cos(lb*r)*gsl_sf_Ci(lb*r)-sin(lb*r)*(M_PI/2.0 - gsl_sf_Si(lb*r)))/M_PI;   
  v *= 2.0;

  return v;
}

double v_pion_f1(double r) {
  r *= B_OSC;
  double v = 1/r;
  double x = r*PION_MASS*0.0050677;
  v *= (x - 2.0)*exp(-x);
  
  return v;  
}

double v_pion_f2(double r) {
  r *= B_OSC;
  double v = 1/r;
  double x = r*PION_MASS*0.0050677;
  v *= (x + 1.0)*exp(-x);
  
  return v;  
}

double v_pion_g1(double r) {
  r *= B_OSC;
  double v = 1/pow(r, 3.0);
  double x = r*PION_MASS*0.0050677;
  v *= -1.0*pow(x, 2.0)/3.0*(4.0 - x)*exp(-x);
  
  return v;
}

double v_pion_g2(double r) {
  r *= B_OSC;
  double v = 1/pow(r, 3.0);
  double x = r*PION_MASS*0.0050677;
  v *= -1.0*(2.0 + 2.0*x + 1.0/3.0*(x*x - x*x*x))*exp(-x);

  return v;
}

double v_pion_NN_g1(double r) {
  r *= B_OSC;
  double v = 1/pow(r, 3.0);
  double x = r*PION_MASS*0.0050677;
  v *= -1.0/3.0*x*x*exp(-x);

  return v;
}

double v_pion_NN_g2(double r) {
  r *= B_OSC;
  double v = 1/pow(r, 3.0);
  double x = r*PION_MASS*0.0050677;
  v *= -1.0*(1.0 + x + 1.0/3.0*x*x)*exp(-x);

  return v;
}

double h_AA_GT_sd(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_A*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double v = r_a*pow(a, 3)/(48*r*pow(b, 2))*exp(-a)*(3 + a*(3 + a));

  return v;
}

double h_AA_T_sd(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_A*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double v = r_a/(48*r*pow(b, 2))*(144 + exp(-a)*(-a*(12 + a*a)*(12 + a*(6 + a)) - 144));

  return v;
}

double h_AP_GT_sd(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_A*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double v = -4.0*r_a*pow(a, 5)/(3*96*r*pow(b, 2)*pow(a*a-b*b, 4))*(-48*pow(a, 3)*pow(b, 2)*exp(-b) + exp(-a)*(pow(a, 6)*(3 + a*(3 + a)) - 3*pow(a, 3)*(-16 + a*(-7 + a + a*a))*b*b + 3*a*a*(-9 + (-1 + a)*a)*pow(b, 4) + (3 - (a-3)*a)*pow(b, 6)));

  return v;
}

double h_AP_T_sd(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_A*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double v = 4.0*r_a*pow(a, 7)/(3*96*r*pow(b, 2)*pow(a*a-b*b, 4))*(exp(-a)*(-6*pow(a, 5) - pow(a, 6) + pow(b, 6) + 3*pow(a, 4)*(b*b-8) + 12*pow(a, 3)*(b*b-6) -3*a*a*(48-8*b*b+pow(b, 4)) -6*a*(24-4*b*b+pow(b, 4))) + exp(-b)*6*a*(8*(3 + 3*b + b*b)));

  return v;
}
 
double h_PP_GT_sd(double r) {
   r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_A*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double v = 2.0*r_a*pow(a, 7)/(3*96*r*pow(b, 2)*pow(a*a-b*b, 5))*(exp(-b)*24*a*b*b*(a*a*(b-4) -b*b*(b+4)) + exp(-a)*(pow(a, 6)*(3 + a*(3 + a)) + 3*a*a*a*(32 + a*(17 + a - a*a))*b*b + 3*a*(32 + a*(-13 + (a-5)*a))*pow(b, 4) - (15 + (a-9)*a)*pow(b, 6)));
  
 return v;
}

double h_PP_T_sd(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_A*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double v = -2.0*r_a*pow(a, 8)/(3*96*r*pow(b, 2)*pow(a*a-b*b, 5))*(exp(-a)*(-6*pow(a, 6)-pow(a, 7) + 6*pow(a, 4)*(b*b-12) + 3*pow(a, 5)*(b*b-8) - 3*pow(a, 3)*(48 + 8*b*b + pow(b, 4)) + a*b*b*(-432 + 48*b*b + pow(b, 4))) - 6*a*a*(4*(-6-6*b-b*b+pow(b, 3))*exp(-b) + (24 + 28*b*b - pow(b, 4))*exp(-a))+6*b*b*(4*(18 + 18*b + 7*b*b + pow(b, 3))*exp(-b) -(72 - 8*b*b + pow(b, 4))*exp(-a)));

  return v;
}

double h_MM_GT_sd(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_V*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double c = r*M_NEUTRON*0.0050677;
  double v = -pow(1 + KAPPA_1, 2)*r_a/(3*96*b*b*c*c*r*pow(G_AXIAL, 2))*pow(a, 5)*exp(-a)*(-3 + a*(a-3));

  return v;
}

double h_MM_T_sd(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_V*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double c = r*M_NEUTRON*0.0050677;
  double v = 0.5*pow(1 + KAPPA_1, 2)*r_a/(3*96*b*b*c*c*r*pow(G_AXIAL, 2))*pow(a, 7)*exp(-a);  

  return v;
}

double h_F_sd(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_V*0.0050677;
  double b = r*PION_MASS*0.0050677;
  double v = 2.0*r_a/(96*r*b*b)*pow(a, 3)*exp(-a)*(3 + a*(3+a));
  
  return v;
}


double h_AA_GT(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double x = r*LAMBDA_A*0.0050677;
  double v = r_a/r*(1.0 - exp(-x)*(1.0 + 11.0/16.0*x + 3.0/16.0*x*x + 1.0/48.0*x*x*x));

  return v;
}

double h_AA_T(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double x = r*LAMBDA_A*0.0050677;
  double v = r_a/r*(0.5 - 12.0/(x*x) + exp(-x)*(12.0/(x*x) + 12.0/x + 11.0/2.0 + 1.5*x + 0.25*x*x + 1.0/48.0*x*x*x));
 
  return v;
}

double h_AP_GT(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double y = r*PION_MASS*0.0050677;
  double x = r*LAMBDA_A*0.0050677;
  double v = 4.0*r_a*pow(x, 3)/(3.0*96*r*pow(x-y, 4)*pow(x+y, 4));
  v *= (exp(-y)*(-48*pow(x, 5)) + exp(-x)*(48*pow(x, 5) + 33*pow(x, 6) + 9*pow(x, 7) + pow(x, 8) - 45*pow(x, 4)*y*y - 21*pow(x, 5)*y*y - 3*pow(x, 6)*y*y + 15*x*y*pow(y, 4) + 15*x*x*x*pow(y, 4) + 3*pow(x*y, 4) - 3*pow(y, 6) - 3*x*pow(y, 6) - x*x*pow(y, 6)));

  return v;
}

double h_AP_T(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double b = r*PION_MASS*0.0050677;
  double a = r*LAMBDA_A*0.0050677;
  double v = r_a/(r*72*b*b*pow(a*a-b*b, 4))*(exp(-b)*(-48*pow(a, 8)*(3 + b*(3+b))) + exp(-a)*(pow(a, 6)*(12 + a*(6 + a))*(48 + a*(24 + a*(6 + a)))*b*b - 3*pow(a, 4)*(12 + a*(6 + a))*(24 + a*(12 + a*(4 + a)))*pow(b, 4) + 3*a*a*(192 + a*(192 + a*(96 + a*(32 + a*(8 + a)))))*pow(b, 6) - (144 + a*(12 + a*a)*(12 + a*(6 + a)))*pow(b, 8)) + 144*pow(a*a-b*b, 4));

  return v;
}

double h_PP_GT(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double y = r*PION_MASS*0.0050677;
  double x = r*LAMBDA_A*0.0050677;
  double v = r_a/r*pow(x, 5)/144.0/pow(x*x - y*y, 5);
  v *= (exp(-y)*(-24*x*x*x*(-2*x*x + x*x*y - 6*y*y - y*y*y)) - exp(-x)*(48*pow(x, 5) + 33*pow(x, 6) + 9*pow(x, 7) + pow(x, 8) + y*y*(144*pow(x, 3) + 9*pow(x, 4) - 15*pow(x, 5) - 3*pow(x, 6)) - 45*pow(y, 4)*x*x + 3*pow(x*y, 4) + 3*pow(y, 6) + 3*x*pow(y, 6) - x*x*pow(y, 6)));

  return v;
}

double h_PP_T(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double b = r*PION_MASS*0.0050677;
  double a = r*LAMBDA_A*0.0050677;
  double v = -2.0*r_a*pow(a, 7)/(3.0*r*96*pow(a-b, 5)*pow(a+b, 5));
  v *= (exp(-b)*(-576*a+24*pow(a, 3)-576*a*b + 24*pow(a,3)*b - 216*a*b*b - 24*a*pow(b, 3)) + exp(-a)*(576*a + 576*a*a + 264*a*a*a + 72*pow(a, 4) + 12*pow(a, 5) + pow(a, 6) - 72*a*b*b - 72*a*a*b*b - 24*pow(a, 3)*b*b - 3*pow(a, 4)*b*b + 12*a*pow(b, 4) + 3*a*a*pow(b, 4) - pow(b, 6)));

  return v;
}

double h_MM_GT(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_V*0.0050677;
  double b = r*M_NEUTRON*0.0050667;
  double v = pow(1 + KAPPA_1, 2.0)*r_a/(288*pow(G_AXIAL, 2)*b*b*r)*pow(a, 3)*exp(-a)*(3 + a*(3+a));
 
  return v;
}

double h_MM_T(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_V*0.0050677;
  double b = r*M_NEUTRON*0.0050677;
  double v = pow(1 + KAPPA_1, 2.0)*r_a/(288*2*pow(G_AXIAL, 2)*b*b*r)*(144 + exp(-a)*(-a*(12 + a*a)*(12 + a*(6 + a)) - 144));

  return v;
}
double h_F(double r) {
  r *= B_OSC;
  double r_a = R_NUC*pow(A_NUC, 1.0/3.0);
  double a = r*LAMBDA_V*0.0050677;
  double v = r_a/(48*r)*(48 + exp(-a)*(-48 - a*(33 + a*(9+a))));

  return v;
}
