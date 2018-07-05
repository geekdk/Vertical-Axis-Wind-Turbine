#ifndef __c1_Turbine_State_Machine_Lib_h__
#define __c1_Turbine_State_Machine_Lib_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_Turbine_State_Machine_LibInstanceStruct
#define typedef_SFc1_Turbine_State_Machine_LibInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  real_T c1_park_speed;
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
  int32_T *c1_sfEvent;
  uint8_T *c1_is_active_c1_Turbine_State_Machine_Lib;
  uint8_T *c1_is_c1_Turbine_State_Machine_Lib;
  real_T *c1_pitch_brake;
  real_T *c1_wind_speed;
  real_T *c1_turbine_speed;
  real_T *c1_parking_brake;
  real_T *c1_generator_trip;
  real_T *c1_wind_speed_cut_in_lower;
  real_T *c1_turbine_speed_cut_in;
  real_T *c1_turbine_state;
  real_T *c1_wind_speed_cut_out;
  real_T *c1_wind_speed_cut_in_upper;
  real_T *c1_turbine_speed_cut_out;
} SFc1_Turbine_State_Machine_LibInstanceStruct;

#endif                                 /*typedef_SFc1_Turbine_State_Machine_LibInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c1_Turbine_State_Machine_Lib_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_Turbine_State_Machine_Lib_get_check_sum(mxArray *plhs[]);
extern void c1_Turbine_State_Machine_Lib_method_dispatcher(SimStruct *S, int_T
  method, void *data);

#endif
