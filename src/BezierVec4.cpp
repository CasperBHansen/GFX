/*
 * BezierVec4.cpp
 */

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <string>
#include <cctype>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "utilities/glmutils.h"
#include "BezierVec4.h"


/**
 * Default constructor creates an empty BezierVec4, i.e. all entries are the zero vector.
 */
BezierVec4::BezierVec4()
{
    glm::vec3 zero(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 4; ++i) this->points[i] = zero;
}

/**
 * Parameterized constructor creates a BezierVec4 containing the arguments as entries.
 * \param G1 - Entry one in the geometry vector.
 * \param G2 - Entry two in the geometry vector.
 * \param G3 - Entry three in the geometry vector.
 * \param G4 - Entry four in the geometry vector.
 */
BezierVec4::BezierVec4(glm::vec3 const& G1, glm::vec3 const& G2, glm::vec3 const& G3, glm::vec3 const& G4)
{
    this->points[0] = G1;
    this->points[1] = G2;
    this->points[2] = G3;
    this->points[3] = G4;
}

/**
 * Copy constructor creates a new BezierVec4 which is a copy of its argument.
 * \param geometryvector - The geometry vector to be copied.
 */
BezierVec4::BezierVec4(BezierVec4 const& geometryvector)
{
    for (int i = 0; i < 4; ++i) this->points[i] = geometryvector.points[i];
}

/**
 * Destructor destroys the current instance of BezierVec4.
 */
BezierVec4::~BezierVec4()
{}

void BezierVec4::draw(Style style, double n)
{
    #define G1 points[0]
    #define G2 points[1]
    #define G3 points[2]
    #define G4 points[3]
    
    double t;
    double delta = 1.0 / n;
    glm::vec3 last = points[0];
    glm::vec3 point;
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // draw curve
    switch (style)
    {
        case STYLE_SAMPLED:
        {
            for (t = 0.0; t <= 1.0; t += delta)
            {
                point = powf((1.0f - t), 3.0f) * points[0]
                      + (float)(3.0f * t * powf((1 - t), 2.0f)) * points[1]
                      + (float)(3.0f * (1.0f - t) * powf(t, 2.0f)) * points[2]
                      + powf(t, 3.0f) * points[3];
                
                glBegin(GL_LINES);
                    glVertex3f(last.x, last.y, last.z);
                    glVertex3f(point.x, point.y, point.z);
                glEnd();
                last = point;
            }
        }
        break;
        
        case STYLE_FORWARD_DIFF:
        {
            // calculate GM matrix vectors
            glm::vec3 a = -G1 + 3.0f * G2 - 3.0f * G3 + G4;
            glm::vec3 b = 3.0f * G1 - 6.0f * G2 + 3.0f * G3;
            glm::vec3 c = -3.0f * G1 + 3.0f * G2;
            glm::vec3 d = G1;
            
            // initialize deltas
            glm::vec3 deltas[4];
            float t1 = delta;
            float t2 = t1 * t1;
            float t3 = t2 * t1;
            
            deltas[0] = d;
            deltas[1] = a * t3 + b * t2 + c * t1;
            deltas[2] = 6.0f * a * t3 + 2.0f * b * t2;
            deltas[3] = 6.0f * a * t3;
            
            last = deltas[0];
            for (t = 0.0; t <= (1.0 - delta); t += delta)
            {
                deltas[0] += deltas[1];
                deltas[1] += deltas[2];
                deltas[2] += deltas[3];
                
                glBegin(GL_LINES);
                    glVertex3f(last.x, last.y, last.z);
                    glVertex3f(deltas[0].x, deltas[0].y, deltas[0].z);
                glEnd();
                
                last = deltas[0];
            }
        }
        break;
        
        case STYLE_SUBDIVISION:
        { 
            subdivide(G1, G2, G3, G4, delta); 
        }
        break;
    }
    
    // draw control points
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < 4; ++i)
    {
        glBegin(GL_POINTS);
            glVertex2i( points[i].x, points[i].y );
        glEnd();
    }
    
    // draw lines
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_LINES);
    for (int i = 0; i < 3; ++i)
    {
        glVertex2i( points[i].x, points[i].y );
        glVertex2i( points[i+1].x, points[i+1].y );
    }
    glEnd();
}

void BezierVec4::subdivide(glm::vec3 const& V1,
                           glm::vec3 const& V2,
                           glm::vec3 const& V3,
                           glm::vec3 const& V4,
                           double epsilon)
{
    glm::vec3 unitV4V1 = glm::normalize(V4 - V1);
    glm::vec3 V2V1 = V2 - V1;
    glm::vec3 V3V1 = V3 - V1;
    
    float dV2 = glm::length(V2V1 - glm::dot(V2V1, unitV4V1) * unitV4V1);
    float dV3 = glm::length(V3V1 - glm::dot(V3V1, unitV4V1) * unitV4V1);
    float d = (dV2 > dV3) ? dV2 : dV3;
    
    if ( d < epsilon )
    {
        glBegin(GL_LINES);
            glVertex3f(V1.x, V1.y, V1.z);
            glVertex3f(V2.x, V2.y, V2.z);
            
            glVertex3f(V2.x, V2.y, V2.z);
            glVertex3f(V3.x, V3.y, V3.z);
            
            glVertex3f(V3.x, V3.y, V3.z);
            glVertex3f(V4.x, V4.y, V4.z);
        glEnd();
    }
    else
    {
        glm::vec3 H = (V2 + V3) / 2.0f;
        glm::vec3 L[4];
        glm::vec3 R[4];
        
        L[0] = V1;                      R[0] = V4;
        L[1] = (V1 + V2) / 2.0f;        R[1] = (V3 + V4) / 2.0f;
        L[2] = (H  + L[1]) / 2.0f;      R[2] = (H  + R[1]) / 2.0f;
        L[3] = (L[2] + R[2]) / 2.0f;    R[3] = (L[2] + R[2]) / 2.0f;
        
        subdivide(L[0], L[1], L[2], L[3], epsilon);
        subdivide(R[0], R[1], R[2], R[3], epsilon);
    }
}

/**
 * Assignent operator assigns its argument to the current instance of BezierVec4.
 * \lparam geometryvector - The geometry vector to be assigned to this instance.
 */
BezierVec4& BezierVec4::operator=(BezierVec4 const& geometryvector)
{
    if (this != &geometryvector) {
	for (int i = 0; i < 4; ++i) this->points[i] = geometryvector.points[i];
    }
    return *this;
}

/**
 * Index operator - read only - returns the i'th entry in the geometry vector,
 * The entry is returned as a homogeneous vector.
 * \param i - The index of the entry to be returned as a homogeneous vector.
 */
glm::vec3 const& BezierVec4::operator[](int i) const
{
    if ((i < 1) && (i > 4)) {
	throw std::out_of_range("BezierVec4::operator[](int): The index must be in the range {1,...,4}");
    }
    return this->points[i - 1];
}

/**
     * Index operator returns a reference to the i'th entry in the geometry vector.
     * The reference is to a homogeneous vector, and it can be assigned to (read/write).
     * \param i - The index of the entry to which a reference is to be returned;
     */
glm::vec3& BezierVec4::operator[](int i)
{
    if ((i < 1) && (i > 4)) {
	throw std::out_of_range("BezierVec4::operator[](int): The index must be in the range {1,...,4}");
    }
    return this->points[i - 1];
}


/**
 * Utlity Functions
 */

/**
 * Multiplication operator, right-multiplies a geometry vector by an ordinary vector (a parameter vector).
 * This can be used to right-multiply the Bezier matrices by the parameter vector. 
 * \param geometryvector - The BezierVec4 that should be multimplied.
 * \param vector - The vector (a parameter vector) that is right-multiplied by the geometry vector.
 * \return The product geometryvector * vector.
 */
glm::vec3 operator*(BezierVec4 const& geometryvector, glm::vec4 const& vector)
{
    glm::vec3 result(0.0f);
    
    for (int i = 0; i < 4; ++i) {
	result += geometryvector[i + 1] * vector[i];
    }
    return result;
}

/**
 * Multiplication operator, right-multiplies a geometry vector by an ordinary matrix (a basis matrix).
 * This can be used to right-multiply a Bezier geometry vector by an ordinary matrix (a basis matrix).
 * \param geometryvector - The BezierVec4 that should be multiplied.
 * \param matrix - The ordinary matrix to be right-multiplied (basis matrix) by the geometry vector.
 * \return The product geometryvector * matrix.
 */
BezierVec4 operator*(BezierVec4 const& geometryvector, glm::mat4x4 const& matrix)
{
    glm::vec3 zeroes(0.0f);
    BezierVec4 result(zeroes, zeroes, zeroes, zeroes);

    for (int c = 0; c < 4; c++) {
	glm::vec4 column(glm::column(matrix, c));
	for (int i = 0; i < 4; ++i) {
	    result[c + 1] += geometryvector[i + 1] * column[i];  
	}
    }
    return result;
}

/**
 * Multiplication operator, left-multiplies an ordinary matrix (a transformation matrix) by a geometry vector.
 * It multiplies the control points by the matrix thereby transforming them.
 * \param matrix - The ordinary matrix (transformation matrix) to be left-multiplied by the geometry vector.
 * \param geometryvector - The BezierVec4 that should be multiplied.
 * \return A new BezierVec4 with the element[i] = matrix * geometryvector[i]; i = 1,...,4
 */
BezierVec4 operator*(glm::mat4x4 const& matrix, BezierVec4 const& geometryvector)
{
    BezierVec4 result;

    for (int i = 1; i <= 4; ++i) {
	glm::vec4 tmpvec = matrix * glm::vec4(geometryvector[i], 1.0f);
	if (tmpvec.w == 0.0) {
	    throw std::runtime_error("operator*(glm::mat4x4&, BezierVec4&): Division by zero");
	}
	result[i] = glm::vec3(tmpvec.x / tmpvec.w, tmpvec.y / tmpvec.w, tmpvec.z / tmpvec.w); 
    }
    return result;
}

/**
 * Insertion operator, inserts a BezierVec4 into an ostream.
 * \param s - The ostream which the geometryvector should be inserted into.
 * \param geometryvector - The BezierVec4 that should be inserted into the ostream.
 * \return The ostream which the geometryvector has been inserted into.
 */
std::ostream& operator<<(std::ostream& s, BezierVec4 const& geometryvector)
{
    s << ' ';
    for (int i = 1; i < 4; ++i) {
	s << std::setw(6) << std::setprecision(4) << geometryvector[i] << " | ";
    }
    s << std::setw(6) << std::setprecision(4) << geometryvector[4] << ' ';

    return s;
}

