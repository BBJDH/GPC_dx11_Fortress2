//#include<Windows.h>

#include <cassert>
#include <d3d11.h>

#include "Pipeline.h"
#pragma comment(lib, "msimg32.lib")

#if not defined _DEBUG
#define MUST(Expression) (      (         (Expression)))
#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif

namespace Engine::Rendering::Pipeline
{
    namespace
    {
        ID3D11Device        * Device;
        ID3D11DeviceContext * DeviceContext;

        IDXGISwapChain * SwapChain;

        //Buffer
        namespace Buffer
        {
            ID3D11Buffer * Vertex;
            ID3D11Buffer * Constant[3];
        }

        ID3D11RenderTargetView * RenderTargetView;
    }
    namespace HmemDC
    {
        HDC hmemdc;

        void Create_hmemdc(HWND const hWindow)
        {
            HDC hdc = GetDC(hWindow);
            hmemdc = CreateCompatibleDC(hdc);
            ReleaseDC(hWindow, hdc);
        }

        HDC getdc()
        {
            return hmemdc;
        }

        void Transparents_Color(HDC hdc_mem, HBITMAP hbitmap, COLORREF const transparents_color, SIZE const& size, POINT const& start)
        {
            IDXGISurface1 * Surface = nullptr;

            MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&Surface)));
            {
                HDC hDC = HDC();

                MUST(Surface->GetDC(false, &hDC));

                SelectObject(hdc_mem,hbitmap);

                TransparentBlt(hDC, start.x, start.y,size.cx,size.cy,
                                hdc_mem,0,0,size.cx,size.cy,transparents_color);

                MUST(Surface->ReleaseDC(nullptr));
            }
            Surface->Release();

            DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);

        }
    }

    namespace String
    {
        void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const & size, POINT const & center)
        {
            IDXGISurface1 * Surface = nullptr;

            MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&Surface)));
            {
                HDC hDC = HDC();

                MUST(Surface->GetDC(false, &hDC));
                {
                    SelectObject(hDC, hFont);

                    SetTextColor(hDC, color);

                    RECT Area = RECT();

                    Area.left   = center.x - size.cx / 2;
                    Area.top    = center.y - size.cy / 2;
                    Area.right  = center.x + size.cx / 2;
                    Area.bottom = center.y + size.cy / 2;

                    UINT const Format = DT_WORDBREAK | DT_NOPREFIX | DT_EDITCONTROL | DT_NOFULLWIDTHCHARBREAK;

                    /*
                    DT_WORDBREAK            : 단어 단위로 개행
                    DT_NOPREFIX             : 
                    DT_EDITCONTROL          :
                    DT_NOFULLWIDTHCHARBREAK : 
                    */

                    DrawText(hDC, string, ~'\0', &Area, Format);
                    
                }
                MUST(Surface->ReleaseDC(nullptr));
            }
            Surface->Release();

            DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
        }
    }

    namespace Texture
    {
        struct Handle final
        {
            ID3D11Texture2D          * const Texture2D;
            ID3D11ShaderResourceView * const ShaderResourceView;
        };

        void Create(Handle *& handle, SIZE const & size, BYTE const * const data)
        {
            D3D11_TEXTURE2D_DESC const Descriptor
            {
                static_cast<UINT>(size.cx),
                static_cast<UINT>(size.cy),
                1,
                1,
                DXGI_FORMAT_B8G8R8A8_UNORM,
                1,
                0,
                D3D11_USAGE_IMMUTABLE,
                D3D11_BIND_SHADER_RESOURCE
            };

            UINT const BPP = 32;

            D3D11_SUBRESOURCE_DATA const Subresource
            {
                data,
                size.cx * (BPP / 8)
            };

            ID3D11Texture2D * Texture2D = nullptr;
            
            MUST(Device->CreateTexture2D(&Descriptor, &Subresource, &Texture2D));

            ID3D11ShaderResourceView * ShaderResourceView = nullptr;

            MUST(Device->CreateShaderResourceView(Texture2D, nullptr, &ShaderResourceView));

            handle = new Handle
            {
                Texture2D,
                ShaderResourceView
            };
        }

        void Render(Handle const * const & handle, RECT const & area)
        {
            DeviceContext->PSSetShaderResources(0, 1, &handle->ShaderResourceView);
            {
                D3D11_MAPPED_SUBRESOURCE Subresource = D3D11_MAPPED_SUBRESOURCE();

                MUST(DeviceContext->Map(Buffer::Vertex, 0, D3D11_MAP_WRITE_DISCARD, 0, &Subresource));
                {
                    float const Coordinates[4][2]
                    {
                        { static_cast<float>(area.left),  static_cast<float>(area.top)    },
                        { static_cast<float>(area.right), static_cast<float>(area.top)    },
                        { static_cast<float>(area.left),  static_cast<float>(area.bottom) },
                        { static_cast<float>(area.right), static_cast<float>(area.bottom) }
                    };

                    memcpy_s(Subresource.pData, Subresource.RowPitch, Coordinates, sizeof(Coordinates));
                }
                DeviceContext->Unmap(Buffer::Vertex, 0);
            }
            DeviceContext->Draw(4, 0);
        }

        void Delete(Handle * const & handle)
        {
            handle->ShaderResourceView->Release();
            handle->Texture2D->Release();

            delete handle;
        }
    }

    namespace Transform
    {
        //template<typename Data>
        //void Update(ID3D11Buffer* const buffer, Data const& data)

        template<Type type>
        void Update(Matrix const & matrix)
        {
            UINT const index = static_cast<UINT>(type);

            D3D11_MAPPED_SUBRESOURCE Subresource = D3D11_MAPPED_SUBRESOURCE();

            MUST(DeviceContext->Map(Buffer::Constant[index], 0, D3D11_MAP_WRITE_DISCARD, 0, &Subresource));
            {
                memcpy_s(Subresource.pData, Subresource.RowPitch, matrix, sizeof(matrix));
            }
            DeviceContext->Unmap(Buffer::Constant[index], 0);
        }

        template void Update<Type::World>      (Matrix const &);
        template void Update<Type::View>       (Matrix const &);
        template void Update<Type::Projection> (Matrix const &);
    }

    void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
    {
        switch(uMessage)
        {
            case WM_CREATE:
            {
                Engine::Rendering::Pipeline::HmemDC::Create_hmemdc(hWindow);
                //hmamdc 생성

#pragma region Swap Chain 생성
                {
                    DXGI_SWAP_CHAIN_DESC Descriptor = DXGI_SWAP_CHAIN_DESC();

                    Descriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                    //하나의 채널당 얼만큼의 메모리를 할당할지
                    //형식 : DXGI_MODE_DESC(너비높이,주사율,데이터 포멧형식 등) 
                    //각 채널별 8비트 할당(0~255),UNORM 크기 1로 정규화
                    //BPP : Bits Per Pixel(32), BPC : Bits Per Channel(8)
                    //Signed NORM : -1 ~ +1 , Unsigned NORM : 0 ~ 1
                    Descriptor.SampleDesc.Count = 1;//최대 32 개까지 가능
                    Descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                    Descriptor.BufferCount = 1;
                    Descriptor.OutputWindow = hWindow;
                    Descriptor.Windowed = true;
                    Descriptor.Flags = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;
                    //어댑터와 스왑체인은 같은 팩토리에서 생성되어야 한다
                    MUST(D3D11CreateDeviceAndSwapChain
                    (
                        nullptr,                            //내부적으로 팩토리와 어댑터를 만든다
                        D3D_DRIVER_TYPE_HARDWARE,           //어댑터 널, 하드웨어 타입으로 지정하면 주 사용 어댑터를 가져온다
                        nullptr,
                        D3D11_CREATE_DEVICE_SINGLETHREADED, //약간의 퍼포먼스 상승
                        nullptr,
                        0,
                        D3D11_SDK_VERSION,
                        &Descriptor,
                        &SwapChain,
                        &Device,
                        nullptr,
                        &DeviceContext
                    ));
                }
#pragma endregion

                {
                    #include "../Shader/Bytecode/Vertex.h"
#pragma region Input Layout 생성
                    {
                        D3D11_INPUT_ELEMENT_DESC const Descriptor[2]
                        {
                            { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0 },
                            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1 }
                        };

                        ID3D11InputLayout* InputLayout = nullptr;

                        MUST(Device->CreateInputLayout
                        (
                            Descriptor,
                            2, //sizeof(Descriptor)/sizeof(*Descriptor) //_ARRAYSIZE(Descriptor) -> winapi에서 지원하는 매크로
                            Bytecode,
                            sizeof(Bytecode),
                            &InputLayout
                        ));

                        DeviceContext->IASetInputLayout(InputLayout);

                        InputLayout->Release();
                    }
#pragma endregion

#pragma region Vertex Shader 생성
                    {
                        ID3D11VertexShader* VertexShader = nullptr;

                        MUST(Device->CreateVertexShader
                        (
                            Bytecode,
                            sizeof(Bytecode),
                            nullptr,
                            &VertexShader
                        ));

                        DeviceContext->VSSetShader(VertexShader, nullptr, 0);

                        VertexShader->Release();
                    }
#pragma endregion

                }
                {
                    #include "../Shader/Bytecode/Pixel.h"
#pragma region Pixel Shader 생성
                    {
                        ID3D11PixelShader* PixelShader = nullptr;

                        MUST(Device->CreatePixelShader
                        (
                            Bytecode,
                            sizeof(Bytecode),
                            nullptr,
                            &PixelShader
                        ));

                        DeviceContext->PSSetShader(PixelShader, nullptr, 0);

                        PixelShader->Release();
                    }
#pragma endregion

                }
#pragma region IA Topology 세팅
                {
                    DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
                }
#pragma endregion

#pragma region Vertex Buffer 생성
                {
                    float const Coordinates[4][2]
                    {
                        { -0.5f, +0.5f }, { +0.5f, +0.5f },
                        { -0.5f, -0.5f }, { +0.5f, -0.5f }
                    };

                    D3D11_BUFFER_DESC const Descriptor
                    {
                        sizeof(Coordinates),
                        D3D11_USAGE_IMMUTABLE,
                        D3D11_BIND_VERTEX_BUFFER,
                        0
                    };

                    D3D11_SUBRESOURCE_DATA const Subresource
                    {
                        Coordinates
                    };

                    ID3D11Buffer* Buffer = nullptr;

                    MUST(Device->CreateBuffer(&Descriptor, &Subresource, &Buffer));

                    UINT const Stride = sizeof(*Coordinates);
                    UINT const Offset = 0;

                    DeviceContext->IASetVertexBuffers(0, 1, &Buffer, &Stride, &Offset);

                    Buffer->Release();
                }
#pragma endregion

#pragma region Pixel buffer 생성
                {
                    D3D11_BUFFER_DESC const Descriptor
                    {
                        sizeof(float[4][2]),
                        D3D11_USAGE_DYNAMIC,
                        D3D11_BIND_VERTEX_BUFFER,
                        D3D11_CPU_ACCESS_WRITE
                    };

                    MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Vertex));

                    UINT const Stride = sizeof(float[2]);
                    UINT const Offset = 0;

                    DeviceContext->IASetVertexBuffers(1, 1, &Buffer::Vertex, &Stride, &Offset);
                }
#pragma endregion

#pragma region Constant Buffer 생성(world, view, proj 행렬)
                {
                    D3D11_BUFFER_DESC const Descriptor
                    {
                        sizeof(float[4][4]),
                        D3D11_USAGE_DYNAMIC,
                        D3D11_BIND_CONSTANT_BUFFER,
                        D3D11_CPU_ACCESS_WRITE
                    };

                    for (UINT u = 0; u < 3; ++u)
                        MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Constant[u]));

                    DeviceContext->VSSetConstantBuffers(0, 3, Buffer::Constant);
                }
#pragma endregion

#pragma region Blend State 생성및 결합
                {
                    D3D11_BLEND_DESC Descriptor = D3D11_BLEND_DESC();

                    Descriptor.RenderTarget->BlendEnable = true;
                    Descriptor.RenderTarget->SrcBlend = D3D11_BLEND_SRC_ALPHA;
                    Descriptor.RenderTarget->DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
                    Descriptor.RenderTarget->BlendOp = D3D11_BLEND_OP_ADD;
                    Descriptor.RenderTarget->SrcBlendAlpha = D3D11_BLEND_ZERO;
                    Descriptor.RenderTarget->DestBlendAlpha = D3D11_BLEND_ONE;
                    Descriptor.RenderTarget->BlendOpAlpha = D3D11_BLEND_OP_ADD;
                    Descriptor.RenderTarget->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


                    ID3D11BlendState* BlendState = nullptr;

                    MUST(Device->CreateBlendState(&Descriptor, &BlendState));

                    DeviceContext->OMSetBlendState(BlendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK);

                    BlendState->Release();
                }
#pragma endregion


                return;
            }
            case WM_APP:
            {
                MUST(SwapChain->Present(0, 0));

                float const Color[4] { 0.0f, 0.0f, 0.0f, 1.0f };

                DeviceContext->ClearRenderTargetView(RenderTargetView, Color);

                return;
            }
            case WM_DESTROY:
            {
                DeviceContext->ClearState();

                RenderTargetView->Release();

                for(UINT u = 0; u < 3; ++u)
                    Buffer::Constant[u]->Release();

                Buffer::Vertex->Release();

                SwapChain->Release();

                DeviceContext->Release();
                Device->Release();

                return;
            }
            case WM_SIZE:
            {
                {
                    D3D11_VIEWPORT const Viewport
                    {
                        0.0f,
                        0.0f,
                        static_cast<float>(LOWORD(lParameter)),
                        static_cast<float>(HIWORD(lParameter))
                    };

                    DeviceContext->RSSetViewports(1, &Viewport);
                }
                {
                    if(RenderTargetView != nullptr)
                    {
                        RenderTargetView->Release();

                        MUST(SwapChain->ResizeBuffers
                        (
                            1,
                            LOWORD(lParameter),
                            HIWORD(lParameter),
                            DXGI_FORMAT_B8G8R8A8_UNORM,
                            DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE
                        ));
                    }
                    {
                        ID3D11Texture2D * Texture2D = nullptr;

                        MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&Texture2D)));
                        {
                            IDXGISurface1 * Surface = nullptr;

                            MUST(Texture2D->QueryInterface(IID_PPV_ARGS(&Surface)));
                            {
                                HDC hDC = HDC();

                                MUST(Surface->GetDC(false, &hDC));
                                {
                                    SetBkMode(hDC, TRANSPARENT);
                                }
                                MUST(Surface->ReleaseDC(nullptr));
                            }
                            Surface->Release();
                        }
                        {
                            MUST(Device->CreateRenderTargetView(Texture2D, nullptr, &RenderTargetView));

                            Texture2D->Release();
                        }
                        
                        

                        DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
                    }
                }

                return;
            }
        }
    }
}

