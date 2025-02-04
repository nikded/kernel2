/*******************************************************************************
 *
 * This file is provided under a dual license.  When you use or
 * distribute this software, you may choose to be licensed under
 * version 2 of the GNU General Public License ("GPLv2 License")
 * or BSD License.
 *
 * GPLv2 License
 *
 * Copyright(C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 *
 * BSD LICENSE
 *
 * Copyright(C) 2016 MediaTek Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef _APS_H
#define _APS_H

/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************
 */

#define MAX_LINK_PLAN_NUM		3

/*******************************************************************************
 *                             D A T A   T Y P E S
 *******************************************************************************
 */

struct CU_INFO {
	uint32_t ucTotalCount;
	uint32_t ucTotalCu;
	enum ENUM_BAND eBand;
};

struct APS_INFO {
#if (CFG_SUPPORT_WIFI_6G == 1)
	/*
	 * Record 6G info from index 256
	 * | <-- 0-255 --> | <-- 256-511 --> |
	 * |	2.4G,5G    |	   6G	     |
	 */
	struct CU_INFO arCuInfo[512];
#else
	struct CU_INFO arCuInfo[256];
#endif
	uint8_t ucConsiderEsp;
	uint8_t fgIsGBandCoex;
};

struct AP_COLLECTION {
	struct LINK_ENTRY rLinkEntry;
	struct AP_COLLECTION *hnext; /* next entry in hash table list */
	uint32_t u4Index;
	struct BSS_DESC *aprTarget[MAX_LINK_PLAN_NUM];
	struct LINK arLinks[MAX_LINK_PLAN_NUM]; /* categorize AP by link */
	uint8_t ucLinkNum;
	uint8_t ucTotalCount; /* total BssDesc count */
	uint8_t aucMask[MAX_LINK_PLAN_NUM];
	uint8_t fgIsMld;
	uint8_t fgIsMatchBssid;
	uint8_t fgIsMatchBssidHint;
	uint8_t fgIsAllLinkInBlackList;
	uint8_t fgIsAllLinkConnected;
	uint32_t u4TotalTput;
	uint32_t u4TotalScore;
	uint8_t aucAddr[MAC_ADDR_LEN]; /* mld addr or bssid */
};

#if (CFG_SUPPORT_AVOID_DESENSE == 1)
struct WFA_DESENSE_CHANNEL_LIST {
	int8_t ucChLowerBound;
	int8_t ucChUpperBound;
};

extern const struct WFA_DESENSE_CHANNEL_LIST desenseChList[BAND_NUM];

#define IS_CHANNEL_IN_DESENSE_RANGE(_prAdapter, _ch, _band) \
	(!!(_prAdapter->fgIsNeedAvoidDesenseFreq && \
	(_band != BAND_2G4) && (_band < BAND_NUM) && \
	(_ch >= desenseChList[_band].ucChLowerBound) && \
	(_ch <= desenseChList[_band].ucChUpperBound)))
#endif

/*******************************************************************************
 *                            P U B L I C   D A T A
 *******************************************************************************
 */

/*******************************************************************************
 *                           P R I V A T E   D A T A
 *******************************************************************************
 */

/*******************************************************************************
 *                                 M A C R O S
 *******************************************************************************
 */

/*******************************************************************************
 *                   F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************
 */

/*******************************************************************************
 *                              F U N C T I O N S
 *******************************************************************************
 */

struct BSS_DESC *apsSearchBssDescByScore(struct ADAPTER *prAdapter,
	enum ENUM_ROAMING_REASON eRoamReason,
	uint8_t ucBssIndex, struct BSS_DESC_SET *prBssDescSet);

#endif

