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
		/*double res = (ab.x*cd.x + ab.y*cd.y) / (Abs(ab) * Abs(cd));
		if (res < -1)
			res = -1;
		else if(res>1) {
			res = 1;
		}*/
		return ab.x*cd.y - cd.x*ab.y;
	}

	double ScalProiz(POINTFLOAT ab , POINTFLOAT cd) {
		double res = Abs(ab) * Abs(ab) * cos(Angle(ab,cd));
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
			maxY.x = _pickets[i].coord.x;
			maxY.y = _pickets[i].coord.y;
			POINTFLOAT maxX;
			maxX.x = _pickets[i].coord.x;
			maxX.y = _pickets[i].coord.y;
			POINTFLOAT minY;
			minY.x = _pickets[i].coord.x;
			minY.y = _pickets[i].coord.y;
			POINTFLOAT minX;
			minX.x = _pickets[i].coord.x;
			minX.y = _pickets[i].coord.y;

			if (_pickets[i].coord.x > _pickets[i + 1].coord.x) {
				minX = _pickets[i + 1].coord;
			}


			if (_pickets[i].coord.x <= _pickets[i + 1].coord.x) {
				minX = _pickets[i].coord;
			}
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
			if (currentPoint.y == maxY.y && currentPoint.x <  minX.x) {
				std::cout << "a";
				count++;
				continue;
			}
			if (currentPoint.y == minY.y) {
				//count++;
				continue;
			}
			if (_pickets[i].coord.y == _pickets[i + 1].coord.y && _pickets[i].coord.y == currentPoint.y) {
				//count++;
				continue;
			}

			if (_pickets[i].coord.y < _pickets[i + 1].coord.y) {
				if ((currentPoint.y > _pickets[i].coord.y && currentPoint.y <= _pickets[i + 1].coord.y) && (VectorProis(CoordToVectorCoord(_pickets[i].coord, currentPoint), CoordToVectorCoord(_pickets[i].coord, _pickets[i + 1].coord)) < 0)) {
					count++;
				}
			}


			if (_pickets[i].coord.y > _pickets[i + 1].coord.y) {
				if ((currentPoint.y > _pickets[i + 1].coord.y && currentPoint.y <= _pickets[i].coord.y) && (VectorProis(CoordToVectorCoord(_pickets[i + 1].coord, currentPoint), CoordToVectorCoord(_pickets[i + 1].coord, _pickets[i].coord)) < 0)) {
					count++;
				}
			}

		}

		{



			
				POINTFLOAT maxY;
				POINTFLOAT maxX;
				POINTFLOAT minY;
				POINTFLOAT minX;
				maxY.x = _pickets[_pickets.size() - 1].coord.x;
				maxY.y = _pickets[_pickets.size() - 1].coord.y;
				maxX.x = _pickets[_pickets.size() - 1].coord.x;
				maxX.y = _pickets[_pickets.size() - 1].coord.y;
				minY.x = _pickets[_pickets.size() - 1].coord.x;
				minY.y = _pickets[_pickets.size() - 1].coord.y;
				minX.x = _pickets[_pickets.size() - 1].coord.x;
				minX.y = _pickets[_pickets.size() - 1].coord.y;

				if (_pickets[_pickets.size() - 1].coord.y == _pickets[0].coord.y && _pickets[0].coord.y == currentPoint.y) {
					std::cout << "a";
					count++;
				}
				else {
					if (_pickets[_pickets.size() - 1].coord.x > _pickets[0].coord.x) {
						minX = _pickets[0].coord;
					}


					if (_pickets[_pickets.size() - 1].coord.x < _pickets[0].coord.x) {
						minX = _pickets[_pickets.size() - 1].coord;
					}

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
					if (_pickets[_pickets.size() - 1].coord.y < _pickets[0].coord.y) {
						maxY = _pickets[0].coord;
					}

					if (_pickets[_pickets.size() - 1].coord.y >= _pickets[0].coord.y) {
						maxY = _pickets[_pickets.size() - 1].coord;
					}
					if (currentPoint.y == maxY.y && currentPoint.x < minX.x) {
						count++;
						
					}
					else {


						if (currentPoint.y == minY.y) {
							//continue;
						}
						else {



							if (_pickets[_pickets.size() - 1].coord.y < _pickets[0].coord.y) {
								if ((currentPoint.y >= _pickets[_pickets.size() - 1].coord.y && currentPoint.y <= _pickets[0].coord.y) && (VectorProis(CoordToVectorCoord(_pickets[_pickets.size() - 1].coord, currentPoint), CoordToVectorCoord(_pickets[_pickets.size() - 1].coord, _pickets[0].coord)) <= 0)) {
									count++;
								}
							}


							if (_pickets[_pickets.size() - 1].coord.y > _pickets[0].coord.y) {
								if ((currentPoint.y >= _pickets[0].coord.y && currentPoint.y <= _pickets[_pickets.size() - 1].coord.y) && (VectorProis(CoordToVectorCoord(_pickets[0].coord, currentPoint), CoordToVectorCoord(_pickets[0].coord, _pickets[_pickets.size() - 1].coord)) <= 0)) {
									count++;
								}
							}
						}

					}
				}
			
		}

		std::cout << count << std::endl;
		std::cout << currentPoint.x << " " << currentPoint.y << std::endl;

		if (count % 2 == 0) {
			return false;
		}
		else if(count==0) {
			return true;
		}
	}

	Picket IsPoint(POINTFLOAT cur, std::vector<Picket> _pickets) {
		Picket th;
		for (auto i : _pickets) {
			for (auto k : i.firingPoint) {
				if (cur.x == k.x && cur.y == k.y) {
					th = i;
				}
			}
		}
		return th;
	}

	bool IsPointHulss(POINTFLOAT currentPoint, std::vector<Picket> _pickets) {
		std::vector<Picket> shellss;
		Picket th;
		for (auto i : _pickets) {
			for (auto k : i.firingPoint) {
				if (currentPoint.x == k.x && currentPoint.y == k.y) {
					th = i;
				}
			}
		}

		for (auto i : _pickets) {
			if (i.coord.x == th.coord.x && i.coord.y == th.coord.y)
				continue;
			else{
				shellss.push_back(i);
			}
		}

		for (auto i : shellss) {
			std::vector<Picket> fir;
			for (auto q : i.firingPoint) {
				Picket cur;
				cur.coord.x = q.x;
				cur.coord.y = q.y;
				fir.push_back(cur);
			}
			if (IsPointHull2(currentPoint, fir)) {
				return true;
			}
		}
		return false;
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


		if (fi < 0.7 * PI && fi > -PI * 0.7)
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


		if (fi < 0.7 * PI && fi > -PI * 0.7)
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

	Picket FindPick(POINTFLOAT cur) {
		auto i = std::find_if(_pickets.begin(), _pickets.end(), find_point_pickets(cur));
		return (*i);
	}

	bool Pointdist(POINTFLOAT a , POINTFLOAT b) {
		if (FindPick(a).coord.x == FindPick(b).coord.x && FindPick(a).coord.y == FindPick(b).coord.y)
			return true;
		return false;
	}

	void NonConvex1() {
		std::vector<Picket> change;
		for (int i = 1; i < _pickets.size(); i++) {
			int countPointInto = 0;
			for (int j = 0; j < _pickets[i].pointsSheellPickets.size(); j++) {
				if (!IsPointHull2(_pickets[i].pointsSheellPickets[j], _pickets)) {
					countPointInto++;
				}
			}
			if (countPointInto == _pickets[i].pointsSheellPickets.size()) {
				change.push_back(_pickets[i]);
			}
		}
		std::vector<POINTFLOAT> SYD;
		for (int t = 0; t < change.size(); t++) {
			for (int i = 0; i < _pickets.size(); i++) {
				if (_pickets[i].coord.x == change[t].coord.x && _pickets[i].coord.y == change[t].coord.y) {
					SYD.push_back(_pickets[0].pointsSheellPickets[0]);
					for (int u = 0; u < _pickets[i - 1].pointsSheellPickets.size(); u++) {
						if (!IsPointHull2(_pickets[i - 1].pointsSheellPickets[u], _pickets)) {
							SYD[t] = _pickets[i - 1].pointsSheellPickets[u];
						}
					}
				}
			}
		}
		std::vector<int> minDis ;
		std::vector <POINTFLOAT> min;
		for (int t = 0; t < change.size(); t++) {
			minDis.push_back (Distance(change[t].pointsSheellPickets[0], SYD[t]));
			min.push_back(change[t].pointsSheellPickets[0]);
			for (int i = 0; i < change[t].pointsSheellPickets.size(); i++) {
				if (minDis[t] > Distance(change[t].pointsSheellPickets[i], SYD[t])) {
					minDis[t] = Distance(change[t].pointsSheellPickets[i], SYD[t]);
					min[t] = change[t].pointsSheellPickets[i];
				}
			}
		}
		for (int t = 0; t < change.size(); t++) {
			while (1) {
				if (change[t].pointsSheellPickets[0].x != min[t].x && change[t].pointsSheellPickets[0].y != min[t].y) {
					POINTFLOAT pop = change[t].pointsSheellPickets[0];
					for (int i = 0; i < change[t].pointsSheellPickets.size() - 1; i++) {
						change[t].pointsSheellPickets[i] = change[t].pointsSheellPickets[i + 1];
					}
					change[t].pointsSheellPickets[change[t].pointsSheellPickets.size() - 1] = pop;
				}
				else {
					break;
				}
			}
		}
		for (int t = 0; t < change.size(); t++) {
			for (auto u : _pickets) {
				if (u.coord.x == change[t].coord.x && u.coord.y == change[t].coord.y) {
					u.pointsSheellPickets = change[t].pointsSheellPickets;
				}
			}
		}
		for (int t = 0; t < change.size(); t++) {
			for (int i = 0; i < _pickets.size(); i++) {
				if (_pickets[i].coord.x == change[t].coord.x && _pickets[i].coord.y == change[t].coord.y) {
					_pickets[i].pointsSheellPickets = change[t].pointsSheellPickets;
				}
			}
		}
		for (auto u : _pickets) {
			for (auto p : u.pointsSheellPickets) {
				if (_pickets.size() > 2) {
					if (!IsPointHull2(p,_pickets ))  {
						
							_NonConvexHull1.push_back(p);
							//std::cout << p.x << " " << p.y << std::endl;
						
					}
				}
				else {
					_NonConvexHull1.push_back(p);
					//std::cout << p.x << " " << p.y << std::endl;
				}
			}
		}

		/*for (int i = 0; i < _NonConvexHull1.size(); i++) {
			if (IsPoint(_NonConvexHull1[i], _pickets).coord.x == change[0].coord.x && IsPoint(_NonConvexHull1[i], _pickets).coord.y == change[0].coord.y) {

			}
		}*/

		for (int i = 1; i < _NonConvexHull1.size()-1; i++) {
			if (!Pointdist(_NonConvexHull1[i], _NonConvexHull1[i + 1])) {
				if (_NonConvexHull1[i].y == _NonConvexHull1[i + 1].y && abs(_NonConvexHull1[i].x - _NonConvexHull1[i - 1].x) > abs(_NonConvexHull1[i + 1].x - _NonConvexHull1[i - 1].x)) {
					std::swap(_NonConvexHull1[i], _NonConvexHull1[i + 1]);
				}
			}
		}
		if (!Pointdist(_NonConvexHull1[_NonConvexHull1.size() - 1], _NonConvexHull1[0])) {
			if (_NonConvexHull1[_NonConvexHull1.size() - 1].y == _NonConvexHull1[0].y && abs(_NonConvexHull1[_NonConvexHull1.size() - 1].x - _NonConvexHull1[_NonConvexHull1.size() - 2].x) > abs(_NonConvexHull1[0].x - _NonConvexHull1[_NonConvexHull1.size() - 2].x)) {
				std::swap(_NonConvexHull1[_NonConvexHull1.size() - 1], _NonConvexHull1[0]);
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