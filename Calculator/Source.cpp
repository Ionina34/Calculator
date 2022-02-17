﻿#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"

CONST UINT WINDOW_WIDTH = 260;
CONST UINT WINDOW_HEIGHT = 350;
UINT i_btn_size = 50;  //Размер кнопки
UINT interval = 2;    //Интервал между кнопками

CONST CHAR g_szClassName[] = "Calculator";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrewInst, LPSTR lmCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = (HICON)LoadImage(hInstance, "calculator.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "calculator.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	wc.hCursor - LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_szClassName;
	wc.lpszMenuName = NULL;

	if (!RegisterClassExA(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND hwnd = CreateWindowEx
	(
		NULL,                                                     //exStyles
		g_szClassName,                                            //Window class
		g_szClassName,                                            //Window title
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //Главное окно, со строкой загловка, не изменяются по размеру
		CW_USEDEFAULT, CW_USEDEFAULT,                             //Position
		WINDOW_WIDTH, WINDOW_HEIGHT,                              //Size
		NULL,                                                     //Parent
		NULL,                                                     //Menu
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",//Windoe class for EditConstrol
			NULL,//Text
			WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY | ES_NUMBER | WS_BORDER,
			10, 10,
			(WINDOW_WIDTH - 35), i_btn_size,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);

		//////////////////////////////////////////////////////////////////
		//////////////////    Create buttons    //////////////////////////
		//////////////////////////////////////////////////////////////////

		UINT start_x = 10;
		UINT start_y = 70;
		//UINT i_btn_size = 50;  //Размер кнопки
		//UINT interval = 2;    //Интервал между кнопками

		INT digit = 1;
		CHAR  sz_digit[5];

		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 3; j++)
			{
				CreateWindowEx
				(
					NULL, "Button", _itoa(digit, sz_digit, 10),
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					start_x + (i_btn_size + interval) * j, start_y + (i_btn_size + interval) * i,
					i_btn_size, i_btn_size,
					hwnd,
					(HMENU)(IDC_BTN_0 + digit),
					GetModuleHandle(NULL),
					NULL
				);
				digit++;
			}
		}
	}
	break;
	case WM_COMMAND:break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}