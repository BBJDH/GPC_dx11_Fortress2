#include<Windows.h>
#include "Rendering.h"

namespace Rendering
{
	namespace Pipeline
	{
		void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter);
	}

	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
		case WM_CREATE:
		{
			Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);
			return;
		}
		case WM_APP:
		{
			Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

			return;
		}
		case WM_SIZE:
		{
			Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

			return;
		}
		case WM_DESTROY:
		{
			Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

			return;
		}
		}
	}

}