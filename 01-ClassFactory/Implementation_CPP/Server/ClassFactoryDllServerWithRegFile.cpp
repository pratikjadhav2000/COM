#include<windows.h>
#include "ClassFactoryDllServerWithRegFile.h"
//class declarations
class CSumSubtract :public ISum,ISubtract,IMultiply
{
private:
	long m_cRef; //member of class reference variable

public:
	//constructor method declaration
	CSumSubtract(void);
	~CSumSubtract(void);
	//IUnknown specific method declarations (inherited)

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum specific method declarations(inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);

	//ISubtract specific method declarations(inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);


	//IMultiply specific method declarations(inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);

};


class CSumSubtractClassFactory:public IClassFactory
{

private:
	long m_cRef;

public:
	//constructor method declarations
	CSumSubtractClassFactory(void);
	//destructor
	~CSumSubtractClassFactory(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory methods
	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);

};

//global varibale declarations
long glNumberOfActiveComponents=0; //number of active components
long glNumberOfServerLocks=0; //number of locks on this dll

//DllMain

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
{
	//code
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
	    MessageBox(NULL, TEXT("Inside DLL_PROCESS_ATTACH "), TEXT("Error"), MB_OK);

		break;

		case DLL_PROCESS_DETACH:
		MessageBox(NULL, TEXT("Inside DLL_PROCESS_DETACH "), TEXT("Error"), MB_OK);

		break;
		
	}
	return(TRUE);

}

//Implementation of csumsubtract's constructor method

CSumSubtract::CSumSubtract(void)
{
	//code
	m_cRef=1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter

}

//implementation of destructor method
CSumSubtract::~CSumSubtract(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter

}

HRESULT CSumSubtract::QueryInterface(REFIID riid,void **ppv)
{
	MessageBox(NULL, TEXT("Inside CSumSubtract QueryInterface"), TEXT("Error"), MB_OK);

	//code
	if(riid==IID_IUnknown)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISum)
		*ppv=static_cast<ISum *>(this);
	else if(riid==IID_ISubtract)
		*ppv=static_cast<ISubtract *>(this);
	else if(riid==IID_IMultiply)
		*ppv=static_cast<IMultiply *>(this);	
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);


}

ULONG CSumSubtract::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//implementation of ISum method
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	//code
	*pSum=num1+num2;
	return(S_OK);
}

//implementation of ISubtract method
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
	//code
	*pSubtract=num1-num2;
	return(S_OK);
}

//implementation of IMultiply method
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiply)
{
	//code
	*pMultiply=num1*num2;
	return(S_OK);
}


//implementation of CSumSubtractClassFactory's Constructor Method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//code
	m_cRef = 1; //hardcoded to anticipate failure of queryinterface()

}

//implementation of CSumSubtractClassFactory's Destructor Method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	//code
}


//Implemetation of CCumSubtractClassFactory's IclassFactory IUnkown methods

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	MessageBox(NULL, TEXT("Inside CSumSubtractClassFactory QueryInterface"), TEXT("Error"), MB_OK);

	//code
		//code
	if(riid==IID_IUnknown)
		*ppv=static_cast<IClassFactory *>(this);
	else if(riid==IID_IClassFactory)
		*ppv=static_cast<IClassFactory *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);

}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if(m_cRef==0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of CSumSubtractClassFactory's IClassFactory Methods

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	//variable declarations
	CSumSubtract *pCSumSubtract=NULL;
	HRESULT hr;
	//code
	if(pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	//create the instance of component i.e. of CSumSubtract class
	pCSumSubtract=new CSumSubtract;
	if(pCSumSubtract==NULL)
		return(E_OUTOFMEMORY);
	//get the requested interface
	hr=pCSumSubtract->QueryInterface(riid,ppv);

	MessageBox(NULL, TEXT("Inside CSumSubtract CreateInstance"), TEXT("Error"), MB_OK);

	pCSumSubtract->Release(); //anticipate failure of queryinterface
	return(hr);

}

HRESULT CSumSubtractClassFactory::LockServer(BOOL flock)
{
	//code
	if(flock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);

}

//Implementation of Exported Functions from this DLL
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,void **ppv)
{
		//varible declarations
	CSumSubtractClassFactory *pCSumSubtractClassFactory=NULL;
	HRESULT hr;

	//code
	if(rclsid!=CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create class factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if(pCSumSubtractClassFactory==NULL)
		return(E_OUTOFMEMORY);

	hr=pCSumSubtractClassFactory->QueryInterface(riid,ppv);
	if(FAILED(hr))
	{
		MessageBox(NULL, TEXT("pCSumSubtractClassFactory QueryInterface FAILED"), TEXT("Program Error"), MB_OK);
		exit(0);
	}
	MessageBox(NULL, TEXT("Inside DllGetClassObject"), TEXT("Error"), MB_OK);

	pCSumSubtractClassFactory->Release();		//To balance the hardcoded mcref 1

	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void){
//code
	if((glNumberOfActiveComponents==0) && (glNumberOfServerLocks==0))
		return(S_OK);
	else
		return(S_FALSE);
}






