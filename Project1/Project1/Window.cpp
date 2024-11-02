/************************************************************************************************************
MIT License

CX3D Game Framework (https://github.com/PardCode/CX3D)

Copyright (c) 2019-2024, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
************************************************************************************************************/

/************************************************************************************************************
 * Library Include Files
************************************************************************************************************/
#include "Window.h"

/************************************************************************************************************
 * Application Include Files
************************************************************************************************************/
/* NONE */

/************************************************************************************************************
 * Feature Include Files
************************************************************************************************************/
/* NONE */

/************************************************************************************************************
 * Feature Macro Definitions
************************************************************************************************************/
/* NONE */

/************************************************************************************************************
 * Feature Level Type Definitions
************************************************************************************************************/
Window* window = NULL;

/************************************************************************************************************
 * Feature Level External Variables
************************************************************************************************************/
/* NONE */

/************************************************************************************************************
 * Task Local Function Prototypes
************************************************************************************************************/
/* NONE */

Window::Window()
{

}

// Events 
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {

    case WM_CREATE:
    {
        // Event fired when the window will be created
        window->onCreate();
        break;
    }

    case WM_DESTROY:
    {
        // Event fired when the window will be destroyed
        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    }
    default:
    {
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return NULL;
    }

}

bool Window::init()
{
    // Setting up the WNDCLASSEX object
    WNDCLASSEX wc;

    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;

    if (!::RegisterClassEx(&wc))
    {
        return false;
    }

    // Set the pointer 
    if (!window)
    {
        window = this;
    }


    //Creation of the window
   // M_HWND = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, NULL);
    HWND M_HWND = CreateWindowExW(
        WS_EX_OVERLAPPEDWINDOW,
        L"MyWindowClass",          // U퓓j L przed ci퉓iem
        L"DirectX Application",    // U퓓j L przed ci퉓iem
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1024,
        768,
        NULL,
        NULL,
        NULL,
        NULL
    );


    // if the creation of the window fail, return false
    if (!M_HWND)
    {
        return false;
    }

    ::ShowWindow(M_HWND, SW_SHOW);
    ::UpdateWindow(M_HWND);



    // set this flag to true, to indicate that the window is initialized and running
    m_is_run = true;

    // Initialize the window
    return true;
}

bool Window::broadcast()
{
    MSG msg;

    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    window->onUpdate();

    Sleep(0);

    return true;
}

bool Window::release()
{
    // Release the window

    if (!::DestroyWindow(M_HWND))
    {
        return false;
    }

    return true;
}

bool Window::isRun()
{
    return m_is_run;
}

void Window::onDestroy()
{
    // set this flag to false, to indicate that the window is not initialized and running
    m_is_run = false;
}

Window ::~Window()
{

}