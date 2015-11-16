#include "WindowsIterator.hpp"
WindowsIterator::WindowsIterator(Mat * originalImage)
{
    WindowsIterator::image=originalImage->clone();
    WindowsIterator::resizingRatio=1.2;
    WindowsIterator::step=1;
    WindowsIterator::windowSize.height=36;
    WindowsIterator::windowSize.width=36;
    WindowsIterator::currentStartingPixel.col=0;
    WindowsIterator::currentStartingPixel.row=0;
    WindowsIterator::windowOriginalSize.height=36;
    WindowsIterator::windowOriginalSize.width=36;
    WindowsIterator::imageInitialSize=image.size();
}

void WindowsIterator::SetResizingRatio(double resizingRatio)
{
    WindowsIterator::resizingRatio=resizingRatio;
}
void WindowsIterator::SetStep(int step)
{
    WindowsIterator::step=step;
}
void WindowsIterator::SetWindowSize(cv::Size windowSize)
{
    WindowsIterator::windowSize=windowSize;
    WindowsIterator::windowOriginalSize=windowSize;
}
Window * WindowsIterator::GetNextWindow()
{
    if (currentStartingPixel.col==-1)
    {
        return NULL;
    }
    cv::Mat  currentWindowImage=GetWindowFromImage();
    MyPixel windowOriginalPixel;
    windowOriginalPixel.col=int(floor(currentStartingPixel.col*imageInitialSize.width/image.size().width));
    windowOriginalPixel.row=int(floor(currentStartingPixel.row*imageInitialSize.height/image.size().height));
    WindowInformation * currentWindowInformation=new WindowInformation(windowOriginalPixel,windowOriginalSize);
    Window * currentWindow=new Window(currentWindowInformation,currentWindowImage);
    IncrementPixel();
    return currentWindow;
}

void WindowsIterator::Reshape()
{
    // reshape the image
    cv::Size oldSize=image.size();
    double newWidth=oldSize.width/resizingRatio;
    double newHeight=oldSize.height/resizingRatio;
    cv::Size newSize(int(ceil(newWidth)),int(ceil(newHeight)));
    cv::resize(image,image,newSize);
    // update the windowOriginalSize
    windowOriginalSize.width=int(max(ceil((windowSize.width*imageInitialSize.width)/newSize.width),ceil((windowSize.height*imageInitialSize.height)/newSize.height)));
    windowOriginalSize.height=windowOriginalSize.width;
}

cv::Mat WindowsIterator::GetWindowFromImage()
{
    return image(cv::Rect(currentStartingPixel.col,currentStartingPixel.row,windowSize.width,windowSize.height));

}

void WindowsIterator::IncrementPixel()
{
    if (IsColIncrementable()){
        currentStartingPixel.col+=step;
    }
    else if (IsRowIncrementable()){
        currentStartingPixel.col=0;
        currentStartingPixel.row+=step;
    }
    else if (IsImageReshabable())
    {
        Reshape();
        currentStartingPixel.col=0;
        currentStartingPixel.row=0;
    }
    else
    {
        currentStartingPixel.col=-1;
        currentStartingPixel.row=-1;
    }

}

bool WindowsIterator::IsRowIncrementable()
{
    return (currentStartingPixel.row+windowSize.height+step<=image.size().height);
}

bool WindowsIterator::IsColIncrementable()
{
    return (currentStartingPixel.col+windowSize.width+step<=image.size().width);
}
bool WindowsIterator::IsImageReshabable()
{
    double nextHeight=image.size().height/resizingRatio;
    double nextWidth=image.size().width/resizingRatio;
    return ((nextHeight>=windowSize.height) && (nextWidth>=windowSize.width));
}
