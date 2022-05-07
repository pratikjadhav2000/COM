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


//CLSID of SubSubtract Component // {412375D3-44CB-43E6-B940-AA7CDB4F01CA}
const CLSID CLSID_MultiplicationDivision = {0x412375d3, 0x44cb, 0x43e6, 0xb9, 0x40, 0xaa, 0x7c, 0xdb, 0x4f, 0x1, 0xca};


//CLSID of ISum Component 
const IID IID_IMultiplication = {0x83062934, 0xa205, 0x4ed3, 0x9d, 0x59, 0xab, 0x54, 0xf1, 0x16, 0x88, 0x49};


//CLSID of ISubtract Component 
const IID IID_IDivision = {0xb50fc34e, 0xf6ab, 0x4204, 0xb0, 0x66, 0x84, 0xd5, 0x83, 0xea, 0x1e, 0xea};
