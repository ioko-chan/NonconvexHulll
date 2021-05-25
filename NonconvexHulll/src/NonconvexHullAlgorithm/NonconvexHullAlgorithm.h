#pragma once
#define PI acos(-1.0)

struct find_picket {
	Picket point;
	find_picket(Picket point) : point(point) {}
	bool operator() (const Picket& a) {
		if (a.coord.x == point.coord.x && a.coord.y == point.coord.y)
			return true;
		return false;
	}
};

struct find_point1 {
	POINTFLOAT point;
	find_point1(POINTFLOAT point) : point(point) {}
	bool operator() (const POINTFLOAT& a) {
		if (a.x == point.x && a.y == point.y)
			return true;
		return false;
	}
};


class NonconvexHullAlgorithm {
public:
	NonconvexHullAlgorithm(std::vector<Picket> pickets,std::vector<POINTFLOAT> points):_pickets(pickets),_pointsShell(points){
		/*AddPointInHull();
		AddShellPoint();*/
		NonConvex1();
	}


	POINTFLOAT CoordToVectorCoord(POINTFLOAT a, POINTFLOAT b) {
		POINTFLOAT ab;
		ab.x = b.x - a.x;
		ab.y = b.y - a.y;

		return ab;
	}
	
	double Abs(POINTFLOAT ab) {
		double res=sqrt( pow(ab.x,2) +pow(ab.y,2) );
		return res;
	}

	double Angle(POINTFLOAT ab, POINTFLOAT cd) {
		double res = (ab.x*cd.x + ab.y*cd.y) / (Abs(ab) * Abs(cd));
		return res;
	}

	double ScalProiz(POINTFLOAT ab , POINTFLOAT cd) {
		double res = Abs(ab) * Abs(ab) * cos(Angle(ab,cd));
		return res;
	}

	double VectorProis(POINTFLOAT ab, POINTFLOAT cd) {
		double res = Abs(ab) * Abs(ab) * sin(Angle(ab, cd));
		return res;
	}

	bool IsPointInHull(POINTFLOAT currentPoint) {
		bool flag = 0;
		double fi = 0;
		for (int i = 0; i < _pickets.size()-1;i++) {
			POINTFLOAT cur1 = CoordToVectorCoord( _pickets[i].coord, currentPoint);
			POINTFLOAT cur2 =CoordToVectorCoord( _pickets[i + 1].coord, currentPoint);
			fi += atan2(VectorProis(cur1,cur2),ScalProiz(cur1,cur2));
		}
		POINTFLOAT cur1 = CoordToVectorCoord( _pickets[_pickets.size() - 1].coord, currentPoint);
		POINTFLOAT cur2 = CoordToVectorCoord( _pickets[0].coord,currentPoint);
		fi += atan2(VectorProis(cur1, cur2), ScalProiz(cur1, cur2));


		if (fi < 0.8*PI && fi > -PI*0.8)
			flag = true;
		else
			flag = false;
		return flag;
	}

	double HoleAngle(float a, float b) {
		float res2 = atan2(a, b);
		if (res2 < 0)
			res2 += 2 * PI;

		return res2;
	}

	float Distance(const POINTFLOAT& point1, const POINTFLOAT& point2) {
		float value = pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2);
		return sqrt(value);
	}

	Picket IsPicket(POINTFLOAT a) {
		double min = Distance(a,_pickets[0].coord);
		Picket minCoord = _pickets[0];
		for (auto i : _pickets) {
			if (Distance(i.coord, a) < min) {
				min = Distance(i.coord, a);
				minCoord = i;
			}
		}
		return minCoord;
	}

	void NonConvex() {
		for (auto i = 0; i < _pointsShell.size();i++) {
			
			
			auto it = std::find_if(_pickets.begin(), _pickets.end(), find_picket(IsPicket(_pointsShell[i])));
			if ((i != _pointsShell.size() - 1)) {
				auto iit = std::find_if(_pickets.begin(), _pickets.end(), find_picket(IsPicket(_pointsShell[i + 1])));
				auto itt = std::find_if((*it).pointsSheellPickets.begin(), (*it).pointsSheellPickets.end(), find_point1(_pointsShell[i]));
				if ((*it).coord.x == (*iit).coord.x && (*it).coord.y == (*iit).coord.y) {
					_NonConvexHull.push_back((*it).coord);
					continue;
				}

				for (auto j = (*it).pointsSheellPickets.begin(); j != (*it).pointsSheellPickets.end(); ++j) {
					if (IsPointInHull(*j)) {
						continue;
					}
					else
						_NonConvexHull.push_back(*j);
				}

			}
			else {
				auto q = std::find_if(_pickets.begin(), _pickets.end(), find_picket(IsPicket(_pointsShell[0])));
				auto w = std::find_if(_pickets.begin(), _pickets.end(), find_picket(IsPicket(_pointsShell[_pointsShell.size()-1])));
				auto itt = std::find_if((*it).pointsSheellPickets.begin(), (*it).pointsSheellPickets.end(), find_point1(_pointsShell[_pointsShell.size() - 1]));
				if ((*q).coord.x ==(*w).coord.x  && (*q).coord.y == (*w).coord.y) {
					_NonConvexHull.push_back((*it).coord);
					continue;
				}
				else {
					for (auto j = (*it).pointsSheellPickets.begin(); j != (*it).pointsSheellPickets.end(); ++j) {
						if (IsPointInHull(*j)) {
							continue;
						}
						else
							_NonConvexHull.push_back(*j);
					}
				}
			}
		}
	}

	bool IsPointInHull(POINTFLOAT currentPoint, std::vector<Picket> _pickets) {
		bool flag = 0;
		double fi = 0;
		for (int i = 0; i < _pickets.size() - 1; i++) {
			POINTFLOAT cur1 = CoordToVectorCoord(currentPoint, _pickets[i].coord);
			POINTFLOAT cur2 = CoordToVectorCoord(currentPoint, _pickets[i + 1].coord);
			fi += atan2(VectorProis(cur1, cur2), ScalProiz(cur1, cur2));
		}
		POINTFLOAT cur1 = CoordToVectorCoord(currentPoint, _pickets[_pickets.size() - 1].coord);
		POINTFLOAT cur2 = CoordToVectorCoord(currentPoint, _pickets[0].coord);
		fi += atan2(VectorProis(cur1, cur2), ScalProiz(cur1, cur2));


		if (fi < 0)
			flag = true;
		else
			flag = false;
		return flag;
	}


	bool IsShelOne(POINTFLOAT a, POINTFLOAT b) {
		Picket aa = IsPicket(a);
		Picket bb = IsPicket(b);
		if (aa.coord.x == bb.coord.x && aa.coord.y == bb.coord.y)
			return true;
		return false;
	}

	void NonConvex1() {
		for (auto u : _pickets) {
			for (auto p : u.pointsSheellPickets) {
				if (_pickets.size() > 2) {
					if (!IsPointInHull(p)) {
						_NonConvexHull1.push_back(p);
						std::cout << p.x << " " << p.y << std::endl;
					}
				}
				else {
					_NonConvexHull1.push_back(p);
					std::cout << p.x << " " << p.y << std::endl;
				}
			}
		}

	}

	std::vector<POINTFLOAT> NonConvexHull(){
		return _NonConvexHull1;
	}

	~NonconvexHullAlgorithm(){}
private:
	std::vector<Picket> _pickets;//пикеты
	std::vector<POINTFLOAT> _pointsShell;//точки верхней оболочки
	std::vector<POINTFLOAT> _NonConvexHull;// точки образующие невыпуклую оболочку
	std::vector<POINTFLOAT> _NonConvexHull1;
}; 