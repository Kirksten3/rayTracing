#include "vec3.h"

Vec3::Vec3( float v0, float v1, float v2 )
{
	this->x = v0;
	this->y = v1;
	this->z = v2;
}

Vec3
Vec3::operator*(float val) {
    Vec3 result;
    result.x = this->x * val;
    result.y = this->y * val;
    result.z = this->z * val;
    return result;
}

Vec3&
Vec3::operator=( const Vec3& rhs )
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

Vec3
Vec3::operator+( const Vec3& that )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
        result.x = this->x + that.x;
        result.y = this->y + that.y;
        result.z = this->z + that.z;
	return result;
}

Vec3
Vec3::operator-( const Vec3& that )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
        result.x = this->x - that.x;
        result.y = this->y - that.y;
        result.z = this->z - that.z;
	return result;
}

Vec3
Vec3::operator-( )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// there is no "that" here
	Vec3 result;
        result.x = -this->x;
        result.y = -this->y;
        result.z = -this->z;
	return result;
}

Vec3
Vec3::Cross( Vec3& that )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
        result.x = this->y*that.z - that.y*this->z;
        result.y = this->z*that.x - that.z*this->x;
        result.z = this->x*that.y - that.x*this->y;
	return result;
}

float
Vec3::Dot( Vec3& that )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	float d = this->x*that.x + this->y*that.y + this->z*that.z;
	return d;
}

void
Vec3::Export( float* out )
{
	out[0] = x;
	out[1] = y;
	out[2] = z;
}

float
Vec3::Length( )
{
	// "this" is a pointer to this class's vec3  (this->name)
	float len = sqrt( SQR(this->x) + SQR(this->y) + SQR(this->z) );
	return len;
}

void
Vec3::Print( char *str, FILE *fp )
{
	fprintf( fp, "%s [ %8.3f %8.3f %8.3f ]\n", str, this->x, this->y, this->z );
}

Vec3
Vec3::Unit( )
{
	// "this" is a pointer to this class's vec3  (this->name)
	float len = this->Length( );
	Vec3 result;
	if (len == 0) {
	   result.x = 0;
	   result.y = 0;
	   result.z = 0;
	}
	else {
	    result.x = this->x / len;
	    result.y = this->y / len;
	    result.z = this->z / len;
	}
	return result;
}