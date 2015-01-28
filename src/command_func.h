/* $Id$ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file command_func.h Functions related to commands. */

#ifndef COMMAND_FUNC_H
#define COMMAND_FUNC_H

#include "command_type.h"
#include "company_type.h"

/**
 * Define a default return value for a failed command.
 *
 * This variable contains a CommandCost object with is declared as "failed".
 * Other functions just need to return this error if there is an error,
 * which doesn't need to specific by a StringID.
 */
static const CommandCost CMD_ERROR = CommandCost(INVALID_STRING_ID);

/**
 * Returns from a function with a specific StringID as error.
 *
 * This macro is used to return from a function. The parameter contains the
 * StringID which will be returned.
 *
 * @param errcode The StringID to return
 */
#define return_cmd_error(errcode) return CommandCost(errcode);

CommandCost DoCommand(TileIndex tile, uint32 p1, uint32 p2, DoCommandFlag flags, uint32 cmd, const char *text = NULL);
CommandCost DoCommand(const Command *container, DoCommandFlag flags);

bool DoCommandP(TileIndex tile, uint32 p1, uint32 p2, uint32 cmd, const char *text = NULL, CommandSource cmdsrc = CMDSRC_SELF);
bool DoCommandP(const Command *container, CommandSource cmdsrc = CMDSRC_SELF);

CommandCost DoCommandPInternal(TileIndex tile, uint32 p1, uint32 p2, uint32 cmd, const char *text, bool estimate_only, CommandSource cmdsrc = CMDSRC_SELF);

#ifdef ENABLE_NETWORK
void NetworkSendCommand(TileIndex tile, uint32 p1, uint32 p2, uint32 cmd, const char *text, CompanyID company, CommandSource cmdsrc = CMDSRC_SELF);
#endif /* ENABLE_NETWORK */

extern Money _additional_cash_required;

bool IsValidCommand(uint32 cmd);
CommandFlags GetCommandFlags(uint32 cmd);
const char *GetCommandName(uint32 cmd);
Money GetAvailableMoneyForCommand();
bool IsCommandAllowedWhilePaused(uint32 cmd);

/**
 * Extracts the DC flags needed for DoCommand from the flags returned by GetCommandFlags
 * @param cmd_flags Flags from GetCommandFlags
 * @return flags for DoCommand
 */
static inline DoCommandFlag CommandFlagsToDCFlags(CommandFlags cmd_flags)
{
	DoCommandFlag flags = DC_NONE;
	if (cmd_flags & CMDF_NO_WATER) flags |= DC_NO_WATER;
	if (cmd_flags & CMDF_AUTO) flags |= DC_AUTO;
	if (cmd_flags & CMDF_ALL_TILES) flags |= DC_ALL_TILES;
	return flags;
}

/*** All command callbacks that exist ***/

/* airport_gui.cpp */
CommandCallback CcBuildAirport;

/* bridge_gui.cpp */
CommandCallback CcBuildBridge;

/* dock_gui.cpp */
CommandCallback CcBuildDocks;
CommandCallback CcBuildCanal;

/* depot_gui.cpp */
CommandCallback CcCloneVehicle;

/* group_gui.cpp */
CommandCallback CcCreateGroup;
CommandCallback CcAddVehicleGroup;

/* industry_gui.cpp */
CommandCallback CcBuildIndustry;

/* main_gui.cpp */
CommandCallback CcPlaySound10;
CommandCallback CcPlaceSign;
CommandCallback CcTerraform;
CommandCallback CcTerraformLand;
CommandCallback CcGiveMoney;

/* object_gui.cpp */
CommandCallback CcBuildObject;

/* rail_gui.cpp */
CommandCallback CcPlaySound1E;
CommandCallback CcSingleRail;
CommandCallback CcRailDepot;
CommandCallback CcStation;

/* road_gui.cpp */
CommandCallback CcPlaySound1D;
CommandCallback CcBuildTunnel;
CommandCallback CcRoadDepot;
CommandCallback CcRoadStop;

/* town_gui.cpp */
CommandCallback CcFoundTown;

/* vehicle_gui.cpp */
CommandCallback CcBuildVehicle;
CommandCallback CcStartStopVehicle;

#endif /* COMMAND_FUNC_H */
