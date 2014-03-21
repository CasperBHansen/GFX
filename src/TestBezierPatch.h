/*
 * Introduction to Computer Graphics
 *
 * TestBezierPatch.h
 *
 */

#ifndef TESTBEZIERPATCH_H
#define TESTBEZIERPATCH_H

#include "Test.h"

class TestBezierPatch : public Test
{
public:
	TestBezierPatch();
	~TestBezierPatch();
    
    virtual int init();
    virtual int run();
    
    void BP_ParameterizedConstructor();
    void BP_IndexOperatorConst();
    void BP_IndexOperator();
    void BP_RightMatMult();

protected:
private:
};

#endif // TESTBEZIERPATCH_H

