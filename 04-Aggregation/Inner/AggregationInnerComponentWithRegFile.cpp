#include<windows.h>
#include "AggregationInnerComponentWithRegFile.h"

//interface declarations 
interface INoAggregationIUnknown
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};


//class declarations
class CMultiplicationDivision :public INoAggregationIUnknown, IMultiplication, IDivision
{
private:
	long m_cRef; //member of class reference variable
	IUnknown *m_pIUnknownOuter;

public:
	//constructor method declaration
	CMultiplicationDivision(IUnknown *);
	~CMultiplicationDivision(void);
	//IUnknown specific method declarations (inherited)

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//Aggregation NonSupported IUnknown specific method declarations (inherited)

	HRESULT __stdcall QueryInterface_NoAggregation(REFIID,void **);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);

	//IMultiplication specific method declarations(inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);

	//IDivision specific method declarations(inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);

};


class CMultiplicationDivisionClassFactory:public IClassFactory
{

private:
	long m_cRef;

public:
	//constructor method declarations
	CMultiplicationDivisionClassFactory(void);
	//destructor
	~CMultiplicationDivisionClassFactory(void);

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

//Implementation of CMultiplicationDivision's constructor method

CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnknownOuter)
{
	//code
	m_cRef=1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter

	if(pIUnknownOuter != NULL)
		m_pIUnknownOuter = pIUnknownOuter;
	else
		m_pIUnknownOuter = reinterpret_cast<IUnknown *>(static_cast<INoAggregationIUnknown *>(this));

}

//implementation of destructor method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter

}

//Aggregation supporting IUnknown methods

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid,void **ppv)
{
	return(m_pIUnknownOuter->QueryInterface(riid, ppv));

}

ULONG CMultiplicationDivision::AddRef(void)
{
	return(m_pIUnknownOuter->AddRef());
}

ULONG CMultiplicationDivision::Release(void)
{
	return(m_pIUnknownOuter->Release());
}

//Aggregation non supporting IUnknown methods

HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid,void **ppv)
{
	MessageBox(NULL, TEXT("Inside CMultiplicationDivision QueryInterface_NoAggregation"), TEXT("Error"), MB_OK);

	//code
	if(riid==IID_IUnknown)
		*ppv=static_cast<INoAggregationIUnknown *>(this);
	else if(riid==IID_IMultiplication)
		*ppv=static_cast<IMultiplication *>(this);
	else if(riid==IID_IDivision)
		*ppv=static_cast<IDivision *>(this);
	else
	{
		MessageBox(NULL, TEXT("Inside ELSE - riid not found. CMultiplicationDivision QueryInterface_NoAggregation"), TEXT("Error"), MB_OK);
		*ppv=NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	MessageBox(NULL, TEXT("Leaving CMultiplicationDivision QueryInterface_NoAggregation"), TEXT("Error"), MB_OK);

	return(S_OK);


}

ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivision::Release_NoAggregation(void)
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

//implementation of IMultiplication method
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	//code
	*pMultiplication=num1*num2;
	return(S_OK);
}

//implementation of IDivision method
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	//code
	if(num2==0)
	{
	MessageBox(NULL, TEXT("Divide by Zero Error"), TEXT("Error"), MB_OK);
	return(S_FALSE);
	}
	*pDivision=num1/num2;
	return(S_OK);
}


//implementation of CMultiplicationDivisionClassFactory's Constructor Method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	//code
	m_cRef = 1; //hardcoded to anticipate failure of queryinterface()

}

//implementation of CMultiplicationDivisionClassFactory's Destructor Method
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	//code
}


//Implemetation of CCumSubtractClassFactory's IclassFactory IUnkown methods

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	MessageBox(NULL, TEXT("Inside CMultiplicationDivisionClassFactory QueryInterface"), TEXT("Error"), MB_OK);

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

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
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

//Implementation of CMultiplicationDivisionClassFactory's IClassFactory Methods

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	//variable declarations
	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;
	//code
	if((pUnkOuter != NULL) && (riid != IID_IUnknown))
		return(CLASS_E_NOAGGREGATION);

	//create the instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision=new CMultiplicationDivision(pUnkOuter);
	if(pCMultiplicationDivision==NULL)
		return(E_OUTOFMEMORY);
	//get the requested interface
	hr=pCMultiplicationDivision->QueryInterface_NoAggregation(riid,ppv);

	MessageBox(NULL, TEXT("Inside CMultiplicationDivision CreateInstance "), TEXT("Error"), MB_OK);

	pCMultiplicationDivision->Release_NoAggregation(); //anticipate failure of queryinterface
	return(hr);

}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL flock)
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
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory=NULL;
	HRESULT hr;

	//code
	if(rclsid!=CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create class factory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if(pCMultiplicationDivisionClassFactory==NULL)
		return(E_OUTOFMEMORY);

	hr=pCMultiplicationDivisionClassFactory->QueryInterface(riid,ppv);
	if(FAILED(hr))
	{
		MessageBox(NULL, TEXT("pCMultiplicationDivisionClassFactory QueryInterface FAILED"), TEXT("Program Error"), MB_OK);
		exit(0);
	}
	MessageBox(NULL, TEXT("Inside DllGetClassObject"), TEXT("Error"), MB_OK);

	pCMultiplicationDivisionClassFactory->Release();		//To balance the hardcoded mcref 1

	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void){
//code
	if((glNumberOfActiveComponents==0) && (glNumberOfServerLocks==0))
		return(S_OK);
	else
		return(S_FALSE);
}






