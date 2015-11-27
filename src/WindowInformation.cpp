#include "WindowInformation.hpp"

WindowInformation::WindowInformation(MyPixel originalStartingPixel,Size originalSize){
    WindowInformation::originalStartingPixel=originalStartingPixel;
    WindowInformation::originalSize=originalSize;
}

MyPixel WindowInformation::GetOriginalStartingPixel()
{
    return WindowInformation::originalStartingPixel;
}

Size WindowInformation::GetOriginalSize()
{
    return WindowInformation::originalSize;
}
float WindowInformation::GetScore()
{
    return score;
}
void WindowInformation::SetScore(float score)
{
    WindowInformation::score=score;
}
