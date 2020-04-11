#include "hstreamcontroller.h"

HStreamController::HStreamController()
{

}

void HStreamController::createScreenSendStream()
{
    mScreenSendStream = HStreamFactory::createScreenSendStream();    
    mScreenSendStream->setUsageType(1);
    mScreenSendStream->setResolution(1280,720);
    mScreenSendStream->setBitrate(2000000);
    mScreenSendStream->setStreamDataFunction(std::bind(&HStreamController::encodedScreenDataReceived,this,std::placeholders::_1,std::placeholders::_2));
    mScreenSendStream->initialize(HCodec::CODEC_VIDEO_H264);
    mScreenSendStream->play();
}

void HStreamController::createVideoReceiveStream()
{
    mVideoReceiveStream = HStreamFactory::createVideoReceiveStream();
    mVideoReceiveStream->setOutput(HOutput::OUTPUT_TO_WINDOW);
    mVideoReceiveStream->setWindowID(mWId);
    mVideoReceiveStream->initialize(HCodec::CODEC_VIDEO_H264);
    mVideoReceiveStream->play();
}

void HStreamController::onEncodedScreenDataCome(char *data, int size)
{
    if(mVideoReceiveStream != nullptr){
        mVideoReceiveStream->feedStream(data,size);
    }
}

void HStreamController::encodedScreenDataReceived(char *data, int size)
{
    emit encodedScreenDataReady(data,size);
}

void HStreamController::setWindowID(WId pWID)
{
    this->mWId = pWID;
}

