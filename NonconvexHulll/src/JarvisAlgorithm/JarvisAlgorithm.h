#pragma once
#include <algorithm>
#define PI acos(-1.0)

struct find_point {
	POINTFLOAT point;
	find_point(POINTFLOAT point) : point(point) {}
	bool operator() (const POINTFLOAT& a) {
		if (a.x == point.x && a.y == point.y)
			return true;
		return false;
	}
};


struct find_point_pickets {
	POINTFLOAT point;
	find_point_pickets(POINTFLOAT point) : point(point) {}
	bool operator() (const Picket& a) {
		for (auto q : a.pointsSheellPickets) {
			if(q.x==point.x && q.y == point.y)
				return true;
		}

		return false;
	}
};


class Misc {
public:
	bool operator() (const POINTFLOAT& a, POINTFLOAT& b) {
		return a.y < b.y;
	}
}misc;

class JarvisAlgorithm {
public:
	JarvisAlgorithm(std::vector<POINTFLOAT> points, bool isShellPoint,std::vector<Picket> pic) :_givenPoints(points),_isShellPoint(isShellPoint),_pic(pic){
		FidingPointsFromShell(_pic);
	}

	double HoleAngle(POINTFLOAT a, POINTFLOAT b) {
		b.x -= a.x;
		b.y -= a.y;

		float res2 = atan2(b.y, b.x);
			if (res2 < 0 )
				res2 += 2 * PI;
	
		return res2;
	}

	double CosAngle(POINTFLOAT a1, POINTFLOAT a2, POINTFLOAT b) {

		POINTFLOAT vec1Coord;
		vec1Coord.x = a2.x - a1.x;
		vec1Coord.y = a2.y - a1.y;

		POINTFLOAT vec2Coord;

		vec2Coord.x = a2.x - b.x;
		vec2Coord.y = a2.y - b.y;

		double numerator =vec1Coord.x * vec2Coord.x + vec1Coord.y * vec2Coord.y;

		double denominator = sqrt(pow(vec1Coord.x,2)+ pow(vec1Coord.y, 2)) * sqrt(pow(vec2Coord.x, 2) + pow(vec2Coord.y, 2));

		double cos = numerator / denominator;
		
		return cos;
	}

	float Distance(const POINTFLOAT& point1, const POINTFLOAT& point2) {
		float value = pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2);
		return sqrt(value);
	}



	POINTFLOAT CoordToVectorCoord(POINTFLOAT a, POINTFLOAT b) {
		POINTFLOAT ab;
		ab.x = b.x - a.x;
		ab.y = b.y - a.y;

		return ab;
	}

	double Abs(POINTFLOAT ab) {
		double qw = pow(ab.x, 2);
		double wze = pow(ab.y, 2);
		double res = sqrt(qw+wze);
		return res;
	}

	double Angle(POINTFLOAT ab, POINTFLOAT cd) {
		double as = (ab.x * cd.x + ab.y * cd.y);
		double ll = (Abs(ab) * Abs(cd));
		double res = as /ll ;
		return res;
	}

	double ScalProiz(POINTFLOAT ab, POINTFLOAT cd) {
		double res = Abs(ab) * Abs(ab) * cos(Angle(ab, cd));
		return res;
	}

	double VectorProis(POINTFLOAT ab, POINTFLOAT cd) {
		double res = ab.x * cd.y - cd.x * ab.y;
		return res;
	}
	bool IsPointHull2(POINTFLOAT currentPoint, std::vector<Picket> _pickets) {
		int count = 0;
		for (int i = 0; i < _pickets.size() - 1; i++) {

			if (_pickets[i].coord.y == _pickets[i + 1].coord.y)
				continue;
			
			POINTFLOAT maxY;
			POINTFLOAT maxX;
			POINTFLOAT minY;
			if (_pickets[i].coord.y > _pickets[i + 1].coord.y) {
				minY = _pickets[i + 1].coord;
			}
			if (_pickets[i].coord.y < _pickets[i + 1].coord.y) {
				minY = _pickets[i].coord;
			}
			if (_pickets[i].coord.x < _pickets[i + 1].coord.x) {
				maxX = _pickets[i + 1].coord;
			}
			if (_pickets[i].coord.x >= _pickets[i + 1].coord.x) {
				maxX = _pickets[i].coord;
			}
			if (_pickets[i].coord.y > _pickets[i + 1].coord.y) {
				maxY = _pickets[i].coord;
			}
			if (_pickets[i].coord.y < _pickets[i + 1].coord.y) {
				maxY = _pickets[i + 1].coord;
			
			}

				if (currentPoint.y == maxY.y && currentPoint.x < maxX.x) {
					count++;
					continue;
				}
				if (currentPoint.y == minY.y) {
					continue;
				}

				


			if (_pickets[i].coord.y < _pickets[i + 1].coord.y) {
				if ((currentPoint.y > _pickets[i].coord.y && currentPoint.y < _pickets[i + 1].coord.y) && (VectorProis( CoordToVectorCoord(_pickets[i].coord, currentPoint), CoordToVectorCoord(_pickets[i].coord, _pickets[i + 1].coord)) < 0)) {
					count++;
				}
			}


			if (_pickets[i].coord.y > _pickets[i + 1].coord.y) {
				if ((currentPoint.y > _pickets[i + 1].coord.y && currentPoint.y < _pickets[i].coord.y) && (VectorProis( CoordToVectorCoord(_pickets[i+1].coord, currentPoint), CoordToVectorCoord(_pickets[i + 1].coord, _pickets[i].coord)) < 0)) {
					count++;
				}
			}

		}

		{


			
			if (_pickets[_pickets.size()-1].coord.y == _pickets[0].coord.y) {
			}
			else {
				POINTFLOAT maxY;
				POINTFLOAT maxX;
				POINTFLOAT minY;
				if (_pickets[_pickets.size() - 1].coord.y > _pickets[0].coord.y) {
					minY = _pickets[0].coord;
				}


				if (_pickets[_pickets.size() - 1].coord.y < _pickets[0].coord.y) {
					minY = _pickets[_pickets.size() - 1].coord;
				}

				if (_pickets[_pickets.size() - 1].coord.x < _pickets[0].coord.x) {
					maxX = _pickets[0].coord;
				}

				if (_pickets[_pickets.size() - 1].coord.x >= _pickets[0].coord.x) {
					maxX = _pickets[_pickets.size() - 1].coord;
				}
				if (_pickets[_pickets.size() - 1].coord.y > _pickets[0].coord.y) {
					maxY = _pickets[_pickets.size() - 1].coord;
				}

				if (_pickets[_pickets.size() - 1].coord.y < _pickets[0].coord.y) {
					maxY = _pickets[0].coord;
				}
				if (currentPoint.y == maxY.y && currentPoint.x < maxX.x) {
					count++;
				}
				else {
					
						if (currentPoint.y == minY.y) {
							//continue;
						}
						else {



							if (_pickets[_pickets.size() - 1].coord.y < _pickets[0].coord.y) {
								if ((currentPoint.y >= _pickets[_pickets.size() - 1].coord.y && currentPoint.y < _pickets[0].coord.y) && (VectorProis( CoordToVectorCoord(_pickets[_pickets.size() - 1].coord, currentPoint), CoordToVectorCoord(_pickets[_pickets.size() - 1].coord, _pickets[0].coord)) <= 0)) {
									count++;
								}
							}


							if (_pickets[_pickets.size() - 1].coord.y > _pickets[0].coord.y) {
								if ((currentPoint.y >= _pickets[0].coord.y && currentPoint.y < _pickets[_pickets.size() - 1].coord.y) && (VectorProis( CoordToVectorCoord(_pickets[0].coord, currentPoint), CoordToVectorCoord(_pickets[0].coord, _pickets[_pickets.size() - 1].coord)) <= 0)) {
									count++;
								}
							}
						}
					
				}
			}
		}


		if (count % 2 == 0 || count == 0) {
			return false;
		}
		else {
			return true;
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


		if (fi < 0.7 * PI && fi > -PI * 0.7)
			flag = true;
		else
			flag = false;
		return flag;
	}


	bool PrisTr(POINTFLOAT a , POINTFLOAT b , std::vector<Picket> _pickets) {
		bool flag=false;
		//отрезок оболочки
		// а , б
		// отрезок двух пикетов
		float minDis=Distance(a,(_pickets[0].coord));
		POINTFLOAT c; 
		POINTFLOAT d;
		c.x = _pickets[0].coord.x;
		c.y = _pickets[0].coord.y;
		int count = 0;
		for (int i = 0; i < _pickets.size();i++) {
			if (Distance(a, _pickets[i].coord) < minDis) {
				minDis = Distance(a, _pickets[i].coord);
				c.x = _pickets[i].coord.x;
				c.y = _pickets[i].coord.y;
				count = i;
			}
		}

		c.x = _pickets[count].coord.x;
		c.y = _pickets[count].coord.y;

		if (count == 0) {
			d.x = _pickets[count+1].coord.x;
			d.y = _pickets[count+1].coord.y;
		}

		if (count == _pickets.size()-1) {
			d.x = _pickets[count -1].coord.x;
			d.y = _pickets[count - 1].coord.y;
		}

		if (count != 0 && count != _pickets.size() - 1) {
			d.x = _pickets[count + 1].coord.x;
			d.y = _pickets[count + 1].coord.y;
		}

		double k1, k2,b1,b2 ;
		if (b.x <= a.x)
			std::swap(a, b);
		if (d.x <= c.x)
			std::swap(d, c);

		if (a.y == b.y)
			k1 = 0;
		else {
		k1 = (b.y - a.y) / (b.x - a.x);
		}

		if (d.y == c.y)
			k2 = 0;
		else {
			k2 = (d.y - c.y) / (d.x - c.x);
		}

		if (k1 == k2) {
			return false;
		}
		/*b1 = a.y - k1 * a.x;
		b2 = c.y - k2 * c.x;*/

		if ((a.x < d.x && d.x < b.x) && ((a.x < c.x) && (c.x < b.x)))
			return true;

		return flag;
	}


	std::vector<POINTFLOAT> OutShell(std::vector<POINTFLOAT> beginpoint, std::vector<Picket> pikets) {
		for (int i = 0; i < pikets.size(); i++) {


			for (int j = 0; j < pikets[i].pointsSheellPickets.size(); j++) {


			}
		}
	}

	void FidingPointsFromShell(std::vector<Picket> _pic) {
		if (_givenPoints.size() > 2) {
			sort(_givenPoints.begin(), _givenPoints.end(), misc);

			POINTFLOAT minY = _givenPoints[0];
			_shell.push_back(minY);
			_givenPoints.erase(_givenPoints.begin());
			double minHoleAngle = HoleAngle(minY, _givenPoints[0]);
			POINTFLOAT minHoleAngleCoord = _givenPoints[0];
			for (auto i : _givenPoints) {
				double currentAngle = HoleAngle(minY, i);
				if (currentAngle < minHoleAngle) {
					minHoleAngle = currentAngle;
					minHoleAngleCoord = i;
				}

			}

			_shell.push_back(minHoleAngleCoord);
			auto it = std::find_if(_givenPoints.begin(), _givenPoints.end(), find_point(minHoleAngleCoord));
			_givenPoints.erase(it);

			_givenPoints.push_back(minY);

			POINTFLOAT currentPeack1 = minY;
			POINTFLOAT currentPeack2 = minHoleAngleCoord;
			POINTFLOAT minCosCoord = _givenPoints[0];

			do {
				double minCos = CosAngle(currentPeack1, currentPeack2, _givenPoints[0]);
				minCosCoord = _givenPoints[0];
				//std::cout << minCos << " " << _givenPoints[0].x << " " << _givenPoints[0].y << std::endl;
				for (int i = 1; i < _givenPoints.size(); i++) {
					double currentCos = CosAngle(currentPeack1, currentPeack2, _givenPoints[i]);
					//std::cout << currentCos<<" "<< _givenPoints[i].x<<" "<< _givenPoints[i].y << std::endl;
					if (currentCos < minCos) {
						minCos = currentCos;
						minCosCoord = _givenPoints[i];
					}
				}
				_shell.push_back(minCosCoord);
				auto it = std::find_if(_givenPoints.begin(), _givenPoints.end(), find_point(minCosCoord));
				_givenPoints.erase(it);
				currentPeack1 = currentPeack2;
				currentPeack2 = minCosCoord;
			} while (currentPeack2.x != minY.x && currentPeack2.y != minY.y);

			for (int i = 0; i < _shell.size() - 1; i++) {
				for (int j = i + 1; j < _shell.size(); j++) {
					if (_shell[i].x == _shell[j].x && _shell[i].y == _shell[j].y) {
						_shell.erase(_shell.begin() + j);
					}
				}
			}
			POINTFLOAT Proverka = _shell[0];
			
			bool one = false;
			if (_isShellPoint) {
				if (_pic.size() > 2) {
					POINTFLOAT t;
					while (!IsPointHull2(minY, _pic)) {
						if ((Proverka.x == _shell[0].x) && (Proverka.y == _shell[0].y) && one == true) {
							//ищем пикет
							POINTFLOAT coorddis = _pic[0].coord;
							//float dis= Distance(_shell[0],_pic[0].coord );
							for (auto i : _pic) {
								for (auto y : i.firingPoint) {
									if (y.x == _shell[0].x && y.y == _shell[0].y) {
										coorddis = y;
									}
								}
							}
							//POINTFLOAT coorddis= _pic[0].coord;
							/*for (size_t i = 0; i < _pic.size(); i++) {
								if (Distance(_shell[0], _pic[i].coord) < dis) {
									dis = Distance(_shell[0], _pic[i].coord);
									coorddis = _pic[i].coord;
								}
							}*/
							//ищем ближайшую точку от пикета до оболочки
							float minDis = Distance(_shell[0], coorddis);
							POINTFLOAT minCoordDis = _shell[0];
							for (int i = 0; i < _shell.size(); i++) {
								if (Distance(_shell[i], coorddis) < minDis) {
									minCoordDis = _shell[i];
									minDis = Distance(_shell[i], coorddis);
								}
							}

							//while (_shell[_shell.size()-1].x != minCoordDis.x    && _shell[_shell.size() - 1].y != minCoordDis.y) {
							//	POINTFLOAT pop = _shell[0];
							//	one = true;
							//	for (int i = 0; i < _shell.size() - 1; i++) {
							//		_shell[i] = _shell[i + 1];
							//	}
							//}
							break;
						}
						POINTFLOAT pop=_shell[0];
						one = true;
						for (int i = 0; i < _shell.size() - 1; i++) {
							_shell[i] = _shell[i + 1];
						}
						_shell[_shell.size() - 1] = pop;
						/*for (int i = 1; i < _shell.size() - 1; i++) {
							t = _shell[i];
							_shell[i] = _shell[i - 1];
							pop = _shell[i + 1];
							_shell[i + 1] = t;
						}*/


						bool neww = false;
						for (size_t i = 0; i < _shell.size() - 1; i++) {
							if (minY.x == _shell[i].x && minY.y == _shell[i].y) {
								minY = _shell[i + 1];
								neww = true;
							}
						}//посмотреть чем явл мину
						if (!neww) {
							if (minY.x == _shell[_shell.size() - 1].x && minY.y == _shell[_shell.size() - 1].y) {
								minY = _shell[0];
							}
						}
					}
				}
			}
		}
		else {
			for (auto u : _givenPoints) {
				_shell.push_back(u);
			}
		}


	}
	std::vector<POINTFLOAT> Shell() {
		return _shell;
	}

	~JarvisAlgorithm() {}
private:
	std::vector<POINTFLOAT> _givenPoints;
	std::vector<POINTFLOAT> _shell;
	std::vector<Picket> _pic;
	bool _isShellPoint;
	std::vector<POINTFLOAT> _shellBegin;
}; 

