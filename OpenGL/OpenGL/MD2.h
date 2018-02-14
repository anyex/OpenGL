#pragma once
#ifndef _MD2_H
#define _MD2_H
#include "stdio.h"
#define  BITMAP_ID 0x4D42//bmpID��
//֧�ֵ���������
enum texTypes_t {
	PCX,BMP,TGA,JPG
};
//md2�ļ�ͷ
typedef struct 
{
	int ident;//MD2�ļ��ı�ʾ
	int version;//Ӧ�õ���8
	int skinwidth;//����Ŀ��
	int skinheight;//����ĸ߶�
	int framesize;//ÿһ֡���ֽ���
	int numSkins;//���������
	int numXYZ;//���������
	int numST;//�������������
	int numTris;//�����ε�����
	int numGLcmds;//OpenGL�������͵�����
	int numFrames;//�ܵ�֡��
	int offsetSkins;//����(Ƥ��)���ֵ�ƫ����(64�ֽ�)
	int offsetST;//����s-t��ƫ����
	int offsetTris;//�����������ƫ����
	int offsetFrames;//֡����(��)��ƫ����
	int offsetGLcmds;//OpenGL�����ƫ����
	int offsetEnd;//�ļ���β


}modelMD2Header_t;
/************************************************************************/
/* ident�����ڽ��������ģ�ͱ�ʾΪһ��MD2�ļ���������ģ��ʱ������ͨ�����ident�Ƿ���ڡ�IDP2��
   skinwidth,skinheight:ָ�������ڶԴ�ģ�ͽ�����Ƥ������Ŀ�Ⱥ͸߶�
   framesize:��������ÿһ֡���ֽ���
   numSkins:������ģ�Ϳ��õ�Ƥ��������
   ���е�offset����ָ���˶�Ӧ���ݵĴ��λ��
*/
/************************************************************************/




/************************************************************************/
/* ��������ش�����                                                                     */
/************************************************************************/
typedef struct {
	float point[3];
}vector_t;

vector_t vecSub(vector_t a, vector_t b);//����
vector_t vecAdd(vector_t a, vector_t b);//�ӷ�
vector_t vecMul(vector_t a, vector_t b);//�˷�
vector_t vecDiv(vector_t a, vector_t b);//����

/************************************************************************/
/* ����            */
/************************************************************************/
//��������
typedef struct
{
	float s;
	float t;
}texCoord_t;
//������������
typedef struct 
{
	short s;
	short t;
}stIndex_t;
typedef struct 
{
	texTypes_t textureType;//�������ͼ���ļ�����

	int width;//����Ŀ��
	int height;//����߶�
	long int scaledWidth;
	long int scaleHeight;//PCXͼ������ſ�Ⱥ͸߶�
	unsigned int texID;//���������������ʾID
	unsigned char *data;//��������
	unsigned char *palett;//����ĵ�ɫ��


}texture_t;

void SetupMD2Texture(texture_t* thisTexture);
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
texture_t *LoadTexture(char *textureName);//��������
texture_t *LoadBMPTexture(char *textureName);//����BMP����
texture_t *LoadJPGTexture(char *textureName);//����JPG����
/************************************************************************/
/* ģ��֡��Ϣ                                                                 */
/************************************************************************/
//һ֡��ÿ�������Ϣ
typedef struct 
{
	unsigned char v[3];//����Ϣ
	unsigned char normalIndex;//
}framePoint_t;

//��һ֡����Ϣ
typedef struct 
{
	float scale[3];//֡�ж�������ű���
	float translate[3];//֡�ж����ƽ��
	char name[16];//ģ�͵�����
	framePoint_t fp[1];//֡�ж����б�Ŀ�ʼ
}frame_t;

typedef struct 
{
	unsigned short meshIndex[3];//��������
	unsigned short stIndex[3];//������������


}mesh_t;


//ģ�͵����ݽṹ
typedef struct 
{
	int numFrames;//֡������
	int numPoints;//���������
	int numTriangles;//�����ε�����
	int numST;//�������������
	int frameSize;//ÿһ֡���ݵ��ֽ���
	int texWidth;
	int texHeight;//����Ŀ�Ⱥ͸߶�
	int currentFrame;//�����еĵ�ǰ֡�ĺ�
	int nextFrame;//�����е���һ֡�ĺ�
	float interpol;//ͨ����ǰ֡�İٷֱ�(��ֵ��ʽ)
	mesh_t *triIndex;//�������б�
	texCoord_t *st;//���������б�
	vector_t *pointList;//�����б�
	texture_t *modelTex;//��������

}modelData_t;


modelData_t *LoadMD2Model(char* filename, char* textureName);//����MD2ģ��
void DisplayMD2(modelData_t* model, int frameNum);//��ʾMD2ģ��



#endif