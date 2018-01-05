#!/bin/bash

set -o errexit

SrcDir=$(dirname $0)/Template
DstDir=$1
DstName=$(basename "${DstDir}")

if [ -z "$DstDir" ]; then
	echo "Usage: $0 <DestinationDir>"
	exit  1
fi
if [ -e "${DstDir}" ]; then
	echo "Already exists: ${DstDir}"
	exit 1
fi

# Copy the template to ${DstDir} and search/replace "Template" with the name provided by the user
mkdir -p ${DstDir}
cp -a ${SrcDir}/* ${DstDir}
mv ${DstDir}/Template.tex ${DstDir}/${DstName}.tex
mv ${DstDir}/TemplateBody.tex ${DstDir}/${DstName}Body.tex
mv ${DstDir}/TemplateTitle.tex ${DstDir}/${DstName}Title.tex
perl -pi -e "s/Template/${DstName}/;" ${DstDir}/Makefile
perl -pi -e "s/TemplateTitle/${DstName}Title/;" -e "s/TemplateBody/${DstName}Body/;" ${DstDir}/${DstName}.tex

echo "Success!"
echo "You may need to modify the COMMON_DIR setting in ${DstDir}/Makefile"
