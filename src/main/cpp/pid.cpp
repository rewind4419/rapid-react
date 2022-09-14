#pragma once
#include "pid.h"

void InitPid(PID* pid)
{
	pid->errorAccum = 0;
	pid->lastError = 0;
}

float EvaluatePid(PID* pid, float error, float dt)
{
	pid->errorAccum += error;

	float output = 
		(pid->kP * error) +
		(pid->kI * pid->errorAccum) * dt +
		(pid->kD * (error - pid->lastError) / dt);

	pid->lastError = error;

	return output;
}