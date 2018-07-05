/* Include files */

#include "Turbine_State_Machine_Lib_sfun.h"
#include "c1_Turbine_State_Machine_Lib.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Turbine_State_Machine_Lib_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c1_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c1_IN_Brake                    ((uint8_T)1U)
#define c1_IN_Generating               ((uint8_T)2U)
#define c1_IN_Park                     ((uint8_T)3U)
#define c1_IN_Startup                  ((uint8_T)4U)
#define c1_const_park_speed            (5.0)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void initialize_params_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void enable_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void disable_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void ext_mode_exec_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void set_sim_state_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_st);
static void c1_set_sim_state_side_effects_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void finalize_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void sf_gateway_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void mdl_start_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void c1_chartstep_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void initSimStructsc1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static int32_T c1_emlrt_marshallIn(SFc1_Turbine_State_Machine_LibInstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_b_emlrt_marshallIn(SFc1_Turbine_State_Machine_LibInstanceStruct
  *chartInstance, const mxArray *c1_b_pitch_brake, const char_T *c1_identifier);
static real_T c1_c_emlrt_marshallIn(SFc1_Turbine_State_Machine_LibInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_d_emlrt_marshallIn
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_b_is_active_c1_Turbine_State_Machine_Lib, const char_T *c1_identifier);
static uint8_T c1_e_emlrt_marshallIn
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_u, const emlrtMsgIdentifier *c1_parentId);
static const mxArray *c1_f_emlrt_marshallIn
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_b_setSimStateSideEffectsInfo, const char_T *c1_identifier);
static const mxArray *c1_g_emlrt_marshallIn
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_u, const emlrtMsgIdentifier *c1_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, int32_T c1_ssid);
static void c1_init_sf_message_store_memory
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);
static void init_dsm_address_info(SFc1_Turbine_State_Machine_LibInstanceStruct
  *chartInstance);
static void init_simulink_io_address
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc1_Turbine_State_Machine_Lib(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  *chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_doSetSimStateSideEffects = 0U;
  chartInstance->c1_setSimStateSideEffectsInfo = NULL;
  *chartInstance->c1_is_active_c1_Turbine_State_Machine_Lib = 0U;
  *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_NO_ACTIVE_CHILD;
  *chartInstance->c1_wind_speed_cut_in_lower = 4.0;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_wind_speed_cut_in_lower, 2U, 1U, 0U, *
                        chartInstance->c1_sfEvent, false);
  *chartInstance->c1_turbine_speed_cut_in = 1200.0;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_speed_cut_in, 0U, 1U, 0U,
                        *chartInstance->c1_sfEvent, false);
  *chartInstance->c1_wind_speed_cut_out = 20.0;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_wind_speed_cut_out, 4U, 1U, 0U,
                        *chartInstance->c1_sfEvent, false);
  *chartInstance->c1_wind_speed_cut_in_upper = 18.0;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_wind_speed_cut_in_upper, 3U, 1U, 0U, *
                        chartInstance->c1_sfEvent, false);
  *chartInstance->c1_turbine_speed_cut_out = 2200.0;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_speed_cut_out, 1U, 1U, 0U,
                        *chartInstance->c1_sfEvent, false);
  chartInstance->c1_park_speed = 5.0;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_park_speed, 11U, 1U, 0U,
                        *chartInstance->c1_sfEvent, false);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c1_pitch_brake = 0.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_pitch_brake, 7U, 1U, 0U,
                          *chartInstance->c1_sfEvent, false);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c1_parking_brake = 0.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_parking_brake, 8U, 1U, 0U,
                          *chartInstance->c1_sfEvent, false);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c1_generator_trip = 0.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_generator_trip, 9U, 1U, 0U,
                          *chartInstance->c1_sfEvent, false);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 4) != 0)) {
    *chartInstance->c1_turbine_state = 0.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_state, 10U, 1U, 0U,
                          *chartInstance->c1_sfEvent, false);
  }
}

static void initialize_params_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  uint32_T c1_prevAniVal;
  c1_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*chartInstance->c1_is_active_c1_Turbine_State_Machine_Lib == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
  }

  if (*chartInstance->c1_is_c1_Turbine_State_Machine_Lib == c1_IN_Generating) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c1_sfEvent);
  }

  if (*chartInstance->c1_is_c1_Turbine_State_Machine_Lib == c1_IN_Startup) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c1_sfEvent);
  }

  if (*chartInstance->c1_is_c1_Turbine_State_Machine_Lib == c1_IN_Park) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c1_sfEvent);
  }

  if (*chartInstance->c1_is_c1_Turbine_State_Machine_Lib == c1_IN_Brake) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
  }

  _SFD_SET_ANIMATION(c1_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  c1_update_debugger_state_c1_Turbine_State_Machine_Lib(chartInstance);
}

static const mxArray *get_sim_state_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  real_T c1_f_hoistedGlobal;
  real_T c1_f_u;
  const mxArray *c1_g_y = NULL;
  real_T c1_g_hoistedGlobal;
  real_T c1_g_u;
  const mxArray *c1_h_y = NULL;
  real_T c1_h_hoistedGlobal;
  real_T c1_h_u;
  const mxArray *c1_i_y = NULL;
  real_T c1_i_hoistedGlobal;
  real_T c1_i_u;
  const mxArray *c1_j_y = NULL;
  uint8_T c1_j_hoistedGlobal;
  uint8_T c1_j_u;
  const mxArray *c1_k_y = NULL;
  uint8_T c1_k_hoistedGlobal;
  uint8_T c1_k_u;
  const mxArray *c1_l_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(11, 1), false);
  c1_hoistedGlobal = *chartInstance->c1_generator_trip;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *chartInstance->c1_parking_brake;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *chartInstance->c1_pitch_brake;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *chartInstance->c1_turbine_state;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = *chartInstance->c1_turbine_speed_cut_in;
  c1_e_u = c1_e_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_f_hoistedGlobal = *chartInstance->c1_turbine_speed_cut_out;
  c1_f_u = c1_f_hoistedGlobal;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_g_hoistedGlobal = *chartInstance->c1_wind_speed_cut_in_lower;
  c1_g_u = c1_g_hoistedGlobal;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_h_hoistedGlobal = *chartInstance->c1_wind_speed_cut_in_upper;
  c1_h_u = c1_h_hoistedGlobal;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_i_hoistedGlobal = *chartInstance->c1_wind_speed_cut_out;
  c1_i_u = c1_i_hoistedGlobal;
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_j_hoistedGlobal = *chartInstance->c1_is_active_c1_Turbine_State_Machine_Lib;
  c1_j_u = c1_j_hoistedGlobal;
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_k_hoistedGlobal = *chartInstance->c1_is_c1_Turbine_State_Machine_Lib;
  c1_k_u = c1_k_hoistedGlobal;
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_k_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 10, c1_l_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_st)
{
  const mxArray *c1_u;
  c1_u = sf_mex_dup(c1_st);
  *chartInstance->c1_generator_trip = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("generator_trip", c1_u, 0)), "generator_trip");
  *chartInstance->c1_parking_brake = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("parking_brake", c1_u, 1)), "parking_brake");
  *chartInstance->c1_pitch_brake = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("pitch_brake", c1_u, 2)), "pitch_brake");
  *chartInstance->c1_turbine_state = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("turbine_state", c1_u, 3)), "turbine_state");
  *chartInstance->c1_turbine_speed_cut_in = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("turbine_speed_cut_in", c1_u, 4)),
    "turbine_speed_cut_in");
  *chartInstance->c1_turbine_speed_cut_out = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("turbine_speed_cut_out", c1_u, 5)),
    "turbine_speed_cut_out");
  *chartInstance->c1_wind_speed_cut_in_lower = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("wind_speed_cut_in_lower", c1_u, 6)),
     "wind_speed_cut_in_lower");
  *chartInstance->c1_wind_speed_cut_in_upper = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("wind_speed_cut_in_upper", c1_u, 7)),
     "wind_speed_cut_in_upper");
  *chartInstance->c1_wind_speed_cut_out = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("wind_speed_cut_out", c1_u, 8)),
    "wind_speed_cut_out");
  *chartInstance->c1_is_active_c1_Turbine_State_Machine_Lib =
    c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "is_active_c1_Turbine_State_Machine_Lib", c1_u, 9)),
    "is_active_c1_Turbine_State_Machine_Lib");
  *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_c1_Turbine_State_Machine_Lib",
       c1_u, 10)), "is_c1_Turbine_State_Machine_Lib");
  sf_mex_assign(&chartInstance->c1_setSimStateSideEffectsInfo,
                c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "setSimStateSideEffectsInfo", c1_u, 11)), "setSimStateSideEffectsInfo"),
                true);
  sf_mex_destroy(&c1_u);
  chartInstance->c1_doSetSimStateSideEffects = 1U;
  c1_update_debugger_state_c1_Turbine_State_Machine_Lib(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void c1_set_sim_state_side_effects_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  if (chartInstance->c1_doSetSimStateSideEffects != 0) {
    chartInstance->c1_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c1_setSimStateSideEffectsInfo);
}

static void sf_gateway_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  c1_set_sim_state_side_effects_c1_Turbine_State_Machine_Lib(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, *chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_speed, 6U, 1U, 0U,
                        *chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_wind_speed, 5U, 1U, 0U,
                        *chartInstance->c1_sfEvent, false);
  *chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_Turbine_State_Machine_Lib(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_Turbine_State_Machine_LibMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  c1_init_sf_message_store_memory(chartInstance);
}

static void c1_chartstep_c1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  boolean_T c1_out;
  boolean_T c1_temp;
  boolean_T c1_b_temp;
  boolean_T c1_b_out;
  boolean_T c1_c_temp;
  boolean_T c1_d_temp;
  boolean_T c1_c_out;
  boolean_T c1_d_out;
  boolean_T c1_e_out;
  boolean_T c1_e_temp;
  boolean_T c1_f_out;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, *chartInstance->c1_sfEvent);
  if (*chartInstance->c1_is_active_c1_Turbine_State_Machine_Lib == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, *chartInstance->c1_sfEvent);
    *chartInstance->c1_is_active_c1_Turbine_State_Machine_Lib = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, *chartInstance->c1_sfEvent);
    *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_Park;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c1_sfEvent);
    *chartInstance->c1_parking_brake = 1.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_parking_brake, 8U, 4U, 2U,
                          *chartInstance->c1_sfEvent, false);
    *chartInstance->c1_generator_trip = 1.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_generator_trip, 9U, 4U, 2U,
                          *chartInstance->c1_sfEvent, false);
    *chartInstance->c1_pitch_brake = 1.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_pitch_brake, 7U, 4U, 2U,
                          *chartInstance->c1_sfEvent, false);
    *chartInstance->c1_turbine_state = 0.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_state, 10U, 4U, 2U,
                          *chartInstance->c1_sfEvent, false);
  } else {
    switch (*chartInstance->c1_is_c1_Turbine_State_Machine_Lib) {
     case c1_IN_Brake:
      CV_CHART_EVAL(0, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                   *chartInstance->c1_sfEvent);
      c1_out = (CV_TRANSITION_EVAL(4U, (int32_T)_SFD_CCP_CALL(4U, 0,
                  CV_RELATIONAL_EVAL(5U, 4U, 0, *chartInstance->c1_turbine_speed,
        c1_const_park_speed, -1, 3U, *chartInstance->c1_turbine_speed <=
        c1_const_park_speed) != 0U, *chartInstance->c1_sfEvent)) != 0);
      if (c1_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, *chartInstance->c1_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
        *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_Park;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c1_sfEvent);
        *chartInstance->c1_parking_brake = 1.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_parking_brake, 8U, 4U, 2U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_generator_trip = 1.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_generator_trip, 9U, 4U, 2U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_pitch_brake = 1.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_pitch_brake, 7U, 4U, 2U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_turbine_state = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_state, 10U, 4U, 2U,
                              *chartInstance->c1_sfEvent, false);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                     *chartInstance->c1_sfEvent);
        c1_c_temp = (_SFD_CCP_CALL(6U, 0, CV_RELATIONAL_EVAL(5U, 6U, 0,
          *chartInstance->c1_wind_speed,
          *chartInstance->c1_wind_speed_cut_in_upper, -1, 2U,
          *chartInstance->c1_wind_speed <
          *chartInstance->c1_wind_speed_cut_in_upper) != 0U,
          *chartInstance->c1_sfEvent) != 0);
        if (c1_c_temp) {
          c1_c_temp = (_SFD_CCP_CALL(6U, 1, CV_RELATIONAL_EVAL(5U, 6U, 1,
            *chartInstance->c1_wind_speed,
            *chartInstance->c1_wind_speed_cut_in_lower, -1, 4U,
            *chartInstance->c1_wind_speed >
            *chartInstance->c1_wind_speed_cut_in_lower) != 0U,
            *chartInstance->c1_sfEvent) != 0);
        }

        c1_e_out = (CV_TRANSITION_EVAL(6U, (int32_T)c1_c_temp) != 0);
        if (c1_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, *chartInstance->c1_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
          *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_Startup;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c1_sfEvent);
          *chartInstance->c1_parking_brake = 0.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_parking_brake, 8U, 4U, 3U,
                                *chartInstance->c1_sfEvent, false);
          *chartInstance->c1_generator_trip = 1.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_generator_trip, 9U, 4U, 3U,
                                *chartInstance->c1_sfEvent, false);
          *chartInstance->c1_pitch_brake = 0.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_pitch_brake, 7U, 4U, 3U,
                                *chartInstance->c1_sfEvent, false);
          *chartInstance->c1_turbine_state = 1.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_state, 10U, 4U, 3U,
                                *chartInstance->c1_sfEvent, false);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                       *chartInstance->c1_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c1_sfEvent);
      break;

     case c1_IN_Generating:
      CV_CHART_EVAL(0, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                   *chartInstance->c1_sfEvent);
      c1_temp = (_SFD_CCP_CALL(3U, 0, CV_RELATIONAL_EVAL(5U, 3U, 0,
        *chartInstance->c1_wind_speed,
        *chartInstance->c1_wind_speed_cut_in_lower, -1, 2U,
        *chartInstance->c1_wind_speed <
        *chartInstance->c1_wind_speed_cut_in_lower) != 0U,
                  *chartInstance->c1_sfEvent) != 0);
      if (!c1_temp) {
        c1_temp = (_SFD_CCP_CALL(3U, 1, CV_RELATIONAL_EVAL(5U, 3U, 1,
          *chartInstance->c1_wind_speed, *chartInstance->c1_wind_speed_cut_out,
          -1, 4U, *chartInstance->c1_wind_speed >
          *chartInstance->c1_wind_speed_cut_out) != 0U,
                    *chartInstance->c1_sfEvent) != 0);
      }

      c1_d_temp = c1_temp;
      if (!c1_d_temp) {
        c1_d_temp = (_SFD_CCP_CALL(3U, 2, CV_RELATIONAL_EVAL(5U, 3U, 2,
          *chartInstance->c1_turbine_speed,
          *chartInstance->c1_turbine_speed_cut_out, -1, 4U,
          *chartInstance->c1_turbine_speed >
          *chartInstance->c1_turbine_speed_cut_out) != 0U,
          *chartInstance->c1_sfEvent) != 0);
      }

      c1_e_temp = c1_d_temp;
      if (!c1_e_temp) {
        c1_e_temp = (_SFD_CCP_CALL(3U, 3, CV_RELATIONAL_EVAL(5U, 3U, 3,
          *chartInstance->c1_turbine_speed,
          *chartInstance->c1_turbine_speed_cut_in * 0.9, -1, 2U,
          *chartInstance->c1_turbine_speed <
          *chartInstance->c1_turbine_speed_cut_in * 0.9) != 0U,
          *chartInstance->c1_sfEvent) != 0);
      }

      c1_f_out = (CV_TRANSITION_EVAL(3U, (int32_T)c1_e_temp) != 0);
      if (c1_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *chartInstance->c1_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *chartInstance->c1_sfEvent);
        *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_Brake;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
        *chartInstance->c1_parking_brake = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_parking_brake, 8U, 4U, 0U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_generator_trip = 1.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_generator_trip, 9U, 4U, 0U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_pitch_brake = 1.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_pitch_brake, 7U, 4U, 0U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_turbine_state = 3.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_state, 10U, 4U, 0U,
                              *chartInstance->c1_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                     *chartInstance->c1_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *chartInstance->c1_sfEvent);
      break;

     case c1_IN_Park:
      CV_CHART_EVAL(0, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U,
                   *chartInstance->c1_sfEvent);
      c1_b_temp = (_SFD_CCP_CALL(0U, 0, CV_RELATIONAL_EVAL(5U, 0U, 0,
        *chartInstance->c1_wind_speed,
        *chartInstance->c1_wind_speed_cut_in_lower, -1, 4U,
        *chartInstance->c1_wind_speed >
        *chartInstance->c1_wind_speed_cut_in_lower) != 0U,
        *chartInstance->c1_sfEvent) != 0);
      if (c1_b_temp) {
        c1_b_temp = (_SFD_CCP_CALL(0U, 1, CV_RELATIONAL_EVAL(5U, 0U, 1,
          *chartInstance->c1_wind_speed, *chartInstance->c1_wind_speed_cut_out,
          -1, 2U, *chartInstance->c1_wind_speed <
          *chartInstance->c1_wind_speed_cut_out) != 0U,
          *chartInstance->c1_sfEvent) != 0);
      }

      c1_c_out = (CV_TRANSITION_EVAL(0U, (int32_T)c1_b_temp) != 0);
      if (c1_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c1_sfEvent);
        *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_Startup;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *chartInstance->c1_sfEvent);
        *chartInstance->c1_parking_brake = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_parking_brake, 8U, 4U, 3U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_generator_trip = 1.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_generator_trip, 9U, 4U, 3U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_pitch_brake = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_pitch_brake, 7U, 4U, 3U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_turbine_state = 1.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_state, 10U, 4U, 3U,
                              *chartInstance->c1_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                     *chartInstance->c1_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c1_sfEvent);
      break;

     case c1_IN_Startup:
      CV_CHART_EVAL(0, 0, 4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   *chartInstance->c1_sfEvent);
      c1_b_out = (CV_TRANSITION_EVAL(1U, (int32_T)_SFD_CCP_CALL(1U, 0,
        CV_RELATIONAL_EVAL(5U, 1U, 0, *chartInstance->c1_turbine_speed,
                           *chartInstance->c1_turbine_speed_cut_in, -1, 4U,
                           *chartInstance->c1_turbine_speed >
                           *chartInstance->c1_turbine_speed_cut_in) != 0U,
        *chartInstance->c1_sfEvent)) != 0);
      if (c1_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *chartInstance->c1_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c1_sfEvent);
        *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_Generating;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *chartInstance->c1_sfEvent);
        *chartInstance->c1_parking_brake = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_parking_brake, 8U, 4U, 1U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_generator_trip = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_generator_trip, 9U, 4U, 1U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_pitch_brake = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_pitch_brake, 7U, 4U, 1U,
                              *chartInstance->c1_sfEvent, false);
        *chartInstance->c1_turbine_state = 2.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_state, 10U, 4U, 1U,
                              *chartInstance->c1_sfEvent, false);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                     *chartInstance->c1_sfEvent);
        c1_d_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
          CV_RELATIONAL_EVAL(5U, 2U, 0, *chartInstance->c1_wind_speed,
                             *chartInstance->c1_wind_speed_cut_in_lower, -1, 2U,
                             *chartInstance->c1_wind_speed <
                             *chartInstance->c1_wind_speed_cut_in_lower) != 0U, *
          chartInstance->c1_sfEvent)) != 0);
        if (c1_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *chartInstance->c1_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *chartInstance->c1_sfEvent);
          *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_Brake;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
          *chartInstance->c1_parking_brake = 0.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_parking_brake, 8U, 4U, 0U,
                                *chartInstance->c1_sfEvent, false);
          *chartInstance->c1_generator_trip = 1.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_generator_trip, 9U, 4U, 0U,
                                *chartInstance->c1_sfEvent, false);
          *chartInstance->c1_pitch_brake = 1.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_pitch_brake, 7U, 4U, 0U,
                                *chartInstance->c1_sfEvent, false);
          *chartInstance->c1_turbine_state = 3.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_turbine_state, 10U, 4U, 0U,
                                *chartInstance->c1_sfEvent, false);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                       *chartInstance->c1_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, *chartInstance->c1_sfEvent);
      break;

     default:
      CV_CHART_EVAL(0, 0, 0);

      /* Unreachable state, for coverage only */
      *chartInstance->c1_is_c1_Turbine_State_Machine_Lib = c1_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c1_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c1_sfEvent);
}

static void initSimStructsc1_Turbine_State_Machine_Lib
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)c1_machineNumber;
  (void)c1_chartNumber;
  (void)c1_instanceNumber;
}

const mxArray *sf_c1_Turbine_State_Machine_Lib_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c1_nameCaptureInfo;
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance;
  chartInstance = (SFc1_Turbine_State_Machine_LibInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_emlrt_marshallIn(SFc1_Turbine_State_Machine_LibInstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i0, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance;
  chartInstance = (SFc1_Turbine_State_Machine_LibInstanceStruct *)
    chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent), &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance;
  chartInstance = (SFc1_Turbine_State_Machine_LibInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_b_emlrt_marshallIn(SFc1_Turbine_State_Machine_LibInstanceStruct
  *chartInstance, const mxArray *c1_b_pitch_brake, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_pitch_brake),
    &c1_thisId);
  sf_mex_destroy(&c1_b_pitch_brake);
  return c1_y;
}

static real_T c1_c_emlrt_marshallIn(SFc1_Turbine_State_Machine_LibInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_pitch_brake;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance;
  chartInstance = (SFc1_Turbine_State_Machine_LibInstanceStruct *)
    chartInstanceVoid;
  c1_b_pitch_brake = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_pitch_brake),
    &c1_thisId);
  sf_mex_destroy(&c1_b_pitch_brake);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_d_emlrt_marshallIn
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_b_is_active_c1_Turbine_State_Machine_Lib, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_Turbine_State_Machine_Lib), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_Turbine_State_Machine_Lib);
  return c1_y;
}

static uint8_T c1_e_emlrt_marshallIn
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static const mxArray *c1_f_emlrt_marshallIn
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_b_setSimStateSideEffectsInfo, const char_T *c1_identifier)
{
  const mxArray *c1_y = NULL;
  emlrtMsgIdentifier c1_thisId;
  c1_y = NULL;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  sf_mex_assign(&c1_y, c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_setSimStateSideEffectsInfo), &c1_thisId), false);
  sf_mex_destroy(&c1_b_setSimStateSideEffectsInfo);
  return c1_y;
}

static const mxArray *c1_g_emlrt_marshallIn
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, const mxArray
   *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  const mxArray *c1_y = NULL;
  (void)chartInstance;
  (void)c1_parentId;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), false);
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance, int32_T c1_ssid)
{
  (void)chartInstance;
  (void)c1_ssid;
  return NULL;
}

static void c1_init_sf_message_store_memory
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_dsm_address_info(SFc1_Turbine_State_Machine_LibInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address
  (SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = (int32_T *)ssGetDWork_wrapper(chartInstance->S, 0);
  chartInstance->c1_is_active_c1_Turbine_State_Machine_Lib = (uint8_T *)
    ssGetDWork_wrapper(chartInstance->S, 1);
  chartInstance->c1_is_c1_Turbine_State_Machine_Lib = (uint8_T *)
    ssGetDWork_wrapper(chartInstance->S, 2);
  chartInstance->c1_pitch_brake = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_wind_speed = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_turbine_speed = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_parking_brake = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_generator_trip = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_wind_speed_cut_in_lower = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_turbine_speed_cut_in = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_turbine_state = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_wind_speed_cut_out = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 5);
  chartInstance->c1_wind_speed_cut_in_upper = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 6);
  chartInstance->c1_turbine_speed_cut_out = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 7);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

static uint32_T* sf_get_sfun_dwork_checksum(void);
void sf_c1_Turbine_State_Machine_Lib_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3104155743U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2197987814U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(817187930U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3842614393U);
}

mxArray* sf_c1_Turbine_State_Machine_Lib_get_post_codegen_info(void);
mxArray *sf_c1_Turbine_State_Machine_Lib_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("YOiYUss4NLwRKsdmnvmVzF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo =
      sf_c1_Turbine_State_Machine_Lib_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_Turbine_State_Machine_Lib_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_Turbine_State_Machine_Lib_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("early");
  mxArray *fallbackReason = mxCreateString("ext_mode");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c1_Turbine_State_Machine_Lib_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_Turbine_State_Machine_Lib_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c1_Turbine_State_Machine_Lib(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[6],T\"generator_trip\",},{M[1],M[21],T\"parking_brake\",},{M[1],M[22],T\"pitch_brake\",},{M[1],M[27],T\"turbine_state\",},{M[3],M[25],T\"turbine_speed_cut_in\",},{M[3],M[33],T\"turbine_speed_cut_out\",},{M[3],M[23],T\"wind_speed_cut_in_lower\",},{M[3],M[32],T\"wind_speed_cut_in_upper\",},{M[3],M[29],T\"wind_speed_cut_out\",},{M[8],M[0],T\"is_active_c1_Turbine_State_Machine_Lib\",}}",
    "100 S'type','srcId','name','auxInfo'{{M[9],M[0],T\"is_c1_Turbine_State_Machine_Lib\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 11, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_Turbine_State_Machine_Lib_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg
    ( (SFc1_Turbine_State_Machine_LibInstanceStruct *) chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance =
      (SFc1_Turbine_State_Machine_LibInstanceStruct *)sf_get_chart_instance_ptr
      (S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _Turbine_State_Machine_LibMachineNumber_,
           1,
           4,
           7,
           0,
           12,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_Turbine_State_Machine_LibMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _Turbine_State_Machine_LibMachineNumber_,chartInstance->chartNumber,
             1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _Turbine_State_Machine_LibMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,0,0,0,"turbine_speed_cut_in");
          _SFD_SET_DATA_PROPS(1,0,0,0,"turbine_speed_cut_out");
          _SFD_SET_DATA_PROPS(2,0,0,0,"wind_speed_cut_in_lower");
          _SFD_SET_DATA_PROPS(3,0,0,0,"wind_speed_cut_in_upper");
          _SFD_SET_DATA_PROPS(4,0,0,0,"wind_speed_cut_out");
          _SFD_SET_DATA_PROPS(5,1,1,0,"wind_speed");
          _SFD_SET_DATA_PROPS(6,1,1,0,"turbine_speed");
          _SFD_SET_DATA_PROPS(7,2,0,1,"pitch_brake");
          _SFD_SET_DATA_PROPS(8,2,0,1,"parking_brake");
          _SFD_SET_DATA_PROPS(9,2,0,1,"generator_trip");
          _SFD_SET_DATA_PROPS(10,2,0,1,"turbine_state");
          _SFD_SET_DATA_PROPS(11,7,0,0,"park_speed");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_CH_SUBSTATE_COUNT(4);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,2);
          _SFD_CH_SUBSTATE_INDEX(3,3);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
        }

        _SFD_CV_INIT_CHART(4,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 39 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 39 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 45 };

          static unsigned int sEndGuardMap[] = { 39, 78 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(0,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 45 };

          static unsigned int sEndRelationalopMap[] = { 39, 78 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(0,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 39 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 39 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 46 };

          static unsigned int sEndGuardMap[] = { 39, 84 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(6,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 46 };

          static unsigned int sEndRelationalopMap[] = { 39, 84 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 2, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 45, 84, 129 };

          static unsigned int sEndGuardMap[] = { 39, 78, 123, 171 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2 };

          _SFD_CV_INIT_TRANS(3,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 45, 84, 129 };

          static unsigned int sEndRelationalopMap[] = { 39, 78, 123, 171 };

          static int sRelationalopEps[] = { -1, -1, -1, -1 };

          static int sRelationalopType[] = { 2, 4, 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(4,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(4,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _Turbine_State_Machine_LibMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance =
      (SFc1_Turbine_State_Machine_LibInstanceStruct *)sf_get_chart_instance_ptr
      (S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c1_pitch_brake);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c1_wind_speed);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c1_turbine_speed);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c1_parking_brake);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c1_generator_trip);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c1_wind_speed_cut_in_lower);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c1_turbine_speed_cut_in);
        _SFD_SET_DATA_VALUE_PTR(10U, chartInstance->c1_turbine_state);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c1_wind_speed_cut_out);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c1_wind_speed_cut_in_upper);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c1_turbine_speed_cut_out);
        _SFD_SET_DATA_VALUE_PTR(11U, &chartInstance->c1_park_speed);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sdlP5iItgydjf2rvHB6kg4D";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_Turbine_State_Machine_Lib_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 1, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c1_Turbine_State_Machine_Lib(void
  *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc1_Turbine_State_Machine_LibInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc1_Turbine_State_Machine_LibInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct*) chartInstanceVar);
  initialize_c1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_Turbine_State_Machine_Lib(void *chartInstanceVar)
{
  enable_c1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_Turbine_State_Machine_Lib(void
  *chartInstanceVar)
{
  disable_c1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_Turbine_State_Machine_Lib(void
  *chartInstanceVar)
{
  sf_gateway_c1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c1_Turbine_State_Machine_Lib(void
  *chartInstanceVar)
{
  ext_mode_exec_c1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_Turbine_State_Machine_Lib
  (SimStruct* S)
{
  return get_sim_state_c1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct *)sf_get_chart_instance_ptr(S));/* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_Turbine_State_Machine_Lib(SimStruct* S,
  const mxArray *st)
{
  set_sim_state_c1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct*)sf_get_chart_instance_ptr(S),
     st);
}

static void sf_opaque_terminate_c1_Turbine_State_Machine_Lib(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_Turbine_State_Machine_LibInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Turbine_State_Machine_Lib_optimization_info();
    }

    finalize_c1_Turbine_State_Machine_Lib
      ((SFc1_Turbine_State_Machine_LibInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_Turbine_State_Machine_Lib
    ((SFc1_Turbine_State_Machine_LibInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_Turbine_State_Machine_Lib(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_Turbine_State_Machine_Lib
      ((SFc1_Turbine_State_Machine_LibInstanceStruct*)sf_get_chart_instance_ptr
       (S));
  }
}

mxArray *sf_c1_Turbine_State_Machine_Lib_get_testpoint_info(void)
{
  return NULL;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x8'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size','local_queue_dwork_idx','local_queue_id'{{T\"int32\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 8, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 642707434U, 565984533U, 233045432U,
    3413621343U };

  return checksum;
}

static void mdlSetWorkWidths_c1_Turbine_State_Machine_Lib(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Turbine_State_Machine_Lib_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 1);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3870451127U));
  ssSetChecksum1(S,(2118927114U));
  ssSetChecksum2(S,(3608529565U));
  ssSetChecksum3(S,(675980771U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_Turbine_State_Machine_Lib(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c1_Turbine_State_Machine_Lib(SimStruct *S)
{
  SFc1_Turbine_State_Machine_LibInstanceStruct *chartInstance;
  chartInstance = (SFc1_Turbine_State_Machine_LibInstanceStruct *)utMalloc
    (sizeof(SFc1_Turbine_State_Machine_LibInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc1_Turbine_State_Machine_LibInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.callGetHoverDataForMsg =
    sf_opaque_get_hover_data_for_msg;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c1_Turbine_State_Machine_Lib;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c1_Turbine_State_Machine_Lib(chartInstance);
}

void c1_Turbine_State_Machine_Lib_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_Turbine_State_Machine_Lib(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_Turbine_State_Machine_Lib(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_Turbine_State_Machine_Lib(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_Turbine_State_Machine_Lib_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
