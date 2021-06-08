#pragma once
#define PI acos(-1.0)

struct Picket {
	POINTFLOAT coord;
	int firingPoints=0;
	std::vector<POINTFLOAT> firingPoint;
	std::vector<POINTFLOAT> pointsSheellPickets;
};

class ShellingAlgorithm {
public:
	ShellingAlgorithm( std::vector<Picket> &pickets):_coordsPickets(pickets){
		//Polygon();
		for (size_t i = 0; i < _coordsPickets.size(); i++) {
			_pickets.push_back(_coordsPickets[i].coord);
		}
	}



	double HoleAngle(float a, float b) {
		float res2 = atan2(a, b);
		if (res2 < 0)
			res2 += 2 * PI;

		return res2;
	}


	POINTFLOAT CoordToVectorCoord(POINTFLOAT a, POINTFLOAT b) {
		POINTFLOAT ab;
		ab.x = b.x - a.x;
		ab.y = b.y - a.y;

		return ab;
	}

	double Abs(POINTFLOAT ab) {
		double res = sqrt(pow(ab.x, 2) + pow(ab.y, 2));
		return res;
	}

	double Angle(POINTFLOAT ab, POINTFLOAT cd) {
		double res = (ab.x * cd.x + ab.y * cd.y) / (Abs(ab) * Abs(cd));
		return res;
	}

	double ScalProiz(POINTFLOAT ab, POINTFLOAT cd) {
		double res = Abs(ab) * Abs(ab) * cos(Angle(ab, cd));
		return res;
	}

	double VectorProis(POINTFLOAT ab, POINTFLOAT cd) {
		double res = Abs(ab) * Abs(ab) * sin(Angle(ab, cd));
		return res;
	}

	bool IsPointInHull(POINTFLOAT currentPoint) {
		bool flag = 0;
		double fi = 0;
		for (int i = 0; i < _pickets.size() - 1; i++) {
			POINTFLOAT cur1 = CoordToVectorCoord(_coordsPickets[i].coord, currentPoint);
			POINTFLOAT cur2 = CoordToVectorCoord(_coordsPickets[i + 1].coord, currentPoint);
			fi += atan2(VectorProis(cur1, cur2), ScalProiz(cur1, cur2));
		}
		POINTFLOAT cur1 = CoordToVectorCoord(_coordsPickets[_pickets.size() - 1].coord, currentPoint);
		POINTFLOAT cur2 = CoordToVectorCoord(_coordsPickets[0].coord, currentPoint);
		fi += atan2(VectorProis(cur1, cur2), ScalProiz(cur1, cur2));


		if (fi < 0.8 * PI && fi > -PI * 0.8)
			flag = true;
		else
			flag = false;
		return flag;
	}

	void Polygon() {
		POINTFLOAT centroid;
		centroid.x = 0;
		centroid.y = 0;
		for (auto i : _coordsPickets) {
			centroid.x += i.coord.x;
			centroid.y += i.coord.y;
		}

		for (size_t i = 0; i < _coordsPickets.size()-1; i++) {
			for (size_t j = i+1; j < _coordsPickets.size(); j++) {
				if ((HoleAngle(_coordsPickets[i].coord.y - centroid.y, _coordsPickets[i].coord.x - centroid.y)) > (HoleAngle(_coordsPickets[j].coord.y - centroid.y, _coordsPickets[j].coord.x - centroid.y)))
					std::swap(_coordsPickets[i], _coordsPickets[j]);
			}
		}
		for (size_t i = 0; i < _coordsPickets.size(); i++) {
			_pickets.push_back(_coordsPickets[i].coord);
		}


			

		

		
	}

	std::vector<Picket> ListOfDistributedPoints() {
		return _coordsPickets;
	}

	std::vector<POINTFLOAT> ListOfDistributedPointsForShell(int  num) {
		return _coordsPickets[num].firingPoint;
	}

	std::vector<POINTFLOAT> ListOfDistributedPicketsForShell() {
		return _pickets;
	}

	~ShellingAlgorithm() {}
private:
	std::vector<POINTFLOAT> _coordsPoints;
	std::vector<Picket> _coordsPickets;
	std::vector<POINTFLOAT> _firstQuarter;
	std::vector<POINTFLOAT> _pickets;
	POINTFLOAT _center;
};