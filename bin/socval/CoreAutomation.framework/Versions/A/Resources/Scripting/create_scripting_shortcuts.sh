#!/bin/bash

# create_scripting_shortcuts.sh
# CoreAutomation

if [[ -d "/AppleInternal/Library/Frameworks/CoreAutomation.framework" ]] ; then
CA_SCRIPTING_PATH="/AppleInternal/Library/Frameworks/CoreAutomation.framework/Versions/Current/Resources/Scripting"
else
DEVELOPER_PATH=`/usr/bin/xcode-select -print-path`
PLATFORM_PATH="${DEVELOPER_PATH}/Platforms/iPhoneOS.platform"
CA_SCRIPTING_PATH="${PLATFORM_PATH}/System/Library/PrivateFrameworks/CoreAutomation.framework/Versions/Current/Resources/Scripting"

echo "Platform Path: ${PLATFORM_PATH}"
fi

# Python
PYTHON_INSTALL_PATH=`python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()"`

sudo rm -rf "${PYTHON_INSTALL_PATH}/CoreAutomation.py"
sudo rm -rf "${PYTHON_INSTALL_PATH}/coreautomation"
sudo rm -rf "${PYTHON_INSTALL_PATH}/CoreAutomationFramework"

sudo ln -fs "${CA_SCRIPTING_PATH}/CoreAutomation.py" "${PYTHON_INSTALL_PATH}/CoreAutomation.py"
sudo ln -fs "${CA_SCRIPTING_PATH}/python_automation/coreautomation" "${PYTHON_INSTALL_PATH}/coreautomation"
sudo ln -fs "${CA_SCRIPTING_PATH}/python_automation/CoreAutomationFramework" "${PYTHON_INSTALL_PATH}/CoreAutomationFramework"

echo "Python libraries installed in '${PYTHON_INSTALL_PATH}'"

# Ruby hooks

# you aren't allowed to have certain names in B&I outputs, and it turns out that "core" is one of them
# sheesh
RUBY_INSTALL_PATHS=(
"/Library/Ruby/Site"    # system ruby
"/Library/Frameworks/MacRuby.framework/Versions/Current/usr/lib/ruby/site_ruby" # manual macruby
"/System/Library/PrivateFrameworks/MacRuby.framework/Versions/Current/usr/lib/ruby/site_ruby"   # system macruby (lion)
)
for RUBY_INSTALL_PATH in "${RUBY_INSTALL_PATHS[@]}" ; do
if [[ -d "$RUBY_INSTALL_PATH" ]] ; then
sudo rm -rf "${RUBY_INSTALL_PATH}/automation"
sudo ln -fs "${CA_SCRIPTING_PATH}/ruby_automation" "${RUBY_INSTALL_PATH}/automation"
echo "Ruby libraires installed in '${RUBY_INSTALL_PATH}'"
fi
done

# Perl
PERL_INSTALL_PATH=$(perl -e 'print ((grep ({m|^/Library/Perl/\d[^/]+/[^/]+|} @INC))[0] . "\n")')

sudo rm -rf "${PERL_INSTALL_PATH}/CoreAutomation"
sudo rm -rf "${PERL_INSTALL_PATH}/CoreAutomation.pm"

sudo ln -fs "${CA_SCRIPTING_PATH}/perl_automation/CoreAutomation.pm" "${PERL_INSTALL_PATH}/CoreAutomation.pm"
sudo ln -fs "${CA_SCRIPTING_PATH}/perl_automation/CoreAutomation" "${PERL_INSTALL_PATH}/CoreAutomation"

echo "Perl libraires installed in '${PERL_INSTALL_PATH}'"
