/*
  15-462 Computer Graphics I
  Assignment 2: Roller Coaster
  C++ Utility Classes and Functions
  Author: rtark
  Aug 2007

  NOTE: You do not need to edit this file for this assignment but may do so, especially to the Camera class

  This file defines the following:
	Vector Class
	Camera Class
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
	Vector Class - A float triplet class with several vector-operation functions

	This class can be used to simplify vector math programming
*/
class Vector
{
public:
	float x, y, z;

	// -- Constructors & Destructors --
	// - Default Constructor - Initializes to Vector <0, 0, 0>
	Vector (void) : x (0.0f), y (0.0f), z (0.0f) {}

	// - Parameter Constructor - Initializes to Vector <a, b, c>
	Vector (float a, float b, float c) : x (a), y (b), z (c) {}

	// - Default Destructor -
	~Vector ()	{}

	// -- Utility Functions --
	// - Magnitude - Returns the Magnitude of the current Vector
	float Magnitude (void);

	// - Normalize - Normalizes to a Unit Vector (Scales to magnitude of 1)
	Vector Normalize (void);

	// - Scale - Scales the Vector by a factor
	Vector Scale (float scaleFactor);

	// - Dot - Calculates the Dot-Product between this and another Vector
	float Dot (Vector vec2);

	// - Cross - Returns the Cross-Product between this and another Vector
	Vector Cross (Vector vec2);

	// -- Operator Overloads to the class --
	// - Assignment Operator - Allows you to simply write "vec1 = vec2"
	Vector operator = (const Vector vec2)
	{
		x = vec2.x;
		y = vec2.y;
		z = vec2.z;
		return *this;
	}

	// NOTE: The following arithmetic operator overloads DO NOT change the value of the current vector
	// - Add Operator - Returns the sum of vectors
	Vector operator + (const Vector vec2)
	{
		return Vector (x + vec2.x, y + vec2.y, z + vec2.z);
	}

	// - Subtract Operator - Returns the difference of vectors
	Vector operator - (const Vector vec2)
	{
		return Vector (x - vec2.x, y - vec2.y, z - vec2.z);
	}

	// - Multiply Operator - Returns the vector scaled by a factor
	Vector operator * (const float scaleFactor)
	{
		return Vector (x * scaleFactor, y * scaleFactor, z * scaleFactor);
	}

	// - Divide Operator - Returns the vectors scaled by a factor
	Vector operator / (const float scaleFactor)
	{
		return Vector (x / scaleFactor, y / scaleFactor, z / scaleFactor);
	}
};


/*
	Camera Class - Class to help keep track of camera movements

	This class keeps the camera vectors together and adds a bit of functionality around it
	NOTE: This is unoptimized code for better readability
*/
class Camera
{
public:
	Vector position;
	Vector target;
	Vector up;

	// -- Constructors & Destructors --
	// - Default Constructor - Initializes to Vector <0, 0, 0>
	Camera (void) {}

	// - Parameter Constructor - Initializes to Vector <a, b, c>
	Camera (Vector p, Vector t, Vector u) { position = p; target = t; up = u; }

	// - Default Destructor -
	~Camera ()	{}

	// -- Accessor Functions --
	// - GetPosition - Returns the position vector of the camera
	Vector GetPosition (void) { return position; }

	// - SetPosition - Sets the position vector of the camera
	void SetPosition (const Vector vec) { position = vec; }

	// - GetTarget - Returns the target vector of the camera
	Vector GetTarget (void) { return target; }

	// - SetTarget - Sets the target vector of the camera
	void SetTarget (const Vector vec) { target = vec; }

	// - GetUp - Returns the up vector of the camera
	Vector GetUp (void) { return up; }

	// - SetUp - Sets the up vector of the camera
	void SetUp (const Vector vec) { up = vec; }
};



// --- Vector Class Functions ---

float Vector::Magnitude (void)
{
	return (float)sqrt (x * x + y * y + z * z);
}

Vector Vector::Normalize (void)
{
	float currentMagnitude = Magnitude ();
	x /= currentMagnitude;
	y /= currentMagnitude;
	z /= currentMagnitude;
	return *this;
}

Vector Vector::Scale (float scaleFactor)
{
	x *= scaleFactor;
	y *= scaleFactor;
	z *= scaleFactor;
	return *this;
}

float Vector::Dot (Vector vec2)
{
	return x * vec2.x + y * vec2.y + z * vec2.z;
}

Vector Vector::Cross (Vector vec2)
{
	Vector crossVec;
	crossVec.x = y * vec2.z - vec2.y * z;
	crossVec.y = vec2.x * z - x * vec2.z;
	crossVec.z = x * vec2.y - vec2.x * y;
	return crossVec;
}
