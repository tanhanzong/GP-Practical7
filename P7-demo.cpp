#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

boolean x = true, y = true, z = true;

//Step 1: Variable declaration.
GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		else if (wParam == 0x58)
		{
			x = true;
		}
		else if (wParam == 0x59)
		{
			y = true;
		}
		else if (wParam == 0x5A)
		{
			z = true;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void initTexture() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "Box.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | 
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
}

void drawCube(float sz)
{
	glBegin(GL_QUADS);
	//front
	glColor3f(1, 0, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(sz, 0.0f, sz);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	//left
	glColor3f(0, 1, 0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(1.0, 1.0f);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, sz);

	//top
	glColor3f(0, 0, 1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(sz, 0.0f, sz);

	//right
	glColor3f(1, 1, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(sz, 0.0f, sz);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);

	//bottom
	glColor3f(0, 1, 1);

	glTexCoord2f(1.0, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	//back
	glColor3f(1, 0, 1);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glEnd();
}

void drawPyramid(float sz)
{
	glColor3f(1, 1, 1);
	//bottom
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(sz, 0, 0);
	glVertex3f(sz, sz, 0);
	glVertex3f(0, sz, 0);
	//front
	glVertex3f(0, 0, 0);
	glVertex3f(sz, 0, 0);
	glVertex3f(0.25, 0.25, sz);
	//left
	glVertex3f(0, 0, 0);
	glVertex3f(0, sz, 0);
	glVertex3f(0.25, 0.25, sz);
	//back
	glVertex3f(0, sz, 0);
	glVertex3f(sz, sz, 0);
	glVertex3f(0.25, 0.25, sz);
	//right
	glVertex3f(sz, 0, 0);
	glVertex3f(sz, sz, 0);
	glVertex3f(0.25, 0.25, sz);
	glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//Step 4: Assign texture to polygon.
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	drawCube(0.5);

	if (x == true) {
		glRotatef(-0.05, 1, 0, 0);
	}
	if (y == true) {
		glRotatef(-0.05, 0, 1, 0);
	}
	if (z == true) {
		glRotatef(-0.05, 0, 0, 1);
	}

	//Step 5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	//drawPyramid(0.5);
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	initTexture();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------