#include "3DFunction.h"
#include "MD2.h"

modelData_t* myModel;
float move_s = 0.0f;
float route_angle = 0;
float armAngle[2] = { 0 };
float legAngle[2] = { 0 };
float angle = 0;
GLuint texture;
AUX_RGBImageRec* textureImage[1];

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
	glEnable(GL_TEXTURE_2D);
	//LoadGLTextures("timg.bmp");
	myModel = LoadMD2Model("chastity.md2", "chastity.bmp");
}

/*void Render1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ǰ��������ֵ

	glLoadIdentity();
	gluLookAt(0.0f, .0f, 2.0f,
		0.0f, 0.0f, 1.0f,
		0.f, 2.0f, 0.0f);//�ı�۲�任�����ｫ��õ�һ��������ͼ��

	
	/*glPushMatrix();//ʹ�þ����ջ��ֻ�������һ���������ƽ��
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

		glEnd();*/
		
	//���ƻ�����
	/*glPushMatrix();
	glTranslatef(0.0f, 8.0f, -30.f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	RenderRobert(0.0f, 0.0f, 0.0f);
	glPopMatrix();

	angle = angle + 0.05f;

	if (angle >= 360.0f)
	{
		angle = 0.0f;
	}
}*/

//��һ��������
void RenderRobert(float xPos,float yPos,float zPos)
{
	static bool leg1 = true;
	static bool leg2 = false;

	static bool arm1 = true;
	static bool arm2 = false;

	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		DrawHead(1.0f, 2.0f, 0.0f);
		DrawTorso(1.5f, 0.0f, 0.0f);
	glPushMatrix();
		if (arm1)
		
			armAngle[0] = armAngle[0] + 0.05f;
		else
			armAngle[0] = armAngle[0] - 0.05f;

		//����첲�ﵽ�����ĽǶ���ı���״̬
		if (armAngle[0]>=1.0f)
		{
			arm1 = false;
		}
		if (armAngle[0]<=-1.0f)
		{
			arm1 = true;
		}

		//ƽ�Ʋ���ת����Ƹ첲
		glTranslatef(0.0f, -0.5f, 0.0f);
		glRotatef(armAngle[0], 1.0f, 0.0f, 0.0f);
		DrawArm(1.5f,0.8f, -0.9f);

	glPopMatrix();
		

	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	DrawHead(1.0f, 2.0f, 0.0f);
	DrawTorso(1.0f, 0.5f, 0.0f);
	glPushMatrix();
	if (arm2)

		armAngle[1] = armAngle[1] + 0.1f;
	else
		armAngle[1] = armAngle[1] - 0.1f;

	//����첲�ﵽ�����ĽǶ���ı���״̬
	if (armAngle[1] >= 1.0f)
	{
		arm2 = false;
	}
	if (armAngle[1] <= -1.0f)
	{
		arm2 = true;
	}

	//ƽ�Ʋ���ת����Ƹ첲
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(armAngle[1], 1.0f, 0.0f, 0.0f);
		DrawArm(-1.5f, 0.5f, -0.5f);
	glPopMatrix();

	//�����Ȳ�

	glPushMatrix();
	if (leg1)
	{
		legAngle[0] = legAngle[0] + 0.1f;
	}
	else
		legAngle[0] = legAngle[0] - 0.1f;

	if (legAngle[0]>=15.0f)
	{
		leg1 = false;
	}
	if (legAngle[0]<=-15.0f)
	{
		leg1 = true;
	}

	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngle[0], 1.0f, 0.0f, 0.0f);
	DrawLeg(-0.5f, -5.0f, -0.5f);

	glPopMatrix();

	glPushMatrix();
	if (leg2)
	{
		legAngle[1] = legAngle[1] + 0.1f;
	}
	else
		legAngle[1] = legAngle[1] - 0.1f;

	if (legAngle[1]>=15.0f)
	{
		leg2 = false;
	}
	
	if (legAngle[1]<=-15.0f)
	{
		leg2 = true;
	}

	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngle[1], 1.0f, 0.0f, 0.0f);
	DrawLeg(1.5f, -5.0f, -0.5f);

	glPopMatrix();



}
//����������
void DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);

	glBegin(GL_POLYGON);
	//����
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	//ǰ��
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	//����
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	//����
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	//����
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	//����
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);

	

	glEnd();


}

void DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(0.5f, 1.0f, 0.5f);
		DrawCube(0.0f, 0.0f, 0.f);
	glPushMatrix();
}

void DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(2.0f, 2.0f, 2.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(3.0f, 5.0f, 2.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPushMatrix();
}

void DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(1.0f, 5.0f, 1.0f);
		DrawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}
//��Ⱦ�������
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 2.0f, 50.0f,
		0.0f, 10.0f, -50.0f,
		0.0f, 1.0f, 0.0f);
	glPushMatrix();
	DisplayMD2(myModel, 40);
	glPopMatrix();

	
	//glTexCoord2f(x,y)�����������꣬��Ϊ����ķ�Χ��0-1,��x,y���������Χʱ���ͻ���s�������ظ�x�Σ�t�������ظ�y��

}

//��������
int LoadGLTextures(char* filename)
{
	int status = FALSE;
	
	
	//�ж�����ͼ�Ƿ񱣴�ɹ�����������textureImage��
	if (textureImage[0] = auxDIBImageLoad(TEXT(filename)))
	{
		status = TRUE;
		glGenTextures(1, &texture);
		//������

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


		//ָ������
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			textureImage[0]->sizeX,
			textureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE,
			textureImage[0]->data);
	
	}

	return status;


}
/************************************************************************/
/* �����ܽ�
  1.ʹ��glEnable(GL_TEXTURE_2D);��������
  2.����������Դ
  3.��������ID�� glGenTextures(1, &texture);
 
  4 ������  glBindTexture(GL_TEXTURE_2D, texture);
  5.��������
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


  6.ָ������
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 textureImage[0]->sizeX,
				 textureImage[0]->sizeY,
				 0, GL_RGB, GL_UNSIGNED_BYTE,
				 textureImage[0]->data);

*/
/************************************************************************/