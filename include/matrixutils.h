/*

Owen Gallagher
21 April 2019
Computer Graphics

matrixutils.h

A 3D homogeneous 4x4 matrix utility class.
Results stored in last args.

*/

class matrixutils {
public:
	static bool invert(const float [16], float [16]);
	static void mult(const float [16], const float [16], float[16]);
};