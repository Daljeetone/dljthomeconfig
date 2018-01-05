from CoreAutomationFramework import *
from xbs_build import XBSBuild
import subprocess

class MacOSXMachine(object):
    def __init__(self, obj):
        self.cam_machine = obj
    
    def __str__(self):
        return self.cam_machine.description()
    
    @classmethod
    def local_machine(cls):
        return MacOSXMachine(CAMMacOSXTarget.localMachine())
    
    @property
    def build(self):
        return XBSBuild(self.cam_machine.build())
            
    @property
    def hostname(self):
        return self.cam_machine.hostname()

    def sdk_version(self,sdk):
        return subprocess.Popen(['/usr/bin/xcodebuild', '-sdk', sdk, '-version', 'ProductBuildVersion'], stdout=subprocess.PIPE).communicate()[0].strip()
    
    @property
    def ios_sdk_version(self):
        return self.sdk_version("iphoneos.internal")
