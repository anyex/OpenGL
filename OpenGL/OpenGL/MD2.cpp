#include "3DFunction.h"
#include "MD2.h"
vector_t vecAdd(vector_t a, vector_t b)
{
	vector_t c = { 0 };
	for (int i = 0;i<3;i++)
	{
		c.point[i] = a.point[i] + b.point[i];
	}
	return c;
	
}
vector_t vecSub(vector_t a, vector_t b)
{
	vector_t c = { 0 };
	for (int i = 0; i < 3; i++)
	{
		c.point[i] = a.point[i] - b.point[i];
	}
	return c;
}

vector_t vecMul(vector_t a, vector_t b)
{
	vector_t c = { 0 };
	for (int i = 0; i < 3; i++)
	{
		c.point[i] = a.point[i] * b.point[i];
	}
	return c;
}

vector_t vecDiv(vector_t a, vector_t b)
{
	vector_t c = { 0 };
	for (int i = 0; i < 3; i++)
	{
		c.point[i] = a.point[i] / b.point[i];
	}
	return c;
}

modelData_t *LoadMD2Model(char* filename, char* textureName)
{
	FILE *filePtr;//�ļ�ָ��
	int filelen;//ģ���ļ��ĳ���
	char *buffer;//�ļ�����

	modelData_t *model;//ģ��
	modelMD2Header_t *modelHeader;//ģ��ͷ�ļ�
	texture_t *md2Texture;//ģ������

	stIndex_t *stPtr;//��������
	frame_t *frame;//֡����
	vector_t *pointListPtr;//��������
	mesh_t *triIndex;
	mesh_t *bufIndexPtr;//
	int i, j;

	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
	{
		return NULL;
	}

	//��ȡ�ļ�����
	fseek(filePtr, 0, SEEK_END);
	filelen = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	//�������ļ����뻺��
	buffer = (char *)malloc(filelen + 1);
	fread(buffer, sizeof(char), filelen, filePtr);
	//��ȡ�ļ�ͷ
	modelHeader = (modelMD2Header_t *)buffer;
	//Ϊģ�����ݷ����ڴ�
	model = (modelData_t *)malloc(sizeof(modelData_t));
	if (model==NULL)
	{
		return NULL;
	}

	//Ϊģ�͵Ķ�������ڴ�
	model->pointList = (vector_t *)malloc(sizeof(vector_t)* modelHeader->numXYZ*modelHeader->numFrames);
	//�洢��Ч��ģ������
	model->numPoints = modelHeader->numXYZ;//��������
	model->numFrames = modelHeader->numFrames;//֡������
	model->frameSize = modelHeader->framesize;//ÿһ֡�Ĵ�С

	//��ģ���ļ���ѭ������ÿһ֡
	for (j = 0;j<modelHeader->numFrames;j++)
	{
		//��ǰ֡�ж������ݵ�ƫ����
		frame = (frame_t *)&buffer[modelHeader->offsetFrames + modelHeader->framesize*j];

		//����֡��ϸ����Ϣ���㶥���λ��
		pointListPtr = (vector_t *)&model->pointList[modelHeader->numXYZ*j];

		for (i = 0;i<modelHeader->numXYZ;i++)
		{
			pointListPtr[i].point[0] = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];


			pointListPtr[i].point[1] = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];

			pointListPtr[i].point[2] = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
		}
	}

	//����ģ������
	md2Texture = LoadTexture(textureName);
	if (md2Texture !=NULL)
	{
		SetupMD2Texture(md2Texture);
		model->modelTex = md2Texture;
	}
	else 
		return NULL;

	model->st = (texCoord_t *)malloc(sizeof(texCoord_t)*modelHeader->numST);
	model->numST = modelHeader->numST;

	
	stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];

	
	for (i = 0; i < modelHeader->numST; i++)
	{
		model->st[i].s = (float)stPtr[i].s / (float)md2Texture->width;
		model->st[i].t = (float)stPtr[i].t / (float)md2Texture->height;
	}

	
	triIndex = (mesh_t*)malloc(sizeof(mesh_t) * modelHeader->numTris);

	// set total number of triangles
	model->numTriangles = modelHeader->numTris;
	model->triIndex = triIndex;

	// point to triangle indexes in buffer
	bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];

	// create a mesh (triangle) list
	for (j = 0; j < model->numFrames; j++)
	{
		// for all triangles in each frame
		for (i = 0; i < modelHeader->numTris; i++)
		{
			triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
			triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
			triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
			triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
			triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
			triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
		}
	}

	// close file and free memory
	fclose(filePtr);
	free(buffer);

	//��ʼ����������
	model->currentFrame = 0;
	model->nextFrame = 1;
	model->interpol = 0.0;

	return model;

}

void SetupMD2Texture(texture_t* thisTexture)
{
	glGenTextures(1, &thisTexture->texID);
	glBindTexture(GL_TEXTURE_2D, thisTexture->texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	switch (thisTexture->textureType)
	{
	case BMP:
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, thisTexture->width, thisTexture->height,
			GL_RGB, GL_UNSIGNED_BYTE, thisTexture->data);
		break;
	case PCX:
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, thisTexture->width, thisTexture->height,
			GL_RGBA, GL_UNSIGNED_BYTE, thisTexture->data);
	case JPG:
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, thisTexture->width, thisTexture->height,
			GL_RGB, GL_UNSIGNED_BYTE, thisTexture->data);
		break;
	default:
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, thisTexture->width, thisTexture->height,
			GL_RGB, GL_UNSIGNED_BYTE, thisTexture->data);
		break;
	}


}
texture_t *LoadBMPTexture(char *textureName)
{
	BITMAPINFOHEADER texInfo;//BMP�ļ�ͷ
	texture_t* thisTexture = {0};

	thisTexture = (texture_t*)malloc(sizeof(texture_t));
	if (thisTexture == NULL)
	{
		return NULL;
	}

	thisTexture->data = LoadBitmapFile(textureName, &texInfo);

	if (thisTexture->data == NULL)
	{
		free(thisTexture);
		return NULL;
	}

	thisTexture->width = texInfo.biWidth;
	thisTexture->height = texInfo.biHeight;
	thisTexture->palett = NULL;
	thisTexture->textureType = BMP;
	
}

texture_t *LoadTexture(char *textureName)
{
	texture_t *thisTexture = {0};
	char *extStr;//
	extStr = strchr(textureName, '.');//��ȡ�ļ���׺
	extStr++;
	if ((strcmp(extStr,"BMP")==0)||(strcmp(extStr,"bmp")==0))
	{
		thisTexture = LoadBMPTexture(textureName);
	}

	else if ((strcmp(extStr,"JPG")==0)||(strcmp(extStr,"jpg")==0))
	{
		thisTexture = LoadJPGTexture(textureName);

	}

	return thisTexture;

}

unsigned char* LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char		*bitmapImage;			// bitmap image data
	unsigned int		imageIdx = 0;		// image index counter
	unsigned char		tempRGB;				// swap variable

												// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	return bitmapImage;
}

texture_t * LoadJPGTexture(char *textureName)
{
	texture_t * thistexture = { 0 };
	return thistexture;
}
void DisplayMD2(modelData_t* model, int frameNum)
{
	vector_t *pointList;
	int i;

	// create a pointer to the frame we want to show
	pointList = &model->pointList[model->numPoints * frameNum];

	// set the texture
	glBindTexture(GL_TEXTURE_2D, model->modelTex->texID);

	// display the textured model with proper lighting normals
	glBegin(GL_TRIANGLES);
	for (i = 0; i < model->numTriangles; i++)
	{
		/*CalculateNormal(pointList[model->triIndex[i].meshIndex[0]].point,
			pointList[model->triIndex[i].meshIndex[2]].point,
			pointList[model->triIndex[i].meshIndex[1]].point);*/
		glTexCoord2f(model->st[model->triIndex[i].stIndex[0]].s,
			model->st[model->triIndex[i].stIndex[0]].t);
		glVertex3fv(pointList[model->triIndex[i].meshIndex[0]].point);

		glTexCoord2f(model->st[model->triIndex[i].stIndex[2]].s,
			model->st[model->triIndex[i].stIndex[2]].t);
		glVertex3fv(pointList[model->triIndex[i].meshIndex[2]].point);

		glTexCoord2f(model->st[model->triIndex[i].stIndex[1]].s,
			model->st[model->triIndex[i].stIndex[1]].t);
		glVertex3fv(pointList[model->triIndex[i].meshIndex[1]].point);
	}
	glEnd();
}
/************************************************************************/
/* typedef struct
{
	texTypes_t textureType;//�������ͼ���ļ�����

	int width;//����Ŀ��
	int height;//����߶�
	long int scaledWidth;
	long int scaleHeight;//PCXͼ������ſ�Ⱥ͸߶�
	unsigned int texID;//���������������ʾID
	unsigned char *data;//��������
	unsigned char *palett;//����ĵ�ɫ��


}texture_t;                                                                     */
/************************************************************************/