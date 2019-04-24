#pragma once

#define DllExport   __declspec(dllexport)


//namespace PaddleCLR 
//{
//	ref class Wrapper
//	{
//	public:
//		// TODO: Add your methods for this class here.
//		Wrapper(const char* vendorId, const char* productId, const char* apiKey, const char* productName, const char* vendorName);
//		void setup();
//		void ShowCheckoutWindow(const char* productId);
//
//	private:
//		PaddleWrapper::PaddleWrapper^ paddleWrapper;
//	};
//}

/*
DllExport void ShowMessageBox(int *value)
{
	ManagedDll::DoWork work;
	work.ShowCSharpMessageBox(value);
}
*/

class PaddleWrapperPrivate;

class DllExport PaddleCLR
{
public:
	PaddleCLR(const char* vendorId, const char* productId, const char* apiKey, const char* productName, const char* vendorName);
	~PaddleCLR();
	void ShowCheckoutWindow(const char* productId);
	
private: 
	PaddleWrapperPrivate* wrapper;

};