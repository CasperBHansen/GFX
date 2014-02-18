/*
 * Introduction to Computer Graphics
 *
 * ProgramGeometricTransformations.h
 *
 */

#ifndef PROGRAMGEOMETRICTRANSFORMATIONS_H
#define PROGRAMGEOMETRICTRANSFORMATIONS_H

#include "../ProgramTemplate.h"

#include "../Shader.h"
#include "../VertexBufferObject.h"

class ProgramGeometricTransformations : public ProgramTemplate
{
public:
	ProgramGeometricTransformations();
	virtual ~ProgramGeometricTransformations();
    
    virtual void init();
    
    virtual void update(unsigned char key, int x, int y);
    virtual void render();

protected:

private:
    VertexBufferObject * vbo;
    Shader * shader;
    
    GLuint m_vbo;
};

#endif // PROGRAMGEOMETRICTRANSFORMATIONS_H

