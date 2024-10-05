
/*
 *  Minigraph: Un mini-conjunto de funciones para abrir una ventana, pintar en
 *    ella y detectar la presion de algunas teclas y el ratón.
 *
*/

// VERSION: 1.2.0 (solo para windows)


//#if defined(_WIN32)

// Windows ////////////////////////////////////////////////////////////////////////////


#include <fstream>
#include <sstream>
#include <queue>
#include <math.h>
#include <process.h>
#include <windows.h>
#include <windowsx.h>

#define MINIGRAPH_SOURCE
#include "minigraph.h"





std::string szClassName = "VentanaP";

//------------------- Variables generales del entorno -------------------

HWND            hWnd;                               // ventana principal
HBITMAP         hBitmap;                            // bitmap para pintar off-screen
int             iWidth  = 400;                      // ancho de la ventana
int             iHeight = 300;                      // alto de la ventana
HDC             hDCMem = NULL;                      // Device Context en memoria
std::string     Tventana = "VentanaP";              // titulo de la ventana
std::queue<int> _teclas;                            // cola de teclas
bool            _raton_dentro;                      // el raton está dentro del 'client area'
int             _xraton, _yraton;                   // posicion del raton
bool            _bot_izq, _bot_der;                 // botones izquierdo y derecho
int             TPen = minigraph::EL_CONTINUA;      // estilo de trazo
int             GPen = 1;                           // grosor del trazo
int             RBrush = minigraph::ER_SOLIDO;      // tipo de Relleno;
int             FTamano = 20;                       // Tamaño letra
int             FInclinacion = 0;                   // inclinación texto
bool            FNegrita = false;                   // texto en negrita
bool            FCursiva = false;                   // texto en cursiva
bool            FSubrayada = false;                 // texto subrayado
bool            FTachada = false;                   // texto Tachado
std::string     FNombre = "Times New Roman";        // nombre de la fuente
UINT            FJustificado = (TA_LEFT|TA_BOTTOM); // justificado Horizontal
//--------------------------------------------------------------------------

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);


std::ostream& log() {
#if defined(DEBUG)
   static std::ofstream _log("log.txt");
#else
   static std::stringstream _log;
   _log.str(""); // lo borra
#endif
   return _log;
}

VOID Thread(PVOID pvoid) {
   Sleep(50); // FIXME
   _main_();
}

void maybe_call_main() {
   static bool started = false;
   if (!started) {
      _beginthread(Thread, 0, NULL); // Llama a 'main' (realmente  '_main_')
      started = true;
   }
}

void frame_real(int w, int h, int& rw, int &rh) {
   RECT frame = { 0, 0, w, h };
   AdjustWindowRect(&frame, WS_OVERLAPPEDWINDOW, FALSE);
   rw = frame.right - frame.left;
   rh = frame.bottom - frame.top;
}

void newMemDC(int w, int h) {
   if (hDCMem != NULL) {
      DeleteObject(hBitmap);
      DeleteDC(hDCMem);
   }
   log() << "New MemDC\n";
   HDC hDC = GetDC(hWnd);
   hDCMem  = CreateCompatibleDC(hDC);
   hBitmap = CreateCompatibleBitmap (hDC, w, h);
   SelectObject(hDCMem, hBitmap);
   SetBkMode(hDCMem, TRANSPARENT);
}

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nFunsterStil){
    static WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName.c_str();
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//

    if (!RegisterClassEx (&wincl))
       return 0;

    int w, h;
    frame_real(iWidth, iHeight, w, h);

    hWnd = CreateWindowEx (
      0,                   /* Extended possibilites for variation */
      szClassName.c_str(), /* Classname */
      Tventana.c_str(),    /* Title Text */
      WS_OVERLAPPEDWINDOW, /* default window */
      CW_USEDEFAULT,       /* Windows decides the position */
      CW_USEDEFAULT,       /* where the window ends up on the screen */
      w,                   /* The programs width */
      h,                   /* and height in pixels */
      HWND_DESKTOP,        /* The window is a child-window to desktop */
      NULL,                /* No menu */
      hThisInstance,       /* Program Instance handler */
      NULL                 /* No Window Creation data */
    );

    hBitmap = NULL;

    ShowWindow (hWnd, nFunsterStil);
    ShowWindow (GetConsoleWindow(), SW_HIDE);

    MSG messages;
    while (GetMessage (&messages, NULL, 0, 0)) {
       TranslateMessage(&messages);
       DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
   switch (message) {
   case WM_SIZE: {
      log() << "WM_SIZE\n";
      RECT R;
      GetClientRect(hWnd, &R);
      int w = R.right - R.left;
      int h = R.bottom - R.top;
      log() << w << ' ' << h << ' ' << '\n';
      if (w == 0 && h == 0) break; // Al minimizar envia WM_SIZE(0,0)

      if (hDCMem == NULL || w != iWidth || h != iHeight) {
         newMemDC(w, h);
         maybe_call_main();
      }
      break;
   }
   case WM_SIZING: {
      RECT* pRECT = (RECT*)lParam;
      log() << pRECT->top << ' ' << pRECT->left << ' '
            << pRECT->bottom << ' ' << pRECT->right << '\n';
      log() << iHeight << '\n';
      int w, h;
      frame_real(iWidth, iHeight, w, h);
      switch (wParam) {
      case WMSZ_BOTTOM:
         pRECT->bottom = pRECT->top + h;
         break;
      case WMSZ_TOP:
         pRECT->top = pRECT->bottom - h;
         break;
      case WMSZ_RIGHT:
         pRECT->right = pRECT->left + w;
         break;
      case WMSZ_LEFT:
         pRECT->left = pRECT->right - w;
         break;
      case WMSZ_TOPLEFT:
         pRECT->top = pRECT->bottom - h;
         pRECT->left = pRECT->right - w;
         break;
      case WMSZ_TOPRIGHT:
         pRECT->top = pRECT->bottom - h;
         pRECT->right = pRECT->left + w;
         break;
      case WMSZ_BOTTOMLEFT:
         pRECT->bottom = pRECT->top + h;
         pRECT->left = pRECT->right - w;
         break;
      case WMSZ_BOTTOMRIGHT:
         pRECT->bottom = pRECT->top + h;
         pRECT->right = pRECT->left + w;
         break;
      }

      return TRUE;
   }
   case WM_PAINT: {
      log() << "WM_PAINT\n";
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      SelectObject(hDCMem, hBitmap);
      if (hBitmap != NULL) {
         BitBlt(hdc, 0, 0, iWidth, iHeight, hDCMem, 0, 0, SRCCOPY);
      }
      EndPaint(hWnd, &ps);
      break;
   }
   case WM_MOUSEMOVE: {
      log() << "WM_MOUSEMOVE\n";
      _raton_dentro = true;
      _xraton = GET_X_LPARAM(lParam);
      _yraton = GET_Y_LPARAM(lParam);
      _bot_izq = wParam & MK_LBUTTON;
      _bot_der = wParam & MK_RBUTTON;
      break;
   }
   case WM_MOUSELEAVE: {
      _raton_dentro = false;
      break;
   }
   case WM_LBUTTONDOWN: {
      _bot_izq = true;
      break;
   }
   case WM_LBUTTONUP: {
      _bot_izq = false;
      break;
   }
   case WM_RBUTTONDOWN: {
      _bot_der = true;
      break;
   }
   case WM_RBUTTONUP: {
      _bot_der = false;
      break;
   }
   case WM_KEYDOWN: {
     bool push_it = false;


     // Escape
     push_it |= (wParam == VK_ESCAPE);

     // Flechas
     push_it |= (wParam == VK_LEFT ||
                 wParam == VK_RIGHT ||
                 wParam == VK_UP ||
                 wParam == VK_DOWN);

     // Barra espaciadora
     push_it |= (wParam == VK_SPACE);

     push_it |= (wParam == VK_BACK);

     push_it |= (wParam == VK_RETURN);

     push_it |= (wParam == VK_TAB);

     // Números 0-9
     push_it |= (wParam >= 48 && wParam <= 57);

     // Letras A-Z
     push_it |= (wParam >= 65 && wParam <= 90);

     // Letra Ñ
     push_it |= (wParam == VK_OEM_3);   //para incluir la Ñ

     // Teclas de función
     for (unsigned int i = 0; i < 12; i++) {
       push_it |= (wParam == (VK_F1 + i));  //hasta 12 teclas de funcion f1-f12
     }

     if (push_it) _teclas.push(wParam);

     break;
   }
   case WM_DESTROY: {
      DeleteObject (hBitmap);
      DeleteDC (hDCMem);
      PostQuitMessage(0);
        return 0;
        break;
   }
   default:
      return DefWindowProc (hWnd, message, wParam, lParam);
   }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Funciones del API
//
////////////////////////////////////////////////////////////////////////////////

COLORREF _color = RGB(255, 255, 255);

namespace minigraph {

int tecla() {
    if (_teclas.empty()) return NINGUNA;

    int ret = NINGUNA;
    switch(_teclas.front()) {
    case VK_LEFT:   ret = IZQUIERDA; break;
    case VK_RIGHT:  ret = DERECHA; break;
    case VK_UP:     ret = ARRIBA; break;
    case VK_DOWN:   ret = ABAJO; break;
    case VK_ESCAPE: ret = ESCAPE; break;
    case VK_SPACE:  ret = ESPACIO; break;
    case VK_RETURN: ret = ENTER; break;
    case VK_F1:     ret = F1; break;
    case VK_F2:     ret = F2; break;
    case VK_F3:     ret = F3; break;
    case VK_F4:     ret = F4; break;
    case VK_F5:     ret = F5; break;
    case VK_F6:     ret = F6; break;
    case VK_F7:     ret = F7; break;
    case VK_F8:     ret = F8; break;
    case VK_F9:     ret = F9; break;
    case VK_F10:    ret = F10; break;
    case VK_F11:    ret = F11; break;
    case VK_F12:    ret = F12; break;
    case VK_BACK:   ret = RETROCESO; break;
    case VK_TAB:    ret = TABULADOR; break;
    case VK_OEM_3:  ret = 'Ñ';break;
    default: ret = _teclas.front();
    }
    _teclas.pop();
    return ret;
}

void limpiamemoriatecla(){
    while(!_teclas.empty())
        _teclas.pop();
}

bool raton(float& x, float& y) {
   if (!_raton_dentro) {
      return false;
   }
   x = _xraton;
   y = _yraton;
   return true;
}

bool raton_dentro() {
   return _raton_dentro;
}

float raton_x() {
   return _xraton;
}

float raton_y() {
   return _yraton;
}

void raton_botones(bool& izq, bool& der) {
   izq = _bot_izq;
   der = _bot_der;
}

bool raton_boton_izq() {
   return _bot_izq;
}

bool raton_boton_der() {
   return _bot_der;
}

void espera(int miliseg) {
   Sleep(miliseg);
}

void mensaje(std::string msj) {
   MessageBox(hWnd, msj.c_str(), "Mensaje...", MB_OK);
}

void mensajeEx(const std::string& msj, void (*callback)()) {
    MessageBox(nullptr, msj.c_str(), "Mensaje...", MB_OK);
    if (callback != nullptr) {
        callback();
    }
}

bool pregunta(std::string msj) {
   return MessageBox(hWnd, msj.c_str(), "Pregunta...", MB_YESNO) == IDYES;
}

void vdefine(int ample, int alt,std::string vtitulo){
    iWidth  = ample;                      // ancho de la ventana
    iHeight = alt;                      // alto de la ventana
    Tventana = vtitulo;
}

int vancho() {
   return iWidth;
}

int valto() {
   return iHeight;
}

void vredimensiona(int ample, int alt) {
   iWidth = ample;
   iHeight = alt;
   int w, h;
   frame_real(iWidth, iHeight, w, h);
   SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOMOVE);
   newMemDC(w, h);
}

void vcierra() {
  PostMessage(hWnd, WM_CLOSE, 0, 0);
}

void vborra() {
   RECT R;
   SetRect(&R, 0, 0, iWidth, iHeight);
   HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
   FillRect(hDCMem, &R, hBrush);
   DeleteObject(hBrush);
   vrefresca();
}

void vrefresca() {
    espera(10);
   InvalidateRect(hWnd, NULL, FALSE);
}

void estilolinea(int ELinea, int GLinea){
    TPen = ((ELinea>0)&&(ELinea<5))?ELinea:0;
    GPen = (TPen == EL_CONTINUA)?GLinea:1;
}

void estilorelleno(int ERelleno){
    RBrush = ((ERelleno>=0)&&(ERelleno<7))?ERelleno:7;

}

void punto(float x, float y) {
  SetPixel(hDCMem, int(x), int(y), _color);
  vrefresca();
}

void linea(float x_ini, float y_ini, float x_fin, float y_fin) {
   BeginPath(hDCMem);
   MoveToEx(hDCMem, int(x_ini), int(y_ini), NULL);
   LineTo(hDCMem, int(x_fin), int(y_fin));
   EndPath(hDCMem);
   HPEN hPen = CreatePen(TPen, GPen, _color);
   SelectObject(hDCMem, hPen);
   StrokePath(hDCMem);
   DeleteObject(hPen);
   vrefresca();
}
void linea_polar(float x, float y, float lon,float ang){
    float angrad= ang*M_PI/180;
    linea(x,y,x+cos(angrad)*lon,y-sin(angrad)*lon);
}

inline void _rect(float izq, float arr, float der, float aba) {
   BeginPath(hDCMem);
   Rectangle(hDCMem,izq,arr,der,aba);
   EndPath(hDCMem);
}

void rectangulo(float izq, float arr, float der, float aba) {
   HPEN hPen = CreatePen(TPen, GPen, _color);
   HGDIOBJ orig = SelectObject(hDCMem, hPen);
   _rect(izq, arr, der, aba);
   StrokePath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hPen);
   vrefresca();
}

void rectangulo_lleno(float izq, float arr, float der, float aba) {
   HBRUSH hBrush = CreateHatchBrush(RBrush,_color);
   HGDIOBJ orig = SelectObject(hDCMem, hBrush);
   _rect(izq, arr, der, aba);
   FillPath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hBrush);
   vrefresca();
}

inline void _rectred(float izq, float arr, float der, float aba, float Resquina) {
   BeginPath(hDCMem);
   RoundRect(hDCMem, izq, arr, der, aba, Resquina, Resquina);
   EndPath(hDCMem);
}

void rectanguloredondeado(float izq, float arr, float der, float aba, float Resquina) {
   HPEN hPen = CreatePen(TPen, GPen, _color);
   HGDIOBJ orig = SelectObject(hDCMem, hPen);
   _rectred(izq, arr, der, aba, Resquina);
   StrokePath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hPen);
   vrefresca();
}

void rectanguloredondeado_lleno(float izq, float arr, float der, float aba, float Resquina) {
   HBRUSH hBrush = CreateHatchBrush(RBrush,_color);
   HGDIOBJ orig = SelectObject(hDCMem, hBrush);
   _rectred(izq, arr, der, aba, Resquina);
   FillPath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hBrush);
   vrefresca();
}

inline void _arc(float x_cen, float y_cen, float radio, float ang_i, float ang_f) {
   BeginPath(hDCMem);
   MoveToEx(hDCMem, x_cen+cos(ang_i*M_PI/180)*radio, y_cen-sin(ang_i*M_PI/180)*radio, NULL); //
   AngleArc(hDCMem, x_cen , y_cen , radio, ang_i, ang_f-ang_i);
   EndPath(hDCMem);
}

void arco(float x_cen, float y_cen, float radio, float ang_i, float ang_f) {
   HPEN hPen = CreatePen(TPen, GPen, _color);
   HGDIOBJ orig = SelectObject(hDCMem, hPen);
   _arc(x_cen, y_cen, radio, ang_i,ang_f);
   StrokePath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hPen);
   vrefresca();
}
void arco_lleno(float x_cen, float y_cen, float radio, float ang_i, float ang_f) {
   HBRUSH hBrush = CreateHatchBrush(RBrush,_color);
   HGDIOBJ orig = SelectObject(hDCMem, hBrush);
   BeginPath(hDCMem);
   MoveToEx(hDCMem, x_cen, y_cen, NULL);
   AngleArc(hDCMem, x_cen , y_cen , radio, ang_i, ang_f-ang_i);
   LineTo(hDCMem, x_cen , y_cen );
   EndPath(hDCMem);
   FillPath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hBrush);
   vrefresca();
}
inline void _circ(float x_cen, float y_cen, float radio) {
   BeginPath(hDCMem);
   Ellipse(hDCMem,(x_cen-radio),(y_cen-radio),(x_cen+radio),(y_cen+radio));
   EndPath(hDCMem);
}

void circulo(float x_cen, float y_cen, float radio) {
   HPEN hPen = CreatePen(TPen, GPen, _color);
   HGDIOBJ orig = SelectObject(hDCMem, hPen);
   _circ(x_cen, y_cen, radio);
   StrokePath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hPen);
   vrefresca();
}

void circulo_lleno(float x_cen, float y_cen, float radio) {
   HBRUSH hBrush = CreateHatchBrush(RBrush,_color);
   HGDIOBJ orig = SelectObject(hDCMem, hBrush);
   _circ(x_cen, y_cen, radio);
   FillPath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hBrush);
   vrefresca();
}


inline void _elip(float izq, float arr, float der, float aba) {
   BeginPath(hDCMem);
   Ellipse(hDCMem,izq,arr,der,aba);
   EndPath(hDCMem);
}

void elipse(float izq, float arr, float der, float aba) {
   HPEN hPen = CreatePen(TPen, GPen, _color);
   HGDIOBJ orig = SelectObject(hDCMem, hPen);
   _elip(izq, arr, der, aba);
   StrokePath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hPen);
   vrefresca();
}

void elipse_lleno(float izq, float arr, float der, float aba) {
   HBRUSH hBrush = CreateHatchBrush(RBrush,_color);
   HGDIOBJ orig = SelectObject(hDCMem, hBrush);
   _elip(izq, arr, der, aba);
   FillPath(hDCMem);
   SelectObject(hDCMem, orig);
   DeleteObject(hBrush);
   vrefresca();
}

void justificartexto(int _estilo){
    switch(_estilo){
    case JF_CENTRO: FJustificado = (TA_CENTER|TA_BOTTOM);break;
    case JF_DERECHA: FJustificado =(TA_RIGHT|TA_BOTTOM);break;
    default : FJustificado = (TA_LEFT|TA_BOTTOM);
    }
}


void texto(float x, float y, float ancho, float alto, const std::string& texto) {
    HFONT HFuente;
    RECT areaR;

    areaR.top = y-alto/2;
    areaR.bottom = y+alto/2;

    if(FJustificado==(TA_CENTER|TA_BOTTOM)){
        areaR.left = x-ancho/2;
        areaR.right = x+ancho/2;
   }

   if(FJustificado==(TA_RIGHT|TA_BOTTOM)){
        areaR.left = x-ancho;
        areaR.right = x;
   }
   if(FJustificado==(TA_LEFT|TA_BOTTOM)){
        areaR.left = x;
        areaR.right = x+ancho;
   }

   SetTextColor(hDCMem, _color);
   HFuente = CreateFont(FTamano,0 ,FInclinacion*10, FInclinacion*10,
            (FNegrita)?700:400, FCursiva, FSubrayada, FTachada,
            DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
            PROOF_QUALITY, DEFAULT_PITCH | FF_ROMAN, FNombre.c_str());
   SelectObject(hDCMem, HFuente);
   SetTextAlign(hDCMem, FJustificado);
   ExtTextOutA(hDCMem, int(x), int(y+alturafuente()/2),ETO_CLIPPED,&areaR,texto.c_str(), int(texto.size()),NULL);
   vrefresca();
}

int alturafuente(){
    return FTamano;
}


void formatotexto(std::string nombrefuente, int tamanofuente, int inclinacion, int NSCT){
    FNombre = nombrefuente;
    FTamano = tamanofuente;
    FInclinacion = inclinacion;
    FNegrita = false;
    FCursiva = false;
    FSubrayada = false;
    FTachada = false;

    if(NSCT&1)  FNegrita = true;

    if(NSCT&2)  FSubrayada = true;

    if(NSCT&4)  FCursiva = true;

    if(NSCT&8)  FTachada = true;
}

static COLORREF _colores[] = {
   RGB(0, 0, 0),       // NEGRO
   RGB(255, 0, 0),     // ROJO
   RGB(0, 255, 0),     // VERDE
   RGB(0, 0, 255),     // AZUL
   RGB(255, 255, 0),   // AMARILLO
   RGB(255, 0, 255),   // MAGENTA
   RGB(0, 255, 255),   // CYAN
   RGB(255, 255, 255), // BLANCO
   RGB(128, 128, 128), // GRIS
   RGB(119, 67, 66),   //CAFE
   RGB(255, 127, 39),   //NARANJA
   RGB(250, 128, 114),  //SALMON
   RGB(255, 192, 203),  //ROSADO
   RGB(255, 105, 180),  //ROSADOFUERTE
   RGB(255, 215, 0),    //ORO
   RGB(230, 230, 250),  //LAVANDA
   RGB(238, 130, 238),  //VIOLETA
   RGB(147, 112, 219),  //MORADO
   RGB(173, 255, 47),   //LIMON
   RGB(128, 128, 0),    //OLIVO
   RGB(64, 224, 208),   //TURQUESA
   RGB(192, 192, 192),  //PLATA

};

void color(int c) {
   _color = _colores[c];
}

void color_rgb(int r, int g, int b) {
   _color = RGB(r, g, b);
}


} // namespace minigrph

///////////////////////////////////////////////////////////////////////////////////////


//#endif
