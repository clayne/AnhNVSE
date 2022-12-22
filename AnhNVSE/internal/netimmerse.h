#pragma once

// Source: JIP - netimmerse.cpp

#define CALL_EAX(addr) __asm mov eax, addr __asm call eax
#define ADDR_ReturnThis			0x6815C0

__declspec(naked) NiAVObject* __fastcall NiNode::GetBlockByName(const char* nameStr)	//	str of NiFixedString
{
	__asm
	{
		movzx	eax, word ptr[ecx + 0xA6]
		test	eax, eax
		jz		done
		push	esi
		push	edi
		mov		esi, [ecx + 0xA0]
		mov		edi, eax
		ALIGN 16
		iterHead:
		dec		edi
			js		iterEnd
			mov		eax, [esi]
			add		esi, 4
			test	eax, eax
			jz		iterHead
			cmp[eax + 8], edx
			jz		found
			mov		ecx, [eax]
			cmp		dword ptr[ecx + 0xC], ADDR_ReturnThis
			jnz		iterHead
			mov		ecx, eax
			call	NiNode::GetBlockByName
			test	eax, eax
			jz		iterHead
			found :
		pop		edi
			pop		esi
			retn
			ALIGN 16
			iterEnd :
			xor eax, eax
			pop		edi
			pop		esi
			done :
		retn
	}
}

__declspec(naked) NiAVObject* __fastcall NiNode::GetBlock(const char* blockName)
{
	__asm
	{
		cmp[edx], 0
		jz		retnNULL
		push	ecx
		push	edx
		CALL_EAX(0xA5B690)
		pop		ecx
		pop		ecx
		test	eax, eax
		jz		done
		lock dec dword ptr[eax - 8]
		jz		retnNULL
		cmp[ecx + 8], eax
		jz		found
		mov		edx, eax
		call	NiNode::GetBlockByName
		retn
		found :
		mov		eax, ecx
			retn
			retnNULL :
		xor eax, eax
			done :
		retn
	}
}

__declspec(naked) void NiAVObject::Update()
{
	__asm
	{
		push	ecx
		push	0
		push	0
		push	0
		mov		edx, esp
		push	0
		push	edx
		mov		eax, [ecx]
		call	dword ptr[eax + 0xA4]
		add		esp, 0xC
		pop		ecx
		mov		ecx, [ecx + 0x18]
		test	ecx, ecx
		jz		done
		mov		eax, [ecx]
		call	dword ptr[eax + 0xFC]
		done:
		retn
	}
}

__declspec(naked) NiNode* TESObjectREFR::GetNiNode()
{
	__asm
	{
		mov		eax, [ecx + 0x64]
		test	eax, eax
		jz		done
		mov		eax, [eax + 0x14]
		cmp		dword ptr[ecx + 0xC], 0x14
		jnz		done
		cmp		byte ptr[ecx + 0x64A], 0
		jnz		done
		mov		eax, [ecx + 0x694]
		done:
		retn
	}
}

__declspec(naked) NiAVObject* __fastcall GetNifBlock(TESObjectREFR* thisObj, UInt32 pcNode, char* blockName)
{
	__asm
	{
		test	dl, dl
		jz		notPlayer
		cmp		dword ptr[ecx + 0xC], 0x14
		jnz		notPlayer
		test	dl, 1
		jz		get1stP
		mov		eax, [ecx + 0x64]
		test	eax, eax
		jz		done
		mov		eax, [eax + 0x14]
		jmp		gotRoot
		get1stP :
		mov		eax, [ecx + 0x694]
			jmp		gotRoot
			notPlayer :
		call	TESObjectREFR::GetNiNode
			gotRoot :
		test	eax, eax
			jz		done
			mov		edx, [esp + 4]
			cmp[edx], 0
			jz		done
			mov		ecx, eax
			call	NiNode::GetBlock
			done :
		retn	4
	}
}