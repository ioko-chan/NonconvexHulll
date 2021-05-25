#pragma once

POINTFLOAT* graf = NULL;
int cnt;

void DrawOs( float alfa) { // функция, рисующая ось
	static float d = 0.05;
	glPushMatrix();
	glRotatef(alfa, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 0);
	glVertex2f(1 - d / 2, 0 + d / 2);
	glVertex2f(1, 0);
	glVertex2f(1 - d / 2, 0 - d / 2);
	glEnd();
	glPopMatrix();
}

void Init(float start, float finish, int count) { // функция , которя создает график
	cnt = count;
	graf = (POINTFLOAT*)realloc(graf, sizeof(*graf) * cnt);
	float dx = (finish - start) / (cnt - 1);
	for (int i = 0; i < cnt; i++) {
		graf[i].x = start;
		graf[i].y = sin(start);
		start += dx;
	}
}

void ShowPoints(const std::vector<POINTFLOAT> &points) {
	float sx = 2.0 / (graf[cnt - 1].x - graf[0].x); // коэффициент масштабирования
	float dx = (graf[cnt - 1].x + graf[0].x) * 0.5; //расстояние от цетра графика до цетра экрана 

	glPushMatrix();
	glScalef(sx, sx * 1.5, 1);
	glTranslatef(-dx, 0, 0);
	int count = 0;
	while (count != points.size()) {
		float a;
		/*glColor3f(0.0f, 1.0f, 0.0f);*/
		glBegin(GL_TRIANGLE_FAN);

		for (int i = 0; i < 50; i++) {
			a = (float)i / 50.0f * 3.1415f * 2.0f;
			glVertex2f(cos(a) * 1 + points[count].x, sin(a) * 1 + points[count].y);
		}

		glEnd();
		count++;
	}
	glPopMatrix();
}

void ShowLines(const std::vector<Picket> &pickets) {
	float sx = 2.0 / (graf[cnt - 1].x - graf[0].x); // коэффициент масштабирования
	float dx = (graf[cnt - 1].x + graf[0].x) * 0.5; //расстояние от цетра графика до цетра экрана 

	glPushMatrix();
	glScalef(sx, sx * 1.5, 1);
	glTranslatef(-dx, 0, 0);
	int count = 0;
	for (auto i : pickets) {

		for (auto j : i.firingPoint) {
			glBegin(GL_LINES);
			glVertex2f(i.coord.x, i.coord.y);
			glVertex2f(j.x, j.y);
			glEnd();
		}

		count++;
	}
	glPopMatrix();
}

void ShowLinesToPoints(const std::vector<POINTFLOAT> &points) {
	float sx = 2.0 / (graf[cnt - 1].x - graf[0].x); // коэффициент масштабирования
	float dx = (graf[cnt - 1].x + graf[0].x) * 0.5; //расстояние от цетра графика до цетра экрана 

	glPushMatrix();
	glScalef(sx, sx * 1.5, 1);
	glTranslatef(-dx, 0, 0);
	for (size_t i = 0; i < points.size() - 1; i++) {
		glBegin(GL_LINES);
		glVertex2f(points[i].x, points[i].y);
		glVertex2f(points[i + 1].x, points[i + 1].y);
		glEnd();
	}
	glBegin(GL_LINES);
	glVertex2f(points[points.size() - 1].x, points[points.size() - 1].y);
	glVertex2f(points[0].x, points[0].y);
	glEnd();
	glPopMatrix();
}
