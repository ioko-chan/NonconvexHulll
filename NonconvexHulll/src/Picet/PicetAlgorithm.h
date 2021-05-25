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
	ShellingAlgorithm(std::vector<POINTFLOAT> &points, std::vector<POINTFLOAT> &pickets):_coordsPoints(points){
		Picket a;
		for (auto i : pickets) {
			a.coord.x=i.x;
			a.coord.y = i.y;
			_coordsPickets.push_back(a);
		}
		DistributionOfPointsToPickets();
		Polygon();
	}

	float Distance(const POINTFLOAT &point1,const POINTFLOAT &point2) {
		float value = pow((point2.x - point1.x),2)+ pow((point2.y - point1.y), 2);
		return sqrt(value);
	}

	void DistributionOfPointsToPickets() {
		for (auto i : _coordsPoints) {
			float minDistance = Distance(i, _coordsPickets[0].coord);
			POINTFLOAT minDisCoord = _coordsPickets[0].coord;
			for (auto j : _coordsPickets) {
				float dis = Distance(i, j.coord);
				if (dis < minDistance) {
					minDistance = dis;
					minDisCoord.x = j.coord.x;
					minDisCoord.y = j.coord.y;
				}
			}
			/*std::cout<<minDistance<<std::endl;*/
			for (int j = 0; j < _coordsPickets.size();j++) {
				if (_coordsPickets[j].coord.x == minDisCoord.x && _coordsPickets[j].coord.y == minDisCoord.y) {
					_coordsPickets[j].firingPoints++;
					_coordsPickets[j].firingPoint.push_back(i);
				}
			}
		}

		
	}

	double HoleAngle(float a, float b) {
		float res2 = atan2(a, b);
		if (res2 < 0)
			res2 += 2 * PI;

		return res2;
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