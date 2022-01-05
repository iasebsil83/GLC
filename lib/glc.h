#ifndef GLC_H
#define GLC_H








// ---------------- IMPORTATIONS ----------------

//openGL + GLU + GLUT
#include <glut.h>








// ---------------- DECLARATIONS ----------------

//keyboard constants
enum GLC_KEYBOARD{
	GLC_KEY_PRESSED,
	GLC_KEY_RELEASED
};

enum GLC_KEYS{

	//function keys
	GLC_KEY_F1  = 0x101,
	GLC_KEY_F2  = 0x102,
	GLC_KEY_F3  = 0x103,
	GLC_KEY_F4  = 0x104,
	GLC_KEY_F5  = 0x105,
	GLC_KEY_F6  = 0x106,
	GLC_KEY_F7  = 0x107,
	GLC_KEY_F8  = 0x108,
	GLC_KEY_F9  = 0x109,
	GLC_KEY_F10 = 0x10a,
	GLC_KEY_F11 = 0x10b,
	GLC_KEY_F12 = 0x10c,

	//command keys
	GLC_KEY_ESCAPE    = 0x01b,
	GLC_KEY_END       = 0x16b,
	GLC_KEY_HOME      = 0x16a,
	GLC_KEY_PAGE_UP   = 0x168,
	GLC_KEY_PAGE_DOWN = 0x169,
	GLC_KEY_DELETE    = 0x07f,
	GLC_KEY_BACKSPACE = 0x008,
	GLC_KEY_INSERT    = 0x16c,

	//combination keys
	GLC_KEY_LEFT_SHIFT  = 0x170,
	GLC_KEY_RIGHT_SHIFT = 0x171,
	GLC_KEY_LEFT_CTRL   = 0x172,
	GLC_KEY_RIGHT_CTRL  = 0x173,
	GLC_KEY_LEFT_ALT    = 0x174,

	//special characters
	GLC_KEY_BACK_QUOTE  = 0x0b2,
	GLC_KEY_AMPERSAND   = 0x026,
	GLC_KEY_DBL_QUOTE   = 0x022, //double quote
	GLC_KEY_QUOTE       = 0x027,
	GLC_KEY_UNDERSCORE  = 0x05f,
	GLC_KEY_TAB         = 0x009,
	GLC_KEY_CIRCUMFLEX  = 0x05e,
	GLC_KEY_DOLLAR      = 0x024,
	GLC_KEY_LESS_THAN   = 0x03c, //<
	GLC_KEY_GREA_THAN   = 0x03e, //>
	GLC_KEY_COMA        = 0x02c,
	GLC_KEY_SEMI_COLON  = 0x03b,
	GLC_KEY_COLON       = 0x03a,
	GLC_KEY_EXCLAMATION = 0x021,
	GLC_KEY_SPACE       = 0x020,
	GLC_KEY_RETURN      = 0x00d,
	GLC_KEY_TILDE       = 0x07e,
	GLC_KEY_HASHTAG     = 0x023,
	GLC_KEY_PARENTH_B   = 0x028, //parentheses begin
	GLC_KEY_PARENTH_E   = 0x029, //            end
	GLC_KEY_BRACKETS_B  = 0x05b, //brackets begin
	GLC_KEY_BRACKETS_E  = 0x05d, //         end
	GLC_KEY_BRACES_B    = 0x07b, //braces begin
	GLC_KEY_BRACES_E    = 0x07d, //       end
	GLC_KEY_POINT       = 0x02e,
	GLC_KEY_PARAGRAPH   = 0x0a7,
	GLC_KEY_DEGREE      = 0x0b0,
	GLC_KEY_PIPE        = 0x07c,
	GLC_KEY_BACKSLASH   = 0x05c,
	GLC_KEY_AT          = 0x040,
	GLC_KEY_POUND       = 0x0a3,
	GLC_KEY_DIERESIS    = 0x0a8,
	GLC_KEY_BLOCK       = 0x0a4,
	GLC_KEY_ACUTE       = 0x060,
	GLC_KEY_MU          = 0x0b5,
	GLC_KEY_QUESTION    = 0x03f,

	//numbers & maths
	GLC_KEY_0        = 0x030,
	GLC_KEY_1        = 0x031,
	GLC_KEY_2        = 0x032,
	GLC_KEY_3        = 0x033,
	GLC_KEY_4        = 0x034,
	GLC_KEY_5        = 0x035,
	GLC_KEY_6        = 0x036,
	GLC_KEY_7        = 0x037,
	GLC_KEY_8        = 0x038,
	GLC_KEY_9        = 0x039,
	GLC_KEY_PLUS     = 0x02b,
	GLC_KEY_MINUS    = 0x02d,
	GLC_KEY_ASTERISK = 0x02a,
	GLC_KEY_SLASH    = 0x02f,
	GLC_KEY_EQUAL    = 0x03d,
	GLC_KEY_PERCENT  = 0x025,

	//arrows
	GLC_KEY_LEFT  = 0x164,
	GLC_KEY_UP    = 0x165,
	GLC_KEY_RIGHT = 0x166,
	GLC_KEY_DOWN  = 0x167,

	//capital letters
	GLC_KEY_A = 0x041,
	GLC_KEY_B = 0x042,
	GLC_KEY_C = 0x043,
	GLC_KEY_D = 0x044,
	GLC_KEY_E = 0x045,
	GLC_KEY_F = 0x046,
	GLC_KEY_G = 0x047,
	GLC_KEY_H = 0x048,
	GLC_KEY_I = 0x049,
	GLC_KEY_J = 0x04a,
	GLC_KEY_K = 0x04b,
	GLC_KEY_L = 0x04c,
	GLC_KEY_M = 0x04d,
	GLC_KEY_N = 0x04e,
	GLC_KEY_O = 0x04f,
	GLC_KEY_P = 0x050,
	GLC_KEY_Q = 0x051,
	GLC_KEY_R = 0x052,
	GLC_KEY_S = 0x053,
	GLC_KEY_T = 0x054,
	GLC_KEY_U = 0x055,
	GLC_KEY_V = 0x056,
	GLC_KEY_W = 0x057,
	GLC_KEY_X = 0x058,
	GLC_KEY_Y = 0x059,
	GLC_KEY_Z = 0x05a,

	//minimal letters
	GLC_KEY_a = 0x061,
	GLC_KEY_b = 0x062,
	GLC_KEY_c = 0x063,
	GLC_KEY_d = 0x064,
	GLC_KEY_e = 0x065,
	GLC_KEY_f = 0x066,
	GLC_KEY_g = 0x067,
	GLC_KEY_h = 0x068,
	GLC_KEY_i = 0x069,
	GLC_KEY_j = 0x06a,
	GLC_KEY_k = 0x06b,
	GLC_KEY_l = 0x06c,
	GLC_KEY_m = 0x06d,
	GLC_KEY_n = 0x06e,
	GLC_KEY_o = 0x06f,
	GLC_KEY_p = 0x070,
	GLC_KEY_q = 0x071,
	GLC_KEY_r = 0x072,
	GLC_KEY_s = 0x073,
	GLC_KEY_t = 0x074,
	GLC_KEY_u = 0x075,
	GLC_KEY_v = 0x076,
	GLC_KEY_w = 0x077,
	GLC_KEY_x = 0x078,
	GLC_KEY_y = 0x079,
	GLC_KEY_z = 0x07a,

	//non-ASCII letters
	GLC_KEY_A_ACCENT_E = 0x0e9, //acute accentuated E
	GLC_KEY_G_ACCENT_E = 0x0e8, //grave accentuated E
	GLC_KEY_G_ACCENT_A = 0x0e0, //grave accentuated A
	GLC_KEY_G_ACCENT_U = 0x0f9, //grave accentuated U
	GLC_KEY_CEDILLA_C  = 0x0e7
};

//event constants
enum GLC_EVENTS{
	GLC_KEYBOARD,
	GLC_MOUSE_CLICK,
	GLC_MOUSE_MOVE,
	GLC_MOUSE_SCROLL,
	GLC_DISPLAY,
	GLC_RESIZE,
	GLC_TIMER
};

//mouse constants
#define GLC_MOUSE_PRESSED  0x0000
#define GLC_MOUSE_RELEASED 0x0001
#define GLC_LEFT_BUTTON    0x0000
#define GLC_MIDDLE_BUTTON  0x0001
#define GLC_RIGHT_BUTTON   0x0002
#define GLC_SCROLL_UP      0x0003
#define GLC_SCROLL_DOWN    0x0004

//maths
#define M_2PI 6.283185307179586

//2D graphics
#define GLC_EMPTY  (char)0
#define GLC_FILLED (char)1

//3D constants
#define GLC_SKYCOLOR 255 //RGBA color corresponding to (0,  0,  0,255) (perfect black)

//glc types
typedef float unit;

typedef struct {
	unit x;
	unit y;
	unit z;
} xyz;

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} color;

typedef GLfloat ambient[4];
typedef GLfloat diffuse[4];
typedef GLfloat specular[4];
typedef struct {
	ambient*  a;
	diffuse*  d;
	specular* s;
} ray;

typedef struct {
	GLfloat pos[4];
	ray*    r;
} light;








// ---------------- GENERAL TOOLS ----------------

//useful
#define GLC_refresh()    glutPostRedisplay()
#define GLC_fullScreen() glutFullScreen()
void GLC_setThickness(unit thickness);
int  GLC_inScreen(unit x, unit y);

//timed executions
void GLC_setTimer(int ms);








// ---------------- BASICS -----------------

//init
void GLC_init(const char* name, unit width, unit height);

//start - stop
#define GLC_start() glutMainLoop()
void GLC_stop();








#endif
