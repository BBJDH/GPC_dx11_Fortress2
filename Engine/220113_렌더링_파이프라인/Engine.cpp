#include<Windows.h>

namespace Rendering
{
	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter);
}


namespace Engine
{
	LRESULT CALLBACK Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
			
			case WM_CREATE:
			{
				Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);
				return 0;
			}
			case WM_APP:
			{
				Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

				return 0;
			}
			case WM_SIZE:
			{
				Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

				return 0;
			}
			case WM_DESTROY:
			{
				Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

				PostQuitMessage(0);

				return 0;
			}
			default:
			{
				return DefWindowProc(hWindow,uMessage,wParameter,lParameter);
			}
		}
	}

}
