#pragma once

#include "GameForms.h"
#include "GameBSExtraData.h"
#include "GameExtraData.h"
#include "GameProcess.h"

class TESObjectCELL;
struct ScriptEventList;
class ActiveEffect;
class NiNode;
class Animation;

// 008
class TESChildCell
{
public:
	TESChildCell();
	~TESChildCell();

	// no virtual destructor
	virtual TESObjectCELL* GetPersistentCell(void);		// 000

//	void	** vtbl;	// 00
};

// 68
class TESObjectREFR : public TESForm
{
public:
	MEMBER_FN_PREFIX(TESObjectREFR);

	TESObjectREFR();
	~TESObjectREFR();

	virtual void		Unk_4E(void);	// GetStartingPosition(Position, Rotation, WorldOrCell)
	virtual void		Unk_4F(void);
	virtual void		Unk_50(void);
	virtual void		Unk_51(void);
	virtual bool		CastShadows(void);
	virtual void		Unk_53(void);
	virtual void		Unk_54(void);
	virtual void		Unk_55(void);
	virtual void		Unk_56(void);
	virtual void		Unk_57(void);
	virtual void		Unk_58(void);
	virtual void		Unk_59(void);
	virtual void		Unk_5A(void);
	virtual void		Unk_5B(void);
	virtual void		Unk_5C(void);
	virtual void		Unk_5D(void);
	virtual void		Unk_5E(void);
	virtual TESObjectREFR* RemoveItem(TESForm* toRemove, BaseExtraList* extraList, UInt32 count, UInt32 unk3, UInt32 unk4, TESObjectREFR* destRef,
		UInt32 unk6, UInt32 unk7, UInt32 unk8, UInt8 unk9);	// 40 unk2 quantity? Returns the reference assigned to the removed item.
	virtual void		Unk_60(void);
	virtual void		Unk_61(void);	// Linked to AddItem, (item, count, ExtraDataList), func0042 in OBSE
	virtual void		Unk_62(void);	// Linked to Unequip (and or equip maybe)
	virtual void		Unk_63(void);
	virtual void		AddItem(TESForm* item, ExtraDataList* xDataList, UInt32 Quantity);	// Needs confirmation
	virtual void		Unk_65(void);
	virtual void		Unk_66(void);
	virtual void		Unk_67(void);					// Actor: GetMagicEffectList
	virtual bool		GetIsChildSize(bool checkHeight);		// 068 Actor: GetIsChildSize
	virtual UInt32		GetActorUnk0148(void);			// result can be interchanged with baseForm, so TESForm* ?
	virtual void		SetActorUnk0148(UInt32 arg0);
	virtual void		Unk_6B(void);
	virtual void		Unk_6C(void);	// REFR: GetBSFaceGenNiNodeSkinned
	virtual void		Unk_6D(void);	// REFR: calls 006C
	virtual void		Unk_6E(void);	// MobileActor: calls 006D then NiNode::Func0040
	virtual void		Unk_6F(void);
	virtual void		Unk_70(void);
	virtual void		AnimateNiNode(void);					// same in FOSE ! identical to Func0052 in OBSE which says (inits animation-related data, and more)
	virtual void		GenerateNiNode(bool arg0);				// same in FOSE !
	virtual void		Set3D(NiNode* niNode, bool unloadArt);	// same in FOSE !
	virtual NiNode* GetNiNode(void);						// same in FOSE !
	virtual void		Unk_75(void);
	virtual void		Unk_76(void);
	virtual void		Unk_77(void);
	virtual void		Unk_78(void);
	virtual AnimData* GetAnimData(void);			// 0079
	virtual ValidBip01Names* GetValidBip01Names(void);	// 007A	Character only
	virtual ValidBip01Names* CallGetValidBip01Names(void);
	virtual void		SetValidBip01Names(ValidBip01Names validBip01Names);
	virtual void		GetPos(void);				// GetPos or GetDistance
	virtual void		Unk_7E(UInt32 arg0);
	virtual void		Unk_7F(void);
	virtual void		Unk_80(UInt32 arg0);
	virtual void		Unk_81(UInt32 arg0);
	virtual void		Unk_82(void);
	virtual UInt32		Unk_83(void);
	virtual void		Unk_84(UInt32 arg0);
	virtual UInt32		Unk_85(void);			// 0 or GetActor::Unk01AC
	virtual bool		Unk_86(void);			// return false for Projectile, Actor and Creature, true for character and PlayerCharacter
	virtual bool		Unk_87(void);			// seems to always return 0
	virtual bool		Unk_88(void);			// seems to always return 0
	virtual void		Unk_89(void);
	virtual void		Unk_8A(void);			// SetParentCell (Interior only ?)
	virtual void		Unk_8B(void);			// IsDead = HasNoHealth (baseForm health <= 0 or Flags bit23 set)
	virtual bool		Unk_8C(void);
	virtual bool		Unk_8D(void);
	virtual void		Unk_8E(void);
	virtual void		Unk_8F(void);

	enum {
		kFlags_Unk00000002 = 0x00000002,
		kFlags_Deleted = 0x00000020,		// refr removed from .esp or savegame
		kFlags_Persistent = 0x00000400,		//shared bit with kFormFlags_QuestItem
		kFlags_Temporary = 0x00004000,
		kFlags_Taken = kFlags_Deleted | kFlags_Unk00000002,

		kChanged_Inventory = 0x08000000,
	};

	struct RenderState
	{
		UInt32	unk00;
		UInt32	unk04;
		float	unk08;		// waterLevel
		float	unk0C;
		UInt32	unk10;		// flags most likely
		NiNode* niNode;	// same in FOSE
		// possibly more, need to find alloc
	};

	struct EditorData {
		UInt32	unk00;	// 00
	};
	// 0C

#ifdef EDITOR
	EditorData	editorData;			// +04
#endif

	TESChildCell	childCell;				// 018

	UInt32			unk1C;					// 01C

	TESForm* baseForm;				// 020

	float			rotX, rotY, rotZ;		// 024 - either public or accessed via simple inline accessor common to all child classes
	float			posX, posY, posZ;		// 030 - seems to be private
	float			scale;					// 03C 

	TESObjectCELL* parentCell;			// 040
	ExtraDataList	extraDataList;			// 044
	RenderState* renderState;			// 064	- (05C in FOSE)

	ExtraScript* GetExtraScript() const;
	ScriptEventList* GetEventList() const;

	bool IsTaken() const { return (flags & kFlags_Taken) != 0; }
	bool IsPersistent() const { return (flags & kFlags_Persistent) != 0; }
	bool IsTemporary() { return (flags & kFlags_Temporary) ? true : false; }
	bool IsDeleted() const { return (flags & kFlags_Deleted) ? true : false; }

	bool Update3D();
	bool Update3D_v1c();	// Less worse version as used by some modders
	TESContainer* GetContainer();
	bool IsMapMarker();
	bool GetInventoryItems(InventoryItemsMap& invItems);
	ExtraDroppedItemList* GetDroppedItems();

	static TESObjectREFR* Create(bool bTemp = false);

	MEMBER_FN_PREFIX(TESObjectREFR);
#if RUNTIME
	DEFINE_MEMBER_FN(Activate, bool, 0x00573170, TESObjectREFR*, UInt32, UInt32, UInt32);	// Usage Activate(actionRef, 0, 0, 1); found inside Cmd_Activate_Execute as the last call (190 bytes)
	DEFINE_MEMBER_FN(Set3D, void, 0x0094EB40, NiNode*, bool);	// Usage Set3D(niNode, true); virtual func 0073
#endif
};

TESForm* GetPermanentBaseForm(TESObjectREFR* thisObj);	// For LevelledForm, find real baseForm, not temporary one.

STATIC_ASSERT(offsetof(TESObjectREFR, baseForm) == 0x020);
STATIC_ASSERT(offsetof(TESObjectREFR, extraDataList) == 0x044);
STATIC_ASSERT(sizeof(TESObjectREFR) == 0x068);

class BaseProcess;

// 088
class MobileObject : public TESObjectREFR
{
public:
	MobileObject();
	~MobileObject();

	virtual void		StartHighProcess(void);		// 090
	virtual void		Unk_91(void);
	virtual void		Unk_92(void);
	virtual void		Unk_93(void);
	virtual void		Unk_94(void);
	virtual void		Unk_95(void);
	virtual void		Unk_96(void);
	virtual void		Unk_97(void);
	virtual void		Unk_98(void);
	virtual void		Unk_99(void);
	virtual void		Unk_9A(void);
	virtual void		Unk_9B(void);
	virtual void		Unk_9C(void);
	virtual void		Unk_9D(void);
	virtual void		Unk_9E(void);
	virtual void		Unk_9F(void);
	virtual void		Unk_A0(void);	// StartConversation(targetActor, subjectLocationData, targetLocationData, headTrack, allowMovement, arg, topicID, arg, arg
	virtual void		Unk_A1(void);
	virtual void		Unk_A2(void);
	virtual void		Unk_A3(void);
	virtual void		Unk_A4(void);
	virtual void		Unk_A5(void);
	virtual void		Unk_A6(void);
	virtual void		Unk_A7(void);
	virtual void		Unk_A8(void);
	virtual void		Unk_A9(void);
	virtual void		Unk_AA(void);
	virtual void		Unk_AB(void);
	virtual void		Unk_AC(void);
	virtual void		Unk_AD(void);
	virtual void		Unk_AE(void);
	virtual void		Unk_AF(void);
	virtual void		Unk_B0(void);
	virtual void		Unk_B1(void);
	virtual void		Unk_B2(void);
	virtual void		Unk_B3(void);
	virtual void		Unk_B4(void);
	virtual void		Unk_B5(void);
	virtual void		Unk_B6(void);
	virtual void		Unk_B7(void);
	virtual void		Unk_B8(void);
	virtual void		Unk_B9(void);
	virtual void		Unk_BA(void);
	virtual void		Unk_BB(void);
	virtual void		Unk_BC(void);
	virtual void		Unk_BD(void);
	virtual void		Unk_BE(void);
	virtual void		Unk_BF(void);
	virtual void		Unk_C0(void);

	BaseProcess* baseProcess;	// 068
	UInt32		unk06C;			// 06C - loaded	set to the talking actor ref when initialising ExtraTalkingActor
	UInt32		unk070;			// 070 - loaded
	UInt32		unk074;			// 074 - loaded
	UInt32		unk078;			// 078 - loaded
	UInt8		unk07C;			// 07C - loaded
	UInt8		unk07D;			// 07D - loaded
	UInt8		unk07E;			// 07E - loaded
	UInt8		unk07F;			// 07F - loaded
	UInt8		unk080;			// 080 - loaded
	UInt8		unk081;			// 081 - loaded
	UInt8		unk082;			// 082 - cleared when starting combat on player
	UInt8		unk083;			// 083 - loaded
	UInt8		unk084;			// 084 - loaded
	UInt8		unk085;			// 085 - loaded
	UInt8		unk086;			// 086 - loaded
	UInt8		unk087;			// 087	Init'd to the inverse of NoLowLevelProcessing
};
STATIC_ASSERT(offsetof(MobileObject, baseProcess) == 0x068);
STATIC_ASSERT(sizeof(MobileObject) == 0x088);

// 00C
class MagicCaster
{
public:
	MagicCaster();
	~MagicCaster();

	UInt32 vtabl;
	UInt32 unk004;	// 004
	UInt32 unk008;	// 008
};

STATIC_ASSERT(sizeof(MagicCaster) == 0x00C);

typedef tList<ActiveEffect> EffectNode;
// 010
class MagicTarget
{
public:
	MagicTarget();
	~MagicTarget();

	virtual void	Destructor(void);
	virtual TESObjectREFR* GetParent(void);
	virtual EffectNode* GetEffectList(void);

	UInt8			byt004;		// 004 
	UInt8			byt005;		// 005 
	UInt8			byt006[2];	// 006-7
	tList<void*>	lst008;		// 008

	void RemoveEffect(EffectItem* effItem);

	void StopEffect(void* arg0, bool arg1)
	{
		ThisStdCall(0x8248E0, this, arg0, arg1);
	}
};

STATIC_ASSERT(sizeof(MagicTarget) == 0x010);

class hkaRaycastInterface
{
public:
	hkaRaycastInterface();
	~hkaRaycastInterface();
	virtual hkaRaycastInterface* Destroy(bool doFree);
	virtual void					Unk_01(void* arg0);
	virtual void					Unk_02(void);

	// Assumed to be 0x010 bytes due to context where the vftable is used
	UInt32	unk000[(0x010 - 0x004) >> 2];	// 0000
};
STATIC_ASSERT(sizeof(hkaRaycastInterface) == 0x010);

class bhkRagdollController : public hkaRaycastInterface
{
public:
	bhkRagdollController();
	~bhkRagdollController();

	UInt32	unk000[(0x021C - 0x010) >> 2];	// 0010
	UInt8	fill021C[3];					// 021C
	bool	bool021F;						// 021F	when null assume FIK status is false
	bool	fikStatus;						// 0220
	UInt8	fill0221[3];					// 0221
};
STATIC_ASSERT(sizeof(bhkRagdollController) == 0x0224);

class bhkRagdollPenetrationUtil;
class PlayerMover;
class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;

// Source: JIP - GameObjects.h L320
// 28
class PathingLocation
{
public:
	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);

	UInt32			unk04[9];	// 04
};

// B0
class PathingRequest : public NiRefObject
{
public:
	/*08*/virtual void	Unk_02(void);
	/*0C*/virtual void	Unk_03(void);
	/*10*/virtual void	Unk_04(void);
	/*14*/virtual void	Unk_05(void);
	/*18*/virtual void	Unk_06(void);
	/*1C*/virtual void	Unk_07(void);
	/*20*/virtual void	Unk_08(void);

	struct ActorData
	{
		TESForm* baseForm;
		void* inventoryChanges;
		bool		isAlarmed;
	};

	UInt32					unk08;					// 08
	PathingLocation			start;					// 0C
	PathingLocation			dest;					// 34
	ActorData				actorData;				// 5C
	float					actorRadius;			// 68
	float					flt6C;					// 6C
	float					goalZDelta;				// 70
	float					targetRadius;			// 74
	float					centerRadius;			// 78
	NiVector3				targetPt;				// 7C
	float					unk88;					// 88
	float					goalAngle;				// 8C
	float					initialPathHeading;		// 90
	void* avoidNodeArray;							// 94
	UInt8					bCantOpenDoors;			// 98
	UInt8					bFaceTargetAtGoal;		// 99
	UInt8					byte9A;					// 9A
	UInt8					bAllowIncompletePath;	// 9B
	UInt8					byte9C;					// 9C
	UInt8					bCanSwim;				// 9D
	UInt8					bCanFly;				// 9E
	UInt8					byte9F;					// 9F
	UInt8					bInitialPathHeading;	// A0
	UInt8					byteA1;					// A1
	UInt8					bCurvedPath;			// A2
	UInt8					byteA3;					// A3
	UInt8					bIgnoreLocks;			// A4
	UInt8					padA5[3];				// A5
	UInt32					iSmoothingRetryCount;	// A8
	UInt8					byteAC;					// AC
	UInt8					padAD[3];				// AD
};

// Source: JIP - GameObjects.h L383
// 88
class ActorMover
{
public:
	virtual void		Destroy(bool doFree);
	virtual void		Unk_01(void);
	virtual void		ClearMovementFlag(UInt32 flag);
	virtual void		SetMovementFlags(UInt32 movementFlags);
	virtual void		Unk_04(void);
	virtual void		Unk_05(void);
	virtual void		HandleTurnAnimationTimer(float timePassed);
	virtual void		Unk_07(void);
	virtual UInt32		GetMovementFlags();
	virtual void		Unk_09(void);
	virtual void		Unk_0A(void);
	virtual void		Unk_0B(void);
	virtual void		Unk_0C(void);
	virtual void		Unk_0D(void);
	virtual void		Unk_0E(void);

	enum MovementFlags
	{
		kMoveFlag_Forward = 1,
		kMoveFlag_Backward = 2,
		kMoveFlag_Left = 4,
		kMoveFlag_Right = 8,
		kMoveFlag_TurnLeft = 0x10,
		kMoveFlag_TurnRight = 0x20,
		kMoveFlag_IsKeyboard = 0x40,	// (returns that the movement is for non-controller)
		kMoveFlag_Walking = 0x100,
		kMoveFlag_Running = 0x200,
		kMoveFlag_Sneaking = 0x400,
		kMoveFlag_Swimming = 0x800,
		kMoveFlag_Jump = 0x1000,
		kMoveFlag_Flying = 0x2000,
		kMoveFlag_Fall = 0x4000,
		kMoveFlag_Slide = 0x8000
	};

	UInt32						unk04[3];			// 04
	NiVector3					overrideMovement;	// 10
	PathingRequest* pathingRequest;	// 1C
	void* pathingSolution;	// 20
	void* pathHandler;		// 24
	Actor* actor;				// 28
	UInt32						unk2C;				// 2C
	void* pathingMsgQueue;	// 30
	UInt32						movementFlags1;		// 34
	UInt32						unk38;				// 38
	UInt32						movementFlags2;		// 3C
	UInt32						unk40;				// 40
	PathingLocation				pathingLocation;	// 44
	UInt32						unk6C;				// 6C
	UInt8						bPathingFailed;		// 70
	UInt8						byte71;				// 71
	UInt8						byte72;				// 72
	UInt8						byte73;				// 73
	UInt8						bWaitingOnPath;		// 74
	UInt8						byte75;				// 75
	UInt8						byte76;				// 76
	UInt8						bOverrideMovement;	// 77
	UInt32						unk78;				// 78
	UInt32						unk7C;				// 7C
	UInt32						unk80;				// 80
	UInt32						unk84;				// 84
};
static_assert(sizeof(ActorMover) == 0x88);

typedef std::vector<TESForm*> EquippedItemsList;

// Source: JIP - GameObjects.h L465
struct ActorValueMod
{
	UInt8		avCode;
	UInt8		pad01[3];
	float		mod;
};

// 68
struct CombatTarget
{
	Actor* target;
	UInt32		unk04[25];
};


// 14
struct CombatAlly
{
	Actor* ally;
	UInt32		unk04[4];
};

struct CombatSearchLocation;
struct CombatSearchDoor;
struct CombatGroupCluster;

// 15C
struct CombatActors
{
	struct Unk0F0
	{
		NiVector3		vector00;
		UInt32			unk0C;
	};

	UInt32									unk000;				// 000
	UInt32									groupID;			// 004
	BSSimpleArray<CombatTarget>				targets;			// 008
	BSSimpleArray<CombatAlly>				allies;				// 018
	UInt32									unk028;				// 028
	UInt8									byte02C;			// 02C
	UInt8									pad02D[3];			// 02D
	NiPoint2								unk030;				// 030
	NiPoint2								unk038;				// 038
	UInt32									unk040;				// 040
	float									flt044;				// 044
	NiPoint2								unk048;				// 048
	NiPoint2								unk050;				// 050
	NiPoint2								unk058;				// 058
	NiPoint2								unk060;				// 060
	NiPoint2								unk068;				// 068
	NiPoint2								unk070;				// 070
	NiPoint2								unk078;				// 078
	NiPoint2								unk080;				// 080
	NiPoint2								unk088;				// 088
	NiPoint2								unk090;				// 090
	NiPoint2								unk098;				// 098
	NiPoint2								unk0A0;				// 0A0
	NiPoint2								unk0A8;				// 0A8
	NiPoint2								unk0B0;				// 0B0
	NiPoint2								unk0B8;				// 0B8
	float									sumThreatValue;		// 0C0
	float									averageDPS;			// 0C4
	float									flt0C8;				// 0C8
	float									flt0CC;				// 0CC
	UInt32									targetSearchState;	// 0D0	0 - Not searching; 1-2 - Searching
	NiRefObject* object0D4;			// 0D4
	NiPoint2								unk0D8;				// 0D8
	NiPoint2								unk0E0;				// 0E0
	float									flt0E8;				// 0E8
	UInt32									unk0EC;				// 0EC
	Unk0F0									unk0F0;				// 0F0
	NiVector3								vector100;			// 100
	float									flt10C;				// 10C
	BSSimpleArray<CombatSearchLocation>		searchLocations;	// 110
	BSSimpleArray<CombatSearchDoor>			searchDoors;		// 120
	NiRefObject* object130;			// 130
	UInt8									byte134;			// 134
	UInt8									pad135[3];			// 135
	BSSimpleArray<CombatGroupCluster>		groupClusters;		// 138
	UInt32									unk148;				// 148
	UInt32									unk14C;				// 14C
	UInt32									unk150;				// 150
	UInt8									byte154;			// 154
	UInt8									pad155[3];			// 155
	NiRefObject* object158;			// 158
};
static_assert(sizeof(CombatActors) == 0x15C);

class Actor : public MobileObject
{
public:
	/*304*/virtual UInt8	IsGuard();
	/*308*/virtual void		SetGuard(UInt8 setTo);
	/*30C*/virtual void		Unk_C3(void);
	/*310*/virtual void		Unk_C4(void);
	/*314*/virtual void		Unk_C5(void);
	/*318*/virtual void		Unk_C6(void);
	/*31C*/virtual void		SetIgnoreCrime(bool ignoreCrime);
	/*320*/virtual bool		GetIgnoreCrime();
	/*324*/virtual void		Resurrect(UInt8 arg1, UInt8 arg2, UInt8 arg3);
	/*328*/virtual void		Unk_CA(void);
	/*32C*/virtual void		Unk_CB(void);
	/*330*/virtual void		Unk_CC(void);
	/*334*/virtual void		Unk_CD(void);
	/*338*/virtual void		DamageHealthAndFatigue(float healthDmg, float fatigueDmg, Actor* source);
	/*33C*/virtual void		DamageActionPoints(float amount); // checks GetIsGodMode before decreasing
	/*340*/virtual void		Unk_D0(void);
	/*344*/virtual void		Unk_D1(void);
	/*348*/virtual void		UpdateMovement(float arg1, UInt32 arg2);
	/*34C*/virtual void		Unk_D3(void);
	/*350*/virtual void		Unk_D4(void);
	/*354*/virtual float	GetDefaultTurningSpeed();
	/*358*/virtual bool		IsOverencumbered();
	/*35C*/virtual void		Unk_D7(void);
	/*360*/virtual bool		IsPlayerRef();
	/*364*/virtual void		Unk_D9(void);
	/*368*/virtual void		Unk_DA(void);
	/*36C*/virtual void		Unk_DB(void);
	/*370*/virtual void		Unk_DC(void);
	/*374*/virtual void		Unk_DD(void);
	/*378*/virtual void		Unk_DE(void);
	/*37C*/virtual TESRace* GetRace();
	/*380*/virtual float	GetHandReachTimesCombatDistance();
	/*384*/virtual void		Unk_E1(void);
	/*388*/virtual void		Unk_E2(void);
	/*38C*/virtual bool		IsPushable();
	/*390*/virtual UInt32	GetActorType();	// Creature = 0, Character = 1, PlayerCharacter = 2
	/*394*/virtual void		SetActorValue(UInt32 avCode, float value);
	/*398*/virtual void		SetActorValueInt(UInt32 avCode, UInt32 value);
	/*39C*/virtual void		ModActorValue(UInt32 avCode, float modifier, Actor* attacker);
	/*3A0*/virtual void		Unk_E8(void);
	/*3A4*/virtual void		ForceActorValue(UInt32 avCode, float modifier, UInt32 arg3);
	/*3A8*/virtual void		ModActorValueInt(UInt32 avCode, int modifier, UInt32 arg3);
	/*3AC*/virtual void		DamageActorValue(UInt32 avCode, float damage, Actor* attacker);
	/*3B0*/virtual void		Unk_EC(void);
	/*3B4*/virtual void		Unk_ED(void);
	/*3B8*/virtual void		Unk_EE(void);
	/*3BC*/virtual ContChangesEntry* GetPreferedWeapon(UInt32 unk);
	/*3C0*/virtual void		Unk_F0(void);
	/*3C4*/virtual void		ResetArmorDRDT();
	/*3C8*/virtual bool		DamageItem(ContChangesEntry* itemEntry, float damage, int unused);
	/*3CC*/virtual void		DropItem(TESForm* itemForm, ExtraDataList* xDataList, SInt32 count, NiVector3* pos, int arg5);
	/*3D0*/virtual void		DoActivate(TESObjectREFR* activatedRef, UInt32 count, bool arg3);
	/*3D4*/virtual void		Unk_F5(void);
	/*3D8*/virtual void		Unk_F6(void);
	/*3DC*/virtual void		Unk_F7(void);
	/*3E0*/virtual bool		AddActorEffect(SpellItem* actorEffect);
	/*3E4*/virtual bool		RemoveActorEffect(SpellItem* actorEffect);
	/*3E8*/virtual void		Reload(TESObjectWEAP* weapon, UInt32 animType, UInt8 hasExtendedClip);
	/*3EC*/virtual void		Reload2(TESObjectWEAP* weapon, UInt32 animType, UInt8 hasExtendedClip, UInt8 isInstantSwapHotkey);
	/*3F0*/virtual void		DecreaseAmmo();
	/*3F4*/virtual void		Unk_FD(void);
	/*3F8*/virtual CombatActors* GetCombatGroup();
	/*3FC*/virtual void		Unk_FF(void);
	/*400*/virtual void		Unk_100(void);
	/*404*/virtual void		Unk_101(void);
	/*408*/virtual void		Unk_102(void);
	/*40C*/virtual void		Unk_103(void);
	/*410*/virtual void		Unk_104(void);
	/*414*/virtual void		Unk_105(void);
	/*418*/virtual void		InitGetUpPackage();
	/*41C*/virtual void		SetAlpha(float alpha);
	/*420*/virtual float	GetAlpha();
	/*424*/virtual void		ForceAttackActor(Actor* target, CombatActors* combatGroup, UInt8 arg3, UInt32 arg4, UInt8 arg5, UInt32 arg6, UInt32 arg7, UInt32 arg8);
	/*428*/virtual void* GetCombatController();
	/*42C*/virtual Actor* GetCombatTarget();
	/*430*/virtual void		UpdateCombat();
	/*434*/virtual void		StopCombat(Actor* target);
	/*438*/virtual void		Unk_10E(void);
	/*43C*/virtual float	GetTotalArmorDR();
	/*440*/virtual float	GetTotalArmorDT();
	/*444*/virtual UInt32	Unk_111(void);
	/*448*/virtual bool		IsTrespassing();
	/*44C*/virtual void		Unk_113(void);
	/*450*/virtual void		Unk_114(void);
	/*454*/virtual void		Unk_115(void);
	/*458*/virtual float	CalculateMoveSpeed();
	/*45C*/virtual float	CalculateRunSpeed();
	/*460*/virtual void		Unk_118(void);
	/*464*/virtual void		Unk_119(void);
	/*468*/virtual void		Unk_11A(void);
	/*46C*/virtual void		Unk_11B(void);
	/*470*/virtual bool		GetAttacked();
	/*474*/virtual void		Unk_11D(void);
	/*478*/virtual void		Unk_11E(void);
	/*47C*/virtual void		Unk_11F(void);
	/*480*/virtual void		Unk_120(void);
	/*484*/virtual void		Unk_121(void);
	/*488*/virtual void		RewardXP(UInt32 amount);
	/*48C*/virtual void		Unk_123(void);
	/*490*/virtual void		Unk_124(void);
	/*494*/virtual void		Unk_125(void);
	/*498*/virtual void		SetPerkRank(BGSPerk* perk, UInt8 rank, bool alt);
	/*49C*/virtual void		RemovePerk(BGSPerk* perk, bool alt);
	/*4A0*/virtual UInt8	GetPerkRank(BGSPerk* perk, bool alt);
	/*4A4*/virtual void		AddPerkEntryPoint(BGSEntryPointPerkEntry* perkEntry, bool alt);
	/*4A8*/virtual void		RemovePerkEntryPoint(BGSEntryPointPerkEntry* perkEntry, bool alt);
	/*4AC*/virtual tList<BGSEntryPointPerkEntry>* GetPerkEntryPointList(UInt8 entryPointID, bool alt);
	/*4B0*/virtual void		Unk_12C(void);
	/*4B4*/virtual bool		GetIsImmobileCreature();
	/*4B8*/virtual void		DoHealthDamage(Actor* attacker, float damage);
	/*4BC*/virtual void		Unk_12F(void);
	/*4C0*/virtual void		Unk_130(void);
	/*4C4*/virtual float	Unk_131(void);
	/*4C8*/virtual void		HandleHeadTracking(float arg1);
	/*4CC*/virtual void		UpdateHeadTrackingEmotions(UInt32 arg1);
	/*4D0*/virtual void		Unk_134(void);
	/*4D4*/virtual void		Unk_135(void);
	/*4D8*/virtual NiVector3* GetAnticipatedLocation(NiVector3* resPos, float time);

	enum LifeStates
	{
		kLifeState_Alive = 0,
		kLifeState_Dying = 1,
		kLifeState_Dead = 2,
		kLifeState_Unconscious = 3,
		kLifeState_Reanimate = 4,
		kLifeState_Restrained = 5
	};

	MagicCaster			magicCaster;			// 088
	MagicTarget			magicTarget;			// 094
	ActorValueOwner		avOwner;				// 0A4
	CachedValuesOwner	cvOwner;				// 0A8

	bhkRagdollController* ragDollController;			// 0AC
	bhkRagdollPenetrationUtil* ragDollPentrationUtil;		// 0B0
	UInt32								unk0B4;						// 0B4-
	float								flt0B8;						// 0B8
	bool								bAIState;					// 0BC-
	UInt8								byte0BD;					// 0BD
	UInt8								byte0BE;					// 0BE
	UInt8								byte0BF;					// 0BF
	Actor* killer;					// 0C0
	UInt8								byte0C4;					// 0C4-
	UInt8								byte0C5;					// 0C5
	UInt8								byte0C6;					// 0C6
	UInt8								byte0C7;					// 0C7
	float								flt0C8;						// 0C8
	float								flt0CC;						// 0CC
	tList<ActorValueMod>				forceAVList;				// 0D0
	UInt8								byte0D8;					// 0D8
	UInt8								byte0D9;					// 0D9
	UInt8								byte0DA;					// 0DA
	UInt8								byte0DB;					// 0DB
	UInt32								unk0DC;						// 0DC
	tList<ActorValueMod>				setAVList;					// 0E0
	UInt8								byte0E8;					// 0E8	const 1
	UInt8								byte0E9;					// 0E9
	UInt8								byte0EA;					// 0EA
	UInt8								byte0EB;					// 0EB
	UInt32								unk0EC;						// 0EC
	UInt8								byte0F0;					// 0F0-
	UInt8								byte0F1;					// 0F1-
	UInt8								byte0F2;					// 0F2
	UInt8								byte0F3;					// 0F3
	tList<void>							list0F4;					// 0F4
	tList<void>							list0FC;					// 0FC
	bool								isInCombat;					// 104
	UInt8								jipActorFlags1;				// 105
	UInt8								jipActorFlags2;				// 106
	UInt8								jipActorFlags3;				// 107
	UInt32								lifeState;					// 108	saved as byte HasHealth
	UInt32								criticalStage;				// 10C
	UInt32								unk110;						// 110-
	float								painSoundTimer;				// 114
	UInt8								byte118;					// 118-
	UInt8								byte119;					// 119+
	UInt8								byte11A;					// 11A
	UInt8								byte11B;					// 11B
	UInt32								unk11C;						// 11C-
	UInt32								resetTime;					// 120-
	bool								forceRun;					// 124
	bool								forceSneak;					// 125
	UInt8								byte126;					// 126-
	bool								searchingForEnemies;		// 127
	Actor* combatTarget;				// 128
	BSSimpleArray<Actor*>* combatTargets;				// 12C
	BSSimpleArray<Actor*>* combatAllies;				// 130
	UInt8								byte134;					// 134-
	UInt8								byte135;					// 135+
	UInt8								byte136;					// 136
	UInt8								byte137;					// 137
	UInt32								unk138;						// 138-
	UInt32								minorCrimeCount;			// 13C
	UInt32								actorFlags;					// 140	0x80000000 - IsEssential
	bool								ignoreCrime;				// 144
	UInt8								byte145;					// 145	Has to do with package evaluation
	UInt8								byte146;					// 146	Has to do with package evaluation
	UInt8								byte147;					// 147
	UInt32								unk148;						// 148-
	UInt8								inWater;					// 14C
	UInt8								isSwimming;					// 14D
	UInt8								byte14E;					// 14E
	UInt8								byte14F;					// 14F
	UInt32								unk150;						// 150-
	float								flt154;						// 154
	float								flt158;						// 158
	UInt8								byte15C;					// 15C-
	UInt8								byte15D;					// 15D-
	UInt8								byte15E;					// 15E
	UInt8								byte15F;					// 15F
	NiVector3							startingPos;				// 160
	float								startingZRot;				// 16C
	TESForm* startingWorldOrCell;		// 170
	UInt8								byte174;					// 174-
	UInt8								byte175;					// 175-
	UInt8								byte176;					// 176
	UInt8								byte177;					// 177
	float								flt178;						// 178
	float								weaponSpread1;				// 17C
	float								weaponSpread2;				// 180
	float								weaponSpread3;				// 184
	float								flt188;						// 188
	UInt8								byte18C;					// 18C-
	bool								isTeammate;					// 18D
	UInt8								byte18E;					// 18E-
	UInt8								byte18F;					// 18F
	ActorMover* actorMover;				// 190
	UInt32								unk194;						// 194-
	UInt32								unk198;						// 198-
	float								flt19C;						// 19C
	UInt32								unk1A0;						// 1A0-
	UInt32								speechExpression;			// 1A4
	UInt32								emotionValue;				// 1A8
	UInt32								sitSleepState;				// 1AC-
	UInt8								isImmobileCreature;			// 1B0-
	bool								forceHit;					// 1B1-
	UInt8								byte1B2;					// 1B2
	UInt8								byte1B3;					// 1B3

	// OBSE: unk1 looks like quantity, usu. 1; ignored for ammo (equips entire stack). In NVSE, pretty much always forced internally to 1 
	// OBSE: itemExtraList is NULL as the container changes entry is not resolved before the call
	// NVSE: Default values are those used by the vanilla script functions.
	__forceinline void EquipItem(TESForm* objType, UInt32 equipCount = 1, ExtraDataList* itemExtraList = NULL, bool applyEnchantment = 1, bool lockEquip = 0, bool noMessage = 1)
	{
		ThisCall(0x88C650, this, objType, equipCount, itemExtraList, applyEnchantment, lockEquip, noMessage);
	}
	__forceinline void UnequipItem(TESForm* objType, UInt32 unequipCount = 1, ExtraDataList* itemExtraList = NULL, bool arg4 = 1, bool lockUnequip = 0, bool noMessage = 1)
	{
		ThisCall(0x88C790, this, objType, unequipCount, itemExtraList, arg4, lockUnequip, noMessage);
	}

	//EquippedItemsList GetEquippedItems();
	//ExtraContainerDataArray GetEquippedEntryDataList();
	//ExtraContainerExtendDataArray GetEquippedExtendDataList();

	bool GetDead() const { return (lifeState == 1) || (lifeState == 2); }
	bool GetRestrained() const { return lifeState == 5; }

	TESActorBase* GetActorBase() const;
	bool GetLOS(Actor* target) const;
	char GetCurrentAIPackage() const;
	char GetCurrentAIProcedure() const;
	bool IsFleeing() const;
	ContChangesEntry* GetWeaponInfo() const;
	ContChangesEntry* GetAmmoInfo() const;
	TESObjectWEAP* GetEquippedWeapon() const;
	bool IsItemEquipped(TESForm* item) const;
	UInt8 EquippedWeaponHasMod(UInt32 modType) const;
	bool IsSneaking() const;
	void StopCombat();
	bool __fastcall IsInCombatWith(Actor* target) const;
	int __fastcall GetDetectionValue(Actor* detected) const;
	TESPackage* GetStablePackage() const;
	void* GetPackageInfo() const;
	TESObjectREFR* GetPackageTarget() const;
	TESCombatStyle* GetCombatStyle() const;
	SInt8 GetKnockedState() const;
	bool IsWeaponOut() const;
	void UpdateActiveEffects(MagicItem* magicItem, EffectItem* effItem, bool addNew);
	bool GetIsGhost() const;
	float GetRadiationLevel();
	void* AddBackUpPackage(TESObjectREFR* targetRef, TESObjectCELL* targetCell, UInt32 flags);
	void __fastcall TurnToFaceObject(TESObjectREFR* target);
	void __vectorcall TurnAngle(float angle);
	void PlayAnimGroup(UInt32 animGroupID);
	UInt32 GetLevel() const;
	double GetKillXP() const;
	void GetHitDataValue(UInt32 valueType, double* result) const;
	void DismemberLimb(UInt32 bodyPartID, bool explode);
	void EquipItemAlt(ContChangesEntry* entry, UInt32 noUnequip = 0, UInt32 noMessage = 1);
	bool HasNoPath() const;
	bool CanBePushed() const;
	float __vectorcall AdjustPushForce(float baseForce);
	void PushActor(float force, float angle, TESObjectREFR* originRef);
	int GetGroundMaterial() const;
	__forceinline void RefreshAnimData()
	{
		ThisCall(0x8B0B00, this, 0);
	}
};


STATIC_ASSERT(offsetof(Actor, magicCaster) == 0x088);

class Character : public Actor
{
public:
	Character();
	~Character();

	virtual void		Unk_137(void);
	virtual void		Unk_138(void);

	ValidBip01Names* validBip01Names;	// 1B4
	float			flt1B8;				// 1B8
	float			flt1BC;				// 1BC
	UInt8			byt1C0;				// 1C0
	UInt8			byt1C1;				// 1C1
	UInt16			unk1C2;				// 1C2
	float			flt1C4;				// 1C4
};

typedef tList<BGSQuestObjective::Target> QuestObjectiveTargets;

// Source: JIP - GameObjects.h L809
struct MusicMarker
{
	TESObjectREFR* markerRef;
	ExtraAudioMarker::Data* markerData;

	MusicMarker(TESObjectREFR* _markerRef, ExtraAudioMarker::Data* data) : markerRef(_markerRef), markerData(data) {}

	bool operator<(const MusicMarker& rhs) const { return markerData->mediaLocCtrlID < rhs.markerData->mediaLocCtrlID; }
};

// Source: JIP - GameObjects.h L819
struct PerkRank
{
	BGSPerk* perk;
	UInt8		rank;
	UInt8		pad05[3];
};

class PerkRankFinder
{
	BGSPerk* m_perk;

public:
	PerkRankFinder(BGSPerk* _perk) : m_perk(_perk) {}

	bool Accept(PerkRank* perkRank) const { return perkRank->perk == m_perk; }
};

// Source: JIP - GameObjects.h L836
struct CasinoStats
{
	UInt32		casinoRefID;
	UInt32		earnings;
	UInt16		unk08;
	UInt8		gap0A[2];
};

// Source: JIP - GameObjects.h L844
// E50
class PlayerCharacter : public Character
{
public:
	// used to flag controls as disabled in disabledControlFlags
	enum
	{
		kControlFlag_Movement = 1 << 0,
		kControlFlag_Look = 1 << 1,
		kControlFlag_Pipboy = 1 << 2,
		kControlFlag_Fight = 1 << 3,
		kControlFlag_POVSwitch = 1 << 4,
		kControlFlag_RolloverText = 1 << 5,
		kControlFlag_Sneak = 1 << 6,
	};

	/*4E4*/virtual void		Unk_139(void);
	/*4E8*/virtual tList<PerkRank>* GetPerkRankList(bool forTeammates);

	struct MapMarkerInfo
	{
		ExtraMapMarker::MarkerData* markerData;
		TESObjectREFR* markerRef;
	};

	struct CompassTarget
	{
		Actor* target;
		UInt8		isHostile;
		UInt8		isDetected;
		UInt8		pad06[2];
	};

	struct PCLevelData
	{
		UInt8		byte00;
		UInt8		pad01[3];
		UInt32		xpToNextLevel;
		UInt8		byte08;
		UInt8		pad09[3];
	};

	struct CameraCollision		// C'tor @ 0x620850
	{
		void* phantom00;
		void* phantom04;
	};

	UInt32								unk1C8[15];				// 1C8	208 could be a DialogPackage
	UInt8								byte204;				// 204
	UInt8								byte205;				// 205
	UInt8								recalcQuestTargets;		// 206
	UInt8								byte207;				// 207
	TESPackage*							package208;				// 208
	void*								unk20C;					// 20C
	tList<ActiveEffect>*				activeEffects;			// 210
	MagicItem*							pcMagicItem;			// 214
	MagicTarget*						pcMagicTarget;			// 218
	CameraCollision*					cameaCollision;			// 21C
	UInt32								unk220[8];				// 220	224 is a package of type 1C
	bool								showQuestItems;			// 240
	UInt8								byte241;				// 241
	UInt8								byte242;				// 242
	UInt8								byte243;				// 243
	float								unk244[77];				// 244	have to be a set of ActorValue
	float								permAVMods[77];			// 378	have to be a set of ActorValue
	float								flt4AC;					// 4AC
	float								actorValues4B0[77];		// 4B0	have to be a set of ActorValue
	tList<BGSNote>						notes;					// 5E4
	ImageSpaceModifierInstanceDOF*		unk5EC;					// 5EC
	ImageSpaceModifierInstanceDOF*		unk5F0;					// 5F0
	ImageSpaceModifierInstanceDRB*		unk5F4;					// 5F4
	UInt8								byte5F8;				// 5F8
	UInt8								byte5F9;				// 5F9
	UInt8								byte5FA;				// 5FA
	UInt8								byte5FB;				// 5FB
	tList<TESObjectREFR>				teammates;				// 5FC
	TESObjectREFR*						lastExteriorDoor;		// 604
	UInt8								isPlayingAttackSound;	// 608
	UInt8								pad609[3];				// 609
	tList<void>*						actionList;				// 60C
	tList<CasinoStats>*					casinoDataList;			// 610
	tList<TESCaravanCard>*				caravanCards1;			// 614
	tList<TESCaravanCard>*				caravanCards2;			// 618
	UInt32								unk61C[6];				// 61C
	void*								ptr634;					// 634	bhkMouseSpringAction when there's a grabbed reference
	TESObjectREFR*						grabbedRef;				// 638
	UInt32								unk63C;					// 63C
	UInt32								unk640;					// 640
	float								grabbedWeight;			// 644
	UInt8								byte648;				// 648
	UInt8								byte649;				// 649
	bool								is3rdPerson;			// 64A
	bool								byte64B;				// 64B
	bool								byte64C;				// 64C
	UInt8								byte64D;				// 64D
	UInt8								byte64E;				// 64E
	bool								isUsingScope;			// 64F
	UInt8								byte650;				// 650
	bool								alwaysRun;				// 651
	bool								autoMove;				// 652
	UInt8								byte653;				// 653
	UInt32								sleepHours;				// 654
	UInt8								isResting;				// 658	Something to do with SleepDeprivation; see 0x969DCF
	UInt8								byte659;				// 659
	UInt8								byte65A;				// 65A
	UInt8								byte65B;				// 65B
	float								flt65C;					// 65C
	UInt32								unk660[3];				// 660
	UInt8								byte66C;				// 66C
	UInt8								byte66D;				// 66D
	UInt8								byte66E;				// 66E
	UInt8								byte66F;				// 66F
	float								worldFOV;				// 670
	float								firstPersonFOV;			// 674
	float								flt678;					// 678
	UInt32								unk67C;					// 67C
	UInt8								pcControlFlags;			// 680
	UInt8								byte681;				// 681
	UInt8								byte682;				// 682
	UInt8								byte683;				// 683
	UInt32								unk684[2];				// 684
	ValidBip01Names*					VB01N1stPerson;			// 68C
	AnimData*							animData1stPerson;		// 690
	NiNode*								node1stPerson;			// 694
	float								flt698;					// 698
	UInt32								unk69C[3];				// 69C
	tList<TESTopic>						topicList;				// 6A8
	UInt32								unk6B0[2];				// 6B0
	TESQuest*							activeQuest;			// 6B8
	tList<BGSQuestObjective>			questObjectiveList;		// 6BC
	tList<ObjectiveTarget>				questTargetList;		// 6C4
	UInt32								unk6CC[5];				// 6CC
	float								sortActorDistanceListTimer;	// 6E0
	float								seatedRotation;			// 6E4
	UInt32								unk6E8;					// 6E8
	UInt32								unk6EC;					// 6EC
	UInt32								playerSpell;			// 6F0
	TESObjectREFR*						placedMarkerRef;		// 6F4
	ObjectiveTargetData					placedMarkerData;		// 6F8
	float 								timeGrenadeHeld;		// 730
	UInt32								unk734[10];				// 734
	bool								inCharGen;				// 75C
	UInt8								byte75D;				// 75D
	UInt8								canUseTelekinesis;		// 75E
	UInt8								byte75F;				// 75F
	TESRegion*							currentRegion;			// 760
	TESRegionList						regionsList;			// 764
	UInt32								unk774[6];				// 774
	UInt32								initialTickCount;		// 78C
	UInt32								timePlayedCurrGame;		// 790	ms
	UInt32								unk794[6];				// 794
	TESForm*							pcWorldOrCell;			// 7AC
	UInt32								unk7B0;					// 7B0
	BGSMusicType*						musicType;				// 7B4
	UInt8								gameDifficulty;			// 7B8
	UInt8								byte7B9;				// 7B9
	UInt8								byte7BA;				// 7BA
	UInt8								byte7BB;				// 7BB
	bool								isHardcore;				// 7BC
	UInt8								byte7BD;				// 7BD
	UInt8								byte7BE;				// 7BE
	UInt8								byte7BF;				// 7BF
	UInt32								killCamMode;			// 7C0
	UInt8								inCombatWithGuard;		// 7C4
	bool								isYoung;				// 7C5
	bool								isToddler;				// 7C6
	bool								canUsePA;				// 7C7
	tList<MapMarkerInfo>				mapMarkers;				// 7C8
	TESWorldSpace*						mapMarkersWorldspace;	// 7D0
	tList<MusicMarker>					musicMarkers;			// 7D4
	MusicMarker*						currMusicMarker;		// 7DC
	float								flycamZRot;				// 7E0
	float								flycamXRot;				// 7E4
	NiVector3							flycamPos;				// 7E8
	UInt32								unk7F4[33];				// 7F4
	PCLevelData*						pcLevelData;			// 878
	tList<PerkRank>						perkRanksPC;			// 87C
	tList<BGSEntryPointPerkEntry>		perkEntriesPC[74];		// 884
	tList<PerkRank>						perkRanksTM;			// AD4
	tList<BGSEntryPointPerkEntry>		perkEntriesTM[74];		// ADC
	Actor* autoAimActor;										// D2C
	NiVector3							vecD30;					// D30
	NiObject*							unkD3C;					// D3C
	UInt32								unkD40;					// D40
	Actor*								reticleActor;			// D44
	tList<CompassTarget>*				compassTargets;			// D48
	UInt32								unkD4C;					// D4C
	float								lastAmmoSwapTime;		// D50
	UInt8								shouldOpenPipboy;		// D54
	UInt8								byteD55;				// D55
	UInt8								byteD56;				// D56
	UInt8								byteD57;				// D57
	NiVector3							cameraPos3rdPerson;		// D58
	CombatActors*						combatActors;			// D64
	UInt32								teammateCount;			// D68
	UInt32								unkD6C[5];				// D6C
	NiNode*								niNodeD80;				// D80
	UInt32								unkD84[12];				// D84
	NiNode*								niNodeDB4;				// DB4
	UInt32								unkDB8[7];				// DB8
	NiVector3							cameraPos1stPerson;		// DD4
	NiVector3							cameraPos;				// DE0
	void*								rigidBody;				// DEC
	bool								pcInCombat;				// DF0
	bool								pcUnseen;				// DF1
	UInt8								isLODApocalypse;		// DF2
	UInt8								byteDF3;				// DF3
	BSSimpleArray<ContChangesEntry*>	rockItLauncherContainer;// DF4
	float								rockItLauncherWeight;	// E04
	UInt8								nightVisionApplied;		// E08
	UInt8								padE09[3];				// E09
	UInt32								unkE0C[3];				// E0C
	float								killCamTimer;			// E18
	float								killCamCooldown;		// E1C
	UInt8								byteE20;				// E20
	UInt8								isUsingTurbo;			// E21
	UInt8								byteE22;				// E22
	UInt8								byteE23;				// E23
	float								fltE24;					// E24
	float								counterAttackTimer;		// E28
	UInt8								byteE2C;				// E2C
	UInt8								cateyeEnabled;			// E2D
	UInt8								spottingEnabled;		// E2E
	UInt8								byteE2F;				// E2F
	UInt32								itemDetectionTimer;		// E30
	NiNode*								ironSightNode;			// E34
	bool								noHardcoreTracking;		// E38	Appears to be unused
	bool								skipHCNeedsUpdate;		// E39
	UInt8								byteE3A;				// E3A
	UInt8								byteE3B;				// E3B
	BSSimpleArray<TESAmmo*>				hotkeyedWeaponAmmos;	// E3C
	UInt32								unkE4C;					// E4C

	bool IsThirdPerson() const { return is3rdPerson; }
	UInt32 GetMovementFlags() const { return actorMover->GetMovementFlags(); }	// 11: IsSwimming, 9: IsSneaking, 8: IsRunning, 7: IsWalking, 0: keep moving
	bool IsPlayerSwimming() const { return (actorMover->GetMovementFlags() & 0x800) != 0; }

	static PlayerCharacter* GetSingleton();

	__forceinline bool ToggleFirstPerson(bool toggleON)
	{
		return ThisCall<bool>(0x950110, this, toggleON);
	}
	int GetDetectionState();

	void ToggleSneak(bool toggle);
};

extern PlayerCharacter** g_thePlayer;

STATIC_ASSERT(offsetof(PlayerCharacter, ragDollController) == 0x0AC);
STATIC_ASSERT(offsetof(PlayerCharacter, questObjectiveList) == 0x6BC);
STATIC_ASSERT(offsetof(PlayerCharacter, actorMover) == 0x190);
//STATIC_ASSERT(sizeof(PlayerCharacter) == 0xE50);