#pragma once

#undef INTERFACE 
#define INTERFACE ISum
DECLARE_INTERFACE_(ISum, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE; 	
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

#undef INTERFACE 
#define INTERFACE ISubtract
DECLARE_INTERFACE_(ISubtract, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE; 	
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

//THIS_ is hidden parameter.1st parameter should be object itself


//CLSID of SubSubtract Component {6A13B11D-5605-4B0C-93E1-44011108AC12}
const CLSID CLSID_SumSubtract = {0x6a13b11d, 0x5605, 0x4b0c, 0x93, 0xe1, 0x44, 0x1, 0x11, 0x8, 0xac, 0x12};


//CLSID of ISum Component 
const IID IID_ISum = {0x6d0d9db2, 0xb7c1, 0x4759, 0xa2, 0x6f, 0xb5, 0x63, 0xd4, 0x99, 0xae, 0x71};


//CLSID of ISubtract Component 
const IID IID_ISubtract = {0x789a8567, 0x646f, 0x4709, 0xb3, 0x8c, 0x0, 0x51, 0x48, 0x9e, 0x6, 0xdb};
