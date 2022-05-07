#pragma once

#undef INTERFACE 
#define INTERFACE IMyMath
DECLARE_INTERFACE_(IMyMath, IDispatch)
{
	//prototype for IUnknown Methods
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE; 	
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;


	//prototype for IDispatch Methods
	STDMETHOD(GetTypeInfoCount)(THIS_ UINT *) PURE;
    STDMETHOD(GetTypeInfo)(THIS_ UINT, LCID, ITypeInfo **) PURE;
    STDMETHOD(GetIDsOfNames)(THIS_ REFIID, LPOLESTR *, UINT, LCID, DISPID *) PURE;
    STDMETHOD(Invoke)(THIS_ DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *) PURE;

    //prototype for user methods
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
	STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

//THIS_ is hidden parameter.1st parameter should be object itself

// CLSID of MyMath Component :  {4827347A-C14A-4A9E-B49E-DB93F9BBCB98}
const CLSID CLSID_MyMath = {0x4827347a, 0xc14a, 0x4a9e, 0xb4, 0x9e, 0xdb, 0x93, 0xf9, 0xbb, 0xcb, 0x98};

// IID of IMyMath Interface  :  {A93A9F4F-75EA-43A6-AB5D-3466423A9D6C}
const IID IID_IMyMath = {0xa93a9f4f, 0x75ea, 0x43a6, 0xab, 0x5d, 0x34, 0x66, 0x42, 0x3a, 0x9d, 0x6c};