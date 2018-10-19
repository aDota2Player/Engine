#pragma once


#ifdef  LONELY_INPUT

/*
* These key codes are same as GLFW key codes, just without GLFW_ prefix. (eg. GLFW_KEY_SPACE -> KEY_SPACE) and some additional aliases
* Purpose of these key codes is to make code a bit neater.
* In order to add these key codes define "LONELY_INPUT" before including this or window header file.
*/


/*  unknown key	 */
#define KEY_UNKNOWN				-1


/*  Printable keys  */
#define KEY_SPACE				32  /*   */
#define KEY_APOSTROPHE			39  /* ' */
#define KEY_COMMA				44  /* , */
#define KEY_MINUS				45  /* - */
#define KEY_PERIOD				46  /* . */
#define KEY_SLASH				47  /* / */

#define KEY_0					48  /* 0 */
#define KEY_1					49  /* 1 */
#define KEY_2					50  /* 2 */
#define KEY_3					51  /* 3 */
#define KEY_4					52  /* 4 */
#define KEY_5					53  /* 5 */
#define KEY_6					54  /* 6 */
#define KEY_7					55  /* 7 */
#define KEY_8					56  /* 8 */
#define KEY_9					57  /* 9 */

#define KEY_SEMICOLON			59 /* ; */
#define KEY_EQUAL				61 /* = */

#define KEY_A					65  /* A */
#define KEY_B					66  /* B */
#define KEY_C					67  /* C */
#define KEY_D					68  /* D */
#define KEY_E					69  /* E */
#define KEY_F					70  /* F */
#define KEY_G					71  /* G */
#define KEY_H					72  /* H */
#define KEY_I					73  /* I */
#define KEY_J					74  /* J */
#define KEY_K					75  /* K */
#define KEY_L					76  /* L */
#define KEY_M					77  /* M */
#define KEY_N					78  /* N */
#define KEY_O					79  /* O */
#define KEY_P					80  /* P */
#define KEY_Q					81  /* Q */
#define KEY_R					82  /* R */
#define KEY_S					83  /* S */
#define KEY_T					84  /* T */
#define KEY_U					85  /* U */
#define KEY_V					86  /* V */
#define KEY_W					87  /* W */
#define KEY_X					88  /* X */
#define KEY_Y					89  /* Y */
#define KEY_Z					90  /* Z */

#define KEY_LEFT_BRACKET		91  /* [ */
#define KEY_BACKSLASH			92  /* \ */
#define KEY_RIGHT_BRACKET		93  /* ] */
#define KEY_GRAVE_ACCENT		96  /* ` */
#define KEY_WORLD_1				161 /* non-US #1 */
#define KEY_WORLD_2				162 /* non-US #2 */


/*  Function keys  */
#define KEY_ESCAPE				256 
#define KEY_ENTER				257 
#define KEY_TAB					258 
#define KEY_BACKSPACE			259 
#define KEY_INSERT				260 
#define KEY_DELETE				261 

#define KEY_RIGHT				262 
#define KEY_LEFT				263 
#define KEY_DOWN				264 
#define KEY_UP					265 

#define KEY_PAGE_UP				266 
#define KEY_PAGE_DOWN			267 
#define KEY_HOME				268 
#define KEY_END					269 

#define KEY_CAPS_LOCK			280 
#define KEY_SCROLL_LOCK			281 
#define KEY_NUM_LOCK			282 
#define KEY_PRINT_SCREEN		283 
#define KEY_PAUSE				284 

#define KEY_F1					290
#define KEY_F2					291
#define KEY_F3					292
#define KEY_F4					293
#define KEY_F5					294
#define KEY_F6					295
#define KEY_F7					296
#define KEY_F8					297
#define KEY_F9					298
#define KEY_F10					299
#define KEY_F11					300
#define KEY_F12					301
#define KEY_F13					302
#define KEY_F14					303
#define KEY_F15					304
#define KEY_F16					305
#define KEY_F17					306
#define KEY_F18					307
#define KEY_F19					308
#define KEY_F20					309
#define KEY_F21					310
#define KEY_F22					311
#define KEY_F23					312
#define KEY_F24					313
#define KEY_F25					314
								
#define KEY_KP_0				320
#define KEY_KP_1				321
#define KEY_KP_2				322
#define KEY_KP_3				323
#define KEY_KP_4				324
#define KEY_KP_5				325
#define KEY_KP_6				326
#define KEY_KP_7				327
#define KEY_KP_8				328
#define KEY_KP_9				329

#define KEY_KP_DECIMAL			330
#define KEY_KP_DIVIDE			331
#define KEY_KP_MULTIPLY			332
#define KEY_KP_SUBTRACT			333
#define KEY_KP_ADD				334
#define KEY_KP_ENTER			335
#define KEY_KP_EQUAL			336

#define KEY_LEFT_SHIFT			340
#define KEY_LEFT_CONTROL		341
#define KEY_LEFT_ALT			342
#define KEY_LEFT_SUPER			343
#define KEY_LSHIFT				340 // alias: KEY_LEFT_SHIFT
#define KEY_LCONTROL			341 // alias: KEY_LEFT_CONTROL
#define KEY_LALT				342 // alias: KEY_LEFT_ALT
#define KEY_LSUPER				343 // alias: KEY_LEFT_SUPER

#define KEY_RIGHT_SHIFT			344
#define KEY_RIGHT_CONTROL		345
#define KEY_RIGHT_ALT			346
#define KEY_RIGHT_SUPER			347
#define KEY_RSHIFT				344 // alias: KEY_RIGHT_SHIFT	    
#define KEY_RCONTROL			345 // alias: KEY_RIGHT_CONTROL
#define KEY_RALT				346 // alias: KEY_RIGHT_ALT
#define KEY_RSUPER				347 // alias: KEY_RIGHT_SUPER

#define KEY_MENU				348


/* Mouse buttons */
#define MOUSE_BUTTON_1         0
#define MOUSE_BUTTON_2         1
#define MOUSE_BUTTON_3         2
#define MOUSE_BUTTON_4         3
#define MOUSE_BUTTON_5         4
#define MOUSE_BUTTON_6         5
#define MOUSE_BUTTON_7         6
#define MOUSE_BUTTON_8         7
#define MOUSE_BUTTON_LEFT      MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT     MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE    MOUSE_BUTTON_3

#endif

#define LONELY_MAX_KEYBOARD_KEYS	    347
#define LONELY_MAX_MOUSE_BUTTONS	    7


namespace lonely { namespace app {


	enum class KeyboardKey { RELEASE = 0, PRESS, REPEAT };
	enum class MouseButton { RELEASE = 0, PRESS         };

	class Input
	{
	private:
		friend class Window;

		KeyboardKey m_Keys    [LONELY_MAX_KEYBOARD_KEYS];
		MouseButton m_Buttons [LONELY_MAX_MOUSE_BUTTONS];

		int m_LastKey;
		int m_LastButton;

		double m_MouseX, m_MouseY;

	public:
		Input(): m_Keys(), m_Buttons() {}

		inline int GetKey   (int key   ) const { return (char)m_Keys[key];       }
		inline int GetButton(int button) const { return (char)m_Buttons[button]; }

		inline double GetMouseX() const { return m_MouseX; }
		inline double GetMouseY() const { return m_MouseY; }
	};

} }
