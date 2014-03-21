/*
 * Introduction to Computer Graphics
 *
 * TestRead.h
 *
 */

#ifndef TESTREAD_H
#define TESTREAD_H

#include "Test.h"

class TestRead : public Test
{
public:
	TestRead();
	~TestRead();
    
    virtual int init();
    virtual int run();

protected:
private:
};

#endif // TESTREAD_H

