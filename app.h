#ifndef _app_h
#define _app_h

class app{
  public:
    bool enableInput = true;
    bool exitApp;
    int animeIndex;
    int renderTime;
    int inputTime; 
    virtual void inputApp()=0;
    virtual void render()=0; 
};

#endif
