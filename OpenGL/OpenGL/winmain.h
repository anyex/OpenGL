#pragma once
#include "windows.h"


HWND CreateWnd(char* className, char* WndTitle, int w, int h,void* wndProc);//��������

void ShowWnd(HWND hwnd);//��ʾ����

LRESULT  CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//���ڴ�����

void SetupPixelFormat(HDC hdc);//��������
