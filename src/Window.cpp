#include "Window.hpp"
Window::Window(WindowInformation * windowInformation,Mat & windowImage)
{
    Window::windowInformation=windowInformation;
    Window::windowImage=windowImage;
}

WindowInformation * Window::GetWindowInformation()
{
    return Window::windowInformation;
}

Mat & Window::GetWindowImage()
{
    return Window::windowImage;
}
