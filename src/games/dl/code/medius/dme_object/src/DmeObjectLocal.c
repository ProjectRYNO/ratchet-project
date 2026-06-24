#include "common.h"

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", InitObjectUpdateList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", AddToObjectUpdateList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", RemoveFromObjectUpdateList);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIGetObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetGetMyPersistantObjectCount);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIGetDataStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetGetStreamChannel);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIGetSessionMasterClientIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", RemoteObjectCreation);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", RemoteObjectUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", RemoteObjectDelete);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetFreeRemoteObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetFreeLocalObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIFreeObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", LocalObjectName2Index);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", FindFreeLocalObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIFreeAllObjects);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIJoin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetJoin2);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIRequestCreateRemoteNamedObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetICreateObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIOpenDataStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIEndDataStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIRequestObjectPrivateOwnership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIReleaseObjectPrivateOwnership);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", CheckFieldsForUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", SendGroupedFieldUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetISendObjectFullUpdate);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIAddToDataStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", ElementErrorExceedsThreshold);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", GlobalFieldErrorExceedsThreshold);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetGetDataStreamPacket);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", SendCloseDataStream);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetIDataStreamBytesFree);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", SendClientDataStreams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetISendFieldUpdates);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", SendClientNetObjectUpdates);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetSetSessionMasterClientIndex);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetCompleteJoin);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetFreeAllDataStreams);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetILeave);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", MyClientJoins);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetClientJoins);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", ReserveNetObjectsAndDataStreamsForClient);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", DmeObjectResolveInterface);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetISetMyClientObject);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetClientLeaves);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", NetFindNextSessionMaster);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", CreateGlobalObjectInfo);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/matchings/medius/dme_object/src/DmeObjectLocal", DestroyGlobalObjectInfo);
