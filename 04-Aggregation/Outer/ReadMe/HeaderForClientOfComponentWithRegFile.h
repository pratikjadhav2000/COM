#pragma once
class IMultiplication:public IUnknown
{
public:
	//ISum specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *)=0; //pure virtual
};

class IDivision:public IUnknown
{
public:
	//ISubtract specific method declarations
		virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *)=0; //pure virtual

};

class ISum:public IUnknown
{
public:
	//ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *)=0; //pure virtual
};

class ISubtract:public IUnknown
{
public:
	//ISubtract specific method declarations
		virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *)=0; //pure virtual

};


//CLSID of SubSubtract Component {6A13B11D-5605-4B0C-93E1-44011108AC12}
const CLSID CLSID_SumSubtract = {0x6a13b11d, 0x5605, 0x4b0c, 0x93, 0xe1, 0x44, 0x1, 0x11, 0x8, 0xac, 0x12};


//CLSID of ISum Component 
const IID IID_IMultiplication = {0x83062934, 0xa205, 0x4ed3, 0x9d, 0x59, 0xab, 0x54, 0xf1, 0x16, 0x88, 0x49};


//CLSID of ISubtract Component 
const IID IID_IDivision = {0xb50fc34e, 0xf6ab, 0x4204, 0xb0, 0x66, 0x84, 0xd5, 0x83, 0xea, 0x1e, 0xea};

//CLSID of ISum Component 
const IID IID_ISum = {0x6d0d9db2, 0xb7c1, 0x4759, 0xa2, 0x6f, 0xb5, 0x63, 0xd4, 0x99, 0xae, 0x71};

//CLSID of ISubtract Component 
const IID IID_ISubtract = {0x789a8567, 0x646f, 0x4709, 0xb3, 0x8c, 0x0, 0x51, 0x48, 0x9e, 0x6, 0xdb};
