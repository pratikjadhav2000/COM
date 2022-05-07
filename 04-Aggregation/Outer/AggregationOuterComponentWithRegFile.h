#pragma once
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


//CLSID of SubSubtract Component {B95DCFEA-38F5-4B98-BAC8-D15FE0749B08}
const CLSID CLSID_SumSubtract = {0xb95dcfea, 0x38f5, 0x4b98, 0xba, 0xc8, 0xd1, 0x5f, 0xe0, 0x74, 0x9b, 0x8};


//CLSID of ISum Component 
const IID IID_ISum = {0xd02b1711, 0xd2c4, 0x4cea, 0xa7, 0x37, 0xa, 0x53, 0xd3, 0x96, 0x7d, 0x11};


//CLSID of ISubtract Component 
const IID IID_ISubtract = {0xd80b19fb, 0x757f, 0x486e, 0xa9, 0xf5, 0x90, 0xdf, 0xa6, 0xa, 0x50, 0xf5};
