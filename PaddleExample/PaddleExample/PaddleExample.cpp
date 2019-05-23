// PaddleExample.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PaddleExample.h"
#include "PaddleCLR.h"
#include <exception>
#include <iostream>
#include <string>

#define MAX_LOADSTRING 100


#if __has_include("PaddleCredentials.h")        // Requires VS2015 Update 2 and above
 #include	"PaddleCredentials.h"
#else
/**
 * Default Paddle credentials
 *
 * Copy and paste into "PaddleCredentials.h" and add your own details 
 * to use your Paddle account
 */
 #define	PAD_VENDOR_ID               "11745"
 #define    PAD_VENDOR_NAME             "My Company"
 #define    PAD_API_KEY                 "4134242689d26430f89ec0858884ab07"
 #define    PAD_PRODUCT_ID              "511013"
 #define    PAD_PRODUCT_NAME            "MyCoolApp"
#endif

//---------------------------------------------------------------------------



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PADDLEEXAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PADDLEEXAMPLE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PADDLEEXAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PADDLEEXAMPLE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//---------------------------------------------------------------------------

// Paddle callbacks

void __stdcall beginTransactionCallback()
{
	OutputDebugStringA("beginTransactionCallback\n");
}

void __stdcall transactionCompleteCallback(const char* productID, 
										   const char* userEmail, 
										   const char* userCountry, 
	                                       const char* licenseCode, 
	                                       const char* orderID, 
	                                       bool flagged, 
	                                       const char* processStatusJson)
{
	OutputDebugStringA("transactionCompleteCallback:\n");
	OutputDebugStringA(productID);
	OutputDebugStringA("\n");
	OutputDebugStringA(userEmail);
	OutputDebugStringA("\n");
	OutputDebugStringA(userCountry);
	OutputDebugStringA("\n");
	OutputDebugStringA(licenseCode);
	OutputDebugStringA("\n");
	OutputDebugStringA(orderID);
	OutputDebugStringA("\n");
	OutputDebugStringA(flagged ? "flagged == true" : "flagged == false");
	OutputDebugStringA("\n");
	OutputDebugStringA(processStatusJson);
}

void __stdcall transactionErrorCallback(const char* error)
{
	OutputDebugStringA("transactionErrorCallback\n");
	OutputDebugStringA(error);
}

void __stdcall productActivateCallback(int stateCode, const char* stateString)
{
    OutputDebugStringA("productActivateCallback\n");
    OutputDebugStringA(std::to_string(stateCode).c_str());
    OutputDebugStringA(stateString);
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   // Relevant example code starts here: 

   auto paddle = PaddleCLR::PaddleCLR(PAD_VENDOR_ID, PAD_PRODUCT_ID, PAD_API_KEY, PAD_PRODUCT_NAME, PAD_VENDOR_NAME);

   paddle.SetBeginTransactionCallback(beginTransactionCallback);
   paddle.SetTransactionCompleteCallback(transactionCompleteCallback);
   paddle.SetTransactionErrorCallback(transactionErrorCallback);
   paddle.ShowCheckoutWindow(PAD_PRODUCT_ID);

   OutputDebugStringA("Checkout complete\n");

   return TRUE;
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);


				}
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
