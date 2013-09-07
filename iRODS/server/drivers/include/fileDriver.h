/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/

/* fileDriver.h - common header file for file driver
 */



#ifndef FILE_DRIVER_H
#define FILE_DRIVER_H

#ifndef windows_platform
#include <dirent.h>
#endif

#include "rods.h"
#include "rcConnect.h"
#include "objInfo.h"
#include "msParam.h"

// =-=-=-=-=-=-=-
// eirods includes
#include "eirods_error.h"
#include "eirods_first_class_object.h"
eirods::error fileCreate  ( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileOpen    ( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileRead    ( rsComm_t*, eirods::first_class_object_ptr, void*, int );
eirods::error fileWrite   ( rsComm_t*, eirods::first_class_object_ptr, void*, int );
eirods::error fileClose   ( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileUnlink  ( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileStat    ( rsComm_t*, eirods::first_class_object_ptr, struct stat* );
eirods::error fileLseek   ( rsComm_t*, eirods::first_class_object_ptr, long long, int ); 
eirods::error fileMkdir   ( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileRmdir   ( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileOpendir ( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileClosedir( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileReaddir ( rsComm_t*, eirods::first_class_object_ptr, struct rodsDirent** );
eirods::error fileRename  ( rsComm_t*, eirods::first_class_object_ptr, const std::string& );
eirods::error fileGetFsFreeSpace( rsComm_t*, eirods::first_class_object_ptr );
eirods::error fileStageToCache( rsComm_t*, eirods::first_class_object_ptr, const std::string& );
eirods::error fileSyncToArch  ( rsComm_t*, eirods::first_class_object_ptr, const std::string& );
eirods::error fileRegistered(rsComm_t* _comm, eirods::first_class_object_ptr _object );
eirods::error fileUnregistered(rsComm_t* _comm, eirods::first_class_object_ptr _object );
eirods::error fileModified(rsComm_t* _comm, eirods::first_class_object_ptr _object );
#endif	/* FILE_DRIVER_H */
