/*
 * IDirect3DVertexBuffer9 implementation
 *
 * Copyright 2002-2004 Jason Edmeades
 *                     Raphael Junqueira
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

#include "config.h"
#include "d3d9_private.h"

WINE_DEFAULT_DEBUG_CHANNEL(d3d);

/* IDirect3DVertexBuffer9 IUnknown parts follow: */
HRESULT WINAPI IDirect3DVertexBuffer9Impl_QueryInterface(LPDIRECT3DVERTEXBUFFER9 iface, REFIID riid, LPVOID* ppobj) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;

    if (IsEqualGUID(riid, &IID_IUnknown)
        || IsEqualGUID(riid, &IID_IDirect3DResource9)
        || IsEqualGUID(riid, &IID_IDirect3DVertexBuffer9)) {
        IDirect3DVertexBuffer9Impl_AddRef(iface);
        *ppobj = This;
        return D3D_OK;
    }

    WARN("(%p)->(%s,%p),not found\n", This, debugstr_guid(riid), ppobj);
    return E_NOINTERFACE;
}

ULONG WINAPI IDirect3DVertexBuffer9Impl_AddRef(LPDIRECT3DVERTEXBUFFER9 iface) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    TRACE("(%p) : AddRef from %ld\n", This, This->ref);
    return InterlockedIncrement(&This->ref);
}

ULONG WINAPI IDirect3DVertexBuffer9Impl_Release(LPDIRECT3DVERTEXBUFFER9 iface) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    ULONG ref = InterlockedDecrement(&This->ref);
    TRACE("(%p) : ReleaseRef to %ld\n", This, This->ref);
    if (ref == 0) {
        IWineD3DVertexBuffer_Release(This->wineD3DVertexBuffer);
        HeapFree(GetProcessHeap(), 0, This);
    }
    return ref;
}

/* IDirect3DVertexBuffer9 IDirect3DResource9 Interface follow: */
HRESULT WINAPI IDirect3DVertexBuffer9Impl_GetDevice(LPDIRECT3DVERTEXBUFFER9 iface, IDirect3DDevice9** ppDevice) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IDirect3DResource9Impl_GetDevice((LPDIRECT3DRESOURCE9) This, ppDevice);
}

HRESULT WINAPI IDirect3DVertexBuffer9Impl_SetPrivateData(LPDIRECT3DVERTEXBUFFER9 iface, REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_SetPrivateData(This->wineD3DVertexBuffer, refguid, pData, SizeOfData, Flags);
}

HRESULT WINAPI IDirect3DVertexBuffer9Impl_GetPrivateData(LPDIRECT3DVERTEXBUFFER9 iface, REFGUID refguid, void* pData, DWORD* pSizeOfData) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_GetPrivateData(This->wineD3DVertexBuffer, refguid, pData, pSizeOfData);
}

HRESULT WINAPI IDirect3DVertexBuffer9Impl_FreePrivateData(LPDIRECT3DVERTEXBUFFER9 iface, REFGUID refguid) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_FreePrivateData(This->wineD3DVertexBuffer, refguid);
}

DWORD WINAPI IDirect3DVertexBuffer9Impl_SetPriority(LPDIRECT3DVERTEXBUFFER9 iface, DWORD PriorityNew) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_SetPriority(This->wineD3DVertexBuffer, PriorityNew);
}

DWORD WINAPI IDirect3DVertexBuffer9Impl_GetPriority(LPDIRECT3DVERTEXBUFFER9 iface) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_GetPriority(This->wineD3DVertexBuffer);
}

void WINAPI IDirect3DVertexBuffer9Impl_PreLoad(LPDIRECT3DVERTEXBUFFER9 iface) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    IWineD3DVertexBuffer_PreLoad(This->wineD3DVertexBuffer);
    return ;
}

D3DRESOURCETYPE WINAPI IDirect3DVertexBuffer9Impl_GetType(LPDIRECT3DVERTEXBUFFER9 iface) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_GetType(This->wineD3DVertexBuffer);
}

/* IDirect3DVertexBuffer9 Interface follow: */
HRESULT WINAPI IDirect3DVertexBuffer9Impl_Lock(LPDIRECT3DVERTEXBUFFER9 iface, UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_Lock(This->wineD3DVertexBuffer, OffsetToLock, SizeToLock, (BYTE **)ppbData, Flags);
}

HRESULT WINAPI IDirect3DVertexBuffer9Impl_Unlock(LPDIRECT3DVERTEXBUFFER9 iface) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_Unlock(This->wineD3DVertexBuffer);
}

HRESULT WINAPI IDirect3DVertexBuffer9Impl_GetDesc(LPDIRECT3DVERTEXBUFFER9 iface, D3DVERTEXBUFFER_DESC* pDesc) {
    IDirect3DVertexBuffer9Impl *This = (IDirect3DVertexBuffer9Impl *)iface;
    return IWineD3DVertexBuffer_GetDesc(This->wineD3DVertexBuffer, pDesc);
}

IDirect3DVertexBuffer9Vtbl Direct3DVertexBuffer9_Vtbl =
{
    IDirect3DVertexBuffer9Impl_QueryInterface,
    IDirect3DVertexBuffer9Impl_AddRef,
    IDirect3DVertexBuffer9Impl_Release,
    IDirect3DVertexBuffer9Impl_GetDevice,
    IDirect3DVertexBuffer9Impl_SetPrivateData,
    IDirect3DVertexBuffer9Impl_GetPrivateData,
    IDirect3DVertexBuffer9Impl_FreePrivateData,
    IDirect3DVertexBuffer9Impl_SetPriority,
    IDirect3DVertexBuffer9Impl_GetPriority,
    IDirect3DVertexBuffer9Impl_PreLoad,
    IDirect3DVertexBuffer9Impl_GetType,
    IDirect3DVertexBuffer9Impl_Lock,
    IDirect3DVertexBuffer9Impl_Unlock,
    IDirect3DVertexBuffer9Impl_GetDesc
};


/* IDirect3DDevice9 IDirect3DVertexBuffer9 Methods follow: */
HRESULT WINAPI IDirect3DDevice9Impl_CreateVertexBuffer(LPDIRECT3DDEVICE9 iface, 
						       UINT Size, DWORD Usage, DWORD FVF, D3DPOOL Pool, 
						       IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle) {
    
    IDirect3DVertexBuffer9Impl *object;
    IDirect3DDevice9Impl *This = (IDirect3DDevice9Impl *)iface;
    HRESULT hrc = D3D_OK;

    /* Allocate the storage for the device */
    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDirect3DVertexBuffer9Impl));
    if (NULL == object) {
        FIXME("Allocation of memory failed\n");
        *ppVertexBuffer = NULL;
        return D3DERR_OUTOFVIDEOMEMORY;
    }

    object->lpVtbl = &Direct3DVertexBuffer9_Vtbl;
    object->ref = 1;
    hrc = IWineD3DDevice_CreateVertexBuffer(This->WineD3DDevice, Size, Usage, FVF, Pool, &(object->wineD3DVertexBuffer), pSharedHandle, (IUnknown *)object);
    
    if (hrc != D3D_OK) {
        /* free up object */ 
        FIXME("(%p) call to IWineD3DDevice_CreateVertexBuffer failed\n", This);
        HeapFree(GetProcessHeap(), 0, object);
        *ppVertexBuffer = NULL;
    } else {
        *ppVertexBuffer = (LPDIRECT3DVERTEXBUFFER9) object;
    }
    return hrc;
}
