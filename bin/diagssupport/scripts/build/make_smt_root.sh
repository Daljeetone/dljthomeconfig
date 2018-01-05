#!/bin/bash

# Change this!
SMT_CONFIG_PATH=/Volumes/Code/FactoryLLDiagsExtras/offline/Bonfire
SMT_STARTUP_PATH=/Volumes/Code/FactoryLLScriptsPlatforms/Scripts/N27

#Do not change below
INPUT=$1
BONFIRE_PATH=/AppleInternal/Diags/Logs/Bonfire
STARTUP_PATH=/AppleInternal/Diags/Scripts/N27


OUTPUT_SMT=${INPUT}_smt
OUTPUT_FATP=${INPUT}_fatp

cp -r ${INPUT} ${OUTPUT_SMT}
cp -r ${INPUT} ${OUTPUT_FATP}

# At this point FATP root is all ready.

cp ${SMT_CONFIG_PATH}/config-smt.txt ${OUTPUT_SMT}${BONFIRE_PATH}/config.txt
cp ${SMT_CONFIG_PATH}/Diags.manifest-smt ${OUTPUT_SMT}${BONFIRE_PATH}/Diags.manifest
cp ${SMT_STARTUP_PATH}/startup-smt.txt ${OUTPUT_SMT}${STARTUP_PATH}/startup.txt

pushd $(dirname $INPUT)

zip -r $(basename ${OUTPUT_SMT}) $(basename ${OUTPUT_SMT})
zip -r $(basename ${OUTPUT_FATP}) $(basename ${OUTPUT_FATP})

popd
