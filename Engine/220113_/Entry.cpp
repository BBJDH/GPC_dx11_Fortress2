#include <Windows.h>

namespace Engine
{ LRESULT CALLBACK Procedure(HWND   const , UINT   const , WPARAM const , LPARAM const );}
//#define GPC_UPDATE WM_APP
//#define GPC_END WM_APP +1
//�̷� �뵵�� ����� ���� �޼����� ������ ���

int APIENTRY WinMain
(
    _In_     HINSTANCE  const hInstance, //nullptr ������ _in_ ������ ���Ŀ� ���ؼ���!
    _In_opt_ HINSTANCE  const hPrevInstance, //_In_ �ɼų� �������� ���
    _In_     LPSTR      const lpCmdLine, //�߰��Ǵ� Ŀ�ǵ� ������ �޴´�
    //LPSTR ->longptr string 
    _In_     int        const nShowCmd //�����ǿ� ������� �ѻ��·� ���� �Ǿ����� ����
)
{


    HWND hWindow = HWND(); //������ â ����
    {//���Ŀ� ���� ����
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize = sizeof(WNDCLASSEX);  //������ ������ ����
        Class.lpfnWndProc = Engine::Procedure;
        Class.hInstance = hInstance; //�ν��Ͻ� �ڵ� (��� �ν��Ͻ� �Ҽ��ΰ�)
        Class.hIcon = LoadIcon(hInstance, IDI_APPLICATION);  //������ ��� ������
        //�Ϲ����� ���ø����̼� ������ ���
        Class.hCursor = LoadCursor(hInstance, IDC_ARROW); //���콺 ��� ������
        Class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        //��� �귯�� �ڵ�
        Class.lpszClassName = "Window";
        /*Ŭ���� ���� ���� like (class name)*/
        Class.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
        //â �»�ܿ� �ߴ� ���� ������ 

        RegisterClassEx(&Class);
    }
    { 
        CREATESTRUCT Window = CREATESTRUCT();
        //CREATESTUCT Ư���������� ����
        //�Լ� �������޽� ������ �ڹٲ�Ƿ� �������� �����Ǿ��ִ�
        Window.lpszClass = "Window";  //String terminated by Zero
        Window.lpszName = "Game";    //-> null�� ������ ���ڿ�
        Window.style = WS_OVERLAPPEDWINDOW; //�ڿ� ������ �پ����
        Window.cx = 1280;
        Window.cy = 720;
        Window.hInstance = hInstance;

        {//������ �۾����� ���߱�
            RECT Rectangle = RECT();
            Rectangle.right = Window.cx;
            Rectangle.bottom = Window.cy;

            AdjustWindowRectEx(&Rectangle, Window.style, static_cast<bool>(Window.hMenu), Window.dwExStyle);
            //cx cy�� ���ؼ� ������ ��Ÿ�Ͽ� �°� ���ۼ����ش�
            Window.cx = Rectangle.right - Rectangle.left;
            Window.cy = Rectangle.bottom - Rectangle.top;

            //ȭ�� ����� ����
            Window.x = (GetSystemMetrics(SM_CXSCREEN) - Window.cx) / 2; //SM_CXSCREEN ȭ���ػ� ũ�⸦ �޾ƿ´� 
            Window.y = (GetSystemMetrics(SM_CYSCREEN) - Window.cy) / 2;
        }

        hWindow = CreateWindowEx  //WndProc ������ ���� ������ ���⼭ ����!
        (//CreateWindowEx ��ť �޼���(�޼����� ť�� ��ť �޼����� ������)
            //create�� ť�� ��ġ�� �ʰ� �Ѿ
            Window.dwExStyle,
            Window.lpszClass,
            Window.lpszName,
            Window.style,
            Window.x,
            Window.y,
            Window.cx,
            Window.cy,
            Window.hwndParent,
            Window.hMenu,
            Window.hInstance,
            Window.lpCreateParams
        ); //������ �����ݷ��� �ٽ� ���̸� �⺻���� ��������..

        ShowWindow(hWindow, SW_RESTORE); //showcmd -> SW_ ...
    }   //SW_RESTORE â �ɼ� ���� ���ϰ� ����

    {
        MSG Message = MSG();


        while (true)
        {
          
            //bkcolor = SetBkColor(hDC, bkcolor);//������ ���� �Ǿ��ִ� ���� �����ް� �� ������ �ٲ� (�������� ����ϱ�����)
            if (PeekMessage(&Message, HWND(), WM_NULL, WM_NULL, PM_REMOVE))
            {
                if (Message.message == WM_QUIT)
                    return static_cast<int>(Message.wParam);   //WM_QUIT �� wParam 0 ����

                DispatchMessage(&Message);
            }
            else
            {
                //�޼��� ���� �Լ� �޼���ť�� �޼��� �߰�
                //PostMessage(hWindow,WM_APP,0,0);  
                //WM_APP ���� ����� ���� Ư�� �޼���
                SendMessage(hWindow, WM_APP, 0, 0);  //��ť �޼����� ������
                
            }

        }

    }

}