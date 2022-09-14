#pragma once

struct PID
{
	float kP;
	float kI;
	float kD;

	float errorAccum;
	float lastError;
};

void InitPid(PID* pid);

float EvaluatePid(PID* pid, float error, float dt);