/*
        ImGui Tutorial By Prodigy 

        Here we talk about
        [---------
        -Icons
        -Fonts
        -Tabs
        -ComboBoxes
        -Listboxes
        -Treenodes
        -Styles
        -Coloring
        -Columns
        -Seperators
        -----------]
        # Disclaimer:

        If you want the custom fonts & icons, you must make sure you have the
        -imgui_font_awesome_4.h
        -font_awesome.cpp

        Otherwise, the fonts and icons will not work! |
        
        -If you're still having trouble with this, goto imgui_demo.cpp, thats where i learned pretty much everything i talk about :)
        Or visit https://learncpp.com if you're new to c++

*/
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include <iostream>
#include <examples/example_win32_directx9/imgui_font_awesome_4.h>
#include <examples/example_win32_directx9/font_awesome.cpp>
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace std;


// Here we do the main coding etc.
int main(int, char**)
{
    system("title ImGui:Window:Launcher - t0xic");
    std::cout << " Initializing ImGui . . . " << std::endl;
    std::cout << " Completed!" << std::endl;
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Launcher"), NULL };
    ::RegisterClassEx(&wc);

    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("ImGui-Tutorial | by Prodigy | https://discord.gg/2Pd77m2SYJ | https://github.com/ProdigyG"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        std::cout << " Failed Creating D3D Device . . . " << std::endl;
        system("pause");
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.WantCaptureMouse = true;
    io.WantCaptureKeyboard = true;
    io.WantSetMousePos = true;
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange; ImFontConfig config;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);
    //Here we load our custom font
    io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
   

    // Our state
    bool showmenu = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    std::cout << " ==================================== " << std::endl;
    std::cout << "" << std::endl;
    std::cout << " ==================================== " << std::endl;
    std::cout << " Tutorial  : By Prodigy " << std::endl;
    std::cout << " Github    : https://github.com/ProdigG" << std::endl;
    std::cout << " Youtube   : https://www.youtube.com/channel/UCHuSm6aliiJBIEKBidepZXw?view_as=subscriber " << std::endl;
    std::cout << " Discord   : https://discord.gg/2Pd77m2SYJ" << std::endl;

    //Here is where we add our icons etc.
    // Note: The OversampleH & V Stuff makes your icons more clear etc.
    // This is the stuff you need to copy for the icon stuff :)
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleV = 2.5f;
    icons_config.OversampleH = 2.5f;
    io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 18.0f, &icons_config, icons_ranges);
    //End of copy all icon stuff

    //STYLES // COLRING THE MENU, you can copy this style if you'd like :D
    ImGuiStyle& style = ImGui::GetStyle();


    style.Alpha = 1.0f;
    style.WindowPadding = ImVec2(8, 8);
    style.WindowMinSize = ImVec2(32, 32);
    style.WindowRounding = 0.f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    
    style.FramePadding = ImVec2(6.5, 6.5);
    style.FrameRounding = 0.0f;
    style.ItemSpacing = ImVec2(4, 9);
    style.ItemInnerSpacing = ImVec2(8, 8);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 3.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabMinSize = 5.0f;
    style.GrabRounding = 0.0f;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.DisplayWindowPadding = ImVec2(22, 22);
    style.DisplaySafeAreaPadding = ImVec2(4, 4);
    style.AntiAliasedLines = true;

    style.CurveTessellationTol = 1.50f;

    style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
    style.Colors[ImGuiCol_WindowBg] = ImColor(15, 14, 15, 255);
    style.Colors[ImGuiCol_ChildBg] = ImColor(25, 25, 25, 255);
    style.Colors[ImGuiCol_Border] = ImColor(64, 64, 64, 0);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
    style.Colors[ImGuiCol_TitleBg] = ImColor(20, 20, 20, 255);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImColor(20, 20, 20, 255);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(205, 92, 92, 175);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);

    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(30 / 255.f, 30 / 255.f, 30 / 255.f, 255 / 255.f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(30 / 255.f, 30 / 255.f, 30 / 255.f, 255 / 255.f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(25 / 255.f, 25 / 255.f, 25 / 255.f, 255 / 255.f);

    style.Colors[ImGuiCol_Tab] = ImVec4(24 / 255.f, 26 / 255.f, 29 / 255.f, 255 / 255.f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 0.97f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(30.0f, 144.0f, 255.0f, 1.00f);

    // We will keep all of our variables here :)
    static float float_slider;
    static int int_slider;
    static int tab = NULL;

    // Our ComboBox Stuff 
    int COMBO_SELECTED_ITEM = NULL; //This is the selected item
    //These are the items in our array / all of the items etc.
    const char* ComboItems[]{ "item1","item2","item3","item4","item5","item6","item7","item8","item9","item10","item11","item12","item13","item14","item15" };

    //Same stuff as the comboBox. 
    int LISTBOX_SELECTED_ITEM = NULL;
    const char* ListBoxItems[]{ "item1","item2","item3","item4","item5","item6","item7","item8","item9","item10","item11","item12","item13","item14","item15" };

    //Checkmarks
    bool IsChecked = false; //set this to be true or false if you want your checkmark to be automatically check yes or no when you load your imgui stuff

    if (IsChecked)
    {
        //this means, if the checkbox is checked then do your code etc etc.... lol
    }

    if (!IsChecked)
    {
        //this means, if it is not checked then do your code etc etc. Or you can put a else where the if(IsChecked) code is lol...
    }

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        if (showmenu)
        {
            //ICON_FA_TICKET = is the icon, you can add a icon by doing ICON_FA_icon name etc etc.
            ImGui::Begin(ICON_FA_TICKET " Your ImGui Menu Name | by Prodigy", &showmenu , ImGuiWindowFlags_NoResize);                          
            ImGui::SetWindowSize(ImVec2(900, 500)); //this sets the imgui window size
            ImGui::Separator(); // A seperator is basically a line lol

            //The ImVec2 refers to the position / size of an item / thing. But in this case it is size because the ImGui::Button can take a ImVec2 as a paramater. It isn't required tho.
            if (ImGui::Button(ICON_FA_BOOK " Tab 1", ImVec2(305, 35))) 
            {
                tab = 1;
            }
            ImGui::SameLine(); //Makes the items on the sameline :)
            if (ImGui::Button(ICON_FA_ROCKET " Tab 2", ImVec2(305,35)))
            {
                tab = 2;
            }
            ImGui::SameLine(); 
            if (ImGui::Button(ICON_FA_BUG " Tab 3", ImVec2(305, 35)))
            {
                tab = 3;
            }
            ImGui::Separator();
            switch (tab)
            {
            case 0:
                //255, 0, 0 = the color (rgb) format | the last number at the end '255' that just means how visible the text is. 255 = most visible, 0 = invisible
                ImGui::TextColored(ImVec4(255, 255, 0, 255), "You need to select a tab on the navbar :)");
                ImGui::Text("ImGui - Tutorial | by Prodigy :)");
                break;

            case 1:
                ImGui::TextColored(ImVec4(255, 255, 0, 255), "This is tab 1 :) Where you learn about ComboBoxes and ListBoxes");
                ImGui::TextColored(ImVec4(255, 0, 0, 255), "Some colored text :)");
                ImGui::ListBox("ListBox", &LISTBOX_SELECTED_ITEM, ListBoxItems, IM_ARRAYSIZE(ListBoxItems));
                ImGui::Combo("ComboBox", &COMBO_SELECTED_ITEM, ComboItems, IM_ARRAYSIZE(ComboItems));
                ImGui::Button("im a button! ");
                if (ImGui::Button("Press me! :)"))
                {
                    MessageBoxA(NULL, "Hello! From the messagebox! :D", "ImGui Tutorial | by Prodigy", MB_OK | MB_ICONINFORMATION);
                }
                
                
                ImGui::Text("ImGui - Tutorial | by Prodigy :)");
                break;

            case 2:
                ImGui::TextColored(ImVec4(255, 255, 0, 255), "This is tab 2 :) Where you learn about treenodes, buttons, checkmarks etc.");
                if (ImGui::TreeNode("name")) //we do if ImGui::TreeNode, because it basically means. "if you open the treenode then: all your stuff inside it etc."
                {
                    ImGui::Button("test button");
                    ImGui::TextColored(ImVec4(255, 255, 0, 255), "hello from inside the treenode! :D");
                    ImGui::TreePop(); //this is required.
                }
                if (ImGui::TreeNode("another treenode!")) //we do if ImGui::TreeNode, because it basically means. "if you open the treenode then: all your stuff inside it etc."
                {
                    ImGui::Button("hello! ");
                    ImGui::TextColored(ImVec4(255, 255, 0, 255), "you can add a treenode in a treenode! :D");
                    if (ImGui::TreeNode("a treenode in a treenode!")) //we do if ImGui::TreeNode, because it basically means. "if you open the treenode then: all your stuff inside it etc."
                    {
                        
                        ImGui::TextColored(ImVec4(255, 255, 0, 255), "hello from inside the treenode in a treenode! :D");
                        ImGui::TreePop(); //this is required.
                    }
                    ImGui::TreePop(); //this is required.
                }
                ImGui::Checkbox("Enabled", &IsChecked);
                ImGui::Text("ImGui - Tutorial | by Prodigy :)");
                break;

            case 3:
                ImGui::TextColored(ImVec4(255, 255, 0, 255), "This is about child windows etc & columns! :D");
                ImGui::Columns(2); //you can change 2 to the amount of columns you want...
                ImGui::Text("column 1! :D");
                ImGui::BeginChild("#child_name", ImVec2(500, 300), false); //begins the child window. False = not show border, set it to true if you want a border.
                if (ImGui::TreeNode("testitem"))
                {
                    ImGui::Text("hello from inside the treenode!");
                    ImGui::TreePop();
                }
                if (ImGui::Button("Click me :D"))
                {
                    int result = MessageBoxA(NULL, "Hello! :D Do you think this is cool hey?", "Question - From Prodigy", MB_YESNOCANCEL | MB_ICONINFORMATION);
                    switch (result) {
                    case IDYES:
                        MessageBoxA(NULL, "Yay!! I like you too my friend :DDD", "ImGui - Tutorial | by Prodigy", MB_OK);
                        if (!showmenu) {
                            showmenu = showmenu;
                        }
                        break;

                    case IDNO:
                        MessageBoxA(NULL, "Okay :((", "ImGui - Tutorial | by Prodigy", MB_OK);
                        if (!showmenu)
                        {
                            showmenu = showmenu;
                        }
                        break;

                    case IDCANCEL:
                        MessageBoxA(NULL, "Okay :((", "ImGui - Tutorial | by Prodigy", MB_OK);
                        if (!showmenu) {
                            showmenu = showmenu;
                        }
                        break;
                    }

                }
                ImGui::EndChild(); //this is required if you're making a child

                ImGui::NextColumn(); //this is basically saying, "next column over"
                ImGui::Text("column 2! :D");
                ImGui::Bullet();
                ImGui::SameLine();
                ImGui::Text("hey! Im next to a bullet :D :))");

                ImGui::NewLine(); //this is spacing / adding a new line like std::endl; sorta lel
                ImGui::Text("ImGui - Tutorial | by Prodigy :)");

                ImGui::SliderFloat("float slider", &float_slider, 0.f, 100.f); //the 0 is the starting value / min value, 100 = max value. You can change both of these values to what ever you want :D
                ImGui::SliderInt("int slider", &int_slider, 0.f, 100.f);

                break;
            }

            ImGui::End();
        }


        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*255.0f), (int)(clear_color.y*255.0f), (int)(clear_color.z*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}


bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           

    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
