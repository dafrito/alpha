#include "Vector3.h"
namespace nt
{

Vector3<double> getAxisAngles(Vector3<double>& vec)
{
	Vector3<double> Rot;
	if (vec.x() == 0) {
		if (vec.y() >= 0){
			Rot.setZ( 0 );
		} else {
			Rot.setZ(M_PI_2 * 2);
		}
	} else if (vec.y() == 0) {
		if (vec.x() > 0) {
			Rot.setZ(M_PI_2 * 3);
		} else {
			Rot.setZ(M_PI_2);
		}
	} else {
		// figure out correct total angle: changes based on quadrant
		Rot.setZ( atan( vec.y() / vec.x() ) );
		if (vec.x() < 0){
			Rot.setZ(Rot.z() + M_PI_2);
		} else {
			Rot.setZ(Rot.z() + M_PI_2 * 3);
		}
	}
	// horizontal distance
	const double dxy = sqrt(
		vec.x() * vec.x() + vec.y() * vec.y()
	);
	// vertical and horizontal angle calculation's aren't exacly the same
	if (vec.z() == 0) {
		Rot.setX(0);
	} else if (dxy == 0) {
		if (vec.z() > 0){
			Rot.setX( M_PI_2);
		} else {
			Rot.setX( M_PI_2 * 3);
		}
	} else {
		Rot.setX(atan( dxy / vec.z() ));
		if (vec.z() < 0){
			Rot.setX(M_PI_2 * 3 - Rot.x());
		} else {
			Rot.setX(M_PI_2 - Rot.x());
		}
	}
	return Rot;
}

}

