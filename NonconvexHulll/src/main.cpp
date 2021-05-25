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
int HEIGHT = 800; //��������� ������� ����

int main() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW!!!" << std::endl;
		return -1;
	}

	//  ������ ����� 
	int countPoints;
	std::cout << "Number of points:" << std::endl;
	std::cin >> countPoints;
	std::vector<POINTFLOAT> inputPoints;
	POINTFLOAT point;
	for (size_t i = 0; i < countPoints; i++){
		std::cout <<"Enter "<< i+1<<" point: " << std::endl;
		std::cin >> point.x>> point.y;
		inputPoints.push_back(point);
	}

	//  ������ ������
	std::vector<POINTFLOAT> inputPickets;
	int countPickets;
	std::cout << "Number of pickets  ("<<inputPoints.size()/8+1<< " desirable ) : "<< std::endl;
	std::cin >> countPickets;
	POINTFLOAT picket;
	for (size_t i = 0; i < countPickets; i++) {
		std::cout << "Enter " << i + 1 << " picket: " << std::endl;
		std::cin >> picket.x >> picket.y;
		inputPickets.push_back(picket);
	}

	ShellingAlgorithm outputPicketFiring(inputPoints, inputPickets);

	std::vector<Picket> PicketFiring = outputPicketFiring.ListOfDistributedPoints();

	JarvisAlgorithm a(inputPoints,false, PicketFiring);
	std::vector<JarvisAlgorithm> q ;


	for (int i = 0; i < inputPickets.size(); i++) {
		JarvisAlgorithm s(outputPicketFiring.ListOfDistributedPointsForShell(i),true, PicketFiring);
		q.push_back(s);
	}

	std::vector<POINTFLOAT> shell = a.Shell();
	std::vector<POINTFLOAT> qq;
	POINTFLOAT z;
	z.x = 0; z.y = 0;
	qq.push_back(z);
	std::vector < POINTFLOAT > wer;
	std::vector < POINTFLOAT > wer1;
	for (int i = 0; i < inputPickets.size(); i++) {
		
		PicketFiring[i].pointsSheellPickets = q[i].Shell();
		//wer.push_back(q[i].HullOfPickets(PicketFiring[i].pointsSheellPickets, PicketFiring));
		//wer1.push_back(q[i].HullOfPickets1(PicketFiring[i].pointsSheellPickets, PicketFiring));
	}
	

	NonconvexHullAlgorithm output(PicketFiring, a.Shell());
	auto out = output.NonConvexHull();

	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"Schedule",nullptr,nullptr); // ������� ����
	glfwMakeContextCurrent(window);

	GLFWwindow* window2 = glfwCreateWindow(WIDTH, HEIGHT, "Schedule", nullptr, nullptr); // ������� ����
	

	Init(-100.0,100.0, 100.0); // ������ ��� ������������ ���������� - ��� ������� �������� �������

	while (!glfwWindowShouldClose(window) ) {  // �������� �� �������� ����, ���� �������
		glfwMakeContextCurrent(window);
		glClearColor(0.88,0.88, 0.88,1); // ��������� ���� ����
		glClear(GL_COLOR_BUFFER_BIT); // ������� �������� ������

		//������ ���
		glLoadIdentity();
		glLineWidth(2);
		glColor3f(1, 0, 0);
		DrawOs(0);
		glColor3f(0, 1, 0);
		DrawOs(90);
		// ������ �������
		glColor3f(0,0,1);
		ShowPoints(inputPoints);
		
		ShowLines(PicketFiring);
		
		glColor3f(1, 1, 0);
		ShowPoints(wer);
		//ShowPoints(wer1);
		for (int i = 0; i < inputPickets.size();i++) {
			
			ShowLinesToPoints(q[i].Shell());
		}
		glColor3f(1, 0, 0);
		if (inputPickets.size() > 1) {
			
			ShowLinesToPoints(outputPicketFiring.ListOfDistributedPicketsForShell());
		}
		ShowPoints(inputPickets);
		glColor3f(0.7, 0, 1);
		//ShowLinesToPoints(out);
		ShowLinesToPoints(shell);

		glfwSwapBuffers(window);//������ ������� ������
		glfwPollEvents();

		glfwMakeContextCurrent(window2);
		glClearColor(0.88, 0.88, 0.88, 1); // ��������� ���� ����
		glClear(GL_COLOR_BUFFER_BIT); // ������� �������� ������
		glLoadIdentity();
		glLineWidth(2);
		glColor3f(1, 0, 0);
		DrawOs(0);
		glColor3f(0, 1, 0);
		DrawOs(90);
		// ������ �������
		glColor3f(0, 0, 1);
		ShowPoints(out);
		ShowLinesToPoints(out);
		ShowLinesToPoints(shell);
		glfwSwapBuffers(window2);//������ ������� ������
		glfwPollEvents();

	}
	glfwDestroyWindow(window); //����������� ���� ����� ������
	glfwTerminate();


	glfwDestroyWindow(window2); //����������� ���� ����� ������
	glfwTerminate();
	
	return 0;
}