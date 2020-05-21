#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<string>
#include<Windows.h>
#include<gdiplus.h>
#include<opencv2/opencv.hpp>
#include<SDL_ttf.h>


# define T 30
#define widh 640
#define hight 480
using namespace cv;

void clean(SDL_Renderer* rend, SDL_Rect* rect) {
    SDL_SetRenderDrawColor(rend, 55,22, 33, 255);
    SDL_RenderFillRect(rend, rect);

}

static int record() {
    HWND winddeck = GetDesktopWindow();
    HDC hdct = GetDC(winddeck);
    HDC hcapt = CreateCompatibleDC(hdct);
    int h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    int w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    HBITMAP hbdeck = CreateCompatibleBitmap(hdct, w, h);
    SelectObject(hcapt, hbdeck);
    BitBlt(hcapt, 0, 0, w, h, hdct, 0, 0, SRCCOPY);
    /* if (!save("capture.bmp", hbdeck)) {
         std::cout << "error in file save" << std::endl;
         return 1;
     }*/
    ReleaseDC(winddeck, hdct);
    DeleteDC(hcapt);
    DeleteObject(hbdeck);
    return 0;
}

bool captvideo(const std::string path, unsigned int t, const std::string name) {
    VideoCapture cap(path.c_str());
    if (!cap.isOpened()) {
        std::cout << "video error054" << std::endl;
        return false;
    }

    Mat fps;
    
    unsigned int i = 0;
    while (i <= t) {
        cap >> fps;

        if (fps.empty()) {
            std::cout << "the frame doesn't exist 021 " << std::endl;
            record();
            return false;
            break;
        }
        
        i++;
    }
    bool see = imwrite(name, fps);
    if (!see)
        return false;
   // imshow("image", fps);
    std::cout << "wrong:";
    cap.release();
    return true;
}

bool chekbox(SDL_Event *event, SDL_Rect rect) {
    int x = 0, y = 0;
     SDL_PollEvent(event);
    SDL_GetMouseState(&x, &y);
    if (x < rect.x)
        return false;
    else if (x > rect.w + rect.x)
        return false;
    else if (y < rect.y)
        return false;
    else if (y > rect.y + rect.h)
        return false;

    return true;
}
void blitxt(SDL_Renderer* rend, SDL_Rect* pos, std::string path,TTF_Font *police) {
    SDL_Color clr = { 255,255,255 };
    SDL_Surface* sfc = NULL;
    SDL_Texture* txt = NULL;
   // SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    sfc = TTF_RenderText_Solid(police, path.c_str(), clr);
    if (sfc == NULL)
        std:: cout << "wrong";
    txt = SDL_CreateTextureFromSurface(rend, sfc);
    SDL_RenderCopy(rend, txt, NULL, pos);
    SDL_RenderPresent(rend);
    SDL_FreeSurface(sfc);
}
void blitxt1(SDL_Renderer* rend, SDL_Rect* pos, std::string path, TTF_Font* police) {
    SDL_Color clr = { 255,255,255 };
    SDL_Surface* sfc = NULL;
    SDL_Texture* txt = NULL;
    int w = 0, h = 0;
    // SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    sfc = TTF_RenderText_Solid(police, path.c_str(), clr);
    if (sfc == NULL)
        std::cout << "wrong";
    
    txt = SDL_CreateTextureFromSurface(rend, sfc);
    SDL_QueryTexture(txt, NULL, NULL, &w, &h);
    pos->w = w;
    pos->h = h;
    clean(rend, pos);
    SDL_RenderCopy(rend, txt, NULL, pos);
    SDL_RenderPresent(rend);
    SDL_FreeSurface(sfc);
}



int H_A(SDL_Renderer* rend,  SDL_Rect *pos, SDL_Event *event, TTF_Font *police) {
    SDL_Color clr = { 255,255,255 };
    SDL_Surface* sfc = NULL;
    SDL_Texture* txt = NULL;
    std::string ir;
    bool stop = false,b=true;
    bool again = false;
    int w = 0, h = 0,m=0;
    while (!stop) {
        SDL_PollEvent(event);
        if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && again) {
            stop = true;
        }
        else if (event->type == SDL_KEYDOWN && event->key.keysym.scancode != SDL_SCANCODE_BACKSPACE && (event->key.keysym.scancode != SDL_SCANCODE_RETURN)) {
            ir = ir + SDL_GetKeyName(event->key.keysym.sym);
            sfc = TTF_RenderText_Solid(police, ir.c_str(), clr);
            txt = SDL_CreateTextureFromSurface(rend, sfc);
            SDL_QueryTexture(txt, NULL, NULL, &w, &h);
            pos->w = w;
            pos->h = h;
            clean(rend, pos);
            SDL_RenderCopy(rend, txt, NULL, pos);
            SDL_RenderPresent(rend);
            std::cout << ir << std::endl;
            if (b == false) b = true;
            again = true;
        }
        else if (b == true && event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
            clean(rend, pos);
            m = ir.size() - 1;
            ir.resize(m);
            sfc = TTF_RenderText_Solid(police, ir.c_str(), clr);
            txt = SDL_CreateTextureFromSurface(rend, sfc);
            SDL_QueryTexture(txt, NULL, NULL, &w, &h);
            pos->w = w;
            pos->h = h;
            clean(rend, pos);
            SDL_RenderCopy(rend, txt, NULL, pos);
            SDL_RenderPresent(rend);
           
            b = false;
        }
    }
    SDL_FreeSurface(sfc);
    pos->w = 0;
    pos->h = 0;
    return atoi(ir.c_str());
}
std::string I_R(SDL_Renderer* rend,SDL_Rect *pos,SDL_Event *event,TTF_Font *police) {
    SDL_Color clr = { 255,255,255 };
    SDL_Surface* sfc = NULL;
    SDL_Texture* txt = NULL;
    //std::string path ="" ;
    bool stop = false , b=true;
    int w = 0, h = 0,m=0;
    bool again = false;
    std::string ir  ="";
    
        while (!stop) {
            //std::cout << "jh";
        SDL_PollEvent(event);
        if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && again){
            stop = true;
            
        }
        else if(event->type == SDL_KEYDOWN) {
            if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
                ir = ir + " ";
            }
            else if (event->key.keysym.scancode == SDL_SCANCODE_KP_PERIOD) {
                ir = ir + ".";
                sfc = TTF_RenderText_Solid(police, ir.c_str(), clr);
                txt = SDL_CreateTextureFromSurface(rend, sfc);
                SDL_QueryTexture(txt, NULL, NULL, &w, &h);
                pos->w = w;
                pos->h = h;
                clean(rend, pos);
                SDL_RenderCopy(rend, txt, NULL, pos);
                SDL_RenderPresent(rend);
                std::cout << ir << std::endl;
                again = true;
            }
            else if (b == true && event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                clean(rend, pos);
                m = ir.size() - 1;
                ir.resize(m);
                sfc = TTF_RenderText_Solid(police, ir.c_str(), clr);
                txt = SDL_CreateTextureFromSurface(rend, sfc);
                SDL_QueryTexture(txt, NULL, NULL, &w, &h);
                pos->w = w;
                pos->h = h;
                clean(rend, pos);
                SDL_RenderCopy(rend, txt, NULL, pos);
                SDL_RenderPresent(rend);
                std::cout << m << b << std::endl;
                b = false;
            }
            else if (event->key.keysym.scancode != SDL_SCANCODE_BACKSPACE && (event->key.keysym.scancode != SDL_SCANCODE_RETURN)) {
                if(b==false) b = true;
                ir = ir + SDL_GetKeyName(event->key.keysym.sym);
                // ir = ir + SDL_GetScancodeName(event->key.keysym.scancode);

                sfc = TTF_RenderText_Solid(police, ir.c_str(), clr);
                txt = SDL_CreateTextureFromSurface(rend, sfc);
                SDL_QueryTexture(txt, NULL, NULL, &w, &h);
                pos->w = w;
                pos->h = h;
                clean(rend, pos);
                SDL_RenderCopy(rend, txt, NULL, pos);
                SDL_RenderPresent(rend);
                std::cout << ir << std::endl;
            }
        }
    }
    SDL_FreeSurface(sfc);
    
    pos->w = 0;
    pos->h = 0;
     
    return ir;
}



class background {
private:
    SDL_Surface surf;
   // SDL_Texture ttx;
   
    SDL_Point ws = { widh,hight };
public: 
    SDL_Renderer *rend;
    background(SDL_Renderer *R);
    ~background();
    void draw();
    void button(SDL_Texture* img, SDL_Rect bt, SDL_Rect* btxt, std::string path, TTF_Font* font);
};

background::background(SDL_Renderer *R) {
    rend = R;
}

background::~background() {
    SDL_DestroyRenderer(rend);
    

}
void background::draw() {
    SDL_SetRenderDrawColor(rend, 55, 22, 33, 255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    int x = (ws.x) / 4;
    int y = (ws.y / 2) - 20;
    int x1 = ((ws.x) / 2) + ((ws.x) / 4);
    

    SDL_RenderDrawLine(rend, x,y,x1,y);
    
    SDL_RenderPresent(rend);
}

void background::button(SDL_Texture *img,SDL_Rect bt,SDL_Rect *btxt ,std::string path, TTF_Font *font) {
    if (img == NULL) {
        SDL_SetRenderDrawColor(rend, 55, 22, 33, 255);
        SDL_RenderClear(rend);
    }else{
        SDL_RenderCopy(rend,img,NULL,NULL);
    }
    SDL_SetRenderDrawColor(rend, 166,16,16,255);
    SDL_RenderFillRect(rend, &bt);
    blitxt(rend, btxt, path, font);

}


int main(int argc, char* argv[]) {

    /* if (!captvideo("ih.mp4", 1, "img.jpg")) {
         std::cout << "error" << std::endl;
         return 1;
     }*/

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* cwindow = nullptr;
    SDL_Renderer* srender = nullptr;
    SDL_Texture* image = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Event event;
    bool stop = false;
    SDL_Rect bt, butcad, txtpos;
    bt.x = (widh / 2) - 100;
    bt.y = (hight / 2) - 50;
    bt.w = 200;
    bt.h = 50;
    butcad.x = bt.x;
    butcad.y = bt.y;
    butcad.w = bt.x + bt.w;
    butcad.h = bt.y + bt.h;
    txtpos.x = bt.x + 50;
    txtpos.y = bt.y + 2;
    txtpos.w = 100;
    txtpos.h = 50;
    SDL_Rect write;
    write.x = widh / 4;
    write.y = (hight / 2) - 50;
    write.w = 500;//(widh / 2);
    write.h = 200;
    SDL_Rect clar, wait;
    wait.x = (widh / 4) + 130;
    wait.y = (hight / 2) - 50;
    clar.x = (widh / 4);
    clar.y = (hight / 2) - 100;
    clar.w = (widh / 2) + (widh / 4);
    clar.h = (hight / 2) - 10;
    SDL_Rect vi, mc, load;
    vi.x = (widh / 8);
    vi.y = (hight / 2) + 30;
    mc.x = (widh / 8) + widh / 2;
    mc.y = write.y;
    int x = widh / 4;
    int y = (hight / 2) - 40;
    int x1 = (widh / 2) + (widh / 4);
    load.x = wait.x + 45;
    load.y = wait.y + 10;
    load.w = 30;
    load.h = 10;


    cwindow = SDL_CreateWindow(
        "screenshot",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        widh,
        hight,
        SDL_WINDOW_RESIZABLE
    );

    if (cwindow == nullptr) {
        std::cout << "window error" << std::endl;
        return 1;
    }
    else {
        srender = SDL_CreateRenderer(cwindow, -1, SDL_RENDERER_PRESENTVSYNC);
        if (srender == nullptr) {
            std::cout << "render error" << std::endl;
            return 1;
        }
        else {
            if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                std::cout << "ing error" << std::endl << IMG_GetError();
                return 1;
            }
        }
    }
    TTF_Init();
    TTF_Font* police = NULL;
    police = TTF_OpenFont("Roboto-Regular.ttf", 20);
    TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 20);
    background bg(srender);


    // bg.button(NULL, bt);
    bool done = false, again = false;
    std::string namev, namei;
    int min = 0;
    int sec = 0;
    int time = 0;
    //bg.draw();
    //namev = I_R(srender, &write, &event, font);
   
   while (!stop) {
        SDL_PollEvent(&event);
        done = false;
        bg.button(NULL, bt, &txtpos, "START", police);
        if (event.type == SDL_QUIT)
        {
            stop = true;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {

            while (chekbox(&event,butcad) && !done) {
               
                bg.draw();
                blitxt1(srender, &vi, "(Exemple)Video Name.mp4 (.avi)", font);
                while ( !done  ) {
                    //bg.draw();
                    namev = I_R(srender, &write, &event, font);
                   // namev = namev + "mp4";
                    std::cout << namev;
                    //clean(srender, &clar);
                    bg.draw();
                    
                        blitxt1(srender, &vi, "(Exemple)Image Name.png (.jpg)", font);
                        SDL_FlushEvent(SDL_KEYDOWN);
                        namei = I_R(srender, &write, &event, font);
                        std::cout << namei;
                        //namei = namei + "png";
                        //clean(srender, &clar);
                        bg.draw();
                        blitxt1(srender, &mc, "Min", font);
                        min = H_A(srender, &write, &event, font);
                        
                        std::cout << min;
                        
                        bg.draw();//clean(srender, &clar);
                        blitxt1(srender, &mc, "Sec", font);
                        //bg.draw();
                        sec = H_A(srender, &write, &event, font);
                       // blitxt1(srender, &mc, "Sec", font);
                        time = T * ((60 * min) + sec);
                        bg.draw();
                            blitxt1(srender, &wait, "WAIT..", font);
                            SDL_SetRenderDrawColor(srender, 255, 255, 255, 255);
                            SDL_RenderDrawLine(srender, x, y, x1, y);
                        if (!captvideo(namev, time, namei)) {
                            
                            done = true;
                        }
                        else  {

                           
                            //SDL_Delay(8000);
                            while ((surface = IMG_Load(namei.c_str()))==NULL) {}
                            
                            image = SDL_CreateTextureFromSurface(srender, surface);
                            bg.button(image, bt, &txtpos, "Done !", police);
                            while (event.type != SDL_MOUSEBUTTONDOWN) {
                                SDL_PollEvent(&event);
                                std::cout << "xait";
                            }
                            chekbox(&event, butcad);
                            done = true;
                        }
                    }
                

            }
        }
    }
    

    // Close and destroy the window
    SDL_DestroyWindow(cwindow);


	std::cout << "helloworld";
	SDL_Quit();
	return 0;
}
