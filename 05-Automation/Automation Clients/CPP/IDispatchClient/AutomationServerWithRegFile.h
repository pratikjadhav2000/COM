class IMyMath : public IDispatch
{
    public:
       
        virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;

        virtual HRESULT __stdcall SubtractionOfTwoIntegers( int , int ,int* )=0;

};

// CLSID of MyMath Component :  {4827347A-C14A-4A9E-B49E-DB93F9BBCB98}
const CLSID CLSID_MyMath = {0x4827347a, 0xc14a, 0x4a9e, 0xb4, 0x9e, 0xdb, 0x93, 0xf9, 0xbb, 0xcb, 0x98};

// IID of IMyMath Interface  :  {A93A9F4F-75EA-43A6-AB5D-3466423A9D6C}
const IID IID_IMyMath = {0xa93a9f4f, 0x75ea, 0x43a6, 0xab, 0x5d, 0x34, 0x66, 0x42, 0x3a, 0x9d, 0x6c};