/*=====================================================================================
 File name:        PID.C  (Float version)


=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20
-------------------------------------------------------------------------------------*/

#include "WYLib28335.h"
#include "DSP28x_Project.h"

float32 pid_calc(PID *v)
{
	// Compute the error
	v->Err = (v->Ref) - (v->Fdb);

	// Compute the proportional output
	v->Up = (v->Kp)*(v->Err);

	// Compute the integral output
	//v->UiPreSat = (v->Ui) + (v->Ki*v->Err) + (v->Kc*v->SatErr);

	//if(v->UiPreSat> v->UiSatLimit)
	//	v->Ui = v->UiSatLimit;
	//else
	//	v->Ui = v->UiPreSat;
	v->Ui = (v->Ui) + (v->Ki*v->Err) + (v->Kc*v->SatErr);

	// Compute the derivative output
	//v->Ud = (v->Kd) * ((v->Err) - (v->Err0));

	// Compute the pre-saturated output
	v->OutPreSat = (v->Up) + (v->Ui) ;//+ (v->Ud);
	//v->OutPreSat = v->Up + v->Ui ;
	//v->OutPreSat=_IQsat(v->OutPreSat,MAX_IQ_POS,MAX_IQ_NEG);

	//s Saturate the output
	if ((v->OutPreSat) > (v->OutMax))
		v->Out = v->OutMax;
	else if ((v->OutPreSat) < (v->OutMin))
		v->Out = v->OutMin;
	else
		v->Out = v->OutPreSat;
	// Compute the saturate difference
	v->SatErr = (v->Out) - (v->OutPreSat);

	// Update the previous Error
	v->Err0 = v->Err;
	return v->Out;
}


