// Datei : DX8Graphics.h

// --------------------------------------------------------------------------------------
//
// Direct Graphics Klasse
// zum initialisieren von DirectX8
// beinhaltet zudem verschiedene Grafik-Funktionen zum Speichern von Screenshots usw
//
// (c) 2002 J�rg M. Winterstein
//
// --------------------------------------------------------------------------------------

#ifndef __DX8Graphics_h__
#define __DX8Graphics_h__

// --------------------------------------------------------------------------------------
// Include Dateien
// --------------------------------------------------------------------------------------

#if defined(PLATFORM_SDL)
#include "SDL_port.h"
#include "texture.h"
#if defined(USE_GL2)
#include "cshader.h"
#endif
#else
#include <d3d8.h>
#include <d3dx8.h>
#include <d3dx8tex.h>
#include <D3dx8math.h>
#endif

// --------------------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------------------

#define D3DFVF_TLVERTEX (D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE)	// Eigenes Flexible Vertex Format

#define	BackBufferSize 10		// Vertrex Unterteilungen des Backbuffers, muss gerade sein

#define ADDITIV_MODE  0
#define COLORKEY_MODE 1
#define WHITE_MODE	  2

#if defined(USE_GL2)
enum {
    PROGRAM_COLOR=0,
    PROGRAM_TEXTURE,
    PROGRAM_TOTAL,
    PROGRAM_NONE
};
#endif

// --------------------------------------------------------------------------------------
// Strukturen
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// Struktur f�r einen 2D Vertex
// --------------------------------------------------------------------------------------

struct VERTEX2D
{
	float		x, y, z;		// x,y,z Koordinaten
	D3DCOLOR	color;			// Vertex-Color
	float		tu, tv;			// Textur-Koordinaten
};

// --------------------------------------------------------------------------------------
// Klassendeklaration
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// DirectGraphics Klasse
// --------------------------------------------------------------------------------------

class DirectGraphicsClass
{
	private:
		bool					useVSync;						// VSync ein/aus ?
		bool					FilterMode;						// Linearer Filter an/aus?
#if defined(PLATFORM_DIRECTX)
		D3DDISPLAYMODE			d3ddm;							// Display Mode
#elif defined(PLATFORM_SDL)
        bool                    use_texture;
		SDL_Surface*            Screen;
		int                     MaxTextureUnits;
#if defined(USE_GL2)
        GLuint                  ProgramCurrent;
		CShader                 Shaders[PROGRAM_TOTAL];
#endif
#endif

	public:
		int						BlendMode;						// Additiv, Colorkey oder White mode aktiviert?
#if defined(PLATFORM_DIRECTX)
		D3DPRESENT_PARAMETERS	d3dpp;							// Present Parameters
#endif
		bool					SquareOnly;						// Nur quadratische Texturen
		bool					PowerOfTwo;						// Nur 2er Potenz Texturen
		void					ShowBackBuffer(void);			// Present aufrufen

	     DirectGraphicsClass(void);							// Konstruktor
		~DirectGraphicsClass(void);							// Desktruktor

		bool Init(HWND hwnd, DWORD dwBreite, DWORD dwHoehe,
                  DWORD dwZ_Bits, bool VSync);
		bool Exit(void);										// D3D beenden
		bool SetDeviceInfo(void);

		bool TakeScreenshot(const char Filename[100], int screenx,
												int screeny);	// Screenshot machen
		void SetColorKeyMode(void);								// Alpha f�r Colorkey oder
		void SetAdditiveMode(void);								// Additive-Blending nutzen
		void SetWhiteMode	(void);								// Komplett weiss rendern
		void SetFilterMode(bool filteron);						// Linearer Textur Filter ein/aus

		void RendertoBuffer (D3DPRIMITIVETYPE PrimitiveType,    // Rendert in den Buffer, der am Ende
							 UINT PrimitiveCount,				// eines jeden Frames komplett in
							 CONST void* pVertexStreamZeroData);// den Backbuffer gerendert wird

		void DisplayBuffer  (void);								// Render den Buffer auf den Backbuffer
#if defined(PLATFORM_SDL)
        void SetTexture( GLuint texture );
#endif
};

// --------------------------------------------------------------------------------------
// Externals
// --------------------------------------------------------------------------------------

extern LPDIRECT3D8				lpD3D;							// Direct3D Hauptobjekt
extern LPDIRECT3DDEVICE8		lpD3DDevice;					// Direct3D Device-Objekt
extern DirectGraphicsClass		DirectGraphics;					// DirectGraphics Klasse
extern LPDIRECT3DSURFACE8		lpBackbuffer;					// Der Backbuffer
#if defined(PLATFORM_DIRECTX)
extern D3DFORMAT				D3DFormat;						// Format der Primary Surface
extern D3DCAPS8					d3dcaps;						// M�glichkeiten der Hardware
#endif
extern LPDIRECT3DVERTEXBUFFER8	lpVBSprite;						// VertexBuffer f�r die Sprites
extern D3DXMATRIX				matProj;						// Projektionsmatrix
extern D3DXMATRIX				matWorld;						// Weltmatrix
extern float					DegreetoRad[360];				// Tabelle mit Rotationswerten

extern const double BackBufferX;
extern const double BackBufferY;

#endif

