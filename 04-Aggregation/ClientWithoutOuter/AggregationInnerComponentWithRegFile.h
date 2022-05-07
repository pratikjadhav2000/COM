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


//CLSID of SubSubtract Component // {3E9A72FE-9C2B-4E8D-AECA-4709D40F0CC4}
const CLSID CLSID_MultiplicationDivision = {0x3e9a72fe, 0x9c2b, 0x4e8d, 0xae, 0xca, 0x47, 0x9, 0xd4, 0xf, 0xc, 0xc4};


//CLSID of ISum Component 
const IID IID_IMultiplication = {0x47f6c224, 0x94ae, 0x4502, 0x84, 0x1a, 0x88, 0x7, 0x30, 0xcb, 0xb5, 0xd5};


//CLSID of ISubtract Component 
const IID IID_IDivision = {0x6e8a923c, 0x4357, 0x47fa, 0x8d, 0xf5, 0x68, 0x67, 0xd3, 0x22, 0xd, 0x4d};
