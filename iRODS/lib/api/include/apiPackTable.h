/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* apiPackTable.h - This file may be generated by a program or script
 */

#ifndef API_PACK_TABLE_H
#define API_PACK_TABLE_H

#include "rods.h"
#include "packStruct.h"
#include "rodsPackInstruct.h"

/* need to include a header for for each API */
#include "apiHeaderAll.h"

//#ifdef  __cplusplus
//extern "C" {
//#endif

packInstruct_t MiscSvrInfo_PIG = MiscSvrInfo_PI;

packInstructArray_t ApiPackTable[] = {
        {"DataObjInp_PI", DataObjInp_PI},
        {"OpenedDataObjInp_PI", OpenedDataObjInp_PI},
#ifdef COMPAT_201
        {"dataObjReadInp_PI", dataObjReadInp_PI},
        {"dataObjWriteInp_PI", dataObjWriteInp_PI},
        {"dataObjCloseInp_PI", dataObjCloseInp_PI},
        {"OpenCollInp_PI", OpenCollInp_PI},
        {"CollInp_PI", CollInp_PI},
#endif

        {"DataCopyInp_PI", DataCopyInp_PI},
        {"DataObjCopyInp_PI", DataObjCopyInp_PI},
        {"fileOpenInp_PI", fileOpenInp_PI},
        {"fileChksumInp_PI", fileChksumInp_PI},
        {"fileChksumOut_PI", fileChksumOut_PI},
        {"fileLseekInp_PI", fileLseekInp_PI},
        {"fileLseekOut_PI", fileLseekOut_PI},
        {"fileStatInp_PI", fileStatInp_PI},
        {"fileUnlinkInp_PI", fileUnlinkInp_PI},
        {"fileReadInp_PI", fileReadInp_PI},
        {"fileCloseInp_PI", fileCloseInp_PI},
        {"fileGetFsFreeSpaceInp_PI", fileGetFsFreeSpaceInp_PI},
        {"fileGetFsFreeSpaceOut_PI", fileGetFsFreeSpaceOut_PI},
        {"fileMkdirInp_PI", fileMkdirInp_PI},
        {"fileOpendirInp_PI", fileOpendirInp_PI},
        {"fileReaddirInp_PI", fileReaddirInp_PI},
        {"fileRenameInp_PI", fileRenameInp_PI},
        {"fileRmdirInp_PI", fileRmdirInp_PI},
        {"fileWriteInp_PI", fileWriteInp_PI},
        {"fileClosedirInp_PI", fileClosedirInp_PI},
        {"MiscSvrInfo_PI", MiscSvrInfo_PI},
        {"ModDataObjMeta_PI", ModDataObjMeta_PI},
        {"authRequestOut_PI", authRequestOut_PI},
        {"authResponseInp_PI", authResponseInp_PI},
        {"CollInpNew_PI", CollInpNew_PI},
        {"ExecMyRuleInp_PI", ExecMyRuleInp_PI},
        {"simpleQueryInp_PI", simpleQueryInp_PI},
        {"generalAdminInp_PI", generalAdminInp_PI},
        {"authCheckInp_PI", authCheckInp_PI},
        {"authCheckOut_PI", authCheckOut_PI},
	    {"modAccessControlInp_PI", modAccessControlInp_PI},
        {"ModAVUMetadataInp_PI", ModAVUMetadataInp_PI},
        {"RULE_EXEC_MOD_INP_PI", RULE_EXEC_MOD_INP_PI},
        {"RULE_EXEC_DEL_INP_PI", RULE_EXEC_DEL_INP_PI},
        {"RULE_EXEC_SUBMIT_INP_PI", RULE_EXEC_SUBMIT_INP_PI},
        {"simpleQueryOut_PI", simpleQueryOut_PI},
        {"RegReplica_PI", RegReplica_PI},
        {"UnregDataObj_PI", UnregDataObj_PI},
        {"ExecCmd_PI", ExecCmd_PI},
        {"ExecCmd241_PI", ExecCmd241_PI},
        {"ExecCmdOut_PI", ExecCmdOut_PI},
        {"SubStructFileFdOpr_PI", SubStructFileFdOpr_PI},
        {"SubStructFileLseekInp_PI", SubStructFileLseekInp_PI},
        {"SubStructFileRenameInp_PI", SubStructFileRenameInp_PI},
        {"getTempPasswordOut_PI", getTempPasswordOut_PI},
        {"GetXmsgTicketInp_PI", GetXmsgTicketInp_PI},
        {"SendXmsgInp_PI", SendXmsgInp_PI},
        {"StructFileOprInp_PI", StructFileOprInp_PI},
        {"gsiAuthRequestOut_PI", gsiAuthRequestOut_PI},
        {"StructFileExtAndRegInp_PI", StructFileExtAndRegInp_PI},
        {"ChkObjPermAndStat_PI", ChkObjPermAndStat_PI},
        {"userAdminInp_PI", userAdminInp_PI},
        {"OpenStat_PI", OpenStat_PI},
        {"fileStageSyncInp_PI", fileStageSyncInp_PI},
        {"generalRowInsertInp_PI", generalRowInsertInp_PI},
        {"generalRowPurgeInp_PI", generalRowPurgeInp_PI},
        {"krbAuthRequestOut_PI", krbAuthRequestOut_PI},
        {"getRescQuotaInp_PI", getRescQuotaInp_PI},
        {"rescQuota_PI", rescQuota_PI},
        {"BulkOprInp_PI", BulkOprInp_PI},
        {"endTransactionInp_PI", endTransactionInp_PI},
        {"ProcStatInp_PI", ProcStatInp_PI},
        {"specificQueryInp_PI", specificQueryInp_PI},
        {"pamAuthRequestInp_PI", pamAuthRequestInp_PI},
        {"pamAuthRequestOut_PI", pamAuthRequestOut_PI},
        {"sslStartInp_PI", sslStartInp_PI},
        {"sslEndInp_PI", sslEndInp_PI},
       {PACK_TABLE_END_PI, (char *) NULL},
};

//#ifdef  __cplusplus
//}
//#endif

#endif	/* API_PACK_TABLE_H */
