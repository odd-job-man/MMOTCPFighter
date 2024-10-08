#pragma once
#include <windows.h>
#include "SerializeBuffer.h"

#include "Client.h"
extern SerializeBuffer g_sb1;

#pragma warning(disable : 4700)

enum PacketNum
{
	dfPACKET_CS_MOVE_START = 10,
	dfPACKET_CS_MOVE_STOP = 12,
	dfPACKET_CS_ATTACK1 = 20,
	dfPACKET_CS_ATTACK2 = 22,
	dfPACKET_CS_ATTACK3 = 24,
	dfPACKET_CS_ECHO = 252,
};

BOOL CS_MOVE_START(st_Client* pClient, BYTE byMoveDir, Pos ClientPos);
BOOL CS_MOVE_STOP(st_Client* pClient, BYTE byViewDir, Pos ClientPos);
BOOL CS_ATTACK1(st_Client* pClient, BYTE byViewDir, Pos ClientPos);
BOOL CS_ATTACK2(st_Client* pClient, BYTE byViewDir, Pos ClientPos);
BOOL CS_ATTACK3(st_Client* pClient, BYTE byViewDir, Pos ClientPos);
BOOL CS_ECHO(st_Client* pClient, DWORD dwTime);

BOOL PacketProc(void* pClient, BYTE byPacketType);
#pragma optimize("",on)

__forceinline BOOL CS_MOVE_START_RECV(st_Client* pClient)
{
	BYTE byMoveDir;
	Pos pos;
	g_sb1 >> byMoveDir >> pos.shX >> pos.shY;
	g_sb1.Clear();
	CS_MOVE_START(pClient, byMoveDir, pos);
	return TRUE;
}


__forceinline BOOL CS_MOVE_STOP_RECV(st_Client* pClient)
{
	BYTE byViewDir;
	Pos pos;
	g_sb1 >> byViewDir >> pos.shX >> pos.shY;
	g_sb1.Clear();
	CS_MOVE_STOP(pClient, byViewDir, pos);
	return TRUE;
}

__forceinline BOOL CS_ATTACK1_RECV(st_Client* pClient)
{
	BYTE byViewDir;
	Pos pos;
	g_sb1 >> byViewDir >> pos.shX >> pos.shY;
	g_sb1.Clear();
	CS_ATTACK1(pClient, byViewDir, pos);
	return TRUE;
}

__forceinline BOOL CS_ATTACK2_RECV(st_Client* pClient)
{
	BYTE byViewDir;
	Pos pos;
	g_sb1 >> byViewDir >> pos.shX >> pos.shY;
	g_sb1.Clear();
	CS_ATTACK2(pClient, byViewDir, pos);
	return TRUE;
}

__forceinline BOOL CS_ATTACK3_RECV(st_Client* pClient)
{
	BYTE byViewDir;
	Pos pos;
	g_sb1 >> byViewDir >> pos.shX >> pos.shY;
	g_sb1.Clear();
	CS_ATTACK3(pClient, byViewDir, pos);
	return TRUE;
}

__forceinline BOOL CS_ECHO_RECV(st_Client* pClient)
{
	DWORD dwTime;
	g_sb1 >> dwTime;
	g_sb1.Clear();
	CS_ECHO(pClient, dwTime);
	return TRUE;
}

__forceinline BOOL IsSync(Pos serverPos, Pos clientPos)
{
	BOOL IsYSync = abs(serverPos.shY - clientPos.shY) > dfERROR_RANGE;
	BOOL IsXSync = abs(serverPos.shX - serverPos.shX) > dfERROR_RANGE;
	return IsXSync || IsYSync;
}

__forceinline BOOL IsRRColide(Pos AttackerPos, Pos VictimPos, SHORT shAttackRangeY, SHORT shAttackRangeX)
{
	BOOL IsYCollide;
	BOOL IsXCollide;
	IsYCollide = ((AttackerPos.shY - shAttackRangeY / 2) < VictimPos.shY) && (VictimPos.shY < (AttackerPos.shY + shAttackRangeY / 2));
	IsXCollide = (AttackerPos.shX < VictimPos.shX) && (AttackerPos.shX + shAttackRangeX) > VictimPos.shX;
	return IsXCollide && IsYCollide;
}

__forceinline BOOL IsLLColide(Pos AttackerPos, Pos VictimPos, SHORT shAttackRangeY, SHORT shAttackRangeX)
{
	BOOL IsYCollide;
	BOOL IsXCollide;
	IsYCollide = ((AttackerPos.shY - shAttackRangeY / 2) < VictimPos.shY) && (VictimPos.shY < (AttackerPos.shY + shAttackRangeY / 2));
	IsXCollide = (AttackerPos.shX > VictimPos.shX) && (AttackerPos.shX - shAttackRangeX) < VictimPos.shX;
	return IsXCollide && IsYCollide;
}
#pragma optimize("",off)
