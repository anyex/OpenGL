#include "3DFunction.h"
float move_s = 0.0f;
float route_angle = 0;
void SetupMatrices(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w/(GLfloat)h,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void InitOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ǰ��������ֵ

	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 2.0f,
		0.0f, -0.0f, 1.0f,
		0.0f, -1.0f, 0.0f);//�ı�۲�任�����ｫ��õ�һ��������ͼ��

	
	glPushMatrix();//ʹ�þ����ջ��ֻ�������һ���������ƽ��
	//glTranslatef(0.5f, 0, 0);
	//���Ƶ�
	glPointSize(15.0f);//���õ�Ĵ�С
	glBegin(GL_POINTS);//��Ҫ���Ƶ�Ĺ���
	glColor3f(1.0f, 0.0f, 0.0f);//�趨��ɫ
	glVertex3f(0.0f, 1.0f, -5.0f);//���õ��λ��
	
	glEnd();//���Ƶ����
	glPopMatrix();
	if (!glIsEnabled(GL_POINT_SMOOTH))//����Ƿ�򿪿��������
	
		glEnable(GL_POINT_SMOOTH);

		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f,1.0f,-5.0f);

		glEnd();
	
	//������
		if (!glIsEnabled(GL_LINE_SMOOTH))
		{
			glEnable(GL_LINE_SMOOTH);//���������
		}

		glLineWidth(16.0f);//�����߿�
		glBegin(GL_LINES);//�����߿�

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(2.0f, 1.5f, -5.0f);
		glVertex3f(-1.0f, 1.5f, -5.0f);

		glEnd();

	//������
		glEnable(GL_LINE_STIPPLE);
		int stipplePattern = 0xAAAA;
		glLineStipple(10, stipplePattern);

		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-6.0f+ move_s, -1.5f, -5.0f);//��̬ƽ������
		glVertex3f(-4.0f+ move_s, -1.5f, -5.0f);
		glEnd();
		glDisable(GL_LINE_STIPPLE);


		//����������

		glTranslatef(0.0f, 0.0f, -5.0f);
		glRotatef(route_angle, 0.0f, 0.0f, 1.0f);//��ת������
		if (!glIsEnabled(GL_POLYGON_SMOOTH))
		{
			glEnable(GL_POLYGON_SMOOTH);
		}
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(2.0f, -1.0f, 0.0f);

		glEnd();
		move_s += 0.04f;
		route_angle += 0.1f;
		if (move_s >=8)
		{
			move_s = 0;
		}
}
