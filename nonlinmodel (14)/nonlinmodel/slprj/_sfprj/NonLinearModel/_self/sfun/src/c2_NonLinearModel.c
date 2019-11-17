/* Include files */

#include "NonLinearModel_sfun.h"
#include "c2_NonLinearModel.h"

/* Type Definitions */

/* Named Constants */
#define c2_IN_NO_ACTIVE_CHILD          (0)

/* Variable Declarations */

/* Variable Definitions */
static SFc2_NonLinearModelInstanceStruct chartInstance;

/* Function Declarations */
static void initialize_c2_NonLinearModel(void);
static void initialize_params_c2_NonLinearModel(void);
static void enable_c2_NonLinearModel(void);
static void disable_c2_NonLinearModel(void);
static void finalize_c2_NonLinearModel(void);
static void sf_c2_NonLinearModel(void);
static void c2_c2_NonLinearModel(void);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static real_T c2_mpower(real_T c2_a);
static real_T c2_b_mpower(real_T c2_a);
static real_T c2_c_mpower(real_T c2_a);
static real_T c2_mrdivide(real_T c2_A, real_T c2_B);
static void c2_eml_warning(void);
static real_T c2_interp1(real_T c2_par1[8], real_T c2_par2[8], real_T c2_par3);
static void c2_eml_error(void);
static void c2_b_eml_error(void);
static real_T c2_d_mpower(real_T c2_a);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[66]);
static void init_dsm_address_info(void);

/* Function Definitions */
static void initialize_c2_NonLinearModel(void)
{
  _sfTime_ = (real_T)ssGetT(chartInstance.S);
}

static void initialize_params_c2_NonLinearModel(void)
{
}

static void enable_c2_NonLinearModel(void)
{
  _sfTime_ = (real_T)ssGetT(chartInstance.S);
}

static void disable_c2_NonLinearModel(void)
{
  _sfTime_ = (real_T)ssGetT(chartInstance.S);
}

static void finalize_c2_NonLinearModel(void)
{
}

static void sf_c2_NonLinearModel(void)
{
  uint8_T c2_previousEvent;
  _sfTime_ = (real_T)ssGetT(chartInstance.S);
  c2_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  c2_c2_NonLinearModel();
  _sfEvent_ = c2_previousEvent;
}

static void c2_c2_NonLinearModel(void)
{
  real_T c2_Mach;
  real_T c2_mass;
  real_T c2_rho;
  real_T c2_M_const;
  real_T c2_V;
  real_T c2_beta;
  real_T c2_alpha;
  real_T c2_de;
  real_T c2_da;
  real_T c2_dr;
  real_T c2_p;
  real_T c2_q;
  real_T c2_r;
  real_T c2_adot;
  real_T c2_CD0;
  real_T c2_y;
  real_T c2_b;
  real_T c2_b_b;
  real_T c2_c_b;
  real_T c2_CDa;
  real_T c2_d_b;
  real_T c2_e_b;
  real_T c2_f_b;
  static real_T c2_dv0[8] = { 0.09, 0.09, 0.09, 0.105, 0.13, 0.12, 0.07, 0.02 };

  static real_T c2_dv1[8] = { 0.0, 0.4, 0.6, 0.7, 0.75, 0.8, 0.85, 0.9 };

  real_T c2_CL0;
  real_T c2_CLa;
  real_T c2_CLalphadot;
  static real_T c2_dv2[8] = { 4.45, 4.45, 4.5, 4.6, 4.7, 4.85, 4.75, 4.75 };

  static real_T c2_dv3[8] = { 0.0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.75, 0.9 };

  real_T c2_CLq;
  static real_T c2_dv4[8] = { 0.025, 0.025, 0.03, 0.025, 0.02, 0.05, -0.02,
    -0.03 };

  real_T c2_Cm0;
  real_T c2_Cma;
  real_T c2_Cmalphadot;
  real_T c2_Cmq;
  real_T c2_B;
  real_T *c2_Cn;
  real_T *c2_Cm;
  real_T *c2_Cl;
  real_T *c2_CZ;
  real_T *c2_CY;
  real_T *c2_CX;
  real_T *c2_b_M_const;
  real_T *c2_b_rho;
  real_T *c2_b_mass;
  real_T *c2_b_Mach;
  real_T (*c2_Wind)[3];
  real_T (*c2_Control)[3];
  real_T (*c2_AngRates)[3];
  real_T (*c2_ABdot)[2];
  c2_CZ = (real_T *)ssGetOutputPortSignal(chartInstance.S, 3);
  c2_CX = (real_T *)ssGetOutputPortSignal(chartInstance.S, 1);
  c2_Control = (real_T (*)[3])ssGetInputPortSignal(chartInstance.S, 1);
  c2_Wind = (real_T (*)[3])ssGetInputPortSignal(chartInstance.S, 0);
  c2_AngRates = (real_T (*)[3])ssGetInputPortSignal(chartInstance.S, 3);
  c2_b_Mach = (real_T *)ssGetInputPortSignal(chartInstance.S, 4);
  c2_Cm = (real_T *)ssGetOutputPortSignal(chartInstance.S, 5);
  c2_b_M_const = (real_T *)ssGetInputPortSignal(chartInstance.S, 7);
  c2_b_rho = (real_T *)ssGetInputPortSignal(chartInstance.S, 6);
  c2_CY = (real_T *)ssGetOutputPortSignal(chartInstance.S, 2);
  c2_Cl = (real_T *)ssGetOutputPortSignal(chartInstance.S, 4);
  c2_ABdot = (real_T (*)[2])ssGetInputPortSignal(chartInstance.S, 2);
  c2_Cn = (real_T *)ssGetOutputPortSignal(chartInstance.S, 6);
  c2_b_mass = (real_T *)ssGetInputPortSignal(chartInstance.S, 5);
  c2_Mach = *c2_b_Mach;
  c2_mass = *c2_b_mass;
  c2_rho = *c2_b_rho;
  c2_M_const = *c2_b_M_const;
  c2_V = (*c2_Wind)[0];
  c2_beta = (*c2_Wind)[1];
  c2_alpha = (*c2_Wind)[2];
  c2_de = (*c2_Control)[0];
  c2_da = (*c2_Control)[1];
  c2_dr = (*c2_Control)[2];

  /*  m */
  c2_p = (*c2_AngRates)[0];
  c2_q = (*c2_AngRates)[1];
  c2_r = (*c2_AngRates)[2];
  c2_adot = (*c2_ABdot)[0];

  /* % Drag */
  /*  Minimum drag */
  if (*c2_b_Mach < 0.4) {
    c2_CD0 = 0.0223;
  } else if (*c2_b_Mach > 0.92) {
    c2_CD0 = 0.1032;
  } else {
    c2_y = 5.9269 * *c2_b_Mach;
    c2_b = c2_c_mpower(*c2_b_Mach);
    c2_b_b = c2_b_mpower(c2_Mach);
    c2_c_b = c2_mpower(c2_Mach);
    c2_CD0 = (((7.861 * c2_c_b - 18.378 * c2_b_b) + 15.832 * c2_b) - c2_y) +
      0.8349;

    /*      CD0 = 7.861*M_const^4 - 18.378*M_const^3 + 15.832*M_const^2 ... */
    /*          - 5.9269*M_const + 0.8349; */
  }

  /*  alpha derivate */
  c2_y = c2_c_mpower(c2_mrdivide(c2_alpha * 180.0, 3.1415926535897931E+000));
  c2_CDa = 0.00103 * c2_y - c2_mrdivide(0.00308 * c2_alpha * 180.0,
    3.1415926535897931E+000);

  /*  Pitch control (elevator) derivative */
  c2_d_b = c2_mrdivide(c2_de * 180.0, 3.1415926535897931E+000);
  c2_e_b = c2_c_mpower(c2_mrdivide(c2_de * 180.0, 3.1415926535897931E+000));
  c2_f_b = c2_b_mpower(c2_mrdivide(c2_de * 180.0, 3.1415926535897931E+000));

  /* % Lift */
  /*  Zero-alpha lift */
  /*  CL0 = 0.3; */
  /*  pocatecni hodnota vztlakoveho soucinitele */
  /*      CL0 = interp1(x_cy0,y_cy0,M_const); */
  c2_CL0 = c2_interp1(c2_dv1, c2_dv0, c2_Mach);

  /*  alpha derivative */
  /*  CLa = 4.44; */
  /*  derivace soucinitele vztlaku podle uhlu nabehu */
  if (c2_Mach <= 0.3) {
    c2_CLa = 4.4418;
  } else {
    c2_y = c2_c_mpower(c2_Mach);
    c2_b = c2_b_mpower(c2_Mach);
    c2_b_b = c2_mpower(c2_Mach);
    c2_c_b = c2_d_mpower(c2_Mach);
    c2_CLa = ((((-62.716 * c2_c_b + 122.09 * c2_b_b) - 85.797 * c2_b) + 28.153 *
               c2_y) - 3.8433 * c2_Mach) + 4.541;
  }

  /*  Pitch control (elevator) derivative */
  /*  alpha-dot derivative */
  /*  CLalphadot = 0; */
  /*  derivace soucinitele vztlaku podle bezrozmerne zmeny uhlu nabehu */
  if (c2_Mach < 0.3) {
    c2_CLalphadot = 2.4997555500000068E+000;
  } else if (c2_Mach > 0.7) {
    c2_CLalphadot = 6.4973095000010517E-001;
  } else {
    c2_CLalphadot = ((((-49.167 + 5.58542E+002 * c2_Mach) - 2.284051E+003 * pow
                       (c2_Mach, 2.0)) + 4.412037E+003 * pow(c2_Mach, 3.0)) -
                     4.06713E+003 * pow(c2_Mach, 4.0)) + 1.435185E+003 * pow
      (c2_Mach, 5.0);
  }

  /*  Pitch rate derivative */
  /*  CLq = 3.8; */
  /*  derivace soucinitele vztlaku podle bezrozmerne rychlosti kloneni */
  /*      CLq = 5.7414 - 9.3115*M + 20.8*M^2 - 13.465*M^3; */
  c2_CLq = c2_interp1(c2_dv3, c2_dv2, c2_Mach);

  /* %% Pitch moment coefficient %%% */
  /*  Zero-alpha pitch */
  /*  Cm0 = 0; */
  /*      pocatecni hodnota klopiveho soucinitele */
  /*      Cm0 = interp1(x_cy0,y_mz0,M); */
  c2_Cm0 = c2_interp1(c2_dv1, c2_dv4, c2_M_const);

  /*      Cm0 = 0.025; */
  /*  	if M <= 0.3 */
  /*          Cm0 = 0.025; */
  /*      else */
  /*          Cm0 = -0.703*M^3 + 0.828*M^2 - 0.258*M + 0.040; */
  /*      end */
  /*  alpha derivative */
  /*  Cma = -0.683; */
  if (c2_Mach <= 0.3) {
    c2_Cma = -0.4899;
  } else {
    /*          M = M_const; */
    c2_Cma = (((5.9964 * pow(c2_Mach, 4.0) - 10.271 * pow(c2_Mach, 3.0)) +
               6.7921 * pow(c2_Mach, 2.0)) - 2.0056 * c2_Mach) - 0.2708;
  }

  /*  Pitch control derivative */
  /*  alpha_dot derivative */
  /*      Cmalphadot = -4.36; */
  if (c2_Mach <= 0.3) {
    c2_Cmalphadot = -1.38271969;
  } else {
    c2_Cmalphadot = ((((5.02427E+002 * pow(c2_Mach, 5.0) - 1.30311E+003 * pow
                        (c2_Mach, 4.0)) + 1330.2481 * pow(c2_Mach, 3.0)) -
                      6.680225E+002 * pow(c2_Mach, 2.0)) + 1.6408E+002 * c2_Mach)
      - 17.0671;
  }

  /*  Pitch rate derivative */
  /*      Cmq = -9.96; */
  if (c2_Mach <= 0.3) {
    c2_Cmq = -4.9934668;
  } else {
    c2_Cmq = ((2.5926 * pow(c2_Mach, 3.0) - 8.7063 * pow(c2_Mach, 2.0)) + 4.859 *
              c2_Mach) - 5.7376;
  }

  /* % Side force coefficient %%% */
  c2_y = 0.5 * c2_rho * pow(c2_V, 2.0) * 18.8;
  if (c2_y == 0.0) {
    c2_eml_warning();
  }

  c2_y = c2_mass * 9.81 / c2_y;

  /*  Sideslip derivative */
  /*  CYbeta = -0.564; */
  /*  Roll control derivative */
  /*  Yaw control derivative */
  /* % Roll moment coefficient %%% */
  /*  Sideslip derivative */
  if (c2_Mach < 0.45) {
    c2_b = (-0.056 - 0.0576 * c2_y) - 0.0088 * c2_Mach;
  } else {
    c2_b = (-0.06 - 0.0576 * c2_y) - 0.0285 * (c2_Mach - 0.45);
  }

  /*  Roll control derivative */
  if (c2_Mach <= 0.6) {
    c2_b_b = -0.156 + 0.04 * (c2_Mach - 0.2);
  } else {
    c2_b_b = ((-1.1039 + 4.6696 * c2_Mach) - 7.5941 * pow(c2_Mach, 2.0)) +
      4.1483 * pow(c2_Mach, 3.0);
  }

  /*  Yaw control derivative */
  /*  Roll rate derivative */
  /*  Yaw rate derivative */
  /* % Yaw moment coefficient %%% */
  /*  Sideslip derivative */
  /*  Roll control derivative    */
  /*  Yaw control derivative */
  /*  Roll rate derivative */
  if (c2_Mach < 0.7) {
    c2_c_b = (-0.07435 + 0.045 * c2_y) - 0.0092 * c2_Mach;
  } else {
    c2_c_b = (-0.08079 + 0.044 * c2_y) - 0.0333 * (c2_Mach - 0.7);
  }

  /*  Yaw rate derivative */
  if (c2_V == 0.0) {
    c2_eml_warning();
  }

  if (c2_V == 0.0) {
    c2_eml_warning();
  }

  c2_M_const = 2.0 * c2_V;
  if (c2_M_const == 0.0) {
    c2_eml_warning();
  }

  c2_rho = 2.0 * c2_V;
  if (c2_rho == 0.0) {
    c2_eml_warning();
  }

  if (c2_V == 0.0) {
    c2_eml_warning();
  }

  if (c2_V == 0.0) {
    c2_eml_warning();
  }

  c2_mass = 2.0 * c2_V;
  if (c2_mass == 0.0) {
    c2_eml_warning();
  }

  c2_B = 2.0 * c2_V;
  if (c2_B == 0.0) {
    c2_eml_warning();
  }

  *c2_CX = (c2_CD0 + c2_CDa) + (((6.2863E-007 * c2_f_b + 4.1831E-005 * c2_e_b) -
    0.00031917 * c2_d_b) + 0.00016834);
  *c2_CY = ((((-0.946 - 0.0333 * c2_y) + 0.0032 * c2_Mach) - 0.16 * pow(c2_Mach,
              2.0)) * c2_beta + -0.02 * c2_da) + ((((-0.1845 +
    0.0325 * c2_y) - 0.0093 * c2_Mach) - 0.0228 * pow(c2_Mach, 2.0)) - 0.012 *
    pow(c2_Mach, 3.0)) * c2_dr;
  *c2_CZ = (((c2_CL0 + c2_CLa * c2_alpha) + 0.305 * c2_de) + 2.15 * c2_q *
            c2_CLq / c2_V) + 2.15 * c2_adot * c2_CLalphadot / c2_V;
  *c2_Cl = (((c2_b * c2_beta + 9.17 * c2_p * ((((-0.5365 - 1.5267 * c2_Mach) +
    10.781 * pow(c2_Mach, 2.0)) - 20.666 * pow(c2_Mach, 3.0
    )) + 12.4242 * pow(c2_Mach, 4.0)) / c2_rho) + 9.17 * c2_r * ((-0.075 - 0.215
    * c2_y) - 0.016 * c2_Mach) / c2_M_const) + c2_b_b *
            c2_da) + (-0.03 + 0.008 * c2_y) * c2_dr;
  *c2_Cm = (((c2_Cm0 + c2_Cma * c2_alpha) + -0.88 * c2_de) + 2.15 * c2_q *
            c2_Cmq / c2_V) + 2.15 * c2_adot * c2_Cmalphadot / c2_V;
  *c2_Cn = (((((((-0.173 + 0.01667 * c2_y) + 0.0092 * c2_Mach) - 0.1 * pow
                (c2_Mach, 2.0)) + 0.0208 * pow(c2_Mach, 3.0)) * c2_beta +
              9.17 * c2_p * c2_c_b / c2_B) + 9.17 * c2_r * ((((((-0.2291 -
    0.0065 * c2_y) - 0.0236 * pow(c2_y, 2.0)) + 0.0069 * pow(c2_y, 3.0)) -
    0.0219 * c2_Mach) + 0.0097 * pow(c2_Mach, 2.0)) - 0.0447 * pow(c2_Mach, 3.0))
             / c2_mass) + -0.0015 * c2_da) + ((((0.015 * c2_y -
    0.095) - 0.0056 * c2_Mach) - 0.0089 * pow(c2_Mach, 2.0)) - 0.0068 * pow
    (c2_Mach, 3.0)) * c2_dr;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static real_T c2_mpower(real_T c2_a)
{
  return pow(c2_a, 4.0);
}

static real_T c2_b_mpower(real_T c2_a)
{
  return pow(c2_a, 3.0);
}

static real_T c2_c_mpower(real_T c2_a)
{
  return pow(c2_a, 2.0);
}

static real_T c2_mrdivide(real_T c2_A, real_T c2_B)
{
  if (c2_B == 0.0) {
    c2_eml_warning();
  }

  return c2_A / c2_B;
}

static void c2_eml_warning(void)
{
  int32_T c2_i0;
  static char c2_varargin_1[19] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'd', 'i',
    'v', 'i', 'd', 'e', 'B', 'y', 'Z', 'e', 'r', 'o' };

  char c2_u[19];
  const mxArray *c2_y = NULL;
  static char c2_varargin_2[15] = { 'D', 'i', 'v', 'i', 'd', 'e', ' ', 'b', 'y',
    ' ', 'z', 'e', 'r', 'o', '.' };

  char c2_b_u[15];
  const mxArray *c2_b_y = NULL;
  for (c2_i0 = 0; c2_i0 < 19; c2_i0 = c2_i0 + 1) {
    c2_u[c2_i0] = c2_varargin_1[c2_i0];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create(&c2_u, "y", 8, 0U, 1U, 2, 1, 19));
  for (c2_i0 = 0; c2_i0 < 15; c2_i0 = c2_i0 + 1) {
    c2_b_u[c2_i0] = c2_varargin_2[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create(&c2_b_u, "y", 8, 0U, 1U, 2, 1, 15));
  sf_mex_call("warning", 0U, 2U, 14, c2_y, 14, c2_b_y);
}

static real_T c2_interp1(real_T c2_par1[8], real_T c2_par2[8], real_T c2_par3)
{
  real_T c2_yi;
  int32_T c2_k;
  real_T c2_x[8];
  real_T c2_r;
  real_T c2_yv[8];
  boolean_T c2_b_x[8];
  real_T c2_y[8];
  boolean_T c2_b_y;
  int32_T c2_exitg1;
  boolean_T c2_b0;
  int32_T c2_low_i;
  int32_T c2_high_i;
  int32_T c2_mid_i;
  real_T c2_b;
  c2_yi = rtNaN;
  for (c2_k = 0; c2_k < 8; c2_k = c2_k + 1) {
    c2_x[c2_k] = c2_par1[c2_k];
    c2_r = c2_par2[c2_k];
    c2_yv[c2_k] = c2_r;
    c2_b_x[c2_k] = rtIsNaN(c2_par1[c2_k]);
    c2_y[c2_k] = c2_r;
  }

  c2_b_y = false;
  c2_k = 1;
  c2_exitg1 = 0U;
  while ((c2_exitg1 == 0U) && (c2_k <= 8)) {
    if (c2_b_x[c2_k - 1] == 0) {
      c2_b0 = true;
    } else {
      sf_mex_lw_bounds_check(c2_k, 1, 8);
      c2_b0 = false;
    }

    if (!c2_b0) {
      c2_b_y = true;
      c2_exitg1 = 1U;
    } else {
      c2_k = c2_k + 1;
    }
  }

  if (c2_b_y) {
    c2_eml_error();
    return rtNaN;
  } else {
    if (c2_par1[1] < c2_par1[0]) {
      for (c2_k = 0; c2_k < 8; c2_k = c2_k + 1) {
        c2_x[c2_k] = c2_par1[7 + -1 * c2_k];
        c2_yv[c2_k] = c2_y[7 + -1 * c2_k];
      }
    }

    for (c2_k = 2; c2_k < 9; c2_k = c2_k + 1) {
      if (c2_x[c2_k - 1] <= c2_x[c2_k - 2]) {
        c2_b_eml_error();
      }
    }

    c2_low_i = 0;
    if ((!(c2_par3 > c2_x[7])) && (!(c2_par3 < c2_x[0]))) {
      c2_low_i = 1;
      c2_k = 2;
      c2_high_i = 8;
      while ((uint32_T)c2_high_i > (uint32_T)c2_k) {
        c2_mid_i = (int32_T)((uint32_T)(c2_low_i + c2_high_i) >> 1);
        if (c2_par3 >= c2_x[c2_mid_i - 1]) {
          c2_low_i = c2_mid_i;
          c2_k = c2_mid_i + 1;
        } else {
          c2_high_i = c2_mid_i;
        }
      }
    }

    if (c2_low_i > 0) {
      c2_k = c2_low_i + 1;
      c2_r = (c2_par3 - c2_x[sf_mex_lw_bounds_check(c2_low_i, 1, 8) - 1]) /
        (c2_x[c2_k - 1] - c2_x[sf_mex_lw_bounds_check(c2_low_i, 1, 8)
         - 1]);
      c2_b = c2_yv[c2_k - 1] - c2_yv[sf_mex_lw_bounds_check(c2_low_i, 1, 8) - 1];
      c2_b = c2_r * (c2_yv[c2_k - 1] - c2_yv[sf_mex_lw_bounds_check(c2_low_i, 1,
        8) - 1]);
      return c2_yv[sf_mex_lw_bounds_check(c2_low_i, 1, 8) - 1] + c2_r *
        (c2_yv[c2_k - 1] - c2_yv[sf_mex_lw_bounds_check(c2_low_i, 1, 8) -
         1]);
    }
  }

  return c2_yi;
}

static void c2_eml_error(void)
{
  int32_T c2_i1;
  static char c2_varargin_1[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'n',
    't', 'e', 'r', 'p', '1', ':', 'N', 'a', 'N', 'i', 'n'
    , 'X' };

  char c2_u[21];
  const mxArray *c2_y = NULL;
  static char c2_varargin_2[38] = { 'N', 'a', 'N', ' ', 'i', 's', ' ', 'n', 'o',
    't', ' ', 'a', 'n', ' ', 'a', 'p', 'p', 'r', 'o', 'p'
    , 'r', 'i', 'a', 't', 'e', ' ', 'v', 'a', 'l', 'u', 'e', ' ', 'f', 'o', 'r',
    ' ', 'X', '.' };

  char c2_b_u[38];
  const mxArray *c2_b_y = NULL;
  for (c2_i1 = 0; c2_i1 < 21; c2_i1 = c2_i1 + 1) {
    c2_u[c2_i1] = c2_varargin_1[c2_i1];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create(&c2_u, "y", 8, 0U, 1U, 2, 1, 21));
  for (c2_i1 = 0; c2_i1 < 38; c2_i1 = c2_i1 + 1) {
    c2_b_u[c2_i1] = c2_varargin_2[c2_i1];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create(&c2_b_u, "y", 8, 0U, 1U, 2, 1, 38));
  sf_mex_call("error", 0U, 2U, 14, c2_y, 14, c2_b_y);
}

static void c2_b_eml_error(void)
{
  int32_T c2_i2;
  static char c2_varargin_1[36] = { 'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', 'M',
    'A', 'T', 'L', 'A', 'B', ':', 'i', 'n', 't', 'e', 'r'
    , 'p', '1', ':', 'n', 'o', 'n', 'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c',
    'X' };

  char c2_u[36];
  const mxArray *c2_y = NULL;
  static char c2_varargin_2[61] = { 'T', 'h', 'e', ' ', 'd', 'a', 't', 'a', ' ',
    'a', 'b', 's', 'c', 'i', 's', 's', 'a', 'e', ' ', 's'
    , 'h', 'o', 'u', 'l', 'd', ' ', 'b', 'e', ' ', 'd', 'i', 's', 't', 'i', 'n',
    'c', 't', ' ', 'a',
    'n', 'd', ' ', 's', 't', 'r', 'i', 'c', 't', 'l', 'y', ' ', 'm', 'o', 'n',
    'o', 't', 'o', 'n', 'i'
    , 'c', '.' };

  char c2_b_u[61];
  const mxArray *c2_b_y = NULL;
  for (c2_i2 = 0; c2_i2 < 36; c2_i2 = c2_i2 + 1) {
    c2_u[c2_i2] = c2_varargin_1[c2_i2];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create(&c2_u, "y", 8, 0U, 1U, 2, 1, 36));
  for (c2_i2 = 0; c2_i2 < 61; c2_i2 = c2_i2 + 1) {
    c2_b_u[c2_i2] = c2_varargin_2[c2_i2];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create(&c2_b_u, "y", 8, 0U, 1U, 2, 1, 61));
  sf_mex_call("error", 0U, 2U, 14, c2_y, 14, c2_b_y);
}

static real_T c2_d_mpower(real_T c2_a)
{
  return pow(c2_a, 5.0);
}

const mxArray *sf_c2_NonLinearModel_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[66];
  c2_ResolvedFunctionInfo (*c2_b_info)[66];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i3;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  c2_b_info = (c2_ResolvedFunctionInfo (*)[66])c2_info;
  (*c2_b_info)[64].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  (*c2_b_info)[64].name = "eml_all_or_any";
  (*c2_b_info)[64].dominantType = "char";
  (*c2_b_info)[64].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  (*c2_b_info)[64].fileLength = 3266U;
  (*c2_b_info)[64].fileTime1 = 1192466764U;
  (*c2_b_info)[64].fileTime2 = 0U;
  (*c2_b_info)[65].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  (*c2_b_info)[65].name = "eml_error";
  (*c2_b_info)[65].dominantType = "char";
  (*c2_b_info)[65].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  (*c2_b_info)[65].fileLength = 318U;
  (*c2_b_info)[65].fileTime1 = 1192466776U;
  (*c2_b_info)[65].fileTime2 = 0U;
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 66));
  for (c2_i3 = 0; c2_i3 < 66; c2_i3 = c2_i3 + 1) {
    c2_r0 = &c2_info[c2_i3];
    sf_mex_addfield(c2_m0, sf_mex_create(c2_r0->context, "nameCaptureInfo", 13,
      0U, 0U, 2, 1, strlen(c2_r0->context)), "context",
                    "nameCaptureInfo", c2_i3);
    sf_mex_addfield(c2_m0, sf_mex_create(c2_r0->name, "nameCaptureInfo", 13, 0U,
      0U, 2, 1, strlen(c2_r0->name)), "name",
                    "nameCaptureInfo", c2_i3);
    sf_mex_addfield(c2_m0, sf_mex_create(c2_r0->dominantType, "nameCaptureInfo",
      13, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c2_i3);
    sf_mex_addfield(c2_m0, sf_mex_create(c2_r0->resolved, "nameCaptureInfo", 13,
      0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved",
                    "nameCaptureInfo", c2_i3);
    sf_mex_addfield(c2_m0, sf_mex_create(&c2_r0->fileLength, "nameCaptureInfo",
      7, 0U, 0U, 0), "fileLength", "nameCaptureInfo", c2_i3);
    sf_mex_addfield(c2_m0, sf_mex_create(&c2_r0->fileTime1, "nameCaptureInfo", 7,
      0U, 0U, 0), "fileTime1", "nameCaptureInfo", c2_i3);
    sf_mex_addfield(c2_m0, sf_mex_create(&c2_r0->fileTime2, "nameCaptureInfo", 7,
      0U, 0U, 0), "fileTime2", "nameCaptureInfo", c2_i3);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[66])
{
  c2_info[0].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/polyfun/interp1.m";
  c2_info[0].name = "eml_guarded_nan";
  c2_info[0].dominantType = "";
  c2_info[0].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c2_info[0].fileLength = 485U;
  c2_info[0].fileTime1 = 1192466780U;
  c2_info[0].fileTime2 = 0U;
  c2_info[1].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/polyfun/interp1.m/reshape_output";
  c2_info[1].name = "reshape";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/reshape.m";
  c2_info[1].fileLength = 1840U;
  c2_info[1].fileTime1 = 1192466754U;
  c2_info[1].fileTime2 = 0U;
  c2_info[2].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_check_dim.m";
  c2_info[2].name = "intmax";
  c2_info[2].dominantType = "char";
  c2_info[2].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[2].fileLength = 1535U;
  c2_info[2].fileTime1 = 1192466728U;
  c2_info[2].fileTime2 = 0U;
  c2_info[3].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[3].name = "isnumeric";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved = "[B]isnumeric";
  c2_info[3].fileLength = 0U;
  c2_info[3].fileTime1 = 0U;
  c2_info[3].fileTime2 = 0U;
  c2_info[4].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_alloc.m/zerosum";
  c2_info[4].name = "plus";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved = "[B]plus";
  c2_info[4].fileLength = 0U;
  c2_info[4].fileTime1 = 0U;
  c2_info[4].fileTime2 = 0U;
  c2_info[5].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[5].name = "isempty";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved = "[B]isempty";
  c2_info[5].fileLength = 0U;
  c2_info[5].fileTime1 = 0U;
  c2_info[5].fileTime2 = 0U;
  c2_info[6].context = "";
  c2_info[6].name = "mrdivide";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.m";
  c2_info[6].fileLength = 638U;
  c2_info[6].fileTime1 = 1197300750U;
  c2_info[6].fileTime2 = 0U;
  c2_info[7].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/datatypes/cast.m";
  c2_info[7].name = "uint32";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved = "[B]uint32";
  c2_info[7].fileLength = 0U;
  c2_info[7].fileTime1 = 0U;
  c2_info[7].fileTime2 = 0U;
  c2_info[8].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/datatypes/cast.m";
  c2_info[8].name = "ischar";
  c2_info[8].dominantType = "char";
  c2_info[8].resolved = "[B]ischar";
  c2_info[8].fileLength = 0U;
  c2_info[8].fileTime1 = 0U;
  c2_info[8].fileTime2 = 0U;
  c2_info[9].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[9].name = "eml_set_singleton_dim";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_set_singleton_dim.m";
  c2_info[9].fileLength = 375U;
  c2_info[9].fileTime1 = 1192466806U;
  c2_info[9].fileTime2 = 0U;
  c2_info[10].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c2_info[10].name = "nan";
  c2_info[10].dominantType = "";
  c2_info[10].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/nan.m";
  c2_info[10].fileLength = 474U;
  c2_info[10].fileTime1 = 1192466744U;
  c2_info[10].fileTime2 = 0U;
  c2_info[11].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[11].name = "eml_assert";
  c2_info[11].dominantType = "char";
  c2_info[11].resolved = "[B]eml_assert";
  c2_info[11].fileLength = 0U;
  c2_info[11].fileTime1 = 0U;
  c2_info[11].fileTime2 = 0U;
  c2_info[12].context = "";
  c2_info[12].name = "lt";
  c2_info[12].dominantType = "double";
  c2_info[12].resolved = "[B]lt";
  c2_info[12].fileLength = 0U;
  c2_info[12].fileTime1 = 0U;
  c2_info[12].fileTime2 = 0U;
  c2_info[13].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[13].name = "size";
  c2_info[13].dominantType = "double";
  c2_info[13].resolved = "[B]size";
  c2_info[13].fileLength = 0U;
  c2_info[13].fileTime1 = 0U;
  c2_info[13].fileTime2 = 0U;
  c2_info[14].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[14].name = "floor";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[14].fileLength = 550U;
  c2_info[14].fileTime1 = 1192466686U;
  c2_info[14].fileTime2 = 0U;
  c2_info[15].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c2_info[15].name = "islogical";
  c2_info[15].dominantType = "logical";
  c2_info[15].resolved = "[B]islogical";
  c2_info[15].fileLength = 0U;
  c2_info[15].fileTime1 = 0U;
  c2_info[15].fileTime2 = 0U;
  c2_info[16].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/datatypes/cast.m";
  c2_info[16].name = "double";
  c2_info[16].dominantType = "double";
  c2_info[16].resolved = "[B]double";
  c2_info[16].fileLength = 0U;
  c2_info[16].fileTime1 = 0U;
  c2_info[16].fileTime2 = 0U;
  c2_info[17].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[17].name = "isreal";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved = "[B]isreal";
  c2_info[17].fileLength = 0U;
  c2_info[17].fileTime1 = 0U;
  c2_info[17].fileTime2 = 0U;
  c2_info[18].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[18].name = "eml_warning";
  c2_info[18].dominantType = "char";
  c2_info[18].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c2_info[18].fileLength = 265U;
  c2_info[18].fileTime1 = 1192466814U;
  c2_info[18].fileTime2 = 0U;
  c2_info[19].context = "";
  c2_info[19].name = "mpower";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[19].fileLength = 3338U;
  c2_info[19].fileTime1 = 1192466918U;
  c2_info[19].fileTime2 = 0U;
  c2_info[20].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m/assert_integral";
  c2_info[20].name = "ne";
  c2_info[20].dominantType = "double";
  c2_info[20].resolved = "[B]ne";
  c2_info[20].fileLength = 0U;
  c2_info[20].fileTime1 = 0U;
  c2_info[20].fileTime2 = 0U;
  c2_info[21].context = "";
  c2_info[21].name = "mtimes";
  c2_info[21].dominantType = "double";
  c2_info[21].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[21].fileLength = 1990U;
  c2_info[21].fileTime1 = 1197652350U;
  c2_info[21].fileTime2 = 0U;
  c2_info[22].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_alloc.m";
  c2_info[22].name = "eml_assert_valid_size_arg";
  c2_info[22].dominantType = "double";
  c2_info[22].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[22].fileLength = 1360U;
  c2_info[22].fileTime1 = 1192466766U;
  c2_info[22].fileTime2 = 0U;
  c2_info[23].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_alloc.m/zerosum";
  c2_info[23].name = "cast";
  c2_info[23].dominantType = "double";
  c2_info[23].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/datatypes/cast.m";
  c2_info[23].fileLength = 866U;
  c2_info[23].fileTime1 = 1192466644U;
  c2_info[23].fileTime2 = 0U;
  c2_info[24].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/polyfun/interp1.m/interp1_work";
  c2_info[24].name = "eml_bsearch";
  c2_info[24].dominantType = "double";
  c2_info[24].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_bsearch.m";
  c2_info[24].fileLength = 1802U;
  c2_info[24].fileTime1 = 1192466768U;
  c2_info[24].fileTime2 = 0U;
  c2_info[25].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/polyfun/interp1.m/interp1_work";
  c2_info[25].name = "uminus";
  c2_info[25].dominantType = "double";
  c2_info[25].resolved = "[B]uminus";
  c2_info[25].fileLength = 0U;
  c2_info[25].fileTime1 = 0U;
  c2_info[25].fileTime2 = 0U;
  c2_info[26].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[26].name = "eml_scalexp_size";
  c2_info[26].dominantType = "double";
  c2_info[26].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_size.m";
  c2_info[26].fileLength = 872U;
  c2_info[26].fileTime1 = 1192466806U;
  c2_info[26].fileTime2 = 0U;
  c2_info[27].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[27].name = "class";
  c2_info[27].dominantType = "double";
  c2_info[27].resolved = "[B]class";
  c2_info[27].fileLength = 0U;
  c2_info[27].fileTime1 = 0U;
  c2_info[27].fileTime2 = 0U;
  c2_info[28].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[28].name = "eq";
  c2_info[28].dominantType = "double";
  c2_info[28].resolved = "[B]eq";
  c2_info[28].fileLength = 0U;
  c2_info[28].fileTime1 = 0U;
  c2_info[28].fileTime2 = 0U;
  c2_info[29].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/datatypes/cast.m";
  c2_info[29].name = "ge";
  c2_info[29].dominantType = "double";
  c2_info[29].resolved = "[B]ge";
  c2_info[29].fileLength = 0U;
  c2_info[29].fileTime1 = 0U;
  c2_info[29].fileTime2 = 0U;
  c2_info[30].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[30].name = "isscalar";
  c2_info[30].dominantType = "double";
  c2_info[30].resolved = "[B]isscalar";
  c2_info[30].fileLength = 0U;
  c2_info[30].fileTime1 = 0U;
  c2_info[30].fileTime2 = 0U;
  c2_info[31].context = "";
  c2_info[31].name = "gt";
  c2_info[31].dominantType = "double";
  c2_info[31].resolved = "[B]gt";
  c2_info[31].fileLength = 0U;
  c2_info[31].fileTime1 = 0U;
  c2_info[31].fileTime2 = 0U;
  c2_info[32].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/polyfun/interp1.m/interp1_work";
  c2_info[32].name = "any";
  c2_info[32].dominantType = "logical";
  c2_info[32].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/any.m";
  c2_info[32].fileLength = 400U;
  c2_info[32].fileTime1 = 1192466906U;
  c2_info[32].fileTime2 = 0U;
  c2_info[33].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[33].name = "ndims";
  c2_info[33].dominantType = "double";
  c2_info[33].resolved = "[B]ndims";
  c2_info[33].fileLength = 0U;
  c2_info[33].fileTime1 = 0U;
  c2_info[33].fileTime2 = 0U;
  c2_info[34].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_alloc.m";
  c2_info[34].name = "zeros";
  c2_info[34].dominantType = "double";
  c2_info[34].resolved = "[B]zeros";
  c2_info[34].fileLength = 0U;
  c2_info[34].fileTime1 = 0U;
  c2_info[34].fileTime2 = 0U;
  c2_info[35].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_bsearch.m";
  c2_info[35].name = "eml_unsigned_class";
  c2_info[35].dominantType = "char";
  c2_info[35].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c2_info[35].fileLength = 526U;
  c2_info[35].fileTime1 = 1192466810U;
  c2_info[35].fileTime2 = 0U;
  c2_info[36].context = "";
  c2_info[36].name = "minus";
  c2_info[36].dominantType = "double";
  c2_info[36].resolved = "[B]minus";
  c2_info[36].fileLength = 0U;
  c2_info[36].fileTime1 = 0U;
  c2_info[36].fileTime2 = 0U;
  c2_info[37].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[37].name = "isvector";
  c2_info[37].dominantType = "double";
  c2_info[37].resolved = "[B]isvector";
  c2_info[37].fileLength = 0U;
  c2_info[37].fileTime1 = 0U;
  c2_info[37].fileTime2 = 0U;
  c2_info[38].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[38].name = "eml_div";
  c2_info[38].dominantType = "double";
  c2_info[38].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[38].fileLength = 4254U;
  c2_info[38].fileTime1 = 1192466772U;
  c2_info[38].fileTime2 = 0U;
  c2_info[39].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_check_dim.m";
  c2_info[39].name = "nargout";
  c2_info[39].dominantType = "";
  c2_info[39].resolved = "[B]nargout";
  c2_info[39].fileLength = 0U;
  c2_info[39].fileTime1 = 0U;
  c2_info[39].fileTime2 = 0U;
  c2_info[40].context = "";
  c2_info[40].name = "pi";
  c2_info[40].dominantType = "";
  c2_info[40].resolved = "[B]pi";
  c2_info[40].fileLength = 0U;
  c2_info[40].fileTime1 = 0U;
  c2_info[40].fileTime2 = 0U;
  c2_info[41].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m/assert_integral";
  c2_info[41].name = "not";
  c2_info[41].dominantType = "logical";
  c2_info[41].resolved = "[B]not";
  c2_info[41].fileLength = 0U;
  c2_info[41].fileTime1 = 0U;
  c2_info[41].fileTime2 = 0U;
  c2_info[42].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_size.m";
  c2_info[42].name = "eml_scalexp_compatible";
  c2_info[42].dominantType = "double";
  c2_info[42].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[42].fileLength = 376U;
  c2_info[42].fileTime1 = 1192466804U;
  c2_info[42].fileTime2 = 0U;
  c2_info[43].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/polyfun/interp1.m/interp1_work";
  c2_info[43].name = "eml_index_plus";
  c2_info[43].dominantType = "int32";
  c2_info[43].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[43].fileLength = 272U;
  c2_info[43].fileTime1 = 1192466786U;
  c2_info[43].fileTime2 = 0U;
  c2_info[44].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/false.m";
  c2_info[44].name = "eml_varargin_to_size";
  c2_info[44].dominantType = "double";
  c2_info[44].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_varargin_to_size.m";
  c2_info[44].fileLength = 625U;
  c2_info[44].fileTime1 = 1192466812U;
  c2_info[44].fileTime2 = 0U;
  c2_info[45].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[45].name = "strcmp";
  c2_info[45].dominantType = "char";
  c2_info[45].resolved = "[B]strcmp";
  c2_info[45].fileLength = 0U;
  c2_info[45].fileTime1 = 0U;
  c2_info[45].fileTime2 = 0U;
  c2_info[46].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[46].name = "eml_alloc";
  c2_info[46].dominantType = "double";
  c2_info[46].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_alloc.m";
  c2_info[46].fileLength = 2558U;
  c2_info[46].fileTime1 = 1197300744U;
  c2_info[46].fileTime2 = 0U;
  c2_info[47].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[47].name = "eml_check_dim";
  c2_info[47].dominantType = "double";
  c2_info[47].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_check_dim.m";
  c2_info[47].fileLength = 1434U;
  c2_info[47].fileTime1 = 1192466768U;
  c2_info[47].fileTime2 = 0U;
  c2_info[48].context = "";
  c2_info[48].name = "interp1";
  c2_info[48].dominantType = "double";
  c2_info[48].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/polyfun/interp1.m";
  c2_info[48].fileLength = 6118U;
  c2_info[48].fileTime1 = 1192466924U;
  c2_info[48].fileTime2 = 0U;
  c2_info[49].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[49].name = "nargin";
  c2_info[49].dominantType = "";
  c2_info[49].resolved = "[B]nargin";
  c2_info[49].fileLength = 0U;
  c2_info[49].fileTime1 = 0U;
  c2_info[49].fileTime2 = 0U;
  c2_info[50].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[50].name = "isinteger";
  c2_info[50].dominantType = "double";
  c2_info[50].resolved = "[B]isinteger";
  c2_info[50].fileLength = 0U;
  c2_info[50].fileTime1 = 0U;
  c2_info[50].fileTime2 = 0U;
  c2_info[51].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.m";
  c2_info[51].name = "rdivide";
  c2_info[51].dominantType = "double";
  c2_info[51].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[51].fileLength = 628U;
  c2_info[51].fileTime1 = 1192466922U;
  c2_info[51].fileTime2 = 0U;
  c2_info[52].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_check_dim.m";
  c2_info[52].name = "le";
  c2_info[52].dominantType = "int32";
  c2_info[52].resolved = "[B]le";
  c2_info[52].fileLength = 0U;
  c2_info[52].fileTime1 = 0U;
  c2_info[52].fileTime2 = 0U;
  c2_info[53].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_bsearch.m";
  c2_info[53].name = "ones";
  c2_info[53].dominantType = "char";
  c2_info[53].resolved = "[B]ones";
  c2_info[53].fileLength = 0U;
  c2_info[53].fileTime1 = 0U;
  c2_info[53].fileTime2 = 0U;
  c2_info[54].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/true.m";
  c2_info[54].name = "logical";
  c2_info[54].dominantType = "double";
  c2_info[54].resolved = "[B]logical";
  c2_info[54].fileLength = 0U;
  c2_info[54].fileTime1 = 0U;
  c2_info[54].fileTime2 = 0U;
  c2_info[55].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m/assert_integral";
  c2_info[55].name = "true";
  c2_info[55].dominantType = "";
  c2_info[55].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/true.m";
  c2_info[55].fileLength = 237U;
  c2_info[55].fileTime1 = 1192466762U;
  c2_info[55].fileTime2 = 0U;
  c2_info[56].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[56].name = "isa";
  c2_info[56].dominantType = "double";
  c2_info[56].resolved = "[B]isa";
  c2_info[56].fileLength = 0U;
  c2_info[56].fileTime1 = 0U;
  c2_info[56].fileTime2 = 0U;
  c2_info[57].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[57].name = "eml_nonsingleton_dim";
  c2_info[57].dominantType = "logical";
  c2_info[57].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_nonsingleton_dim.m";
  c2_info[57].fileLength = 404U;
  c2_info[57].fileTime1 = 1192466800U;
  c2_info[57].fileTime2 = 0U;
  c2_info[58].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m/assert_integral";
  c2_info[58].name = "false";
  c2_info[58].dominantType = "";
  c2_info[58].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/false.m";
  c2_info[58].fileLength = 238U;
  c2_info[58].fileTime1 = 1192466720U;
  c2_info[58].fileTime2 = 0U;
  c2_info[59].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[59].name = "power";
  c2_info[59].dominantType = "double";
  c2_info[59].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[59].fileLength = 4979U;
  c2_info[59].fileTime1 = 1192466920U;
  c2_info[59].fileTime2 = 0U;
  c2_info[60].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[60].name = "int32";
  c2_info[60].dominantType = "double";
  c2_info[60].resolved = "[B]int32";
  c2_info[60].fileLength = 0U;
  c2_info[60].fileTime1 = 0U;
  c2_info[60].fileTime2 = 0U;
  c2_info[61].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_check_dim.m";
  c2_info[61].name = "eml_index_class";
  c2_info[61].dominantType = "";
  c2_info[61].resolved =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[61].fileLength = 909U;
  c2_info[61].fileTime1 = 1192466782U;
  c2_info[61].fileTime2 = 0U;
  c2_info[62].context = "[I]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_alloc.m";
  c2_info[62].name = "isstruct";
  c2_info[62].dominantType = "double";
  c2_info[62].resolved = "[B]isstruct";
  c2_info[62].fileLength = 0U;
  c2_info[62].fileTime1 = 0U;
  c2_info[62].fileTime2 = 0U;
  c2_info[63].context =
    "[I]$matlabroot$/toolbox/eml/lib/matlab/polyfun/interp1.m/interp1_work";
  c2_info[63].name = "isnan";
  c2_info[63].dominantType = "double";
  c2_info[63].resolved = "[I]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[63].fileLength = 472U;
  c2_info[63].fileTime1 = 1192466736U;
  c2_info[63].fileTime2 = 0U;
}

static void init_dsm_address_info(void)
{
}

/* SFunction Glue Code */
void sf_c2_NonLinearModel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(178247359U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(548201267U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3878692077U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(109214889U);
}

mxArray *sf_c2_NonLinearModel_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(1606954985U);
    pr[1] = (double)(4059923409U);
    pr[2] = (double)(3040205467U);
    pr[3] = (double)(69728845U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "aliasId", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,3,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"aliasId",mxCreateDoubleScalar(0));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  return(mxAutoinheritanceInfo);
}

static void sf_opaque_initialize_c2_NonLinearModel(void *chartInstanceVar)
{
  initialize_params_c2_NonLinearModel();
  initialize_c2_NonLinearModel();
}

static void sf_opaque_enable_c2_NonLinearModel(void *chartInstanceVar)
{
  enable_c2_NonLinearModel();
}

static void sf_opaque_disable_c2_NonLinearModel(void *chartInstanceVar)
{
  disable_c2_NonLinearModel();
}

static void sf_opaque_gateway_c2_NonLinearModel(void *chartInstanceVar)
{
  sf_c2_NonLinearModel();
}

static void sf_opaque_terminate_c2_NonLinearModel(void *chartInstanceVar)
{
  if (sim_mode_is_rtw_gen(chartInstance.S) || sim_mode_is_external
      (chartInstance.S)) {
    sf_clear_rtw_identifier(chartInstance.S);
  }

  finalize_c2_NonLinearModel();
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_NonLinearModel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_NonLinearModel();
  }
}

static void mdlSetWorkWidths_c2_NonLinearModel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable("NonLinearModel","NonLinearModel",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop("NonLinearModel","NonLinearModel",2,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop("NonLinearModel",
      "NonLinearModel",2,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"NonLinearModel","NonLinearModel",2,
        8);
      sf_mark_chart_reusable_outputs(S,"NonLinearModel","NonLinearModel",2,6);
    }

    sf_set_rtw_dwork_info(S,"NonLinearModel","NonLinearModel",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
    ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  }

  ssSetChecksum0(S,(3028321274U));
  ssSetChecksum1(S,(4093281636U));
  ssSetChecksum2(S,(1438963440U));
  ssSetChecksum3(S,(3303492703U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_NonLinearModel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "NonLinearModel", "NonLinearModel",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_NonLinearModel(SimStruct *S)
{
  chartInstance.chartInfo.chartInstance = NULL;
  chartInstance.chartInfo.isEMLChart = 1;
  chartInstance.chartInfo.chartInitialized = 0;
  chartInstance.chartInfo.sFunctionGateway = sf_opaque_gateway_c2_NonLinearModel;
  chartInstance.chartInfo.initializeChart =
    sf_opaque_initialize_c2_NonLinearModel;
  chartInstance.chartInfo.terminateChart = sf_opaque_terminate_c2_NonLinearModel;
  chartInstance.chartInfo.enableChart = sf_opaque_enable_c2_NonLinearModel;
  chartInstance.chartInfo.disableChart = sf_opaque_disable_c2_NonLinearModel;
  chartInstance.chartInfo.zeroCrossings = NULL;
  chartInstance.chartInfo.outputs = NULL;
  chartInstance.chartInfo.derivatives = NULL;
  chartInstance.chartInfo.mdlRTW = mdlRTW_c2_NonLinearModel;
  chartInstance.chartInfo.mdlStart = mdlStart_c2_NonLinearModel;
  chartInstance.chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_NonLinearModel;
  chartInstance.chartInfo.extModeExec = NULL;
  chartInstance.chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance.chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance.chartInfo.storeCurrentConfiguration = NULL;
  chartInstance.S = S;
  ssSetUserData(S,(void *)(&(chartInstance.chartInfo)));/* register the chart instance with simstruct */
  if (!sim_mode_is_rtw_gen(S)) {
    init_dsm_address_info();
  }
}

void c2_NonLinearModel_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_NonLinearModel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_NonLinearModel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_NonLinearModel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_NonLinearModel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
