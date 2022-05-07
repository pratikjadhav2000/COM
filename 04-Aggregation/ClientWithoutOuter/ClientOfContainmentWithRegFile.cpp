#include<windows.h>
#include "AggregationInnerComponentWithRegFile.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND , UINT, WPARAM, LPARAM);


//global variable declarations
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Pratik_Containment_Client");
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
	int iNum1,iNum2,iMultiplication,iDivision;
	TCHAR str[255];

	//code
	switch (iMsg)
	{

	case WM_CREATE:

		//code of client
	hr=CoCreateInstance(CLSID_MultiplicationDivision,NULL,CLSCTX_INPROC_SERVER,IID_IMultiplication,(void **)&pIMultiplication);
	if(FAILED(hr))
	{
		MessageBox(hwnd, TEXT("IMultiplication Interface Can not be Obtained"), TEXT("Error"), MB_OK);
		exit(0);
	}

	iNum1=20;
	iNum2=30;
	//again call MultiplicationOfTwoIntegers() of ISubtract to get new sum
	pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);

	//display the result
	wsprintf(str,TEXT("Multiplication Of %d And %d = %d"), iNum1, iNum2, iMultiplication);
	MessageBox(hwnd, str, TEXT("Result"), MB_OK);

	//call QueryInterface(IID_IDivision,(void **)&pIDivision);
	hr=pIMultiplication->QueryInterface(IID_IDivision,(void **)&pIDivision);
	if(FAILED(hr))
	{
		MessageBox(hwnd, TEXT("IDivision Interface Can not be Obtained"), TEXT("Error"), MB_OK);
		exit(0);
	}

	//as IMultiplication is not not needed onwords,release it
	pIMultiplication->Release();
	pIMultiplication=NULL;

	iNum1=500;
	iNum2=10;
	//again call DivisionOfTwoIntegers() of ISum to get new sum
	pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);

	//display the result
	wsprintf(str,TEXT("Division Of %d And %d = %d"), iNum1, iNum2, iDivision);
	MessageBox(hwnd, str, TEXT("Result"), MB_OK);

	//as IDivision is not not needed onwords,release it
	pIDivision->Release();
	pIDivision=NULL;


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


