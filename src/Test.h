/*
 * Introduction to Computer Graphics
 *
 * Test.h
 *
 */

#ifndef TEST_H
#define TEST_H

class Test
{
public:
	Test();
	~Test();
    
    virtual int init() = 0;
    virtual int run() = 0;

protected:
private:
};

#endif // TEST_H

