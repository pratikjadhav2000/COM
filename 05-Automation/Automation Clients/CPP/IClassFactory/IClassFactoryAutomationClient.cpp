#include<windows.h>
#include "AutomationServerWithRegFile.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND , UINT, WPARAM, LPARAM);


//global variable declarations
IMyMath *pIMyMath = NULL;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("PratikClient");
	HRESULT hr;

	//code
	//COM Initialization
	hr=CoInitialize(NULL);
	if(FAILED(hr))
	{
		MessageBox(NULL, TEXT("1:COM Library Can not be initialized.\nProgram Will Now Exit"), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc; 
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	//create the window in memory
	hwnd = CreateWindow(szAppName,
		TEXT("Client of Pratik COM Dll Server"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop(windows) //event loop(linux) //run loop (mac os) // game loop(rendering technology)
	while (GetMessage(&msg, NULL, 0, 0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	//COM un-initialization
	CoUninitialize();
	return ((int)msg.wParam);



}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	
	HRESULT hr;
	int iNum1,iNum2,iSum;
	TCHAR str[255];

	//code
	switch (iMsg)
	{

	case WM_CREATE:

		//code of client
	hr=CoCreateInstance(CLSID_MyMath,NULL,CLSCTX_INPROC_SERVER,IID_IMyMath,(void **)&pIMyMath);

	if(FAILED(hr))
	{
		MessageBox(hwnd, TEXT("IMyMath Interface cannot be obtained"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}

	//initialize arguements hardcoded
	iNum1=300;
	iNum2=200;

	//call SumOfTwoIntegers() of ISum to get sum
	pIMyMath->SumOfTwoIntegers(iNum1, iNum2, &iSum);

	//display the result
	wsprintf(str,TEXT("Sum Of %d And %d = %d"), iNum1, iNum2, iSum);
	MessageBox(hwnd, str, TEXT("Result"), MB_OK);

	iNum1=300;
	iNum2=200;
	//again call SubtractionOfTwoIntegers() of ISum to get new sum
	pIMyMath->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);


	//display the result
	wsprintf(str,TEXT("Substraction Of %d And %d = %d"), iNum1, iNum2, iSum);
	MessageBox(hwnd, str, TEXT("Result"), MB_OK);


	pIMyMath->Release();
	pIMyMath=NULL;

	//exit the application
	DestroyWindow(hwnd);
	
		break;
			
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}


