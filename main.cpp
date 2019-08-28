#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
	printf("1\n");
	
	// Register the window class.
	const char CLASS_NAME[] = "Sample Window Class";

	WNDCLASS wc;

	wc.lpfnWndProc		= WindowProc;
	wc.hInstance		= hInstance;
	wc.lpszClassName	= CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	printf("2\n");

	HWND hwnd = CreateWindowEx(
		0,								// Optional window styles.
		CLASS_NAME,						// Window class
		"Learn to Program Windows",		// Window text
		WS_OVERLAPPEDWINDOW,			// Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,		// Parent window
		NULL,		// Menu
		hInstance,	// Instance handle
		NULL		// Additional application data
		);

	printf("3\n");

	if (hwnd == NULL)
	{
		LPVOID lpMsgBuf;
		DWORD last_error = GetLastError();
		DWORD num_chars = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
										FORMAT_MESSAGE_FROM_SYSTEM |
										FORMAT_MESSAGE_IGNORE_INSERTS,
					  				    NULL,
					  				    last_error,
					  				    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					  				    (LPTSTR) &lpMsgBuf,
					  				    0, NULL);
		if(num_chars == 0) {
			printf("There was a problem formatting the message!\n");
			return 0;
		}

		MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK);
		LocalFree(lpMsgBuf);
		return 0;
	}

	printf("4\n");

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			EndPaint(hwnd, &ps);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
