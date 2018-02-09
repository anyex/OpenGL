#include "winmain.h"
#include "3DFunction.h"


HINSTANCE g_hInst;
HDC hdc;
HGLRC hrc;

void SetupPixelFormat(HDC hdc)
{
	int pixelFormat;//������ظ�ʽ������ֵ

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,0,0,0 };
	pixelFormat = ChoosePixelFormat(hdc, &pfd);//����һ����ӽ�pfd���ʺ�hdc�豸�����ظ�ʽ������
	SetPixelFormat(hdc, pixelFormat, &pfd);//�������ظ�ʽ




}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	g_hInst = hInstance;
	HWND hwnd = CreateWnd("OpenGL", "OpenGL����", 400, 400, WindowProc);
	ShowWnd(hwnd);


	return 0;

}



void ShowWnd(HWND hwnd)
{
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

};
HWND CreateWnd(char* className,char* title, int w, int h, void* wndProc)
{
	WNDCLASS	wc = { 0 };
	wc.lpfnWndProc = (WNDPROC)wndProc;
	wc.lpszClassName = className;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(className, title, WS_OVERLAPPEDWINDOW, 200, 200, w, h, NULL, NULL, g_hInst, NULL);

	return hWnd;
};
LRESULT  CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_CREATE:
	{
		hdc = GetDC(hWnd);//��ȡ���ڵ����þ��
		SetupPixelFormat(hdc);//���ô������ظ�ʽ

		hrc = wglCreateContext(hdc);//������Ⱦ����
		wglMakeCurrent(hdc, hrc);//�趨��ǰ�豸�Ļ����Լ���ǰ����Ⱦ����

		SetupMatrices(640, 480);

		InitOpenGL();

		SetTimer(hWnd, 1, 1, NULL);

	}break;

	case  WM_TIMER:
	{
		Render();
		SwapBuffers(hdc);

	}break;
		 
		 


	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);

};

