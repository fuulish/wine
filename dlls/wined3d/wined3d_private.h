/*
 * Direct3D wine internal private include file
 *
 * Copyright 2002-2003 The wine-d3d team
 * Copyright 2002-2003 Raphael Junqueira
 * Copyright 2004      Jason Edmeades   
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __WINE_WINED3D_PRIVATE_H
#define __WINE_WINED3D_PRIVATE_H

#include <stdarg.h>
#define NONAMELESSUNION
#define NONAMELESSSTRUCT
#include "windef.h"
#include "winbase.h"
#include "winreg.h"
#include "wingdi.h"
#include "winuser.h"
#include "wine/debug.h"

#include "d3d9.h"
#include "d3d9types.h"
#include "wine/wined3d_interface.h"
#include "wine/wined3d_gl.h"

extern int vs_mode;
#define VS_NONE 0
#define VS_HW   1
#define VS_SW   2

extern int ps_mode;
#define PS_NONE 0
#define PS_HW   1

/* X11 locking */

extern void (*wine_tsx11_lock_ptr)(void);
extern void (*wine_tsx11_unlock_ptr)(void);

/* As GLX relies on X, this is needed */
extern int num_lock;

#if 0
#define ENTER_GL() ++num_lock; if (num_lock > 1) FIXME("Recursive use of GL lock to: %d\n", num_lock); wine_tsx11_lock_ptr()
#define LEAVE_GL() if (num_lock != 1) FIXME("Recursive use of GL lock: %d\n", num_lock); --num_lock; wine_tsx11_unlock_ptr()
#else
#define ENTER_GL() wine_tsx11_lock_ptr()
#define LEAVE_GL() wine_tsx11_unlock_ptr()
#endif

/*****************************************************************************
 * Defines
 */
#define GL_SUPPORT(ExtName)           (This->gl_info.supported[ExtName] != 0)


#define MAX_STREAMS  16  /* Maximum possible streams - used for fixed size arrays
                            See MaxStreams in MSDN under GetDeviceCaps */

#define WINED3D_VSHADER_MAX_CONSTANTS  96   
                         /* Maximum number of constants provided to the shaders */

/*****************************************************************************
 * IWineD3D implementation structure
 */
typedef struct IWineD3DImpl
{
    /* IUnknown fields */
    IWineD3DVtbl           *lpVtbl;
    DWORD                   ref;     /* Note: Ref counting not required */

    /* WineD3D Information */
    UINT                    dxVersion;

    /* GL Information */
    BOOL                    isGLInfoValid;
    WineD3D_GL_Info         gl_info;
} IWineD3DImpl;

extern IWineD3DVtbl IWineD3D_Vtbl;

/*****************************************************************************
 * IWineD3DDevice implementation structure
 */
typedef struct IWineD3DDeviceImpl
{
    /* IUnknown fields */
    IWineD3DDeviceVtbl     *lpVtbl;
    DWORD                   ref;     /* Note: Ref counting not required */

    /* WineD3D Information */
    IWineD3D               *WineD3D;

    /* GL Information */
} IWineD3DDeviceImpl;

extern IWineD3DDeviceVtbl IWineD3DDevice_Vtbl;

/* Utility function prototypes */
const char* debug_d3dformat(D3DFORMAT fmt);
const char* debug_d3ddevicetype(D3DDEVTYPE devtype);
const char* debug_d3dresourcetype(D3DRESOURCETYPE res);
const char* debug_d3dusage(DWORD usage);



#if 0 /* Needs fixing during rework */
/*****************************************************************************
 * IDirect3DVertexShaderDeclaration implementation structure
 */
struct IDirect3DVertexShaderDeclarationImpl {
  /* The device */
  /*IDirect3DDeviceImpl* device;*/

  /** precomputed fvf if simple declaration */
  DWORD   fvf[MAX_STREAMS];
  DWORD   allFVF;

  /** dx8 compatible Declaration fields */
  DWORD*  pDeclaration8;
  DWORD   declaration8Length;
};


/*****************************************************************************
 * IDirect3DVertexShader implementation structure
 */
struct IDirect3DVertexShaderImpl {
  /* The device */
  /*IDirect3DDeviceImpl* device;*/

  DWORD* function;
  UINT functionLength;
  DWORD usage;
  DWORD version;
  /* run time datas */
  VSHADERDATA* data;
  VSHADERINPUTDATA input;
  VSHADEROUTPUTDATA output;
};


/*****************************************************************************
 * IDirect3DPixelShader implementation structure
 */
struct IDirect3DPixelShaderImpl { 
  /* The device */
  /*IDirect3DDeviceImpl* device;*/

  DWORD* function;
  UINT functionLength;
  DWORD version;
  /* run time datas */
  PSHADERDATA* data;
  PSHADERINPUTDATA input;
  PSHADEROUTPUTDATA output;
};

#endif /* Needs fixing during rework */
#endif
