#include<windows.h>
#include "AutomationServerWithRegFile.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND , UINT, WPARAM, LPARAM);


//global variable declarations
IDispatch *pIDispatch = NULL;

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

	DISPID dispid;
	OLECHAR *szFunction1 = L"SumOfTwoIntegers";
	OLECHAR *szFunction2 = L"SubtractionOfTwoIntegers";
	VARIANT vArg[2], vRet;
	DISPPARAMS param = { vArg,0,2,NULL };

	//code
	switch (iMsg)
	{

	case WM_CREATE:
				MessageBox(hwnd, str, TEXT("Inside wmcreate"), MB_OK);

		//code of client
	hr=CoCreateInstance(CLSID_MyMath,NULL,CLSCTX_INPROC_SERVER,IID_IDispatch,(void **)&pIDispatch);

	if(FAILED(hr))
	{
		MessageBox(hwnd, TEXT("IDispatch Interface cannot be obtained"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}

	iNum1 = 155;
	iNum2 = 145;

	VariantInit(vArg);		//name of array is address
	vArg[0].vt = VT_INT;
	vArg[0].intVal = iNum2;
	vArg[1].vt = VT_INT;
	vArg[1].intVal = iNum1;
	param.cArgs = 2;
	param.cNamedArgs = 0;
	param.rgdispidNamedArgs = NULL;
	param.rgvarg = vArg;

	VariantInit(&vRet);	//not array hence &

	hr = pIDispatch->GetIDsOfNames(IID_NULL,&szFunction1,1,GetUserDefaultLCID(),&dispid);

	if(FAILED(hr))
	{
		MessageBox(hwnd, TEXT("IDispatch Interface cannot be obtained"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}

	hr = pIDispatch->Invoke(dispid,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,&param,&vRet,NULL,NULL);

	if(FAILED(hr))
	{
		MessageBox(hwnd, TEXT("IDispatch Interface cannot be obtained"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}
		wsprintf(str,TEXT("Sum Of %d And %d = %d"), iNum1, iNum2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("SUMOFTWOINTEGERS"), MB_OK);


hr = pIDispatch->GetIDsOfNames(IID_NULL,&szFunction2,1,GetUserDefaultLCID(),&dispid);

	if(FAILED(hr))
	{
		MessageBox(hwnd, TEXT("IDispatch Interface cannot be obtained"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}

	hr = pIDispatch->Invoke(dispid,IID_NULL,GetUserDefaultLCID(),DISPATCH_METHOD,&param,&vRet,NULL,NULL);

	if(FAILED(hr))
	{
		MessageBox(hwnd, TEXT("IDispatch Interface cannot be obtained"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}
		wsprintf(str,TEXT("Subtraction Of %d And %d = %d"), iNum1, iNum2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("SUBTRACTOFTWOINTEGERS"), MB_OK);

	
		pIDispatch->Release();
		pIDispatch = NULL;
	

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


