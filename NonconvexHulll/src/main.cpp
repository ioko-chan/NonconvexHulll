#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "Picet/PicetAlgorithm.h"
#include "JarvisAlgorithm/JarvisAlgorithm.h"
#include "ShowFunction/Rendering.h"
#include "NonconvexHullAlgorithm/NonconvexHullAlgorithm.h"
#include <iterator>

int WIDTH = 1200;
int HEIGHT = 800; //указываем размеры окна


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

bool IsPointInHull(POINTFLOAT currentPoint, std::vector<Picket> _pickets) {
	bool flag = 0;
	double fi = 0;
	for (int i = 0; i < _pickets.size() - 1; i++) {
		POINTFLOAT cur1 = CoordToVectorCoord(_pickets[i].coord, currentPoint);
		POINTFLOAT cur2 = CoordToVectorCoord(_pickets[i + 1].coord, currentPoint);
		fi += atan2(VectorProis(cur1, cur2), ScalProiz(cur1, cur2));
	}
	POINTFLOAT cur1 = CoordToVectorCoord(_pickets[_pickets.size() - 1].coord, currentPoint);
	POINTFLOAT cur2 = CoordToVectorCoord(_pickets[0].coord, currentPoint);
	fi += atan2(VectorProis(cur1, cur2), ScalProiz(cur1, cur2));


	if (fi < 0.8 * PI && fi > -PI * 0.8)
		flag = true;
	else
		flag = false;
	return flag;
}


int main() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW!!!" << std::endl;
		return -1;
	}

	// водим количество пикетов и к каждому пикетту количество точек, ему принадлежащие
	std::vector<Picket> inputPickets;
	std::vector<POINTFLOAT> inputPoints;
	int countPickets;
	std::cout << "Number of pickets  : " << std::endl;
	std::cin >> countPickets;
	Picket picket;
	for (size_t i = 0; i < countPickets; i++) {

		std::cout << "Enter " << i + 1 << " picket: " << std::endl;
		std::cin >> picket.coord.x >> picket.coord.y;
		inputPickets.push_back(picket);

		int countPoints;
		std::cout << "Number of points:" << std::endl;
		std::cin >> countPoints;
		POINTFLOAT point;
		for (size_t j = 0; j < countPoints; j++) {
			std::cout << "Enter " << i + 1 << " point: " << std::endl;
			std::cin >> point.x >> point.y;
			inputPickets[i].firingPoint.push_back(point);
			inputPoints.push_back(point);
		}
	}


	ShellingAlgorithm outputPicketFiring( inputPickets);

	std::vector<Picket> PicketFiring = outputPicketFiring.ListOfDistributedPoints();

	JarvisAlgorithm a(inputPoints,false, PicketFiring);
	std::vector<JarvisAlgorithm> q ;


	for (int i = 0; i < inputPickets.size(); i++) {


		JarvisAlgorithm s(outputPicketFiring.ListOfDistributedPointsForShell(i),true, PicketFiring);
		q.push_back(s);
	}

	std::vector < POINTFLOAT > wer;
	for (int i = 0; i < inputPickets.size(); i++) {
		
		PicketFiring[i].pointsSheellPickets = q[i].Shell();
	}
	std::vector<POINTFLOAT> inputPicketss;
	for (int i = 0; i < inputPickets.size(); i++) {
		inputPicketss.push_back(inputPickets[i].coord);
	}
	NonconvexHullAlgorithm output(PicketFiring, a.Shell());
	auto out = output.NonConvexHull();

	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"Schedule",nullptr,nullptr); // создаем окно
	glfwMakeContextCurrent(window);

	GLFWwindow* window2 = glfwCreateWindow(WIDTH, HEIGHT, "Schedule", nullptr, nullptr); // создаем окно
	

	Init(-100.0,100.0, 100.0); // первые две передаваемые переменные - это пределы создания графика

	while (!glfwWindowShouldClose(window) ) {  // проверка на закрытие окна, цикл событий
		glfwMakeContextCurrent(window);
		glClearColor(0.88,0.88, 0.88,1); // указываем цвет окна
		glClear(GL_COLOR_BUFFER_BIT); // очищаем цветовой буффер

		//рисуем оси
		glLoadIdentity();
		glLineWidth(2);
		glColor3f(1, 0, 0);
		DrawOs(0);
		glColor3f(0, 1, 0);
		DrawOs(90);
		// рисуем графики
		glColor3f(0,0,1);
		ShowPoints(inputPoints);
		
		ShowLines(inputPickets);
		
		glColor3f(1, 1, 0);
		//ShowPoints(wer);
		

		for (int i = 0; i < inputPickets.size();i++) {
			
			ShowLinesToPoints(q[i].Shell());
		}
		glColor3f(1, 0, 0);
		if (inputPickets.size() > 1) { // отрисовываем оболочки пикетов 
			

			ShowLinesToPoints(outputPicketFiring.ListOfDistributedPicketsForShell());
		}
		ShowPoints(inputPicketss);
		glColor3f(0.7, 0, 1);
		//ShowLinesToPoints(out);
		//ShowLinesToPoints(shell);// отрисовываем оболочку выпуклую

		glfwSwapBuffers(window);//меняем текущей буффер
		glfwPollEvents();

		glfwMakeContextCurrent(window2);
		glClearColor(0.88, 0.88, 0.88, 1); // указываем цвет окна
		glClear(GL_COLOR_BUFFER_BIT); // очищаем цветовой буффер
		glLoadIdentity();
		glLineWidth(2);
		glColor3f(1, 0, 0);
		DrawOs(0);
		glColor3f(0, 1, 0);
		DrawOs(90);
		// рисуем графики
		glColor3f(0, 0, 1);
		ShowPoints(out);
		ShowLinesToPoints(out);// отрисовываем оболочку невыпуклую
		//ShowLinesToPoints(shell);// отрисовываем оболочку выпуклую
		glfwSwapBuffers(window2);//меняем текущей буффер
		glfwPollEvents();

	}
	glfwDestroyWindow(window); //уничтожение окна после работы
	glfwTerminate();


	glfwDestroyWindow(window2); //уничтожение окна после работы
	glfwTerminate();
	
	return 0;
}